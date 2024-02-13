#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct hash {
	struct node *head;
	int count;
};

struct node{
	int key;
	char name[40];
	struct node *next;
};

struct hash *hashTable=NULL;
struct node* createNode(int key, char name[]);
void insertToHash(int key,char name[],int M);
int Horner(char name[],int M);
int main(int argc, char *argv[]) {
	int M=101;
	char kelime[40];
	hashTable=(struct hash*) calloc (M,sizeof(struct head));
	if(hashTable==NULL){
		printf("not enough memory");
		exit(0);
	}
	int flag=0;
	int key;
	FILE *dosya;
	while(fgets(kelime,40,fp)!=NULL){
		if(flag%2==1){
			key=Horner(kelime,M);
			insertToHast(key,kelime,M);
		}
		flag++;
	}
	fclose(dosya);
	
	return 0;
}

void insertToHash(int key,char name[],int M){
	int hashIndex=key%M;
	struct node *newNode = createNode(key,name);
	if(!hashTable[hashIndex].head){
		hashTable[hashIndex].head = newNode;
		hashTable[hashIndex].count = 1;
		return;
	}
	newNode->next=hashTable[hashIndex].head;
	hashTable[hashIndex].head=newNode;
	hashTable[hashIndex].count++;
	return;
}

struct node* createNode(int key, char name[]){
	struct node* newNode;
	struct node* newNode=(struct node*)malloc(sizeof(struct node));
	newNode->key = key;
	strcpy(newNode->name,name);
}

int Horner(char name[],int M){
	int i, sonuc=0;
	int length = sizeof(name)/sizeof(name[0]);
	for(i=0;i<uzunluk;i++){
		sonuc+=name[i]*pow(31,uzunluk-i-1);
	}
	return sonuc;
}
