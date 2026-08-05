//base code->1bin 
//https://github.com/1bin01/algorithm/blob/main/geometry/template.cpp
struct pt{
    ll x, y;
    pt operator + (pt t){return {x + t.x, y + t.y};}
    pt operator - (pt t){return {x - t.x, y - t.y};}
    ll operator * (pt t){return x * t.x + y * t.y;}
    ll operator / (pt t){return x * t.y - y * t.x;}
    bool operator == (const pt t)const{return x == t.x && y == t.y;}
    bool operator <(const pt t)const{return x == t.x ? y < t.y : x < t.x;}
    ll sz(){return x * x + y * y;}
    
    pt mul(ll m){return {x * m, y * m};}
};

// 실수 좌표 점
struct pd{
    double x, y;
    pd(){};
    pd(double x, double y) : x(x), y(y) {};
    //pd(pt t) : x(t.x), y(t.y) {};
    
    pd operator +(pd t){return {x + t.x, y + t.y};}
    pd operator -(pd t){return {x - t.x, y - t.y};}
    double operator * (pd t){return x * t.x + y * t.y;}
    double operator / (pd t){return x * t.y - y * t.x;}
    // *등호 사용시 주의
    //bool operator == (const pd t)const{return x == t.x && y == t.y;}
    //bool operator <(const pd t)const{return x == t.x ? y < t.y : x < t.x;}
    //
    double sz(){return x * x + y * y;}
};

int ccw(pt a, pt b, pt c){
    b = b - a; c = c - a;
    return (b / c > 0) - (b / c < 0);
}

// 선분 교차 판정
bool intersect(pt p1, pt p2, pt p3, pt p4){
    int a = ccw(p1, p2, p3) * ccw(p1, p2, p4);
    int b = ccw(p3, p4, p1) * ccw(p3, p4, p2);
    if(!a && !b){
        if(p2 < p1) swap(p1, p2);
        if(p4 < p3) swap(p3, p4);
        return !(p2 < p3 || p4 < p1);
    }
    return a <= 0 && b <= 0;
}

// 두 선분의 교점 구하기
bool getpoint(pt p1, pt p2, pt p3, pt p4, pt& p){
    double d = (p4.y - p3.y) * (p2.x - p1.x) - (p4.x - p3.x) * (p2.y - p1.y);
    double t = (p4.x - p3.x) * (p1.y - p3.y) - (p4.y - p3.y) * (p1.x - p3.x);
    double s = (p2.x - p1.x) * (p1.y - p3.y) - (p2.y - p1.y) * (p1.x - p3.x);
    if(!d){
        // t == 0 : 동일한 선
        
        // t != 0 : 평행
        if(p2 < p1) swap(p1, p2);
        if(p4 < p3) swap(p3, p4);
        
        // 한 점에서 만나는 경우
        if(p2 == p3) {
            p = p2; return 1;
        }    
        if(p4 == p1){
            p = p4; return 1;
        }
        return 0;
    }
    t /= d; s /= d;
    // t >= 0 && t <= 0 : 교점 존재
    p.x = p1.x + (p2.x - p1.x) * t;
    p.y = p1.y + (p2.y - p1.y) * t;
    return 1;
}

// 두 점 사이의 거리 (제곱)
ll dist(pt a, pt b){ return (b - a).sz(); }

// 직선(선분)과 점의 거리
double linedist(pt a, pt b, pt c){
    pt t = b - a;
    // 선분일 경우
    if(t * (c - a) <= 0) return sqrt(dist(a, c));
    if(t * (c - b) >= 0) return sqrt(dist(b, c));
    //   
    return abs(t / (c - a)) / sqrt(t.sz());
}

// 다각형의 넓이 O(n)
double area(vector<pt>& v){
    double ret = 0;
    for(int i = 0, n = v.size(); i < n; i++)
        ret += v[i] / v[(i + 1) % n];
    return abs(ret) / 2.0;
}

