#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int commaNumber(char line[25]);
void mEleme(int A[20][20],int M,int satir,char Names[20][20],int in_degree[20]);
void yazdir(int A[20][20],char Names[20][20],int satir);
void DFS(int v, int A[20][20],int satir,int visited[20];);



int main(int argc, char *argv[]) {
	int mod,i,j,M=1,X=2,Y=4;
	printf("M degeri: ");
	scanf("%d",&M);
	printf("X degeri: ");
	scanf("%d",&X);
	printf("Y degeri: ");
	scanf("%d",&Y);
	
	printf("Normal mod icin 1'e, detay mod icin 2'ye basiniz: ");
	scanf("%d",&mod);
	int A[20][20];
	char Names[20][20];
	char surNames[20][20];
	int visited[20][20];
	int in_degree[20];
	for(i=0;i<20;i++){
		in_degree[20]=0;
		for(j=0;j<20;j++){
			A[i][j]=0;
			visited[i][j]=0;
		}
	}
	//dosyadan okuma yapiyoruz (en fazla 20 karakterli dosya olabilir)
	FILE *fp = fopen("socialNET.txt", "r");
    const char s[1] = ",";
    char *token;
    int cn, satir=1;//satir degiskeni dosyanin kacinci satirinda oldugumuzu, cn ise virgul sayisini tutacak
    if(fp != NULL){
		char line[40];
		while(fgets(line, sizeof line, fp) != NULL)
    	{
			cn=commaNumber(line);//fonksiyon yardimiyla virgul sayisi cn'ye atandi
			token = strtok(line, s);//kacinci satirda oldugumuz token'e char olarak atandi
			if(satir%2==1){//tek sayiysa isimleri almamiz lazim
				strcpy(Names[atoi(token)],strtok(NULL,s)); //satir bilgisi 1'den basladigindan, Names ve surNames dizilerine 1. adreslerinden itibaren yerlestiriyoruz
				strcpy(surNames[atoi(token)],strtok(NULL,s));
			}
			else{
				for(i=0;i<=cn;i++){//virguller arasinda kalan bolgeleri ayiriyoruz
     				if(i!=cn){//son bolgede degilsek
						A[satir/2-1][atoi(token)-1]=1;
						token = strtok(NULL,s);
					}
					else {//son bolgedeysek (daha kesme yapmiyoruz)
        				A[satir/2-1][atoi(token)-1]=1;
					}
				}
			}
			satir++;
		}
		fclose(fp);
	}else{
		perror("socialNET.txt");
	}
	if(mod==2){
		printf("\nBaslangictaki in degree degerleri:\n\n");
		int counter;
		for(j=0;j<satir/2;j++){
			counter=0;
			for(i=0;i<satir/2;i++){
				counter+=A[i][j];
			}
			printf("%d. dugum in degree degeri: %d\n",j+1,counter);
		}
	}
	int total_degree[20];//bu degisken her karakterin toplam in degree sayisini tutacak (dogrudan ve dolayli)
	for(i=0;i<20;i++){
		total_degree[i]=0;
	}
	
	int Tmp[20][20];//asil diziyi kaybetmek istemedigimden islemleri Tmp'de yapacagim
	for(i=0;i<20;i++){
		for(j=0;j<20;j++){
			Tmp[i][j]=A[i][j];
		}
	}

	mEleme(Tmp,M,satir/2,Names,in_degree);//M'den az in degreesi olanlari eliyoruz
	
	if(mod==2){
		printf("\nEleme sonrasi:\n\n");
		for(i=0;i<satir/2;i++){
			printf("%d. dugum in degree degeri: %d\n",i+1,in_degree[i]);
		}
		printf("\n\n");
	}
	
	//Burada ise bir karaktere gelen dogrudan veya dolayli karakterlerin toplam sayisini bulup total_degree'ye atayacagiz
	for(i=0;i<satir/2;i++){
		DFS(i,Tmp,satir/2,visited[i]);//visited 2 boyutlu bir dizi ama her karakter icin bir satiri kullaniliyor
	}
	
	for(i=0;i<satir/2;i++){
		for(j=0;j<satir/2;j++){
			total_degree[j]+=visited[i][j];//eger baglanti varsa visited 1 oluyor, bu sayede visited degerlerini toplamak toplam baglantiyi verir
		}
	}
	
	printf("Influencer olanlar:\n\n");
	if(mod==1){
		for(i=0;i<satir/2;i++){
			if(in_degree[i]>=X && total_degree[i]>=Y){//istenen kosullar saglaniyorsa yazdiriyoruz
				printf("%d numarali %s %s\n",i+1,Names[i+1],surNames[i+1]);
			}
		}
	}
	else if(mod==2){
		for(i=0;i<satir/2;i++){
			if(in_degree[i]>=X && total_degree[i]>=Y){//istenen kosullar saglaniyorsa yazdiriyoruz
				printf("%d numarali %s %s (in degree degeri: %d  dogrudan veya dolayli toplam in degree degeri: %d)\n\n",i+1,Names[i+1],surNames[i+1],in_degree[i],total_degree[i]);
			}
		}
	}
	return 0;
}

void DFS(int v, int A[20][20],int satir,int visited[20]){
	int i;
	visited[v] = 1;
	for(i=0;i<satir;i++){
		if (A[v][i]==1 && visited[i]==0){
			DFS(i,A,satir,visited);
		}
	}
}

void mEleme(int A[20][20],int M,int satir,char Names[20][20],int in_degree[20]){//in degree degerleri hesaplanip M'den kucuk olanlari eler
	//counter, in degree degerini tutmak icin. counter2 ise eleme isleminin tamamlanip tammalanmadigini kontol etmek icin
	int i,j,k,counter=0,flag=1,counter2=1;
	while(flag==1){
		flag=0;
		counter2=1;
		for(j=0;j<satir;j++){//takipci sayisini ogrenmek icin sutundaki sayilari toplayacagim. o yuzden ilk for j ile donuyor
			counter=0;
			for(i=0;i<satir;i++){
				counter+=A[i][j];//sutundaki 1'leri toplayarak toplam in degree sayisini ogreniyorum
			}
			if(counter<M){//eleme yapiyoruz
				flag=1;
				for(i=0;i<satir;i++){
					A[j][i]=0;
					A[i][j]=0;
				}
				in_degree[j]=0;
			}
			else{
				in_degree[j]=counter;//eleme yoksa in_degree degerini daha sonrasi icin kaydediyoruz
				counter2++;//bastan sona eleme olmazsa counter2 satir sayisina esit olacak
			}
		}
		if(counter2==satir){//hiz eleme olamdiysa flag'i 0 yapiyoruz
			flag=0;
		}
	}
}

int commaNumber(char line[40]){//toplam virgul sayisini hesapliyor
	int i=0;
	int counter=0;
	while(line[i]!='\0'){
		if(line[i]==',') counter++;
		i++;
	}
	return counter;
}

void yazdir(int A[20][20],char Names[20][20],int satir){//diziyi yazdirmak icin. kodu yazarken kontorl amacli kullandim
	int i,j;
	printf("\nA yazdir:\n");
	for(i=0;i<satir;i++){
		printf("%d:\t",i+1);
		for(j=0;j<satir;j++){
			printf("%d\t",A[i][j]);
		}
		printf("\n");
	}
	printf("\nNames yazdir:\n");
	for(i=1;i<=satir;i++){
		printf("%s ",Names[i]);
	}
}
