//
// detail/pipe_select_interrupter.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2018 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef EGT_ASIO_DETAIL_PIPE_SELECT_INTERRUPTER_HPP
#define EGT_ASIO_DETAIL_PIPE_SELECT_INTERRUPTER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <egt/asio/detail/config.hpp>

#if !defined(EGT_ASIO_WINDOWS)
#if !defined(EGT_ASIO_WINDOWS_RUNTIME)
#if !defined(__CYGWIN__)
#if !defined(__SYMBIAN32__)
#if !defined(EGT_ASIO_HAS_EVENTFD)

#include <egt/asio/detail/push_options.hpp>

namespace egt {
namespace asio {
namespace detail {

class pipe_select_interrupter
{
public:
  // Constructor.
  EGT_ASIO_DECL pipe_select_interrupter();

  // Destructor.
  EGT_ASIO_DECL ~pipe_select_interrupter();

  // Recreate the interrupter's descriptors. Used after a fork.
  EGT_ASIO_DECL void recreate();

  // Interrupt the select call.
  EGT_ASIO_DECL void interrupt();

  // Reset the select interrupt. Returns true if the call was interrupted.
  EGT_ASIO_DECL bool reset();

  // Get the read descriptor to be passed to select.
  int read_descriptor() const
  {
    return read_descriptor_;
  }

private:
  // Open the descriptors. Throws on error.
  EGT_ASIO_DECL void open_descriptors();

  // Close the descriptors.
  EGT_ASIO_DECL void close_descriptors();

  // The read end of a connection used to interrupt the select call. This file
  // descriptor is passed to select such that when it is time to stop, a single
  // byte will be written on the other end of the connection and this
  // descriptor will become readable.
  int read_descriptor_;

  // The write end of a connection used to interrupt the select call. A single
  // byte may be written to this to wake up the select which is waiting for the
  // other end to become readable.
  int write_descriptor_;
};

} // namespace detail
} // namespace asio
} // namespace egt

#include <egt/asio/detail/pop_options.hpp>

#if defined(EGT_ASIO_HEADER_ONLY)
# include <egt/asio/detail/impl/pipe_select_interrupter.ipp>
#endif // defined(EGT_ASIO_HEADER_ONLY)

#endif // !defined(EGT_ASIO_HAS_EVENTFD)
#endif // !defined(__SYMBIAN32__)
#endif // !defined(__CYGWIN__)
#endif // !defined(EGT_ASIO_WINDOWS_RUNTIME)
#endif // !defined(EGT_ASIO_WINDOWS)

#endif // EGT_ASIO_DETAIL_PIPE_SELECT_INTERRUPTER_HPP
