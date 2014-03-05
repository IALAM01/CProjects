//Isfaqual Alam
//Number Cross
//Each number cannot be vertically, horizontally or diagonally adjacent to a value 1 less than it or 1 greater than it (ex. 6 cannot be near 7 or 8)
//CS211
#include <iostream> 
#include <cmath> 
using namespace std;

/* The board looks like this

		1	2
	0	3	4	7	
		5	6

*/ 

bool ok(int cross[], int col)
{

	int help[][4] = 
	{
		{-1},			//0
		{0,-1},			//1
		{1, -1},		//2
		{0, 1, 2, -1},	//3
		{1, 2, 3, -1},	//4
		{0, 3, 4, -1},	//5
		{3, 4, 5, -1},	//6
		{2, 4, 6, -1}	//7
	};
	
	
	for (int i=0; i<col; ++i)				//check to see if number has been used
	{
		if (cross[col] == cross[i]) {return false;}
	}

	for (int j=0; help[col][j]!=-1; j++)	//checks each column in helper array until -1
	{
		if(1 == abs( cross[col]-cross[ help[col][j] ] )) {return false;}
	}
    return true;
}
 
void backtrack(int &col)
{
	col--;
	if(col==-1){ system("PAUSE"); exit(1);}
}
 
void print(int q[]) //prints the number-cross
{ 
    static int count =0; 
    cout << "Solution: " << ++count << endl; 
	cout << endl;
	cout << "  "<< q[1]+1 << " "<< q[2]+1 << endl;  //+1 to show numbers as 1 2 3 4 5 6 7 8 and not 0 1 2 3 4 5 6 7
	cout << q[0]+1 << " "<< q[3]+1 << " "<< q[4]+1 << " "<< q[7]+1 <<endl;
	cout << "  "<< q[5]+1 << " "<< q[6]+1 << endl;
	cout <<endl;
} 
 
int main()
{
        
    int q[8], c=0;
	q[0] = 0;

	bool from_backtrack=false;

	while(true)
	{
		while(c<8)
		{
			if(!from_backtrack) {q[c] = -1;} //Start at the top
			from_backtrack=false;
			while(q[c]<8) 
			{ 
				q[c]++;
				if  (q[c]==8)
				{
					backtrack(c);
					continue;
				}
				if( ok(q,c) ) break; //get out of the closest while loop
			}
			c++;
		}
		print(q);
		backtrack(c); 
		from_backtrack=true;
	}

	system("PAUSE");
	return 0;
 
}