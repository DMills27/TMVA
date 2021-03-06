############################################################################
# CMakeLists.txt file for building ROOT core/utils package
############################################################################
ROOT_USE_PACKAGE(cint/cint)
ROOT_USE_PACKAGE(core/metautils)


#---rootcint executable------------------------------------------------------
ROOT_EXECUTABLE(rootcint rootcint.cxx RStl.cxx
                         ${METAUTILS_CXX_SOURCES} 
                         ${CMAKE_SOURCE_DIR}/core/clib/src/strlcpy.c 
                         ${CMAKE_SOURCE_DIR}/core/clib/src/strlcat.c 
                         LIBRARIES Cint)
add_dependencies(rootcint IOSENUM_H)

#---rootcint_tmp executable--------------------------------------------------
add_custom_command(OUTPUT rootcint_tmp.cxx RStl_tmp.cxx loadfile_tmp.cxx
                   COMMAND cmake -E copy_if_different ${CMAKE_CURRENT_SOURCE_DIR}/src/rootcint.cxx rootcint_tmp.cxx
                   COMMAND cmake -E copy_if_different ${CMAKE_CURRENT_SOURCE_DIR}/src/RStl.cxx RStl_tmp.cxx
                   COMMAND cmake -E copy_if_different ${CMAKE_SOURCE_DIR}/cint/cint/src/loadfile.cxx loadfile_tmp.cxx
                                  DEPENDS ${CMAKE_SOURCE_DIR}/cint/cint/src/loadfile.cxx
                                          ${CMAKE_CURRENT_SOURCE_DIR}/src/RStl.cxx
                                          ${CMAKE_CURRENT_SOURCE_DIR}/src/rootcint.cxx)

if(MACOSX_TMPNAM_DEPRECATED)
  add_definitions(-Wno-deprecated-declarations)
endif()

set_source_files_properties(loadfile_tmp.cxx rootcint_tmp.cxx RStl_tmp.cxx PROPERTIES COMPILE_FLAGS 
                            "-I${CMAKE_SOURCE_DIR}/core/utils/src -I${CMAKE_SOURCE_DIR}/cint/cint/src ${CINT_CXX_DEFINITIONS} -DG__HAVE_CONFIG -DG__NOMAKEINFO -DG__CINTBODY -UR__HAVE_CONFIG -DROOTBUILD")
ROOT_EXECUTABLE(rootcint_tmp  rootcint_tmp.cxx RStl_tmp.cxx loadfile_tmp.cxx
                              ${METAUTILS_CXX_SOURCES}
                              ${CMAKE_SOURCE_DIR}/core/clib/src/strlcpy.c 
                              ${CMAKE_SOURCE_DIR}/core/clib/src/strlcat.c 
                              LIBRARIES Cint_static ${CMAKE_DL_LIBS} NOINSTALL)
add_dependencies(rootcint_tmp IOSENUM_H)

#---Trick to avoid building all dictionaties when CINT is changed-------------
add_custom_target(ROOTCINTTARGET DEPENDS rootcint rootcint_tmp)

#---rlibmap executable--------------------------------------------------------
ROOT_EXECUTABLE(rlibmap rlibmap.cxx LIBRARIES ${CMAKE_THREAD_LIBS_INIT})

