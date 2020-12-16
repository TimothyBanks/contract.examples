# cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_FRAMEWORK_PATH=/Users/timothy.banks/Work/issues/develop/eos/release -DCMAKE_FRAMEWORK_PATH=/Users/timothy.banks/Work/issues/develop/eosio.cdt/release -DEOSIO_ROOT=/Users/timothy.banks/Work/issues/develop/eos/release -DEOSIO_CDT_ROOT=/Users/timothy.banks/Work/issues/develop/eosio.cdt/release ..

project(contract.examples)

cmake_minimum_required(VERSION 3.5)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(ExternalProject)

set(EOSIO_WASM_OLD_BEHAVIOR "Off")
find_package(eosio.cdt REQUIRED)
find_package(eosio REQUIRED)

add_subdirectory(contracts)