﻿cmake_minimum_required (VERSION 3.8)
project (libraryManagementSystem)

set(SOURCE_FILES
	main.cpp
	MenuManager.cpp
	AccountManager.cpp
	User.cpp
	Staff.cpp
	BookManager.cpp
	sha256.cpp
	BookSearch.cpp
	BookInfo.cpp
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable (${PROJECT_NAME} ${SOURCE_FILES})

add_subdirectory(deps/libpqxx pqxx-build)

target_link_libraries(${PROJECT_NAME} PRIVATE pqxx)