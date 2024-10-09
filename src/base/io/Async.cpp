/* XMRig
 * Copyright (c) 2015-2020 libuv project contributors.
 * Copyright (c) 2020      cohcho      <https://github.com/cohcho>
 * Copyright (c) 2018-2020 SChernykh   <https://github.com/SChernykh>
 * Copyright (c) 2016-2020 XMRig       <https://github.com/mlinference>, <support@mlinference.com>
 *
 *   This program is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include "base/io/Async.h"
#include "base/kernel/interfaces/IAsyncListener.h"
#include "base/tools/Handle.h"
#include "base/io/log/custom_uv_wrappers.h" // Include custom_uv_wrappers.h

// since 2019.05.16, Version 1.29.0 (Stable) https://github.com/mlinference/mlinference/pull/1889
#if (UV_VERSION_MAJOR >= 1) && (UV_VERSION_MINOR >= 29) && defined(__linux__)
#include <sys/eventfd.h>
#include <sys/poll.h>
#include <unistd.h>
#include <cstdlib>


namespace mlinference {


struct uv_async_t: uv_poll_t
{
    using uv_async_cb = void (*)(uv_async_t *);
    ~uv_async_t();
    int m_fd = -1;
    uv_async_cb m_cb = nullptr;
};


using uv_async_cb = uv_async_t::uv_async_cb;


uv_async_t::~uv_async_t()
{
    close(m_fd);
}


static void on_schedule(uv_poll_t *handle, int, int)
{
    static uint64_t val;
    auto async = reinterpret_cast<uv_async_t *>(handle);
    for (;;) {
        int r = read(async->m_fd, &val, sizeof(val));

        if (r == sizeof(val))
            continue;

        if (r != -1)
            break;

        if (errno == EAGAIN || errno == EWOULDBLOCK)
            break;

        if (errno == EINTR)
            continue;

        abort();
    }
    if (async->m_cb) {
        (*async->m_cb)(async);
    }
}


static int uv_async_init(uv_loop_t *loop, uv_async_t *async, uv_async_cb cb)
{
    int fd = eventfd(0, EFD_CLOEXEC | EFD_NONBLOCK);
    if (fd < 0) {
        return uv_translate_sys_error(errno);  // Use uv_translate_sys_error instead of custom_uv_translate_sys_error
    }
    uv_poll_init(loop, (uv_poll_t *)async, fd);  // Use uv_poll_init instead of custom_uv_poll_init
    uv_poll_start((uv_poll_t *)async, POLLIN, on_schedule);  // Use uv_poll_start instead of custom_uv_poll_start
    async->m_cb = cb;
    async->m_fd = fd;
    return 0;
}


static int uv_async_send(uv_async_t *async)
{
    static const uint64_t val = 1;
    int r;
    do {
        r = write(async->m_fd, &val, sizeof(val));
    }
    while (r == -1 && errno == EINTR);
    if (r == sizeof(val) || (r == 1 && (errno == EAGAIN || errno == EWOULDBLOCK))) {
        return 0;
    }
    abort();
}



} // namespace mlinference
#endif


namespace mlinference {


class AsyncPrivate
{
public:
    Async::Callback callback;
    IAsyncListener *listener    = nullptr;
    uv_async_t *async           = nullptr;
};


} // namespace mlinference


mlinference::Async::Async(Callback callback) : d_ptr(new AsyncPrivate())
{
    d_ptr->callback     = std::move(callback);
    d_ptr->async        = new uv_async_t;
    d_ptr->async->data  = this;

    uv_async_init(uv_default_loop(), d_ptr->async, [](uv_async_t *handle) { static_cast<Async *>(handle->data)->d_ptr->callback(); });  // Use uv_async_init
}


mlinference::Async::Async(IAsyncListener *listener) : d_ptr(new AsyncPrivate())
{
    d_ptr->listener     = listener;
    d_ptr->async        = new uv_async_t;
    d_ptr->async->data  = this;

    uv_async_init(uv_default_loop(), d_ptr->async, [](uv_async_t *handle) { static_cast<Async *>(handle->data)->d_ptr->listener->onAsync(); });  // Use uv_async_init
}


mlinference::Async::~Async()
{
    custom_uv_close(reinterpret_cast<uv_handle_t*>(d_ptr->async), nullptr);  // Use custom_uv_close with proper cast

    delete d_ptr;
}


void mlinference::Async::send()
{
    uv_async_send(d_ptr->async);  // Use uv_async_send instead of custom_uv_async_send
}