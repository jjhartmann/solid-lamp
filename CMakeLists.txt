cmake_minimum_required(VERSION 3.3)
project(SortableChallengeRepo)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp EResolution.cpp EResolution.h ListingObject.h ListingManufacturer.cpp ListingManufacturer.h StringMatcher.cpp StringMatcher.h)
add_executable(SortableChallengeRepo ${SOURCE_FILES})
