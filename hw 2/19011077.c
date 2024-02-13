#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int divide(int A[], int low, int high,int *first, int *last);
int maximum(int a, int b);

int main(int argc, char *argv[]) {
	int N, k, secim;
	printf("maden boyu: ");
	scanf("%d",&N);
	int A[N];
	for(k=0;k<N;k++){
		printf("%d. deger: ",k);
		scanf("%d",&A[k]);
	}
	printf("Brute Force icin 1'e, Divide and Conquer icin 2'ye basin: ");
	scanf("%d",&secim);
	if(secim==1){
		int i, j, sum, max_i, max_j, max=0;
	// olabilecek her tür i ve j kombinasyonlarina bakiyoruz
		for(i=0;i<N-1;i++){
			for(j=i+1;j<N;j++){
				sum=0;
				// her kombinasyon icin toplam degeri buluyoruz
				for(k=i;k<=j;k++){
					sum+=A[k];
				}
				// en buyun kombinasyonu seciyoruz
				if(sum>max){
					max=sum;
					max_i=i;
					max_j=j;
				}
			}
		}
	
		printf("max kazanc: %d\nkazilmasi gerekilen blok butunlugu: %d-%d",max,max_i,max_j);
	
		return 0;
	}
	else{
		int i, j;
		int sonuc = divide(A, 0, N - 1, &i, &j);
		printf("en kazancli sonuc: %d\n%d ile %d arasi",sonuc,i,j);
		return 0;
	}
}

int divide(int A[], int low, int high,int *first, int *last){
	//bolum kisminda tek bir deger mi kaldi kontrolu
	if (high <= low){
        return A[low];
    }
	int mid = (low + high) / 2;
	int maxLeft = -21000000;
	int maxRight = -21000000;
	int i, tmpFirst, tmpLast;
	int sum=0;
// dizinin soluna bakiyoruz
	for (i = mid; i >= low; i--){
        sum += A[i];
        if (sum > maxLeft) {
            maxLeft = sum;
            tmpFirst = i;
        }
    }
    sum=0;
// dizinin sagina bakiyoruz
    for (i = mid + 1; i <= high; i++){
        sum += A[i];
        if (sum > maxRight) {
            maxRight = sum;
            tmpLast = i;
        }
    }
    // burada recursive olarak dizinin once soluna sonra sagina bakiyoruz
    // ve fonksiyona her girdiginde ayni kontrol devam ediyor ta ki tek bir eleman kalana kadar
    int maxAll = maximum(divide(A, low, mid, first, last), divide(A, mid + 1, high, first, last));
    // en buyuk deger saginda ya da solunda ise bu if'e giriyor
    if(maxAll>maxLeft + maxRight){
    	return maxAll;
	}
	// degilse buna giriyor. ayrica first ve last pointerlari da indisleri tutmak icin
	// en buyuk deger orta noktanin saginda ya da solunda da olsa dizi surekli bolundugu icin
	// bir noktada dizinin ortasina denk gelecek o yuzden bu kisma illa ki girecek
	else{
		*first = tmpFirst;
		*last = tmpLast;
		return maxLeft + maxRight;
	}
}

int maximum(int a, int b){
	if(a>b)	return a;
	return b;	
}
