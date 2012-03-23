# #IF(itk-module)
# 
# itk_module_test()
# 
# set(ITKIOMINCTests
#   itkMINCImageIOTest.cxx
# )
# 
# INCLUDE_DIRECTORIES(../minc4itk ../ezminc ../libsrc ../libsrc2 )
# 
# CreateTestDriver(ITKIOMINC  "${ITKIOMINC-Test_LIBRARIES};${NETCDF_LIBRARY}" "${ITKIOMINCTests}")
# 
# itk_add_test(NAME itkMINCImageIOTest
#   COMMAND ITKIOMINCTestDriver itkMINCImageIOTest ${ITK_TEST_OUTPUT_DIR} )
# 
# #ENDIF(itk-module)
