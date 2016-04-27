/* 
 * Author: JORGE HERNANDEZ DE BENITO
 *
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>

using namespace std;

//Variables globales


//Procedimientos

int main(int argc, char** argv) {
    ios_base::sync_with_stdio(false);
    vector<string> corpus;
    corpus.push_back("");
    ifstream file("corpus.txt");
    string line;
    string word;
    map<string, vector<int> > positions;
    int i = 1;
    while(getline(file,line)){
    	stringstream ss(line);
    	while(ss>>word){
    		corpus.push_back(word);
    		positions[word].push_back(i);
    		i++;    		
    	}
    }
    int cases, first, last;
    string first_word, second_word, third_word;
    int first_word_ap, second_word_ap, third_word_ap;
    cin >> cases;
	for(int i = 0; i < cases; i++){
		first_word_ap=0;
		second_word_ap=0;
		third_word_ap=0;
		cin >> first >> last;
		bool visto[last-first+1];
		for(int j = 0; j <= (last-first) ; j++)
			visto[j]=false;
		/*Búsqueda de los mejores*/
		for(int j = 0; j <= (last -first); j++){
			if(!visto[j]){
				int times = 0;
				vector<int> p = positions[corpus.at(first+j)];
				for(int k = 0; k < p.size(); k++){
					int pos = p.at(k);
					if( pos >= first && pos <= last){
						times++;
						visto[pos - first]=true;;
					}
					else if(pos > last)
						break;
				}
				if(first_word_ap< times){
					third_word = second_word;
					third_word_ap = second_word_ap;
					second_word = first_word;
					second_word_ap = first_word_ap;
					first_word = corpus.at(first+j);
					first_word_ap = times;
				}
				else if(second_word_ap< times){
					third_word = second_word;
					third_word_ap = second_word_ap;
					second_word = corpus.at(first+j);
					second_word_ap = times;
				}
				else if(third_word_ap < times){
					third_word = corpus.at(first+j);
					third_word_ap = times;
				}
			}
		}
		cout << "Case #"<< i+1 << ": ";
		cout << first_word  << " " << first_word_ap  << ",";
		cout << second_word << " " << second_word_ap << ",";
		cout << third_word  << " " << third_word_ap << endl;
	}
	return 0;
}