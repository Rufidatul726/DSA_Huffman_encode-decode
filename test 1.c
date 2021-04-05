#include <stdio.h>
#include <stdlib.h>
#include<string.h>

#define MAX_TREE_HT 1000

char strrr[100];
int strr[1000][15]={0};
int count=0,count1[100]={0};

struct MinHeapNode {
	char data;
	unsigned freq;
	struct MinHeapNode *left, *right;
};

struct MinHeap {
	unsigned size;
	unsigned capacity;
	struct MinHeapNode** array;
};

struct MinHeapNode* newNode(char data, unsigned freq){
	struct MinHeapNode* temp = (struct MinHeapNode*)malloc(sizeof(struct MinHeapNode));

	temp->left = temp->right = NULL;
	temp->data = data;
	temp->freq = freq;

	return temp;
}

struct MinHeap* createMinHeap(unsigned capacity){
	struct MinHeap* minHeap= (struct MinHeap*)malloc(sizeof(struct MinHeap));

	minHeap->size = 0;

	minHeap->capacity = capacity;

	minHeap->array = (struct MinHeapNode**)malloc(minHeap->capacity * sizeof(struct MinHeapNode*));
	return minHeap;
}


void EncodedData(char data, int freq[], int size){
        int i;
        for(i=0;i<size;i++){
                strr[count][i]=freq[i];
        }
        count1[count]=i;
        strrr[count]=data;
        count++;
}

void swapMinHeapNode(struct MinHeapNode** a, struct MinHeapNode** b){
	struct MinHeapNode* t = *a;
	*a = *b;
	*b = t;
}

void minHeapify(struct MinHeap* minHeap, int idx){

	int smallest = idx;
	int left = 2 * idx + 1;
	int right = 2 * idx + 2;

	if (left < minHeap->size && minHeap->array[left]->freq< minHeap->array[smallest]->freq)smallest = left;

	if (right < minHeap->size&& minHeap->array[right]->freq< minHeap->array[smallest]->freq)smallest = right;

	if (smallest != idx) {
	    swapMinHeapNode(&minHeap->array[smallest],&minHeap->array[idx]);
            minHeapify(minHeap, smallest);
	}
}

int isSizeOne(struct MinHeap* minHeap){
	return (minHeap->size == 1);
}

struct MinHeapNode* extractMin(struct MinHeap* minHeap){

	struct MinHeapNode* temp = minHeap->array[0];
	minHeap->array[0] = minHeap->array[minHeap->size - 1];

	--minHeap->size;
	minHeapify(minHeap, 0);

	return temp;
}


void insertMinHeap(struct MinHeap* minHeap,struct MinHeapNode* minHeapNode){
	++minHeap->size;
	int i = minHeap->size - 1;

	while (i && minHeapNode->freq< minHeap->array[(i - 1) / 2]->freq) {
		minHeap->array[i] = minHeap->array[(i - 1) / 2];
		i = (i - 1) / 2;
	}

	minHeap->array[i] = minHeapNode;
}


void buildMinHeap(struct MinHeap* minHeap){

	int n = minHeap->size - 1;
	int i;

	for (i = (n - 1) / 2; i >= 0; --i)minHeapify(minHeap, i);
}

void printArr(int arr[], int n){
	int i;
	for (i = 0; i < n; ++i)printf("%d", arr[i]);

	printf("\n");
}

int isLeaf(struct MinHeapNode* root){
	return !(root->left) && !(root->right);
}

struct MinHeap* createAndBuildMinHeap(char data[],int freq[], int size){

	struct MinHeap* minHeap = createMinHeap(size);

	for (int i = 0; i < size; ++i)
		minHeap->array[i] = newNode(data[i], freq[i]);

	minHeap->size = size;
	buildMinHeap(minHeap);

	return minHeap;
}

struct MinHeapNode* buildHuffmanTree(char data[],int freq[], int size){
	struct MinHeapNode *left, *right, *top;

	struct MinHeap* minHeap= createAndBuildMinHeap(data, freq, size);

	while (!isSizeOne(minHeap)) {
		left = extractMin(minHeap);
		right = extractMin(minHeap);

		top = newNode('$', left->freq + right->freq);

		top->left = left;
		top->right = right;

		insertMinHeap(minHeap, top);
	}
	return extractMin(minHeap);
}


void printCodes(struct MinHeapNode* root, int arr[],int top){
	if (root->left) {

		arr[top] = 0;
		printCodes(root->left, arr, top + 1);
	}
	if (root->right) {
        arr[top] = 1;
		printCodes(root->right, arr, top + 1);
	}

	if (isLeaf(root)) {

		printf("%c: ", root->data);
		printArr(arr, top);
		EncodedData(root->data, arr, top);
	}
}


void HuffmanCodes(char data[], int freq[], int size){
	struct MinHeapNode* root= buildHuffmanTree(data, freq, size);

	int arr[MAX_TREE_HT], top = 0;

	printCodes(root, arr, top);
}

int search(char str){
    int i;
    for(i=0;i<count;i++){
        if(str==strrr[i])return i;
    }

}


void decoder(int a[], int size){
    int j=0,n=0;
    for(int i=0;i<size;i++){
             j=0;
            n=0;
            while(j<count1[n]){
                    if(a[i]!=strr[n][j]){n++;}
                    if(a[i]==strr[n][j] && j!=count1[n]-1){i++;j++;}
                    if(a[i]==strr[n][j] && j==count1[n]-1){
                       printf("%c",strrr[n]);
                       break;
                    }
            }
    }
}


int main(){
   char s[1000],string[1000],str[1000];
    int a1[1000][2],a[1000];
  //entering input

   FILE *fptr;

   fptr = fopen("F:\\Sumon sir\\Assignment huffman coding\\test.txt","r");

    if(fptr == NULL){
      printf("Error! Try again. ");
      return 0;
   }

   fgets(string,sizeof(string),fptr);
    printf("%s",string);
   fclose(fptr);

    //frequency counting

   int i, length,j=0;
   int frequency[100]={0};

   length = strlen(string);

   for(i=0; i<length; i++){
        frequency[string[i] - 32]++;
   }

   printf("\nFrequency of all characters in string: \n");
   for(i=0; i<100; i++)
      if(frequency[i] != 0){
            str[j]=32+i;
            printf("'%c' = %d\n", str[j], frequency[i]);
            frequency[j++]=frequency[i];
      }
    str[j]='\0';
   int size=strlen(str),k=0;

    //encoding code:
    printf("\nThe encrypted code of each Character is:\n");
    HuffmanCodes(str, frequency, size);
    int p=0;


    //Encoded coded:
    printf("The Encoded code is:\n");
    for(i=0;i<strlen(string);i++){
        int n= search(string[i]);

        for(k=0;k<count1[n];k++){
            printf("%d",strr[n][k]);
            a[p++]=strr[n][k];
        }
    }

    //now encrypted code is a;
    printf("\nThe Decoded code:\n");
    decoder(a ,p);



   return 0;
}