// ConvexHull O(nlogn)
vector<pt> hull(vector<pt> v){
    int ix = min_element(all(v)) - v.begin();
    swap(v[0], v[ix]);
    vector<pt> st;
    
    sort(v.begin() + 1, v.end(), [&] (pt& a, pt& b){
       pt x = a - v[0], y = b - v[0];
       return x / y ? x / y > 0 : x.sz() < y.sz();
    });
    for(auto& p : v){
        while(st.size() > 1 && ccw(st[st.size() - 2], st.back(), p) <= 0) st.pop_back();
        st.emplace_back(p);
    }
    
    /*
    # 마지막 점들이 일직선 상에 있는 경우에 예외처리를 해야 하는 경우
    int i = v.size() - 1;
    while(i >= 1 && !ccw(v[0], v[i], v[i - 1])) i--;
    reverse(v.begin() + i, v.end());
    */
    return st;
}

// 삼각형 내부의 점 판별 O(1)
int inTriangle(vector<pt>& t, pt p){
    int sign[3];
    for(int i = 0; i < 3; i++)
        sign[i] = ccw(t[i], t[(i + 1) % 3], p);
    if(sign[0] == sign[1] && sign[1] == sign[2]) return -1;
    for(int i = 0; i < 3; i++) if(sign[i] * sign[(i + 1) % 3] == -1) return 1;
    return 0;
}

// 볼록 다각형 내부의 점 판별 O(n)
int inside(pt p, vector<pt>& v){
    if(v.size() < 3) return 0;
    for(int i = 0, n = v.size(); i < n; i++)
        if(ccw(v[i], v[(i + 1) % n], p) <= 0) return 0;
    return 1;
}

// 볼록 다각형 내부의 점 판별 O(logn)
// p가 다각형의 변이나 꼭짓점 위에 있지 않다고 가정
int inside(pt p, vector<pt>& v){
    int n = v.size();
    if(n < 3 || ccw(v[0], v[1], p) < 0 || ccw(v[0], v[n - 1], p) > 0) return 0;
    
    int l = 2, r = n - 1, m;
    while(l < r){
        m = (l + r) / 2;
        if(ccw(v[0], v[m], p) < 0) r = m;
        else l = m + 1;
    }
    return ccw(v[l - 1], p, v[l]) < 0;
}


//삼각형의 외접원의 중심을 return
pd get_circle_center(pd a,pd b,pd c){
	pd aa=b-a,bb=c-a;
	auto c1 = aa*aa * 0.5, c2 = bb*bb * 0.5;
    auto d = aa / bb;
    auto x = a.x + (c1 * bb.y - c2 * aa.y) / d;
    auto y = a.y + (c2 * aa.x - c1 * bb.x) / d;
    return pd(x, y);
}

/*
    Additional Geometry Algorithms

    필요한 기존 함수 및 연산:
    - ccw(a, b, c)
    - intersect(a, b, c, d)
    - pt operator-(pt)
    - a / b : cross product
    - p.sz() : x^2 + y^2
*/


/*------------------------------------------------------------*
 | 1. Point in General Simple Polygon
 *------------------------------------------------------------*/

// 일반 simple polygon에서 점 p의 위치를 O(n)에 판정
//
// 조건:
// - polygon은 self-intersecting하지 않는 simple polygon
// - 꼭짓점 순서는 CW, CCW 어느 쪽이어도 가능
// - v[0]을 맨 뒤에 다시 넣지 않은 상태
//
// return:
// 0 = outside
// 1 = inside
// 2 = boundary
//
// ray casting:
// p에서 오른쪽으로 반직선을 쏘았을 때
// polygon의 변과 교차하는 횟수의 홀짝을 확인한다.
//
// 꼭짓점을 두 번 세지 않기 위해
// a.y <= p.y < b.y와 같은 half-open interval을 사용한다.
int inside_polygon(pt p, vector<pt>& v){
    int n = v.size();
    bool in = 0;

    for(int i = 0; i < n; i++){
        pt a = v[i];
        pt b = v[(i + 1) % n];

        // 선분 ab와 점 p가 교차한다
        // <=> p가 polygon의 변 또는 꼭짓점 위에 있다.
        if(intersect(a, b, p, p))
            return 2;

        // 아래에서 위로 올라가는 변과 오른쪽 ray가 교차
        if(a.y <= p.y && p.y < b.y && ccw(a, b, p) > 0)
            in ^= 1;

        // 위에서 아래로 내려가는 변과 오른쪽 ray가 교차
        if(b.y <= p.y && p.y < a.y && ccw(a, b, p) < 0)
            in ^= 1;
    }

    return in ? 1 : 0;
}


