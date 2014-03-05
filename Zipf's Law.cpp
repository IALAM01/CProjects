#include<iostream>
#include<stdlib.h>
#include<vector>
#include<string>
#include<regex>
#include<cmath>
#include<algorithm>

using namespace std;

/*
Input
	The first line of input contains two integers n and m (1 ≤ n ≤ 50000, 1 ≤ m ≤ n), 
the number of songs on the album, and the number of songs to select. Then follow n lines. 
The i’th of these lines contains an integer fi and string si, where 0 ≤ fi ≤ 1012 is the number 
of times the i’th song was listened to, and si is the name of the song. Each song name is at most 
30 characters long and consists only of the characters ‘a’-‘z’, ‘0’-‘9’, and underscore (‘_’).

Output
	Output a list of the m songs with the highest quality qi, in decreasing order of quality. 
If two songs have the same quality, give precedence to the one appearing first on the album 
(presumably there was a reason for the producers to put that song before the other).
*/

class track{
	int fi; //number of times played
	string trackName;

	public:
		float qi;

		track( ){
			trackName = "";
			fi = 0;
		}

		track( string trackTitle ){
			/*
			std::smatch matcher;
			std::regex e("^[A-Za-z0-9_]+$");
			try{
				if (std::regex_search(trackTitle, matcher, e) )
					trackName = trackTitle;
			}
			catch(bool match){
				cout<<"Track name invalid"<<endl;
			}*/
			trackName = trackTitle;
			fi = 0;
		}

		track( int p, string trackTitle ){
			/*
			std::smatch matcher;
			std::regex e("^[A-Za-z0-9_]+$");
			try{
				if (std::regex_search(trackTitle, matcher, e) )
					trackName = trackTitle;
			}
			catch(bool match){
				cout<<"Track name invalid"<<endl;
			}*/
			trackName = trackTitle;
			fi = p;
		}

		int get_fi(){ return fi; }
		float get_qi(){ return qi; }
		string getTrackName(){ return trackName; }

		bool operator<(track compareToThis){
			if (qi<compareToThis.qi)
				return true;
			else return false;
		}
		
		void setfi(int i){fi = i; }
		void setTrackName(string setThis){ trackName = setThis; } 

		void calculate_qi( track first, int position ){
			float zi;

			zi = first.fi/(position+1);
			qi = fi/zi;
		}

		friend ostream& operator<<(ostream& os, track t);
		friend istream& operator>>(istream& is, track& t);
};

ostream& operator<<(ostream& os, track t){
	os<< t.fi << " " << t.trackName << endl;
	return os;
}

istream& operator>>(istream& is, track& t){
	is>> t.fi >> t.trackName;
	return is;
}

void swap( track &thisTrack, track &withThisTrack ){
	track temp;
	temp = thisTrack;
	thisTrack = withThisTrack;
	withThisTrack = temp;
}

//findPivotPosition
int findSplitPoint( std::vector<track> &a, track pivot, int beginIndex, int endIndex ){
	int leftWall = beginIndex;
	int rightWall = endIndex;

	while ( leftWall<rightWall ){
		while( pivot.qi < a[rightWall].qi && leftWall<rightWall ){
			--rightWall;
		}
		swap(a[leftWall],a[rightWall]);
		while( pivot.qi >= a[leftWall].qi && leftWall<rightWall ){
			++leftWall;
		}
		swap( a[rightWall], a[leftWall] );
	}
	return leftWall;
}

//quicksort
void quickSort( std::vector<track> &a, int beginIndex, int endIndex ){
	track Pivot = a[beginIndex];
	int splitPoint;
	track temp;

	if(endIndex>beginIndex){
		splitPoint = findSplitPoint( a, Pivot, beginIndex, endIndex );

		a[splitPoint] = Pivot;
		quickSort( a,   beginIndex, splitPoint-1 );
		quickSort( a, splitPoint+1, endIndex     );
	}
}


int main(){
	std::vector<track> album;
	int n,m;
	track first, temp;

	
	cout<<"Please enter the number of tracks in the album: \n";
	while (1){
		if ( !(cin>>n) ) {
			cout<<"Please enter a number between 1 and 50,000: \n";
			cin.clear();
		}
		else if (n<1 || n>50000){
			cout<<"Please enter a number between 1 and 50,000: \n";
			cin.clear();
		}
		else
			break;
	}//while
		
	cout<<"Please enter the number of high quality tracks to be chosen from the album: \n";
	while (1){
		if ( !(cin>>m) ) {
			cout<<"Please enter a number between 1 and "<<n<<": \n";
			cin.clear();
		}
		else if (m<1 || m>n){
			cout<<"Please enter a number between 1 and "<<n<<": \n";
			cin.clear();
		}
		else
			break;
	}//while
	
	cout<<"Please enter a number and the title of the track: \n";
	for (int i=0; i<n; i++){
		/*
		while(1){
			if (!(cin>>temp) ){
				cout<<"The name of the track can only have letters a-z, numbers 0-9 and _ : \n";
				cin.clear();
			}
			else{
				if(i == 0)
					first = temp;
			temp.calculate_qi(first, i);
			album.push_back(temp);
			break;
			}
		}//while
		*/
		cin>>temp;
			if(i == 0)
					first = temp;
			temp.calculate_qi(first, i);
			album.push_back(temp);
			
	}//for

	//std::sort( album.begin(), album.end() );
	quickSort(album, 0, album.size()-1 );

	for(int i=0; i<m; i++){
		cout<<album[i].qi<<" "<<album[i];
	}
	
	system("PAUSE");
	return 0;
}