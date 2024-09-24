#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;
using namespace __gnu_cxx;
template <typename T>
using oset = tree<T, null_type, greater<T>,rb_tree_tag, tree_order_statistics_node_update>;
//mt19937 rng(chrono::system_clock::now().time_since_epoch().count());
//uniform_int_distribution<int> random(1, 1000000);
#define ll long long
#define fast ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
#define pb push_back
#define ok cout<<"ok"<<endl<<flush;
#define endl '\n'
#define INF 1e16
const ll M =1e9+7;
const ll N =2e5+1;
void debug(vector<ll>&v){for(auto it:v){cout<<it<<" ";}cout<<endl;}
ll n,m;
//https://www.hackerearth.com/practice/data-structures/disjoint-data-strutures/basics-of-disjoint-data-structures/practice-problems/algorithm/city-and-campers-2/
int par[N];
vector<oset<ll>>S(N);
void Make(int i)
{
    par[i]=i;
    S[i].insert(i);
}
int Find(int i)
{
    if(par[i]==i){return i;}
    return par[i] = Find(par[i]);
}
void mrg(int x,int y)
{
    x = Find(x);
    y = Find(y);
    if(x!=y)
    {
        if(S[x].size()<S[y].size()){swap(x,y);}
        par[y]=x;
        for(auto it:S[y])
        {
            S[x].insert(it);
        }
        S[y].clear();
    }
}
void solve()
{
    ll i,x,y,z;
    cin>>n>>m;
    for(i=1;i<=n;i++)
    {
        par[i]=i;
        S[i].insert(i);
    }
    while(m--)
    {
        cin>>z>>x>>y;
        if(--z)
        {
            ll z=Find(x);
            if(S[z].size()<y){cout<<-1<<endl;}
            else{cout<<*S[z].find_by_order(y-1)<<endl;}
        }
        else
        {
            mrg(x,y);
        }
    }


}
int32_t main()
{
    int i,j,k,n,m,q,tc=1,cs=0,ans,f;//cin>>tc;
    while(tc--)
    {
        solve();
    }
}
//https://atcoder.jp/contests/abc372/tasks/abc372_e
