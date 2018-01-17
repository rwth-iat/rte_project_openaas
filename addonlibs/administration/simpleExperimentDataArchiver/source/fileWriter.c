
/******************************************************************************
 *
 *   FILE
 *   ----
 *   fileWriter.c
 *
 *   History
 *   -------
 *   2017-11-16   File created
 *
 *******************************************************************************
 *
 *   This file is generated by the 'acplt_builder' command
 *
 ******************************************************************************/


#ifndef OV_COMPILE_LIBRARY_simpleExperimentDataArchiver
#define OV_COMPILE_LIBRARY_simpleExperimentDataArchiver
#endif


#include "simpleExperimentDataArchiver.h"
#include "libov/ov_macros.h"
#include <unistd.h>

typedef enum {
	CONFIGURE = 0,
	SYNC = 1,
	PREPAREARCHIVE = 2,
	WAITING = 3,
	SAVETOFILE = 4,
	CLEANUP = 5,
	FAULT = 99
} WriterState_Types;

OV_STRING anyToString(OV_ANY *value, OV_STRING* tmpStr) {
	OV_STRING tmpStr2 = NULL;
	OV_UINT memsize = 0;

#undef Finally
#define Finally()								\
		ov_string_setvalue(&tmpStr2,NULL);		\

	if(ov_string_compare(*tmpStr,"") != OV_STRCMP_EQUAL){
		ov_string_setvalue(tmpStr,NULL);
	}

	switch (value->value.vartype & OV_VT_KSMASK) {

	case (OV_VT_STRING):{
		Finally();
		ov_string_setvalue(tmpStr,value->value.valueunion.val_string);
		return *tmpStr;
	}
	case (OV_VT_STRING_VEC):{
		if (value->value.valueunion.val_string_vec.veclen > 0) {
			memsize = value->value.valueunion.val_string_vec.veclen;
			ov_string_setvalue(tmpStr, "[ ");
			for (OV_UINT i = 0; i < memsize - 1; i++) {
				ov_string_append(tmpStr, value->value.valueunion.val_string_vec.value[i]);
				ov_string_append(tmpStr, " , ");
			}
			ov_string_append(tmpStr, value->value.valueunion.val_string_vec.value[memsize - 1]);
			ov_string_append(tmpStr, " ]");
		}
		Finally();
		return *tmpStr;
	}
	case (OV_VT_BOOL):{
		ov_string_print(tmpStr, "%d", value->value.valueunion.val_bool); //TODO: Fix mem leak
		Finally();
		return *tmpStr;
	}
	case (OV_VT_BOOL_VEC):{
		if (value->value.valueunion.val_bool_vec.veclen > 0) {
			memsize = value->value.valueunion.val_bool_vec.veclen;
			ov_string_setvalue(tmpStr, "[ ");
			for (OV_UINT i = 0; i < memsize - 1; i++) {
				ov_string_print(&tmpStr2, "%d , ",value->value.valueunion.val_bool_vec.value[i]);
				ov_string_append(tmpStr, tmpStr2);
			}
			ov_string_print(&tmpStr2, "%d ]",value->value.valueunion.val_bool_vec.value[memsize - 1]);
			ov_string_append(tmpStr, tmpStr2);
		}
		Finally();
		return *tmpStr;
	}
	case (OV_VT_INT):{
		ov_string_print(tmpStr, "%d", value->value.valueunion.val_int);
		Finally();
		return *tmpStr;
	}
	case (OV_VT_INT_VEC): {
		if (value->value.valueunion.val_int_vec.veclen > 0) {
			memsize = value->value.valueunion.val_int_vec.veclen;
			ov_string_setvalue(tmpStr, "[ ");
			for (OV_UINT i = 0; i < memsize - 1; i++) {
				ov_string_print(&tmpStr2, "%d , ",value->value.valueunion.val_int_vec.value[i]);
				ov_string_append(tmpStr, tmpStr2);
			}
			ov_string_print(&tmpStr2, "%d ]",value->value.valueunion.val_int_vec.value[memsize - 1]);
			ov_string_append(tmpStr, tmpStr2);
		}
		Finally();
		return *tmpStr;
	}

	case (OV_VT_UINT):{
		ov_string_print(tmpStr, "%u", value->value.valueunion.val_uint);
		Finally();
		return *tmpStr;
	}
	case (OV_VT_UINT_VEC):{
		if (value->value.valueunion.val_uint_vec.veclen > 0) {
			memsize = value->value.valueunion.val_uint_vec.veclen;
			ov_string_setvalue(tmpStr, "[ ");
			for (OV_UINT i = 0; i < memsize - 1; i++) {
				ov_string_print(&tmpStr2, "%u , ", value->value.valueunion.val_uint_vec.value[i]);
				ov_string_append(tmpStr, tmpStr2);
			}
			ov_string_print(&tmpStr2, "%u ]", value->value.valueunion.val_uint_vec.value[memsize - 1]);
			ov_string_append(tmpStr, tmpStr2);
		}
		Finally();
		return *tmpStr;
	}
	case (OV_VT_SINGLE):{
		ov_string_print(tmpStr, "%f", value->value.valueunion.val_single);
		Finally();
		return *tmpStr;
	}
	case (OV_VT_SINGLE_VEC):{
		if (value->value.valueunion.val_single_vec.veclen > 0) {
			memsize = value->value.valueunion.val_single_vec.veclen;
			ov_string_setvalue(tmpStr, " [");
			for (OV_UINT i = 0; i < memsize - 1; i++) {
				ov_string_print(&tmpStr2, "%f , ",value->value.valueunion.val_single_vec.value[i]);
				ov_string_append(tmpStr, tmpStr2);
			}
			ov_string_print(&tmpStr2, "%f ]",value->value.valueunion.val_single_vec.value[memsize - 1]);
			ov_string_append(tmpStr, tmpStr2);
		}
		Finally();
		return *tmpStr;
	}
	case (OV_VT_DOUBLE):{
		ov_string_print(tmpStr, "%f", value->value.valueunion.val_double);
		Finally();
		return *tmpStr;
	}
	case (OV_VT_DOUBLE_VEC):{
		if (value->value.valueunion.val_double_vec.veclen > 0) {
			memsize = value->value.valueunion.val_double_vec.veclen;
			ov_string_setvalue(tmpStr, "[");
			for (OV_UINT i = 1; i < memsize; i++) {
				ov_string_print(&tmpStr2, "%f , ",value->value.valueunion.val_double_vec.value[i]);
				ov_string_append(tmpStr, tmpStr2);
			}
			ov_string_print(&tmpStr2, "%f ]",value->value.valueunion.val_double_vec.value[memsize - 1]);
			ov_string_append(tmpStr, tmpStr2);
		}
		Finally();
		return *tmpStr;
	}
	case (OV_VT_TIME):{
		tmpStr2 = ov_time_timetoascii(&value->value.valueunion.val_time);
		ov_string_setvalue(tmpStr,tmpStr2);
		return *tmpStr;
	}
	default:{
		Finally();
		return NULL;
	}
	}
	return NULL;
}

