//购物网站信息管理
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define OK 1
#define ERROR 0
#define Maxsize 20
typedef struct Snode{
	char name[Maxsize];
	int price;
	int solesnum;
	struct Snode *next;
}*Shop,shopNode;
typedef struct{
	Shop head,tail;
	int length;
}Shoplist;
//每一个店铺商品的链表
typedef struct{
	int num;
	char name1[Maxsize];
	int crditeworth;
    int shopnum;
}Shopping;
typedef struct Lnode{
	Shopping data;
	struct Lnode *next;
}*link,Lnode;
typedef struct {
	link head,tail;
	int length;
}linklist;
//关于店铺的结构体链表 
typedef struct Mnode{
	char name2[Maxsize];
	int num1;
	int credit;
	char name3[Maxsize];
	int shopnum1;
	int pprice1;
	struct Mnode *next;
}*Mid,Mnode;
typedef struct{
	Mid head,tail;
	int length;
}Midlist;
bool initmidlist(Midlist &M){
	M.head=(Mid)malloc(sizeof(Mnode));
	M.head->next=NULL;
	M.tail=M.head;
	M.length=0;
	return OK;
}
bool initlinklist(linklist &L){
	L.head=(link)malloc(sizeof(Lnode));
	L.head->next=NULL;
	L.tail=L.head; 
	L.length=0;
	return OK;
}
//店铺链表的初始化 
bool initshoplist(Shoplist &S){
	S.head=(Shop)malloc(sizeof(shopNode));
	S.head->next=NULL;
	S.tail=S.head;
	S.length=0;
	return OK;
} 
//商品链表的初始化
bool createshoplist(Shoplist &S,int num){
	initshoplist(S);
	Shop p=NULL;
	FILE *fq;
	if((fq=fopen("shoplist.txt","ab"))==NULL){
		printf("无该文件!");
		exit(0);
	}
	for(int i=1;i<=num;i++){
		p=(Shop)malloc(sizeof(shopNode));
		printf("输入第%d个商品的信息(名称、价格):\n",i);
		scanf("%s %d",&p->name,&p->price);	
		p->solesnum=0;
		fwrite(p,sizeof(struct Snode),1,fq);
		p->next=NULL;		
		if(i==1){
			S.head=p;
			S.tail=p;
			S.length++;
		}
		else{
			S.tail->next=p;
			S.tail=p;
			S.length++;
		}	
	}
	fclose(fq);	
	return OK;
}
//商品链表创建成功 
bool createlinklist(linklist &L,int num_1){
	initlinklist(L);
	Shoplist S;
	link p=NULL;
	FILE *fp;
	if((fp=fopen("shop.txt","wb"))==NULL){
		printf("没有该文件!");
		exit(0);
	}
	for(int i=1;i<=num_1;i++){
		p=(link)malloc(sizeof(Lnode));
		printf("向链表输入第%d个店铺的信息(商铺编号、商铺名、信誉度、商品数量):\n",i);
		scanf("%d %s %d %d",&p->data.num,&p->data.name1,&p->data.crditeworth,&p->data.shopnum);
		getchar();
		fwrite(p,sizeof(struct Lnode),1,fp);
		createshoplist(S,p->data.shopnum);
		p->next=NULL;
		if(i==1){
			L.head=p;
			L.tail=p;
			L.length++;
		}
		else {
			L.tail->next=p;
			L.tail=p;
			L.length++;
		}
	}
	fclose(fp);
	return OK;
} 
//创建商铺链表成功 
bool insertlinklist(){
	FILE *fp,*f;
	if((fp=fopen("shop.txt","rb"))==NULL) exit(0); 
	 Shoplist S;
	 linklist L;
	 initlinklist(L);
	 
	 link q,s;
	 s=L.head;
	 Lnode temp;
	 fread(&temp,sizeof(struct Lnode),1,fp);
	 while(!feof(fp)){
	 	q=(link)malloc(sizeof(Lnode));
	 	q->data.num=temp.data.num;
	 	strcpy(q->data.name1,temp.data.name1);
	 	q->data.crditeworth=temp.data.crditeworth;
	 	q->data.shopnum=temp.data.shopnum;
	 	s->next=q;
	 	q->next=NULL;
	 	s=q;
	 	L.length++;
	 	fread(&temp,sizeof(struct Lnode),1,fp);
	 }
	 fclose(fp);

	 link m;
	 int j=0;
	 m=(link)malloc(sizeof(Lnode));
	 printf("输入新的商铺的信息(商铺名、信誉度、商品数量):\n");
	 scanf("%s %d %d",&m->data.name1,&m->data.crditeworth,&m->data.shopnum);
	 m->data.num=L.length+1;
	 createshoplist(S,m->data.shopnum);
	 m->next=s->next;
	 s->next=m;
	 L.length++;
	 
	 if((f=fopen("shop.txt","wb"))==NULL) exit(0);
	 link lin=L.head->next;
	 for(int i=0;i<L.length;i++){
	 	fwrite(lin,sizeof(struct Lnode),1,f);
	 	lin=lin->next;
	 }
	 fclose(f);
}
//将店铺信息插入 
bool deleteshoplist(int num1,int num2){//num1是删除商品之前的数量，num2是要删除的之后的 
	FILE *fp,*f;
	if((fp=fopen("shoplist.txt","rb"))==NULL) exit(0);
	Shoplist S;
	initshoplist(S);
	Shop p,q;
	p=S.head;
	Snode temp;
	fread(&temp,sizeof(struct Snode),1,fp);
	while(!feof(fp)){
		q=(Shop)malloc(sizeof(Snode));
		strcpy(q->name,temp.name);
		q->price=temp.price;
		q->solesnum=temp.solesnum;
		p->next=q;
		q->next=NULL;
		p=q;
		S.length++;
		fread(&temp,sizeof(struct Snode),1,fp);
	}
	fclose(fp);

	Shop m=S.head,P=NULL;
	for(int i=0;i<num1;i++){
		m=m->next;
	}
    P=m->next;
	for(int i=0;i<num2-num1;i++){
		m->next=P->next;
		free(P);
		S.length--;
		P=m->next;
	}

	if((f=fopen("shoplist.txt","wb"))==NULL) exit(0);
	Shop lin=S.head->next;
	for(int j=0;j<=S.length-1;j++){
		fwrite(lin,sizeof(struct Snode),1,f);
		lin=lin->next;
	}
	fclose(fp);
}
//将对应商铺的商品全部删除 
bool deletelinklist(int num1){//num是删除的编号
	FILE *fp,*f;
	if((fp=fopen("shop.txt","rb"))==NULL) exit(0); 
	 Shoplist S;
	 linklist L;
	 initlinklist(L);
	 int count=0;
	 link q,s,lin;
	 s=L.head;
	 Lnode temp;
	 fread(&temp,sizeof(struct Lnode),1,fp);
	 while(!feof(fp)){
	 	q=(link)malloc(sizeof(Lnode));
	 	q->data.num=temp.data.num;
	 	strcpy(q->data.name1,temp.data.name1);
	 	q->data.crditeworth=temp.data.crditeworth;
	 	q->data.shopnum=temp.data.shopnum;
	 	s->next=q;
	 	q->next=NULL;
	 	s=q;
	 	L.length++;
	 	fread(&temp,sizeof(struct Lnode),1,fp);
	 }
	 fclose(fp);

	 lin=L.head->next;
	 while(lin&&lin->data.num!=num1){
	 	count=count+lin->data.shopnum; 
	 	lin=lin->next;
	 }//找到该商铺对应的商品的节点起始位置 

	 int m=lin->data.shopnum;//要删除的店铺的商品数量 
	 m=m+count;
	 s=L.head;
	 for(int i=0;i<num1-1;i++){
	 	s=s->next;
	 }
	 lin=s->next;
	 s->next=lin->next;
	 free(lin);
	 L.length--;

	 if((f=fopen("shop.txt","wb"))==NULL) exit(0);
	 lin=L.head->next;
	 for(int i=0;i<=L.length-1;i++){
	 	lin->data.num=i+1;
	 	fwrite(lin,sizeof(struct Lnode),1,f);
	 	lin=lin->next;
	 }
	 fclose(f);
	 deleteshoplist(count,m); 	 
}
//删除店铺信息 
bool insertshoplist(int num1){
	FILE *f,*fp;
	if((f=fopen("shop.txt","rb"))==NULL) exit(0);
	if((fp=fopen("shoplist.txt","rb"))==NULL) exit(0);
	linklist L;
	Shoplist S;
	initlinklist(L);
	initshoplist(S);
	int count=0;
	
	link q,s,lin;
	s=L.head;
	Lnode temp;
	fread(&temp,sizeof(struct Lnode),1,f);
	while(!feof(f)){
	   q=(link)malloc(sizeof(Lnode));
	   q->data.num=temp.data.num;
	   strcpy(q->data.name1,temp.data.name1);
	   q->data.crditeworth=temp.data.crditeworth;
	   if(L.length+1==num1) q->data.shopnum=temp.data.shopnum+1;
	   else q->data.shopnum=temp.data.shopnum;
	   s->next=q;
	   q->next=NULL;
	   s=q;
	   L.length++;
	   fread(&temp,sizeof(struct Lnode),1,f);
	}
	fclose(f);//将商铺信息放到链表中 
	lin=L.head->next;
	while(lin&&lin->data.num!=num1){
	   count=count+lin->data.shopnum; 
	   lin=lin->next;
	}//找到该商铺对应的商品的节点起始位置
	if((f=fopen("shop.txt","wb"))==NULL) exit(0);
	lin=L.head->next;
	for(int i=0;i<L.length;i++){
		fwrite(lin,sizeof(struct Lnode),1,f);
		lin=lin->next;
	}
	fclose(f);

	Shop p,r;
	p=S.head;
	Snode tem;
	fread(&tem,sizeof(struct Snode),1,fp);
	while(!feof(fp)){
		r=(Shop)malloc(sizeof(Snode));
		strcpy(r->name,tem.name);
		r->price=tem.price;
		r->solesnum=tem.solesnum;
		p->next=r;
		r->next=NULL;
		p=r;
		S.length++;
		fread(&tem,sizeof(struct Snode),1,fp);
	}
	fclose(fp);//将商品信息放到链表中 
	Shop m=S.head,P=NULL;
	for(int i=0;i<count;i++){
		m=m->next;
	}
	printf("输入添加的商品信息(名称、价格):\n");
	P=(Shop)malloc(sizeof(Snode));
	scanf("%s %d",&P->name,&P->price);
	P->solesnum=0;
	P->next=m->next;
	m->next=P;
	S.length++;
	if((fp=fopen("shoplist.txt","wb"))==NULL) exit(0);
	Shop li=S.head->next;
	for(int j=0;j<S.length;j++){
		fwrite(li,sizeof(struct Snode),1,fp);
		li=li->next;
	}
	fclose(fp);
}
//添加商品信息 
bool deleteshoplist(int num1){
	char na[Maxsize];
	FILE *f,*fp;
	if((f=fopen("shop.txt","rb"))==NULL) exit(0);
	if((fp=fopen("shoplist.txt","rb"))==NULL) exit(0);
	linklist L;
	Shoplist S;
	initlinklist(L);
	initshoplist(S);
	int count=0;
	link q,s,lin;
	s=L.head;
	Lnode temp;
	fread(&temp,sizeof(struct Lnode),1,f);
	while(!feof(f)){
	   q=(link)malloc(sizeof(Lnode));
	   q->data.num=temp.data.num;
	   strcpy(q->data.name1,temp.data.name1);
	   q->data.crditeworth=temp.data.crditeworth;
	   if(L.length+1==num1) q->data.shopnum=temp.data.shopnum-1;
	   else q->data.shopnum=temp.data.shopnum;
	   s->next=q;
	   q->next=NULL;
	   s=q;
	   L.length++;
	   fread(&temp,sizeof(struct Lnode),1,f);
	}
	fclose(f);//将商铺信息放到链表中 
	lin=L.head->next;
	while(lin&&lin->data.num!=num1){
	   count=count+lin->data.shopnum; 
	   lin=lin->next;
	}//找到该商铺对应的商品的节点起始位置
	int numm=lin->data.num;
	lin->data.shopnum;
	if((f=fopen("shop.txt","wb"))==NULL) exit(0);
	lin=L.head->next;
	for(int i=0;i<L.length;i++){
		fwrite(lin,sizeof(struct Lnode),1,f);
		lin=lin->next;
	}
	fclose(f);
	
	Shop p,r;
	p=S.head;
	Snode tem;
	fread(&tem,sizeof(struct Snode),1,fp);
	while(!feof(fp)){
		r=(Shop)malloc(sizeof(Snode));
		strcpy(r->name,tem.name);
		r->price=tem.price;
		r->solesnum=tem.solesnum;
		p->next=r;
		r->next=NULL;
		p=r;
		S.length++;
		fread(&tem,sizeof(struct Snode),1,fp);
	}
	fclose(fp);//将商品信息放到链表中 
	Shop m=S.head,n=S.head;
	for(int i=0;i<count;i++){
		m=m->next;
		n=n->next;
	}
	printf("输入要删除的商品的(名称):\n");
	scanf("%s",&na);
	m=m->next;
	for(int i=0;i<numm;i++){
		if(strcmp(na,m->name)==0){
			n->next=m->next;
			free(m);
			S.length--;
			break;
		}
		else {
			m=m->next;
			n=n->next;
		}
	}

	if((fp=fopen("shoplist.txt","wb"))==NULL) exit(0);
	Shop li=S.head->next;
	while(li){
		fwrite(li,sizeof(struct Snode),1,fp);
		li=li->next; 
	}
	fclose(fp);
}
//删除商品信息 
bool lookinformation(){
	FILE *f,*f1;
	if((f=fopen("shop.txt","rb"))==NULL) exit(0);
	if((f1=fopen("shoplist.txt","rb"))==NULL) exit(0);
	linklist L;
	Shoplist S;
	initlinklist(L);
	initshoplist(S);
	int count=0,num1;
	
	link q,s;
	s=L.head;
	Lnode temp;
	fread(&temp,sizeof(struct Lnode),1,f);
	while(!feof(f)){
	   q=(link)malloc(sizeof(Lnode));
	   q->data.num=temp.data.num;
	   strcpy(q->data.name1,temp.data.name1);
	   q->data.crditeworth=temp.data.crditeworth;
	   q->data.shopnum=temp.data.shopnum;
	   s->next=q;
	   q->next=NULL;
	   s=q;
	   L.length++;
	   fread(&temp,sizeof(struct Lnode),1,f);
	}
	fclose(f);//将商铺信息放到链表中 

	Shop p,r;
	p=S.head;
	Snode tem;
	fread(&tem,sizeof(struct Snode),1,f1);
	while(!feof(f1)){
		r=(Shop)malloc(sizeof(Snode));
		strcpy(r->name,tem.name);
		r->price=tem.price;
		r->solesnum=tem.solesnum;
		p->next=r;
		r->next=NULL;
		p=r;
		S.length++;
		fread(&tem,sizeof(struct Snode),1,f1);
	}
	fclose(f1);//将商品信息放到链表中 

	link line=L.head->next;
	Shop m=S.head->next;
	printf("----------------------------------\n");
	while(line){
		num1=line->data.shopnum;
		printf("商铺(%s)的商品情况(编号:%d):\n",line->data.name1,line->data.num);
		for(int j=0;j<num1;j++){
			printf("商品名:%s ",m->name);
			printf("商品价格:%d ",m->price);
			printf("商品销量:%d",m->solesnum);
			printf("\n");
			m=m->next;
		}
		printf("----------------------------------\n");
		line=line->next;
	}
} 
//查看所有商铺及其商品 
bool sortlist(Midlist &M){
	Mid p=NULL,q=NULL;
	int i=1,another,another1,another2,another3;
	char na1[Maxsize],na2[Maxsize];
	while(i<M.length){
		p=M.head;
		for(int m=0;m<i;m++){
			p=p->next;
		}	
		q=M.head;	//找到自己想要拿出比较的元素位置 
		for(int m=0;m<i;m++){
			if(p->shopnum1<q->shopnum1){  //m的值决定从哪个位置开始往后移 
				another=p->shopnum1;
				another1=p->credit;
				another2=p->num1;
				another3=p->pprice1;
				strcpy(na1,p->name2);
				strcpy(na2,p->name3);
				for(int j=m;j<i;j++){  //i的位置觉得移到哪个位置结束 
					q=M.head;
					//q=q->next;
					while(q->next!=p){
						q=q->next;
					} 
					p->shopnum1=q->shopnum1;
					p->credit=q->credit;
					p->num1=q->num1;
					p->pprice1=q->pprice1;
					strcpy(p->name2,q->name2);
					strcpy(p->name3,q->name3);
					p=q;
				}
				p=M.head;
				if(m==0) {
					p->shopnum1=another;
					p->credit=another1;
					p->num1=another2;
					p->pprice1=another3;
					strcpy(p->name2,na1);
					strcpy(p->name3,na2);
				}
				else{
					for(int j=0;j<m;j++){
						p=p->next;
					}
					p->shopnum1=another;
					p->credit=another1;
					p->num1=another2;
					p->pprice1=another3;
					strcpy(p->name2,na1);
					strcpy(p->name3,na2);
				}
				m=i;
			}
			q=q->next;
		} 
		i++;
	}
} 
//将链表进行排序 
bool checkshoplist(char na[]){
	FILE *f,*f1;
	if((f=fopen("shop.txt","rb"))==NULL) exit(0);
	if((f1=fopen("shoplist.txt","rb"))==NULL) exit(0);
	linklist L;
	Shoplist S;
	initlinklist(L);
	initshoplist(S);
	int count=0,num1;
	
	link q,s;
	s=L.head;
	Lnode temp;
	fread(&temp,sizeof(struct Lnode),1,f);
	while(!feof(f)){
	   q=(link)malloc(sizeof(Lnode));
	   q->data.num=temp.data.num;
	   strcpy(q->data.name1,temp.data.name1);
	   q->data.crditeworth=temp.data.crditeworth;
	   q->data.shopnum=temp.data.shopnum;
	   s->next=q;
	   q->next=NULL;
	   s=q;
	   L.length++;
	   fread(&temp,sizeof(struct Lnode),1,f);
	}
	fclose(f);//将商铺信息放到链表中 

	Shop p,r;
	p=S.head;
	Snode tem;
	fread(&tem,sizeof(struct Snode),1,f1);
	while(!feof(f1)){
		r=(Shop)malloc(sizeof(Snode));
		strcpy(r->name,tem.name);
		r->price=tem.price;
		r->solesnum=tem.solesnum;
		p->next=r;
		r->next=NULL;
		p=r;
		S.length++;
		fread(&tem,sizeof(struct Snode),1,f1);
	}
	fclose(f1);//将商品信息放到链表中 
	
	link line=L.head->next;
	Shop m=S.head->next;
	Midlist M;
	initmidlist(M);
	Mid a,b=M.head;
	//printf("----------------------------------\n");
	while(line){
		num1=line->data.shopnum;
		//printf("商铺(%s)的商品情况(编号:%d):\n",line->data.name1,line->data.numo0);
		for(int j=0;j<num1;j++){
			if(strcmp(m->name,na)==0){
				a=(Mid)malloc(sizeof(Mnode));
				strcpy(a->name2,line->data.name1);
				strcpy(a->name3,m->name);
				a->num1=line->data.num;
				a->credit=line->data.crditeworth;
				a->shopnum1=m->solesnum;
				a->pprice1=m->price;
				b->next=a;
				a->next=NULL;
				b=a;
				M.length++;
			}
			m=m->next;
		}
		//printf("----------------------------------\n");
		line=line->next;
	}
	
//	sortlist(M);
	Mid mid=M.head->next;
	printf("----------------------------------\n");
	while(mid){
		printf("商铺(编号%d)%s  信誉度:%d\n商品:%s  商品价格:%d  商品销量:%d\n",mid->num1,mid->name2,mid->credit,mid->name3,mid->pprice1,mid->shopnum1);
		printf("----------------------------------\n");
		mid=mid->next;
	}
}
//用户查找所有有商品存在的情况 
bool buyshop(char na[],int num){
	FILE *f,*f1;
	if((f=fopen("shop.txt","rb"))==NULL) exit(0);
	if((f1=fopen("shoplist.txt","rb"))==NULL) exit(0);
	linklist L;
	Shoplist S;
	initlinklist(L);
	initshoplist(S);
	int count=0;
	
	link q,s;
	s=L.head;
	Lnode temp;
	fread(&temp,sizeof(struct Lnode),1,f);
	while(!feof(f)){
	   q=(link)malloc(sizeof(Lnode));
	   q->data.num=temp.data.num;
	   strcpy(q->data.name1,temp.data.name1);
	   q->data.crditeworth=temp.data.crditeworth;
	   q->data.shopnum=temp.data.shopnum;
	   s->next=q;
	   q->next=NULL;
	   s=q;
	   L.length++;
	   fread(&temp,sizeof(struct Lnode),1,f);
	}
	fclose(f);//将商铺信息放到链表中 

	Shop p,r;
	p=S.head;
	Snode tem;
	fread(&tem,sizeof(struct Snode),1,f1);
	while(!feof(f1)){
		r=(Shop)malloc(sizeof(Snode));
		strcpy(r->name,tem.name);
		r->price=tem.price;
		r->solesnum=tem.solesnum;
		p->next=r;
		r->next=NULL;
		p=r;
		S.length++;
		fread(&tem,sizeof(struct Snode),1,f1);
	}
	fclose(f1);//将商品信息放到链表中 
	
	int numm,m=0;
	link line=L.head->next;
	Shop lin=S.head->next;
	while(line){
		numm=line->data.shopnum;
		if(line->data.num==num){
			for(int j=0;j<numm;j++){
				if(strcmp(lin->name,na)==0){
					(lin->solesnum)++;
					m=1;
					break;
				}
				lin=lin->next;
			}
		}
		if(m==1) break;
		for(int i=0;i<numm;i++){
			lin=lin->next;
		}
		line=line->next;
	}
	if((f1=fopen("shoplist.txt","wb"))==NULL) exit(0);
	Shop mm=S.head->next;
	while(mm){
		fwrite(mm,sizeof(struct Snode),1,f1);
		mm=mm->next;
	}
	fclose(f1);
}
//购买商品的操作 
bool changeprice(int num){
	char na[Maxsize];
	printf("你要改变价格的商品名称:");
	scanf("%s",&na);
	FILE *f,*f1;
	if((f=fopen("shop.txt","rb"))==NULL) exit(0);
	if((f1=fopen("shoplist.txt","rb"))==NULL) exit(0);
	linklist L;
	Shoplist S;
	initlinklist(L);
	initshoplist(S);
	int count=0,num1;
	
	link q,s;
	s=L.head;
	Lnode temp;
	fread(&temp,sizeof(struct Lnode),1,f);
	while(!feof(f)){
	   q=(link)malloc(sizeof(Lnode));
	   q->data.num=temp.data.num;
	   strcpy(q->data.name1,temp.data.name1);
	   q->data.crditeworth=temp.data.crditeworth;
	   q->data.shopnum=temp.data.shopnum;
	   s->next=q;
	   q->next=NULL;
	   s=q;
	   L.length++;
	   fread(&temp,sizeof(struct Lnode),1,f);
	}
	fclose(f);//将商铺信息放到链表中 
	
	Shop p,r;
	p=S.head;
	Snode tem;
	fread(&tem,sizeof(struct Snode),1,f1);
	while(!feof(f1)){
		r=(Shop)malloc(sizeof(Snode));
		strcpy(r->name,tem.name);
		r->price=tem.price;
		r->solesnum=tem.solesnum;
		p->next=r;
		r->next=NULL;
		p=r;
		S.length++;
		fread(&tem,sizeof(struct Snode),1,f1);
	}
	fclose(f1);//将商品信息放到链表中 

	int m=0;
	link lin=L.head->next;
	Shop line=S.head->next;
	while(lin){
		num1=lin->data.num;
		if(lin->data.num==num){
			for(int j=0;j<num1;j++){
				if(strcmp(na,line->name)==0){
					printf("输入新价格:");
					scanf("%d",&line->price);
					m=1;
					break;
				}
				lin=lin->next;
			}
		}
		if(m==1) break;
		for(int i=0;i<num1;i++){
			line=line->next;
		}
		lin=lin->next;
	}
	
	if((f1=fopen("shoplist.txt","wb"))==NULL) exit(0);
	Shop mm=S.head->next;
	while(mm){
		fwrite(mm,sizeof(struct Snode),1,f1);
		mm=mm->next;
	}
	fclose(f1);
}
void guanlimeau(){
	Lnode p;
	shopNode q;
	linklist L;
	char a[10];
	int b=1,which;
	getchar();
	while(b==1){
		printf("输入密码:");
		gets(a);
		if(strcmp(a,"123456")!=0){
			printf("密码错误!\n");
			b=1;
		}
		else b=0;
	}
	printf("1、创建商城的店铺\n");
	printf("2、添加店铺\n");
	printf("3、删除店铺\n");
	printf("4、增加商品\n");
	printf("5、删除商品\n");
	printf("6、更改商品价格\n");
	printf("7、查看所有店铺信息\n"); 
	printf("0、退出\n");
	int choice,num;
	printf("输入你的选择:");
	scanf("%d",&choice);
	while(choice!=0){
		switch(choice){
			case 1:{
				printf("输入商铺个数:");
				scanf("%d",&num); 
				createlinklist(L,num);
				break;
			}
			case 2:{
				insertlinklist();
				break;
			}
			case 3:{
				printf("删除的商铺的编号:");
				scanf("%d",&which);
				deletelinklist(which);
				break;
			}
			case 4:{
				printf("哪个商铺增加商品:");
				scanf("%d",&which);
				insertshoplist(which);
				break;
			}
			case 5:{
				printf("删除哪个商铺的产品:");
				scanf("%d",&which);
				deleteshoplist(which);
				break;
			}
			case 6:{
				printf("----------------------------------\n");
				printf("以下是商场的所有商铺及商品\n");
				lookinformation();
				printf("更改哪家的商品价格:");
				scanf("%d",&which);
				changeprice(which);
				break;
			}
			case 7:{
				lookinformation();
				break;
			}
			case 0:{
				exit(0);
				break;
			} 
		} 
		printf("输入你的选择:");
		scanf("%d",&choice);
	}
}
//管理员的操作 
void gukemeau(){
	int choice,which;
	char na[Maxsize];
	printf("选择操作:\n");
	printf("1、查找商品\n");
	printf("2、购买商品\n");
	printf("0、退出\n");
	printf("输入你的选择:");
	scanf("%d",&choice);
	while(choice!=0){
		switch(choice){
			case 1:{
				printf("你想查找的商品名称:");
				scanf("%s",&na);
				printf("商品信息如下:\n"); 
				checkshoplist(na);
				break;
			}
			case 2:{
				printf("----------------------------------\n");
				printf("以下是商场的所有商铺及商品\n");
				lookinformation();
				printf("输入买的商品以及商家编号:");
				scanf("%s %d",&na,&which);
				buyshop(na,which);
				break;
			}
			case 0:{
				exit(0);
				break;
			}
		}
		printf("输入你的选择:");
		scanf("%d",&choice);
	}
}
//顾客的操作 
int main(){
	int choice;
	printf("                                                 -----店铺管理-----  \n");
	printf("                                                1、管理员   2、顾客\n");
	printf("                                                    选择你的身份:");
	scanf("%d",&choice);
	if(choice!=1&&choice!=2){
		printf("                                                    选择你的身份:");
		scanf("%d",&choice);
	}
	switch(choice){
		case 1:{
			guanlimeau();
			break;
		}
		case 2:{
			gukemeau();
			break;
		}
	}
}








