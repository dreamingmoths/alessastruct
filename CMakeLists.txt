cmake_minimum_required(VERSION 3.31)

set(LLVM_LINK_COMPONENTS support)

add_clang_executable(alessastruct
    tool/Alessastruct.cpp

    lib/Debug.cpp
    lib/Reader.cpp
    lib/KaitaiSerializer.cpp
    lib/KaitaiVisitor.cpp
)

include_directories(include)

target_link_libraries(alessastruct
    PRIVATE
    clangAST
    clangASTMatchers
    clangBasic
    clangFrontend
    clangSerialization
    clangTooling
)
