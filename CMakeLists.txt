cmake_minimum_required(VERSION 3.5)
project(vqaSDK_examples)


set(CMAKE_CXX_STANDARD 11)
#option(ENABLE_GPU '' OFF)


set(OpenCV_DIR "/home/charlie/vqasdk2.1/third_parties/opencv3.4.6/share/OpenCV")


include_directories(include)


message(STATUS "vqasdk binary_dir:${PROJECT_BINARY_DIR}")

link_directories(lib third_parties/opencv3.4.6/lib)
add_executable(pyvqa src/test_vqa_c.cpp)

target_link_libraries(pyvqa  vqasdk )



