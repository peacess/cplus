
#include <utility>
#include <vector>


void f(const int & p){

}
template<typename T>
void fwd(T&& param){
    f(std::forward<T>(param));
}

class C{
public:
    static const int Min = 28;
};

const int C::Min;

int main(){
    fwd(C::Min);
}