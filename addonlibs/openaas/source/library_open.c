
/******************************************************************************
*
*   FILE
*   ----
*   library_open.c
*
*   History
*   -------
*   2014-10-13   File created
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
#ifdef ov_library_open_openaas
#undef ov_library_open_openaas
#endif

#include "libov/ov_macros.h"
#include "libov/ov_result.h"
#include "libov/ov_logfile.h"
#include "libov/ov_memstack.h"
#include "libov/ov_result.h"


OV_INSTPTR_openaas_nodeStoreFunctions pNodeStoreFunctions = NULL;

 OV_RESULT ov_library_setglobalvars_openaas_new(void) {
	OV_RESULT result = OV_ERR_OK;
	OV_INSTPTR_ov_domain pcommunication = NULL;
	OV_INSTPTR_ov_domain pDomOpenAAS = NULL;
	OV_INSTPTR_ov_library pLibOPCUA = NULL;
	OV_INSTPTR_openaas_modelmanager pmodelmanager = NULL;
	/*
	 *    set the global variables of the original version
	 *    and if successful, load other libraries
	 *    and create some objects
	 */
	 result = ov_library_setglobalvars_openaas();
	 if (Ov_Fail(result)){
		 return result;
	 }
	/*
	 * Your code goes here.
	 */

	 Ov_ForEachChildEx(ov_instantiation, pclass_ov_library, pLibOPCUA, ov_library){
		if(ov_string_compare(pLibOPCUA->v_identifier, "opcua") == OV_STRCMP_EQUAL){
			break;
		}
	}
	if(!pLibOPCUA)
	{
		result = Ov_CreateObject(ov_library, pLibOPCUA, &(pdb->acplt), "opcua");
		if(Ov_Fail(result)){
			ov_memstack_lock();
			ov_logfile_error("openaas: Fatal: Couldn't load dependency \"pLibOPCUA\" Reason: %s", ov_result_getresulttext(result));
			ov_memstack_unlock();
			return result;
		}
	}

	 /*	initialize the ServiceImplementations Structure of the open62541 Stack with our service functions	*/
	//get the communication domain for putting in the ksxdr-objects
	//OV_INSTPTR_openaas_nodeStoreFunctions pNodeStoreFunctions;
	pcommunication = Ov_StaticPtrCast(ov_domain, Ov_SearchChild(ov_containment, &(pdb->root), "communication"));
	if(!pcommunication) {
		result = Ov_CreateObject(ov_domain, pcommunication, &(pdb->root), "communication");
		if(Ov_Fail(result)) {
			ov_logfile_error("Fatal: Could not create Object 'communication'");
			return result;
		}
	}
	else if(!Ov_CanCastTo(ov_domain, (OV_INSTPTR_ov_object) pcommunication)){
		ov_logfile_error("Fatal: communication object found but not domain (or derived)");
		return OV_ERR_GENERIC;
	}

	pDomOpenAAS = Ov_StaticPtrCast(ov_domain, Ov_SearchChild(ov_containment, pcommunication, "OpenAAS"));
	if(!pDomOpenAAS) {
		result = Ov_CreateObject(ov_domain, pDomOpenAAS, pcommunication, "OpenAAS");
		if(Ov_Fail(result)){
			ov_logfile_error("Fatal: could not create OpenAAS domain");
			return result;
		}
	}
	else if(!Ov_CanCastTo(ov_domain, (OV_INSTPTR_ov_object) pDomOpenAAS)){
		ov_logfile_error("Fatal: OpenAAS object found but not domain (or derived)");
		return OV_ERR_GENERIC;
	}

	// create nodeStoreFunctions
	pNodeStoreFunctions = Ov_StaticPtrCast(openaas_nodeStoreFunctions, Ov_GetFirstChild(ov_instantiation, pclass_openaas_nodeStoreFunctions));
	if(!pNodeStoreFunctions){
		result = Ov_CreateObject(openaas_nodeStoreFunctions, pNodeStoreFunctions, pDomOpenAAS, "NodeStoreFunctionsOpenAAS");
		if(Ov_Fail(result))	{
			ov_logfile_error("Fatal: could not create nodestoreFunctions object - reason: %s", ov_result_getresulttext(result));
			return result;
		}
	}

	// Create Folder for AAS
	OV_INSTPTR_ov_domain pTechUnits = NULL;
	OV_INSTPTR_ov_domain pAASFolder = NULL;
	pTechUnits = Ov_StaticPtrCast(ov_domain, Ov_SearchChild(ov_containment, &(pdb->root), "TechUnits"));
	if(!pTechUnits) {
		result = Ov_CreateObject(ov_domain, pTechUnits, &(pdb->root), "TechUnits");
		if(Ov_Fail(result)) {
			ov_logfile_error("Fatal: Could not create Object 'pTechUnits'");
			return result;
		}
	}
	else if(!Ov_CanCastTo(ov_domain, (OV_INSTPTR_ov_object) pTechUnits))	{
		ov_logfile_error("Fatal: pTechUnits object found but not domain (or derived)");
		return OV_ERR_GENERIC;
	}
	pAASFolder = Ov_StaticPtrCast(ov_domain, Ov_SearchChild(ov_containment, pTechUnits, "AASFolder"));
	if(!pAASFolder) {
		result = Ov_CreateObject(ov_domain, pAASFolder, pTechUnits, "AASFolder");
		if(Ov_Fail(result))	{
			ov_logfile_error("Fatal: could not create AASFolder domain");
			return result;
		}
	}
	else if(!Ov_CanCastTo(ov_domain, (OV_INSTPTR_ov_object) pAASFolder)){
		ov_logfile_error("Fatal: AASFolder object found but not domain (or derived)");
		return OV_ERR_GENERIC;
	}


	// create modelmanager
	pmodelmanager = Ov_StaticPtrCast(openaas_modelmanager, Ov_GetFirstChild(ov_instantiation, pclass_openaas_modelmanager));
	if(!pmodelmanager){
		result = Ov_CreateObject(openaas_modelmanager, pmodelmanager, pAASFolder, "ModelmanagerOpenAAS");
		if(Ov_Fail(result)){
			ov_logfile_error("Fatal: could not create modelmanager object - reason: %s", ov_result_getresulttext(result));
			return result;
		}
		pmodelmanager->v_Container.AASConvertListSize = 0;
		pmodelmanager->v_Container.AASConvertList = NULL;
	}

	return result;
	}

 OV_DLLFNCEXPORT OV_LIBRARY_DEF *ov_library_open_openaas(void) {
 	/* local variables */
 	static OV_LIBRARY_DEF *OV_LIBRARY_DEF_openaas_new;
 	/*
 	*       replace the 'setglobalvars' function created by the code generator
 	*       with a new one.
 	*/
 	OV_LIBRARY_DEF_openaas_new = ov_library_open_openaas_old();
 	OV_LIBRARY_DEF_openaas_new->setglobalvarsfnc = ov_library_setglobalvars_openaas_new;
 	return OV_LIBRARY_DEF_openaas_new;
  }


