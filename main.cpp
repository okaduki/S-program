#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <sstream>
#include <map>

using namespace std;

void stolower(string& s){
  transform(begin(s), end(s), begin(s), ::tolower);
}

void die(const string& msg){
  cerr << msg << endl;
  exit(1);
}

int main(int argc, char* argv[]){
  vector<string> cmds;
  string line;
  while(getline(cin, line)){
	stolower(line);
	cmds.emplace_back(line);
  }


  int sz = cmds.size();
  if(sz < 1 || cmds.back() != "end"){
	die("Program must end with 'END'");
  }

  map<string,int> vars;
  for(int i=1;i<argc;++i){
	int n = atoi(argv[i]);
	vars["x"+to_string(i)] = n;
  }

  for(int pc=1;pc<=sz;++pc){
	stringstream ss(cmds[pc-1]);
	string tmp;

	ss >> tmp;
	if(tmp == "++"){
	  ss >> tmp;
	  vars[tmp]++;
	}
	else if(tmp == "--"){
	  ss >> tmp;
	  vars[tmp]--;
	  if(vars[tmp] < 0) vars[tmp] = 0;
	}
	else if(tmp == "if"){
	  ss >> tmp;
	  if(vars[tmp]){
		ss >> tmp;
		if(tmp != "goto"){
		  die("Syntax error: GOTO is required");
		}
		ss >> tmp;
		int n = stoi(tmp);
		if(n <= 0 || sz < n){
		  die("GOTO range error: " + cmds[pc-1]);
		}
		pc = n - 1;
	  }
	}
	else if(tmp == "end"){
	  break;
	}
	else{
	  die("Unrecognized command: " + cmds[pc-1]);
	}
  }

  cout << "OUTPUT: " << vars["y"] << endl;
  
  return 0;
}
