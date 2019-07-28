#include <iostream>
#include <vector>
#include <stack>
#include <cstdio>
#include <utility>

using namespace std;

vector <int> v;
vector <char> z; 
//vector <int> x;
//vector <vector <int>> a;
int n, m;
string s;

void print( int n, int val ) {
	cout<<"Case #"<<n<<": "<<val<<"\n"; 
}

char comp( char a ) {
	if( a == 'x') return 'X';
	else return 'x'; 
}

bool isin( char ch ) {
	if( ch == 'x' || ch == 'X' ) return false; else return true; 
}

char to( int a ) {
	if( a == 1 ) return '1'; else return '0';
}

char e( char a, char b, char c ) {
	int aa = a-'0'; int cc = c-'0';
	if( b == '|' ) return to(aa|cc);
	else if( b == '&' ) return to(aa&cc);
	else if( b == '^' ) return to(aa^cc);
	return '1';
}

void d( int i, char a, char b, char c ) {
	//cout<<"-"<<i<<"-"<<a<<"-"<<b<<"-"<<c<<"\n";
	if( (a == '1' || a == '0') && (b == '1' || b == '0') ) z[i] = e(a,c,b);
	else if( a == '1' || b == '1' ) {
		char ch; if( a == '1') ch = b; else ch = a; 
		if( c == '|' ) z[i] = '1';
		else if( c == '^' ) z[i] = comp(ch);
		else if( c == '&' ) z[i] = ch;
	} 
	else if( a == '0' || b == '0' ) {
		char ch; if( a == '0') ch = b; else ch = a; 
		if( c == '|' ) z[i] = ch;
		else if( c == '^' ) z[i] = ch;
		else if( c == '&' ) z[i] = '0';
	} 
	else if( a == b ) {
		if( c == '^' ) z[i] = '0';
		else z[i] = a;
	} else if( c == '^' || c == '|' ) z[i] = '1';
	else z[i] = '0';
}

void eval( int i ) {
	if( v[i]-i == 4 ) {
		d( i, s[i+1], s[i+3], s[i+2] );
		return;
	}
	if( s[i+1] == '(' ) {
		int h = v[i+1]; 
		eval(i+1);
		if( s[h+2] == '(' ) {
			eval(h+2);
		}
		else z[h+2] = s[h+2], v[h+2] = h+2;
		d(i,z[i+1],z[h+2],s[h+1]);
	}
	else {
		z[i+1] = s[i+1]; v[i+1] = i+1;
		if( s[i+3] == '(' ) {
			eval(i+3);
		}
		else z[i+3] = s[i+3], v[i+3] = i+3;
		d(i,z[i+1],z[i+3],s[i+2]);
	}
}
/*
int makeopp( int i ){
	if( i == v[i] ) return 1;
	else if( a[0][i] != -1 ) return a[0][i];
	else{
		int h = v[i];
		bool aa = isin(z[i+1]), bb = isin(z[h+2]); 
		if( ( !aa && bb ) || ( aa && !bb ) ) a[i][0] = (!aa)?makeopp(i+1):makeopp(h+2);
		else if( !aa && !bb ) a[i][0] = ;
	}
}

int make1( int i ){
	if( i == v[i] ) return 1;
	else if( a[1][i] != -1 ) return a[1][i];
}

int make0( int i ){
	if( i == v[i] ) return 1;
	else if( a[2][i] != -1 ) return a[2][i];
}

void change( int i ) {
	int h = v[i];
	bool aa = isin(z[i+1]), bb = isin(z[h+2]); 
	if( (!aa)&&(!bb) ) {
		if( s[h+1] == '|' || s[h+1] == '&' ) {
			int a = makeopp(i+1); a = min(a,makeopp(h+2)); a = min(a,(s[h+1] == '|')? min(make1(i+1),make1(h+2)):min(make0(i+1),make0(h+2)));
			x[i] = a;
		}
	}
	else if( !aa || !bb ) {
		int a=INT_MAX;
		if( s[h+1] == '^' ) a = min(a,(!aa)?min(make1(i+1),make0(i+1)):min(make1(h+2),make0(h+2)));
		else if( s[h+1] == '|' ) a = min(a,(!aa)?make1(i+1):make1(h+2));
		else a = min(a,(!aa)?make0(i+1):make0(h+2));
		x[i] = a;
	}
	else x[i] = 0;
}*/

int main() {
	freopen("in (1).txt", "r", stdin);
	freopen("a3.txt","w",stdout);
	cin>>n; char ch = getchar();
	for( int i = 1; i <= n; i++ ) {
		getline(cin,s,'\n');
		v.clear(); z.clear(); //x.clear(); a.clear();
		m = s.length();
		if( m == 1 ) {
			if( s[0] == '1' || s[0] == '0' ) print(i,0); else print(i,1); continue;
		}
		v.assign(m,-1); z.assign(m,'?'); //x.assign(m,-1); a.assign(3,vector<int>(m,INT_MAX)); 
		stack<pair<int,char> > ss;
		for( int j = 0; j < m ; j++ ) {
			if( s[j] == '(' ) ss.push({j,'('});
			else if( s[j] == ')' ) {
				pair<int,char> y = ss.top(); 
				if( y.second == '(' ) {
					ss.pop(); v[y.first] = j; v[j] = y.first;
				} else ss.push({j,')'});
			}
		}
		eval(0);
	//	for( int i = 0; i < m; i++ ) cout<<v[i]<<" "; cout<<"\n";
	//	for( int i = 0; i < m; i++ ) cout<<z[i]<<" "; cout<<"\n";
	//	for( int i = 0; i < m; i++ ) cout<<s[i]<<" "; cout<<"\n";
		if( z[0] == '1' || z[0] == '0' ) print(i,0);
		else print(i,1);
	}	
	return 0;
}
