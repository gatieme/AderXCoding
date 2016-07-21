#ifndef __PROCESS_H
#define __PROCESS_H

#include <set>
#include <map>
#include <string>
#include <iostream>




#include <pthread.h>

#include <net/ethernet.h>
#include <net/if.h>
#include <netinet/ip.h>
#include <netinet/ip6.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>
#include <string.h>

#include <ncurses.h>
#include <asm/types.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <pwd.h>


#include <netinet/in.h>

#include <stdio.h>
#include <stdlib.h>


#include <sys/types.h>
#include <errno.h>
#include <string.h>
#include <dirent.h>
#include <ctype.h>
#include <cstdlib>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string>
#include <sys/stat.h>
#include <fcntl.h>
#include <limits.h>


#include <pcap.h>

#include "conninode.h"

#define HASHKEYSIZE 92

std::set<long>* getProcessSocketInode(long pid);

struct dpargs {
	int sa_family;
	in_addr ip_src;
	in_addr ip_dst;
	in6_addr ip6_src;
	in6_addr ip6_dst;
};

class Process{
public:
	Process(int pid) {
		this->pid = pid;
		this->inodes = getProcessSocketInode(this->pid);
	}
	~Process() {
		delete this->inodes;
	}


	bool hasInode(long inode) {
		std::set<long>::iterator it;
		it = this->inodes->find(inode);
		if (it == this->inodes->end()) {
			return false;;
		} else {
			return true;
		}
	}
	void refershInodes() {
		if (this->inodes != NULL) {
			std::set<long>::iterator it = this->inodes->begin();
			while (it != this->inodes->end()) {
				this->inodes->erase(it);
				it++;
			}
			this->inodes->clear();
			delete this->inodes;
			this->inodes = NULL;
		}
		this->inodes = getProcessSocketInode(this->pid);
	}

	double sudu = 0;
	int len = 0;
	int pid;
	std::set<long>* inodes = NULL;
	
	

	
};






#endif