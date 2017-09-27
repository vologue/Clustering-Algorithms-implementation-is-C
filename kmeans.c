#include<stdio.h>
#include<math.h>
struct pt{
	float x;
	float y;
}lis[100],clus[2][75];
int c1=1,c2=1;
float di[2][75];
void input(){
	printf("Enter data - (ex- for (1,2)- 1 2 )");
	char y='y';
	int i=0;
	do{
		scanf("%f",&lis[i].x);
		scanf("%f",&lis[i].y);
		printf("do you want to continue  entering?(y/n)\n");
		fflush(stdin);
		scanf("%c",&y);
	}while(y=='y');
}
float mandist(struct pt a,struct pt b){
	struct pt h;
	float y;
	h.x=a.x-b.y;
	h.y=a.y-b.y;
	if(h.x<0)
	h.x=-h.x;
	if(h.y<0)
	h.y=-h.y;
	y=h.x+h.y;
	
}
float eucdist(struct pt a,struct pt b){
	struct pt h;
	float d;
	h.x=a.x-b.x;
	h.x=h.x*h.x;
	h.y=a.y-b.y;
	h.y=h.y*h.y;
	d=h.x+h.y;
	d=sqrt(d);
	return d;
}
void printclus(struct pt clus[2][75]){
	int i,j;
	printf("\tCluster 1\tCluster 2\n");
	for(i=1,j=1;;i++,j++){
		if(i<=c1 && j<=c2)
		printf("\t (%f,%f) \t (%f,%f)\n",clus[0][i].x,clus[0][i].y,clus[1][j].x,clus[1][j].y);
		else if(i<=c1 && j>c2){
			printf("\t (%f,%f)\n",clus[0][i].x,clus[0][i].y);
		}
		else if(i>c1 && j<=c2){
			printf("\t         \t (%f,%f)\n",clus[1][j].x,clus[1][j].y);
		}
		else if(i>c1 && j>c2)
		{break;}
	}
}
void mean(struct pt clus[2][75]){
	int i;
	for(i=1;i<=c1;i++){
		clus[0][0].x=clus[0][0].x+clus[0][i].x;
		clus[0][0].y=clus[0][0].y+clus[0][i].y;
	}
	clus[0][0].x=clus[0][0].x/c1;
	clus[0][0].y=clus[0][0].y/c1;
	for(i=1;i<=c2;i++){
		clus[0][1].x=clus[1][0].x+clus[1][i].x;
		clus[0][1].y=clus[1][0].y+clus[1][i].y;
	}
	clus[1][0].x=clus[1][0].x/c2;
	clus[1][0].y=clus[1][0].y/c2;
}

void inicluster(struct pt clus[2][75],int i,struct pt lis[100]){
	int k;
	float tem1,tem2;
	for(k=0;k<i;k++){
		tem1=mandist(clus[0][0],lis[k]);
		tem2=mandist(clus[1][0],lis[k]);
		if(tem1<tem2){
			clus[0][c1]=lis[k];
			c1++;
		}
		else{
			clus[1][c2]=lis[k];
			c2++;
		}
		mean(clus);
	}
	printclus(clus);
}

void pdist(struct pt clus[2][75],int i,struct pt lis[100]){
	
	printf("\tPoint\tCluster 1\tCluster 2\n");
	for(int k=0;k<i;k++){
		di[0][k]=eucdist(clus[0][0],lis[k]);
		di[1][k]=eucdist(clus[1][0],lis[k]);
		printf("\t(%f,%f)\t  %f \t  %f",lis[k].x,lis[k].y,di[0][k],di[1][k]);
	}
}

void itrations(int i,struct pt clus[2][75]){
	int a=0,b=0;
	while(1==1){
		if(clus[0][a+1].x==lis[a+b].x && clus[0][a+1].y==lis[+b].y){
			a++;
			if(di[0][a+b]>di[1][a+b]){
				int l;
				c2++;
				clus[1][c2].x=clus[0][a].x;
				clus[1][c2].y=clus[0][a].y;
				for(l=a;l<c1;l++){
					clus[0][l].x=clus[0][l+1].x;
					clus[0][c1].y=clus[0][l+1].y;
				}
			c1--;
			a=b=0;
			}
		}
		else if(clus[1][b+1].x==lis[a+b].x && clus[1][b+1].y==lis[a+b].y){
			b++;
			if(di[1][a+b]>di[0][a+b]){
				int l;		
				c1++;
                	        clus[0][c1].x=clus[1][b].x;	
				clus[0][c1].y=clus[1][b].y;
				for(l=b;l<c2;l++){
					clus[1][l].x=clus[1][l+1].x;
					clus[1][c2].y=clus[1][l+1].y;	
				}
				c1--;
				a=b=0;
			}
		}
		mean(clus);
		if((a+b)==i){
			printclus(clus);
			break;
		}
	}
	pdist(clus,i,lis);
	printclus(clus);
}
int main(){
	input();
	printf("Enter number of values entered");
	int i;
	scanf("%d",&i);
	int pos1=0,pos2=0,j;
	float v1,v2;
	for(j=1;j<i;j++){
		v1=lis[pos1].x+lis[pos1].y;
		v2=lis[j].x+lis[j].y;
		if(v1>v2){
			pos1=j;
		}
		v1=lis[pos2].x+lis[pos2].y;
		if(v1<v2){
			pos2=j;
		}
	}
	clus[0][0].x=lis[pos1].x;
	clus[0][0].y=lis[pos1].y;
	clus[1][0].x=lis[pos2].x;
	clus[1][0].y=lis[pos2].y;
	inicluster(clus,i,lis);
	itrations(i,clus);
	return 0;
}
		
	
