#include <stdio.h>

// 求0 到 Size这个范围的素数的个数并打印出来这些素数
void SuNum(int Size){
    int i,j;
    int count;
    for(i = 2;i <= Size;i++){
        count = 0;
        for(j = 2;j <= i;j++){
            if(i%j==0){
                count++;
                if(count>1){
                    break;
                }
            }
        }
        if(count == 1){
            printf("%d\n",i);
        }
    }
}

int main(){
    SuNum(100);
}