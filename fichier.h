/*
 * fichier.h
 *
 *  Created on: 1 avr. 2016
 *      Author: raouf
 */

#ifndef FICHIER_H_
#define FICHIER_H_

using namespace std;
using namespace cv;
class fichier {
public:
	fichier();
	virtual ~fichier();
	void ecrire(int o, vector<int>  vn);
	void ecrired(float tab[][60]);
};

#endif /* FICHIER_H_ */
