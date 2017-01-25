
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


#ifndef OV_COMPILE_LIBRARY_opcua
#define OV_COMPILE_LIBRARY_opcua
#endif



#include "libov/ov_macros.h"
#include "ksbase.h"
#include "opcua.h"
#include "opcua_helpers.h"
#include "ks_logfile.h"
#include "NoneTicketAuthenticator.h"
#include "libov/ov_path.h"
#include "libov/ov_memstack.h"

extern OV_INSTPTR_opcua_uaServer opcua_pUaServer;

UA_StatusCode opcua_WalkPath(const UA_RelativePath *relativePath, UA_UInt32 levelCounter, const OV_INSTPTR_ov_object baseNode, UA_UInt32 *elementCount,
		UA_Boolean fillDescription, UA_BrowsePathTarget *browsePathTargets){
	OV_ELEMENT startElem;
	OV_ELEMENT refElem;
	OV_STRING targetIdentifier = NULL;
	UA_StatusCode uaResult;

	if(fillDescription && !browsePathTargets){
		return UA_STATUSCODE_BADINVALIDARGUMENT;
	}

	/*	check ns-index and prepare identifier	*/
	targetIdentifier = ov_memstack_alloc(relativePath->elements[levelCounter-1].targetName.name.length +1);
	if(!targetIdentifier){
		return UA_STATUSCODE_BADOUTOFMEMORY;
	}
	memcpy(targetIdentifier, relativePath->elements[levelCounter-1].targetName.name.data, relativePath->elements[levelCounter-1].targetName.name.length);
	targetIdentifier[relativePath->elements[levelCounter-1].targetName.name.length] = '\0';
	if(relativePath->elements[levelCounter-1].targetName.namespaceIndex != opcua_pUaServer->v_NameSpaceIndex){
		if(relativePath->elements[levelCounter-1].targetName.namespaceIndex != 0
				|| (ov_string_compare(targetIdentifier, "InputArguments") != OV_STRCMP_EQUAL
						&& ov_string_compare(targetIdentifier, "OutputArguments") != OV_STRCMP_EQUAL)){
			return UA_STATUSCODE_GOOD;
		}
	}

	/*	only working for basic UA-REferenceTypes and no subtypes	*/
	if(relativePath->elements[levelCounter-1].referenceTypeId.identifierType != UA_NODEIDTYPE_NUMERIC
			|| relativePath->elements[levelCounter-1].referenceTypeId.namespaceIndex != 0
			|| relativePath->elements[levelCounter-1].includeSubtypes){
		KS_logfile_info(("opua_WalkPath: tried to use non numeric ReferencType ID, non NS0 Reference Type ID or include subtypes."));
		return UA_STATUSCODE_BADNOTIMPLEMENTED;
	}
	switch(relativePath->elements[levelCounter-1].referenceTypeId.identifier.numeric){
	case UA_NODEID_Organizes:
		if(!relativePath->elements[levelCounter-1].isInverse){
			startElem.elemtype = OV_ET_OBJECT;
			startElem.pobj = baseNode;
			refElem.elemtype = OV_ET_NONE;
			refElem.pobj = NULL;
			/*	children	*/
			ov_element_getnextchild(&startElem, &refElem);
			while(refElem.elemtype != OV_ET_NONE){
				if(refElem.elemtype == OV_ET_OBJECT){
					if(ov_string_compare(refElem.pobj->v_identifier, targetIdentifier) == OV_STRCMP_EQUAL){
						/*	found a match -> if we have the last path element, count up (and fill description). If not, recurse 	*/
						if(levelCounter == relativePath->elementsSize){
							if(fillDescription){
								browsePathTargets[*elementCount].remainingPathIndex = 0;
								UA_ExpandedNodeId_init(&(browsePathTargets[*elementCount].targetId));
								browsePathTargets[*elementCount].targetId.nodeId.namespaceIndex = opcua_pUaServer->v_NameSpaceIndex;
								browsePathTargets[*elementCount].targetId.nodeId.identifierType = UA_NODEIDTYPE_NUMERIC;
								browsePathTargets[*elementCount].targetId.nodeId.identifier.numeric = refElem.pobj->v_idL;
							}
							(*elementCount)++;
						} else {
							uaResult = opcua_WalkPath(relativePath, levelCounter+1, refElem.pobj, elementCount, fillDescription, browsePathTargets);
							if(uaResult != UA_STATUSCODE_GOOD){
								return uaResult;
							}
						}
					}
				}
				ov_element_getnextchild(&startElem, &refElem);
			}
			/*	parts	*/
			ov_element_getnextpart(&startElem, &refElem, OV_ET_OBJECT | OV_ET_VARIABLE);
			while(refElem.elemtype != OV_ET_NONE){
				if(refElem.elemtype == OV_ET_OBJECT){
					if(ov_string_compare(refElem.pobj->v_identifier, targetIdentifier) == OV_STRCMP_EQUAL){
						/*	found a match -> if we have the last path element, count up (and fill description). If not, recurse 	*/
						if(levelCounter == relativePath->elementsSize){
							if(fillDescription){
								browsePathTargets[*elementCount].remainingPathIndex = 0;
								UA_ExpandedNodeId_init(&(browsePathTargets[*elementCount].targetId));
								browsePathTargets[*elementCount].targetId.nodeId.namespaceIndex = opcua_pUaServer->v_NameSpaceIndex;
								browsePathTargets[*elementCount].targetId.nodeId.identifierType = UA_NODEIDTYPE_NUMERIC;
								browsePathTargets[*elementCount].targetId.nodeId.identifier.numeric = refElem.pobj->v_idL;
							}
							(*elementCount)++;
						} else {
							uaResult = opcua_WalkPath(relativePath, levelCounter+1, refElem.pobj, elementCount, fillDescription, browsePathTargets);
							if(uaResult != UA_STATUSCODE_GOOD){
								return uaResult;
							}
						}
					}
				} else {
					if(ov_string_compare(refElem.elemunion.pvar->v_identifier, targetIdentifier) == OV_STRCMP_EQUAL){
						if(levelCounter == relativePath->elementsSize){
							if(fillDescription){//TODO Var-NodeIDs!!!
								browsePathTargets[*elementCount].remainingPathIndex = 0;
								UA_ExpandedNodeId_init(&(browsePathTargets[*elementCount].targetId));
								browsePathTargets[*elementCount].targetId.nodeId.namespaceIndex = opcua_pUaServer->v_NameSpaceIndex;
								browsePathTargets[*elementCount].targetId.nodeId.identifierType = UA_NODEIDTYPE_STRING;
								browsePathTargets[*elementCount].targetId.nodeId.identifier.string = UA_String_fromChars(refElem.elemunion.pvar->v_identifier);
							}
							(*elementCount)++;
						}
					}
				}
				ov_element_getnextchild(&startElem, &refElem);
			}
		} else {
			refElem.pobj = (OV_INSTPTR_ov_object)Ov_GetParent(ov_containment, startElem.pobj);
			if(!refElem.pobj){
				refElem.pobj = startElem.pobj->v_pouterobject;
			}
			if(!refElem.pobj){
				return UA_STATUSCODE_BADINTERNALERROR;
			}
			if(ov_string_compare(refElem.pobj->v_identifier, targetIdentifier) == OV_STRCMP_EQUAL){
				/*	found a match -> if we have the last path element, count up (and fill description). If not, recurse 	*/
				if(levelCounter == relativePath->elementsSize){
					if(fillDescription){
						browsePathTargets[*elementCount].remainingPathIndex = 0;
						UA_ExpandedNodeId_init(&(browsePathTargets[*elementCount].targetId));
						browsePathTargets[*elementCount].targetId.nodeId.namespaceIndex = opcua_pUaServer->v_NameSpaceIndex;
						browsePathTargets[*elementCount].targetId.nodeId.identifierType = UA_NODEIDTYPE_NUMERIC;
						browsePathTargets[*elementCount].targetId.nodeId.identifier.numeric = refElem.pobj->v_idL;
					}
					(*elementCount)++;
				} else {
					uaResult = opcua_WalkPath(relativePath, levelCounter+1, refElem.pobj, elementCount, fillDescription, browsePathTargets);
					if(uaResult != UA_STATUSCODE_GOOD){
						return uaResult;
					}
				}
			}
		}
		break;
	case UA_NODEID_HasTypeDefinition:
		if(!relativePath->elements[levelCounter-1].isInverse){
			startElem.elemtype = OV_ET_OBJECT;
			startElem.pobj = baseNode;
			refElem.elemtype = OV_ET_NONE;
			refElem.pobj = NULL;
			/*	get parent on instantiation for objects	*/
			refElem.pobj = (OV_INSTPTR_ov_object)Ov_GetParent(ov_instantiation, startElem.pobj);
			if(!refElem.pobj){
				return UA_STATUSCODE_BADINTERNALERROR;
			}
			if(ov_string_compare(refElem.pobj->v_identifier, targetIdentifier) == OV_STRCMP_EQUAL){
				/*	found a match -> if we have the last path element, count up (and fill description). If not, recurse 	*/
				if(levelCounter == relativePath->elementsSize){
					if(fillDescription){
						browsePathTargets[*elementCount].remainingPathIndex = 0;
						UA_ExpandedNodeId_init(&(browsePathTargets[*elementCount].targetId));
						browsePathTargets[*elementCount].targetId.nodeId.namespaceIndex = opcua_pUaServer->v_NameSpaceIndex;
						browsePathTargets[*elementCount].targetId.nodeId.identifierType = UA_NODEIDTYPE_NUMERIC;
						browsePathTargets[*elementCount].targetId.nodeId.identifier.numeric = refElem.pobj->v_idL;
					}
					(*elementCount)++;
				} else {
					uaResult = opcua_WalkPath(relativePath, levelCounter+1, refElem.pobj, elementCount, fillDescription, browsePathTargets);
					if(uaResult != UA_STATUSCODE_GOOD){
						return uaResult;
					}
				}
			}
		} else {
			if(Ov_GetClassPtr(startElem.pobj) == pclass_ov_class){
				Ov_ForEachChild(ov_instantiation, (Ov_StaticPtrCast(ov_class, startElem.pobj)), refElem.pobj){
					if(ov_string_compare(refElem.pobj->v_identifier, targetIdentifier) == OV_STRCMP_EQUAL){
						/*	found a match -> if we have the last path element, count up (and fill description). If not, recurse 	*/
						if(levelCounter == relativePath->elementsSize){
							if(fillDescription){
								browsePathTargets[*elementCount].remainingPathIndex = 0;
								UA_ExpandedNodeId_init(&(browsePathTargets[*elementCount].targetId));
								browsePathTargets[*elementCount].targetId.nodeId.namespaceIndex = opcua_pUaServer->v_NameSpaceIndex;
								browsePathTargets[*elementCount].targetId.nodeId.identifierType = UA_NODEIDTYPE_NUMERIC;
								browsePathTargets[*elementCount].targetId.nodeId.identifier.numeric = refElem.pobj->v_idL;
							}
							(*elementCount)++;
						} else {
							uaResult = opcua_WalkPath(relativePath, levelCounter+1, refElem.pobj, elementCount, fillDescription, browsePathTargets);
							if(uaResult != UA_STATUSCODE_GOOD){
								return uaResult;
							}
						}
					}
				}
			}
		}
		break;
	case UA_NODEID_HasSubtype:
		if(!relativePath->elements[levelCounter-1].isInverse){
			startElem.elemtype = OV_ET_OBJECT;
			startElem.pobj = baseNode;
			refElem.elemtype = OV_ET_NONE;
			refElem.pobj = NULL;
			/*	get child on inheritance for classes	*/
			if(Ov_GetClassPtr(startElem.pobj) == pclass_ov_class){
				OV_INSTPTR_ov_class pClass = Ov_StaticPtrCast(ov_class, refElem.pobj);
				Ov_ForEachChild(ov_inheritance, (Ov_StaticPtrCast(ov_class, startElem.pobj)), pClass){
					if(ov_string_compare(refElem.pobj->v_identifier, targetIdentifier) == OV_STRCMP_EQUAL){
						/*	found a match -> if we have the last path element, count up (and fill description). If not, recurse 	*/
						if(levelCounter == relativePath->elementsSize){
							if(fillDescription){
								browsePathTargets[*elementCount].remainingPathIndex = 0;
								UA_ExpandedNodeId_init(&(browsePathTargets[*elementCount].targetId));
								browsePathTargets[*elementCount].targetId.nodeId.namespaceIndex = opcua_pUaServer->v_NameSpaceIndex;
								browsePathTargets[*elementCount].targetId.nodeId.identifierType = UA_NODEIDTYPE_NUMERIC;
								browsePathTargets[*elementCount].targetId.nodeId.identifier.numeric = refElem.pobj->v_idL;
							}
							(*elementCount)++;
						} else {
							uaResult = opcua_WalkPath(relativePath, levelCounter+1, refElem.pobj, elementCount, fillDescription, browsePathTargets);
							if(uaResult != UA_STATUSCODE_GOOD){
								return uaResult;
							}
						}
					}
				}
			}

		} else {
			refElem.pobj = (OV_INSTPTR_ov_object)Ov_GetParent(ov_inheritance, (Ov_StaticPtrCast(ov_class, startElem.pobj)));
			if(refElem.pobj && ov_string_compare(refElem.pobj->v_identifier, targetIdentifier) == OV_STRCMP_EQUAL){
				/*	found a match -> if we have the last path element, count up (and fill description). If not, recurse 	*/
				if(levelCounter == relativePath->elementsSize){
					if(fillDescription){
						browsePathTargets[*elementCount].remainingPathIndex = 0;
						UA_ExpandedNodeId_init(&(browsePathTargets[*elementCount].targetId));
						browsePathTargets[*elementCount].targetId.nodeId.namespaceIndex = opcua_pUaServer->v_NameSpaceIndex;
						browsePathTargets[*elementCount].targetId.nodeId.identifierType = UA_NODEIDTYPE_NUMERIC;
						browsePathTargets[*elementCount].targetId.nodeId.identifier.numeric = refElem.pobj->v_idL;
					}
					(*elementCount)++;
				} else {
					uaResult = opcua_WalkPath(relativePath, levelCounter+1, refElem.pobj, elementCount, fillDescription, browsePathTargets);
					if(uaResult != UA_STATUSCODE_GOOD){
						return uaResult;
					}
				}
			}
		}
		break;
	case UA_NODEID_HasProperty:
	case UA_NODEID_HasComponent:
		if(!relativePath->elements[levelCounter-1].isInverse){
			startElem.elemtype = OV_ET_OBJECT;
			startElem.pobj = baseNode;
			refElem.elemtype = OV_ET_NONE;
			refElem.pobj = NULL;
			/*	check if it is a methodNode	*/
			OV_INSTPTR_opcua_methodNode pMethod = Ov_DynamicPtrCast(opcua_methodNode, startElem.pobj);
			if(pMethod){
				/*	add the hasproperty references for arguments	*/
				refElem.elemtype = OV_ET_NONE;
				ov_element_getnextpart(&startElem, &refElem, OV_ET_OBJECT);
				while(refElem.elemtype != OV_ET_NONE){
					/*	check if we are handling the InputArguments or OutputArguments part, if so add reference hasProperty	*/
					if(ov_string_compare(refElem.pobj->v_identifier, targetIdentifier) == OV_STRCMP_EQUAL){
						if(levelCounter == relativePath->elementsSize){
							if(fillDescription){
								browsePathTargets[*elementCount].remainingPathIndex = 0;
								UA_ExpandedNodeId_init(&(browsePathTargets[*elementCount].targetId));
								browsePathTargets[*elementCount].targetId.nodeId.namespaceIndex = opcua_pUaServer->v_NameSpaceIndex;
								browsePathTargets[*elementCount].targetId.nodeId.identifierType = UA_NODEIDTYPE_NUMERIC;
								browsePathTargets[*elementCount].targetId.nodeId.identifier.numeric = refElem.pobj->v_idL;
							}
							(*elementCount)++;
						}
					}
					ov_element_getnextpart(&startElem, &refElem, OV_ET_OBJECT);
				}
			}
			if(Ov_GetClassPtr(startElem.pobj) != pclass_opcua_arguments) {
				refElem.elemtype = OV_ET_NONE;
				ov_element_getnextpart(&startElem, &refElem, OV_ET_VARIABLE | OV_ET_MEMBER);
				while(refElem.elemtype != OV_ET_NONE){
					if(refElem.pobj && ov_string_compare(refElem.pobj->v_identifier, targetIdentifier) == OV_STRCMP_EQUAL){
						if(levelCounter == relativePath->elementsSize){
							if(fillDescription){//TODO Var-NodeIDs!!!
								browsePathTargets[*elementCount].remainingPathIndex = 0;
								UA_ExpandedNodeId_init(&(browsePathTargets[*elementCount].targetId));
								browsePathTargets[*elementCount].targetId.nodeId.namespaceIndex = opcua_pUaServer->v_NameSpaceIndex;
								browsePathTargets[*elementCount].targetId.nodeId.identifierType = UA_NODEIDTYPE_NUMERIC;
								browsePathTargets[*elementCount].targetId.nodeId.identifier.numeric = refElem.pobj->v_idL;
							}
							(*elementCount)++;
						}
					}
					ov_element_getnextpart(&startElem, &refElem, OV_ET_VARIABLE | OV_ET_MEMBER);
				}
			}
			if(relativePath->elements[levelCounter-1].referenceTypeId.identifier.numeric == UA_NODEID_HasComponent){
				refElem.elemtype = OV_ET_NONE;
				ov_element_getnextchild(&startElem, &refElem);
				while(refElem.elemtype != OV_ET_NONE){
					if(Ov_CanCastTo(opcua_methodNode, refElem.pobj)){
						if(refElem.pobj && ov_string_compare(refElem.pobj->v_identifier, targetIdentifier) == OV_STRCMP_EQUAL){
							if(levelCounter == relativePath->elementsSize){
								if(fillDescription){
									browsePathTargets[*elementCount].remainingPathIndex = 0;
									UA_ExpandedNodeId_init(&(browsePathTargets[*elementCount].targetId));
									browsePathTargets[*elementCount].targetId.nodeId.namespaceIndex = opcua_pUaServer->v_NameSpaceIndex;
									browsePathTargets[*elementCount].targetId.nodeId.identifierType = UA_NODEIDTYPE_NUMERIC;
									browsePathTargets[*elementCount].targetId.nodeId.identifier.numeric = refElem.pobj->v_idL;
								}
								(*elementCount)++;
							} else {
								uaResult = opcua_WalkPath(relativePath, levelCounter+1, refElem.pobj, elementCount, fillDescription, browsePathTargets);
								if(uaResult != UA_STATUSCODE_GOOD){
									return uaResult;
								}
							}
						}
					}
					ov_element_getnextchild(&startElem, &refElem);
				}
			}
		} else {
			if(startElem.pobj->v_pouterobject && Ov_GetClassPtr(startElem.pobj) == pclass_opcua_arguments){
				refElem.pobj = startElem.pobj->v_pouterobject;
				if(refElem.pobj && ov_string_compare(refElem.pobj->v_identifier, targetIdentifier) == OV_STRCMP_EQUAL){
					if(levelCounter == relativePath->elementsSize){
						if(fillDescription){
							browsePathTargets[*elementCount].remainingPathIndex = 0;
							UA_ExpandedNodeId_init(&(browsePathTargets[*elementCount].targetId));
							browsePathTargets[*elementCount].targetId.nodeId.namespaceIndex = opcua_pUaServer->v_NameSpaceIndex;
							browsePathTargets[*elementCount].targetId.nodeId.identifierType = UA_NODEIDTYPE_NUMERIC;
							browsePathTargets[*elementCount].targetId.nodeId.identifier.numeric = refElem.pobj->v_idL;
						}
						(*elementCount)++;
					}
				}
			} else if(Ov_CanCastTo(opcua_methodNode, startElem.pobj)){
				refElem.pobj = (OV_INSTPTR_ov_object)Ov_GetParent(ov_containment, startElem.pobj);
				if(refElem.pobj && ov_string_compare(refElem.pobj->v_identifier, targetIdentifier) == OV_STRCMP_EQUAL){
					if(levelCounter == relativePath->elementsSize){
						if(fillDescription){
							browsePathTargets[*elementCount].remainingPathIndex = 0;
							UA_ExpandedNodeId_init(&(browsePathTargets[*elementCount].targetId));
							browsePathTargets[*elementCount].targetId.nodeId.namespaceIndex = opcua_pUaServer->v_NameSpaceIndex;
							browsePathTargets[*elementCount].targetId.nodeId.identifierType = UA_NODEIDTYPE_NUMERIC;
							browsePathTargets[*elementCount].targetId.nodeId.identifier.numeric = refElem.pobj->v_idL;
						}
						(*elementCount)++;
					}
				}
			}
		}
		break;

	default:
		KS_logfile_info(("opua_WalkPath: reference type id not recognized."));
				return UA_STATUSCODE_BADNOTIMPLEMENTED;
		break;

	}

	return UA_STATUSCODE_GOOD;
}


