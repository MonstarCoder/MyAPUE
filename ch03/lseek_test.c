//测试标准输入能否被设置偏移量
#include "../apue.3e/include/apue.h"
 int main()
{
    if (lseek(STDIN_FILENO, 0, SEEK_CUR) == -1)
        printf("cannot seek\n");
    else
        printf("seek OK\n");
    exit(0);
}
