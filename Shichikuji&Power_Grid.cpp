#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;
using namespace __gnu_cxx;
template <typename T>
using oset = tree<T, null_type, less<T>,rb_tree_tag, tree_order_statistics_node_update>;
mt19937 rng(chrono::system_clock::now().time_since_epoch().count());
uniform_int_distribution<int> random(1, 1000000);
#define ll long long
#define fast ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
#define pb push_back
#define ok cout<<"ok"<<endl<<flush;
#define endl '\n'
#define INF 1e16
const ll M =1e9+7;
const ll N =1e5+1;
void debug(vector<ll>&v){for(auto it:v){cout<<it<<" ";}cout<<endl;}
ll n,m;
vector<ll>par(N),sz(N),mn(N),ttl(N),build_in(N);
ll Find(ll x)
{
    if(par[x]==x){return x;}
    return par[x]=Find(par[x]);
}
void mrg(ll x, ll y, ll cst)
{
    x=Find(x);
    y=Find(y);
    if(x==y){return;}
    if(sz[x]<sz[y]){swap(x,y);}
    sz[x]+=sz[y];
    par[y]=x;
    ll temp1=ttl[x]+ttl[y]-max(mn[x],mn[y])+cst;
    if(mn[x]>mn[y])
    {
        build_in[x]=build_in[y];
    }
    ll temp2=min(mn[x],mn[y]);
    ttl[x]=temp1;
    mn[x]=temp2;
}
int32_t main()
{
    fast
    ll i,j,k,p,q,tc=1,cs=0;//cin >> tc;
    while(tc--)
    {
        cin>>n;
        vector<pair<ll,ll>>pos(n+1);
        vector<ll>build_cst(n+1),connection_cst(n+1),min_connection(n+1,INT_MAX),connected_to(n+1);
        for(i=1;i<=n;i++)
        {
            cin>>pos[i].first>>pos[i].second;
        }
        for(i=1;i<=n;i++)
        {
            cin>>build_cst[i];
            min_connection[i]=build_cst[i];
            connected_to[i]=i;
        }
        for(i=1;i<=n;i++)
        {
            cin>>connection_cst[i];
        }
        for(i=1;i<=n;i++)
        {
            par[i]=build_in[i]=i;
            sz[i]=1;
            ttl[i]=mn[i]=build_cst[i];
        }
        priority_queue<array<ll,3>,vector<array<ll,3>>,greater<array<ll,3>>>pq;
        for(i=2;i<=n;i++)
        {
            for(j=1;j<i;j++)
            {
                ll dist=abs(pos[i].first-pos[j].first)+abs(pos[i].second-pos[j].second);
                ll cst=dist*(connection_cst[i]+connection_cst[j]);
                pq.push({cst,j,i});
            }
        }
        vector<pair<ll,ll>>diff;
        ll ans=0;
        while(pq.size())
        {
            auto t=pq.top();
            pq.pop();
            ll x=t[1];
            ll y=t[2];
            ll cst=t[0];
            x=Find(x);
            y=Find(y);
            if(x==y){continue;}
            if(sz[x]<sz[y]){swap(x,y);}
            if(max(mn[x],mn[y])>cst){mrg(x,y,cst);diff.pb({t[1],t[2]});}

        }vector<ll>single;
        for(i=1;i<=n;i++)
        {
            if(par[i]==i)
            {
                ans+=ttl[i];
                single.pb(build_in[i]);
            }
        }
        cout<<ans<<endl;
        cout<<single.size()<<endl;
        debug(single);
        cout<<diff.size()<<endl;
        for(auto [x,y]:diff){cout<<x<<" "<<y<<endl;}
    }
}
//https://codeforces.com/problemset/problem/1245/D
/*
This problem needs a bit of midification over dsu. So I think its a among the problems that helps you to master the concept of dsu.
*/
