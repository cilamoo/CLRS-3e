#include <stdio.h>

/* return value */
typedef struct rt_val{
    int low;
    int high;
    int sum;
}rt_val;

void assign_rt_val(rt_val *p, int low, int high, int sum){
    p->low = low;
    p->high = high;
    p->sum = sum;
}

rt_val maximum_subarray_linear(int *A, int low, int high){
    rt_val tmp;
    int i,sum_extend,sum,max_left,max_right;

    sum = -999;
    sum_extend = 0;
    idx = 1;

    for(i = 1; i <= high; i++){
        sum_extend += A[i-1];
        if(sum_extend > sum){
            max_left = idx;
            max_right = i+1;
            sum = sum_extend;
        }

        if(sum_extend < 0){
            sum_extend = 0;
            idx = i + 1;
        }
    }

    assign_rt_val(&tmp,max_left,max_right,sum);
}

int main(){
    struct rt_val result;
    int A[16] = {13,-3,-25,20,-3,-16,-23,18,20,-7,12,-5,-22,15,-4,7};

    result = maximum_subarray_linear(A,1,16);
    printf("max subarray is: max_left = %d, max_right = %d, sum = %d\n", result.low, result.high, result.sum);

    return 0;
}