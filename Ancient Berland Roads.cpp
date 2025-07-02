#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;
using namespace __gnu_cxx;
template <typename T>
using oset = tree<T, null_type, less<T>,rb_tree_tag, tree_order_statistics_node_update>;
mt19937 rng(chrono::system_clock::now().time_since_epoch().count());
#define ll long long
#define fast ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
#define pb push_back
#define ok cout<<"ok"<<endl<<flush;
#define endl '\n'
#define INF 1e17
const ll M = 998244353;
const ll N = 1e6+1;
const ll LOG = 11;
void debug(vector<ll> v){for(auto it:v){cout<<it<<" ";}cout<<endl;}
ll n,m;
vector<ll>par(N),sz(N),people(N),g[N];
multiset<ll>st;
ll Find(ll x)
{
    if(par[x] == x){return x;}
    return par[x] = Find(par[x]);
}

void mrg(ll x, ll y)
{
    x = Find(x);
    y = Find(y);

    if(x == y){return;}

    if(sz[x] < sz[y])
    {
        swap(x,y);
    }

    sz[x]+=sz[y];
    st.erase(st.find(people[x]));
    st.erase(st.find(people[y]));
    people[x]+=people[y];
    st.insert(people[x]);
    par[y]=x;
}
int32_t main()
{
    fast
    ll i,j=1,k,p,q,tc=1,cs=0;
    //cin>>tc;
    while(tc--)
    {
        cin >> n >> m >> q;

        vector<ll>rem(m);
        for(i=1;i<=n;i++){cin>>people[i];}

        vector<pair<ll,ll>>edges;
        vector<array<ll,3>>queries;

        for(i=0;i<m;i++)
        {
            ll x, y;
            cin>>x>>y;
            edges.pb({x,y});
        }

        for(i=0;i<q;i++)
        {
            char c;
            cin>>c;
            ll x,y;
            if(c == 'P')
            {
                cin>>x>>y;
                queries.pb({x,y,people[x]});
                people[x] = y;
            }
            else
            {
                cin>>x;
                queries.pb({x-1,-1,-1});
                rem[x-1] = 1;
            }
        }
        for(i=1;i<=n;i++)
        {
            par[i] = i;
            sz[i] = 1;
            st.insert(people[i]);
        }
        i=0;
        for(auto [x,y] : edges)
        {
            if(rem[i++]){continue;}
            mrg(x,y);
        }
        vector<ll>ans;
        reverse(queries.begin(),queries.end());

        for(auto [x,y,z]:queries)
        {
            ans.pb(*--st.end());

            if(y == -1)
            {
                mrg(edges[x].first,edges[x].second);
            }
            else
            {
                ll t = Find(x);
                auto it = st.find(people[t]);
                st.erase(it);
                people[t] = people[t] - y + z;
                st.insert(people[t]);
            }
        }
        reverse(ans.begin(),ans.end());
        for(auto it:ans){cout<<it<<endl;}
    }
}
