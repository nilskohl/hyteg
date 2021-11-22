/*
 * Copyright (c) 2021 Marcus Mohr.
 *
 * This file is part of HyTeG
 * (see https://i10git.cs.fau.de/hyteg/hyteg).
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

// clang-format off
#include "hyteg/forms/form_hyteg_generated/p2/p2_epsiloncc_0_0_affine_q2.hpp"
#include "hyteg/forms/form_hyteg_generated/p2/p2_epsiloncc_0_1_affine_q2.hpp"
#include "hyteg/forms/form_hyteg_generated/p2/p2_epsiloncc_0_2_affine_q2.hpp"
#include "hyteg/forms/form_hyteg_generated/p2/p2_epsiloncc_1_0_affine_q2.hpp"
#include "hyteg/forms/form_hyteg_generated/p2/p2_epsiloncc_1_1_affine_q2.hpp"
#include "hyteg/forms/form_hyteg_generated/p2/p2_epsiloncc_1_2_affine_q2.hpp"
#include "hyteg/forms/form_hyteg_generated/p2/p2_epsiloncc_2_0_affine_q2.hpp"
#include "hyteg/forms/form_hyteg_generated/p2/p2_epsiloncc_2_1_affine_q2.hpp"
#include "hyteg/forms/form_hyteg_generated/p2/p2_epsiloncc_2_2_affine_q2.hpp"

#include "hyteg/forms/form_hyteg_generated/p2/p2_epsilonvar_0_0_affine_q2.hpp"
#include "hyteg/forms/form_hyteg_generated/p2/p2_epsilonvar_0_1_affine_q2.hpp"
#include "hyteg/forms/form_hyteg_generated/p2/p2_epsilonvar_0_2_affine_q2.hpp"
#include "hyteg/forms/form_hyteg_generated/p2/p2_epsilonvar_1_0_affine_q2.hpp"
#include "hyteg/forms/form_hyteg_generated/p2/p2_epsilonvar_1_1_affine_q2.hpp"
#include "hyteg/forms/form_hyteg_generated/p2/p2_epsilonvar_1_2_affine_q2.hpp"
#include "hyteg/forms/form_hyteg_generated/p2/p2_epsilonvar_2_0_affine_q2.hpp"
#include "hyteg/forms/form_hyteg_generated/p2/p2_epsilonvar_2_1_affine_q2.hpp"
#include "hyteg/forms/form_hyteg_generated/p2/p2_epsilonvar_2_2_affine_q2.hpp"

// #include "hyteg/forms/form_hyteg_generated/p2/p2_epsiloncc_0_0_blending_q2.hpp"
// #include "hyteg/forms/form_hyteg_generated/p2/p2_epsiloncc_0_1_blending_q2.hpp"
// #include "hyteg/forms/form_hyteg_generated/p2/p2_epsiloncc_0_2_blending_q2.hpp"
// #include "hyteg/forms/form_hyteg_generated/p2/p2_epsiloncc_1_0_blending_q2.hpp"
// #include "hyteg/forms/form_hyteg_generated/p2/p2_epsiloncc_1_1_blending_q2.hpp"
// #include "hyteg/forms/form_hyteg_generated/p2/p2_epsiloncc_1_2_blending_q2.hpp"
// #include "hyteg/forms/form_hyteg_generated/p2/p2_epsiloncc_2_0_blending_q2.hpp"
// #include "hyteg/forms/form_hyteg_generated/p2/p2_epsiloncc_2_1_blending_q2.hpp"
// #include "hyteg/forms/form_hyteg_generated/p2/p2_epsiloncc_2_2_blending_q2.hpp"

#include "hyteg/forms/form_hyteg_generated/p2/p2_epsilonvar_0_0_blending_q2.hpp"
#include "hyteg/forms/form_hyteg_generated/p2/p2_epsilonvar_0_1_blending_q2.hpp"
#include "hyteg/forms/form_hyteg_generated/p2/p2_epsilonvar_0_2_blending_q2.hpp"
#include "hyteg/forms/form_hyteg_generated/p2/p2_epsilonvar_1_0_blending_q2.hpp"
#include "hyteg/forms/form_hyteg_generated/p2/p2_epsilonvar_1_1_blending_q2.hpp"
#include "hyteg/forms/form_hyteg_generated/p2/p2_epsilonvar_1_2_blending_q2.hpp"
#include "hyteg/forms/form_hyteg_generated/p2/p2_epsilonvar_2_0_blending_q2.hpp"
#include "hyteg/forms/form_hyteg_generated/p2/p2_epsilonvar_2_1_blending_q2.hpp"
#include "hyteg/forms/form_hyteg_generated/p2/p2_epsilonvar_2_2_blending_q2.hpp"

#include "hyteg/forms/form_hyteg_generated/p2/p2_epsiloncc_0_0_blending_q3.hpp"
#include "hyteg/forms/form_hyteg_generated/p2/p2_epsiloncc_0_1_blending_q3.hpp"
#include "hyteg/forms/form_hyteg_generated/p2/p2_epsiloncc_0_2_blending_q3.hpp"
#include "hyteg/forms/form_hyteg_generated/p2/p2_epsiloncc_1_0_blending_q3.hpp"
#include "hyteg/forms/form_hyteg_generated/p2/p2_epsiloncc_1_1_blending_q3.hpp"
#include "hyteg/forms/form_hyteg_generated/p2/p2_epsiloncc_1_2_blending_q3.hpp"
#include "hyteg/forms/form_hyteg_generated/p2/p2_epsiloncc_2_0_blending_q3.hpp"
#include "hyteg/forms/form_hyteg_generated/p2/p2_epsiloncc_2_1_blending_q3.hpp"
#include "hyteg/forms/form_hyteg_generated/p2/p2_epsiloncc_2_2_blending_q3.hpp"
// clang-format on
