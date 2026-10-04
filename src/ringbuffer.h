#ifndef RINGBUFFER_H
#define RINGBUFFER_H

#include <cstddef>

class RingBuffer 
{
public:
    RingBuffer(size_t capacity);
    ~RingBuffer();

    void enqueue(double value);
    double dequeue();
    size_t copyLast(double *buffer, size_t size) const;
    bool isEmpty() const;
    bool isFull() const;
    size_t size() const;

private:
    double* m_buffer;
    size_t m_capacity;
    size_t m_head;
    size_t m_tail;
    size_t m_size;
};   

#endif // RINGBUFFER_H