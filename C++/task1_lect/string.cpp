#include "string.hpp"

const size_t String::npos;

size_t String::str_len(const char* s) {
    if (!s) return 0;
    size_t len = 0;
    
    while(s[len] != '\0') ++len;
    
    return len;
}

void String::mem_move(char* dest, const char* src, size_t n) {
    if (!dest || !src || n == 0) return;
    if (dest > src) {
        for (int i = n - 1; i >= 0; --i) {
            dest[i] = src[i];
        }
    } else {
        for (int i = 0; i < n; ++i) {
            dest[i] = src[i];
        }
    }
}

void String::str_fill(char* dest, char c, size_t n) {
    for (int i = 0; i < n; ++i) {
        dest[i] = c;
    }
}

void String::detach() {
    if (*_ref_count == 1) return;
    (*_ref_count)--;
    char* new_buffer = new char[_capacity + 1];
    mem_move(new_buffer, _buffer, _length);
    new_buffer[_length] = '\0';
    _buffer = new_buffer;
    _ref_count = new size_t(1);
}

void String::ensure_capacity(size_t min_cap) {
    if (min_cap <= _capacity) return;
    size_t new_cap = _capacity * 2 + 1;
    if (new_cap < min_cap) new_cap = min_cap;

    char* new_buffer = new char[new_cap + 1];
    mem_move(new_buffer, _buffer, _length);
    new_buffer[_length] = '\0';

    delete[] _buffer;
    _buffer = new_buffer;
    _capacity = new_cap;
}

String::String() {
    _capacity = 0;
    _length = 0;
    _buffer = new char[1];
    _buffer[0] = '\0';
    _ref_count = new size_t(1);
}

String::String(const char* str) {
    if (!str) str = "";
    _length = str_len(str);
    _capacity = _length;

    _buffer = new char[_capacity + 1];
    mem_move(_buffer, str, _length);
    _buffer[_length] = '\0';
    _ref_count = new size_t(1);
}

String::String(const char* str, size_t n) {
    if (!str) str = "";
    size_t src_len = str_len(str);
    _length = (n < src_len) ? n : src_len;
    _capacity = _length;
    _buffer = new char[_capacity + 1];
    mem_move(_buffer, str, _length);
    _buffer[_length] = '\0';
    _ref_count = new size_t(1);
}

String::String(size_t n, char c) {
    _length = n;
    _capacity = n;
    _buffer = new char[_capacity + 1];
    str_fill(_buffer, c, n);
    _buffer[_length] = '\0';
    _ref_count = new size_t(1);
}

String::String(const String& str) {
    _buffer = str._buffer;
    _length = str._length;
    _capacity = str._capacity;
    _ref_count = str._ref_count;
    ++(*_ref_count);
}

String::String(const String& str, size_t pos, size_t len) {
    if (pos > str._length) throw std::out_of_range("String substring out of range");
    if (len == npos) len = str._length - pos;
    size_t max_len = str._length - pos;
    _length = (len < max_len) ? len : max_len;
    _capacity = _length;
    _buffer = new char[_capacity + 1];
    mem_move(_buffer, str._buffer + pos, _length);
    _buffer[_length] = '\0';
    _ref_count = new size_t(1);
}

String::~String() {
    if (--(*_ref_count) == 0) {
        delete[] _buffer;
        delete _ref_count;
    }
}

size_t String::size() const {return _length;}

size_t String::capacity() const {return _capacity;}

bool String::empty() const {return _length == 0;}

const char* String::data() const {return _buffer;}

size_t String::countRef() const {return *_ref_count;}

char& String::at(size_t pos) { 
    if (pos >= _length) throw std::out_of_range("String at out of range"); 
    detach(); 
    return _buffer[pos];
}

const char& String::at(size_t pos) const { 
    if (pos > _length) throw std::out_of_range("String at out of range");
    return _buffer[pos];
}

char& String::operator[](size_t pos) {
    detach();
    return _buffer[pos];
}

