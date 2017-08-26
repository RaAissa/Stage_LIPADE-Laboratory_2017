/*
 * fichier.cpp
 *
 *  Created on: 1 avr. 2016
 *      Author: raouf
 */

#include "fichier.h"

fichier::fichier() {
	// TODO Auto-generated constructor stub

}

fichier::~fichier() {
	// TODO Auto-generated destructor stub
}

void fichier::ecrire(int o, vector<int>  vn){

	  ofstream fichier("test4.txt", ios::out | ios::app);  //déclaration du flux et ouverture du fichier

	        if(fichier)  // si l'ouverture a réussi
	        {

	            // instructions

	        	fichier<<"image"<<o<<endl;

	                		for(int l=0;l<vn.size();l++){

	                			int y=vn[l];
	                			fichier<<y<<" ";

	                		}
	                		fichier<<""<<endl;

	                fichier.close();  // on referme le fichier

	        }
	        else  // sinon
	                cerr << "Erreur à l'ouverture !" << endl;



}

void fichier::ecrired(float tab[][60]){

	  ofstream fichier("testaff.txt", ios::out | ios::app);  //déclaration du flux et ouverture du fichier

	        if(fichier)  // si l'ouverture a réussi
	        {

	            // instructions

	        	fichier<<"dtw resultat"<<endl;

	                		for(int l=0;l<60;l++){
	                			for(int k=0;k<60;k++){
	                			float y=tab[l][k];
	                			fichier<<y<<"\t";

	                		}
	                		fichier<<""<<endl;
	                		}

	                fichier.close();  // on referme le fichier

	        }
	        else  // sinon
	                cerr << "Erreur à l'ouverture !" << endl;



}
