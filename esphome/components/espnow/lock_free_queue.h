// dummy version of the ESP32 lock_free_queue for ESP8266
// it ignores the need for atomic operations and does not activate tasks

#pragma once

#ifdef USE_ESP8266

namespace esphome {

// Base lock-free queue without task notification
template<class T, uint8_t SIZE> class LockFreeQueue {
 public:
  LockFreeQueue() : dropped_count_(0), head_(0), tail_(0) {}

  bool push(T *element) {
    bool was_empty;
    uint8_t old_tail;
    return push_internal_(element, was_empty, old_tail);
  }

 protected:
  // Internal push that reports queue state - for use by derived classes
  bool push_internal_(T *element, bool &was_empty, uint8_t &old_tail) {
    if (element == nullptr)
      return false;

    uint8_t current_tail = tail_;
    uint8_t next_tail = (current_tail + 1) % SIZE;

    // Read head before incrementing tail
    uint8_t head_before = head_;

    if (next_tail == head_before) {
      // Buffer full
      dropped_count_++;
      return false;
    }

    was_empty = (current_tail == head_before);
    old_tail = current_tail;

    buffer_[current_tail] = element;
    tail_ = next_tail;

    return true;
  }

 public:
  T *pop() {
    uint8_t current_head = head_;
    if (current_head == tail_) {
      return nullptr;  // Empty
    }

    T *element = buffer_[current_head];
    head_ = (current_head + 1) % SIZE;
    return element;
  }

  size_t size() const { return (tail_ - head_ + SIZE) % SIZE; }
  uint16_t get_and_reset_dropped_count() {
    uint16_t dropped_count = dropped_count_;
    dropped_count_ = 0;
    return dropped_count;
  }

  void increment_dropped_count() { dropped_count_++; }

  bool empty() const { return head_ == tail_; }

  bool full() const {
    uint8_t next_tail = (tail_ + 1) % SIZE;
    return next_tail == head_;
  }

 protected:
  T *buffer_[SIZE];
  uint16_t dropped_count_;  // 65535 max - more than enough for drop tracking
  uint8_t head_;
  uint8_t tail_;
};

// Extended queue with task notification support
template<class T, uint8_t SIZE> class NotifyingLockFreeQueue : public LockFreeQueue<T, SIZE> {
 public:
  NotifyingLockFreeQueue() : LockFreeQueue<T, SIZE>(), task_to_notify_(nullptr) {}

  bool push(T *element) {
    bool was_empty;
    uint8_t old_tail;
    bool result = this->push_internal_(element, was_empty, old_tail);

    return result;
  }

  void set_task_to_notify(void *task) { task_to_notify_ = task; }

 private:
  void *task_to_notify_;
};

}  // namespace esphome

#endif  // USE_ESP8266
