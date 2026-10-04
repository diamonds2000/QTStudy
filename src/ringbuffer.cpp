#include "ringbuffer.h"
#include <stdexcept>

RingBuffer::RingBuffer(size_t capacity)
    : m_capacity(capacity), m_head(0), m_tail(0), m_size(0)
{
    m_buffer = new double[capacity];
}

RingBuffer::~RingBuffer()
{
    delete[] m_buffer;
}

void RingBuffer::enqueue(double value)
{
    if (isFull())
    {
        m_head = (m_head + 1) % m_capacity; // Move head forward to make space
    }
    m_buffer[m_tail] = value;
    m_tail = (m_tail + 1) % m_capacity;

    if (m_size < m_capacity)
    {
        m_size++;
    }
}

double RingBuffer::dequeue()
{
    if (isEmpty())
    {
        throw std::runtime_error("RingBuffer is empty");
    }
    double value = m_buffer[m_head];
    //m_head = (m_head + 1) % m_capacity;
    //m_size--;
    return value;
}

size_t RingBuffer::copyLast(double *buffer, size_t size) const
{
    if (size > m_size)
    {
        for (size_t i = 0; i < m_size; ++i)
        {
            buffer[i] = m_buffer[(m_head + i) % m_capacity];
        }
        return m_size;
    }
    else
    {
        for (size_t i = 0; i < size; ++i)
        {
            buffer[i] = m_buffer[(m_tail - size + i) % m_capacity];
        }
        return size;
    }
}

bool RingBuffer::isEmpty() const
{
    return m_size == 0;
}

bool RingBuffer::isFull() const
{
    return m_size == m_capacity;
}

size_t RingBuffer::size() const
{
    return m_size;
}