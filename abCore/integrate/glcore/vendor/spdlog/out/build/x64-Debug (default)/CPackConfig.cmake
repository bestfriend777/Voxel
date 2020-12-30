# This file will be configured to contain variables for CPack. These variables
# should be set in the CMake list file of the project before CPack module is
# included. The list of available CPACK_xxx variables and their associated
# documentation may be obtained using
#  cpack --help-variable-list
#
# Some variables are common to all generators (e.g. CPACK_PACKAGE_NAME)
# and some are specific to a generator
# (e.g. CPACK_NSIS_EXTRA_INSTALL_COMMANDS). The generator specific variables
# usually begin with CPACK_<GENNAME>_xxxx.


set(CPACK_BUILD_SOURCE_DIRS "C:/ab_dev/opengl/abCore/abCore/integrate/glcore/vendor/spdlog;C:/ab_dev/opengl/abCore/abCore/integrate/glcore/vendor/spdlog/out/build/x64-Debug (default)")
set(CPACK_CMAKE_GENERATOR "Ninja")
set(CPACK_COMPONENT_UNSPECIFIED_HIDDEN "TRUE")
set(CPACK_COMPONENT_UNSPECIFIED_REQUIRED "TRUE")
set(CPACK_DEFAULT_PACKAGE_DESCRIPTION_FILE "C:/Program Files (x86)/Microsoft Visual Studio/2019/Community/Common7/IDE/CommonExtensions/Microsoft/CMake/CMake/share/cmake-3.18/Templates/CPack.GenericDescription.txt")
set(CPACK_DEFAULT_PACKAGE_DESCRIPTION_SUMMARY "spdlog built using CMake")
set(CPACK_GENERATOR "TGZ;ZIP")
set(CPACK_INCLUDE_TOPLEVEL_DIRECTORY "0")
set(CPACK_INSTALL_CMAKE_PROJECTS "C:/ab_dev/opengl/abCore/abCore/integrate/glcore/vendor/spdlog/out/build/x64-Debug (default);spdlog;ALL;.")
set(CPACK_INSTALL_PREFIX "C:/ab_dev/opengl/abCore/abCore/integrate/glcore/vendor/spdlog/out/install/x64-Debug (default)")
set(CPACK_MODULE_PATH "")
set(CPACK_NSIS_DISPLAY_NAME "spdlog 1.5.0")
set(CPACK_NSIS_INSTALLER_ICON_CODE "")
set(CPACK_NSIS_INSTALLER_MUI_ICON_CODE "")
set(CPACK_NSIS_INSTALL_ROOT "$PROGRAMFILES64")
set(CPACK_NSIS_PACKAGE_NAME "spdlog 1.5.0")
set(CPACK_NSIS_UNINSTALL_NAME "Uninstall")
set(CPACK_OUTPUT_CONFIG_FILE "C:/ab_dev/opengl/abCore/abCore/integrate/glcore/vendor/spdlog/out/build/x64-Debug (default)/CPackConfig.cmake")
set(CPACK_PACKAGE_CONTACT "Gabi Melman <gmelman1@gmail.com>")
set(CPACK_PACKAGE_DEFAULT_LOCATION "/")
set(CPACK_PACKAGE_DESCRIPTION_FILE "C:/Program Files (x86)/Microsoft Visual Studio/2019/Community/Common7/IDE/CommonExtensions/Microsoft/CMake/CMake/share/cmake-3.18/Templates/CPack.GenericDescription.txt")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Fast C++ logging library")
set(CPACK_PACKAGE_FILE_NAME "spdlog-1.5.0-win64")
set(CPACK_PACKAGE_INSTALL_DIRECTORY "spdlog 1.5.0")
set(CPACK_PACKAGE_INSTALL_REGISTRY_KEY "spdlog 1.5.0")
set(CPACK_PACKAGE_NAME "spdlog")
set(CPACK_PACKAGE_RELOCATABLE "true")
set(CPACK_PACKAGE_VENDOR "Gabi Melman")
set(CPACK_PACKAGE_VERSION "1.5.0")
set(CPACK_PACKAGE_VERSION_MAJOR "1")
set(CPACK_PACKAGE_VERSION_MINOR "5")
set(CPACK_PACKAGE_VERSION_PATCH "0")
set(CPACK_PROJECT_URL "https://github.com/gabime/spdlog")
set(CPACK_RESOURCE_FILE_LICENSE "C:/Program Files (x86)/Microsoft Visual Studio/2019/Community/Common7/IDE/CommonExtensions/Microsoft/CMake/CMake/share/cmake-3.18/Templates/CPack.GenericLicense.txt")
set(CPACK_RESOURCE_FILE_README "C:/Program Files (x86)/Microsoft Visual Studio/2019/Community/Common7/IDE/CommonExtensions/Microsoft/CMake/CMake/share/cmake-3.18/Templates/CPack.GenericDescription.txt")
set(CPACK_RESOURCE_FILE_WELCOME "C:/Program Files (x86)/Microsoft Visual Studio/2019/Community/Common7/IDE/CommonExtensions/Microsoft/CMake/CMake/share/cmake-3.18/Templates/CPack.GenericWelcome.txt")
set(CPACK_RPM_PACKAGE_DESCRIPTION "Very fast, header-only/compiled, C++ logging library.")
set(CPACK_RPM_PACKAGE_GROUP "System Environment/Libraries")
set(CPACK_RPM_PACKAGE_LICENSE "MIT")
set(CPACK_RPM_PACKAGE_URL "https://github.com/gabime/spdlog")
set(CPACK_SET_DESTDIR "OFF")
set(CPACK_SOURCE_7Z "ON")
set(CPACK_SOURCE_GENERATOR "7Z;ZIP")
set(CPACK_SOURCE_OUTPUT_CONFIG_FILE "C:/ab_dev/opengl/abCore/abCore/integrate/glcore/vendor/spdlog/out/build/x64-Debug (default)/CPackSourceConfig.cmake")
set(CPACK_SOURCE_ZIP "ON")
set(CPACK_SYSTEM_NAME "win64")
set(CPACK_TOPLEVEL_TAG "win64")
set(CPACK_WIX_SIZEOF_VOID_P "8")

if(NOT CPACK_PROPERTIES_FILE)
  set(CPACK_PROPERTIES_FILE "C:/ab_dev/opengl/abCore/abCore/integrate/glcore/vendor/spdlog/out/build/x64-Debug (default)/CPackProperties.cmake")
endif()

if(EXISTS ${CPACK_PROPERTIES_FILE})
  include(${CPACK_PROPERTIES_FILE})
endif()
