//BOJ 19702,2323 AC CODE
#include<bits/stdc++.h>
#include<random>
#define all(v) v.begin(),v.end()
using namespace std;
using ll = long long;


mt19937_64 seed(20240623);
uniform_real_distribution<double>rng(0, 1);

random_device rd;
mt19937 gen(rd());
ll C[1111][1111],n,m;
class state{
    public:
    vector<int>arr,cur;
    ll val=0;
    state(int n){
        arr.resize(n);
        cur.resize(n);
        for(int i=0;i<n;i++)arr[i]=i;
        uniform_int_distribution<int>R(0,n-1);
        for(int i=0;i<n*2;i++){
            int a=R(gen),b=R(gen);
            swap(arr[a],arr[b]);
        }
        cal();
    }
    void cal(){
        val=0;
        for(int i=0;i<n;i++){
            int a=(i+n-1)%n;
            if(C[arr[i]][arr[a]])val++,cur[i]++;
        }
    }
};

void mutate(state& S){
    uniform_int_distribution<int>R(0,n-1);
    int a=R(gen),b=R(gen);
    set<int>st;
    for(int i=-1;i<=1;i++){
        st.insert((a+i+n)%n);
        st.insert((b+i+n)%n);
    }
    swap(S.arr[a],S.arr[b]);
    for(auto nxt:st){
        if(S.cur[nxt])S.val--;
        S.cur[nxt]=0;
        int a=(nxt+n-1)%n;
        if(C[S.arr[nxt]][S.arr[a]]){
            S.cur[nxt]++;
            S.val++;
        }
    }
}
//LEN : fitness array의 length를 표기.
int inc(int x,int mod){
    return (x+1)%mod;
}
state dlas(state cur,ll LEN,ll iter_lim){
    state res_state=cur;
    ll ret=0,idx=0;
    vector<ll>fitness(LEN);
    for(int i=0;i<LEN;i++)fitness[i]=cur.val;
    vector<state>S{cur,cur,cur};

    ll now=0,cur_pos=0,curf=cur.val;
    for(int it=0;it<iter_lim;it++){
        ll pre=now,pref=curf;
        ll nxt_pos=inc(cur_pos,3);
        if(nxt_pos==cur_pos)cur_pos=inc(cur_pos,3);

        auto &curS=S[cur_pos],&nxtS=S[nxt_pos];
        nxtS=curS;
        mutate(nxtS);
        ll nxtf=nxtS.val;
        if(nxtf>res_state.val){
            it=0;
            res_state=nxtS;
        }
        if(nxtf==curf || nxtf>*(min_element(fitness.begin(),fitness.end()))){
            cur_pos=nxt_pos;
            curf=nxtf;
        }
        auto &fit=fitness[idx];
        if(curf < fit || (curf>fit && curf>pref)){
            fit=curf;
            //만약 새로운상태가 fit[idx]보다 안 좋으면 바로 채택(diversify);
            //fit[idx]보다도 좋고, 이전것보다도 좋아지면 채택 (intesify)
        }
        idx=inc(idx,LEN);
    }

    return res_state;
}
void solve(){
    cin>>n>>m;
    while(m--){
        ll a,b;
        cin>>a>>b;
        a--,b--;
        C[a][b]=C[b][a]=1;
    }
    state res(n);
    for(int i=0;i<5;i++){
        state now(n);
        //cout<<i<<' '<<now.val<<endl;
        //for(auto nxt:now.arr)cout<<nxt+1<<' ';
        now=dlas(now,5,100000);
        //cout<<endl;
        if(now.val>res.val)res=now;
    }
    cout<<n-res.val<<endl;
    for(auto nxt:res.arr)cout<<nxt+1<<' ';
    return;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
    solve();
       
}
