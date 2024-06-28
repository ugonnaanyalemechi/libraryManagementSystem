cmake_minimum_required (VERSION 3.8)
project ("libraryManagementSystem")

set(SOURCE_FILES
	main.cpp
	MenuManager.cpp
	EntryManager.cpp
	User.cpp
	Staff.cpp
	BookManager.cpp
)

add_executable (${PROJECT_NAME} ${SOURCE_FILES})