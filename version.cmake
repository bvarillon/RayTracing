find_package(Git REQUIRED)

execute_process(COMMAND ${GIT_EXECUTABLE} log --pretty=format:'%h' -n1
                OUTPUT_VARIABLE GIT_REV
                ERROR_QUIET)

execute_process(COMMAND ${GIT_EXECUTABLE} describe --tags --always
        OUTPUT_VARIABLE GIT_DESCRIBE
        ERROR_QUIET)

execute_process(
        COMMAND bash -c "${GIT_EXECUTABLE} diff --quiet --exit-code || echo +"
        OUTPUT_VARIABLE GIT_DIFF)
execute_process(
        COMMAND git describe --exact-match --tags
        OUTPUT_VARIABLE GIT_TAG ERROR_QUIET)
execute_process(
        COMMAND git rev-parse --abbrev-ref HEAD
        OUTPUT_VARIABLE GIT_BRANCH)

string(STRIP "${GIT_REV}" GIT_REV)
string(SUBSTRING "${GIT_REV}" 1 7 GIT_REV)
string(STRIP "${GIT_DESCRIBE}" GIT_DESCRIBE)
string(STRIP "${GIT_DIFF}" GIT_DIFF)
string(STRIP "${GIT_TAG}" GIT_TAG)
string(STRIP "${GIT_BRANCH}" GIT_BRANCH)

set(VERSION "#define GIT_REV \"${GIT_REV}${GIT_DIFF}\"
#define GIT_DESCRIBE \"${GIT_DESCRIBE}${GIT_DIFF}\"
#define GIT_TAG \"${GIT_TAG}\"
#define GIT_BRANCH \"${GIT_BRANCH}\"")

if(EXISTS ${CMAKE_BINARY_DIR}/version.h)
    file(READ version.h VERSION_)
    message("${CMAKE_BINARY_DIR}/version.h exists")
else()
    set(VERSION_ "")
    message("${CMAKE_BINARY_DIR}/version.h doesn't exists")
endif()

if (NOT "${VERSION}" STREQUAL "${VERSION_}")
    file(WRITE ${CMAKE_BINARY_DIR}/version.h "${VERSION}")
    message("new version detected")
endif()