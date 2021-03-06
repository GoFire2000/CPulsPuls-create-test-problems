#include <queue>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
#define LL long long
#define Inf 1e9
const int maxn=310;
struct Node{
	int x,y,z,dis,tp;
	Node(){};
	Node(int xx,int yy,int zz,int _dis=0,int _tp=0){
		x=xx;y=yy;z=zz;
		dis=_dis;tp=_tp;
	}
}S,T;
int n,m,h; 
bool flag[maxn][maxn][maxn][3];//0:无防弹衣，1：拿到但未用，2：拿到已用 
char s[maxn][maxn][maxn];
const int dx[8]={0,0,1,-1,0,0};
const int dy[8]={1,-1,0,0,0,0};
const int dz[8]={0,0,0,0,1,-1};
queue<Node> q;
void NextPos(int &x,int &y,int &z){
	x=(x+n)%n;
	y=(y+m)%m;
	z=(z+h)%h;
}
int Bfs(){
	q.push(S);flag[S.x][S.y][S.z][0]=true;
	while(!q.empty()){
		Node tmp=q.front();q.pop();
		if(tmp.x==T.x && tmp.y==T.y && tmp.z==T.z) return tmp.dis;
		for(int i=0;i<6;i++){
			int xx=tmp.x+dx[i],yy=tmp.y+dy[i],zz=tmp.z+dz[i];
			NextPos(xx,yy,zz);
			if(tmp.tp==1){
				if(s[xx][yy][zz]=='#') {
					if(!flag[xx][yy][zz][2]) {
						q.push(Node(xx,yy,zz,tmp.dis+1,2));
						flag[xx][yy][zz][2]=true;
					}
				}else {
					if(!flag[xx][yy][zz][1]){
						q.push(Node(xx,yy,zz,tmp.dis+1,1));
						flag[xx][yy][zz][1]=true;
					}
				}
			}else if(tmp.tp==0){
				if(s[xx][yy][zz]=='P'){
					if(!flag[xx][yy][zz][1]){
						q.push(Node(xx,yy,zz,tmp.dis+1,1));
						flag[xx][yy][zz][1]=true;	
					}
				}else if(s[xx][yy][zz]!='#'){
					if(!flag[xx][yy][zz][0]){
						flag[xx][yy][zz][0]=true;
						q.push(Node(xx,yy,zz,tmp.dis+1,0));
					}
				}
			}else if(tmp.tp==2){
				if(s[xx][yy][zz]!='#'){
					if(!flag[xx][yy][zz][2]){
						flag[xx][yy][zz][2]=true;
						q.push(Node(xx,yy,zz,tmp.dis+1,2));
					}
				}
			}
		}
	}
	return -1;
}
void Init();
int main(){
	Init();
	return 0;
}
void Init(){
	scanf("%d%d%d",&n,&m,&h);
	for(int k=0;k<h;k++){
		for(int i=0;i<n;i++){
			for(int j=0;j<m;j++){
				scanf(" %c",&s[i][j][k]);
				if(s[i][j][k]=='S') S=Node(i,j,k);
				else if(s[i][j][k]=='T') T=Node(i,j,k);			
			}
		}
	}
	int nowx=max(S.x,T.x)-min(S.x,T.x); 
	int movex=min(nowx,n-nowx);
	int nowy=max(S.y,T.y)-min(S.y,T.y); 
	int movey=min(nowy,m-nowy);
	int nowz=max(S.z,T.z)-min(S.z,T.z); 
	int movez=min(nowz,h-nowz);
	printf("%d\n",movex+movey+movez);
}
/*
3 3 3
SP#
**#
##*

##*
##*
***

##*
###
*#T

6
*/
