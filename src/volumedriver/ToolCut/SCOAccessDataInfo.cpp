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

#include <boost/python.hpp>
#include <backend-python/ConnectionInterface.h>
#include <boost/python/tuple.hpp>
#include <boost/foreach.hpp>

#include "SCOAccessDataInfo.h"

namespace toolcut
{

SCOAccessDataInfo::SCOAccessDataInfo(const fs::path& p)
    : sad_(vd::SCOAccessDataPersistor::deserialize(p))
{
}

SCOAccessDataInfo::SCOAccessDataInfo(const fs::path& dst_path,
                                     bpy::object& backend,
                                     const std::string& nspace)
    : sad_(nullptr)
{

    backend.attr("read")(nspace,
                         dst_path.string(),
                         vd::SCOAccessDataPersistor::backend_name,
                         true);
    sad_ = vd::SCOAccessDataPersistor::deserialize(dst_path);
}

std::string
SCOAccessDataInfo::getNamespace() const
{
    return sad_->getNamespace().str();
}

float
SCOAccessDataInfo::getReadActivity() const
{
    return sad_->read_activity();
}

bpy::list
SCOAccessDataInfo::getEntries() const
{
    bpy::list res;

    BOOST_FOREACH(const vd::SCOAccessData::EntryType& e, sad_->getVector())
    {
        res.append(bpy::make_tuple(e.first.str(), e.second));
    }

    return res;
}

}

// Local Variables: **
// mode: c++ **
// End: **
