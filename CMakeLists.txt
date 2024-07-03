cmake_minimum_required (VERSION 3.8)
project (libraryManagementSystem)

set(SOURCE_FILES
	main.cpp
	MenuManager.cpp
	EntryManager.cpp
	User.cpp
	Staff.cpp
	BookManager.cpp
)

# Set the minimum required C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add executable target for project
add_executable (${PROJECT_NAME} ${SOURCE_FILES})

# Add subdirectory for libpqxx
add_subdirectory(debs/lipqxx build-pqxx)

# Links project with libpqxx submodule
target_link_libraries(${PROJECT_NAME} PRIVATE pqxx)