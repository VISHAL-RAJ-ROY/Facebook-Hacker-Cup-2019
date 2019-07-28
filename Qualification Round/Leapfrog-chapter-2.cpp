#include <iostream>
#include <cstdio>

/*
n-1 odd then n/2
n-1 even then n-1/2 atleast
aur atmax n-2*/


using namespace std;

void print( char g, int i ) {
	cout<<"Case #"<<i<<": "<<g; cout<<"\n";
}

int main()
{
	freopen("leapfrog_ch_.txt", "r", stdin);
	freopen("a2.txt", "w", stdout);
	int n; cin>>n;char ch;
	for( int i = 1; i <= n; i++ ) {
		ch = getchar();
	/*	cout<<i;
		cout<<"-"<<ch<<"-";*/
		int b = 0; int tot = 1;
		while( true ) {
			ch = getchar(); 
		//	cout<<"-"<<ch<<"-";
			if( ch == '\n' ) break;
			tot++;
			if( ch == 'B' ) b++;
		}
		if( tot == 2 ) print('N',i);
		else if( !b ) print('N',i); 
		else if( b == tot-2 ) print('Y',i);
		else if( b > tot-2 )  print('N',i);
		else if( b >= 2 ) print('Y',i);
		else print('N',i); 
	}
	return 0;
}
