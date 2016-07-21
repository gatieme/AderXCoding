#ifndef __APP_H
#define __APP_H
#include <iostream>
#include <map>
#include <set>
#include <vector>



#include <Python.h>

#include <pthread.h>

#include <net/ethernet.h>
#include <net/if.h>
#include <netinet/ip.h>
#include <netinet/ip6.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>
#include <iostream>

#include <string.h>
#include <string>

#include <asm/types.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <pwd.h>
#include <map>

#include <netinet/in.h>
#include <map>
#include <stdio.h>
#include <stdlib.h>


#include <sys/types.h>
#include <errno.h>
#include <dirent.h>
#include <ctype.h>
#include <cstdlib>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/time.h>
#include <time.h>

#include <pcap.h>

#include "conninode.h"
#include "process.h"



#define HASHKEYSIZE 92


extern pthread_mutex_t pmutex;


void* wakeUp(void *arg);

void processCallBack(u_char *userData, const  pcap_pkthdr *header, const u_char *packet);

double doProcess(int pid, int time);

void* loop(void *arg);





class App{
public:
	App(int time) {
		this->con = new Connection();
		this->time = time;
		this->len = 0;
		pthread_mutex_init(&pmutex, NULL);
	}

	~App() {
		size_t size = this->processs.size();
		for (int i = 0; i< size; i++) {
			Process *now = this->processs[i];
			delete now;
		}
		delete this->con;
	}

	void refreshConnection() {
		delete this->con;
		this->con = new Connection();
	}


	void dispatch() {
		char errbuff[PCAP_ERRBUF_SIZE];
		char *dev = pcap_lookupdev(errbuff);
		
		this->handle = pcap_open_live(dev, BUFSIZ, 0, 1000, errbuff);

		this->linkType = pcap_datalink(this->handle);

		int err = pthread_create(&this->ptid, NULL, loop, this);

	}

	void addProcess(Process *pro) {
		size_t size = this->processs.size();
		for (int i = 0; i< size; i++) {
			Process *now = this->processs[i];
			if (now->pid == pro->pid) {
				delete pro;
				return;
			}
		}
		this->processs.push_back(pro);
	}

	void removeProcess(int pid) {
		std::vector<Process*>::iterator it = this->processs.begin();
		while (it != this->processs.end()) {
			Process *pro = *it;
			if (pro->pid == pid) {
				it = this->processs.erase(it);
				delete pro;
				break;
			} else {
				it++;
			}
		}
		
	}

	void dp_parse_ethernet (const pcap_pkthdr * header, const u_char * packet){
		const struct ether_header * ethernet = (struct ether_header *)packet;
		u_char * payload = (u_char *) packet + sizeof (struct ether_header);


		/* parse payload */
		switch (ethernet->ether_type)
		{
			case (0x0008):
				this->dp_parse_ip (header, payload);
				break;
			case (0xDD86):
				//dp_parse_ip6 (handle, header, payload);
				break;
			default:
				// TODO: maybe support for other protocols apart from IPv4 and IPv6 
				break;
		}
	}

	void dp_parse_ip (const pcap_pkthdr * header, const u_char * packet){
		const struct ip * ip = (struct ip *) packet;

		this->info.sa_family = AF_INET;
		this->info.ip_src = ip->ip_src;
		this->info.ip_dst = ip->ip_dst;

		u_char * payload = (u_char *) packet + sizeof (struct ip);
		switch (ip->ip_p)
		{
			case (6):
				this->dp_parse_tcp (header, payload);
				break;
			default:
				// TODO: maybe support for non-tcp IP packets
				break;
		}
	}

	void dp_parse_tcp (const pcap_pkthdr * header, const u_char * packet){
		struct tcphdr * tcp = (struct tcphdr *) packet;

		unsigned long inode = this->con->getConnectionInoe(this->info.ip_src, ntohs(tcp->source), this->info.ip_dst, ntohs(tcp->dest));
		pthread_mutex_lock(&pmutex);
		size_t size = this->processs.size();
		for (int i = 0; i< size; i++) {
			Process *now = this->processs[i];
			if (now->hasInode(inode)) {
				now->len += header->len;
				break;
			}
		}
		pthread_mutex_unlock(&pmutex);
		/*
		if (this->process->hasInode(inode)) {
			this->len += header->len;
		}*/
	}

	pcap_t *handle;
	int time;
	int linkType;
	dpargs info;
	pthread_t ptid;
	long pid;
	int len;
	std::vector<Process*> processs;

private:
	Process *process;
	Connection *con;
	
	
	
};






#endif