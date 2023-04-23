#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct Stack{
    long long arr[10000];
    int size;
};
int is_empty(struct Stack* st){
    return st->size == 0;
}
void push(struct Stack* st, long long data){
    st->arr[st->size] = data;
    st->size++;
}
void top(struct Stack* st){
    if((st->size) > 0) {
        printf("%lld\n", st->arr[st->size-1]);
    } else {
        printf("error\n");;
    }
}
void pop(struct Stack* st){
    if(is_empty(st)){
        printf("error\n");
    }
    else{
        printf("%lld\n", st->arr[st->size - 1]);
        st->size --;
    }
}
void stackSize(struct Stack* st){
    printf("%d\n", st->size);
}
void stack_clear(struct Stack* st){
    st->size = 0;
    printf("%s\n", "ok");
}

int main() {
    char str[100] = "";
    long long n;
    struct Stack st;
    st.size = 0;
    while(true){
        if(scanf("%s",str)){}
        if(str[0] == 'p'){
            if(str[1] == 'u'){
                if(scanf("%lld",&n)){}
                push(&st, n);
                printf("%s\n", "ok");
            }
            else{
                pop(&st);
            }
        }
        else if(str[0] == 'b'){
            top(&st);
        }
        else if(str[0] == 's'){
            stackSize(&st);
        }
        else if(str[0] == 'c'){
            stack_clear(&st);
        }
        else if(str[0] == 'e'){
            printf("%s\n", "bye");
            return 0;
        }
    }
}
