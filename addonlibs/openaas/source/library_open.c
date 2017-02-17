
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
#include "libov/ov_time.h"


OV_INSTPTR_openaas_nodeStoreFunctions pNodeStoreFunctions = NULL;

 OV_RESULT ov_library_setglobalvars_openaas_new(void) {
	OV_RESULT result = OV_ERR_OK;
	OV_INSTPTR_ov_domain pcommunication = NULL;
	OV_INSTPTR_ov_domain pDomOpenAAS = NULL;
	OV_INSTPTR_ov_library pLibOPCUA = NULL;
	OV_INSTPTR_openaas_modelmanager pmodelmanager = NULL;
	OV_INSTPTR_openaas_aas pComCo = NULL;
	OV_INSTPTR_openaas_ExternalPostOffice pExternalPost = NULL;
	OV_INSTPTR_ksapi_setVar psendAASMessage = NULL;
	OV_INSTPTR_ksapi_getVar pGetComCoAddressFromAASDiscoveryServer = NULL;
	OV_INSTPTR_fb_task	purtask = NULL;
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
	 if(!pLibOPCUA){
		result = Ov_CreateObject(ov_library, pLibOPCUA, &(pdb->acplt), "opcua");
		if(Ov_Fail(result)){
			ov_memstack_lock();
			ov_logfile_error("openaas: Fatal: Couldn't load dependency Library opcua Reason: %s", ov_result_getresulttext(result));
			ov_memstack_unlock();
			return result;
		}
	 }

	 Ov_ForEachChildEx(ov_instantiation, pclass_ov_library, pLibOPCUA, ov_library){
		if(ov_string_compare(pLibOPCUA->v_identifier, "ksapi") == OV_STRCMP_EQUAL){
			break;
		}
	 }
	 if(!pLibOPCUA){
		result = Ov_CreateObject(ov_library, pLibOPCUA, &(pdb->acplt), "ksapi");
		if(Ov_Fail(result)){
			ov_memstack_lock();
			ov_logfile_error("openaas: Fatal: Couldn't load dependency Library ksapi Reason: %s", ov_result_getresulttext(result));
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

	// create sendAASMessage
	Ov_ForEachChildEx(ov_instantiation, pclass_ksapi_setVar, psendAASMessage, ksapi_setVar){
		if(ov_string_compare(psendAASMessage->v_identifier, "SendAASMessage") == OV_STRCMP_EQUAL){
			break;
		}
	}
	if(!psendAASMessage){
		result = Ov_CreateObject(ksapi_setVar, psendAASMessage, pDomOpenAAS, "SendAASMessage");
		if(Ov_Fail(result)){
			ov_logfile_error("Fatal: could not create SendAASMessage object - reason: %s", ov_result_getresulttext(result));
			return result;
		}
	}

	// create getComCoAddressFromAASDiscoveryServer
	Ov_ForEachChildEx(ov_instantiation, pclass_ksapi_getVar, pGetComCoAddressFromAASDiscoveryServer, ksapi_getVar){
		if(ov_string_compare(pGetComCoAddressFromAASDiscoveryServer->v_identifier, "GetComCoAddressFromAASDiscoveryServer") == OV_STRCMP_EQUAL){
			break;
		}
	}
	if(!pGetComCoAddressFromAASDiscoveryServer){
		result = Ov_CreateObject(ksapi_getVar, pGetComCoAddressFromAASDiscoveryServer, pDomOpenAAS, "GetComCoAddressFromAASDiscoveryServer");
		if(Ov_Fail(result)){
			ov_logfile_error("Fatal: could not create GetComCoAddressFromAASDiscoveryServer object - reason: %s", ov_result_getresulttext(result));
			return result;
		}
	}

	// Create Folder for NodeStoreFunctionsOpenAAS & ModelManagerOpenAAS
	OV_INSTPTR_ov_domain pdata = NULL;
	OV_INSTPTR_ov_domain popenAAS = NULL;
	pdata = Ov_StaticPtrCast(ov_domain, Ov_SearchChild(ov_containment, &(pdb->root), "data"));
	if(!pdata) {
		result = Ov_CreateObject(ov_domain, pdata, &(pdb->root), "data");
		if(Ov_Fail(result)) {
			ov_logfile_error("Fatal: Could not create Object 'data'");
			return result;
		}
	}
	else if(!Ov_CanCastTo(ov_domain, (OV_INSTPTR_ov_object) pdata))	{
		ov_logfile_error("Fatal: pdata object found but not domain (or derived)");
		return OV_ERR_GENERIC;
	}
	popenAAS = Ov_StaticPtrCast(ov_domain, Ov_SearchChild(ov_containment, pdata, "openAAS"));
	if(!popenAAS) {
		result = Ov_CreateObject(ov_domain, popenAAS, pdata, "openAAS");
		if(Ov_Fail(result))	{
			ov_logfile_error("Fatal: could not create openAAS domain");
			return result;
		}
	}
	else if(!Ov_CanCastTo(ov_domain, (OV_INSTPTR_ov_object) popenAAS)){
		ov_logfile_error("Fatal: openAAS object found but not domain (or derived)");
		return OV_ERR_GENERIC;
	}

	// Create Folder for AAS
	OV_INSTPTR_ov_domain pTechUnits = NULL;
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

	OV_INSTPTR_ov_domain popenAASFolder = NULL;
	popenAASFolder = Ov_StaticPtrCast(ov_domain, Ov_SearchChild(ov_containment, pTechUnits, "openAAS"));
	if(!popenAASFolder) {
		result = Ov_CreateObject(ov_domain, popenAASFolder, pTechUnits, "openAAS");
		if(Ov_Fail(result))	{
			ov_logfile_error("Fatal: could not create openAAS domain");
			return result;
		}
	}
	else if(!Ov_CanCastTo(ov_domain, (OV_INSTPTR_ov_object) popenAASFolder)){
		ov_logfile_error("Fatal: openAAS object found but not domain (or derived)");
		return OV_ERR_GENERIC;
	}

	OV_INSTPTR_ov_domain pAASFolder = NULL;
	pAASFolder = Ov_StaticPtrCast(ov_domain, Ov_SearchChild(ov_containment, popenAASFolder, "AASFolder"));
	if(!pAASFolder) {
		result = Ov_CreateObject(ov_domain, pAASFolder, popenAASFolder, "AASFolder");
		if(Ov_Fail(result))	{
			ov_logfile_error("Fatal: could not create AASFolder domain");
			return result;
		}
	}
	else if(!Ov_CanCastTo(ov_domain, (OV_INSTPTR_ov_object) pAASFolder)){
		ov_logfile_error("Fatal: AASFolder object found but not domain (or derived)");
		return OV_ERR_GENERIC;
	}

	// create nodeStoreFunctions
	pNodeStoreFunctions = Ov_StaticPtrCast(openaas_nodeStoreFunctions, Ov_GetFirstChild(ov_instantiation, pclass_openaas_nodeStoreFunctions));
	if(!pNodeStoreFunctions){
		result = Ov_CreateObject(openaas_nodeStoreFunctions, pNodeStoreFunctions, popenAAS, "NodeStoreFunctionsOpenAAS");
		if(Ov_Fail(result))	{
			ov_logfile_error("Fatal: could not create nodestoreFunctions object - reason: %s", ov_result_getresulttext(result));
			return result;
		}
	}

	// create modelmanager
	pmodelmanager = Ov_StaticPtrCast(openaas_modelmanager, Ov_GetFirstChild(ov_instantiation, pclass_openaas_modelmanager));
	if(!pmodelmanager){
		result = Ov_CreateObject(openaas_modelmanager, pmodelmanager, popenAASFolder, "ModelmanagerOpenAAS");
		if(Ov_Fail(result)){
			ov_logfile_error("Fatal: could not create modelmanager object - reason: %s", ov_result_getresulttext(result));
			return result;
		}
	}

	// create ComCo
	Ov_ForEachChildEx(ov_instantiation, pclass_openaas_aas, pComCo, openaas_aas){
		if(ov_string_compare(pComCo->v_identifier, "ComCo") == OV_STRCMP_EQUAL){
			break;
		}
	}
	if(!pComCo){
		IdentificationType aasId;
		aasId.IdSpec = NULL;
		ov_string_setvalue(&aasId.IdSpec, "http://acplt.org/ComCo");
		aasId.IdType = 0;

		IdentificationType assetId;
		assetId.IdSpec = NULL;
		ov_string_setvalue(&assetId.IdSpec, "http://acplt.org/Manager");
		assetId.IdType = 0;

		if (AASSTATUSCODE_FAIL(openaas_modelmanager_createAAS(aasId, "ComCo", assetId))){
			ov_logfile_error("Fatal: Could not create Object 'ComCo'");
			return OV_ERR_GENERIC;
		}

	}

	// create ExternalPostOffice
	Ov_ForEachChildEx(ov_instantiation, pclass_openaas_ExternalPostOffice, pExternalPost, openaas_ExternalPostOffice){
		if(ov_string_compare(pExternalPost->v_identifier, "ExternalPostOffice") == OV_STRCMP_EQUAL){
			break;
		}
	}
	if(!pExternalPost){
		result = Ov_CreateObject(openaas_ExternalPostOffice, pExternalPost, pAASFolder, "ExternalPostOffice");
		if(Ov_Fail(result)){
			ov_logfile_error("Fatal: could not create externalPostOffice object - reason: %s", ov_result_getresulttext(result));
			return result;
		}
		purtask = (OV_INSTPTR_fb_task)ov_path_getobjectpointer("/Tasks/UrTask", 2);
		result = Ov_Link(fb_tasklist, purtask, pExternalPost);
		if (Ov_Fail(result)) {
			ov_logfile_error("Fatal: could not link externalPostOffice object - reason: %s", ov_result_getresulttext(result));
			return result;
		}
	}

	// Performance
	OV_INSTPTR_fb_task ptask = NULL;
	Ov_ForEachChildEx(ov_instantiation, pclass_fb_task, ptask, fb_task){
		if(ov_string_compare(ptask->v_identifier, "UrTask") == OV_STRCMP_EQUAL){
			break;
		}
	}
	if(ptask){
		ptask->v_cyctime.secs = 0;
		ptask->v_cyctime.usecs = 1;
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


