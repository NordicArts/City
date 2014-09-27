SET(_valkyrie_HEADER_SEARCH_DIRS 
    ${PROJECT_SOURCE_DIR}/./Valkyrie/
    ${PROJECT_SOURCE_DIR}/../Valkyrie/
    ${PROJECT_SOURCE_DIR}/../../Valkyrie/
    ${PROJECT_SOURCE_DIR}/../../../Valkyrie/
)
SET(_valkyrie_ENV_ROOT_DIR "$ENV{VALKYRIE_ROOT_DIR}")

IF(NOT VALKYRIE_ROOT_DIR AND _valkyrie_ENV_ROOT_DIR)
    SET(VALKYRIE_ROOT_DIR "${_VALKYRIE_ENV_ROOT_DIR}")
ENDIF(NOT VALKYRIE_ROOT_DIR AND _valkyrie_ENV_ROOT_DIR)

IF(VALKYRIE_ROOT_DIR)
    SET(_valkyrie_HEADER_SEARCH_DIRS "${VALKYRIE_ROOT_DIR}" "${VALKYRIE_ROOT_DIR}/Valkyrie" ${_valkyrie_HEADER_SEARCH_DIRS})
ENDIF(VALKYRIE_ROOT_DIR)

FIND_PATH(VALKYRIE_INCLUDE_DIR Valkyrie/Valkyrie.hpp PATH_SUFFIXES Valkyrie PATHS ${_valkyrie_HEADER_SEARCH_DIRS})
IF (NOT VALKYRIE_INCLUDE_DIR)
	SET(VALKYRIE_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/Valkyrie/)
ENDIF(NOT VALKYRIE_INCLUDE_DIR)

INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(VALKYRIE DEFAULT_MSG VALKYRIE_INCLUDE_DIR)

IF (VALKYRIE_FOUND)
    SET(VALKYRIE_INCLUDE_DIRS "${VALKYRIE_INCLUDE_DIR}")
    SET(VALKYRIE_LIBRARY_DIRS "${VALKYRIE_INCLUDE_DIR}")
    SET(VALKYRIE_LIBRARY_DIR  "${VALKYRIE_LIBRARY_DIRS}")
ENDIF(VALKYRIE_FOUND)
