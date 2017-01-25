
/******************************************************************************
*
*   FILE
*   ----
*   decoder.c
*
*   History
*   -------
*   2014-03-28   File created
*
*******************************************************************************
*
*   This file is generated by the 'acplt_builder' command
*
******************************************************************************/


#ifndef OV_COMPILE_LIBRARY_SSChelper
#define OV_COMPILE_LIBRARY_SSChelper
#endif


#include "SSChelper.h"
#include "libov/ov_macros.h"


OV_DLLFNCEXPORT OV_RESULT SSChelper_decoder_CMD_set(
    OV_INSTPTR_SSChelper_decoder          pobj,
    const OV_STRING  value
) {
	OV_UINT len=0;
	OV_STRING* temp=NULL;
	OV_RESULT result;

	if(!value)
	{
		return OV_ERR_OK;
	}
	temp=ov_string_split(value,";",&len);
	if(len ==2){
		result = ov_string_setvalue(&pobj->v_user,temp[0]);
		if(Ov_Fail(result))
			return result;
		result = ov_string_setvalue(&pobj->v_order,temp[1]);
		if(Ov_Fail(result))
			return result;
	}
	if(len ==3){
		result = ov_string_setvalue(&pobj->v_user,temp[0]);
		if(Ov_Fail(result))
			return result;
		result = ov_string_setvalue(&pobj->v_order,temp[1]);
		if(Ov_Fail(result))
			return result;
		result = ov_string_setvalue(&pobj->v_parameter,temp[2]);
		if(Ov_Fail(result))
			return result;
	}
	ov_string_setvalue(temp,NULL);
	ov_string_setvalue(&pobj->v_CMD,"");
	return OV_ERR_OK;

}

OV_DLLFNCEXPORT void SSChelper_decoder_typemethod(
	OV_INSTPTR_fb_functionblock	pfb,
	OV_TIME						*pltc
) {

    return;
}

