#******************************************************************************
#*
#*   FILE
#*   ----
#*   generic.mk - Makefile for user libs (generic part)
#******************************************************************************
#*
#*   This file is generated by the 'acplt_makmak' command
#*
#******************************************************************************

#	Directories
#	-----------

MODEL_DIR         = ../../model/
SOURCE_DIR        = ../../source/
INCLUDE_DIR       = ../../include/
ROOT_DIR          = ../../../../
BASE_DIR          = $(ROOT_DIR)
BASE_INC_DIR      = $(BASE_DIR)system/sysdevbase/ov/include/
BASE_LIB_DIR      = $(BASE_DIR)system/sysdevbase/ov/lib/
BASE_MODEL_DIR    = $(BASE_DIR)system/sysdevbase/ov/model/
BIN_DIR           = $(ROOT_DIR)system/sysbin/
USER_DIR          = ../../../
USERLIB_DIR       = $(ROOT_DIR)system/addonlibs/
SYS_DIR           = $(BASE_DIR)system/sysdevbase/
SYSLIB_DIR        = $(ROOT_DIR)system/syslibs/
KSBASE_MODEL_DIR           = $(USER_DIR)ksbase/model/
KSBASE_INCLUDE_DIR         = $(USER_DIR)ksbase/include/
OPCUA_MODEL_DIR           = $(USER_DIR)opcua/model/
OPCUA_INCLUDE_DIR         = $(USER_DIR)opcua/include/
KSAPI_MODEL_DIR           = $(USER_DIR)ksapi/model/
KSAPI_INCLUDE_DIR         = $(USER_DIR)ksapi/include/
IDENTIFICATION_MODEL_DIR           = $(USER_DIR)identification/model/
IDENTIFICATION_INCLUDE_DIR         = $(USER_DIR)identification/include/
PROPERTYVALUESTATEMENT_MODEL_DIR           = $(USER_DIR)propertyValueStatement/model/
PROPERTYVALUESTATEMENT_INCLUDE_DIR         = $(USER_DIR)propertyValueStatement/include/
LIFECYCLEENTRY_MODEL_DIR           = $(USER_DIR)lifeCycleEntry/model/
LIFECYCLEENTRY_INCLUDE_DIR         = $(USER_DIR)lifeCycleEntry/include/
MESSAGESYS_MODEL_DIR           = $(USER_DIR)MessageSys/model/
MESSAGESYS_INCLUDE_DIR         = $(USER_DIR)MessageSys/include/
OPENAAS_MODEL_DIR           = $(USER_DIR)openaas/model/
OPENAAS_INCLUDE_DIR         = $(USER_DIR)openaas/include/
SERVICES_MODEL_DIR           = $(USER_DIR)services/model/
SERVICES_INCLUDE_DIR         = $(USER_DIR)services/include/
SUBMODELADMINISTRATION_MODEL_DIR           = $(USER_DIR)subModelAdministration/model/
SUBMODELADMINISTRATION_INCLUDE_DIR         = $(USER_DIR)subModelAdministration/include/
IDENTIFICATIONOPCUAINTERFACE_MODEL_DIR           = $(USER_DIR)identificationOPCUAInterface/model/
IDENTIFICATIONOPCUAINTERFACE_INCLUDE_DIR         = $(USER_DIR)identificationOPCUAInterface/include/
PROPERTYVALUESTATEMENTOPCUAINTERFACE_MODEL_DIR           = $(USER_DIR)propertyValueStatementOPCUAInterface/model/
PROPERTYVALUESTATEMENTOPCUAINTERFACE_INCLUDE_DIR         = $(USER_DIR)propertyValueStatementOPCUAInterface/include/
LIFECYCLEENTRYOPCUAINTERFACE_MODEL_DIR           = $(USER_DIR)lifeCycleEntryOPCUAInterface/model/
LIFECYCLEENTRYOPCUAINTERFACE_INCLUDE_DIR         = $(USER_DIR)lifeCycleEntryOPCUAInterface/include/
SERVICESOPCUAINTERFACE_MODEL_DIR           = $(USER_DIR)servicesOPCUAInterface/model/
SERVICESOPCUAINTERFACE_INCLUDE_DIR         = $(USER_DIR)servicesOPCUAInterface/include/
OPENAASOPCUAINTERFACE_MODEL_DIR           = $(USER_DIR)openaasOPCUAInterface/model/
OPENAASOPCUAINTERFACE_INCLUDE_DIR         = $(USER_DIR)openaasOPCUAInterface/include/
FB_MODEL_DIR           = $(SYS_DIR)fb/model/
FB_INCLUDE_DIR         = $(SYS_DIR)fb/include/
#   Rules
#   -----

.SUFFIXES:
.SUFFIXES: $(_C) .h .ovm $(_LIB) $(_DLL) $(_OBJ)

