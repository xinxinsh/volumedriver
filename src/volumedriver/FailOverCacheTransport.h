// Copyright (C) 2016 iNuron NV
//
// This file is part of Open vStorage Open Source Edition (OSE),
// as available from
//
//      http://www.openvstorage.org and
//      http://www.openvstorage.com.
//
// This file is free software; you can redistribute it and/or modify it
// under the terms of the GNU Affero General Public License v3 (GNU AGPLv3)
// as published by the Free Software Foundation, in version 3 as it comes in
// the LICENSE.txt file of the Open vStorage OSE distribution.
// Open vStorage is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY of any kind.

#ifndef VD_FAILOVERCACHE_TRANSPORT_H_
#define VD_FAILOVERCACHE_TRANSPORT_H_

#include <iosfwd>

namespace volumedriver
{

enum class FailOverCacheTransport
{
    TCP,
    RSocket
};

std::ostream&
operator<<(std::ostream&,
           FailOverCacheTransport);

std::istream&
operator>>(std::istream&,
           FailOverCacheTransport&);

}

#endif // !VD_FAILOVERCACHE_TRANSPORT_H_
