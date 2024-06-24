#include <bitset>
#include <string.h>
#include <dirent.h>
#include <vector>
#include <string>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <cassert>
#include <iostream>
#include <sstream>
#include <cmath>
#include <map>
#include <string>
#include <set>

#define PARTITION_NODES_SIZE 8 
#define PARTITION_MASK 0x7
#define PARTITION_LENGTH 3
#define PARTITION_ROOT_LEVEL 30
#define KEY_LENGTH 32
#define TREE_MASK 0xfffffff8

// char bit
#define BASE 0x01

using namespace std;
 
class Partition {
public:
	char bitmap;
	
	Partition() : bitmap(0) {}
	~Partition() {
		//cout << "free Partition" << endl;
	}
	
	int insert_key(const long long int key) {
		const long long  int tmp_key = key & PARTITION_MASK;
		if (bitmap & (BASE << tmp_key)) {
			return -1;  // duplicate
		} else {
			bitset<PARTITION_LENGTH> huff(tmp_key);
			bitmap = bitmap | (BASE << tmp_key);
			return 0;  // insert successfully
		}
	}
	
	void show_key(const long long int node) {
		for (int i = PARTITION_NODES_SIZE - 1; i >= 0; i--) {
			if (bitmap & (BASE << i)) {
				//cout << hex << (node << PARTITION_LENGTH) + i << endl;
			}
		}
	}

        bool search_key(const long long int node, int key) {
                for (int i = PARTITION_NODES_SIZE - 1; i>=0; i--) {
                        if (bitmap & (BASE << i)) {
                                if ((node << PARTITION_LENGTH) + i == key) return true;
                        }
                }
                return false;
        }
};

class Tree {
public:
	map<long long int, Partition*> child;
	
	Tree() {
	
	}
    
    ~Tree() {
    	map<long long int, Partition*>::iterator it;
    	for (it = child.begin(); it != child.end(); it++) {
    		delete (it->second);
		}
    }
    
    int insert_key(long long int key) {
    	bitset<KEY_LENGTH> bit(key);
    	long long int tree_key = (key & TREE_MASK) / PARTITION_NODES_SIZE;
    	map<long long int, Partition*>::iterator it;
    	it = child.find(tree_key);
    	if (it == child.end()) {
    		Partition *part = new Partition();
    		child.insert(pair<long long int, Partition*>(tree_key, part));
    		part->insert_key(key);
    		return -1;
		} else {
			(it->second)->insert_key(key);
			return 0;
		}
	}
	
	void show() {
		map<long long int, Partition*>::iterator it;
		cout << "++++++++Tree++++++++" << endl; 
		for (it = child.begin(); it != child.end(); it++) {
			cout << "|"; 
			cout << it->first << "--->"
			<< bitset<PARTITION_NODES_SIZE>(it->second->bitmap) << endl;
		}
	}
	
	void show_key() {
		map<long long int, Partition*>::iterator it;
		cout << "******** All keys ********" << endl;
		
		for (it = child.begin(); it != child.end(); it++) {
			it->second->show_key(it->first);
		}
	}
};

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
 
int main()
{
    string root = ".";
    vector<string> vs;
    FILE *fstream;
    char buf[8];
    FindFiles(root, vs);
    string command;

    Tree *t = new Tree();

	double time = 0;
	int space = 8;
    vector<string>::iterator it;
	set<int> keys;
	set<int>::iterator kit;

    for (it = vs.begin(); it != vs.end(); it ++) {
		command = "md5sum " + *it;
		fstream = popen(command.data(), "r");
		fread(buf, sizeof(char), sizeof(buf), fstream);
		pclose(fstream);
		t->insert_key(strtol(buf, NULL, 16));
		kit = keys.find(strtol(buf, NULL, 16));
		time += 0.0001;
		keys.insert(strtol(buf, NULL, 16));
		if (keys.size() > space) {
			time += 10;
			for (int j = 0; j < 4;j++) {
				keys.erase(keys.begin());
			}
		}
    }
	cout << "huff time: " << time << endl;
	cout << "huffu size : "<< dec <<  t->child.size() << endl;

    delete t;
    return 0;
}

