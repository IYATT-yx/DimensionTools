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
	acutPrintf(L"����ֵ��%s\n", dimText.kACharPtr());
	pDim->setDimensionText(dimText.kACharPtr());
}

void DimSymbol::cbRemoveParentheses(AcDbDimension* pDim)
{
	AcString dimText;
    pDim->dimensionText(dimText);

	if (dimText.isEmpty())
	{
		acutPrintf(L"�ձ�ע����������\n");
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
		int ret = acedEntSel(L"ѡ��һ����ע���󣨰�Esc��Enterȡ�������\n", ent, pt);
		if (ret != RTNORM)
		{
			acutPrintf(L"ȡ�����\n");
			break;
		}

		if (acdbGetObjectId(objId, ent) != Acad::eOk)
		{
            acutPrintf(L"��ȡ����IDʧ�ܡ�\n");
            continue;
		}

		if (acdbOpenObject(pEnt, objId, AcDb::kForWrite) != Acad::eOk)
		{
            acutPrintf(L"�򿪶���ʧ�ܡ�\n");
			continue;
		}

		if (!pEnt->isKindOf(AcDbDimension::desc()))
		{
            acutPrintf(L"ѡ��Ĳ��Ǳ�ע����\n");
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