/******************************************************************************
 *                       ____    _    _____                                   *
 *                      / ___|  / \  |  ___|    C++                           *
 *                     | |     / _ \ | |_       Actor                         *
 *                     | |___ / ___ \|  _|      Framework                     *
 *                      \____/_/   \_|_|                                      *
 *                                                                            *
 * Copyright 2011-2018 Dominik Charousset                                     *
 *                                                                            *
 * Distributed under the terms and conditions of the BSD 3-Clause License or  *
 * (at your option) under the terms and conditions of the Boost Software      *
 * License 1.0. See accompanying files LICENSE and LICENSE_ALTERNATIVE.       *
 *                                                                            *
 * If you did not receive a copy of the license files, see                    *
 * http://opensource.org/licenses/BSD-3-Clause and                            *
 * http://www.boost.org/LICENSE_1_0.txt.                                      *
 ******************************************************************************/

#pragma once

#include <string>

#include "caf/detail/core_export.hpp"
#include "caf/detail/type_list.hpp"
#include "caf/fwd.hpp"

namespace caf::detail {

template <class In, class Out>
struct replies_to_helper;

template <class... In, class Out>
struct replies_to_helper<type_list<In...>, type_list<Out>> {
  using type = Out(In...);
};

template <class... In, class Out0, class Out1, class... Outs>
struct replies_to_helper<type_list<In...>, type_list<Out0, Out1, Outs...>> {
  using type = result<Out0, Out1, Outs...>(In...);
};

} // namespace caf::detail

namespace caf {

/// @private
CAF_CORE_EXPORT std::string
replies_to_type_name(size_t input_size, const std::string* input,
                     size_t output_size, const std::string* output);

template <class... Is>
struct replies_to {
  template <class... Os>
  using with =
    typename detail::replies_to_helper<detail::type_list<Is...>,
                                       detail::type_list<Os...>>::type;
};

template <class... Is>
using reacts_to = void(Is...);

} // namespace caf
