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

void DimSymbol::cbAddDiameter(AcDbDimension* pDim)
{
	AcString dimText;
	pDim->dimensionText(dimText);

	const AcString target = L"<>";
	const AcString diameterSymbol = L"%%c";
	if (dimText.isEmpty())
	{
		dimText = diameterSymbol + target;
	}
	else
	{
		int pos = dimText.find(target);
		if (pos != -1)
		{
			dimText.insert(pos, diameterSymbol);
		}
		else
		{
			acutPrintf(L"��ʵ��ߴ�������ע���޷����ֱ�����š�\n");
			return;
		}
	}
	pDim->setDimensionText(dimText.kACharPtr());
}

AcString DimSymbol::beginningOrEnd = "";
AcString DimSymbol::customSymbol = "";

void DimSymbol::cbAddCustomSymbol(AcDbDimension* pDim)
{
	if (DimSymbol::beginningOrEnd.empty())
	{
		acedGetString(Adesk::kTrue, L"\n��ȷ��������(B)����β(E)������ţ�B?",DimSymbol::beginningOrEnd);

		// ����Ϊ�գ�Ĭ������
		if (DimSymbol::beginningOrEnd.empty())
		{
			DimSymbol::beginningOrEnd = "B";
		}

		acedGetString(Adesk::kFalse, L"\n������Ҫ����ķ��ţ�", DimSymbol::customSymbol);
	}

	AcString dimText;
	pDim->dimensionText(dimText);

	if (DimSymbol::beginningOrEnd == "B" || DimSymbol::beginningOrEnd == "b")
	{
        dimText = DimSymbol::customSymbol + dimText;
	}
	else
	{
        dimText = dimText + DimSymbol::customSymbol;
	}

    pDim->setDimensionText(dimText.kACharPtr());
}

void DimSymbol::cbRemoveCustomSymbol(AcDbDimension* pDim)
{
	if (DimSymbol::beginningOrEnd.empty())
	{
		acedGetString(Adesk::kTrue, L"\n��ȷ��Ҫ������(B)����β(E)ɾ���ķ��ţ�B?", DimSymbol::beginningOrEnd);

		// ����Ϊ�գ�Ĭ������
		if (DimSymbol::beginningOrEnd.empty())
		{
			DimSymbol::beginningOrEnd = "B";
		}

		acedGetString(Adesk::kFalse, L"\n������Ҫ����ķ��ţ�", DimSymbol::customSymbol);
	}

	AcString dimText;
	pDim->dimensionText(dimText);

	if (DimSymbol::beginningOrEnd == "B" || DimSymbol::beginningOrEnd == "b")
	{
		if (dimText.substr(0, DimSymbol::customSymbol.length()) == DimSymbol::customSymbol)
		{
			dimText = dimText.substr(DimSymbol::customSymbol.length());
		}
		else
		{
            acutPrintf(L"����û��Ҫɾ���ķ��š�\n");
			return;
		}
	}
	else
	{
		if (dimText.substr(dimText.length() - DimSymbol::customSymbol.length(), DimSymbol::customSymbol.length()) == DimSymbol::customSymbol)
		{
            dimText = dimText.substr(0, dimText.length() - DimSymbol::customSymbol.length());
		}
		else
		{
            acutPrintf(L"��βû��Ҫɾ���ķ��š�\n");
            return;
		}
	}

	pDim->setDimensionText(dimText.kACharPtr());
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
			DimSymbol::beginningOrEnd = "";
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

void DimSymbol::cmdSetDiameter()
{
	selectAndProcess(cbAddDiameter);
}

void DimSymbol::cmdSetCustomSymbol()
{
	selectAndProcess(cbAddCustomSymbol);
}

void DimSymbol::cmdCancelCustomSymbol()
{
	selectAndProcess(cbRemoveCustomSymbol);
}