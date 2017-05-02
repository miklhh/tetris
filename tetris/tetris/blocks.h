#pragma once
#include "game.h"
#include "draw.h"


/* --------------------------------------
 * --------  Block references.  ---------
 * -------------------------------------- */
const static block block_ref_i = {
	COLOR_BLUE,					// Color.
	{ 3, 0 },					// Center.
	{ { { 1, 0, 0, 0 },			// Block structure.
		{ 1, 0, 0, 0 },
		{ 1, 0, 0, 0 },
		{ 1, 0, 0, 0 } } }
};

const static block block_ref_j = {
	COLOR_BLUE,					// Color.
	{ 2, 1 },					// Center.
	{ { { 0, 1, 0, 0 },			// Block structure.
		{ 0, 1, 0, 0 },
		{ 1, 1, 0, 0 },
		{ 0, 0, 0, 0 } } }
};

const static block block_ref_l = {
	COLOR_BLUE,					// Color.
	{ 2, 0 },					// Center.
	{ { { 1, 0, 0, 0 },			// Block structure.
		{ 1, 0, 0, 0 },
		{ 1, 1, 0, 0 },
		{ 0, 0, 0, 0 } } }
};

const static block block_ref_o = {
	COLOR_BLUE,					// Color.
	{ 0, 0 },					// Center.
	{ { { 1, 1, 0, 0 },			// Block structure.
		{ 1, 1, 0, 0 },
		{ 0, 0, 0, 0 },
		{ 0, 0, 0, 0 } } }
};

const static block block_ref_z = {
	COLOR_BLUE,					// Color.
	{ 0, 1 },					// Center.
	{ { { 1, 1, 0, 0 },			// Block structure.
		{ 0, 1, 1, 0 },
		{ 0, 0, 0, 0 },
		{ 0, 0, 0, 0 } } }
};

const static block block_ref_t = {
	COLOR_BLUE,					// Color.
	{ 1, 1 },					// Center.
	{ { { 0, 1, 0, 0 },			// Block structure.
		{ 1, 1, 1, 0 },
		{ 0, 0, 0, 0 },
		{ 0, 0, 0, 0 } } }
};

const static block block_ref_s = {
	COLOR_BLUE,					// Color.
	{ 0, 1 },					// Center.
	{ { { 0, 1, 1, 0 },			// Block structure.
		{ 1, 1, 0, 0 },
		{ 0, 0, 0, 0 },
		{ 0, 0, 0, 0 } } }
};