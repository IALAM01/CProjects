#include <iostream>
#include <cmath>
using namespace std;

typedef char box[5][7];

void print(int q[]) {
	int i,j,k,l;
	box bq, wq, bb, wb, *board[8][8];
	static int count = 0;
	cout<<++count<<endl;
		//fill in wb=whiteboard and bb=blackboard
		for(i=0;i<5;i++){
				for(j=0;j<7;j++){
					wb[i][j]=' ';
					bb[i][j]=char(219);
				}
		}
		// black queen on white square
		for(i=0;i<5;i++){
			for(j=0;j<7;j++){
				if ( (i==1 && j%2==1) || ( (i==2 || i==3) && (j>0 && j<6) ) )
					bq[i][j]=char(219);
				else
					bq[i][j]=' ';
			}
		}
		// white queen on black square
		for(i=0;i<5;i++){
			for(j=0;j<7;j++){
				if ( (i==1 && j%2==1) || ( (i==2 || i==3) && (j>0 && j<6) ) )
					wq[i][j]=' ';
				else
					wq[i][j]=char(219);
			}
		}
		//fill board[][] with addresses of wb and bb
		for (i=0;i<8;i++){
			for(j=0;j<8;j++){
				if ((i+j)%2==0) 
				{board[i][j]= &wb;}
				else 
				{board[i][j]= &bb;}
			}
		}
		//change values of board[][] if there is a queen in it
		for (i=0;i<8;i++){
			for(j=0;j<8;j++){
				if (q[j]==i){
					if (board[i][j]== &wb)
						{board[i][j]= &bq;}
					else
						{board[i][j]= &wq;}
				}
			}
		}
		//printing upper border
		cout<<"   ";
		for(i=0; i<7*8;i++)
			cout<<'_';
		cout<<endl;

		//print the actual board
		for(i=0; i<8; i++){
			for(k=0; k<5; k++){
				cout<<"  "<<char(179);
				for(j=0; j<8;j++){
					for(l=0;l<7;l++){
						cout<<(*board[i][j])[k][l];
					}
				}
				cout<<endl;
			}
		}

		//before exiting print lower border
		cout<<"   ";
		for(i=0; i<7*8;i++)
			cout<<char(196);
		cout<<endl;
		
}

bool ok(int q[], int col)
{
   for(int i=0; i<col; i++)
      if(q[col]==q[i] || (col-i)==abs(q[col]-q[i])) return false;
    
return true;
};

void backtrack(int &col)
{
col--;
if(col==-1) 
{system("PAUSE"); exit(1);}
};


void main() {
	
	int q[8]; q[0]=0;
	int c=1;

	bool from_backtrack=false;

	while(true)
	{
		while(c<8)
		{
			if(!from_backtrack)
				q[c] = -1; //Start at the top
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
}