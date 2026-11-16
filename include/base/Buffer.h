#pragma once

#include <cstddef>
#include <vector>

namespace base {
class Buffer {
 public:
  void append(const char* data, size_t len);
  void consume(size_t leb);

  [[nodiscard]] size_t readableBytes() const { return write_index_ - read_index_; }
  [[nodiscard]] size_t writableBytes() const { return buffer_.size() - write_index_; }
  [[nodiscard]] const char* peek() const;

 private:
  void ensureWritable(size_t len);

  std::vector<char> buffer_;
  size_t read_index_ = 0;
  size_t write_index_ = 0;
};

}  // namespace base
