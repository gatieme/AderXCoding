
#include "app.h"



pthread_mutex_t pmutex = PTHREAD_MUTEX_INITIALIZER;

void* wakeUp(void *arg){
	pthread_detach(pthread_self());
	App *app = (App*)arg;
	sleep(app->time);
	pcap_breakloop(app->handle);
	return ((void*)0);
}


std::vector<int> res;

void* loop(void *arg){
	App *app = (App*)arg;
	timeval begin, end;
	pthread_t ptid;
	while (true) {
		gettimeofday(&begin, NULL);



		int err = pthread_create(&ptid, NULL, wakeUp, app);

		pcap_loop(app->handle, -1, processCallBack, (u_char*)app);
		size_t size = app->processs.size();
		
		gettimeofday(&end, NULL);

		double sec = end.tv_sec - begin.tv_sec;
		sec += ((double)(end.tv_usec - begin.tv_usec)) / 1000000;


		pthread_mutex_lock(&pmutex);
		for (int i = 0; i < size; i++) {
			Process *now = app->processs[i];
			double all = (double)now->len;
			now->len = 0;
			double su = all / sec / 1000;
			now->sudu = su;
			now->refershInodes();
			if (now->inodes == NULL) {
				res.push_back(now->pid);
			}
		}
		pthread_mutex_unlock(&pmutex);


		for (int i = 0; i < res.size(); i++) {
			int pid = res[i];
			app->removeProcess(pid);
		}
		res.clear();
		app->refreshConnection();
	}
}


void processCallBack(u_char *userData, const  pcap_pkthdr *header, const u_char *packet){
	App *app = (App*)userData;

	switch (app->linkType) {
		case (DLT_EN10MB):
			app->dp_parse_ethernet (header, packet);
			break;
			/*
		case (DLT_PPP):
			dp_parse_ppp (handle, header, packet);
			break;
		case (DLT_LINUX_SLL):
			dp_parse_linux_cooked (handle, header, packet);
			break;
		case (DLT_RAW):
		case (DLT_NULL):
			// hope for the best
			dp_parse_ip (handle, header, packet);
			break;)*/
		default:
			printf("unknown link type");
			break;
	}
}

double doProcess(int pid, int time){

/*
	timeval begin, end;
	gettimeofday(&begin, NULL);

	App app(pid, time);
	app.dispatch();
	int len = app.len;

	gettimeofday(&end, NULL);

	double sec = end.tv_sec - begin.tv_sec;
	sec += ((double)(end.tv_usec - begin.tv_usec)) / 1000000;
	double all = (double)len;

	double su = all / sec / 1000;


	printf("%.2f KB/S\n", su);
	return su;*/
	return 0;
}


/*
int main(){
	timeval begin, end;
	gettimeofday(&begin, NULL);

	App app(7140, 10);
	app.dispatch();
	int len = app.len;

	gettimeofday(&end, NULL);

	double sec = end.tv_sec - begin.tv_sec;
	sec += ((double)(end.tv_usec - begin.tv_usec)) / 1000000;
	double all = (double)len;

	double su = all / sec / 1000;

	printf("%.2f KB/S\n", su);

	return 0;
	
	Process p(7140);
	if (p.hasInode(23045)) {
		printf("you de \n");
	} else {
		printf("meiyou \n");
	}
	
	cons = new Connection();

	char errbuff[PCAP_ERRBUF_SIZE];
	char *dev = pcap_lookupdev(errbuff);
	handle = pcap_open_live(dev, BUFSIZ, 0, 1000, errbuff);

	linkType = pcap_datalink(handle);
	int err = pthread_create(&ptid, NULL, doIt, NULL);
	pcap_loop(handle, -1, pcap_callBack, NULL);


	delete cons;
	printf("main\n");


	std::map <std::string, unsigned long> *conninode = refreshconninode();
	for (std::map <std::string, unsigned long>::iterator it = conninode->begin(); it != conninode->end(); it++) {
		std::cout<<it->first<<" :  "<<it->second<<"\n";
	}


}*/


