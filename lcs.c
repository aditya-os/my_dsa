int find_lcs(char *A,char*B,int n){
    int lcs[5000+1]={0,};
    int prev=0,temp,i,j;
    for(i = 0 ; i < n ; i++){
        prev = 0 ; 
        for(j = 0 ; j < n ;j++){
            temp = lcs[j];
            if (A[i] == B[j]){
                lcs[j] = prev + 1;
            }
            else{
                lcs[j] = max(lcs[j], (j?lcs[j-1]: 0) ) ;
            }
            prev = temp;
        }
    }
    return lcs[n-1];
}
