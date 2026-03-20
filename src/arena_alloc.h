#pragma once

#include <iostream>

// the arena is a contiguous block of memory
// the arena should give a pointer to buffer + offset
// that is where you can construct the object in memory
// then you += offest by the size of the new object

// we know the size of the arena and have to do safety checks so we
// don't access memory outs ide our contiguous block of memory

class arena_alloc {
public:
    arena_alloc(const size_t size)
        : arena_buffer(nullptr), arena_size(size), offset(0) {
        arena_buffer = new char[size];
        offset = 0;
    }

    ~arena_alloc() {
        delete[] arena_buffer;
        arena_buffer = nullptr;
        arena_size = 0;
        offset = 0;
    }

    void clear() {
        offset = 0;
    }

    // increase the offset by the size of every added object to never add objects to the same memory space
    // then return the memory that the offset was aka the new place for the thing we allocate
    void* add(const size_t size) {
        if (offset + size >= arena_size) {
            return nullptr;
        }
        offset += size;
        void* ptr = (arena_buffer + (offset - size));
        return ptr;
    }

    size_t get_size() const { return arena_size; };
    size_t get_offset() const {return offset; };

private:
    char* arena_buffer;
    size_t arena_size;
    size_t offset; // the place in the allocated memory we are in
};