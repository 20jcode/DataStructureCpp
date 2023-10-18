cmake_minimum_required(VERSION 3.26)
project(DataStructureCpp)

set(CMAKE_C_FLAGS "-fexec-charset=CP949")

set(CMAKE_CXX_STANDARD 17)

add_executable(DataStructureCpp main.cpp)

add_executable(ch1 ch1-CppStudy/useCpp.cpp)

add_executable(useOperatorTemplate ch1-CppStudy/useOperatorTemplate.cpp)

add_executable(queen8 ch3-Stack/queen8.cpp)

add_executable(useOperator3types ch1-CppStudy/useOperator1.cpp)
add_executable(work5List ch4-list/availableList.cpp)
add_executable(intList ch4-list/_01IntList.cpp)
add_executable(objList ch4-list/_02ObjList.cpp)