OV_DLLFNCEXPORT OV_BOOL simpleExperimentDataArchiver_writer_start_get(
    OV_INSTPTR_simpleExperimentDataArchiver_writer          pobj
) {
    return pobj->v_start;
}

OV_DLLFNCEXPORT OV_RESULT simpleExperimentDataArchiver_writer_start_set(
    OV_INSTPTR_simpleExperimentDataArchiver_writer          pobj,
    const OV_BOOL  value
) {
    pobj->v_start = value;
    return OV_ERR_OK;
}

OV_DLLFNCEXPORT OV_BOOL simpleExperimentDataArchiver_writer_stop_get(
    OV_INSTPTR_simpleExperimentDataArchiver_writer          pobj
) {
    return pobj->v_stop;
}

OV_DLLFNCEXPORT OV_RESULT simpleExperimentDataArchiver_writer_stop_set(
    OV_INSTPTR_simpleExperimentDataArchiver_writer          pobj,
    const OV_BOOL  value
) {
    pobj->v_stop = value;
    return OV_ERR_OK;
}

OV_DLLFNCEXPORT OV_BOOL simpleExperimentDataArchiver_writer_reset_get(
    OV_INSTPTR_simpleExperimentDataArchiver_writer          pobj
) {
    return pobj->v_reset;
}

OV_DLLFNCEXPORT OV_RESULT simpleExperimentDataArchiver_writer_reset_set(
    OV_INSTPTR_simpleExperimentDataArchiver_writer          pobj,
    const OV_BOOL  value
) {
    pobj->v_reset = value;
    return OV_ERR_OK;
}

OV_DLLFNCEXPORT OV_UINT simpleExperimentDataArchiver_writer_state_get(
    OV_INSTPTR_simpleExperimentDataArchiver_writer          pobj
) {
    return pobj->v_state;
}

