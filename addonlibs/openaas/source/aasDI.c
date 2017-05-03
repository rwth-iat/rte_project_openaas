
/******************************************************************************
*
*   FILE
*   ----
*   aasDI.c
*
*   History
*   -------
*   2017-02-08   File created
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
#include "opcua_interface.h"
#include "openaas_helpers.h"
#include "opcua_helpers.h"
#include "ua_openaas_generated.h"
#include "ua_openaas_generated_handling.h"
#include "ua_openaas_generated_encoding_binary.h"

OV_DLLFNCEXPORT OV_RESULT openaas_aasDI_AssetIPAddress_set(
    OV_INSTPTR_openaas_aasDI          pobj,
    const OV_STRING  value
) {
    return ov_string_setvalue(&pobj->v_AssetIPAddress,value);
}

OV_DLLFNCEXPORT OV_RESULT openaas_aasDI_AssetAASIdString_set(
    OV_INSTPTR_openaas_aasDI          pobj,
    const OV_STRING  value
) {
    return ov_string_setvalue(&pobj->v_AssetAASIdString,value);
}

OV_DLLFNCEXPORT OV_RESULT openaas_aasDI_AssetAASIdType_set(
    OV_INSTPTR_openaas_aasDI          pobj,
    const OV_UINT  value
) {
    pobj->v_AssetAASIdType = value;
    return OV_ERR_OK;
}

OV_DLLFNCEXPORT OV_RESULT openaas_aasDI_AASIdString_set(
    OV_INSTPTR_openaas_aasDI          pobj,
    const OV_STRING  value
) {
    return ov_string_setvalue(&pobj->v_AASIdString,value);
}

OV_DLLFNCEXPORT OV_RESULT openaas_aasDI_AASIdType_set(
    OV_INSTPTR_openaas_aasDI          pobj,
    const OV_UINT  value
) {
    pobj->v_AASIdType = value;
    return OV_ERR_OK;
}

OV_DLLFNCEXPORT OV_RESULT openaas_aasDI_StartAASDI_set(
    OV_INSTPTR_openaas_aasDI          pobj,
    const OV_BOOL  value
) {
    pobj->v_StartAASDI = value;
    pobj->v_actimode = 1;
    pobj->v_iexreq = TRUE;
    pobj->v_cyctime.secs = 3;
    return OV_ERR_OK;
}

OV_DLLFNCEXPORT OV_RESULT openaas_aasDI_StopAASDI_set(
    OV_INSTPTR_openaas_aasDI          pobj,
    const OV_BOOL  value
) {
    pobj->v_StopAASDI = value;
    pobj->v_actimode = 0;
    pobj->v_iexreq = FALSE;
    return OV_ERR_OK;
}

OV_DLLFNCEXPORT OV_ACCESS openaas_aasDI_getaccess(
	OV_INSTPTR_ov_object	pobj,
	const OV_ELEMENT		*pelem,
	const OV_TICKET			*pticket
) {
    /*    
    *   local variables
    */
	return (OV_ACCESS)(OV_AC_WRITE | OV_AC_READ | OV_AC_LINKABLE | OV_AC_UNLINKABLE | OV_AC_DELETEABLE | OV_AC_RENAMEABLE);
}

