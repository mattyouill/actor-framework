/******************************************************************************
 *                       ____    _    _____                                   *
 *                      / ___|  / \  |  ___|    C++                           *
 *                     | |     / _ \ | |_       Actor                         *
 *                     | |___ / ___ \|  _|      Framework                     *
 *                      \____/_/   \_|_|                                      *
 *                                                                            *
 * Copyright 2011-2020 Dominik Charousset                                     *
 *                                                                            *
 * Distributed under the terms and conditions of the BSD 3-Clause License or  *
 * (at your option) under the terms and conditions of the Boost Software      *
 * License 1.0. See accompanying files LICENSE and LICENSE_ALTERNATIVE.       *
 *                                                                            *
 * If you did not receive a copy of the license files, see                    *
 * http://opensource.org/licenses/BSD-3-Clause and                            *
 * http://www.boost.org/LICENSE_1_0.txt.                                      *
 ******************************************************************************/

#define CAF_SUITE type_id_list

#include "caf/type_id_list.hpp"

#include "caf/test/dsl.hpp"

#include "caf/init_global_meta_objects.hpp"

using namespace caf;

CAF_TEST(lists store the size at index 0) {
  type_id_t data[] = {3, 1, 2, 4};
  type_id_list xs{data};
  CAF_CHECK_EQUAL(xs.size(), 3u);
  CAF_CHECK_EQUAL(xs[0], 1u);
  CAF_CHECK_EQUAL(xs[1], 2u);
  CAF_CHECK_EQUAL(xs[2], 4u);
}

CAF_TEST(lists are comparable) {
  type_id_t data[] = {3, 1, 2, 4};
  type_id_list xs{data};
  type_id_t data_copy[] = {3, 1, 2, 4};
  type_id_list ys{data_copy};
  CAF_CHECK_EQUAL(xs, ys);
  data_copy[1] = 10;
  CAF_CHECK_NOT_EQUAL(xs, ys);
  CAF_CHECK_LESS(xs, ys);
}

CAF_TEST(make_type_id_list constructs a list from types) {
  auto xs = make_type_id_list<uint8_t, bool, float>();
  CAF_CHECK_EQUAL(xs.size(), 3u);
  CAF_CHECK_EQUAL(xs[0], type_id_v<uint8_t>);
  CAF_CHECK_EQUAL(xs[1], type_id_v<bool>);
  CAF_CHECK_EQUAL(xs[2], type_id_v<float>);
}

CAF_TEST(type ID lists are convertible to strings) {
  detail::clear_global_meta_objects();
  init_global_meta_objects<builtin_type_ids>();
  auto xs = make_type_id_list<uint8_t, bool, float>();
  CAF_CHECK_EQUAL(to_string(xs), "[uint8_t, bool, float]");
}
