#include <stdio.h>
#include <stdlib.h>
typedef int Data;
struct Stack{
    Data *a;
    size_t capacity;//для скольки элементов выделена память
    unsigned int size;//сколько элементов хранится в стеке
};
struct Stack* stack_ctr(size_t size, size_t element_size){
    struct Stack* st;
    st = malloc(sizeof(struct Stack));
    st->size = 0;
    st->capacity = size;
    st->a = malloc(st->capacity * element_size);
    return st;
};
void printStack(struct Stack* st){
    for(unsigned int i = 0; i < st->size; i++){
        printf("%d", st->a[i]);
    }
    printf("\n");
}
int is_full(struct Stack* st){
    return st->size == st->capacity;
}
int is_empty(struct Stack* st){
    return st->size == 0;
}
int push(struct Stack* st, Data data){
    if(is_full(st)){
        st->capacity++;
        st->a = realloc(st->a, st->capacity*sizeof(Data));
    }
    st->a[st->size] = data;
    st->size++;
    return 1;
}
int top(struct Stack* st){
    if((st->size) > 0) {
        return st->a[st->size-1];
    } else {
        printf("Стек пуст!\n");
        return 0;
    }
}
int pop(struct Stack* st){
    if(is_empty(st)){
        return 0;
    }
    else{
        printf("Удален элемент= %d\n", st->a[st->size - 1]);
        st->size --;
        if(st->capacity > st->size * 4){
            st->a = realloc(st->a, st->capacity / 4);
        }
    }
    return 1;
}
struct Stack* stack_dtr(struct Stack* st){
    free(st->a);
    free(st);
    return NULL;
}
int main(){
    Data test[8] = {5, 1, -3, 0, 1, 2, 3, 4};
    struct Stack* st = stack_ctr(8, sizeof(Data));
    printf("empty: %s\n", is_empty(st) ? "YES" : "NO");
    Data d;
    for(int i = 0; i < 8; i++){
        d = test[i];
        push(st, d);
    }
    printf("%d", top(st));
    printf("empty: %s\n", is_empty(st) ? "YES" : "NO");
    printf("full: %s\n", is_full(st) ? "YES" : "NO");
    for(int i = 0; i < 8; i++){
        pop(st);
    }
    printf("empty: %s\n", is_empty(st) ? "YES" : "NO");
    printf("full: %s\n", is_full(st) ? "YES" : "NO");
    st = stack_dtr(st);
}