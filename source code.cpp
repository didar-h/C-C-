// @author Didar   +8618813033602
#include <bits/stdc++.h>
#define MaxSize 100
#define QNODE struct QNode
using  namespace std;
int new_t=0;
typedef struct Node{char Action;int NO;int time;}Node;
typedef struct Stack{ struct Node	data[MaxSize]; int top; int num;}SqStack;
SqStack *Init_SeqStack(){
    SqStack *s;
    s=(SqStack*)malloc(sizeof(SqStack));
    s->top=-1;
    s->num=0;
    return s;
}
int ISEmpty_SeqStack(SqStack *s){return (s->top == (-1));}
int  ISFULL_SeqStack(SqStack *s,int n){ return (s->top==(n-1));}
void Push_SeqStack(SqStack *p,struct Node s){   //??
    p->top ++;
    p->data[p->top]=s;
    p->num++;
}
int POP_SeqStack(SqStack *s,struct Node car){
    SqStack *p;
    int t,top=s->top,num=s->num;
    p=Init_SeqStack();
    //cout<<"P num = "<<p->num<<endl;
    while(s->data[top].NO !=car.NO){
        Push_SeqStack(p,s->data[top]);
        top--; num--;
        if(num==0){
            //cout<<"No Value"<<endl;
            return 0;
        }
    }
    //std::cout<<std::endl<<car.time<<"\t"<<s->data[s->top].time<<std::endl;
    t=car.time-s->data[top].time;
    new_t=car.time;
    top--; num--;
    s->num=num;
    s->top=top;
    while(!ISEmpty_SeqStack(p)){
        Push_SeqStack(s,p->data[p->top]);
        p->top--;
        p->num--;
    }
    return t;
}



QNODE{struct Node data; QNODE *next;};
typedef struct linkqueue{ QNODE *front,*rear;int num;}LinkQueue;
LinkQueue *Init_LQueue(){
    LinkQueue *q;
    QNODE *p;
    q=(LinkQueue*)malloc(sizeof(LinkQueue));
    p=(QNODE*)malloc(sizeof(QNODE));
    p->next=NULL;
    q->front=q->rear=p;
    q->num=0;
    return q;
}
int ISEmpty_LQueue(LinkQueue *q){return (q->front==q->rear);}
void IN_Lqueue(	LinkQueue *q,struct Node s){
    QNODE *p;
    p=(QNODE*)malloc(sizeof(QNODE));
    p->data=s;
    p->next=NULL;
    q->num++;
    q->rear->next =p;
    q->rear =p;
}
struct Node Out_LQueue(LinkQueue *q){
    QNODE *p;
    p=q->front->next;
    q->front->next=p->next;
    q->num --;
    if(	q->front->next==NULL)
        q->rear=q->front;
    p->data.time=new_t;
    return p->data;
}
int Find_delate(LinkQueue *q, struct Node car){
    QNODE *p=q->front;
    while(car.NO!=q->front->next->data.NO){ //finding
        q->front=q->front->next;
    }
    std::cout<<q->front->next->data.NO<<std::endl;
    if(q->front->next->next!=NULL) {    //delating
        QNODE *a = q->front->next;
        q->front->next = a->next;
        free(a);
    }
    else
        q->rear=q->front;
    q->num--;
    q->front=p;
    return true;
}


int main(){
    SqStack *parkstack;
    LinkQueue *parkqueue;
    struct Node car;
    int n,t;
    parkstack=Init_SeqStack();
    parkqueue=Init_LQueue();
    std::cout<<"N:";    std::cin>>n;
    std::cout<<"input car information\n";
    scanf("%c,%d,%d",&car.Action,&car.NO,&car.time);
    while(car.Action!='E'){
        if(car.Action=='A' ){
            if(ISFULL_SeqStack(parkstack,n)){
                IN_Lqueue(parkqueue,car);
                printf("This car is on %d place of the queue \n",parkqueue->num);
            }
            else{
                Push_SeqStack(parkstack,car);
                printf("This car is on %d place of the lot \n",parkstack->num);
            }
            std::cout<<"Enter next car`s info\n";
        }

        if(car.Action=='D'){
            t=POP_SeqStack(parkstack,car);
            if(!t){
                Find_delate(parkqueue, car);
                printf("You was just on queue, it`s free\n");
            }
            else {
                printf("The time you used the lot:%d\n", t);
                printf("Enter next car`s info\n");
                if (!ISEmpty_LQueue(parkqueue))
                    Push_SeqStack(parkstack, Out_LQueue(parkqueue));
            }
        }
        scanf("%c,%d,%d",&car.Action,&car.NO,&car.time);
    }
    return 1;
}