OV_DLLFNCEXPORT OV_RESULT simpleExperimentDataArchiver_writer_state_set(
    OV_INSTPTR_simpleExperimentDataArchiver_writer          pobj,
    const OV_UINT  value
) {
	switch (value) {
		case CONFIGURE:
			simpleExperimentDataArchiver_writer_stateName_set(pobj,"CONFIGURE");
			break;
		case PREPAREARCHIVE:
			simpleExperimentDataArchiver_writer_stateName_set(pobj,"PREPAREARCHIVE");
			break;
		case WAITING:
			simpleExperimentDataArchiver_writer_stateName_set(pobj,"WAITING");
			break;
		case SAVETOFILE:
			simpleExperimentDataArchiver_writer_stateName_set(pobj,"SAVETOFILE");
			break;
		case CLEANUP:
			simpleExperimentDataArchiver_writer_stateName_set(pobj,"CLEANUP");
			break;
		case FAULT:
			simpleExperimentDataArchiver_writer_stateName_set(pobj,"FAULT");
			break;
		default:
			simpleExperimentDataArchiver_writer_stateName_set(pobj,"INVALIDSTATE");
			break;
		}
		pobj->v_state = value;
		return OV_ERR_OK;
}

OV_DLLFNCEXPORT OV_RESULT simpleExperimentDataArchiver_fileWriter_archiveDir_set(
		OV_INSTPTR_simpleExperimentDataArchiver_fileWriter          pobj,
		const OV_STRING  value
) {
	return ov_string_setvalue(&pobj->v_archiveDir,value);
}

OV_DLLFNCEXPORT OV_STRING simpleExperimentDataArchiver_fileWriter_fileName_get(
		OV_INSTPTR_simpleExperimentDataArchiver_fileWriter          pobj
) {
	return pobj->v_fileName;
}

OV_DLLFNCEXPORT OV_RESULT simpleExperimentDataArchiver_fileWriter_fileName_set(
		OV_INSTPTR_simpleExperimentDataArchiver_fileWriter          pobj,
		const OV_STRING  value
) {
	return ov_string_setvalue(&pobj->v_fileName,value);
}

OV_DLLFNCEXPORT OV_RESULT simpleExperimentDataArchiver_fileWriter_constructor(
		OV_INSTPTR_ov_object 	pobj
) {
	/*
	 *   local variables
	 */
	// OV_INSTPTR_simpleExperimentDataArchiver_fileWriter pinst = Ov_StaticPtrCast(simpleExperimentDataArchiver_fileWriter, pobj);
	OV_RESULT    result;

	/* do what the base class does first */
	result = fb_functionblock_constructor(pobj);
	if(Ov_Fail(result))
		return result;

	/* do what */


	return OV_ERR_OK;
}

OV_DLLFNCEXPORT void simpleExperimentDataArchiver_fileWriter_destructor(
		OV_INSTPTR_ov_object 	pobj
) {
	/*
	 *   local variables
	 */
	// OV_INSTPTR_simpleExperimentDataArchiver_fileWriter pinst = Ov_StaticPtrCast(simpleExperimentDataArchiver_fileWriter, pobj);

	/* do what */

	/* destroy object */
	fb_functionblock_destructor(pobj);

	return;
}

