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
struct Node{
    struct Node* next;
    Data data;
};
struct Stack{
    struct Node* a;
    unsigned int size;
};

struct Stack* stack_ctr(){
    struct Stack* st = (struct Stack*)malloc(sizeof(struct Stack));
    st->a = NULL;
    st->size = 0;
    return st;
}

int push(struct Stack* st, void* buffer){
    Data data = *((Data*) buffer);
    struct Node* replace = st->a;
    st->a = (struct Node*)malloc(sizeof(struct Node));
    if(st->a == NULL){
        st->a = replace;
        return 0;
    }
    st->a->next = replace;
    st->a->data= data;
    st->size++;
    return 1;
}
Data top(struct Stack* st){
    return st->a->data;
}
int pop(struct Stack* st){
    if(st->size == 0){
        return 0;
    }
    struct Node* replace = st->a->next;
    free(st->a);
    st->a = replace;
    st->size--;
    return 1;
}
struct Stack* stack_dtr(struct Stack* st){
    while (st->a != NULL){
        pop(st);
    }
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
    File* f = fopen("test_stack2.txt", "w");
    fprintf(f, "TEST 1(ms)\n");
    long average_time = 0;
    for(int i = 0; i < 3; i++){
        struct Stack* st = stack_ctr();
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
        struct Stack* st = stack_ctr();
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
        struct Stack* st = stack_ctr();
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


