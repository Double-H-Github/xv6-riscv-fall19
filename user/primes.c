#include "kernel/types.h"
#include "user/user.h"

void func (int *input, int prime){
    if(prime == 1){ //为1时退出
        printf("prime %d\n", *input);
        return;
    }
    int p[2];
    pipe(p);    //创建管道
    int current_prime = *input; //记住当前的值
    printf("prime %d\n", current_prime);    //每个进程打印一个数
    for (int i = 1; i < prime; i++){    //从当前的值后一个开始判断
        if (*(input + i) % current_prime != 0){ //判断是否为质数
            write(p[1],(char *)((input + i) ), 4);
        }
    }
    close(p[1]);    //关闭写通道
    if (fork() == 0){   //创建子进程
        int count = 0;
        char buffer[4];
        while (read(p[0], buffer, 4) != 0){ //从通道中读取
            *(input + count) = *((int *) buffer);
            count ++;
        }
        func(input, count); //递归
        exit();
    }
    wait();
}

void main(){
    int input[34];
    for(int i = 0; i < 34; i ++){
        input[i] = i + 2;
    } 
    func(input, 34);
    exit();
}