const char& String::operator[](size_t pos) const {
    return _buffer[pos];
}

char& String::back() {
    detach();
    return _buffer[_length - 1];
}

const char& String::back() const {
    return _buffer[_length - 1];
}

char& String::front() {
    detach();
    return _buffer[0];
}

const char& String::front() const {
    return _buffer[0];
}

void String::reserve(size_t n) {
    if (n <= _capacity) return;
    detach();
    ensure_capacity(n);
}

void String::clear() {
    detach();
    _length = 0;
    _buffer[0] = '\0';
}

String& String::operator+=(const String& str) {
    size_t add_len = str._length;
    size_t new_len = _length + add_len;
    detach();
    ensure_capacity(new_len);
    mem_move(_buffer + _length, str._buffer, add_len);
    _length = new_len;
    _buffer[_length] = '\0';
    return *this;
}

String& String::operator+=(const char* str) {
    if (!str) return *this;
    size_t add_len = str_len(str);
    size_t new_len = _length + add_len;
    detach();
    ensure_capacity(new_len);
    mem_move(_buffer + _length, str, add_len);
    _length = new_len;
    _buffer[_length] = '\0';
    return *this;
}

String& String::operator+=(char c) {
    size_t new_len = _length + 1;
    detach();
    ensure_capacity(new_len);
    _buffer[_length] = c;
    _length = new_len;
    _buffer[_length] = '\0';
    return *this;
}

String& String::operator=(const String& str) {
    if (this == &str) return *this;
    if (--(*_ref_count) == 0) {
        delete[] _buffer;
        delete _ref_count;
    }
    _buffer = str._buffer;
    _length = str._length;
    _capacity = str._capacity;
    _ref_count = str._ref_count;
    ++(*_ref_count);
    return *this;
}

String& String::operator=(const char* str) {
    if (--(*_ref_count) == 0) {
        delete[] _buffer;
        delete _ref_count;
    }
    if (!str) str = "";
    _length = str_len(str);
    _capacity = _length;
    _buffer = new char[_capacity + 1];
    mem_move(_buffer, str, _length);
    _buffer[_length] = '\0';
    _ref_count = new size_t(1);
    return *this;
}

String& String::insert(size_t pos, const String& str) {
    if (pos > _length) throw std::out_of_range("String insert out of range");
    size_t add_len = str._length;
    size_t new_len = _length + add_len;
    detach();
    ensure_capacity(new_len);
    mem_move(_buffer + pos + add_len, _buffer + pos, _length - pos + 1);
    mem_move(_buffer + pos, str._buffer, add_len);
    _length = new_len;
    return *this;
}

String& String::insert(size_t pos, const char* str) {
    if (pos > _length) throw std::out_of_range("String insert out of range");
    if (!str) return *this;
    size_t add_len = str_len(str);
    size_t new_len = _length + add_len;
    detach();
    ensure_capacity(new_len);
    mem_move(_buffer + pos + add_len, _buffer + pos, _length - pos + 1);
    mem_move(_buffer + pos, str, add_len);
    _length = new_len;
    return *this;
}

String& String::insert(size_t pos, size_t n, char c) {
    if (pos > _length) throw std::out_of_range("String insert out of range");
    size_t new_len = _length + n;
    detach();
    ensure_capacity(new_len);
    mem_move(_buffer + pos + n, _buffer + pos, _length - pos + 1);
    str_fill(_buffer + pos, c, n);
    _length = new_len;
    return *this;
}

String& String::erase(size_t pos, size_t len) {
    if (pos > _length) throw std::out_of_range("String erase out of range");
    detach();
    if (len == npos || pos + len > _length) len = _length - pos;
    mem_move(_buffer + pos, _buffer + pos + len, _length - pos - len + 1);
    _length -= len;
    return *this;
}

