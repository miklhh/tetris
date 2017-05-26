#pragma once
#include "game.h"
#include "draw.h"
#include "data_structures.h"


/* --------------------------------------
 * --------  Block references.  ---------
 * -------------------------------------- */
const static block_t block_ref_i = {
    COLOR_BLUE,                 // Color.
    BLOCK_I,                    // Block type.
    { 0, 0 },                   // Center.
    { { { 0, 1, 0, 0 },         // Block structure.
        { 0, 1, 0, 0 },
        { 0, 1, 0, 0 },
        { 0, 1, 0, 0 } } }
};

const static block_t block_ref_j = {
    COLOR_BLUE,                 // Color.
    BLOCK_J,                    // Block type.
    { 0, 0 },                   // Center.
    { { { 0, 1, 0, 0 },         // Block structure.
        { 0, 1, 0, 0 },
        { 1, 1, 0, 0 },
        { 0, 0, 0, 0 } } }
};

const static block_t block_ref_l = {
    COLOR_BLUE,                 // Color.
    BLOCK_L,                    // Block type.
    { 0, 0 },                   // Center.
    { { { 0, 1, 0, 0 },         // Block structure.
        { 0, 1, 0, 0 },
        { 0, 1, 1, 0 },
        { 0, 0, 0, 0 } } }
};

const static block_t block_ref_o = {
    COLOR_BLUE,                 // Color.
    BLOCK_O,                    	// Block type.
    { 0, 0 },                   // Center.
    { { { 1, 1, 0, 0 },         // Block structure.
        { 1, 1, 0, 0 },
        { 0, 0, 0, 0 },
        { 0, 0, 0, 0 } } }
};

const static block_t block_ref_z = {
    COLOR_BLUE,                 // Color.
    BLOCK_Z,                    // Block type.
    { 0, 0 },                   // Center.
    { { { 1, 1, 0, 0 },         // Block structure.
        { 0, 1, 1, 0 },
        { 0, 0, 0, 0 },
        { 0, 0, 0, 0 } } }
};

const static block_t block_ref_t = {
    COLOR_BLUE,                 // Color.
    BLOCK_T,                    // Block type.
    { 0, 0 },                   // Center.
    { { { 0, 1, 0, 0 },         // Block structure.
        { 1, 1, 1, 0 },
        { 0, 0, 0, 0 },
        { 0, 0, 0, 0 } } }
};

const static block_t block_ref_s = {
    COLOR_BLUE,                 // Color.
    BLOCK_S,                    // Block type.
    { 0, 0 },                   // Center.
    { { { 0, 1, 1, 0 },         // Block structure.
        { 1, 1, 0, 0 },
        { 0, 0, 0, 0 },
        { 0, 0, 0, 0 } } }
};