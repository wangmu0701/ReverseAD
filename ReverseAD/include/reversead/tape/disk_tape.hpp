#ifndef REVERSEAD_DISK_TAPE_H_
#define REVERSEAD_DISK_TAPE_H_

#include <iostream>
#include <fstream>
#include <string>
#include <sys/stat.h>

#define DISK_TAPE_BUFF_SIZE 2000

namespace ReverseAD {

extern int _disk_tape_id;
extern int rank;

template <typename T>
class DiskTape : public AbstractTape<T> {
 public:
  DiskTape();
  ~DiskTape();
  
  void init_taping();
  void put(T);
  void end_taping();
  int size() const;
  
  void init_forward();
  void end_forward();
  bool has_next_f();
  T get_next_f();

  void init_reverse();
  void end_reverse();
  bool has_next_r();
  T get_next_r();

  void dump_tape() const;
 private:
  void read_forward_buff();
  void read_reverse_buff();

  char* _buff_raw_memory;
  T* _buff_tp;
  int _buff_size;
  int _buff_pos;

  int _tape_id;
  int _size;
  int _curr_pos;

  std::string _tape_name;
  std::fstream fs;
};
template <typename T>
DiskTape<T>::DiskTape() {
  _tape_id = _disk_tape_id++;
  _tape_name = "./Reverse_Tape_" + std::to_string(rank)
             + "_" + std::to_string(_tape_id) + ".tap";
  _buff_raw_memory = (char*)::operator new[](sizeof(T) * DISK_TAPE_BUFF_SIZE);
  _buff_tp = (T*)_buff_raw_memory;
  _buff_size = 0;
  _buff_pos = 0;
}

template <typename T>
DiskTape<T>::~DiskTape() {
  ::operator delete[](_buff_raw_memory);
  struct stat stat_buffer;
  if (stat(_tape_name.c_str(), &stat_buffer) == 0) {
    if (std::remove(_tape_name.c_str()) != 0) {
      std::cerr << "Fail to remove taping file : " << _tape_name << std::endl;
    }
  }
}

template <typename T>
void DiskTape<T>::init_taping() {
  fs.open(_tape_name,
          std::fstream::out|std::fstream::trunc|std::fstream::binary);
  if (!fs) {
    std::cerr << "Fail to open taping file : " << _tape_name << std::endl;
  }
  _size = 0;
  _buff_size = DISK_TAPE_BUFF_SIZE;
  _buff_pos = 0;
}

template <typename T>
void DiskTape<T>::end_taping() {
  if (_buff_pos != 0) {
    fs.write(_buff_raw_memory, sizeof(T) * _buff_pos);
  }
  if (fs.is_open()) {
    fs.close();
  }
}
template <typename T>
int DiskTape<T>::size() const {
  return _size;
}

template <typename T>
void DiskTape<T>::put(T val) {
  _buff_tp[_buff_pos] = val;
  _buff_pos++;
  _size++;
  if (_buff_pos == _buff_size) {
    fs.write(_buff_raw_memory, sizeof(T) * _buff_size);
    _buff_pos = 0;
  }
}

template <typename T>
void DiskTape<T>::init_forward() {
  if (fs.is_open()) {
    std::cerr << "File still opening!" << std::endl;
    return;
  }
  fs.open(_tape_name, std::fstream::in|std::fstream::binary); 
  _curr_pos = 0;
  read_forward_buff();
}

template <typename T>
void DiskTape<T>::end_forward() {
  fs.close();
}

template <typename T>
bool DiskTape<T>::has_next_f() {
  return (_buff_pos != _buff_size) || (_curr_pos != _size);
}

template <typename T>
T DiskTape<T>::get_next_f() {
  if (_buff_pos == _buff_size) {
    if (_curr_pos != _size) {
      read_forward_buff();
    } else {
      std::cerr << "Reaches forward end!" << std::endl;
      return T();
    }
  }
  return _buff_tp[_buff_pos++];
}

template <typename T>
void DiskTape<T>::init_reverse() {
  if (fs.is_open()) {
    std::cerr << "File still opening!" << std::endl;
    return;
  }
  fs.open(_tape_name, std::fstream::in|std::fstream::binary); 
  _curr_pos = _size;
  read_reverse_buff();
}
template <typename T>
void DiskTape<T>::end_reverse() {
  fs.close();
}

template <typename T>
bool DiskTape<T>::has_next_r() {
  return (_buff_pos != 0) || (_curr_pos != 0);
}

template <typename T>
T DiskTape<T>::get_next_r() {
  if (_buff_pos == 0) {
    if (_curr_pos > 0) {
      read_reverse_buff();
    } else {
      std::cerr << "Reaches reverse ends!" << std::endl;
      return T();
    }
  }
  _buff_pos--;
  return _buff_tp[_buff_pos];
}

template <typename T>
void DiskTape<T>::read_forward_buff() {
  if (_size - _curr_pos <= DISK_TAPE_BUFF_SIZE) {
    _buff_size = _size - _curr_pos;
  } else {
    _buff_size = DISK_TAPE_BUFF_SIZE;
  }
  _curr_pos += _buff_size;
  fs.read(_buff_raw_memory, sizeof(T) * _buff_size);
  _buff_pos = 0;
}

template <typename T>
void DiskTape<T>::read_reverse_buff() {
  if (_curr_pos <= DISK_TAPE_BUFF_SIZE) {
    _buff_size = _curr_pos;
  } else {
    _buff_size = DISK_TAPE_BUFF_SIZE;
  }
  _curr_pos -= _buff_size;
  fs.seekg(sizeof(T)*_curr_pos, std::fstream::beg);
  fs.read(_buff_raw_memory, sizeof(T) * _buff_size);
  _buff_pos = _buff_size;
}

template <typename T>
void DiskTape<T>::dump_tape() const {
  std::cout << "taping backend file name : " << _tape_name << std::endl;
  std::ifstream _is;
  _is.open(_tape_name, std::fstream::in);
  T val;
  std::cout << "[" << _size << "]";
  for (int i = 0; i < _size; i++) {
    _is.read((char*)&val, sizeof(T));
    std::cout << " " << val; 
  }
  _is.close();
  std::cout << std::endl;
}
} //namespace ReverseAD

#endif // REVERSEAD_DISK_TAPE_H_
