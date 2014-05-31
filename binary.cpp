#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

std::string dec2bin(unsigned n){
    const int size=sizeof(n)*8;
    std::string res;
    bool s=0;
    for (int a=0;a<size;a++){
        bool bit=n>>(size-1);
        if (bit)
            s=1;
        if (s)
            res.push_back(bit+'0');
        n<<=1;
    }
    if (!res.size())
        res.push_back('0');
    return res;
}

int main(int argc, char* argv[])
{
	if(argc != 4){
		cout << "Incorrect Number of Params\n";
		cout << "Usage: ./binary M e n\n";
		return 1;
	}

	int M = atoi(argv[1]);
	int e = atoi(argv[2]);
	int n = atoi(argv[3]);
	string e_binary = dec2bin(e);
	int k = dec2bin(e).length();
	int C;

	//cout << e_binary << endl;
	//cout << k << "and"<<e_binary.at(0)<< endl;

	//step1
	if(e_binary.at(0) == '1'){
		C = M;
	}else{
		C = 1;
	}
	
	//step2
	for(int i=1;i<k;i++){
		//step2a
		C = C*C;
		C = C%n;
		//step2b
		if(e_binary.at(i)=='1'){
			C=C*M;
			C=C%n;
		}
	}
	//step3
	cout << C << endl;
	return C;

}
