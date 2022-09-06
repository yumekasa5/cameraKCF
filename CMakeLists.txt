cmake_minimum_required(VERSION 3.0)

#project name
PROJECT(kcfsample)

aux_source_directory(./src SRC_FILES)

set(EXECUTABLE_OUTPUT_PATH ../bin)

include_directories(./include)

find_package(OpenCV REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS})

#make target (filename ${SRC_FILES})
ADD_EXECUTABLE(kcf ${SRC_FILES})

#link target to libraries (file name libraries)
target_link_libraries(kcf ${OpenCV_LIBS})
