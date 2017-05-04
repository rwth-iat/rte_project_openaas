
/******************************************************************************
*
*   FILE
*   ----
*   aasDI.c
*
*   History
*   -------
*   2017-05-03   File created
*
*******************************************************************************
*
*   This file is generated by the 'acplt_builder' command
*
******************************************************************************/


#ifndef OV_COMPILE_LIBRARY_openaasOPCUAInterface
#define OV_COMPILE_LIBRARY_openaasOPCUAInterface
#endif


#include "openaasOPCUAInterface.h"
#include "libov/ov_macros.h"


OV_DLLFNCEXPORT OV_RESULT openaasOPCUAInterface_aasDI_AssetIPAddress_set(
    OV_INSTPTR_openaasOPCUAInterface_aasDI          pobj,
    const OV_STRING  value
) {
    return ov_string_setvalue(&pobj->v_AssetIPAddress,value);
}

OV_DLLFNCEXPORT OV_RESULT openaasOPCUAInterface_aasDI_AssetAASIdString_set(
    OV_INSTPTR_openaasOPCUAInterface_aasDI          pobj,
    const OV_STRING  value
) {
    return ov_string_setvalue(&pobj->v_AssetAASIdString,value);
}

OV_DLLFNCEXPORT OV_RESULT openaasOPCUAInterface_aasDI_AssetAASIdType_set(
    OV_INSTPTR_openaasOPCUAInterface_aasDI          pobj,
    const OV_UINT  value
) {
    pobj->v_AssetAASIdType = value;
    return OV_ERR_OK;
}

OV_DLLFNCEXPORT OV_RESULT openaasOPCUAInterface_aasDI_AASIdString_set(
    OV_INSTPTR_openaasOPCUAInterface_aasDI          pobj,
    const OV_STRING  value
) {
    return ov_string_setvalue(&pobj->v_AASIdString,value);
}

OV_DLLFNCEXPORT OV_RESULT openaasOPCUAInterface_aasDI_AASIdType_set(
    OV_INSTPTR_openaasOPCUAInterface_aasDI          pobj,
    const OV_UINT  value
) {
    pobj->v_AASIdType = value;
    return OV_ERR_OK;
}

OV_DLLFNCEXPORT OV_RESULT openaasOPCUAInterface_aasDI_StartAASDI_set(
    OV_INSTPTR_openaasOPCUAInterface_aasDI          pobj,
    const OV_BOOL  value
) {
    pobj->v_StartAASDI = value;
    return OV_ERR_OK;
}

OV_DLLFNCEXPORT OV_RESULT openaasOPCUAInterface_aasDI_StopAASDI_set(
    OV_INSTPTR_openaasOPCUAInterface_aasDI          pobj,
    const OV_BOOL  value
) {
    pobj->v_StopAASDI = value;
    return OV_ERR_OK;
}

OV_DLLFNCEXPORT OV_ACCESS openaasOPCUAInterface_aasDI_getaccess(
	OV_INSTPTR_ov_object	pobj,
	const OV_ELEMENT		*pelem,
	const OV_TICKET			*pticket
) {
    /*    
    *   local variables
    */
    OV_INSTPTR_openaasOPCUAInterface_aasDI pinst = Ov_StaticPtrCast(openaasOPCUAInterface_aasDI, pobj);

    return (OV_ACCESS)0;
}

OV_DLLFNCEXPORT void openaasOPCUAInterface_aasDI_typemethod(
	OV_INSTPTR_fb_functionblock	pfb,
	OV_TIME						*pltc
) {
    /*    
    *   local variables
    */
    OV_INSTPTR_openaasOPCUAInterface_aasDI pinst = Ov_StaticPtrCast(openaasOPCUAInterface_aasDI, pfb);

    return;
}

