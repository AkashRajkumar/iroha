add_library(tbb UNKNOWN IMPORTED)

find_path(tbb_INCLUDE_DIR tbb/tbb.h)
mark_as_advanced(tbb_INCLUDE_DIR)

find_library(tbb_LIBRARY tbb)
mark_as_advanced(tbb_LIBRARY)

find_package_handle_standard_args(tbb DEFAULT_MSG
    tbb_INCLUDE_DIR
    tbb_LIBRARY
    )


set(URL https://github.com/01org/tbb.git)
set(VERSION eb6336ad29450f2a64af5123ca1b9429ff6bc11d)
set_target_description(tbb "Concurrent queue" ${URL} ${VERSION})

iroha_get_lib_name(RLIB tbb       SHARED)
iroha_get_lib_name(DLIB tbb_debug SHARED)

if (NOT tbb_FOUND)
  set(release_lib_path ${EP_PREFIX}/src/01org_tbb/build/build_release/${RLIB})
  set(debug_lib_path   ${EP_PREFIX}/src/01org_tbb/build/build_debug/${DLIB})

  ExternalProject_Add(01org_tbb
      GIT_REPOSITORY  ${URL}
      GIT_TAG         ${VERSION}
      BUILD_IN_SOURCE 1
      BUILD_COMMAND
          $(MAKE) info && $(MAKE) tbb_build_prefix=build
      BUILD_BYPRODUCTS
          ${release_lib_path}
          ${debug_lib_path}
      CONFIGURE_COMMAND "" # remove configure step
      INSTALL_COMMAND   "" # remove install step
      TEST_COMMAND      "" # remove test step
      UPDATE_COMMAND    "" # remove update step
      )
  ExternalProject_Get_Property(01org_tbb source_dir)
  set(tbb_INCLUDE_DIR ${source_dir}/include)

  if (CMAKE_BUILD_TYPE MATCHES Debug)
    set(tbb_LIBRARY ${debug_lib_path})
  else()
    set(tbb_LIBRARY ${release_lib_path})
  endif ()

  file(MAKE_DIRECTORY ${tbb_INCLUDE_DIR})

  add_dependencies(tbb 01org_tbb)
endif ()

set_target_properties(tbb PROPERTIES
    INTERFACE_INCLUDE_DIRECTORIES ${tbb_INCLUDE_DIR}
    IMPORTED_LOCATION ${tbb_LIBRARY}
    )
