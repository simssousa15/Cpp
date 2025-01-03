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
                (*cnt)--;

                if((*cnt) == 0){
                    if(cnt){ delete cnt; }
                    if(ptr){ delete ptr; }
                    cnt = nullptr;
                    ptr = nullptr;
                }
            }
        }

    public:
        // constructors
        shared_ptr(): ptr(nullptr), cnt(nullptr){};
        shared_ptr(T val): ptr(new T(val)), cnt(new uint(1)){}
        shared_ptr(T* val): ptr(val), cnt(new uint(1)){}

        // overloads
        T* operator->() const { return ptr; }
        T& operator*() const{ return *ptr; }

        // destructor
        ~shared_ptr(){ clean_up(); }

        // copy constructor
        shared_ptr(const shared_ptr& s){
            ptr = s.ptr;
            cnt = s.cnt;

            if(cnt != nullptr){ (*cnt)++; }
        }

        // copy assignment
        shared_ptr& operator=(const shared_ptr& s){
            clean_up();
            ptr = s.ptr;
            cnt = s.cnt;

            if(cnt != nullptr){ (*cnt)++; }

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
        shared_ptr& operator=(shared_ptr&& s){
            clean_up();
            cnt = s.cnt;
            ptr = s.ptr;
            s.cnt = cnt;
            s.ptr = ptr;

            return *this;
        }

};

int main(){
    {
        shared_ptr<int> ptr1; 
        std::cout << "Default constructor ok." << std::endl;

        shared_ptr<int> ptr2(new int(10));
        std::cout << "Param constructor ok." << std::endl;

        shared_ptr<int> ptr3(ptr2);
        std::cout << "Copy constructor ok." << std::endl;

        ptr3 = ptr2;
        std::cout << "Copy assignment ok." << std::endl;

        shared_ptr<int> ptr4(std::move(ptr1));
        std::cout << "Move constructor ok" << std:: endl;

        ptr2 = std::move(ptr3);
        std::cout << "Move assignment ok" << std:: endl;

        std::cout << "Pointer value: " << (*ptr2) << std::endl;
    }

    
    std::cout << "Destructor ok." << std::endl;

    return 0;
}

// g++ -o a.out shared_ptr.cpp && ./a.out

/* std::cout << "this->ptr " << this->ptr << std::endl;
std::cout << "this->cnt " << this->cnt << std::endl;
std::cout << "other->ptr " << s.ptr << std::endl;
std::cout << "other->cnt " << s.cnt << std::endl; */