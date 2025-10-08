#pragma once

#include <stdlib.h>
#include <stdexcept>

class String {
    public:
    String();
    String(const char* str);
    String(const char* str, size_t n);
    String(size_t n, char c);
    String(const String& str);
    String(const String& str, size_t pos, size_t len = npos);
    virtual ~String();

    size_t size() const;
    size_t capacity() const;
    void reserve(size_t n = 0);
    void clear();
    bool empty() const;

    char& at(size_t pos);
    const char& at(size_t pos) const;

    char& operator[](size_t pos);
    const char& operator[](size_t pos) const;

    char& back();
    const char& back() const;

    char& front();
    const char& front() const;

    String& operator+=(const String& str);
    String& operator+=(const char* str);
    String& operator+=(char c);

    String& operator=(const String& str);
    String& operator=(const char* str);

    String& insert(size_t pos, const String& str);
    String& insert(size_t pos, const char* str);
    String& insert(size_t pos, size_t n, char c);

    String& erase(size_t pos = 0, size_t len = npos);

    String& replace(size_t pos, size_t len, const String& str);
    String& replace(size_t pos, size_t len, const char* str);
    String& replace(size_t pos, size_t len, size_t n, char c);

    void swap(String& str);
    const char* data() const;

    size_t find(const String& str, size_t pos = 0) const;
    size_t find(const char* str, size_t pos = 0) const;
    size_t find(char c, size_t pos = 0) const;

    String substr(size_t pos = 0, size_t len = npos) const;

    int compare(const String& str) const;
    int compare(const char* str) const;

    static const size_t npos = static_cast<size_t>(-1);

    size_t countRef() const;

    private:

    char* _buffer;
    size_t _length;
    size_t _capacity;
    size_t* _ref_count;

    static size_t str_len(const char* s);
    static void mem_move(char* dest, const char* src, size_t n);
    static void str_fill(char* dest, char c, size_t n);

    void detach();
    void ensure_capacity(size_t new_capacity);
};