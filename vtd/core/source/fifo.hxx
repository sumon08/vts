#ifndef _FIFO_INCLUDE_H
#define _FIFO_INCLUDE_H

#include<memory.hxx>
#include <adapter.hxx>
#include <cxx/cstdio>

namespace Core {



    #define LIST_DEFAULT_SIZE       10

    template<typename T>
    class FifoBase
    {
        private:
        T * queue;
        int queue_size;
        int head,tail;
        int max_size;



        protected:



        FifoBase<T>(int size): max_size(size)
        {
            queue = new T[size];
            queue_size = 0;
            head = 0;
            tail=0;

        }

        ~FifoBase<T>()
        {
            delete [] queue;
        }


        inline T front()
        {

            T val = queue[head];
            return val;
        }

        inline bool push(T element)
        {
            if(tail == max_size){
                tail=0;
            }
            queue[tail] = element;
            tail++;
            queue_size++;
            return true;
        }

        T  pop()
        {
            if(head == max_size){
                head = 0;
            }

            queue_size--;

            T temp = queue[head++];

            return temp;

        }

        inline int size()
        {
            return queue_size;
        }
        inline bool empty()
        {
            return (queue_size==0);
        }

        inline int max()
        {
            return max_size;
        }
    };


    template<typename T>
    class FifoBase<unique_ptr<T>>
    {
         private:
        unique_ptr<T> * queue;
        int queue_size;
        int head,tail;
        int max_size;



        protected:



        FifoBase<unique_ptr<T>>(int size): max_size(size)
        {
            queue = new unique_ptr<T>[size];
            queue_size = 0;
            head = 0;
            tail=0;

        }

        ~FifoBase<unique_ptr<T>>()
        {
            delete [] queue;
        }


        inline unique_ptr<T> front()
        {

            T val = queue[head];
            return val;
        }

        inline bool push(unique_ptr<T> element)
        {
            if(tail == max_size){
                tail=0;
            }
            queue[tail] = Core::move(element);
            tail++;
            queue_size++;
            return true;
        }

        unique_ptr<T>  pop()
        {
            if(head == max_size){
                head = 0;
            }

            queue_size--;

            unique_ptr<T> temp = Core::move(queue[head++]);

            return temp;

        }

        inline int size()
        {
            return queue_size;
        }
        inline bool empty()
        {
            return (queue_size==0);
        }

        inline int max()
        {
            return max_size;
        }
    };




    template<typename T>
    class Fifo : public FifoBase<T>
    {

        adapter::PthreadCondition cond_more;
        adapter::PthreadCondition cond_less;

        adapter::PthreadMutex mutex;

        public:
        Fifo<T>(int size): FifoBase<T>(size)
        {
           //
        }
        ~Fifo<T>()
        {

        }

        T Front()
        {
            return this->front();
        }

        bool Push(T element)
        {
            mutex.Lock();

            while(this->Full())
                cond_less.TimedWait(mutex);

            bool ret = this->push(Core::move(element));
            cond_more.Broadcast();
            mutex.Unlock();
            return ret;
        }

        T  Pop()
        {
            mutex.Lock();
            while(this->empty())
                cond_more.TimedWait(mutex);

            T  ret = this->pop();

            cond_less.Broadcast();
            mutex.Unlock();
           return ret;

        }

        int Size()
        {
            return this->size();
        }
        bool Empty()
        {
            return this->empty();
        }

        bool Full()
        {
            return (this->size() == this->max());
        }

    };



    template<typename T>
    class List : private FifoBase<T>
    {
        public:
        List<T>(int size) : FifoBase<T>(size)
        {

        }

        List<T>() : FifoBase<T>(LIST_DEFAULT_SIZE)
        {

        }

        T & operator[]( int index)
        {
            return this->GetRef(index);
        }

        bool Push(T & val)
        {
            if(this->size() == this->max())
            {
                std::printf("List out of bound detected. Please increase list size.\n");
                return false;
            }
            return this->push(val);
        }

        int CurrentSize()
        {
            return this->size();
        }
        int MaxSize()
        {
            return this->max();
        }

        bool Find( T & val)
        {
            for(int i = 0; i < this->size(); i++)
            {
                if(this->GetRef(i) == val)
                    return true;
            }

            return false;
        }
    };
}
#endif //_FIFO_INCLUDE_H
