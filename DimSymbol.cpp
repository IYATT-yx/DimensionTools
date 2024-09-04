#include "StdAfx.h"
#include "DimSymbol.hpp"

void DimSymbol::cbAddParentheses(AcDbDimension* pDim)
{
	AcString dimText;
	pDim->dimensionText(dimText);

	if (dimText.isEmpty())
	{
		dimText = L"(<>)";
	}
	else
	{
		dimText = L"(" + dimText + L")";
	}
	acutPrintf(L"设置值：%s\n", dimText.kACharPtr());
	pDim->setDimensionText(dimText.kACharPtr());
}

void DimSymbol::cbRemoveParentheses(AcDbDimension* pDim)
{
	AcString dimText;
    pDim->dimensionText(dimText);

	if (dimText.isEmpty())
	{
		acutPrintf(L"空标注，不做处理。\n");
		return;
	}
	else
	{
		if (dimText[0] == L'(' && dimText[dimText.length() - 1] == L')')
		{
			dimText = dimText.mid(1, dimText.length() - 2);
			pDim->setDimensionText(dimText.kACharPtr());
		}
	}
}

void DimSymbol::selectAndProcess(CallbackFun pFun)
{
	ads_name  ent;
	ads_point pt;
	AcDbObjectId objId;
	AcDbEntity* pEnt = nullptr;

	while (true)
	{
		int ret = acedEntSel(L"选择一个标注对象（按Esc或Enter取消命令）：\n", ent, pt);
		if (ret != RTNORM)
		{
			acutPrintf(L"取消命令。\n");
			break;
		}

		if (acdbGetObjectId(objId, ent) != Acad::eOk)
		{
            acutPrintf(L"获取对象ID失败。\n");
            continue;
		}

		if (acdbOpenObject(pEnt, objId, AcDb::kForWrite) != Acad::eOk)
		{
            acutPrintf(L"打开对象失败。\n");
			continue;
		}

		if (!pEnt->isKindOf(AcDbDimension::desc()))
		{
            acutPrintf(L"选择的不是标注对象。\n");
			goto END;
		}

		AcDbDimension* pDim = AcDbDimension::cast(pEnt);
		pFun(pDim);
END:
		pEnt->close();
	}
}

void DimSymbol::cmdSetReferenceDimension()
{
    selectAndProcess(cbAddParentheses);
}

void DimSymbol::cmdCancelReferenceDimension()
{
    selectAndProcess(cbRemoveParentheses);
}