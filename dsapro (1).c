#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct node{
    int amount,id;
    char name[10],pass[10];
    struct node *prev;
    struct node *next;
};
struct node *head=NULL;
struct node *tail;

struct loan{
    int id;
    float ratio;
    int amt;
};

void insert(int id,int amt,char name[],char pass[]){
    struct node *new;
    new=(struct node*)malloc(sizeof(struct node));
    new->id=id;
    new->amount=amt;
    strcpy(new->name,name);
    strcpy(new->pass,pass);
    
    if(head==NULL){
       head=new;
       new->prev=NULL;
       new->next=NULL;
    }
    if(new->id<head->id){
        head->prev=new;
        new->next=head;
        new->prev=NULL;
        head=new;
    }
    else{
        struct node *temp=head;
        while(temp->next!=NULL){
            if(temp->id>id){
                (temp->prev)->next=new;
                new->next=temp;
                new->prev=temp->prev;
                temp->prev=new;
                break;
            }
            temp=temp->next;
        }
        if(temp->next==NULL){
            if(temp->id>id){
                (temp->prev)->next=new;
                new->next=temp;
                new->prev=temp->prev;
                temp->prev=new;
            }
            else{
                temp->next=new;
                new->prev=temp;
                new->next=NULL;
            }
        }

    }
}
void withdraw(int a,int amt){
    struct node *temp =head;
      while(temp != NULL)
      {
            if(temp->id== a)
            {
                temp->amount=temp->amount-amt;
                if((temp->amount)<0)
                {
                    printf("\nInsufficient value!!!\n");
                    temp->amount=temp->amount+amt;
                    break;
                }
                else
                {
                    printf("\nAmount has been withdrawn!!!\n");
                    break;
                }
            }
      }    
}
void deposit(int id,int amt){
    struct node*temp=head;
    while(temp!=NULL){
        if(temp->id==id){
            temp->amount+=amt;
            printf("\nSuccessfully deposited");
            return;
        }
        temp=temp->next;
    }
}
void min_heap(struct loan *a,int n,int i){
    int small=i;
    int l=(2*i);
    int r=(2*i)+1;

    if(l<=n && (a[l].ratio<a[small].ratio)){
        small=l;
    }
    if(r<=n && (a[r].ratio<a[small].ratio)){
        small=r;
    }
    if(small!=i){
        int id=a[i].id;
        a[i].id=a[small].id;
        a[small].id=id;
        int ratio=a[i].ratio;
        a[i].ratio=a[small].ratio;
        a[small].ratio=ratio;
        int amt=a[i].amt;
        a[i].amt=a[small].amt;
        a[small].amt=amt;
        
        min_heap(a,n,small);
    }
}

void loan(struct loan *ln,int i){
    int id;
    float l_amt=0;
    printf("\nEnter your id:");
    scanf("%d",&id);
    printf("\nEnter amount of loan:");
    scanf("%f",&l_amt);
    //printf("%f",l_amt);
    struct node *save=head;
    while((save!=NULL)&&(save->id!=id)){
        save=save->next;
    }
    if(save->id==id){
        ln[i].id=id;
        ln[i].amt=save->amount;
    }
    else{
        printf("\nUser doesn't exist!!");
        return;
    }
    //printf("\n%d",ln[i].amt);
    float bal=(float)ln[i].amt;
    float r=l_amt/bal;
    ln[i].ratio=r;
    int n=i;
    printf("\nn:%d",n);

    for(int j=(n/2);j>0;j--){
        min_heap(ln,n,j);
    }
    for(int j=1;j<=n;j++){
        printf("\n%d",ln[j].id);
        printf("\n%f",ln[j].ratio);
        printf("\n%d",ln[j].amt);
    }
}

void loan_allote(struct loan *ln,int n){
    
    int id=ln[1].id;
    ln[1].id=ln[n].id;
    ln[n].id=id;
    float ratio=ln[1].ratio;
    ln[1].ratio=ln[n].ratio;
    ln[n].ratio=ratio;
    int amt=ln[1].amt;
    ln[1].amt=ln[n].amt;
    ln[n].id=amt;
    ln=(struct loan*)realloc(ln,(n-1)*(sizeof(struct loan)));
    for(int i=(n/2);i>0;i--){
        min_heap(ln,n-1,i);
    }
}
void display(){
    struct node *temp=head;
    while(temp!=NULL){
        printf("\nid: %d",temp->id);
        printf("\namt: %d",temp->amount);
        temp=temp->next;
    }
}

int main(){
    insert(102,1000,"yash","1234");
    insert(103,2000,"abcd","6666");
    withdraw(102,800);
    display();
    struct loan *pro;
    pro=(struct loan*)malloc(sizeof(struct loan));
    int i=1,no_loan;
    while(1){
        pro=(struct loan*)realloc(pro,(i+1)*sizeof(struct loan));
        scanf("%d",&no_loan);
        if(no_loan==1){
            break;
        }
    loan(pro,i);
    printf("\n");
    i++;
    }
    // display();
    printf("\n");
    
    int n=i-1;
    int s;
    while(n>0){
    scanf("%d",&s);
    if(s==1){
        printf("id : %d\n amt : %d  \nratio : %f\n",pro[1].id,pro[1].amt,pro[1].ratio);
        loan_allote(pro,n);
        n--;
    }
    else if(s==0) break;
    }
}
