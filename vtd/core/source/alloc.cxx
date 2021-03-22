

#include <cxx/cstdint>

extern "C" {


    typedef struct 
    {
        void * pool_base;
        uint32_t total_block_count;
        uint16_t block_size;
        uint32_t free_block_count;
        uint32_t allocated_block_count;

    }MemPool;

    typedef struct MemManager
    {
        void * heap_base;
    }MemManager;
};