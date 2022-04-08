#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <string.h>
#include <time.h>
#include <stdarg.h>
#include <unistd.h>
#include <fcntl.h>


FILE *inicial_log(){
    FILE *fp;
    char *path = getenv("MSM_OUPUT");
    if(path == NULL){
        path = "./root/ecole2600/my_secmallocgit/Log.txt";
    }
    fp = fopen(path,"a+");
    time_t timestamp = time( NULL );
    struct tm * timeInfos = localtime( & timestamp );
    log_generator(fp,"*******************\n");
    //log_generator(fp,("%02d:%02d:%02d\n\n",timeInfos->tm_hour, timeInfos->tm_min,timeInfos->tm_sec));
    return fp;
}

void log_generator(int fd, const char* format,...){
    char buf [500];
    va_list argslist;
    va_start(argslist,format);
    int size = vsnprintf(buf,500,format,argslist);
    va_end(argslist);
    write(fd,buf,size);

}

void *my_malloc(size_t size){
    FILE *fp = inicial_log();

    log_generator(fp,"INFO: Calling malloc function...\n");
    if(size == 0){
        log_generator(fp,"WARN: allocating 0 bytes returning NULL pointer\n"); 
        return NULL;
    }
    int *pointer = mmap(NULL,sizeof(size_t)+size,PROT_READ | PROT_WRITE | PROT_EXEC,MAP_PRIVATE | MAP_ANONYMOUS,-1,0);
    if(pointer == MAP_FAILED) {
        log_generator(fp,"ERROR: Mapping Failed\n");  
    }
    else {
        //int *ptr = pointer;
        pointer += sizeof(size_t)/sizeof(int); // 8/4 = 2
        //*ptr = size + sizeof(size_t);
        log_generator(fp,"INFO: Successfully Allocate %ld bytes at %p\n",size,pointer);
    }
    
    return pointer;
}


void my_free(void *ptr){
    FILE *fp = inicial_log();
    log_generator(fp,"INFO: Calling free function...\n");
    if(ptr != NULL){
        int *pointer = ptr - sizeof(size_t); 
        int size = *pointer;
        int result = munmap(pointer,size);
        if(0 == result){
            log_generator(fp,"INFO: Successfully free %ld bytes at %p",size - sizeof(size_t),ptr);
        }
    }else{
       log_generator(fp,"WARN: Performing free on NULL pointer"); 
    }
}

void *my_calloc(size_t nmemb, size_t size){
    FILE *fp = inicial_log();
    log_generator(fp,"INFO: Calling function calloc...\n");
    size_t max_size = nmemb * size;
    int *ptr = my_malloc(max_size);
    int *cp_ptr = ptr;

    log_generator(fp,"BEFORE %p\n",ptr);
    if(ptr != MAP_FAILED){
        for(int i = 0;i<max_size;i++){
            cp_ptr += 1;
            *cp_ptr = 0;
            log_generator(fp,"%d",*cp_ptr);
        }
        log_generator(fp,"AFTER %p\n",ptr);
    }

    return ptr;
}

void *my_realloc(void *ptr, size_t size){
    FILE *fp = inicial_log();
    log_generator(fp,"INFO: Calling function realloc...\n");

    if(ptr == NULL){
        return my_malloc(size);
    }
    if(size == 0){
        my_free(ptr);
        return NULL;
    }

    int *pointer = ptr - sizeof(size_t); 
    int old_size = *pointer - sizeof(size_t);
    *pointer = size + sizeof(size_t);
    if(size > old_size){
        log_generator(fp,"WARN: size provided bigger than old size, can't reallocate\n");
    }
    log_generator(fp,"INFO: Successfully reallocate %ld bytes at %p \n",size,ptr);
    return ptr;
}
