
#ifndef BC_CIRCULAR_BUFFER
#define BC_CIRCULAR_BUFFER 1

/**
 * The CircularBuffer class implements a basic https://en.wikipedia.org/wiki/Circular_buffer that only supports
 * inserting and calculating statistics.
 * 
 * The aggregation methods (getSum and getAverage) take an optional template type that will be used for
 * aggregation purposes and could for example be used to get a decimal average from a buffer of ints.
 * 
 */
template<typename NumType, int Capacity>
class CircularBuffer {
  NumType array_buffer[Capacity];
  int max_fill;
  int pointer;

public:
  explicit CircularBuffer() : max_fill(0), pointer(0) {
    for (int i = 0; i < Capacity; i++) {
       array_buffer[i] = 0;
    }
  }

  void push(NumType value) {
    array_buffer[pointer++] = value;
    max_fill = max(max_fill, pointer);
    pointer %= Capacity;
  }

  template<typename ResultType = NumType>
  ResultType getAverage() {
    ResultType acc = 0;
    for (int i = 0; i < max_fill; i++) {
      acc += (ResultType) array_buffer[i];
    }
    return acc / (ResultType) max_fill;
  }

  template<typename ResultType = NumType>
  ResultType getSum() {
    ResultType acc = 0;
    for (int i = 0; i < max_fill; i++) {
      acc += (ResultType) array_buffer[i];
    }
    return acc;
  }

  int getSize() {
    return max_fill;
  }

  
};


#endif

