#ifndef LUCASKANADEDIRECTION_H
#define LUCASKANADEDIRECTION_H

#include <opencv2/opencv.hpp>
#include "opencv/highgui.h"
#include "dossier.h"

class LucasKanadeDirection
{
public:
    LucasKanadeDirection();
    void runDirectionsDeplacement(int taillevideo, string nouveauDossier, string traitement);
};

#endif // LUCASKANADEDIRECTION_H
