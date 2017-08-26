#ifndef VIDEO_H
#define VIDEO_H
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;

class Video
{
public:
    Video();
    void creerVideo(string nomChemin, string nomFichier, int tailleVideo, string nouveauDossier, string traitement, Size frameSize);
};

#endif // VIDEO_H
