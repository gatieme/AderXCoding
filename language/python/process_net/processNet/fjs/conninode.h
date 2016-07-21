#include "process.h"


#ifndef __CONNINODE_H
#define __CONNINODE_H

#define HASHKEYSIZE 92

std::map <std::string, unsigned long>* refreshconninode ();



class Connection{
public:
	Connection(){
		this->conninode = refreshconninode();
	}

	~Connection(){
		std::map <std::string, unsigned long>::iterator it = this->conninode->begin();
		while (it != this->conninode->end()) {
			this->conninode->erase(it);
			it++;
		}
		this->conninode->clear();
		delete this->conninode;
	}

	unsigned long getConnectionInoe(in_addr ip_src, unsigned short port_src, in_addr ip_dst, unsigned short port_dst){
		char *hashString1 = (char*)malloc(92);
		char *hashString2 = (char*)malloc(92);

		char *local_string = (char*)malloc(50);
		char *remote_string = (char*)malloc(50);

		inet_ntop(AF_INET, &ip_src, local_string, 49);
		inet_ntop(AF_INET, &ip_dst, remote_string, 49);

		snprintf(hashString1, HASHKEYSIZE, "%s:%d-%s:%d", local_string, port_src, remote_string, port_dst);
		snprintf(hashString2, HASHKEYSIZE, "%s:%d-%s:%d", remote_string, port_dst, local_string, port_src);


		int out = -1;
		
		std::map <std::string, unsigned long>::iterator it = this->conninode->find(hashString1);
		if (it != this->conninode->end()) {
			//printf("to out, inode is %d\n", it->second);
			out = it->second;
		} 
		it = this->conninode->find(hashString2);
		if (it != this->conninode->end()) {
			//printf("come in, inode is %d\n", it->second);
			out = it->second;
		} 
		free(hashString1);
		free(hashString2);
		free(local_string);
		free(remote_string);
		

		return out;

	}

private:
	std::map <std::string, unsigned long> *conninode;
};



#endif
