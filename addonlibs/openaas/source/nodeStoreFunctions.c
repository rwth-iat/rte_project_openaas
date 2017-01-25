
/******************************************************************************
*
*   FILE
*   ----
*   nodeStoreFunctions.c
*
*   History
*   -------
*   2016-12-22   File created
*
*******************************************************************************
*
*   This file is generated by the 'acplt_builder' command
*
******************************************************************************/


#ifndef OV_COMPILE_LIBRARY_openaas
#define OV_COMPILE_LIBRARY_openaas
#endif


#include "openaas.h"
#include "libov/ov_macros.h"


OV_DLLFNCEXPORT OV_RESULT openaas_nodeStoreFunctions_constructor(
	OV_INSTPTR_ov_object 	pobj
) {
    /*    
    *   local variables
    */
    //OV_INSTPTR_openaas_nodeStoreFunctions pinst = Ov_StaticPtrCast(openaas_nodeStoreFunctions, pobj);
    OV_RESULT    result;

    /* do what the base class does first */
    result = ov_object_constructor(pobj);
    if(Ov_Fail(result))
         return result;

    /* do what */

    return OV_ERR_OK;
}


OV_DLLFNCEXPORT void openaas_nodeStoreFunctions_startup(
	OV_INSTPTR_ov_object 	pobj
) {
    /*
    *   local variables
    */
    OV_INSTPTR_openaas_nodeStoreFunctions pinst = Ov_StaticPtrCast(openaas_nodeStoreFunctions, pobj);

    /* do what the base class does first */
    ov_object_startup(pobj);

    /* do what */
    openaas_nodeStoreFunctions_ovNodeStoreInterfaceOpenAASNew(&pinst->v_NodeStoreInterface);

    return;
}

