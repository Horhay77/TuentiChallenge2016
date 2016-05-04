/* 
 * Author: JORGE HERNANDEZ DE BENITO
 *
 */

#include <iostream>
#include <string>
#include <map>
#include <vector> 
using namespace std;

typedef struct{
	char input;
	char output;
	int movement;
	string newState;
} transition;

int main(int argc, char** argv) {
    ios_base::sync_with_stdio(false);
    // Lectura de la Turing Machine
    map<string, vector<transition> > machine;
    string token;
    cin >> token >> token;// leemos  --- y code:
    cin >> token; // leemos el primer estado
    while(token.compare("tapes:")){ //0 significa que son iguales
    	//Quitar el : del estado
    	string stateName = token.substr(0,token.size()-1);
    	//cout << "Found state named " << stateName << endl;
    	cin >> token; //Leemos el caracter que dispara la rimera transicion
		while(token.at(0)=='\''){
			transition newtransition;
			if(token.size()==1){ //entrada ' ':
				cin >> token;
				newtransition.input = ' ';
			}
			else
				newtransition.input = token.at(1);
			newtransition.output = 'W'; //Wrong es no hace nada
			newtransition.movement = 0; // Nos desplazamos 0 a priori en la cinta
			newtransition.newState = "";	// a priori no hay cambio de estado
			cin >> token;
			while(token.at(0)!='\'' && token.compare("tapes:")){
				if(!token.compare("write:")){
					cin >> token;
					newtransition.output = token.at(1);
					//cout << newtransition.input << " write "<< newtransition.output << endl; 
				}
				else if(!token.compare("move:")){
					cin >> token;
					if(!token.compare("right")){
						newtransition.movement = 1;
					//	cout << newtransition.input << " move right"<< endl;
					}
					else{
						newtransition.movement = -1;
						//cout << newtransition.input << " move left"<< endl;
					}
				}
				else if(!token.compare("state:")){
					cin >> token;
					newtransition.newState = token;
					//cout << newtransition.input << " goes to "<< newtransition.newState << endl;
				}
				else{
					break;
				}
				//Lectura de la siguiente transicion o estado
				cin >> token;
			}
			//Añadimos el estado alº conjunto de estados de la maquina.
			//cout << "Añado una nueva transicion desde el estado "<< stateName;
			//cout << " hasta el estado "<< newtransition.newState<<endl;
			machine[stateName].push_back(newtransition);	
		}    	
    }
    //Vamos a probar a imprimir los estados:
    /*for (map< string , vector< transition> >::iterator it=machine.begin(); it!=machine.end(); ++it)
    	cout << it->first << '\n';
	*/
    int caso;
    char doblespuntos;
    string cinta;
    string state;
    int pos;
 	int maxpos;
 	int end;
    while(cin >> caso >> doblespuntos >> cinta){
    	//procesar cinta
    	cinta = cinta.substr(1,cinta.length()-2);
    	maxpos = cinta.length();
    	state = "start";
    	pos = 0;
    	end = 0;
    	while(!end){
    		end = 1;
    		for(vector<transition>::iterator it=machine[state].begin(); it != machine[state].end();it++){
    			if(it->input == cinta.at(pos)){
    				//Realizar la acción indicada
    				if(it->output != 'W')
    					cinta.at(pos)=it->output;
    				if(it->newState.length()>0)
    					state = it->newState;
    				pos+=it->movement;
    				if(pos == maxpos){
    					cinta+=' ';
    					maxpos++;
    				}
    				end = 0;
    				break;
    			}
    		}
    	}
    	cout << "Tape #"<<caso<<": "<< cinta << endl;
    }
    return 0;
}