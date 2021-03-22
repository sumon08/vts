

#include <crc8.h>
#include <crc16.h>
#include <crc32.h>

namespace adapter
{

    template<typename T>
    struct CrcType 
    {
    };

    template<>
    struct CrcType <uint8_t>
    {
        using crc_func_up = uint8_t (*)( const uint8_t * src, size_t len, uint8_t crc8val);
        static constexpr crc_func_up CrcUpdate = crc8part;
    };

    template<>
    struct CrcType<uint16_t>
    {
        using crc_func_up = uint16_t (*)( const uint8_t * src, size_t len, uint16_t crc16val);
        static constexpr crc_func_up CrcUpdate = crc16part;
    };

    template<>
    struct CrcType<uint32_t>
    {
        using crc_func_up = uint32_t (*)( const uint8_t * src, size_t len, uint32_t crc16val);
        static constexpr crc_func_up CrcUpdate = crc32part;
    };



    template<typename T>
    class Crc 
    {
        T crc_val;
        public:

        void Reset()
        {
            crc_val = 0;
        }

        T operator << (uint8_t val)
        {
            crc_val = CrcType<T>::CrcUpdate(&val, 1, crc_val);
            return crc_val;
        }

        T Update(const uint8_t * data, size_t len)
        {
            crc_val = CrcType<T>::CrcUpdate(data, len, crc_val);
            return crc_val;
        }

        operator T () const
        {
            return crc_val;
        }
    };


    using CrcEight = Crc<uint8_t>;
    using CrcSixteen = Crc<uint16_t>;
    using CrcThirtyTwo = Crc<uint32_t>;
}