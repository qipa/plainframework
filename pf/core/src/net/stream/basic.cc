#include "pf/sys/assert.h"
#include "pf/net/stream/basic.h"

namespace pf_net {

namespace stream {

Basic::Basic(socket::Basic *socket, 
             uint32_t bufferlength, 
             uint32_t bufferlength_max) : 
              socket_{socket},
              encrypt_isenable_{false},
              isinit_{false} {
  streamdata_.buffer = nullptr;
  streamdata_.bufferlength = bufferlength;
  streamdata_.bufferlength_max = bufferlength_max;
  compressor_.sethead(NET_STREAM_COMPRESSOR_HEADER_SIZE);
  compressor_.settail(NET_STREAM_COMPRESSOR_HEADER_SIZE);
  compressor_.setencryptor(&encryptor_);
}

Basic::~Basic() {
  safe_delete_array(streamdata_.buffer);
}

void Basic::init() {
  if (isinit()) return;
  auto buffersize = sizeof(char) * streamdata_.bufferlength;
  streamdata_.buffer = new char[buffersize];
  Assert(streamdata_.buffer);
  memset(streamdata_.buffer, 0, buffersize);
  streamdata_.head = 0;
  streamdata_.tail = 0;
  encrypt_isenable_ = false;
  receive_bytes_ = send_bytes_ = 0;
  compressor_.sethead(NET_STREAM_COMPRESSOR_HEADER_SIZE);
  compressor_.settail(NET_STREAM_COMPRESSOR_HEADER_SIZE);
  set_isinit(true);
}

bool Basic::resize(int32_t size) {
  bool result = true;
  uint32_t bufferlength = streamdata_.bufferlength;
  uint32_t head = streamdata_.head;
  uint32_t tail = streamdata_.tail;
  uint32_t _reallength = reallength();
  size = max(size, static_cast<int32_t>(bufferlength >> 1));
  uint32_t newbuffer_length = bufferlength + size;
  if (size < 0 && (newbuffer_length < 0 || newbuffer_length < _reallength))
    return false;
  char *oldbuffer = streamdata_.buffer;
  char *newbuffer = new char[sizeof(char) * newbuffer_length];
  if (!newbuffer) return false;
  memset(newbuffer, 0, sizeof(char) * newbuffer_length);
  if (head < tail) {
    memcpy(newbuffer, &oldbuffer[head], tail - head);
  } else {
    memcpy(newbuffer, &oldbuffer[head], bufferlength - head);
    memcpy(&newbuffer[bufferlength - head], oldbuffer, tail);
  }
  safe_delete_array(oldbuffer);
  streamdata_.buffer = newbuffer;
  streamdata_.bufferlength = newbuffer_length;
  streamdata_.head = 0;
  streamdata_.tail = _reallength;
  return result;
}

uint32_t Basic::reallength() const {
  uint32_t length = 0;
  uint32_t bufferlength = streamdata_.bufferlength;
  uint32_t head = streamdata_.head;
  uint32_t tail = streamdata_.tail;
  if (head <= tail) {
    length = tail - head;
  } else {
    length = bufferlength - head + tail;
  }
  return length;
}

void Basic::clear() {
  streamdata_.head = 0;
  streamdata_.tail = 0;
  receive_bytes_ = send_bytes_ = 0;
  compressor_.sethead(NET_STREAM_COMPRESSOR_HEADER_SIZE);
  compressor_.settail(NET_STREAM_COMPRESSOR_HEADER_SIZE);
}

}; //namespace stream

}; //namespace pf_net
