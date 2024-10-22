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
			acutPrintf(L"非实体尺寸驱动标注，无法添加直径符号。\n");
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
		acedGetString(Adesk::kTrue, L"\n请确认在行首(B)或行尾(E)插入符号：B?",DimSymbol::beginningOrEnd);

		// 输入为空，默认行首
		if (DimSymbol::beginningOrEnd.empty())
		{
			DimSymbol::beginningOrEnd = "B";
		}

		acedGetString(Adesk::kFalse, L"\n请输入要插入的符号：", DimSymbol::customSymbol);
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
		acedGetString(Adesk::kTrue, L"\n请确认要在行首(B)或行尾(E)删除的符号：B?", DimSymbol::beginningOrEnd);

		// 输入为空，默认行首
		if (DimSymbol::beginningOrEnd.empty())
		{
			DimSymbol::beginningOrEnd = "B";
		}

		acedGetString(Adesk::kFalse, L"\n请输入要插入的符号：", DimSymbol::customSymbol);
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
            acutPrintf(L"行首没有要删除的符号。\n");
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
            acutPrintf(L"行尾没有要删除的符号。\n");
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
		int ret = acedEntSel(L"选择一个标注对象（按Esc或Enter取消命令）：\n", ent, pt);
		if (ret != RTNORM)
		{
			acutPrintf(L"取消命令。\n");
			DimSymbol::beginningOrEnd = "";
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