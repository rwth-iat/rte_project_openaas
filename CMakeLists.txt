cmake_minimum_required(VERSION 3.12)

project(openaas C)

# Disable default build of unrequired libraries
SET(BUILD_OV_LIBRARY_cshmi OFF CACHE BOOL "")
SET(BUILD_OV_LIBRARY_UDPbind OFF CACHE BOOL "")

# Include ov core and rte_misc (for MessageSys)
add_subdirectory(rte)
add_subdirectory(rte_misc)


# Include ov helper functions and definitions
get_target_property(RTE_CMAKE_DIR ov RTE_CMAKE_DIR)
include(${RTE_CMAKE_DIR}/ov_functions.cmake)
include(${RTE_CMAKE_DIR}/ov_definitions.cmake)


# Helper
add_subdirectory(opcuaSubscription)

# Model
add_subdirectory(identification)
add_subdirectory(identificationOPCUAInterface)
add_subdirectory(lifeCycleEntry)
add_subdirectory(lifeCycleEntryOPCUAInterface)
add_subdirectory(propertyValueStatement)
add_subdirectory(propertyValueStatementOPCUAInterface)
add_subdirectory(services)
add_subdirectory(servicesOPCUAInterface)


# Discovery & openAAS
add_subdirectory(openAASDiscoveryServer)
add_subdirectory(openaas)
add_subdirectory(openAASDiscoveryServerHTTP)
add_subdirectory(AASCrawler)
add_subdirectory(Databases)
add_subdirectory(DSServices)

add_subdirectory(openaasOPCUAInterface)
add_subdirectory(openaasHTTP)
add_subdirectory(subModelAdministration)
add_subdirectory(subModelAdministrationOPCUAInterface)
#add_subdirectory(subModelDiscovery)
#add_subdirectory(subModelDiscoveryOPCUAInterface)
add_subdirectory(subModelLifeCycleEntry)
add_subdirectory(subModelLifeCycleEntryOPCUAInterface)
add_subdirectory(subModelSendMessage)
add_subdirectory(subModelSendMessageOPCUAInterface)
