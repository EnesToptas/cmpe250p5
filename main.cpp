#include <iostream>
#include <cmath>
#include <fstream>
#include <vector>

#define mod 1000000007
#define prime 29
using namespace std;

vector<vector <int>> hashes;
vector<int> dict;
vector<string> realDict;
vector<int> length;
vector<int> dynamic;
string text;

long long powe(long long base, long long power) {
    long long result = 1;
    while(power > 0) {
        if(power & 1) {
            result = (result*base) % mod;
        }
        base = (base * base) % mod;
        power >>= 1;
    }
    return result;
}

long long int hashing(string s){
    long long int h = (s[0]-96)*powe(prime,s.size()-1);
    for(int i = 1; i< s.size() ; i++){
      h += ((s[i] - 96)*powe(prime,s.size()-i-1))%mod;
      h = h%mod;
    }
    return h;
}

void fillArr(string s){
    for(int i=0; i< s.size() ; i++){
        hashes[i][0]= hashing(s.substr(0,i+1));
        for(int j = 1; j < s.size()-i ; j++){
            hashes[i][j]= ((((hashes[i][j-1] - (s[j-1]-96)*powe(prime,i))*prime)+ ((s[i+j]-96)))%mod+mod)%mod;
        }
    }
}

long long int funny(int index){

    if(index == hashes.size())
        return 1;

    if(index > hashes.size())
    	return 0;

    if(dynamic[index]!=-1)
        return dynamic[index];


    int count = 0;

    for(int i = 0 ; i< dict.size(); i++){
    	if(hashes.size() >= length[i]){
    		if (dict[i] == hashes[length[i] - 1][index]) {
        		if(realDict[i] == text.substr(index,length[i])){
            		count += funny(index+length[i])%mod;
            		count = count %mod;	
        	}
        }
    	}
    }

    dynamic[index] = count;
    return count;
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        cout << "Run the code with the following command: ./project5 [input_file] [output_file]" << endl;
        return 1;
    }
    ifstream infile;
    ofstream gofile;
    infile.open(argv[1]);

    int dictLength;
    infile >> text;
    infile >> dictLength;

    hashes = *new vector<vector <int>>(text.size(),vector<int>(text.size()));
    dict = *new vector<int>(dictLength);
    realDict = *new vector<string>(dictLength);
    length = *new vector<int>(dictLength);
    dynamic = *new vector<int>(text.size(),-1);

    for(int i= 0 ; i< dictLength; i++){
        string tmp;
        infile >> tmp;
        realDict[i] = tmp;
        dict[i] = hashing(tmp);
        length[i] = tmp.size();
    }
    infile.close();
    fillArr(text);
    gofile.open(argv[2]);
    gofile << funny(0);
    gofile.close();
    return 0;
}

