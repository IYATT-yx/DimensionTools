#include "StdAfx.h"
#include "DimensionTools.hpp"
#include "DimLock.hpp"
#include "DimSymbol.hpp"

void DimensionTools::init()
{
	acedRegCmds->addCommand(L"IYATTyxDimensionTools", L"LD", L"LD", ACRX_CMD_MODAL, DimLock::cmdLockDim); // LD - Lock Dimension
	acedRegCmds->addCommand(L"IYATTyxDimensionTools", L"RD", L"RD", ACRX_CMD_MODAL, DimLock::cmdResetDim); // RD - Reset Dimension
	acedRegCmds->addCommand(L"IYATTyxDimensionTools", L"SRD", L"SRD", ACRX_CMD_MODAL, DimSymbol::cmdSetReferenceDimension); // SRD - Set Reference Dimension
	acedRegCmds->addCommand(L"IYATTyxDimensionTools", L"CRD", L"CRD", ACRX_CMD_MODAL, DimSymbol::cmdCancelReferenceDimension); // CRD - Cancel Reference Dimension
	acedRegCmds->addCommand(L"IYATTyxDimensionTools", L"SD", L"SD", ACRX_CMD_MODAL, DimSymbol::cmdSetDiameter); // SD - Set Diameter
	acedRegCmds->addCommand(L"IYATTyxDimensionTools", L"SCS", L"SCS", ACRX_CMD_MODAL, DimSymbol::cmdSetCustomSymbol); // SCS - Set Custom Symbol
	acedRegCmds->addCommand(L"IYATTyxDimensionTools", L"CCS", L"CCS", ACRX_CMD_MODAL, DimSymbol::cmdCancelCustomSymbol); // CCS - Cancel Custom Symbol
}

void DimensionTools::unload()
{
	acedRegCmds->removeGroup(L"IYATTyxDimensionTools");
}