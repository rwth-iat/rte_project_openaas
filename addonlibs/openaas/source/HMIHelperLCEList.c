/******************************************************************************
*
*   FILE
*   ----
*   HMIHelperLCEList.c
*
*   History
*   -------
*   2017-03-08   File created
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
#include "libov/ov_time.h"


OV_DLLFNCEXPORT void openaas_HMIHelperLCEList_typemethod(
	OV_INSTPTR_fb_functionblock	pfb,
	OV_TIME						*pltc
) {
    /*    

    *   local variables
    */


	OV_INSTPTR_openaas_HMIHelperLCEList pinst = Ov_StaticPtrCast(openaas_HMIHelperLCEList, pfb);
	OV_INSTPTR_ov_object pobj = NULL;
	OV_INSTPTR_openaas_LifeCycleEntry pchild = NULL;
	OV_INSTPTR_openaas_aas paas = NULL;


	ov_string_setvalue(&pinst->v_CreatingInstanceId, "");
	ov_string_setvalue(&pinst->v_Data, "");
	ov_string_setvalue(&pinst->v_EventClass, "");
	ov_string_setvalue(&pinst->v_Id, "");
	ov_string_setvalue(&pinst->v_Subject, "");
	ov_string_setvalue(&pinst->v_TimeStamp, "");
	ov_string_setvalue(&pinst->v_WritingInstanceId, "");

	OV_UINT len = 0;
	OV_STRING *pathList = NULL;
	OV_STRING path = NULL;
	pathList = ov_string_split(pinst->v_AASPath, "/", &len);


	for (OV_UINT i = 4; i < len; i++){
		ov_string_append(&path, "/");
		ov_string_append(&path, pathList[i]);
	}

	pobj = ov_path_getobjectpointer(path,2);
	if (!pobj){
		pinst->v_Error = TRUE;
		ov_string_setvalue(&pinst->v_ErrorText, "Could not find an object for this path");
		ov_string_freelist(pathList);
		ov_database_free(path);
		return;
	}

	paas = Ov_DynamicPtrCast(openaas_aas, pobj);
	if (!paas){
		pinst->v_Error = TRUE;
		ov_string_setvalue(&pinst->v_ErrorText, "Object is not of aas-Type");
		ov_string_freelist(pathList);
		ov_database_free(path);
		return;
	}

	OV_STRING tmpString = NULL;
	OV_UINT i = 0;
	Ov_ForEachChildEx(ov_containment, &paas->p_LifeCycleArchive, pchild, openaas_LifeCycleEntry){
		if (i != 0){
			ov_string_append(&pinst->v_CreatingInstanceId, ";");
			ov_string_append(&pinst->v_Data, ";");
			ov_string_append(&pinst->v_EventClass, ";");
			ov_string_append(&pinst->v_Id, ";");
			ov_string_append(&pinst->v_Subject, ";");
			ov_string_append(&pinst->v_TimeStamp, ";");
			ov_string_append(&pinst->v_WritingInstanceId, ";");
		}

		switch (pchild->v_CreatingInstanceIdType){
			case URI:
				ov_string_append(&pinst->v_CreatingInstanceId, "URI:");
			break;
			case ISO:
				ov_string_append(&pinst->v_CreatingInstanceId, "ISO:");
			break;
		}
		ov_string_append(&pinst->v_CreatingInstanceId, pchild->v_CreatingInstanceIdString);

		ov_string_append(&pinst->v_EventClass, pchild->v_EventClass);

		ov_string_print(&tmpString, "%i", pchild->v_Id);
		ov_string_append(&pinst->v_Id, tmpString);

		ov_string_append(&pinst->v_Subject, pchild->v_Subject);


		ov_string_append(&pinst->v_TimeStamp, ov_time_timetoascii(&pchild->v_TimeStamp));

		switch (pchild->v_WritingInstanceIdType){
			case URI:
				ov_string_append(&pinst->v_WritingInstanceId, "URI:");
			break;
			case ISO:
				ov_string_append(&pinst->v_WritingInstanceId, "ISO:");
			break;
		}
		ov_string_append(&pinst->v_WritingInstanceId, pchild->v_WritingInstanceIdString);

		if(!(pchild->v_Data.value.vartype & OV_VT_ISVECTOR)){
			switch(pchild->v_Data.value.vartype & OV_VT_KSMASK){
				case OV_VT_BOOL:
					if (pchild->v_Data.value.valueunion.val_bool == TRUE)
						ov_string_append(&pinst->v_Data, "true");
					else
						ov_string_append(&pinst->v_Data, "false");
				break;
				case OV_VT_STRING:
					ov_string_append(&pinst->v_Data, pchild->v_Data.value.valueunion.val_string);
				break;
				case OV_VT_DOUBLE:
					ov_string_print(&tmpString, "%lf", pchild->v_Data.value.valueunion.val_double);
					ov_string_append(&pinst->v_Data, tmpString);
				break;
				case OV_VT_INT:
					ov_string_print(&tmpString, "%i", pchild->v_Data.value.valueunion.val_int);
					ov_string_append(&pinst->v_Data, tmpString);
				break;
				case OV_VT_UINT:
					ov_string_print(&tmpString, "%u", pchild->v_Data.value.valueunion.val_uint);
					ov_string_append(&pinst->v_Data, tmpString);
				break;
				case OV_VT_SINGLE:
					ov_string_print(&tmpString, "%f", pchild->v_Data.value.valueunion.val_single);
					ov_string_append(&pinst->v_Data, tmpString);
				break;
				default:
					ov_string_append(&pinst->v_Data, "DataType not supported");
				break;
			}
		}else{
			ov_string_append(&pinst->v_Data, "Array");
		}

	i++;
	}

	ov_database_free(tmpString);
	ov_string_freelist(pathList);
	ov_database_free(path);

    return;
}