#	Paths and defines
#	-----------------

ifeq ($(COMPILER), MSVC)
INCLUDES  = /I$(BASE_INC_DIR) /I$(BASE_MODEL_DIR) \
			/I$(KSBASE_MODEL_DIR) /I$(KSBASE_INCLUDE_DIR) \
			/I$(OPCUA_MODEL_DIR) /I$(OPCUA_INCLUDE_DIR) \
			/I$(KSAPI_MODEL_DIR) /I$(KSAPI_INCLUDE_DIR) \
			/I$(IDENTIFICATION_MODEL_DIR) /I$(IDENTIFICATION_INCLUDE_DIR) \
			/I$(PROPERTYVALUESTATEMENT_MODEL_DIR) /I$(PROPERTYVALUESTATEMENT_INCLUDE_DIR) \
			/I$(LIFECYCLEENTRY_MODEL_DIR) /I$(LIFECYCLEENTRY_INCLUDE_DIR) \
			/I$(MESSAGESYS_MODEL_DIR) /I$(MESSAGESYS_INCLUDE_DIR) \
			/I$(OPENAAS_MODEL_DIR) /I$(OPENAAS_INCLUDE_DIR) \
			/I$(SERVICES_MODEL_DIR) /I$(SERVICES_INCLUDE_DIR) \
			/I$(SUBMODELADMINISTRATION_MODEL_DIR) /I$(SUBMODELADMINISTRATION_INCLUDE_DIR) \
			/I$(IDENTIFICATIONOPCUAINTERFACE_MODEL_DIR) /I$(IDENTIFICATIONOPCUAINTERFACE_INCLUDE_DIR) \
			/I$(PROPERTYVALUESTATEMENTOPCUAINTERFACE_MODEL_DIR) /I$(PROPERTYVALUESTATEMENTOPCUAINTERFACE_INCLUDE_DIR) \
			/I$(LIFECYCLEENTRYOPCUAINTERFACE_MODEL_DIR) /I$(LIFECYCLEENTRYOPCUAINTERFACE_INCLUDE_DIR) \
			/I$(SERVICESOPCUAINTERFACE_MODEL_DIR) /I$(SERVICESOPCUAINTERFACE_INCLUDE_DIR) \
			/I$(OPENAASOPCUAINTERFACE_MODEL_DIR) /I$(OPENAASOPCUAINTERFACE_INCLUDE_DIR) \
			/I$(FB_MODEL_DIR) /I$(FB_INCLUDE_DIR) \
			/I$(MODEL_DIR) /I$(INCLUDE_DIR)
else
INCLUDES  = -I$(BASE_INC_DIR) -I$(BASE_MODEL_DIR)\
			-I$(KSBASE_MODEL_DIR) -I$(KSBASE_INCLUDE_DIR) \
			-I$(OPCUA_MODEL_DIR) -I$(OPCUA_INCLUDE_DIR) \
			-I$(KSAPI_MODEL_DIR) -I$(KSAPI_INCLUDE_DIR) \
			-I$(IDENTIFICATION_MODEL_DIR) -I$(IDENTIFICATION_INCLUDE_DIR) \
			-I$(PROPERTYVALUESTATEMENT_MODEL_DIR) -I$(PROPERTYVALUESTATEMENT_INCLUDE_DIR) \
			-I$(LIFECYCLEENTRY_MODEL_DIR) -I$(LIFECYCLEENTRY_INCLUDE_DIR) \
			-I$(MESSAGESYS_MODEL_DIR) -I$(MESSAGESYS_INCLUDE_DIR) \
			-I$(OPENAAS_MODEL_DIR) -I$(OPENAAS_INCLUDE_DIR) \
			-I$(SERVICES_MODEL_DIR) -I$(SERVICES_INCLUDE_DIR) \
			-I$(SUBMODELADMINISTRATION_MODEL_DIR) -I$(SUBMODELADMINISTRATION_INCLUDE_DIR) \
			-I$(IDENTIFICATIONOPCUAINTERFACE_MODEL_DIR) -I$(IDENTIFICATIONOPCUAINTERFACE_INCLUDE_DIR) \
			-I$(PROPERTYVALUESTATEMENTOPCUAINTERFACE_MODEL_DIR) -I$(PROPERTYVALUESTATEMENTOPCUAINTERFACE_INCLUDE_DIR) \
			-I$(LIFECYCLEENTRYOPCUAINTERFACE_MODEL_DIR) -I$(LIFECYCLEENTRYOPCUAINTERFACE_INCLUDE_DIR) \
			-I$(SERVICESOPCUAINTERFACE_MODEL_DIR) -I$(SERVICESOPCUAINTERFACE_INCLUDE_DIR) \
			-I$(OPENAASOPCUAINTERFACE_MODEL_DIR) -I$(OPENAASOPCUAINTERFACE_INCLUDE_DIR) \
			-I$(FB_MODEL_DIR) -I$(FB_INCLUDE_DIR) \
			-I$(MODEL_DIR) -I$(INCLUDE_DIR)
