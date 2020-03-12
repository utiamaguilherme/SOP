#include "includes/utils.hpp"

bool getFiles(vector<string>& files, const char * name, const char * nthr, unsigned int ithr){
  string tname = name;
  string tnthr = nthr;
  files.push_back(tname);

  for(unsigned int i=1; i<=ithr; i++){
    string temp = tname+"-"+to_string(i);
    if(temp.size() <= tname.size()){
      return false;
    }
    files.push_back(temp);
  }
  return true;
}