OV_DLLFNCEXPORT void openaas_aasDI_typemethod(
	OV_INSTPTR_fb_functionblock	pfb,
	OV_TIME						*pltc
) {
    /*    
    *   local variables
    */

    OV_INSTPTR_openaas_aasDI pinst = Ov_StaticPtrCast(openaas_aasDI, pfb);
    OV_STRING ipAddress = NULL;
    ov_string_setvalue(&ipAddress, "opc.tcp://");
    ov_string_append(&ipAddress, pinst->v_AssetIPAddress);
    ov_string_append(&ipAddress, ":16664");

    UA_Client *client = UA_Client_new(UA_ClientConfig_standard);
	UA_StatusCode retval = UA_Client_connect(client, ipAddress);
	if (retval != UA_STATUSCODE_GOOD) {
		UA_Client_delete(client);
		return ;
	}
	size_t argInSize = 2;
	size_t argOutSize;
	UA_Variant *inputArgs = UA_Array_new(argInSize,
			&UA_TYPES[UA_TYPES_VARIANT]);
	for (size_t i = 0; i < argInSize; i++) {
		UA_Variant_init(&inputArgs[i]);
	}
	// convert input to UA types
	UA_Identification AASId;
	AASId.idType = pinst->v_AssetAASIdType;
	AASId.idSpec = UA_String_fromChars(pinst->v_AssetAASIdString);
	UA_UInt32 count = 100000;

	UA_Variant_setScalarCopy(&inputArgs[0], &AASId,
			&UA_OPENAAS[UA_OPENAAS_IDENTIFICATION]);
	UA_Variant_setScalarCopy(&inputArgs[1], &count, &UA_TYPES[UA_TYPES_UINT32]);

	UA_NodeId methNodeId = UA_NODEID_STRING(4,
			"/TechUnits/openAAS/ModelmanagerOpenAAS||getLastLCEs");
	UA_NodeId objectId = UA_NODEID_STRING(4,
			"/TechUnits/openAAS/ModelmanagerOpenAAS");

	UA_Variant *output;
	retval = UA_Client_call(client, objectId, methNodeId, argInSize, inputArgs,
			&argOutSize, &output);

	IdentificationType aasId;
	IdentificationType_init(&aasId);
	ov_string_setvalue(&aasId.IdSpec, pinst->v_AASIdString);
	aasId.IdType = pinst->v_AASIdType;

	IdentificationType assetAASId;
	IdentificationType_init(&assetAASId);
	ov_string_setvalue(&assetAASId.IdSpec, pinst->v_AssetAASIdString);
	assetAASId.IdType = pinst->v_AssetAASIdType;

	if (retval == UA_STATUSCODE_GOOD) {
		if (argOutSize == 3){
			//UA_StatusCode *tmpUAStatusCode = (UA_StatusCode*)(output[0].data);
			//UA_LifeCycleEntry *tmpUALifeCycleEntry = (UA_LifeCycleEntry*)(output[1].data);
			UA_UInt32 *tmpUAarrayDimension = (UA_UInt32*)(output[2].data);

			for (OV_UINT i = 0; i < *tmpUAarrayDimension; i++){
				LifeCycleEntry lce;
				LifeCycleEntry_init(&lce);
				UA_LifeCycleEntry tmpUALifeCycleEntry;
				UA_LifeCycleEntry_init(&tmpUALifeCycleEntry);

				UA_ExtensionObject ext = ((UA_ExtensionObject*) output[1].data)[i];
				size_t offset = 0;
				UA_LifeCycleEntry_decodeBinary(&ext.content.encoded.body, &offset,
						&tmpUALifeCycleEntry);

				copyOPCUAStringToOV(tmpUALifeCycleEntry.creatingInstance.idSpec, &lce.creatingInstance.IdSpec);
				lce.creatingInstance.IdType = tmpUALifeCycleEntry.creatingInstance.idType;

				copyOPCUAStringToOV(tmpUALifeCycleEntry.writingInstance.idSpec, &lce.writingInstance.IdSpec);
				lce.writingInstance.IdType = tmpUALifeCycleEntry.writingInstance.idType;

				copyOPCUAStringToOV(tmpUALifeCycleEntry.eventClass, &lce.eventClass);

				copyOPCUAStringToOV(tmpUALifeCycleEntry.subject, &lce.subject);

				ov_VariantToAny(&tmpUALifeCycleEntry.data.value, &lce.data);
				lce.data.time = ov_1601nsTimeToOvTime(tmpUALifeCycleEntry.data.sourceTimestamp);

				openaas_modelmanager_createLCE(aasId, lce);

				size_t argInSize2 = 2;
				size_t argOutSize2 = 0;
				UA_Variant *inputArgs2 = UA_Array_new(argInSize,
						&UA_TYPES[UA_TYPES_VARIANT]);
				for (size_t i = 0; i < argInSize2; i++) {
					UA_Variant_init(&inputArgs[i]);
				}

				UA_UInt64 lceId = tmpUALifeCycleEntry.id;

				UA_Variant_setScalarCopy(&inputArgs2[0], &AASId,
						&UA_OPENAAS[UA_OPENAAS_IDENTIFICATION]);
				UA_Variant_setScalarCopy(&inputArgs2[1], &lceId, &UA_TYPES[UA_TYPES_UINT64]);

				UA_NodeId methNodeId2 = UA_NODEID_STRING(4,
						"/TechUnits/openAAS/ModelmanagerOpenAAS||deleteLCE");
				UA_NodeId objectId2 = UA_NODEID_STRING(4,
						"/TechUnits/openAAS/ModelmanagerOpenAAS");

				UA_Variant *output2 = NULL;
				retval = UA_Client_call(client, objectId2, methNodeId2, argInSize2, inputArgs2,
						&argOutSize2, &output2);


				UA_Array_delete(output2, argOutSize2, &UA_TYPES[UA_TYPES_VARIANT]);
				UA_Array_delete(inputArgs2, argInSize2, &UA_TYPES[UA_TYPES_VARIANT]);
				UA_LifeCycleEntry_deleteMembers(&tmpUALifeCycleEntry);
				LifeCycleEntry_deleteMembers(&lce);
			}
		}
	}
	UA_Identification_deleteMembers(&AASId);
	UA_Array_delete(inputArgs, argInSize, &UA_TYPES[UA_TYPES_VARIANT]);
	UA_Array_delete(output, argOutSize, &UA_TYPES[UA_TYPES_VARIANT]);
	IdentificationType_deleteMembers(&aasId);
	IdentificationType_deleteMembers(&assetAASId);
	UA_Client_disconnect(client);
	UA_Client_delete(client);
	ov_database_free(ipAddress);
    return;
}
