# Add the executable target
add_executable(Optional
    main.cpp)

# Add the library target (no source file needed for header-only)
add_library(Optionallib INTERFACE)

# Specify the include directory for the header file
target_include_directories(Optionallib INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

# Link the library to the executable
target_link_libraries(Optional PUBLIC Optionallib)


if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(Optional PRIVATE -fsanitize=address -g)
    target_link_libraries(Optional PRIVATE -fsanitize=address)
endif()