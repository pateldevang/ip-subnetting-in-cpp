// ip-subnetting 

// MARK: - Headers
#include <iostream>
#include <string.h>
#include <math.h>
using namespace std;

// MARK: - Error function
void error(int a)
{
    cout<<"The IP is invalid-"<<a;
    exit(1);
}

// MARK: - Sum function
int sum(int s1,int s2,int s3,int co)
{
    int sum=0;
    if(co==1)
    {
        sum=s1;
    }
    else if(co==2)
    {
        sum=s2+s1*10;
    }
    else
    {
        sum=s1*100+s2*10+s3;
    }
    return sum;
}

// MARK: - Check range function (0 to 255)
void checkRange(int tm)
{
    if (!(tm>=0 && tm<=255))
    {
        // Error type 1
        error(1);
    }
}

// MARK: - function to check valid ipv4
void check(string s)
{
	 // MARK: - Variables and user inputs
    
    int test=0,t1=0;
    int count=0,a[30],b[30],c[30],d[30],k=0;
    int ca=0,cb=0,cc=0,cd=0;
    int n = s.size()-3;
    
    // Initialise a,b,c,d to 0.
    for(int i=0;i<30;i++)
    {
        a[i]=0;
        b[i]=0;
        c[i]=0;
        d[i]=0;
    }
    
    // MARK: - Function to check bit size is less then three else throw error type 2
    for(int i=0;i<n;i++)
    {
        if (test > 3)
        {
            error(2);
        }
        else if(s[i]=='.')
        {
            count++;
            test=0;
        }
        else
        {
            test++;
        }
    }
    if(count!=3)
    {
        error(2);
    }
    
   
    // MARK: - Function to check preceding zeros if then throw error type 3 and type 4
    for(int i=0;i<n;i++)
    {
        if(s[i]=='.')
        {
            if(t1==2)
            {
                if(s[i-2]=='0')
                {
                    error(3);
                }
            }
            else if(t1==3)
            {
                if(s[i-3]=='0' && s[i-2]=='0')
                {
                    error(4);
                }
            }
            t1=0;
        }
        else
        {
            t1++;
        }
    }
    
   
    int t=0;
    count=0;
    
    // MARK: - Function to get values values of a,b,c,d by adding the 4 parts of the ipv4 and also to get the count of each part i.e ca, cb, cc, cd
    for(int i=0;i<n;i++)
    {
        
        if(s[i]=='.' && count!=3)
        {
            for(int j=t;j<i;j++)
            {
                if (isdigit(s[j]) == 1)
                {
                    if(count==0)
                    {
                        a[k]=(int)s[j]-48;
                        ca++;
                        k++;
                    }
                    else if(count==1)
                    {
                        b[k]=(int)s[j]-48;
                        cb++;
                        k++;
                    }
                    else if(count==2)
                    {
                        c[k]=(int)s[j]-48;
                        cc++;
                        k++;
                    }
                }
                else {
                    error(5);
                }
            }
            t=i+1;
            k=0;
            count++;
        }
        if(count==3)
        {
            k=0;
            // Goto to e
            goto e;
        }
    }

    
    // MARK : - e label for goto
e:
    for(int j=t;j<n;j++)
    {
        if (isdigit(s[j]) == 1)
        {
            d[k]=(int)s[j]-48;
            cd++;
            k++;
        }
        else {
            error(5);
        }
    }
    
    
    
    // MARK: - sum variables
    int sa=0,sb=0,sc=0,sd=0;
    
 
    // Calculate the vaule of sa, sb, sc, sd using sum()
    sa=sum(a[0],a[1],a[2],ca);
    sb=sum(b[0],b[1],b[2],cb);
    sc=sum(c[0],c[1],c[2],cc);
    sd=sum(d[0],d[1],d[2],cd);
    
    // Check range for the above vaules using checkRange()
    checkRange(sa);
    checkRange(sb);
    checkRange(sc);
    checkRange(sd);
    
    // If no error then continue	
}


// MARK : - Function to calculate number of addresses in the given block
void numofaddrblock(int n1)
{
	cout<<"Number of addresses in given block = "<<pow(2,32-n1);
}


// MARK : - Function to calculate decimal to binary
string decto8bin(int n)
{
	string t;
	short digit = n;
	//print out each bit of the digit
	for(int i = 0; i < 8; i++)
	{
		if(0x80 & digit) //if the high bit is on, print 1
		{
			t[i]='1';
		}
		else
		{
			//otherwise print 0
			t[i]='0';
		}
    digit = digit << 1; //shift the bits left by one to get the next highest bit.
    }
    
    return t;
    
}


// MARK : - Function to convert bianry to decimal
int convertBinaryToDecimal(long long n)
{
    int decimalNumber = 0, i = 0, remainder;
    while (n!=0)
    {
        remainder = n%10;
        n /= 10;
        decimalNumber += remainder*pow(2,i);
        ++i;
    }
    return decimalNumber;
}


