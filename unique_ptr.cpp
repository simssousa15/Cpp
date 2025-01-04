#include <iostream>
#include <memory>

template <typename T>
class unique_ptr{
    private:
        T * _res;
    
    public:
        unique_ptr(): _res(nullptr){}
        unique_ptr(T*ptr): _res(ptr){}

        ~unique_ptr(){ if(_res){ delete _res; } }
        
        // copy
        unique_ptr(const unique_ptr& u) = delete;
        void operator=(const unique_ptr& u) = delete;

        // move
        unique_ptr(unique_ptr&& u){
            _res = u._res; 
            u._res = nullptr;
        }
        void operator=(unique_ptr&& u){
            _res = u._res; 
            u._res = nullptr;
        }


        T operator*(){ return *_res; }
        T* operator->(){ return _res; }

        void release(){
            delete _res;
            _res = nullptr;
        }

        void reset(T* ptr){
            release();
            _res = ptr;
        }
};

int main(){
    {
        unique_ptr<int> ptr1; 
        std::cout << "Default constructor ok." << std::endl;

        unique_ptr<int> ptr2(new int(10));
        std::cout << "Param constructor ok." << std::endl;

        unique_ptr<int> ptr4(std::move(ptr2));
        std::cout << "Move constructor ok" << std:: endl;

        ptr2 = std::move(ptr4);
        std::cout << "Move assignment ok." << std:: endl;

        std::cout << "Pointer value: " << (*ptr2) << std::endl;
    }

    
    std::cout << "Destructor ok." << std::endl;

    return 0;
}

// g++ -o a.out unique_ptr.cpp && ./a.out

/* std::cout << "this->ptr " << this->ptr << std::endl;
std::cout << "this->cnt " << this->cnt << std::endl;
std::cout << "other->ptr " << s.ptr << std::endl;
std::cout << "other->cnt " << s.cnt << std::endl; */