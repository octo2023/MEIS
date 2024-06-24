#include "MurmurHash3.h"
#include <iostream>
#include <stdlib.h>
#include <vector>
#include <set>
#include <string>
#include <sstream>
#include <sys/types.h>
#include <stdio.h>
#include <dirent.h>
#include <unistd.h>
#include <cmath>
#include <string.h>

using namespace std;

void FindFiles(string root ,vector<string> &files){
    DIR *dir;
    struct dirent *ent;
    if ((dir = opendir (root.c_str())) != NULL) {

        while ((ent = readdir (dir)) != NULL) {
            if(!strcmp(ent->d_name,".")||!strcmp(ent->d_name,".."))
                continue;
            files.push_back(ent->d_name);

        }
        closedir (dir);
    }
}

int main() {
	int *a = (int *)malloc(sizeof(int));
	int seed = 0;
	int len = 32;
	int ret;
	double time=0;
	int space = 5000;
	MurmurHash3_x86_32(a, len, seed, &ret);
	set<int> cache;
	set<int> disk;
    string root = ".";
    vector<string> vs;
    FILE *fstream;
    char buf[8];
    FindFiles(root, vs);
    string command;
    vector<string>::iterator it;
    set<int>::iterator sit;
    for (it = vs.begin(); it != vs.end(); it ++) {
        command = "md5sum " + *it;
        fstream = popen(command.data(), "r");
        fread(buf, sizeof(char), sizeof(buf), fstream);
        pclose(fstream);
		*a = strtol(buf, NULL, 16);
		MurmurHash3_x86_32(a, len, seed, &ret);

		disk.insert(ret);
		cache.insert(ret);
		time += 0.0001;
		if (cache.size()*4 > space) {
			time += 10;
			cache.erase(cache.begin());
		}
    }
	cout << "murmur time: " << time << endl;
	cout << "murmur size: " << disk.size()*4 << endl;

}
