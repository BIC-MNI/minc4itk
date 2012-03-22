IF(itk-module)

itk_module_test()

set(ITKIOMINCTests
  itkMINCImageIOTest.cxx
)

CreateTestDriver(ITKIOMINC  "${ITKIOMINC-Test_LIBRARIES}" "${ITKIOMINCTests}")

itk_add_test(NAME itkMINCImageIOTest
  COMMAND ITKIOMINCTestDriver itkMINCImageIOTest ${ITK_TEST_OUTPUT_DIR} )

ENDIF(itk-module)
