#include <iostream>
#include <random>
#include <fstream>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include "common/common.h"
using namespace common;

const int MAXN = 10000000;

int numbers[MAXN];


void rand_write(){
    ofstream fout;
    fout.open("/home/wzy/project/io_optimization/cmake-build-debug-hx_52/data.txt");
    for (int i = 0; i < MAXN; ++i) {
        fout<<(rand() % 100000)<<" ";
    }
    fout.close();
}

void scanf_read()
{
    freopen("/home/wzy/project/io_optimization/cmake-build-debug-hx_52/data.txt","r",stdin);
    for(int i = 0; i < MAXN; ++i){
        scanf("%d",&numbers[i]); // scanf 1.37

    }
}

void cin_read()
{
    freopen("/home/wzy/project/io_optimization/cmake-build-debug-hx_52/data.txt","r",stdin);
    ios::sync_with_stdio(false); // 禁用cin与stdin的同步
    for(int i = 0; i < MAXN; ++i){
        cin>>numbers[i];           // 未禁用stdin的同步 4.71，禁用stdin的同步 1.35

    }
}

//先读入整个文件再进行处理
const int MAXS = 60*1024*1026; // 数组缓存大小
char buf[MAXS];

void analyse(char *buf,int len = MAXS){

    int i = 0;
    numbers[i = 0] = 0;
    for(char *p = buf; *p && p - buf < len; p++){
        if(*p == '\n'){
            numbers[++i] = 0;
        }
        else{
            numbers[i] = numbers[i] * 10 + *p -'0';
        }
    }
}

void readahead_analyse(){
    int fd = open("/home/wzy/project/io_optimization/cmake-build-debug-hx_52/data.txt",O_RDONLY,0);
    if(fd == -1){
        DLOG(ERROR)<< " Error open file for read "<<endl;
        return;
    }
//    int len = lseek(fd,0,SEEK_END); // 移动文件的读写位置。读写指针 测得文件大小
    readahead(fd,0,1024*1024*4);  //预读 执行文件预读入缓存页 因为是按页来读的，offset和 offset + count会被合理的按页取整
    int len = fread(buf,1,MAXS,stdin); // 效率提升至0.37s
    buf[len] = '\0'; // 字符串结束符
    analyse(buf,len);

}

void fread_analyse(){
    freopen("/home/wzy/project/io_optimization/cmake-build-debug-hx_52/data.txt","rb",stdin); // 不管多大文件 一次读取速度相差不大
    int len = fread(buf,1,MAXS,stdin); // 效率提升至0.37s
    DLOG(INFO)<< " buf len "<<len<<endl; //buf len 58888988 buf
    buf[len] = '\0'; // 字符串结束符
    analyse(buf,len);
}

void mmap_analyse(){
    int fd = open("/home/wzy/project/io_optimization/cmake-build-debug-hx_52/data.txt",O_RDONLY,0);
    if(fd == -1){
        DLOG(ERROR)<< " Error open file for read "<<endl;
        return;
    }
     //
    int len = lseek(fd,0,SEEK_END); // 移动文件的读写位置。读写指针 测得文件大小
    DLOG(INFO)<< " buf len "<<len<<endl;  //buf len 58888988 耗时0.37

    //使用mmap进行文件映射
    char* mbuf = (char*)mmap(nullptr,len,PROT_READ,MAP_PRIVATE,fd,0); //对于同一文件
    analyse(mbuf,len);
}


int main(int argc, char *argv[])  {

    string log_path;
    int log_level = 0;

    //初始化Glog
    common::InitGlog(argv);
    common::SetLogPath(log_path, log_level);

    //测试程序运行时间

    int start = clock();
//    readahead_analyse();
//    rand_write(); // 1.15
//    scanf_read();
//    cin_read();
//    fread_analyse();
    mmap_analyse();

/**
 * fread和mmap对于读取文件差别并不大
 */

    DLOG(INFO)<< "test io_optimization!" <<double(clock() - start)/CLOCKS_PER_SEC<<std::endl;
    return 0;
}
