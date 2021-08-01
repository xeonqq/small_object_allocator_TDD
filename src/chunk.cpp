//
// Created by root on 8/1/21.
//
#include "include/chunk.h"
Chunk::Chunk(size_t chunk_size, unsigned char num_of_chunks): current_idx_{0},available_chunks_{num_of_chunks}{
    head_ = new unsigned char[chunk_size*num_of_chunks];
    for (unsigned char i{0};i<num_of_chunks;)
    {
        auto ptr=head_+i*chunk_size;
        *ptr = ++i;
    }
}


void* Chunk::allocate(size_t size)
{
    if (available_chunks_==0)
        return nullptr;

    unsigned char* ptr = head_+current_idx_;
    current_idx_ = *ptr;
    --available_chunks_;
    return ptr;
}

void Chunk::deallocate(void* ptr, size_t size){
    auto p = static_cast<unsigned char*>(ptr);
    * p= current_idx_;
    current_idx_ = p - head_;
    ++available_chunks_;
}

bool Chunk::in(unsigned char* p, size_t num_of_chunks) const{
    return (p>head_) && (p<head_+num_of_chunks);
}

bool Chunk::full() const {
    return available_chunks_ == 0;
}