#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

using namespace std;

void myinit (void);

vector <float> vect_coordx,vect_coordy;
   vector <float> :: iterator CoordIterx,CoordItery;
   float co_ordx,co_ordy;


int main()
{
  string line;
  ifstream in_stream ("C:\\Users\\Anirudh\\Desktop\\nmea_log.txt");
  ofstream gllLog("C:\\Users\\Anirudh\\Desktop\\gllLog.txt",ios::trunc);
  ifstream gll_in_stream ("C:\\Users\\Anirudh\\Desktop\\gllLog.txt");



  string gll_line;

  int jump=0;
  
  if (in_stream.is_open())
  {
	  while ( getline (in_stream,line))
		if (line.compare(1,5,"GPGLL")==0)
			if (gllLog.is_open())
				gllLog<<line<<endl;
				    
    in_stream.close();
  }
  else
  { 
	  cout << "Unable to open test.txt";
	  system("hit any key to continue");
  }

  if (gll_in_stream.is_open())
  {
	  cout<<"Longitude value"<<"	     "<<"Latitude Value"<<endl;
	  while ( getline (gll_in_stream,gll_line) && !gll_in_stream.eof())
	  {   
		  stringstream parse(gll_line);
		  string gll_token;
		  
		  float getX;
		  float getY;
		  while(getline(parse,gll_token,','))
		  {
			  if((jump%7)==1)
			    getX=stof(gll_token);
				
			  if((jump%7)==2)
			  {
				  if(gll_token.compare(0,1,"S")==0)
				  {
					  co_ordx = getX *-1;
					  vect_coordx.push_back(co_ordx);
					  cout<<co_ordx;
				  }
				  else
				  {
					  co_ordx = getX;
					  vect_coordx.push_back(co_ordx);
					  cout<<co_ordx;
				  }
			  }

			if((jump%7)==3)
				getY=stof(gll_token);
				
			if((jump%7)==4)
			  {

				  if(gll_token.compare(0,1,"W")==0)
				  {
					  co_ordy = getY *-1;
					  vect_coordy.push_back(co_ordy);
					  cout<<"   "<<co_ordy<<endl;
				  }
				  else
				  {
					  co_ordy = getY;
					  vect_coordy.push_back(co_ordy);
					  cout<<"   "<<co_ordy<<endl;
				  }

			  }

				jump++;
			  
		  }//while
	  }//while
  }//if 
  else
  {
		  cout << "Unable to open test.txt"; 
  }
system("done...");
 
 myinit();

return 0;
}
