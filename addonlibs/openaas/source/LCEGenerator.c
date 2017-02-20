
/******************************************************************************
*
*   FILE
*   ----
*   LCEGenerator.c
*
*   History
*   -------
*   2017-02-16   File created
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
#include "openaas_helpers.h"


OV_DLLFNCEXPORT OV_RESULT openaas_LCEGenerator_AASIdString_set(
    OV_INSTPTR_openaas_LCEGenerator          pobj,
    const OV_STRING  value
) {
    return ov_string_setvalue(&pobj->v_AASIdString,value);
}

OV_DLLFNCEXPORT OV_RESULT openaas_LCEGenerator_AASIdType_set(
    OV_INSTPTR_openaas_LCEGenerator          pobj,
    const OV_UINT  value
) {
    pobj->v_AASIdType = value;
    return OV_ERR_OK;
}

OV_DLLFNCEXPORT OV_RESULT openaas_LCEGenerator_LCECreatingInstanceIdString_set(
    OV_INSTPTR_openaas_LCEGenerator          pobj,
    const OV_STRING  value
) {
    return ov_string_setvalue(&pobj->v_LCECreatingInstanceIdString,value);
}

OV_DLLFNCEXPORT OV_RESULT openaas_LCEGenerator_LCECreatingInstanceIdType_set(
    OV_INSTPTR_openaas_LCEGenerator          pobj,
    const OV_UINT  value
) {
    pobj->v_LCECreatingInstanceIdType = value;
    return OV_ERR_OK;
}

OV_DLLFNCEXPORT OV_RESULT openaas_LCEGenerator_LCEWritingInstanceIdString_set(
    OV_INSTPTR_openaas_LCEGenerator          pobj,
    const OV_STRING  value
) {
    return ov_string_setvalue(&pobj->v_LCEWritingInstanceIdString,value);
}

OV_DLLFNCEXPORT OV_RESULT openaas_LCEGenerator_LCEWritingInstanceIdType_set(
    OV_INSTPTR_openaas_LCEGenerator          pobj,
    const OV_UINT  value
) {
    pobj->v_LCEWritingInstanceIdType = value;
    return OV_ERR_OK;
}

OV_DLLFNCEXPORT OV_RESULT openaas_LCEGenerator_LCEEventClass_set(
    OV_INSTPTR_openaas_LCEGenerator          pobj,
    const OV_STRING  value
) {
    return ov_string_setvalue(&pobj->v_LCEEventClass,value);
}

OV_DLLFNCEXPORT OV_RESULT openaas_LCEGenerator_LCESubject_set(
    OV_INSTPTR_openaas_LCEGenerator          pobj,
    const OV_STRING  value
) {
    return ov_string_setvalue(&pobj->v_LCESubject,value);
}

OV_DLLFNCEXPORT OV_RESULT openaas_LCEGenerator_LCEValue_set(
    OV_INSTPTR_openaas_LCEGenerator          pobj,
    const OV_ANY*  value
) {
    return ov_variable_setanyvalue(&pobj->v_LCEValue, value);
}

OV_DLLFNCEXPORT OV_RESULT openaas_LCEGenerator_StartLCEGenerator_set(
    OV_INSTPTR_openaas_LCEGenerator          pobj,
    const OV_BOOL  value
) {
    pobj->v_StartLCEGenerator = value;
	pobj->v_actimode = 1;
	pobj->v_iexreq = TRUE;
	pobj->v_cyctime.secs = 30;
    return OV_ERR_OK;
}

OV_DLLFNCEXPORT OV_RESULT openaas_LCEGenerator_StopLCEGenerator_set(
    OV_INSTPTR_openaas_LCEGenerator          pobj,
    const OV_BOOL  value
) {
    pobj->v_StopLCEGenerator = value;
    pobj->v_actimode = 0;
	pobj->v_iexreq = FALSE;
	return OV_ERR_OK;
}

OV_DLLFNCEXPORT OV_ACCESS openaas_LCEGenerator_getaccess(
	OV_INSTPTR_ov_object	pobj,
	const OV_ELEMENT		*pelem,
	const OV_TICKET			*pticket
) {
    /*    
    *   local variables
    */

    return (OV_ACCESS)(OV_AC_WRITE | OV_AC_READ | OV_AC_LINKABLE | OV_AC_UNLINKABLE | OV_AC_DELETEABLE | OV_AC_RENAMEABLE);
}

OV_DLLFNCEXPORT void openaas_LCEGenerator_typemethod(
	OV_INSTPTR_fb_functionblock	pfb,
	OV_TIME						*pltc
) {
    /*    
    *   local variables
    */
    OV_INSTPTR_openaas_LCEGenerator pinst = Ov_StaticPtrCast(openaas_LCEGenerator, pfb);
    OV_INSTPTR_raspi_gpioIn pgpioIn = NULL;
    OV_INSTPTR_fb_task	purtask = NULL;
    OV_RESULT ovResult = OV_ERR_OK;
    LifeCycleEntry lce;
	LifeCycleEntry_init(&lce);

	ov_string_setvalue(&lce.creatingInstance.IdSpec, pinst->v_LCECreatingInstanceIdString);
	lce.creatingInstance.IdType =  pinst->v_LCECreatingInstanceIdType;

	ov_string_setvalue(&lce.writingInstance.IdSpec,  pinst->v_LCEWritingInstanceIdString);
	lce.writingInstance.IdType =  pinst->v_LCEWritingInstanceIdType;

	ov_string_setvalue(&lce.eventClass,  pinst->v_LCEEventClass);

	ov_string_setvalue(&lce.subject,  pinst->v_LCESubject);

	ov_variable_setanyvalue(&lce.data.Value, &pinst->v_LCEValue);

	ov_time_gettime(&lce.data.TimeStamp);

	IdentificationType aasId;
	IdentificationType_init(&aasId);
	ov_string_setvalue(&aasId.IdSpec, pinst->v_AASIdString);
	aasId.IdType = pinst->v_AASIdType;

	pgpioIn = Ov_StaticPtrCast(raspi_gpioIn, Ov_SearchChild(ov_containment, Ov_StaticPtrCast(ov_domain, pinst), "RASPIIN"));
	if(!pgpioIn){
		ovResult = Ov_CreateObject(raspi_gpioIn, pgpioIn, Ov_StaticPtrCast(ov_domain, pinst), "RASPIIN");
		if(Ov_Fail(ovResult)){
			ov_logfile_error("Fatal: could not create RASPIIN object - reason: %s", ov_result_getresulttext(ovResult));
			return ;
		}
		purtask = (OV_INSTPTR_fb_task)ov_path_getobjectpointer("/Tasks/UrTask", 2);
		ovResult = Ov_Link(fb_tasklist, purtask, pgpioIn);
		if (Ov_Fail(ovResult)) {
			ov_logfile_error("Fatal: could not link object - reason: %s", ov_result_getresulttext(ovResult));
			return ;
		}
		pgpioIn->v_pin = 0;
		pgpioIn->v_pullUpDown = 2;
		pgpioIn->v_iexreq = true;
		pgpioIn->v_actimode = 1;
	}

	switch(pinst->v_State){
	case 0:
		if(pgpioIn->v_output == TRUE)
			pinst->v_State = 1;
		break;
	case 1:
		pinst->v_Status = openaas_modelmanager_createLCE(aasId, lce);
		pinst->v_State = 2;
		break;
	case 2:
		if(pgpioIn->v_output == FALSE)
			pinst->v_State = 0;
		break;
	}

    return;
}

