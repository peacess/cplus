#include <cstdio>
#include "./inline_.h"
#include "./static_.h"
#include "./static_.cpp"
#include "./static_inline_.h"
#include "./static_inline_.cpp"

int main(){
    printf("static: \n");
    static_f();
    static_f();
    static_call_inline();
    printf("inline: \n");
    inline_f();
    inline_f();
    printf("static inline: \n");
    static_inline_f();
    static_inline_f();
}