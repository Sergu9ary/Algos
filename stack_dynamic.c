#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

struct timeval tv1,tv2,dtv;
struct timezone tz;
void time_start() { gettimeofday(&tv1, &tz); }
long time_stop(){
    gettimeofday(&tv2, &tz);
    dtv.tv_sec= tv2.tv_sec -tv1.tv_sec;
    dtv.tv_usec=tv2.tv_usec-tv1.tv_usec;
    if(dtv.tv_usec<0) { dtv.tv_sec--; dtv.tv_usec+=1000000; }
    return dtv.tv_sec*1000+dtv.tv_usec/1000;
}
typedef int Data;
typedef struct File File;
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
int push(struct Stack* st, void* buffer){
    Data data = *((Data*) buffer);
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

void load_million(struct Stack* st){
    for(int i = 0; i < 1000000; i++){
        push(st, &i);
    }
}
void first_test(struct Stack* st){
    load_million(st);
    while(st->size >= 100000){
        int count_delete = st->size / 2;
        int count_push = st->size / 4;
        for(int i = 0; i < count_delete; i++){
            pop(st);
        }
        for(int i = 0; i < count_push; i++){
            push(st, &i);
        }
    }
}
void second_test_first(struct Stack* st){
    for(int i = 0; i < 100; i++){
        for(int j = 0; j < 1000; j++){
            pop(st);
        }
        for(int j = 0; j < 1000; j++){
            push(st, &j);
        }
    }
}
void second_test_second(struct Stack* st){
    load_million(st);
    second_test_first(st);
    first_test(st);
    second_test_first(st);

}
void third_test(struct Stack* st){
    for(int i = 0; i < 1000000; i++) {
        int random_number = rand() % 2 + 1;
        if(random_number == 2){
            pop(st);
        }
        else{
            push(st, &random_number);
        }
    }

}
int main(){
    File* f = fopen("test_stack1.txt", "w");
    fprintf(f, "TEST 1(ms)\n");
    long average_time = 0;
    for(int i = 0; i < 3; i++){
        struct Stack* st = stack_ctr(1000000, sizeof(Data));
        time_start();
        first_test(st);
        long mid_result = time_stop();
        average_time += mid_result;
        fprintf(f, "%d. %ld\n", i + 1, mid_result);
        stack_dtr(st);
    }
    fprintf(f, "Average time = %ld \n", average_time / 3);

    fprintf(f, "TEST 2(ms)\n");
    average_time = 0;
    for(int i = 0; i < 3; i++){
        struct Stack* st = stack_ctr(1000000, sizeof(Data));
        time_start();
        second_test_second(st);
        long mid_result = time_stop();
        average_time += mid_result;
        fprintf(f, "%d. %ld\n", i + 1, mid_result);
        stack_dtr(st);
    }
    fprintf(f, "Average time = %ld \n", average_time / 3);

    fprintf(f, "TEST 3(ms)\n");
    average_time = 0;
    for(int i = 0; i < 3; i++){
        struct Stack* st = stack_ctr(1000000, sizeof(Data));
        load_million(st);
        time_start();
        third_test(st);
        long mid_result = time_stop();
        average_time += mid_result;
        fprintf(f, "%d. %ld\n", i + 1, mid_result);
        stack_dtr(st);
    }
    fprintf(f, "Average time = %ld \n", average_time / 3);

    return 0;
}