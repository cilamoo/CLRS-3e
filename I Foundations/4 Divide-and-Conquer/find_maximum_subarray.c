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

rt_val find_max_crossing_subarray(int *A, int low, int mid, int high){
    int i, j, left_sum, right_sum, sum, max_left, max_right;
    rt_val cross;

    left_sum = -999;
    sum = 0;
    for(i = mid; i >0; i--){
        sum += A[i-1];
        if(sum > left_sum){
            left_sum = sum;
            max_left = i;
        }
    }
    
    right_sum = -999;
    sum = 0;
    for(j = mid+1; j <= high; j++){
        sum += A[j-1];
        if(sum > right_sum){
            right_sum = sum;
            right_max = j;
        }
    }

    assign_rt_val(&cross,max_left,max_right,left_sum + right_sum);
    return cross;
}

rt_val find_maximum_subarray(int *A, int low, int high){
    rt_val tmp,left,right;
    int mid;

    if(low == high){
        assign_rt_val(&tmp,low,high,A[low]);
        return tmp;
    }
    else{
        mid = (low+hign)/2;
        left = find_maximum_subarray(A,low,mid);
        right = find_maximum_subarray(A,mid+1,high);
        cross = find_max_crossing_subarray(A,low,mid,high);

        if(left.sum >= right.sum && left.sum >= cross.sum)
            return left;
        else if(right.sum >= left.sum && right.sum >= cross.sum)
            return right;
        else
            return cross;
    }
}

int main(){
    struct rt_val result;
    int A[16] = {13,-3,-25,20,-3,-16,-23,18,20,-7,12,-5,-22,15,-4,7};

    result = find_maximum_subarray(A,1,16);
    printf("max subarray is: max_left = %d, max_right = %d, sum = %d\n", result.low, result.high, result.sum);

    return 0;
}