endif

VPATH     = $(MODEL_DIR) $(SOURCE_DIR) $(INCLUDE_DIR) \
			$(KSBASE_MODEL_DIR) $(KSBASE_INCLUDE_DIR) \
			$(OPCUA_MODEL_DIR) $(OPCUA_INCLUDE_DIR) \
			$(KSAPI_MODEL_DIR) $(KSAPI_INCLUDE_DIR) \
			$(IDENTIFICATION_MODEL_DIR) $(IDENTIFICATION_INCLUDE_DIR) \
			$(PROPERTYVALUESTATEMENT_MODEL_DIR) $(PROPERTYVALUESTATEMENT_INCLUDE_DIR) \
			$(LIFECYCLEENTRY_MODEL_DIR) $(LIFECYCLEENTRY_INCLUDE_DIR) \
			$(MESSAGESYS_MODEL_DIR) $(MESSAGESYS_INCLUDE_DIR) \
			$(OPENAAS_MODEL_DIR) $(OPENAAS_INCLUDE_DIR) \
			$(SERVICES_MODEL_DIR) $(SERVICES_INCLUDE_DIR) \
			$(SUBMODELADMINISTRATION_MODEL_DIR) $(SUBMODELADMINISTRATION_INCLUDE_DIR) \
			$(IDENTIFICATIONOPCUAINTERFACE_MODEL_DIR) $(IDENTIFICATIONOPCUAINTERFACE_INCLUDE_DIR) \
			$(PROPERTYVALUESTATEMENTOPCUAINTERFACE_MODEL_DIR) $(PROPERTYVALUESTATEMENTOPCUAINTERFACE_INCLUDE_DIR) \
			$(LIFECYCLEENTRYOPCUAINTERFACE_MODEL_DIR) $(LIFECYCLEENTRYOPCUAINTERFACE_INCLUDE_DIR) \
			$(SERVICESOPCUAINTERFACE_MODEL_DIR) $(SERVICESOPCUAINTERFACE_INCLUDE_DIR) \
			$(OPENAASOPCUAINTERFACE_MODEL_DIR) $(OPENAASOPCUAINTERFACE_INCLUDE_DIR) \
			$(FB_MODEL_DIR) $(FB_INCLUDE_DIR) \
			$(BASE_INC_DIR) $(BASE_MODEL_DIR)

ifeq ($(COMPILER), MSVC)
DEFINES    = /DOV_SYSTEM_$(SYSTEM)=1 /DPLT_SYSTEM_$(SYSTEM)=1
else
DEFINES    = -DOV_SYSTEM_$(SYSTEM)=1 -DPLT_SYSTEM_$(SYSTEM)=1
endif

#	User library
#	------------

LIBRARY        = subModelAdministrationOPCUAInterface
USERLIB_C      = $(LIBRARY)$(_C)
USERLIB_LIB    = $(LIBRARY)$(_LIB)
USERLIB_DLL    = $(LIBRARY)$(_DLL)

#	Targets
#	-------
USERLIB_SRC = $(USERLIB_C) $(wildcard $(SOURCE_DIR)*$(_C))
USERLIB_OBJ = $(foreach source, $(USERLIB_SRC), $(basename $(notdir $(source)))$(_OBJ))

HEADERS = \
	ov.h \
	ksbase.h \
	opcua.h \
	ksapi.h \
	identification.h \
	propertyValueStatement.h \
	lifeCycleEntry.h \
	MessageSys.h \
	openaas.h \
	services.h \
	subModelAdministration.h \
	identificationOPCUAInterface.h \
	propertyValueStatementOPCUAInterface.h \
	lifeCycleEntryOPCUAInterface.h \
	servicesOPCUAInterface.h \
	openaasOPCUAInterface.h \
	fb.h \
	subModelAdministrationOPCUAInterface.h 

ifndef STATIC_ONLY
TARGETS = \
	$(HEADERS) \
	$(USERLIB_LIB) \
	$(USERLIB_DLL)
else
TARGETS = \
	$(HEADERS) \
	$(USERLIB_LIB)
endif

SOURCES = \
	ov.h \
	ksbase.h \
	opcua.h \
	ksapi.h \
	identification.h \
	propertyValueStatement.h \
	lifeCycleEntry.h \
	MessageSys.h \
	openaas.h \
	services.h \
	subModelAdministration.h \
	identificationOPCUAInterface.h \
	propertyValueStatementOPCUAInterface.h \
	lifeCycleEntryOPCUAInterface.h \
	servicesOPCUAInterface.h \
	openaasOPCUAInterface.h \
	fb.h \
	$(USERLIB_SRC)

