#option(Build_Array_tests "Build the test of the array class ? " ${Build_Triqs_General_Tools_Test})
#mark_as_advanced(Build_Array_tests)
set (Build_Array_tests ${Build_Triqs_General_Tools_Test})
if (Build_Array_tests)
add_subdirectory (C++)
add_subdirectory (C++_with_py_support)
#add_subdirectory (python)
#add_subdirectory (speed)
endif (Build_Array_tests)

