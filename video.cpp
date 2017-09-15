#include "video.h"

Video::Video()
{
}

void Video::creerVideo(string nomChemin, string nomFichier, int tailleVideo, string nouveauDossier, string traitement, Size frameSize){
    //Initialisation de l'objet VideoWriter
    VideoWriter oVideoWriter;
    oVideoWriter.open(nomChemin + "/" + nomFichier + "_" + /*traitement +*/ ".avi", CV_FOURCC('M','P','E','G'), 25, frameSize, true);
    cout << "write to folder : " << nomChemin + "/" + nomFichier + "_" +/* traitement +*/ ".mp4" << " " << frameSize.width << " " << frameSize.height << endl;
    //Verification si le VideoWriter a ete initialise avec succes
    if (oVideoWriter.isOpened() && tailleVideo > 1)
    {
        for(int i = 1 ; i <= tailleVideo ; i++)
        {
            //Lecture des images enregistrees dans le dossier une par une
            Mat img = imread(cv::format((nouveauDossier /*+ "/" + traitement */+ "/frame%d.tif").c_str(), i).c_str(), CV_LOAD_IMAGE_COLOR);
            cv::resize(img, img, frameSize);
            //Ecriture de l'image dans l'objet VideoWriter pour l'enregistrement
            oVideoWriter.write(img);
            img.release();
        }
    }else{
        cout << "Erreur: Impossible de sauvegarder la video" << endl;
        //return -1;
    }
}
