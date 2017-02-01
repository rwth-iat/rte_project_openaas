/******************************************************************************
 *
 *   FILE
 *   ----
 *   nodeStoreFunctions.c
 *
 *   History
 *   -------
 *   2014-10-21   File created
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
#include "ksbase.h"
#include "opcua.h"
#include "opcua_helpers.h"
#include "NoneTicketAuthenticator.h"
#include "libov/ov_path.h"
#include "libov/ov_memstack.h"
#include "ks_logfile.h"
#include "nodeset.h"
#include "ua_openaas_generated.h"
#include "ua_openaas_generated_handling.h"

extern OV_INSTPTR_openaas_nodeStoreFunctions pNodeStoreFunctions;




OV_DLLFNCEXPORT UA_StatusCode openaas_nodeStoreFunctions_ovLifeCycleEntryNodeToOPCUA(
		void *handle, const UA_NodeId *nodeId, UA_Node** opcuaNode) {
	UA_Node 				*newNode = NULL;
	UA_StatusCode 			result = UA_STATUSCODE_GOOD;
	OV_PATH 				path;
	OV_INSTPTR_ov_object	pobj = NULL;
	OV_TICKET 				*pTicket = NULL;
	OV_VTBLPTR_ov_object	pVtblObj = NULL;
	OV_ACCESS				access;
	UA_NodeClass 			*nodeClass = NULL;

	ov_memstack_lock();
	result = opcua_nodeStoreFunctions_resolveNodeIdToPath(*nodeId, &path);
	if(result != UA_STATUSCODE_GOOD){
		ov_memstack_unlock();
		return result;
	}
	result = opcua_nodeStoreFunctions_getVtblPointerAndCheckAccess(&(path.elements[path.size-1]), pTicket, &pobj, &pVtblObj, &access);
	if(result != UA_STATUSCODE_GOOD){
		ov_memstack_unlock();
		return result;
	}

	nodeClass = UA_NodeClass_new();
	if(!nodeClass){
		result = ov_resultToUaStatusCode(OV_ERR_HEAPOUTOFMEMORY);
		ov_memstack_unlock();
		return result;
	}

	*nodeClass = UA_NODECLASS_VARIABLE;
	newNode = (UA_Node*)ov_database_malloc(sizeof(UA_VariableNode));


	// Basic Attribute
	// BrowseName
	UA_QualifiedName qName;
	qName.name = UA_String_fromChars(pobj->v_identifier);
	if(Ov_GetClassPtr(pobj) != pclass_opcua_arguments){
		qName.namespaceIndex = pNodeStoreFunctions->v_NameSpaceIndexNodeStoreInterface;
	} else {
		qName.namespaceIndex = 0;
	}
	newNode->browseName = qName;

	// Description
	OV_STRING tempString = pVtblObj->m_getcomment(pobj, &(path.elements[path.size-1]));
	UA_LocalizedText lText;
	lText.locale = UA_String_fromChars("en");
	if(tempString){
		lText.text = UA_String_fromChars(tempString);
	} else {
		lText.text = UA_String_fromChars("");
	}
	newNode->description = lText;

	// DisplayName
	lText.locale = UA_String_fromChars("en");
	lText.text = UA_String_fromChars(pobj->v_identifier);
	newNode->displayName = lText;

	// NodeId
	newNode->nodeId = *nodeId;

	// NodeClass
	newNode->nodeClass 	= *nodeClass;

	// WriteMask
	UA_UInt32 writeMask = 0;
	if(path.elements[path.size-1].elemtype != OV_ET_VARIABLE){
		if(access & OV_AC_WRITE){
			writeMask |= (1<<2);	//	BrowseName
			writeMask |= (1<<6);	//	DisplayName
		}
		if(access & OV_AC_RENAMEABLE){
			writeMask |= (1<<14);	//	NodeId
		}
	}
	newNode->writeMask 	= writeMask;

	// Variable specific attributes
	// arrayDemensions
	((UA_VariableNode*)newNode)->arrayDimensionsSize = 0;
	((UA_VariableNode*)newNode)->arrayDimensions = UA_Array_new(((UA_VariableNode*)newNode)->arrayDimensionsSize, &UA_TYPES[UA_TYPES_INT32]);	/*	scalar or one dimension	*/

	// valuerank
	((UA_VariableNode*)newNode)->valueRank = 1;	/*	one dimension	*/

	// value
	OV_ELEMENT tmpPart;
	tmpPart.elemtype = OV_ET_NONE;
	OV_ELEMENT tmpParrent;
	tmpParrent.pobj = pobj;
	tmpParrent.elemtype = OV_ET_OBJECT;
	UA_LifeCycleEntry tmpLifeCycleEntry;
	do {
		ov_element_getnextpart(&tmpParrent, &tmpPart, OV_ET_VARIABLE);
		if (tmpPart.elemtype == OV_ET_NONE)
			break;
		if (ov_string_compare(tmpPart.elemunion.pvar->v_identifier, "CreatingInstanceString") == OV_STRCMP_EQUAL)
			copyOvStringToOPCUA(*(OV_STRING*)tmpPart.pvalue, &tmpLifeCycleEntry.creatingInstance.idSpec);
		if (ov_string_compare(tmpPart.elemunion.pvar->v_identifier, "CreatingInstanceType") == OV_STRCMP_EQUAL)
			tmpLifeCycleEntry.creatingInstance.idType = *(UA_UInt32*)tmpPart.pvalue;
		if (ov_string_compare(tmpPart.elemunion.pvar->v_identifier, "WritingInstanceString") == OV_STRCMP_EQUAL)
			copyOvStringToOPCUA(*(OV_STRING*)tmpPart.pvalue, &tmpLifeCycleEntry.writingInstance.idSpec);
		if (ov_string_compare(tmpPart.elemunion.pvar->v_identifier, "WritingInstanceType") == OV_STRCMP_EQUAL)
			tmpLifeCycleEntry.writingInstance.idType = *(UA_UInt32*)tmpPart.pvalue;
		if (ov_string_compare(tmpPart.elemunion.pvar->v_identifier, "Data") == OV_STRCMP_EQUAL)
			ov_AnyToVariant((OV_ANY*)tmpPart.pvalue, &tmpLifeCycleEntry.data.value);
		if (ov_string_compare(tmpPart.elemunion.pvar->v_identifier, "TimeStamp") == OV_STRCMP_EQUAL)
			tmpLifeCycleEntry.data.sourceTimestamp = *(UA_DateTime*)tmpPart.pvalue;
		if (ov_string_compare(tmpPart.elemunion.pvar->v_identifier, "Subject") == OV_STRCMP_EQUAL)
			copyOvStringToOPCUA(*(OV_STRING*)tmpPart.pvalue, &tmpLifeCycleEntry.subject);
		if (ov_string_compare(tmpPart.elemunion.pvar->v_identifier, "EventClass") == OV_STRCMP_EQUAL)
			copyOvStringToOPCUA(*(OV_STRING*)tmpPart.pvalue, &tmpLifeCycleEntry.eventClass);
		if (ov_string_compare(tmpPart.elemunion.pvar->v_identifier, "View") == OV_STRCMP_EQUAL)
			tmpLifeCycleEntry.view = *(UA_UInt32*)tmpPart.pvalue;
	} while(true);

	((UA_Variant*)&((UA_VariableNode*)newNode)->value.data.value.value)->type = &UA_OPENAAS[UA_OPENAAS_LIFECYCLEENTRY];
	((UA_Variant*)&((UA_VariableNode*)newNode)->value.data.value.value)->data = UA_LifeCycleEntry_new();
	if (!((UA_Variant*)&((UA_VariableNode*)newNode)->value.data.value.value)->data){
		result = UA_STATUSCODE_BADOUTOFMEMORY;
		ov_memstack_unlock();
		return result;
	}
	UA_LifeCycleEntry_copy(&tmpLifeCycleEntry, ((UA_Variant*)&((UA_VariableNode*)newNode)->value.data.value.value)->data);

	// accessLevel
	UA_Byte accessLevel = 0;
	if(access & OV_AC_READ){
		accessLevel |= (1<<0);
	}
	if(access & OV_AC_WRITE){
		accessLevel |= (1<<1);
	}
	((UA_VariableNode*)newNode)->accessLevel = accessLevel;
	// minimumSamplingInterval
	((UA_VariableNode*)newNode)->minimumSamplingInterval = -1;
	// historizing
	((UA_VariableNode*)newNode)->historizing = UA_FALSE;
	// dataType
	((UA_VariableNode*)newNode)->dataType.identifierType = UA_NODEIDTYPE_NUMERIC;
	((UA_VariableNode*)newNode)->dataType.namespaceIndex = pNodeStoreFunctions->v_NameSpaceIndexInformationModel;
	((UA_VariableNode*)newNode)->dataType.identifier.numeric = UA_NS2ID_LIFECYCLEENTRY;


	// References
	OV_INSTPTR_ov_object pchild = NULL;
	size_t size_references = 0;
	Ov_ForEachChild(ov_containment, Ov_DynamicPtrCast(ov_domain,pobj), pchild) {
		size_references++;
	}

	size_references = size_references + 2;// For Parent&TypeNode
	newNode->references = UA_calloc(size_references, sizeof(UA_ReferenceNode));
	newNode->referencesSize = size_references;
	// ParentNode
	newNode->references[0].referenceTypeId = UA_NODEID_NUMERIC(0, UA_NS0ID_HASPROPERTY);
	newNode->references[0].isInverse = UA_TRUE;
	OV_UINT len = 0;
	OV_STRING *plist = NULL;
	OV_STRING tmpString = NULL;
	copyOPCUAStringToOV(nodeId->identifier.string, &tmpString);
	plist = ov_string_split(tmpString, "/", &len);
	ov_string_setvalue(&tmpString, "");
	for (OV_UINT i = 0; i < len-1; i++){
		if (i != 0)
			ov_string_append(&tmpString, "/");
		ov_string_append(&tmpString, plist[i]);
	}
	newNode->references[0].targetId = UA_EXPANDEDNODEID_STRING(pNodeStoreFunctions->v_NameSpaceIndexNodeStoreInterface, tmpString);

	// TypeNode
	newNode->references[1].referenceTypeId = UA_NODEID_NUMERIC(0, UA_NS0ID_HASTYPEDEFINITION);
	newNode->references[1].isInverse = UA_FALSE;
	newNode->references[1].targetId = UA_EXPANDEDNODEID_NUMERIC(0, UA_NS0ID_PROPERTYTYPE);

	size_t i = 1;

	Ov_ForEachChild(ov_containment, Ov_DynamicPtrCast(ov_domain,pobj), pchild) {
		i++;
	}

	*opcuaNode = newNode;
	ov_memstack_unlock();
	return UA_STATUSCODE_GOOD;
}

