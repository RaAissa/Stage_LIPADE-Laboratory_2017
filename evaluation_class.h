#ifndef EVALUATION_CLASS_H
#define EVALUATION_CLASS_H
#include "etoile_k.h"
#include <math.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <sstream>
#include <iostream>
#include <fstream>
#include <time.h>
#include "lucaskanadecartedechaleur.h"
class Evaluation_class
{
public:
    Evaluation_class();
    void runevaluation(int&positionswitch,bool &premiere_fois,vector<Mat>allImages,int &position,int taillevideo, string nouveauDossier, string traitement);
};

#endif // EVALUATION_CLASS_H
