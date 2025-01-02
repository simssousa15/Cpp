#include <iostream>
#include <memory>

typedef unsigned int uint;

template <typename T>
class shared_ptr{
    private:
        T * ptr = nullptr;
        uint * cnt = nullptr;

        void clean_up(){
            if(cnt != nullptr){
                *cnt--;

                if(*cnt == 0){
                    delete cnt;
                    delete ptr;
                }
            }
        }

    public:
        // constructors
        shared_ptr() = delete;
        shared_ptr(T val): ptr(new T(val)), cnt(new uint(1)){}
        // shared_ptr(T* val): ptr(val), cnt(new uint(1)){}

        // overloads
        T* operator->() const { return this->ptr; }
        T& operator*() const{ return *ptr; }

        // destructor
        ~shared_ptr(){ clean_up(); }

        // copy constructor
        shared_ptr(const shared_ptr& s){
            ptr = s.ptr;
            cnt = s.cnt;

            if(ptr != nullptr){ *cnt++; }
        }

        // copy assignment
        shared_ptr& operator=(const shared_ptr& s){
            clean_up();
            ptr = s.ptr;
            cnt = s.cnt;

            if(ptr != nullptr){ *cnt++; }

            return *this;
        }

        // move constructor
        shared_ptr(shared_ptr&& s){
            cnt = s.cnt;
            ptr = s.ptr;
            s.ptr = nullptr;
            s.cnt = nullptr;
        }

        // move assignment
        shared_ptr& operator=(const shared_ptr&& s){
            clean_up();
            cnt = s.cnt;
            ptr = s.ptr;
            s.ptr = nullptr;
            s.cnt = nullptr;

            return *this;
        }

};

int main(){
    shared_ptr<int*> ptr1(new int);
    auto ptr2 = ptr1;
    return 0;
}