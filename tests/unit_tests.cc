#include "catch2/catch_test_macros.hpp"
#include "common.h"
#include "chunk.h"
#include "debugger.h"

TEST_CASE("Bytes") {
    Chunk chunk;
    chunk.write_constant(1.2, 123);
    chunk.write_chunk(OP_RETURN, 123);
    chunk.write_constant(4.3, 155);
    chunk.write_chunk(OP_RETURN, 155);

    std::vector<Byte> expected_bytes = {
        OP_CONSTANT, 
        0,
        OP_RETURN,
        OP_CONSTANT,
        1,
        OP_RETURN
    };

    REQUIRE(chunk.code == expected_bytes);
}

