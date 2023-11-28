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

add_executable(ch4-5-avList ch4-list/_05AvailableList.cpp)
add_executable(ch4-h1-avHomework ch4-list/_home_01workAv.cpp)
add_executable(ch4-4-CircleIter ch4-list/_04CircleIter.cpp)
add_executable(ch4-h2-DoubleCircle ch4-list/_home_02DoubleCircleIter.cpp)

add_executable(ch4-h3-PolyList ch4-list/_home_03PolyList.cpp)
add_executable(ch4-h3-1Single ch4-list/_home_03_01singlePoly.cpp)
add_executable(ch4-h3-2CircleHead ch4-list/_home_03_02CircleHead.cpp)

add_executable(ch5-h1-trededTree ch5-tree/ch5_h1_treded.cpp)
add_executable(ch5-h2-rank ch5-tree/ch5-h2-rankTree.cpp)
