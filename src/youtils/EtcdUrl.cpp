// Copyright 2016 iNuron NV
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "Assert.h"
#include "EtcdUrl.h"

#include <iostream>

#include <boost/lexical_cast.hpp>
#include <boost/regex.hpp>

namespace youtils
{

using namespace std::literals::string_literals;

namespace
{
const std::string proto("etcd");
}

const uint16_t EtcdUrl::default_port = 2379;

std::ostream&
operator<<(std::ostream& os,
           const EtcdUrl& url)
{
    os << proto <<
        "://" << url.host <<
        ":" << url.port;
    if (not url.key.empty())
    {
        os << url.key;
    }

    return os;
}

std::istream&
operator>>(std::istream& is,
           EtcdUrl& url)
{
    std::string str;
    is >> str;
    boost::regex rex("("s + proto + ")://([^/ :]+):?([^/ ]*)(/?[^ #?]*)"s);

    boost::smatch match;
    if (boost::regex_match(str,
                           match,
                           rex))
    {
        ASSERT(proto == match[1]);

        url.host = match[2];

        if (not match[3].str().empty())
        {
            url.port = boost::lexical_cast<uint16_t>(match[3]);
        }

        if (not match[4].str().empty())
        {
            url.key = match[4];
        }
        else
        {
            url.key = "/"s;
        }
    }
    else
    {
        is.setstate(std::ios::failbit);
    }

    return is;
}

}