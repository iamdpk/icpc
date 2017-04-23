#include<iostream>
using namespace std;

int LOG,n;
vector<int>g[100009];
int tmr,tin[100009],tout[100009];
int dp[100009][20];

void pre(){
  
  //finding ceil(logn)
  LOG=1;
  while((1<<LOG)<=n)
    ++LOG;
  
  for(int i=0;i<=100000;++i)
    for(int j=0;j<20;++j)
      dp[i][j]=0;
  
  tmr=0;
  dfs(1,0);
}

void dfs(int nd,int par){

  tin[nd]=++tmr;
  
  dp[nd][0]=par;
  for(int i=1;i<=LOG;++i)
    dp[nd][i]=dp[dp[nd][i-1]][i-1];
  
  for(auto ch:g[nd])
    if(ch!=par)
      dfs(ch,nd);
  
  tout[nd]=++tmr;

}

bool upper(int a,int b){
  //returns true iff b is in subtree of a
  return tin[a]<=tin[b]&&tout[a]>=tout[b];
}

int lca(int a,int b){
  //3 cases b is in subtree of a,  a is in bs subtree, different subtrees 
  
  if(upper(a,b))
    return a;
  if(upper(b,a))
    return b;
  
  //similar idea as in finding binary repn of num
  for(int i=LOG;i>=0;--i)
    if(!upper(dp[a][i],b))
      a=dp[a][i];
  
  return dp[a][0];//why always dp[a][0] what if odd???
}

int main(){

  cin>>n;
  for(int i=1;i<n;++i){
    int u,v;
    cin>>u>>v;
    g[u].push_back(v);
    g[v].push_back(u);
  }  
  pre();
  
  int q;
  cin>>q;
  for(int i=1;i<=q;++i){
    int u,v;
    cin>>u>>v;
    cout<<lca(u,v)<<endl;  
  }

  return 0;
}


