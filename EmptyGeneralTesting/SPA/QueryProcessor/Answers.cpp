#include "Answers.h"
#include <vector>

vector<Answers*> Answers::getLinksOfList(int ListIndex){
	return links[ListIndex];
}

void Answers::addLink(Answers answer1, Answers answer2){
	answer1.links[answer2.ListIndex].push_back(&answer2);
	answer2.links[answer1.ListIndex].push_back(&answer1);
}

bool Answers::hasLinksWith(int index){
	return !(links[index].empty());
}

vector<Answers*> Answers::cleanLinks(){

	vector<Answers*> needDelete;

	for(int i=0;i<links.size();i++)
		for(int j=0;j<links[i].size();j++){
			if(!(*links[i][j]).links[ListIndex].empty()){
				vector<Answers*> *tempList = &((*links[i][j]).links[ListIndex]);

				vector<Answers*>::iterator iter = (*tempList).begin();

				while(iter!=(*tempList).end()){
					Answers* temp = *iter; 
					if(temp == this)  
						iter = (*tempList).erase(iter);
					else iter++;
				}

				if((*links[i][j]).links[ListIndex].empty()){
					needDelete.push_back(links[i][j]);
				}
			}
		}

	return needDelete;
}