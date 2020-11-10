#include<stdio.h>
#include<stdlib.h>
#include<time.h>

struct Tree{
	int b;
	int data;
};
int knowHeight(struct Tree tree[],int i);
void creator(struct Tree tree[],int i,int j){
	if(tree[i].data!=0){
		tree[j].data=tree[i].data;
		tree[i].data=0;
		creator(tree,2*i+1,2*j+1);
		creator(tree,2*i+2,2*j+2);
	} 
}
void shiftRightDown(struct Tree tree[],int i,int p){
	int j=i,k=(i-2)/2;
	while(tree[j].data!=0){
		k=j;
		j=j*2+2;
	}
	while(k!=p){
		tree[j].data=tree[k].data;
		creator(tree,2*k+1,2*j+1);
		k=(k-2)/2;
		j=(j-2)/2;
	}
	tree[j].data=tree[k].data;
}
void shiftLeftUp(struct Tree tree[],int i){
	int j=i*2+1;
	while(tree[j].data!=0){
		tree[i].data=tree[j].data;
		creator(tree,j*2+2,i*2+2);
		j=j*2+1;
		i=i*2+1;
	}
	tree[i].data=0;
}
void llRotate(struct Tree tree[],int p,int s){
	int temp=2*p+2;
	shiftRightDown(tree,2*p+2,p);
	creator(tree,s*2+2,temp*2+1);
	tree[p].data=tree[s].data;
	shiftLeftUp(tree,s);
}
void shiftLeftDown(struct Tree tree[],int i,int p){
	int j=i,k=i/2;
	while(tree[j].data!=0){
		k=j;
		j=j*2+1;
	}
	while(k!=p){
		tree[j].data=tree[k].data;
		creator(tree,k*2+2,j*2+2);
		j=j/2;
		k=k/2;
	}
	tree[j].data=tree[k].data;
}
void shiftRightUp(struct Tree tree[],int i){
	int j=i*2+2;
	while(tree[j].data!=0){
		tree[i].data=tree[j].data;
		creator(tree,j*2+1,i*2+1);
		j=j*2+2;
		i=i*2+2;
	}
	tree[i].data=0;
}
void rrRotate(struct Tree tree[],int p,int s){
	int temp=2*p+1;
	shiftLeftDown(tree,p*2+1,p);
	creator(tree,s*2+1,temp*2+2);
	tree[p].data=tree[s].data;
	shiftRightUp(tree,s);
}
void rlRotate(struct Tree tree[],int p,int s){
	llRotate(tree,s,s*2+1);
	rrRotate(tree,p,s);
}
void lrRotate(struct Tree tree[],int p,int s){
	rrRotate(tree,s,s*2+2);
	llRotate(tree,p,s);
}
int knowBalance(struct Tree tree[],int left,int right){
	int a,b;
	a=knowHeight(tree,left);
	b=knowHeight(tree,right);
	return a-b;
}
int maxim(int a,int b){
	return a>b?a:b;
}
void reBalance(struct Tree tree[],int i,int fix){
	int j,bal,rbal,temp;
	int a,b;
	if(i!=0){
	if(i%2==0){
		j=(i-2)/2;
	} else {
		j=i/2;
	}
	bal=knowBalance(tree,j*2+1,j*2+2);
	tree[j].b=bal;
	if(bal<2&&bal>-2){
		reBalance(tree,j,fix);
	} else {
		if(fix>tree[j].data){
			temp=j*2+1;
			rbal=knowBalance(tree,temp*2+1,temp*2+2);
			if(rbal==0){
				llRotate(tree,j,temp);
			} else if(rbal==1){
				llRotate(tree,j,temp);
			} else if(rbal==-1){
				lrRotate(tree,j,temp);
			}
		} else if(fix<tree[j].data){
			temp=j*2+2;
			rbal=knowBalance(tree,temp*2+1,temp*2+2);
			if(rbal==0){
				rrRotate(tree,j,temp);
			} else if(rbal==-1){
				rrRotate(tree,j,temp);
			} else if(rbal==1){
				rlRotate(tree,j,temp);
			}
		}
	}
}
}
void balance(struct Tree tree[],int i,int fix){
	int j,bal;
	int a,b;
	if(i!=0){
	if(i%2==0){
		j=(i-2)/2;
	} else {
		j=i/2;
	}
	bal=knowBalance(tree,j*2+1,j*2+2);
	tree[j].b=bal;
	if(bal<2&&bal>-2){
		balance(tree,j,fix);
	} else {
		if(i%2==0){
			if(tree[fix].data>tree[i].data){
				rrRotate(tree,j,i);
			} else{
				rlRotate(tree,j,i);
			}
		} else {
			if(tree[fix].data<tree[i].data){
				llRotate(tree,j,i);
			} else {
				lrRotate(tree,j,i);
			}
			
		}
	}
}
}
int findSuccessor(struct Tree tree[],int i){
	if(tree[i*2+1].data!=0){
		findSuccessor(tree,i*2+1);
	}
	return i;
}
int delete(struct Tree tree[],int i,int item){
	int temp,j;
	int s;
	if(tree[i].data!=0){
		if(tree[i].data>item){
			delete(tree,i*2+1,item);
		} else if(tree[i].data<item){
			delete(tree,i*2+2,item);
		} else {
			s=tree[i].data;
			if(tree[i*2+1].data==0&&tree[i*2+2].data==0){
				tree[i].data=0;
			} else if(tree[i*2+1].data==0){
				shiftRightUp(tree,i);
			} else if(tree[i*2+2].data==0){
				shiftLeftUp(tree,i);
			} else{
				temp=i*2+2;
				j=findSuccessor(tree,i*2+2);
				if(tree[temp*2+1].data!=0){
					if(tree[j*2+2].data!=0){
						tree[i].data=tree[j].data;
						delete(tree,temp,tree[j].data);
					} else {
					tree[i].data=tree[j].data;
					tree[j].data=0;
					}
				} else {
					tree[i].data=tree[j].data;
					shiftRightUp(tree,j);
				}
			}
			reBalance(tree,i,s);
			return 1;
		}
}
}
void insert(struct Tree tree[],int item,int i){
	if(tree[i].data!=0){
		if(item>tree[i].data){
			insert(tree,item,i*2+2);
		} else if(item<tree[i].data){
			insert(tree,item,i*2+1);
		}
	} else {
		tree[i].data=item;
		tree[i].b=0;
		balance(tree,i,i);
	}
}
void createTree(struct Tree tree[],int a[],int i,int t,int n){
		if(t!=n){
		if(a[t]>tree[i].data&&tree[i].data!=0){
			createTree(tree,a,2*i+2,t,n);
		}else if(a[t]<=tree[i].data&&tree[i].data!=0){
			createTree(tree,a,2*i+1,t,n);
		}else if(tree[i].data==0){
			tree[i].data=a[t];
			tree[i].b=0;
			balance(tree,i,i);	
			createTree(tree,a,0,t+1,n);
		}
	}
}
int knowHeight(struct Tree tree[],int i){
	if(tree[i].data!=0){
		return maxim(knowHeight(tree,i*2+1)+1,knowHeight(tree,i*2+2)+1);
	}
	return 0;
}
void printTree(struct Tree tree[],int i){
	if(tree[i].data!=0){
		printTree(tree,2*i+1);
		printf("%d ",tree[i].data);
		printTree(tree,2*i+2);
	}
}
int search(struct Tree tree[],int item,int i){
	if(tree[i].data!=0){
		if(tree[i].data>item){
			search(tree,item,i*2+1);
		} else if(tree[i].data<item){
			search(tree,item,i*2+2);
		} else{
			return 1;
		}
	}
}
int searchArray(int a[],int item,int n){
	for(int i=0;i<n;i++){
		if(a[i]==item){
			return 1;
		}
	}
	return -1;
}
int main(){
	struct Tree *tree=(struct Tree*)malloc(sizeof(struct Tree)*1000);
	int i,item,temp;
	for(i=0;i<999;i++){
		tree[i].data=0;
		tree[i].b=0;
	}
	int a[20],n;
	int h,p;
	printf("Enter the number of elements\n");
	scanf("%d",&n);
	for(int i=0;i<n;i++){
		scanf("%d",&a[i]);
	}
	tree[0].data=a[0];
	createTree(tree,a,0,1,n);
	do{
		printf("\n\n\n\n\tEnter your choice\n");
		printf("\t1.Insert an Item\n");
		printf("\t2.Delete an Item\n");
		printf("\t3.Search for the key\n");
		printf("\t4.Print in sorted order\n");
		printf("\t5.Search in array\n");
		printf("\t6.Quit\n");
		scanf("%d",&h);
		switch(h){
			case 1:printf("Enter a element to be inserted\n");
				   scanf("%d",&p);
				   insert(tree,p,0);
				   printf("Element inserted\n");
				   break;
			case 2:	printf("Enter the element to delete\n");
					scanf("%d",&item);
					temp=delete(tree,0,item);
					if(temp==1){
						printf("element deleted\n");
					} else {
						printf("Element not found\n");
					}
					break;
			case 3: printf("Enter the element to search\n");
					scanf("%d",&p);
					clock_t begin=clock();
					temp=search(tree,p,0);
					clock_t end=clock();
					if(temp==1){
						printf("Element Found\n");
					} else {
						printf("Element not found\n");
					}
					// long double t=((long double)(end-begin))/CLOCKS_PER_SEC;
					// printf("Time taken in search is %.500Lf\n",t);
					break;
			case 4: printf("Elements are:\n");
					printTree(tree,0);
					printf("\n");
					break;
			case 5: printf("Enter the element\n");
					scanf("%d",&p);
					clock_t b=clock();
					temp=searchArray(a,p,n);
					clock_t e=clock();
					if(temp==1){
						printf("Element Found\n");
					} else {
						printf("Element not found\n");
					}
					// long double ti=((long double)(e-b))/CLOCKS_PER_SEC;
					// printf("Time taken in search is %.500Lf\n",ti);
					break;
			case 6: exit(0);
			default: printf("Wrong choice\n");
		}
	}while(1);
}