#ifndef TEST_TAPE_H_
#define TEST_TAPE_H_

namespace ReverseAD {

template<typename T>
class TestTape{
 public:
  TestTape(T val);
  T getVal();
 private:
  T val;
};

template <typename T>
TestTape<T>::TestTape(T val) {
  this->val = val;
}

template <typename T>
T TestTape<T>::getVal() {
  return val;
}

} // namespace ReverseAD

#endif // TEST_TAPE_H_
