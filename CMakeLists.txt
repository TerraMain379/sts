cmake_minimum_required(VERSION 3.10)
project(YourProjectName)

# Только для индексации - не влияет на вашу сборку
include_directories(
        src
        src/sts
        src/sts/metaparser
        src/sts/contentparser
        src/collections
        src/strings
        src/errors
        src/collections/gmaps
        src/collections/gmap
)

# Укажите исходные файлы для индексации
file(GLOB_RECURSE SOURCE_FILES
        "src/*.c"
        "src/*.h"
)
add_executable(dummy_indexing_target ${SOURCE_FILES})