#include<stdio.h>
#include<stdlib.h>
#define p(x) printf("%d", x)
#define px(x,s) printf("%d%s", x,s)
#define pf(x) printf("%f\n", x)
#define ps(x) printf("%s", x)
#define s(x) scanf("%d", &x)
int main(void){
int m,n;
s(m),s(n);
int **matrix = (int **)malloc(m*sizeof(int*));
if(matrix==NULL){
    fprintf(stderr,"memory allocation failed");
    return 1;
}
for(int **i=matrix;i<(matrix+m);i++){
*i = (int *)(malloc(n*sizeof(int)));
if(*matrix==NULL){
    fprintf(stderr,"memory allocation failed");
    return 1;
}
}
for(int **i=matrix;i<(matrix+m);i++){
    for(int *j=*i;j<(*i+n);j++){
        *j=rand();
    }
}
for(int **i=matrix;i<(matrix+m);i++){
    for(int *j=*i;j<(*i+n);j++){
        p(*j);ps(" ");
    }
    ps("\n");
}
for(int **i=matrix;i<(matrix+m);i++){
    free(*i);
}
free(matrix);

return 0;
}