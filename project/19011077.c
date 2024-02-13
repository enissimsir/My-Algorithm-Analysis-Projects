#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void backtrack(int N, int A[N][N], int satir, char Renkler[N][20]);
void shift(int N, int A[N]);
void yazdir(int N, int A[N][N], char Renkler[N][20]);
void backtrackDetayModu(int N, int A[N][N], int satir, char Renkler[N][20]);

int main(int argc, char *argv[]) {
	int mod;
	printf("Oncelikle mod secelim. Normal icin 1, detay icin 2: "); scanf("%d",&mod);
	int i,j,k,N;
	printf("Programima hosgeldiniz\nHer renkten her satirda bir tane olacak sekilde degerleri girerseniz her sutunda da bir tane olacak sekilde shiftlerim\nEger hicbir sey listelemezsem girdiginiz matriste boyle bir duzen mumkun degil demektir\n\n");
	printf("N degeri: "); scanf("%d",&N);
	printf("Lutfen renk matrisini giriniz\n");
	char A[N][N][20];
	for(i=0;i<N;i++){
		for(j=0;j<N;j++){
			printf("%d,%d: ",i,j); scanf("%s",&A[i][j]);
		}
	}
	int B[N][N];
	for(i=0;i<N;i++){
		B[0][i]=i;
	}
	for(i=1;i<N;i++){
		for(j=0;j<N;j++){
			for(k=0;k<N;k++){
				if(strcmp(A[i][j],A[0][k])==0){
					B[i][j]=k;
				}
			}
		}
	}

	if(mod==1){
		backtrack(N,B,1,A[0]);
	}
	else if(mod==2){
		backtrackDetayModu(N,B,1,A[0]);
	}
	
	
	return 0;
}

void backtrack(int N, int A[N][N], int satir, char Renkler[N][20]){
	int i,j,k,flag;
	for(i=0;i<N;i++){
		flag=0;
		for(j=satir-1;j>=0;j--){
			for(k=0;k<N;k++){
				if(A[j][k]==A[satir][k])
					flag=1;
			}
		}
		if(flag==0){
			if(satir<N-1){
				backtrack(N,A,satir+1,Renkler);
			}
			else{
				yazdir(N,A,Renkler);
			}
		}
		shift(N,A[satir]);
	}
}

void backtrackDetayModu(int N, int A[N][N], int satir, char Renkler[N][20]){
	int i,j,k,flag;
	for(i=0;i<N;i++){
		flag=0;
		for(j=satir-1;j>=0;j--){
			for(k=0;k<N;k++){
				if(A[j][k]==A[satir][k])
					flag=1;
			}
		}
		if(flag==0){
			if(satir<N-1){
				backtrack(N,A,satir+1,Renkler);
			}
			else{
				printf("\n\nSonuc bulundu:");
				yazdir(N,A,Renkler);
			}
		}
		shift(N,A[satir]);
		printf("\n\nShift islemi yapildi:");
		yazdir(N,A,Renkler);
	}
}

void shift(int N, int A[N]){
	int i,temp=A[N-1];
    for(i=N-1;i>0;i--)
    {
        A[i]=A[i-1];
    }
    A[0]=temp;
}

void yazdir(int N, int A[N][N], char Renkler[N][20]){
	int i,j;
	printf("\n\n");
	for(i=0;i<N;i++){
		for(j=0;j<N;j++){
			printf("%s\t",Renkler[A[i][j]]);
		}
		printf("\n");
	}
}
