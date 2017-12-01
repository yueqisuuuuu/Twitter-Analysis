#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <cmath>

using namespace std;

/*
 * Scale number on base and/or range of input values
 * (Max character allowed in one line is 100)
 * if number is scaled, we want at least 1 "o" for each row (except number is 0)
 *
 * return new range and val
 */
pair<int, int> scaleNum(int min, int max){
	int base=0;
	int val=1;
	if (max>100){ // large base
		base=min-10;
	}

	if ((max-min) > 90){ // large range
		//cout<<max-base<<endl;
		
		// find the smallest x (> 1) where
		// max/x - base/x < 100
		val = ceil((max-base)/double (100));
	}
	
	//cout<<"Base: "<<base<<" val: "<<val<<endl;
	return ( pair<int, int> (base, val) );
}


/*
cat tweet.txt | while read number
do
  result=""
  if [ $number = '0' ]
  then
    echo $result
  else
    for n in $(seq 1 $number)
    do
      result+="o"
    done
    echo $result
  fi
done
*/

/*
 * Draw histogram
 *
 */
void histogram(vector<int> num, int base, int val){
	// formatting
	for (int k=0; k<100; k++){
		cout<<'-';
	}
	cout<<endl;

	cout<<"Note: All numbers are rounded up when graphed"<<endl;
	cout<<"Base starts at "<<base<<endl;
	cout<<"Each 'o' represents "<<val<<endl;
	
	// formatting
    cout<<' ';
    for (int k=0; k<100; k++){
        cout<<'-';
    }
    cout<<' ';
    cout<<endl;

    //graph
	for (int i=0; i<num.size(); i++){
        cout<<'|';
        int j;
		for (j=0; j<ceil((num[i]-base)/double (val)); j++){
			cout<<'o';
		}
        for (j; j<100; j++){
            cout<<' ';
        }
		cout<<'|'<<endl;
	}
	
	//formatting
    cout<<' ';
	for (int k=0; k<100; k++){
		cout<<'-';
	}
    cout<<' ';
	cout<<endl;
}


int main(){
	vector<int> num;
  	// open tweet.txt
  	ifstream ifs("tweet.txt");
    if (ifs.fail()){
      	cout<<"Can't open tweet.txt!"<<endl;
      	exit(1);
    }
  	// read tweet.txt into vector
  	string n;
  	while (getline(ifs, n)){
    	num.push_back(stoi(n));
  	}
  	// close connection
  	ifs.close();

	int total=0;
  	int min = num[0];
  	int max = num[0];
  	// find min and max of data
  	for (int i = 1; i<num.size(); i++){
    	if (num[i]<min){
    		min = num[i];
    	}
    	else if (num[i]>max){
    		max = num[i];
    	}
    	total += num[i];
  	}
	int avg = total/num.size();

	// scale graph
  	pair<int, int> temp = scaleNum (min, max);
  	int base = temp.first;
  	int val = temp.second;
  	//cout<<"Range: "<<base<<" val: "<<val<<endl;

	cout<<"Statistics:"<<endl;
	cout<<"Min "<<min<<"    Max "<<max<<"    Average "<<avg<<"    Duration "<<((num.size())*10)<<"s"<<endl;
	// print histogram
	histogram(num, base, val);

  	return 0;
}
