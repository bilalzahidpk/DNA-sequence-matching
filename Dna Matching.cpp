#include<iostream>
#include<cstring>
#include<fstream>
using namespace std;

class DynamicSafeArray
{
	private:
		void DeleteAll()
		{
			if (data != 0)
				delete data;
			data = 0;
		}
	public:
		char *data;
		int size;
		
		int SizeStr(string strtemp)	
		{
			int i = 0;
			while (strtemp[i] != '\0')
				i++;
			return i;
		}
		int SizeStr(const char *strtemp)	
		{
			int i = 0;
			while (strtemp[i] != '\0')
				i++;
			return i;
		}
		
		DynamicSafeArray() : size(0), data(0) {}	
		DynamicSafeArray(const char *strtemp)
		{
			size = SizeStr(strtemp);
			data = new char[size];
			memcpy(data, strtemp, sizeof(char) * size);
			data[size] = '\0';
		}
		
		DynamicSafeArray(string strtemp)
		{
			size = SizeStr(strtemp);
			data = new char[size];
			
			int i;
			for (i = 0; i < size; i++)
				data[i] = strtemp[i];
			data[i] = '\0';
		}
		
		int getSize() const
		{
			return size;
		}
		void Renew()
		{
			size = 0;
			data[0] = '\0';
		}
		char& operator [] (int i)
		{
			
			if (i > size)
			{
				char *temp;
				temp = new char[size];
				memcpy(temp, data, sizeof(char) * size);
				size += 2;	
				delete data;	
				data = 0;
				data = new char[size];	
				memcpy(data, temp, sizeof(char) * size);
				data[size - 1] = '\0';
			}
			else if (size == 0)
			{
				
				size += 2;
				data = new char[size];
				data[size - 1] = '\0';
			}
			else if (i == size - 1)	
			{
				
				char *temp ;
				temp = new char[size];
				memcpy(temp, data, sizeof(char) * size);
				size++;	
				delete data;	
				data = 0;
				data = new char[size];	
				memcpy(data, temp, sizeof(char) * size);
				data[size - 1] = '\0';

			}
			else
			{
				data[i + 1] = '\0';
			}
			return *(data + i);
		}
		const char& operator () (int i) const
		{
			return *(data + i);
		}
		~DynamicSafeArray()
		{
			
		}
};

void AlteredKnuthMorrisPrattArray(char val,int index,char *p) 
{ 
	
   p[index]=val;
     
} 
 
int min(int x, int y, int z) 
{ 
    return min(min(x, y), z); 
} 
  
int LevenShteinDistanceAlgo(DynamicSafeArray s,DynamicSafeArray t, int m,int n) 
{ 
    
    int dp[m+1][n+1]; 
  
    for (int i=0; i<=m; i++) 
    { 
        for (int j=0; j<=n; j++) 
        { 
            if (i==0) 
                dp[i][j] = j; 
            else if (j==0) 
                dp[i][j] = i; 
                
			else if (s.data[i-1] == t.data[j-1]) 
                dp[i][j] = dp[i-1][j-1]; 
  
            else
                dp[i][j] = 1 + min(dp[i][j-1], dp[i-1][j], dp[i-1][j-1]);  
        } 
    } 
  
    return dp[m][n]; 
} 
  
void checkrelation(DynamicSafeArray s1,DynamicSafeArray s2)
{
	 int n=LevenShteinDistanceAlgo(s1,s2,s1.getSize(),s2.getSize());
	 float check=(((float)s1.getSize()-(float)n)/(float)s1.getSize())*100;
	 
    if(check==100)
    {
    	cout<<"Matching percentage:"<<check<<"%"<<endl;
		cout<<"These two persons are twins";
	}
    
    else if(check>=50&&check<100)
    {
    	cout<<"Matching percentage:"<<check<<"%"<<endl;
		cout<<"These two persons have parent and child relation";
	}
    
    else if(check>=25&&check<50)
    {
    	cout<<"Matching percentage:"<<check<<"%"<<endl;
		cout<<"These two persons have grandparent and grandchild relation";
	}
    
    else if(check>=12.5&&check<25)
    {
    	cout<<"Matching percentage:"<<check<<"%"<<endl;
		cout<<"These two perseons have uncle/aunt and niece/nephew relation";
	}
    
   else if(check>=6.25&&check<12.5)
    {
    	cout<<"Matching percentage:"<<check<<"%"<<endl;
		cout<<"These two persons are first cousins";
	}
    
    else
    {
    	cout<<"Matching percentage:"<<check<<"%"<<endl;
		cout<<"These two persons are 1st cousin once removed";
	}
    
} 
  
void AlteredKnuthMorrisPratt(DynamicSafeArray pat, DynamicSafeArray txt) 
{ 
    int M = pat.getSize(); 
    int N = txt.getSize(); 
    char lps[50]={0}; 
    int count=0;
  	bool temp=false;
	int i = 0;  
    int j = 0;
    while (i < N) 
	{ 
		
		if (pat.data[j] == txt.data[i]) 
		{ 
          	
			AlteredKnuthMorrisPrattArray(pat.data[j],count,lps);
			count++;
			j++; 
            i++; 
            temp=true;
        } 
       else if((pat.data[j]!=txt.data[i])&&temp==true)
       {
       	
		count++;
		temp=false;	
		AlteredKnuthMorrisPrattArray(' ',count,lps);
		 j++;
	   }
		else
		{
		
			j++;
		}
    }
    cout<<endl<<"Matched pattern is:";
	for(i=0;i<M;i++)
	{
		cout<<lps[i];
	 } 
	 cout<<endl;
} 
   
int main() 
{ 
	string str1,str2;
	ifstream infile("INPUT2.txt");
	getline(infile,str1);
	getline(infile,str2);
	cout<<"For String 1:"<<endl;
	DynamicSafeArray firststring(str1),secondstring(str2);
    AlteredKnuthMorrisPratt(firststring,secondstring); 
    cout<<endl;
    cout<<"No of changes to make it equivalent DNA:"<<LevenShteinDistanceAlgo(firststring,secondstring,firststring.getSize(),secondstring.getSize());
    cout<<endl;
	checkrelation(firststring,secondstring);
	ifstream infile1("INPUT1.txt");
	getline(infile1,str1);
	getline(infile1,str2);
	cout<<endl;
	cout<<endl;
	cout<<"For String 2:"<<endl;
	DynamicSafeArray thirdstring(str1),fourthstring(str2);
    AlteredKnuthMorrisPratt(thirdstring,fourthstring); 
    cout<<endl;
	cout<<"No of changes to make it equivalent DNA:"<<LevenShteinDistanceAlgo(thirdstring,fourthstring,thirdstring.getSize(),fourthstring.getSize());
	cout<<endl;
	checkrelation(thirdstring,fourthstring);
	cout<<endl;
	ifstream infile2("INPUT3.TXT");
	getline(infile2,str1);
	getline(infile2,str2);
	cout<<endl;
	cout<<"For String 3:"<<endl;
	DynamicSafeArray fifthstring(str1),sixthstring(str2);
    AlteredKnuthMorrisPratt(fifthstring,sixthstring); 
    cout<<endl;
	cout<<"No of changes to make it equivalent DNA:"<<LevenShteinDistanceAlgo(fifthstring,sixthstring,fifthstring.getSize(),sixthstring.getSize());
	cout<<endl;
	checkrelation(fifthstring,sixthstring);
	return 0; 
} 
