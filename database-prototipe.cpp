#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct data{
	int number;
	char name[101];
	int balance;
	int height;
	data *left;
	data *right;
};

int getHeight(data *curr){
	if(curr==NULL) return 0;
	return curr->height;
}

int getBF(data *curr){
	if(curr==NULL) return 0;
	return getHeight(curr->left)-getHeight(curr->right);
}

int getMax(int a,int b){
	if(a>b)return a;
	return b;
}

data *rightRotate(data *C){
	data *B = C->left;
	data *x = B->right;
	B->right=C;
	C->left=x;
	C->height = getMax(getHeight(C->left),getHeight(C->right))+1;
	B->height = getMax(getHeight(B->left),getHeight(B->right))+1;
	return B;
}

data *leftRotate(data *A){
	data *B=A->right;
	data *y=B->left;	
	B->left=A;
	A->right=y;
	A->height = getMax(getHeight(A->left),getHeight(A->right))+1;
	B->height = getMax(getHeight(B->left),getHeight(B->right))+1;
	return B;
}

data *insert(data *curr,int number,char name[],int balance){
	if(curr==NULL){
		curr=(data*)malloc(sizeof(data));
		curr->number=number;
		strcpy(curr->name,name);
		curr->balance=balance;
		curr->height=1;
		curr->left=NULL;
		curr->right=NULL;
		return curr;
	}else if(number < curr->number){
		curr->left = insert(curr->left,number,name,balance);
	}else{
		curr->right = insert(curr->right,number,name,balance);
	}
	curr->height = getMax(getHeight(curr->left),getHeight(curr->right))+1;
	int BF = getBF(curr);
	if(BF>1&&number<curr->left->number){
		return rightRotate(curr);
	}
	if(BF<-1&&number>curr->right->number){
		return leftRotate(curr);
	}
	if(BF>1&&number>curr->left->number){
		curr->left=leftRotate(curr->left);
		return rightRotate(curr);
	}
	if(BF<-1&&number<curr->right->number){
		curr->right=rightRotate(curr->right);
		return leftRotate(curr);
	}
	return curr;
}

data *predecessor(data *curr){
	data *temp = curr->left;
	while(temp->right!=NULL){
		temp=temp->right;
	}
	return temp;
}

data *deleteNode(data *curr,int number){
	if(curr==NULL)return NULL;
	if(number<curr->number){
		curr->left = deleteNode(curr->left,number);
	}else if(number>curr->number){
		curr->right = deleteNode(curr->right,number);
	}else{
		if(curr->left==NULL||curr->right==NULL){
			data *temp=NULL;
			if(curr->left!=NULL)temp=curr->left;
			else temp=curr->right;
			
			if(temp==NULL){
				temp=curr;
				curr=NULL;
			}else{
				*curr=*temp;
			}
			free(temp);
		}
		else{
			data *temp = predecessor(curr);
			curr->number = temp->number;
			curr->left = deleteNode(curr->left,temp->number);
		}
	}
	if(curr==NULL)return curr;
	curr->height = getMax(getHeight(curr->left),getHeight(curr->right))+1;
	int BF = getBF(curr);
	if(BF>1&&getBF(curr->left)>=0){
		return rightRotate(curr);
	}
	if(BF<-1&&getBF(curr->right)<=0){
		return leftRotate(curr);
	}
	if(BF>1&&getBF(curr->left)<0){
		curr->left = leftRotate(curr->left);
		return rightRotate(curr);
	}
	if(BF<-1&&getBF(curr->right)>0){
		curr->right=rightRotate(curr->right);
		return leftRotate(curr);
	}
	return curr;
}

void inOrder(data *curr){
	if(curr==NULL)return;
	inOrder(curr->left);
	printf("Account Number : %d\n",curr->number);
	printf("Customer Name : %s\n",curr->name);
	printf("Balance : %d\n\n",curr->balance);
	inOrder(curr->right);
}

int isExist(data *curr, int number){
	if(curr == NULL){
		return 0;
	}else if(curr->number > number){
		return isExist(curr->left, number);
	}else if(curr->number < number){
		return isExist(curr->right, number);
	}else if(curr->number == number){
		return 1;
	}
}

int balancee(data *curr, int number){
	if(curr == NULL){
		return 0;
	}else if(curr->number > number){
		return balancee(curr->left, number);
	}else if(curr->number < number){
		return balancee(curr->right, number);
	}else if(curr->number == number){
		return curr->balance;
	}
}

char* namee(data *curr, int number){
	if(curr == NULL){
		return 0;
	}else if(curr->number > number){
		return namee(curr->left, number);
	}else if(curr->number < number){
		return namee(curr->right, number);
	}else if(curr->number == number){
		return curr->name;
	}
}