/*------------------------------------------------------------*
 | 2. Polar Angle Sort
 *------------------------------------------------------------*/

// 벡터를 polar angle 기준으로 두 반평면으로 나눈다.
//
// true:
// 양의 x축을 포함하는 위쪽 반평면
//
// false:
// 음의 x축을 포함하는 아래쪽 반평면
bool upper(pt p){
    return p.y > 0 || (p.y == 0 && p.x >= 0);
}

// 원점 기준 polar angle comparator
//
// 정렬 순서:
// 양의 x축부터 시작하여 반시계 방향
//
// 같은 방향의 벡터는 길이가 짧은 것이 먼저 온다.
//
// 주의:
// - 영벡터 (0, 0)는 방향이 없으므로 가급적 넣지 않는다.
// - 기준점 o를 중심으로 정렬하려면
//   cmp_angle(a - o, b - o)로 비교한다.
/*
o 기준 정렬 *** v[0]-v[0]은 정의 안되서 v[1] 부터 정렬 해야 함 ***
pt o = v[0];

sort(v.begin() + 1, v.end(), [&](pt a, pt b){
    return cmp_angle(a - o, b - o);
});
*/

bool cmp_angle(pt a, pt b){
    bool ua = upper(a);
    bool ub = upper(b);

    if(ua != ub)
        return ua > ub;

    ll cr = a / b;

    if(cr != 0)
        return cr > 0;

    return a.sz() < b.sz();
}

/*
사용 예시 1: 원점 기준

sort(v.begin(), v.end(), cmp_angle);


사용 예시 2: 점 o 기준

sort(v.begin(), v.end(), [&](pt a, pt b){
    return cmp_angle(a - o, b - o);
});
*/


/*------------------------------------------------------------*
 | 3. Rotating Calipers: Convex Polygon Diameter
 *------------------------------------------------------------*/

// convex polygon에서 가장 먼 두 점 사이 거리의 제곱
//
// 조건:
// - h는 convex polygon
// - 꼭짓점은 CCW 순서
// - h[0]을 맨 뒤에 다시 넣지 않은 상태
//
// 시간복잡도: O(n)
//
// return:
// max |h[i] - h[j]|^2
ll diameter2(vector<pt>& h){
    int n = h.size();

    if(n <= 1)
        return 0;

    if(n == 2)
        return (h[0] - h[1]).sz();

    ll ret = 0;
    int j = 1;

    // directed edge h[i] -> h[ni]와 점 h[k]가 만드는
    // 평행사변형 넓이의 절댓값
    auto area2 = [&](int i, int ni, int k){
        return abs((h[ni] - h[i]) / (h[k] - h[i]));
    };

    for(int i = 0; i < n; i++){
        int ni = (i + 1) % n;

        // 현재 edge (i, ni)에서 가장 먼 반대편 점까지 j를 이동
        //
        // convexity에 의해 다음 edge로 넘어가도
        // 최적의 j는 뒤로 돌아가지 않으므로 전체 O(n)
        while(area2(i, ni, (j + 1) % n)
            > area2(i, ni, j)){
            j = (j + 1) % n;
        }

        ret = max(ret, (h[i] - h[j]).sz());
        ret = max(ret, (h[ni] - h[j]).sz());
    }

    return ret;
}

/*
사용 예시:

vector<pt> h = hull(v);

ll d2 = diameter2(h);          // 최대 거리의 제곱
double d = sqrt((double)d2);    // 실제 최대 거리
*/
