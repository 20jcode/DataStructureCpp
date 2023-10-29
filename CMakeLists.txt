cmake_minimum_required(VERSION 3.26)
project(DataStructureCpp)

set(CMAKE_C_FLAGS "-fexec-charset=CP949")

set(CMAKE_CXX_STANDARD 17)

add_executable(ch1 ch1-CppStudy/useCpp.cpp)

add_executable(useOperatorTemplate ch1-CppStudy/useOperatorTemplate.cpp)
add_executable(useOperator3types ch1-CppStudy/useOperator1.cpp)

add_executable(queen8 ch3-Stack/queen8.cpp)


add_executable(ch4-1-intList ch4-list/_01IntList.cpp)
add_executable(ch4-2-objList ch4-list/_02ObjList.cpp)
add_executable(ch4-3-03objIter ch4-list/_03ObjIter.cpp)

add_executable(work5List ch4-list/availableList.cpp)
add_executable(avHomework ch4-list/homeworkAv.cpp)
add_executable(ch4-4-CircleIter ch4-list/_04CircleIter.cpp)
add_executable(_ch4-h2-DoubleCircle ch4-list/_home2DoubleCircleIter.cpp)