data *tambahBalance(data *curr, int number, int balance){
	if(curr == NULL){
		return 0;
	}else if(curr->number > number){
		curr->left = tambahBalance(curr->left, number, balance);
	}else if(curr->number < number){
		curr->right = tambahBalance(curr->right, number, balance);
	}else if(curr->number == number){
		curr->balance+=balance;
		return curr;
	}
}

data *kurangBalance(data *curr, int number, int balance){
	if(curr == NULL){
		return 0;
	}else if(curr->number > number){
		curr->left = kurangBalance(curr->left, number, balance);
	}else if(curr->number < number){
		curr->right = kurangBalance(curr->right, number, balance);
	}else if(curr->number == number){
			curr->balance-=balance;
			return curr;
	}
}

int main(){
	int pilih=0;
	data *root = NULL;
	do{
	int number=0;
	char name[101];
	int balance=0;
		do{
		printf("HOVBank Database Prototype\n");
		printf("==========================\n");
		printf("[1] Show All Account\n");
		printf("[2] Register a New Account\n");
		printf("[3] Remove an Existing Account\n");
		printf("[4] Deposit to an Account\n");
		printf("[5] Withdraw from an Account\n");
		printf("[6] Exit and Purge All Data\n");
		printf(">> ");
		scanf("%d", &pilih);
		}while(pilih<1||pilih>6);
		switch(pilih){
			case 1:{
				inOrder(root);
				printf("Press ENTER to continue...\n");
				getchar();
				getchar();
				break;
			}
			case 2:{
				do{
					printf("Input account number [8 digits]        : ");
					scanf("%d", &number);
					getchar();
					fflush(stdin);
				}while(number<10000000);
				do{
					printf("Input account name [1 - 100 characters]: ");
					scanf("%[^\n]", name);
				}while(strlen(name)<1||strlen(name)>100);
				do{
					printf("Input account initial balance          : ");
					scanf("%d", &balance);
					fflush(stdin);
				}while(balance<=0);
				printf("Account [%d (%s)] was registered successfully.\n", number, name);
				root = insert(root,number,name,balance);
				printf("Press ENTER to continue...\n");
				getchar();
				break;
			}
			case 3:{
				do{
					printf("Input account number [8 digits]: ");
					scanf("%d",&number);
					fflush(stdin);
				}while(number<10000000);
				int temp = isExist(root,number);
				if(temp==1){
					printf("Account with number [%d(%s)] was removed successfully!\n",number,namee(root,number));
					root = deleteNode(root, number);
				}
				else{
					printf("Account with number [%d] was not found.\n",number);
				}
					printf("Press ENTER to continue...\n");
					getchar();
				break;
			}
			case 4:{
				do{
					printf("Input account number [8 digits]: ");
					scanf("%d",&number);
					fflush(stdin);
				}while(number<10000000);
				do{
					printf("Input nominal to deposit : ");
					scanf("%d",&balance);
					fflush(stdin);
				}while(balance<=0);
				int temp2 = isExist(root, number);
				if(temp2==1){
					int temp3 = balancee(root,number);
					printf("Account with number [%d (%s)] was found.\n",number,namee(root,number));
					printf("Previous balance: %d\n",temp3);
					printf("New balance: %d\n\n",temp3+balance);
					root = tambahBalance(root,number,balance);
				}
				else{
					printf("Account with number [%d] was not found.\n",number);
				}
					printf("Press ENTER to continue...\n");
					getchar();
				break;
			}
			case 5:{
				do{
					printf("Input account number [8 digits]: ");
					scanf("%d",&number);
					fflush(stdin);
				}while(number<10000000);
				do{
					printf("Input nominal to deposit : ");
					scanf("%d",&balance);
					fflush(stdin);
				}while(balance<=0);
				int temp2 = isExist(root, number);
				if(temp2==1){
					int temp3 = balancee(root,number);
					printf("Account with number [%d(%s)] was found.\n",number,namee(root,number));
					printf("Previous balance: %d\n",temp3);
					if((temp3-balance)<0){
						printf("Fail to withdraw, not enough balance\n");
					}
					else{
						printf("New balance: %d\n\n",temp3-balance);
						root = kurangBalance(root,number,balance);
					}
				}
				else{
					printf("Account with number [%d] was not found.\n",number);
				}
					printf("Press ENTER to continue...\n");
					getchar();
				break;
			}
			case 6:{
				printf("All data was removed succesfully.\n\n");
				printf("Press ENTER to continue...\n");
				getchar();
				getchar();
				break;
			}
		}
	}while(pilih!=6);
	
	return 0;
}