// MARK : - 8 bit binary from string


int to8bitbinary(int s,int e,string b)
{
	int sum=0,t=7;
	for(int k=s;k<e;k++)
	{
		sum=sum+pow(10,t)*((int)b[k]-48);
		t--;
	}
	return sum;
}


// MARK: - Main function

int main()
{
	
	// MARK: - Variables and input
	string s;
	int netmask,count=0,i=0,flag=0;
    int a[30],b[30],c[30],d[30],k=0;
    int ca=0,cb=0,cc=0,cd=0;
    
    // Initialise a,b,c,d to 0.
    for(i=0;i<30;i++)
    {
        a[i]=0;
        b[i]=0;
        c[i]=0;
        d[i]=0;
    }
	cout<<"Enter block of addresses given : ";
	cin>>s;
	
	int n=s.size();
	
	// calling check() to validate the ipv4 before further calculation if error then stop.
	check(s);
	
	// Setting flag to calculate netmask
	for(i=0;i<n;i++)
	{
		if(s[i]=='/')
		{
			flag=1;
		}
		if (flag==1)
		{
			count++;
		}
	}
	count--;
	
	// Calculating netmask
	if (count==1)
	{
		netmask=int(s[n-1])-48;
	}
	else
	{
		netmask=int(s[n-1])-48+10*(int(s[n-2])-48);
	}
	count=0;
	
	
	int t=0;
    count=0;
    
    // MARK: - Function to get values values of a,b,c,d by adding the 4 parts of the ipv4 and also to get the count of each part i.e ca, cb, cc, cd
    for(int i=0;i<n-3;i++)
    {
        
        if(s[i]=='.' && count!=3)
        {
            for(int j=t;j<i;j++)
            {
                if (isdigit(s[j]) == 1)
                {
                    if(count==0)
                    {
                        a[k]=(int)s[j]-48;
                        ca++;
                        k++;
                    }
                    else if(count==1)
                    {
                        b[k]=(int)s[j]-48;
                        cb++;
                        k++;
                    }
                    else if(count==2)
                    {
                        c[k]=(int)s[j]-48;
                        cc++;
                        k++;
                    }
                }
                else {
                    error(5);
                }
            }
            t=i+1;
            k=0;
            count++;
        }
        if(count==3)
        {
            k=0;
            // Goto to e
            goto e;
        }
    }

    
    // MARK : - e label for goto
e:
    for(int j=t;j<n-3;j++)
    {
        if (isdigit(s[j]) == 1)
        {
            d[k]=(int)s[j]-48;
            cd++;
            k++;
        }
        else {
            error(5);
        }
    }
    
    // MARK: - sum variables
    int sa=0,sb=0,sc=0,sd=0;
    
 
    // Calculate the vaule of sa, sb, sc, sd using sum()
    sa=sum(a[0],a[1],a[2],ca);
    sb=sum(b[0],b[1],b[2],cb);
    sc=sum(c[0],c[1],c[2],cc);
    sd=sum(d[0],d[1],d[2],cd);
    
    // For binary ipv4
    string bin;
    string temp=decto8bin(sa);
    string temp1=decto8bin(sb);
    string temp2=decto8bin(sc);
    string temp3=decto8bin(sd);
	
	// Calculate binary ipv4
    for(i=0;i<8;i++)
    {
		bin=bin+temp[i];
	}
	k=0;
	for(i=8;i<16;i++)
    {
		bin=bin+temp1[k];
		k++;
	}
	k=0;
	
	for(i=16;i<24;i++)
    {
		bin=bin+temp2[k];
		k++;
	}
	k=0;
	for(i=24;i<32;i++)
    {
		bin=bin+temp3[k];
		k++;
	}
	
	// For First ip address in block we set (32-netmask) bit from right to '0'
	for(i=0;i<32;i++)
	{
		if(i>=netmask)
		{
			bin[i]='0';
		}
	}
	
	// convert the binary to decimal ipv4
	sa=to8bitbinary(0,8,bin);
	sa=convertBinaryToDecimal(sa);
	sb=to8bitbinary(8,16,bin);
	sb=convertBinaryToDecimal(sb);
	sc=to8bitbinary(16,24,bin);
	sc=convertBinaryToDecimal(sc);
	sd=to8bitbinary(24,32,bin);
	sd=convertBinaryToDecimal(sd);
	
	cout<<"First address in block is = "<<sa<<"."<<sb<<"."<<sc<<"."<<sd;
	
	
	return 0;
}






// Calling numofaddrblock() to calculate number of addresses in the block by passing netmask as parameter.
	//numofaddrblock(netmask);

	// TODO: - 1. number of subnets, 
	// 	   3. last address in the block, 

