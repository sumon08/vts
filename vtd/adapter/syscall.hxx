#ifndef __INCLUDE_ADAPTER_SYSCALL_HPP
#define __INCLUDE_ADAPTER_SYSCALL_HPP
//#include <nuttx/config.h>
#include <sys/types.h>
#include <sys/time.h>
#include <unistd.h>
#include <stdlib.h>
#include "base_type.hpp"
#include "fileio.hpp"
#include <config.hxx>
namespace adapter{

    class FdSet{
        public:
            Int_t nrfd;     /* no of read file descriptors */
            Int_t nwrfd;    /* no of write file descriptors */

            #if CONFIG_NO_OF_READ_FD > 0
                FileDescriptor read_fds[CONFIG_NO_OF_READ_FD];
            #endif //CONFIG_NO_OF_READ_FD > 0

            #if CONFIG_NO_OF_WRITE_FD > 0
                FileDescriptor write_fds[CONFIG_NO_OF_WRITE_FD];
            #endif //CONFIG_NO_OF_WRITE_FD > 0

            Int_t timeout_milis;


    };

    class PathName{
        public:

            typedef base_type<char *> path_type;
            path_type pathname;
    };

    class MemoryBuffer{
        public:
            typedef base_type<char *> buffer_type;
            buffer_type buffer;
    };

    class Syscall{
        public:
            static FileDescriptor Select(FdSet &adapter_fd);
            static void Exit(Int_t status);
            static FileDescriptor Open(PathName Pname, Int_t Flags);
            static FileDescriptor Open(PathName Pname, Int_t Flags, Uint32_t Modes);
            static WrittenBytes Write(FileDescriptor fd, MemoryBuffer buff, Int_t Count);
            static ReadBytes Read(FileDescriptor fd, MemoryBuffer *buff, Int_t Count);
            static Int_t Close(FileDescriptor fd);
            
    };

}
#endif //__INCLUDE_ADAPTER_SYSCALL_HPP
