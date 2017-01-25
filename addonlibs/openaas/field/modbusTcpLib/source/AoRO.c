
/******************************************************************************
*
*   FILE
*   ----
*   AO.c
*
*   History
*   -------
*   2015-04-29   File created
*
*******************************************************************************
*
*   This file is generated by the 'acplt_builder' command
*
******************************************************************************/


#ifndef OV_COMPILE_LIBRARY_modbusTcpLib
#define OV_COMPILE_LIBRARY_modbusTcpLib
#endif


#include "modbusTcpLib.h"
#include "libov/ov_macros.h"

OV_DLLFNCEXPORT OV_RESULT modbusTcpLib_AoRO_RawHi_set(
    OV_INSTPTR_modbusTcpLib_AoRO          pobj,
    const OV_INT  value
) {
	if(value > 0xFFFF){
		return OV_ERR_BADVALUE;
	}
    pobj->v_RawHi = value;
    return OV_ERR_OK;
}

OV_DLLFNCEXPORT OV_RESULT modbusTcpLib_AoRO_RawLo_set(
    OV_INSTPTR_modbusTcpLib_AoRO          pobj,
    const OV_INT  value
) {
	if(value > 0xFFFF){
		return OV_ERR_BADVALUE;
	}
    pobj->v_RawLo = value;
    return OV_ERR_OK;
}

OV_DLLFNCEXPORT OV_RESULT modbusTcpLib_AoRO_SP_set(
    OV_INSTPTR_modbusTcpLib_AoRO          pobj,
    const OV_SINGLE  value
) {
	if(value > 1.0 || value < 0.0){
		return OV_ERR_BADVALUE;
	}
    pobj->v_SP = value;
    if(!pobj->v_rawSwitch){
    	pobj->v_FV = (pobj->v_SP * (OV_SINGLE)(pobj->v_RawHi - pobj->v_RawLo)) + pobj->v_RawLo;
    }
    return OV_ERR_OK;
}

OV_DLLFNCEXPORT OV_RESULT modbusTcpLib_AoRO_SPRaw_set(
    OV_INSTPTR_modbusTcpLib_AoRO          pobj,
    const OV_INT  value
) {
    pobj->v_SPRaw = value;
    if(pobj->v_rawSwitch){
    	pobj->v_FV = pobj->v_SPRaw;
    }
    return OV_ERR_OK;
}


OV_DLLFNCEXPORT OV_RESULT modbusTcpLib_AoRO_constructor(
	OV_INSTPTR_ov_object 	pobj
) {
    /*    
    *   local variables
    */
    OV_INSTPTR_modbusTcpLib_AoRO pinst = Ov_StaticPtrCast(modbusTcpLib_AoRO, pobj);
    OV_RESULT    result;

    /* do what the base class does first */
    result = modbusTcpLib_IOChannel_constructor(pobj);
    if(Ov_Fail(result))
         return result;

    /* do what */
    pinst->v_functionCode = 16;

    return OV_ERR_OK;
}

