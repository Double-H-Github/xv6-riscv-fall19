#include <kernel/types.h>
#include <user/user.h>

int main(){
     int parent_p1[2],child_p2[2];//创建两个管道
     char buffer1[] = {'p','i','n','g'};
     char buffer2[] = {'p','o','n','g'};
     int length1 = sizeof( buffer1 );
     int length2 = sizeof( buffer2 );
     pipe(parent_p1);//父进程写，子进程读
     pipe(child_p2);//子进程写，父进程读
     if(fork() == 0){
        close(parent_p1[1]);
        close(child_p2[0]);

        if(read(parent_p1[0],buffer1,length1) != length1){
            printf("a-->b,read error!");
            exit();
        }

        printf("%d: received %s\n",getpid(),buffer1);

        if(write(child_p2[1],buffer2, length2) != length2){
            printf("a<--b, write error");
            exit();
        }
        exit();
     }
     close(parent_p1[0]);
     close(child_p2[1]);

     if(write(parent_p1[1],buffer1, length1) != length1){
        printf("a-->b, write error");
        exit();
     }

     if(read(child_p2[0],buffer2,length2) != length2){
        printf("a<--b,read error!");
        exit();
     }

     printf("%d: received %s\n", getpid(),buffer2);

     wait();
     exit();
}
