#include "StdAfx.h"
#include "DimLock.hpp"

constexpr double PI = 3.14159265358979323846;

void DimLock::setPrecision(std::wstring& sMeasureValue, double& value, int& precision, bool isAugular)
{
    double factor = pow(10, precision);
    if (isAugular)
    {
        value = value / PI * 180;
    }
    sMeasureValue = std::to_wstring(static_cast<int>(value * factor + 0.51) / factor); // 【算法待验证】【算法待验证】【算法待验证】【算法待验证】【算法待验证】【算法待验证】【算法待验证】
    sMeasureValue.erase(sMeasureValue.find_last_not_of(L'0') + 1, std::wstring::npos);
    if (sMeasureValue.back() == L'.')
    {
        sMeasureValue.pop_back();
    }
}

bool DimLock::insertValue(std::wstring& sMeasureValue, std::wstring& sText)
{
    static const ACHAR* psPlaceholder = L"<>";
    static const size_t placeholderLen = wcslen(psPlaceholder);

    size_t pos = sText.find(psPlaceholder);
    if (pos != std::wstring::npos)
    {
        std::wstring sNewText = sText.substr(0, pos);
        sNewText += sMeasureValue;
        sNewText += sText.substr(pos + placeholderLen);
        sText = sNewText;
        return true;
    }
    else
    {
        return false;
    }
}

void DimLock::cbDimNumToText(AcDbDimension* pDimension)
{
    static int precision;
    static double measureValue;
    static std::wstring sMeasureValue;
    static std::wstring sText;

    sText = pDimension->dimensionText();

    pDimension->measurement(measureValue);

    if (pDimension->isA() == AcDb2LineAngularDimension::desc())
    {
        precision = pDimension->dimadec();
        DimLock::setPrecision(sMeasureValue, measureValue, precision, true);
        sMeasureValue = sMeasureValue + L"%%d";
    }
    else
    {
        precision = pDimension->dimdec();
        DimLock::setPrecision(sMeasureValue, measureValue, precision);
        if (pDimension->isA() == AcDbDiametricDimension::desc())
        {
            sMeasureValue = L"%%c" + sMeasureValue;
        }
        else if (pDimension->isA() == AcDbRadialDimension::desc())
        {
            sMeasureValue = L"R" + sMeasureValue;
        }
    }

    if (sText.length() == 0)
    {
        pDimension->setDimensionText(sMeasureValue.c_str());
        acutPrintf(L"测量值：%lf，设置值：%s\n", measureValue, sMeasureValue.c_str());
    }
    else
    {
        bool status = DimLock::insertValue(sMeasureValue, sText);
        if (status)
        {
            pDimension->setDimensionText(sText.c_str());
            acutPrintf(L"测量值：%lf，设置值：%s\n", measureValue, sText.c_str());
        }
        else
        {
            acutPrintf(L"纯文本标注：%s，不做任何处理。\n", sText.c_str());
            return;
        }
    }
}

void DimLock::cbResetDim(AcDbDimension* pDimension)
{
    pDimension->setDimensionText(L"");
}

void DimLock::selectSetForeach(CallbackFun pFun)
{
    ads_name ss = { 0, 0 };
    if (acedSSGet(nullptr, nullptr, nullptr, nullptr, ss) != RTNORM)
    {
        acutPrintf(L"获取选择集失败。\n");
        return;
    }

    Adesk::Int32 len = 0;
    if (acedSSLength(ss, &len) != RTNORM)
    {
        acutPrintf(L"获取选择集长度失败。\n");
        return;
    }

    for (Adesk::Int32 i = 0; i < len; ++i)
    {
        ads_name name = { 0, 0 };
        acedSSName(ss, i, name);

        AcDbObjectId objId;
        acdbGetObjectId(objId, name);

        AcDbEntity* pEntity = nullptr;
        if (acdbOpenObject(pEntity, objId, AcDb::kForWrite) != Acad::eOk) // 可写方式打开
        {
            continue;
        }

        if (pEntity->isKindOf(AcDbDimension::desc()))
        {
            AcDbDimension* pDimension = AcDbDimension::cast(pEntity);
            pFun(pDimension);
        }

        pEntity->close();
    }
    acedSSFree(ss);
}

void DimLock::cmdLockDim()
{
    DimLock::selectSetForeach(DimLock::cbDimNumToText);
}

void DimLock::cmdResetDim()
{
    DimLock::selectSetForeach(DimLock::cbResetDim);
}