OV_DLLFNCEXPORT void simpleExperimentDataArchiver_fileWriter_typemethod(
		OV_INSTPTR_fb_functionblock	pfb,
		OV_TIME						*pltc
) {
	/*
	 *   local variables
	 */
	OV_INSTPTR_simpleExperimentDataArchiver_fileWriter pinst = Ov_StaticPtrCast(simpleExperimentDataArchiver_fileWriter, pfb);
	WriterState_Types state = simpleExperimentDataArchiver_writer_state_get(Ov_DynamicPtrCast(simpleExperimentDataArchiver_writer,pinst));
	OV_INSTPTR_simpleExperimentDataArchiver_DataArchiver pSubscription = NULL;
	OV_INSTPTR_simpleExperimentDataArchiver_Variable pVariable = NULL;
	OV_STRING tmpfilename = NULL;
	OV_STRING firstLine = NULL;
	OV_STRING line = NULL;
	OV_STRING tmpS = NULL;
	OV_TIME tmpT = {.secs = 0, .usecs = 0};
	OV_TIME_SPAN tmpTS = {.secs = 0, .usecs = 0};
	OV_UINT fileIndex = 0;
	FILE *pFile;
	OV_TIME * timeStamp = NULL;


#define GETDATASOURCE() \
		pSubscription = Ov_GetParent(simpleExperimentDataArchiver_HandleData,pinst);\
		if(!pSubscription){\
			state = FAULT;\
			simpleExperimentDataArchiver_writer_errorMsg_set(Ov_DynamicPtrCast(simpleExperimentDataArchiver_writer,pinst),"Connection to Subscription missing");\
			break;\
		}\

	switch (state){
	case SYNC : {
		/* check inputs */
		GETDATASOURCE();

		fb_task_cyctime_set(Ov_DynamicPtrCast(fb_task,pinst),&pSubscription->v_cyctime);
		tmpTS.secs = (OV_UINT) 15/10 * pSubscription->v_cyctime.secs;
		tmpTS.usecs = (OV_UINT) 15/10 * pSubscription->v_cyctime.usecs;
		ov_time_add(&tmpT, & pSubscription->v_proctime, & tmpTS);
		fb_task_proctime_set(Ov_DynamicPtrCast(fb_task,pinst),&tmpT);

		state = PREPAREARCHIVE;
		break;
	}
	case PREPAREARCHIVE : {
		/* create file name */
		if(ov_string_compare(pinst->v_archiveDir,"")==OV_STRCMP_EQUAL){
			state = FAULT;
			simpleExperimentDataArchiver_writer_errorMsg_set(Ov_DynamicPtrCast(simpleExperimentDataArchiver_writer,pinst),"Archive Directory missing");
			break;
		}

		/* create new file name, e.g. Mixture_1.csv, increase index if file already exists
		 * TODO: max fileIndex?
		 *  */
		do {
			ov_string_print(&tmpfilename, "%s/Mixture_%u.csv",pinst->v_archiveDir, ++fileIndex);
		} while (access(tmpfilename, F_OK) != -1 && fileIndex < 10000);
		if (fileIndex < 10000) {
			// filename set
			simpleExperimentDataArchiver_fileWriter_fileName_set(pinst,tmpfilename);
			ov_string_setvalue(&tmpfilename, NULL);
		} else {
			ov_string_setvalue(&pinst->v_errorMsg,"PREPAREARCHIVE: Could not set filename");
		}

		/* collect information for first line of file */
		GETDATASOURCE();
		ov_string_setvalue(&firstLine,"timeStamp; ");
		Ov_ForEachChildEx(simpleExperimentDataArchiver_SubscriptionResult,pSubscription,pVariable,simpleExperimentDataArchiver_Variable){
			ov_string_append(&firstLine,simpleExperimentDataArchiver_Variable_NodeIDIdentifier_get(pVariable));
			ov_string_append(&firstLine,"; ");
		}
		ov_string_append(&firstLine,"\n");

		/* create file and write first line */
		pFile = fopen(pinst->v_fileName, "ab+");
		fputs(firstLine, pFile);
		fclose(pFile);
		ov_string_setvalue(&firstLine, NULL);

		/* switch to state waiting */
		pinst->v_timeLastWrite.secs = 0;
		pinst->v_timeLastWrite.usecs = 0;
		state = WAITING;
		break;
	}
	case WAITING : {
		/* wait for start command */
		if(pinst->v_start){
			state = SAVETOFILE;
			pinst->v_start = false;
		}
		break;
	}
	case SAVETOFILE : {
		/*TODO: check if file still accessible, i.e. not opened by user */

		if(pinst->v_stop){
			state = SYNC;
			pinst->v_stop = false;
		}

		GETDATASOURCE();

		pVariable = Ov_GetFirstChild(simpleExperimentDataArchiver_SubscriptionResult,pSubscription);

		/* timeStamp of first NodeID*/
		timeStamp = simpleExperimentDataArchiver_Variable_varTime_get(pVariable);

		/* get time stamp of first nodeID TODO: hopefully values of all node IDs have the same time stamp i.e. change at same rate
		 * save to output string
		 * Stringformat:
		 * TIMESTAMP; VALUE; VALUE; VALUE; [VECVALUE , VECVALUE]; VALUE; \n */
		if(ov_time_compare(timeStamp,&pinst->v_timeLastWrite) != OV_TIMECMP_AFTER){ // TODO: check if new data is available
			break;
		}

		pinst->v_timeLastWrite.secs = timeStamp->secs;
		pinst->v_timeLastWrite.usecs = timeStamp->usecs;

		/* add timeStamp to line */
		ov_string_print(&line,"%s; ",ov_time_timetoascii(timeStamp));

		/* get values of all node IDs */
		Ov_ForEachChildEx(simpleExperimentDataArchiver_SubscriptionResult,pSubscription,pVariable,simpleExperimentDataArchiver_Variable){
			anyToString(&pVariable->v_varValue,&tmpS);
			ov_string_append(&line,tmpS);
			ov_string_append(&line,"; ");
			ov_string_setvalue(&tmpS,"");
		}
		ov_string_append(&line,"\n");

		/*write response to file
		 * create file if it does not exist, append if it does */
		pFile = fopen(pinst->v_fileName, "ab+");
		fputs(line, pFile);
		ov_string_setvalue(&line,"");
		fclose(pFile);

		break;
	}
	case CLEANUP : {
		break;
	}
	case FAULT : {
		if(pinst->v_reset){
			state = SYNC;
			ov_string_setvalue(&pinst->v_errorMsg,"");
		}
		break;
	}
	default: {
		state = FAULT;
		break;
	}
	}

	simpleExperimentDataArchiver_writer_state_set(Ov_DynamicPtrCast(simpleExperimentDataArchiver_writer,pinst),state);
	return;
}

