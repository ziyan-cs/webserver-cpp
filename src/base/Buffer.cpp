#include "base/Buffer.h"

#include <algorithm>
#include <stdexcept>

namespace base {

void Buffer::append(const char* data, std::size_t len) {
  if (len == 0)
    return;

  ensureWritable(len);
  std::copy_n(data, len, buffer_.data() + write_index_);
  write_index_ += len;
}

void Buffer::consume(std::size_t len) {
  if (len > readableBytes())
    throw std::out_of_range("Buffer::consume exceeds readable data");

  read_index_ += len;
  if (read_index_ == write_index_) {
    read_index_ = 0;
    write_index_ = 0;
  }
}

const char* Buffer::peek() const {
  return buffer_.data() + read_index_;
}

void Buffer::ensureWritable(std::size_t len) {
  if (writableBytes() >= len)
    return;

  const auto readable = readableBytes();
  if (read_index_ + writableBytes() >= len) {
    std::move(buffer_.begin() + static_cast<std::ptrdiff_t>(read_index_),
              buffer_.begin() + static_cast<std::ptrdiff_t>(write_index_), buffer_.begin());
    read_index_ = 0;
    write_index_ = readable;
  } else {
    buffer_.resize(write_index_ + len);
  }
}

}  // namespace base
