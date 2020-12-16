cmake_minimum_required(VERSION 3.5)

set(EOSIO_WASM_OLD_BEHAVIOR "Off")
find_package(eosio.cdt REQUIRED)
find_package(eosio REQUIRED)

include(${EOSIO_CDT_ROOT}/lib/cmake/eosio.cdt/EosioWasmToolchain.cmake)

add_contract(dbcontract dbcontract dbcontract.cpp)
add_contract(kvcontract kvcontract kvcontract.cpp)

target_include_directories(kvcontract
	PUBLIC 
	${CMAKE_SOURCE_DIR}/include
	${EOSIO_ROOT}/../libraries/fc/include
  /usr/local/include/
)

target_include_directories(dbcontract
	PUBLIC 
	${CMAKE_SOURCE_DIR}/include
	${EOSIO_ROOT}/../libraries/fc/include
  /usr/local/include/
)

set_target_properties(kvcontract
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/kvcontract"
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS OFF
)

set_target_properties(dbcontract
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/dbcontract"
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS OFF
)

#target_ricardian_directory(accounting ${CMAKE_SOURCE_DIR}/../ricardian)