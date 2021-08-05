//
// Created by root on 8/1/21.
//
#include "include/chunk.h"
#include <memory>
#include <assert.h>
#include <iostream>
Chunk::Chunk(size_t chunk_size, unsigned char num_of_chunks): current_idx_{0},available_chunks_{num_of_chunks}{
    data_ = std::make_unique<unsigned char[]>(chunk_size*num_of_chunks);

    for (unsigned char i{0};i<num_of_chunks;)
    {
        auto ptr=data_.get()+i*chunk_size;
        *ptr = ++i;
    }
}

void* Chunk::allocate(size_t size)
{
    if (available_chunks_==0)
        return nullptr;

    unsigned char* ptr = data_.get()+current_idx_*size;
    current_idx_ = *ptr;
    --available_chunks_;
    return ptr;
}

void Chunk::deallocate(void* ptr, size_t size){
    assert(ptr>=data_.get());
    auto p = static_cast<unsigned char*>(ptr);
    * p= current_idx_;
    assert((p-data_.get()) % size == 0);
    current_idx_ = static_cast<unsigned char>((p - data_.get())/size);
    ++available_chunks_;
}

bool Chunk::in(unsigned char* p, size_t num_of_chunks) const{
    return (p>data_.get()) && (p<data_.get()+num_of_chunks);
}

bool Chunk::full() const {
    return available_chunks_ == 0;
}