String& String::replace(size_t pos, size_t len, const String& str) {
    if (pos > _length) throw std::out_of_range("String replace out of range");
    detach();
    if (len == npos || pos + len > _length) len = _length - pos;
    size_t add_len = str._length;
    size_t new_len = _length - len + add_len;
    ensure_capacity(new_len);
    mem_move(_buffer + pos + add_len, _buffer + pos + len, _length - pos - len + 1);
    mem_move(_buffer + pos, str._buffer, add_len);
    _length = new_len;
    return *this;
}

String& String::replace(size_t pos, size_t len, const char* str) {
    if (pos > _length) throw std::out_of_range("String replace out of range");
    detach();
    if (len == npos || pos + len > _length) len = _length - pos;
    size_t add_len = str ? str_len(str) : 0;
    size_t new_len = _length - len + add_len;
    ensure_capacity(new_len);
    mem_move(_buffer + pos + add_len, _buffer + pos + len, _length - pos - len + 1);
    if (str) mem_move(_buffer + pos, str, add_len);
    _length = new_len;
    return *this;
}

String& String::replace(size_t pos, size_t len, size_t n, char c) {
    if (pos > _length) throw std::out_of_range("String replace out of range");
    detach();
    if (len == npos || pos + len > _length) len = _length - pos;
    size_t new_len = _length - len + n;
    ensure_capacity(new_len);
    mem_move(_buffer + pos + n, _buffer + pos + len, _length - pos - len + 1);
    str_fill(_buffer + pos, c, n);
    _length = new_len;
    return *this;
}

void String::swap(String& str) {
    char* temp_buffer = _buffer;
    _buffer = str._buffer;
    str._buffer = temp_buffer;

    size_t temp_length = _length;
    _length = str._length;
    str._length = temp_length;

    size_t temp_capacity = _capacity;
    _capacity = str._capacity;
    str._capacity = temp_capacity;

    size_t* temp_ref_count = _ref_count;
    _ref_count = str._ref_count;
    str._ref_count = temp_ref_count;
}

size_t String::find(char c, size_t pos) const {
    if (pos > _length) return npos;
    for (size_t i = pos; i < _length; ++i) {
        if (_buffer[i] == c) return i;
    }
    return npos;
}

size_t String::find(const String& str, size_t pos) const {
    if (pos > _length || str._length == 0) return npos;
    for (size_t i = pos; i <= _length - str._length; ++i) {
        bool match = true;
        if (_buffer[i] == str[0]) {
            for (size_t j = 1; j < str._length; ++j) {
                if (_buffer[i + j] != str._buffer[j]) {
                    match = false;
                    break;
                }
            }
        }
        else match = false;
        if (match) return i;
    }
    return npos;
}

size_t String::find(const char* str, size_t pos) const {
    if (pos > _length || !str) return npos;
    size_t str_len_val = str_len(str);
    if (str_len_val == 0) return pos;
    for (size_t i = pos; i <= _length - str_len_val; ++i) {
        bool match = true;
        if (_buffer[i] == str[0]) {
            for (size_t j = 0; j < str_len_val; ++j) {
                if (_buffer[i + j] != str[j]) {
                    match = false;
                    break;
                }
            }
        }
        else match = false;
        if (match) return i;
    }
    return npos;
}

String String::substr(size_t pos, size_t len) const {
    if (pos > _length) throw std::out_of_range("String substr out of range");
    if (pos == _length) return String();
    return String(*this, pos, len);
}

int String::compare(const String& str) const {
    size_t min_len = (_length < str._length) ? _length : str._length;
    for (size_t i = 0; i < min_len; ++i) {
        if (_buffer[i] != str._buffer[i]) return (int)(_buffer[i]) - (int)(str._buffer[i]);
    }
    return (int)(_length) - (int)(str._length);
}

int String::compare(const char* str) const {
    if (!str) str = "";
    size_t str_len_val = str_len(str);
    size_t min_len = (_length < str_len_val) ? _length : str_len_val;
    for (size_t i = 0; i < min_len; ++i) {
        if (_buffer[i] != str[i]) return (int)(_buffer[i]) - (int)(str[i]);
    }
    return (int)(_length) - (int)(str_len_val);
}