/*
 * resolves a path. if a variable is encountered it will NOT go on from there
 * BIG TODO: consolidate with brose to reduce code-overlap and enhance maintainability
 */
OV_DLLFNCEXPORT UA_Int32 opcua_nodeStoreFunctions_translateBrowsePathsToNodeIDs(
	void *ensHandle,
	const UA_RequestHeader *requestHeader,
	UA_BrowsePath *browsePath,
	UA_UInt32 *indices,
	UA_UInt32 indicesSize,
	UA_BrowsePathResult *browsePathResults,
	UA_DiagnosticInfo *diagnosticInfos
) {
	UA_StatusCode uaResult;
	UA_UInt32 index;
	UA_UInt32 nodeCount = 0;
	OV_PATH nodePath;
	OV_INSTPTR_ov_object startingNode = NULL;
	UA_UInt32 levelCounter = 1;

	for(index = 0; index<indicesSize;index++){
		KS_logfile_debug(("translateBrowsePathsToNodeIDs: iteration %u, index %u", index, indices[index]));
		ov_memstack_lock();
		/*	get starting node	*/
		uaResult = opcua_nodeStoreFunctions_resolveNodeIdToPath(browsePath[indices[index]].startingNode, &nodePath);
		if(uaResult != UA_STATUSCODE_GOOD){
			KS_logfile_debug(("translateBrowsePathsToNodeIDs: could not resolve node for index %u in list. Skipping.", index));
			browsePathResults[indices[index]].statusCode = UA_STATUSCODE_BADNODEIDUNKNOWN;
			ov_memstack_unlock();
			continue;
		}
		if(nodePath.elements[nodePath.size - 1].elemtype != OV_ET_OBJECT){
			KS_logfile_debug(("translateBrowsePathsToNodeIDs: tried to use something not an object to start from. (index %u) Skipping.", index));
			browsePathResults[indices[index]].statusCode = UA_STATUSCODE_BADNOTIMPLEMENTED;
			ov_memstack_unlock();
			continue;
		}
		startingNode = (nodePath.elements[nodePath.size - 1].pobj);
		KS_logfile_debug(("translateBrowsePathsToNodeIDs: starting node is: %s", startingNode->v_identifier));

		/*	count possibilities	*/
		uaResult = opcua_WalkPath(&(browsePath[indices[index]].relativePath), levelCounter, startingNode, &nodeCount, UA_FALSE, NULL);
		/*	get Array	*/
		browsePathResults[indices[index]].targets = UA_Array_new(nodeCount, &UA_TYPES[UA_TYPES_BROWSEPATHTARGET]);
		if(!browsePathResults[indices[index]].targets && nodeCount){
			browsePathResults[indices[index]].statusCode = UA_STATUSCODE_BADOUTOFMEMORY;
			ov_memstack_unlock();
			break;
		}
		browsePathResults[indices[index]].targetsSize = nodeCount;
		/*	fill in DAta	*/
		nodeCount = 0;
		browsePathResults[indices[index]].statusCode = opcua_WalkPath(&(browsePath[indices[index]].relativePath), levelCounter, startingNode, &nodeCount, UA_TRUE, browsePathResults[indices[index]].targets);
		ov_memstack_unlock();
	}
    return UA_STATUSCODE_GOOD;
}
