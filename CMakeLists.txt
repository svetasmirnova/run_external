CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
# Avoid warnings in higher versions
if("${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION}" GREATER 2.6)
 CMAKE_POLICY(VERSION 2.8)
endif()

project(run_external)

# Path for MySQL include directory
SET(MYSQL_DIR_NAME_DOCSTRING "Path to MySQL directory")
IF(DEFINED MYSQL_DIR)
  SET(MYSQL_DIR ${MYSQL_DIR} CACHE STRING ${MYSQL_DIR_NAME_DOCSTRING} FORCE)
ELSE()
  MESSAGE(WARNING "${MYSQL_DIR_NAME_DOCSTRING} was not specified. If something goes wrong re-reun with option -DMYSQL_DIR")  
ENDIF()

INCLUDE_DIRECTORIES("${MYSQL_DIR}/include")

ADD_DEFINITIONS("-DMYSQL_DYNAMIC_PLUGIN")
ADD_DEFINITIONS("-rdynamic")
ADD_DEFINITIONS("-fPIC")

ADD_LIBRARY(run_external MODULE run_external_udf.cc run_external_udf.def)
IF(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
TARGET_LINK_LIBRARIES(run_external wsock32)
ELSE()
TARGET_LINK_LIBRARIES(run_external)
ENDIF()
