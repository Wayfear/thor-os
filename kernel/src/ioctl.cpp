//=======================================================================
// Copyright Baptiste Wicht 2013-2016.
// Distributed under the terms of the MIT License.
// (See accompanying file LICENSE or copy at
//  http://www.opensource.org/licenses/MIT)
//=======================================================================

#include <tlib/errors.hpp>

#include "ioctl.hpp"
#include "scheduler.hpp"
#include "logging.hpp"
#include "fs/devfs.hpp"

int64_t ioctl(size_t device_fd, io::ioctl_request request, void* data){
    if(!scheduler::has_handle(device_fd)){
        return -std::ERROR_INVALID_FILE_DESCRIPTOR;
    }

    auto& device = scheduler::get_handle(device_fd);

    if(request == io::ioctl_request::GET_BLK_SIZE){
        return devfs::get_device_size(device, *reinterpret_cast<size_t*>(data));
    }

    return std::ERROR_INVALID_REQUEST;
}
