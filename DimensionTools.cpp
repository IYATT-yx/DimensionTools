#include "StdAfx.h"
#include "DimensionTools.hpp"
#include "DimLock.hpp"

void DimensionTools::init()
{
	acedRegCmds->addCommand(L"IYATTyxDimensionTools", L"LD", L"LD", ACRX_CMD_MODAL, DimLock::cmdLockDim);
	acedRegCmds->addCommand(L"IYATTyxDimensionTools", L"RD", L"RD", ACRX_CMD_MODAL, DimLock::cmdResetDim);
}

void DimensionTools::unload()
{
	acedRegCmds->removeGroup(L"IYATTyxDimensionTools");
}