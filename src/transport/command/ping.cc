/**
 * Copyright (C) 2013 Tadas Vilkeliskis <vilkeliskis.t@gmail.com>
 *
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
 * of the Software, and to permit persons to whom the Software is furnished to do
 * so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
#include "core/logging.h"
#include "transport/client.h"
#include "transport/response.h"
#include "transport/command/ping.h"


namespace chimp {
namespace transport {
namespace command {

Ping::Ping(chimp::transport::Client *client)
{
    client_ = client;
}

int Ping::Execute()
{
    CH_LOG_DEBUG("ping handler");
    response_.reset(new chimp::transport::response::SuccessResponse());
    client_->Write(response_);
    return 0;
}

int Ping::FromMessagePack(const msgpack_unpacked *msg)
{
    // don't do anything. Ping command is like a singleton
    return 0;
}

msgpack_sbuffer *Ping::ToMessagePack()
{
    msgpack_sbuffer* buffer = msgpack_sbuffer_new();
    msgpack_packer* pk = msgpack_packer_new(buffer, msgpack_sbuffer_write);

    msgpack_pack_array(pk, 1);
    msgpack_pack_raw(pk, 4);
    msgpack_pack_raw_body(pk, "PING", 4);

    msgpack_packer_free(pk);
    return buffer;
}


}
}
}
