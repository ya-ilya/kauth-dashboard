cmake_minimum_required(VERSION 3.20)
project(kauth-dashboard)

set(CMAKE_CXX_STANDARD 17)
set(CPR_ENABLE_SSL OFF)

if (WIN32)
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
endif ()

add_executable(kauth-dashboard
        src/main.cpp src/api/models/Application.cpp
        src/api/models/ApplicationUser.cpp
        src/api/models/Application.h
        src/api/models/ApplicationUser.h
        src/api/Api.h src/api/Api.cpp)

include(FetchContent)

FetchContent_Declare(cpr GIT_REPOSITORY https://github.com/libcpr/cpr.git
        GIT_TAG f88fd7737de3e640c61703eb57a0fa0ce00c60cd) # Release 1.9.2
FetchContent_MakeAvailable(cpr)

FetchContent_Declare(json GIT_REPOSITORY https://github.com/nlohmann/json.git
        GIT_TAG bc889afb4c5bf1c0d8ee29ef35eaaf4c8bef8a5d) # Release 3.11.2
FetchContent_MakeAvailable(json)

FetchContent_Declare(libcli GIT_REPOSITORY https://github.com/ya-ilya/libcli.git
        GIT_TAG origin) # Latest Version
FetchContent_MakeAvailable(libcli)

target_link_libraries(kauth-dashboard PRIVATE cpr::cpr)
target_link_libraries(kauth-dashboard PRIVATE nlohmann_json::nlohmann_json)
target_link_libraries(kauth-dashboard PRIVATE libcli::libcli)

set(CPACK_PACKAGE_VERSION 0.1)
set(CPACK_PACKAGE_VENDOR ya-ilya)
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Dashboard for kauth")
set(CPACK_PACKAGE_DESCRIPTION "kauth-dashboard is dashboard for kauth")
set(CPACK_PACKAGE_CONTACT https://github.com/ya-ilya/kauth-dashboard/issues)

include(CPack)

if(UNIX)
    install(TARGETS ${PROJECT_NAME}
            EXPORT ${PROJECT_NAME}
            INCLUDES DESTINATION inc
            PUBLIC_HEADER DESTINATION inc
            LIBRARY DESTINATION lib)
else()
    install(TARGETS ${PROJECT_NAME}
            RUNTIME DESTINATION bin)
endif()