#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
using namespace std;
#define MAXN 1000000
#define lc(x) (x<<1)
#define rc(x) ((x<<1)|1)
#define mx(x) t[x].mx
#define lz(x) t[x].lz
#define mid ((lef+rig)>>1)
int read()
{
	char ch=getchar();int f=0,x=1;
	while(ch<'0'||ch>'9'){if(ch=='-') x=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){f=(f<<1)+(f<<3)+ch-'0';ch=getchar();}
	return f*x;
}
struct Node
{
    int mx,lz;
};
struct Segment_Tree
{
    Node t[MAXN+5];
    int dat[MAXN+5];
    void Push(int cur)
    {
        mx(cur) = mx(lc(cur)) + mx(rc(cur));
        return;
    }
    void Lazy(int cur, int lef, int rig)
    {
        if(lz(cur))
        {
            mx(lc(cur)) = (lz(cur)-1)*(mid-lef+1);
            mx(rc(cur)) = (lz(cur)-1)*( rig-mid );
            lz(lc(cur)) = lz(cur);
            lz(rc(cur)) = lz(cur);
            lz(cur) = 0;
        }
        return;
    }
    void Build(int cur, int lef, int rig)
    {
        if(lef == rig)
        {
            mx(cur) = dat[lef], lz(cur) = 0;
            return;
        }
        Build(lc(cur),lef,mid);
        Build(rc(cur),mid+1,rig);
        Push(cur);
        return; 
    }
    int Query(int cur, int lef, int rig, int L, int R)
    {
        Lazy(cur,lef,rig);
        if(L == lef && R == rig)
            return mx(cur);
        if(R <= mid)
            return Query(lc(cur),lef,mid,L,R);
        if(L >  mid)
            return Query(rc(cur),mid+1,rig,L,R);
        return Query(lc(cur),lef,mid,L,mid)+Query(rc(cur),mid+1,rig,mid+1,R);
    }
    void Edit(int cur, int lef, int rig, int L, int R, int x)
    {
        Lazy(cur,lef,rig);
        if(L == lef && R == rig)
        {
            mx(cur) = x*(rig-lef+1);
            lz(cur) = x+1;
            return;
        }
        if(R <= mid)
            Edit(lc(cur),lef,mid,L,R,x);
        else if(L >  mid)
            Edit(rc(cur),mid+1,rig,L,R,x);
        else
            Edit(lc(cur),lef,mid,L,mid,x),Edit(rc(cur),mid+1,rig,mid+1,R,x);
        Push(cur);
        return;
    }
};
struct Edge
{
    int to,nex;
    Edge(){}
    Edge(int _to, int _nex):to(_to),nex(_nex){}
};
Edge e[MAXN+5];
int first[MAXN+5],tot;
void Add(int a, int b)
{
    e[tot] = Edge(b,first[a]);
    first[a] = tot++;
    return;
}
int pos[MAXN+5],dep[MAXN+5],fa[MAXN+5],top[MAXN+5],sz[MAXN+5],heavy[MAXN+5],bound[MAXN+5],n,m,dfn;
char s[20];
void DFS1(int p, int father)
{
    sz[p] = 1;
    for(int u = first[p]; u != -1; u = e[u].nex)
        if(e[u].to != father)
        {
            fa[e[u].to] = p, dep[e[u].to] = dep[p]+1, DFS1(e[u].to,p), sz[p] += sz[e[u].to];
            if(!heavy[p] || sz[e[u].to] >= sz[heavy[p]])
                heavy[p] = e[u].to;
        }
    return;
}
void DFS2(int p)
{
    bound[p] = pos[p];
    if(heavy[p])
        pos[heavy[p]] = dfn++, top[heavy[p]] = top[p], DFS2(heavy[p]), bound[p] = max(bound[p],bound[heavy[p]]);
    for(int u = first[p]; u != -1; u = e[u].nex)
        if(e[u].to != heavy[p] && e[u].to != fa[p])
            pos[e[u].to] = dfn++, top[e[u].to] = e[u].to, DFS2(e[u].to), bound[p] = max(bound[p],bound[e[u].to]);
    return;
}
Segment_Tree T;
int Qroot(int p)
{
    int ans = 0;
    while(p)
        ans += T.Query(1,1,n,pos[top[p]],pos[p]), p = fa[top[p]];
    return ans;
}
void Eroot(int p)
{
    while(p)
        T.Edit(1,1,n,pos[top[p]],pos[p],1), p = fa[top[p]];
    return;
}
int main()
{
	freopen("manager.in","r",stdin);
	freopen("manager.out","w",stdout);
    scanf("%d",&n), memset(first,-1,sizeof(first));
    for(int i = 2, a; i <= n; i++)
        a=read(), Add(a+1,i);
    fa[1] = 0, dep[1] = 1, top[1] = 1, pos[1] = 1, dfn = 2, DFS1(1,0), DFS2(1), T.Build(1,1,n);
    scanf("%d",&m);
    for(int i = 1, x, a, b; i <= m; i++)
    {
        scanf("%s",s), x=read(), x++;
         if(s[0] == 'i')
             a = Qroot(x), Eroot(x), b = Qroot(x);
        else
            b = T.Query(1,1,n,pos[x],bound[x]), T.Edit(1,1,n,pos[x],bound[x],0), a = T.Query(1,1,n,pos[x],bound[x]);
        printf("%d\n",b-a);
    }
    return 0;
}
