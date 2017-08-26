#include "lucaskanadecartedechaleur.h"

LucasKanadeCarteDeChaleur::LucasKanadeCarteDeChaleur()
{
}


//void LucasKanadeCarteDeChaleur::runCarteDeChaleur(int taillevideo, string nouveauDossier, string traitement){
//    Dossier *ddf;
//    ddf->creerDossier(nouveauDossier + "/" + traitement + "/Intensite_du_deplacementImage");
//    delete ddf;

//    Dossier *drdf;
//    drdf->creerDossier(nouveauDossier + "/" + traitement + "/Intensite_du_deplacementImage/PNG");
//    delete drdf;

//    Dossier *ddd;
//    ddd->creerDossier(nouveauDossier + "/" + traitement);
//    delete ddd;

//    Dossier *dddf;
//    dddf->creerDossier(nouveauDossier + "/" + traitement + "/PNG");
//    delete dddf;


//    for(int m = 1 ; m < taillevideo ; m++)
//    {
//        cout << m <<endl;
//        // Load two images and allocate other structures
//        Mat imgA = imread(cv::format((nouveauDossier + "/frame%d.tif").c_str(), m).c_str(), CV_LOAD_IMAGE_GRAYSCALE);
//        Mat imgB = imread(cv::format((nouveauDossier + "/frame%d.tif").c_str(), m+1).c_str(), CV_LOAD_IMAGE_GRAYSCALE);

//        Size img_sz = imgA.size();
//        Mat imgC(img_sz, CV_8UC3,cv::Scalar(0,0,0));
//        int win_size = 21;
//        int maxCorners = 2000000000000000;
//        std::vector<cv::Point2f> cornersA;
//        cornersA.reserve(maxCorners);
//        std::vector<cv::Point2f> cornersB;
//        cornersB.reserve(maxCorners);


//        for(int y = 0 ; y < imgA.rows ; y = y + 10){
//            for(int x = 0 ; x < imgA.cols ; x = x+ 10){

//                cornersA.push_back(Point(x,y));
//            }
//        }

//        for(int y = 0 ; y < imgB.rows ;  y = y + 10){
//            for(int x = 0 ; x < imgB.cols ;  x = x+ 10){
//                cornersB.push_back(Point(x,y));
//            }
//        }

//        std::vector<uchar> features_found;
//        features_found.reserve(maxCorners);
//        std::vector<float> feature_errors;
//        feature_errors.reserve(maxCorners);

//        calcOpticalFlowPyrLK(imgA, imgB, cornersA, cornersB, features_found, feature_errors, Size( win_size, win_size), 5, cvTermCriteria(CV_TERMCRIT_ITER | CV_TERMCRIT_EPS, 20, 0.3), 0);


//        Mat carte_de_chaleur(imgA.size(), CV_8UC3,Scalar(255,255,255));
//        double max = 0;
//        double min = 100000000;


//        //creer une image avec les resultats
//        vector<LineIterator> alllines;
//        for( int i=0; i < features_found.size(); i++ ){
//            Point p0( ceil( cornersA[i].x ), ceil( cornersA[i].y ) );
//            Point p1( ceil( cornersB[i].x ), ceil( cornersB[i].y ) );
//            double dist_euclidienne = sqrt((p0.x-p1.x)*(p0.x-p1.x) +  (p0.y-p1.y)*(p0.y-p1.y));
//            if(dist_euclidienne>=0){
//                cv::LineIterator li(carte_de_chaleur, p0, p1);
//                alllines.push_back(li);
//            }

//            if(dist_euclidienne > max){
//                max = dist_euclidienne;
//            }

//            if(dist_euclidienne < min){
//                min = dist_euclidienne;
//            }

//        }

//        //calculer la couleur du point a afficher
//        for(int i = 0; i < alllines.size();i++){
//            cv::LineIterator li = alllines.at(i);
//            int nbpoints = li.count;
//            Point p0 = li.pos();
//            Point p;
//            float max1 = max/5;
//            //arriver au dernier point de cette ligne
//            for(int i = 0 ; i < nbpoints ; i++,li++){
//                p = li.pos();
//            }
//            double d = sqrt((p0.x-p.x)*(p0.x-p.x) + (p0.y-p.y)*(p0.y-p.y));
//            float H = 0;
//            if ( d < max1){
//                H = (-240.0 * d/max1) + 240.0;
//            }

//            float r=0, g =0, b=0;
//            HSVtoRGB(&r, &g, &b, H);
//            rectangle(carte_de_chaleur, Rect(p0.x, p0.y,9,9),Scalar (b *255,g *255,r *255),-1 );
//        }

//        Mat img = imread(cv::format((nouveauDossier + "/frame%d.tif").c_str(), m).c_str(), CV_LOAD_IMAGE_COLOR);

//        Mat carte_de_chaleur_dist = Mat::zeros(imgC.size(), CV_8UC3);
//        addWeighted(img, 0.5, carte_de_chaleur, 0.5, 0.0, carte_de_chaleur_dist);
//        imwrite(cv::format((nouveauDossier + "/" + traitement + "/Intensite_du_deplacementImage/frame%d.tif").c_str(), m).c_str(), carte_de_chaleur_dist);
//        imwrite(cv::format((nouveauDossier + "/" + traitement + "/Intensite_du_deplacementImage/PNG/frame%d.png").c_str(), m).c_str(), carte_de_chaleur_dist);

//        imwrite(cv::format((nouveauDossier + "/" + traitement + "/frame%d.tif").c_str(), m).c_str(), carte_de_chaleur);
//        imwrite(cv::format((nouveauDossier + "/" + traitement + "/PNG/frame%d.png").c_str(), m).c_str(), carte_de_chaleur);

//        //reinitialisation de limage pour eviter laddition des differents resultats du flot optiaue dans la meme trame
//        carte_de_chaleur_dist.setTo(0);
//        carte_de_chaleur.setTo(0);
//    }
//}


void LucasKanadeCarteDeChaleur::runCarteDeChaleur(int taillevideo, string nouveauDossier, string traitement){
    Dossier::creerDossier(nouveauDossier + "/" + traitement + "/Intensite_du_deplacementImage");
    Dossier::creerDossier(nouveauDossier + "/" + traitement + "/Intensite_du_deplacementImage/PNG");
    Dossier::creerDossier(nouveauDossier + "/" + traitement);
    Dossier::creerDossier(nouveauDossier + "/" + traitement + "/PNG");
    Dossier::creerDossier(nouveauDossier + "/" + traitement +"/NonNormalise");
    Dossier::creerDossier(nouveauDossier + "/" + traitement +"/NonNormalise/PNG");

    map<int,int> histogramme;
    //    float magnitude_max = -1.0;

    int nombre_dist = 0;
    int derniere_valeur = 0;
    vector<LineIterator> alllines;
    vector<LineIterator> alllines_trame;

    Mat imgA = imread(nouveauDossier + "/frame1.tif", CV_LOAD_IMAGE_GRAYSCALE);
    Mat carte_de_chaleur(imgA.size(), CV_8UC3,Scalar(255,255,255));
    Mat carte_de_chaleur_nonNorm(imgA.size(), CV_8UC3,Scalar(255,255,255));

    for(int m = 1 ; m < taillevideo ; m++)
    {
        cout << m <<endl;
        // Load two images and allocate other structures
        Mat imgA = imread(cv::format((nouveauDossier + "/frame%d.tif").c_str(), m).c_str(), CV_LOAD_IMAGE_GRAYSCALE);
        Mat imgB = imread(cv::format((nouveauDossier + "/frame%d.tif").c_str(), m+1).c_str(), CV_LOAD_IMAGE_GRAYSCALE);

        int win_size = 21;
        int maxCorners = INT_MAX;
        std::vector<cv::Point2f> cornersA;
        cornersA.reserve(maxCorners);
        std::vector<cv::Point2f> cornersB;
        cornersB.reserve(maxCorners);


        for(int y = 0 ; y < imgA.rows ; y = y + 10){
            for(int x = 0 ; x < imgA.cols ; x = x+ 10){
                cornersA.push_back(Point(x,y));
            }
        }

        for(int y = 0 ; y < imgB.rows ;  y = y + 10){
            for(int x = 0 ; x < imgB.cols ;  x = x+ 10){
                cornersB.push_back(Point(x,y));
            }
        }

        std::vector<uchar> features_found;
        features_found.reserve(maxCorners);
        std::vector<float> feature_errors;
        feature_errors.reserve(maxCorners);

        calcOpticalFlowPyrLK(imgA, imgB, cornersA, cornersB, features_found, feature_errors, Size( win_size, win_size), 5, cvTermCriteria(CV_TERMCRIT_ITER | CV_TERMCRIT_EPS, 20, 0.3), 0);

        double maximum = -1.0;
        //creer une image avec les resultats
        //        vector<LineIterator> alllines;
        for( int i=0; i < features_found.size(); i++ ){
            Point p0( ceil( cornersA[i].x ), ceil( cornersA[i].y ) );
            Point p1( ceil( cornersB[i].x ), ceil( cornersB[i].y ) );
            double dist_euclidienne = sqrt((p0.x-p1.x)*(p0.x-p1.x) +  (p0.y-p1.y)*(p0.y-p1.y));
            int dist_euclidienne_int = (int) dist_euclidienne;

            cv::LineIterator line_trame(carte_de_chaleur_nonNorm, p0, p1);
            alllines_trame.push_back(line_trame);

            if(dist_euclidienne > maximum){
                maximum = dist_euclidienne;
            }


            nombre_dist++;
            map<int,int>::iterator search = histogramme.find(dist_euclidienne_int);
            if(search != histogramme.end()) {
                //                   std::cout << "Found avant" << search->first << " " << search->second << '\n';
                search->second++;
                //                   std::cout << "Found apres" << search->first << " " << search->second << '\n';
            }
            else {
                //                   std::cout << "Not found\n";
                histogramme.insert(pair<int,int>(dist_euclidienne_int, 1));
            }
        }

        //calculer la couleur du point a afficher
        for(int i = 0; i < alllines_trame.size();i++){
            cv::LineIterator line = alllines_trame.at(i);
            int nbpoints = line.count;
            Point p0 = line.pos();
            Point p;
            float max1 = maximum/5;
            //arriver au dernier point de cette ligne
            for(int i = 0 ; i < nbpoints ; i++,line++){
                p = line.pos();
            }
            double d = sqrt((p0.x-p.x)*(p0.x-p.x) + (p0.y-p.y)*(p0.y-p.y));
            float H = 0;
            if ( d < max1){
                H = (-240.0 * d/max1) + 240.0;
            }

            float r=0, g =0, b=0;
            HSVtoRGB(&r, &g, &b, H);
            rectangle(carte_de_chaleur_nonNorm, Rect(p0.x, p0.y,9,9),Scalar (b *255,g *255,r *255),-1 );
        }

        imwrite(cv::format((nouveauDossier + "/" + traitement + "/NonNormalise/frame%d.tif").c_str(), m).c_str(), carte_de_chaleur_nonNorm);
        imwrite(cv::format((nouveauDossier + "/" + traitement + "/NonNormalise/PNG/frame%d.png").c_str(), m).c_str(), carte_de_chaleur_nonNorm);
        //        break;
    }

    for (map<int,int>::iterator it=histogramme.begin(); it!=histogramme.end(); ++it){
        std::cout << it->first << " => " << it->second << '\n';
    }

    int nombre_dist_reduit = nombre_dist*0.95;
    cout << "nombre de dist : " << nombre_dist <<endl;
    cout << "95% du nombre de dist : " << nombre_dist_reduit <<endl;

    int somme = 0;

    for (map<int,int>::iterator it=histogramme.begin(); it!=histogramme.end(); ++it){
        somme = somme + it->second;
        cout << "somme : " << somme << endl;
        if(somme >= nombre_dist_reduit){
            derniere_valeur = it->first;
            cout << "derniere valeur : " << derniere_valeur << endl;
            break;
        }
    }

    //    magnitude_max = (float)derniere_valeur;
    map<int,int>::iterator it;
    it=histogramme.find (derniere_valeur);
    histogramme.erase ( it, histogramme.end() );

    //*******************************************************************************************************************************

    for(int m = 1 ; m < taillevideo ; m++)
    {   cout << m <<endl;
        // Load two images and allocate other structures
        Mat imgA = imread(cv::format((nouveauDossier + "/frame%d.tif").c_str(), m).c_str(), CV_LOAD_IMAGE_GRAYSCALE);
        Mat imgB = imread(cv::format((nouveauDossier + "/frame%d.tif").c_str(), m+1).c_str(), CV_LOAD_IMAGE_GRAYSCALE);
        int win_size = 21;
        int maxCorners = INT_MAX;
        std::vector<cv::Point2f> cornersA;
        cornersA.reserve(maxCorners);
        std::vector<cv::Point2f> cornersB;
        cornersB.reserve(maxCorners);

        for(int y = 0 ; y < imgA.rows ; y = y + 10){
            for(int x = 0 ; x < imgA.cols ; x = x+ 10){
                cornersA.push_back(Point(x,y));
            }
        }

        for(int y = 0 ; y < imgB.rows ;  y = y + 10){
            for(int x = 0 ; x < imgB.cols ;  x = x+ 10){
                cornersB.push_back(Point(x,y));
            }
        }

        std::vector<uchar> features_found;
        features_found.reserve(maxCorners);
        std::vector<float> feature_errors;
        feature_errors.reserve(maxCorners);

        calcOpticalFlowPyrLK(imgA, imgB, cornersA, cornersB, features_found, feature_errors, Size( win_size, win_size), 5, cvTermCriteria(CV_TERMCRIT_ITER | CV_TERMCRIT_EPS, 20, 0.3), 0);

        //        double max = 0;
        //        double min = 100000000;
        //creer une image avec les resultats

        for( int i=0; i < features_found.size(); i++ ){
            Point p0( ceil( cornersA[i].x ), ceil( cornersA[i].y ) );
            Point p1( ceil( cornersB[i].x ), ceil( cornersB[i].y ) );
            double dist_euclidienne = sqrt((p0.x-p1.x)*(p0.x-p1.x) +  (p0.y-p1.y)*(p0.y-p1.y));
            int dist_euclidienne_int = (int) dist_euclidienne;
            //            cout << "derniere_valeur" << derniere_valeur <<endl;

            if(dist_euclidienne_int <= derniere_valeur){
                cv::LineIterator li(carte_de_chaleur, p0, p1);
                alllines.push_back(li);
            }
        }

        //calculer la couleur du point a afficher
        for(int i = 0; i < alllines.size();i++){
            cv::LineIterator li = alllines.at(i);
            int nbpoints = li.count;
            Point p0 = li.pos();
            Point p;
            //float max1 = derniere_valeur/2;
            float max1 = derniere_valeur;
            //arriver au dernier point de cette ligne
            for(int i = 0 ; i < nbpoints ; i++,li++){
                p = li.pos();
            }
            double d = sqrt((p0.x-p.x)*(p0.x-p.x) + (p0.y-p.y)*(p0.y-p.y));
            float H = 0;
            if ( d <= max1){
                H = (-240.0 * d/max1) + 240.0;
            }
            float r=0, g =0, b=0;
            HSVtoRGB(&r, &g, &b, H);
            rectangle(carte_de_chaleur, Rect(p0.x, p0.y,9,9),Scalar (b *255,g *255,r *255),-1 );
        }

        Mat img = imread(cv::format((nouveauDossier + "/PNG/frame%d.png").c_str(), m).c_str(), CV_LOAD_IMAGE_COLOR);
        Mat carte_de_chaleur_dist = Mat::zeros(img.size(), CV_8UC3);
        addWeighted(img, 0.5, carte_de_chaleur, 0.5, 0.0, carte_de_chaleur_dist);
        imwrite(cv::format((nouveauDossier + "/" + traitement + "/Intensite_du_deplacementImage/frame%d.tif").c_str(), m).c_str(), carte_de_chaleur_dist);
        imwrite(cv::format((nouveauDossier + "/" + traitement + "/Intensite_du_deplacementImage/PNG/frame%d.png").c_str(), m).c_str(), carte_de_chaleur_dist);

        imwrite(cv::format((nouveauDossier + "/" + traitement + "/frame%d.tif").c_str(), m).c_str(), carte_de_chaleur);
        imwrite(cv::format((nouveauDossier + "/" + traitement + "/PNG/frame%d.png").c_str(), m).c_str(), carte_de_chaleur);

        //reinitialisation de limage pour eviter laddition des differents resultats du flot optiaue dans la meme trame
        carte_de_chaleur_dist.setTo(cv::Scalar(255,255,255));
        carte_de_chaleur.setTo(cv::Scalar(255,255,255));
        alllines.clear();
        //    break;
    }

}



void LucasKanadeCarteDeChaleur::HSVtoRGB(float *r, float *g, float *b, float h, float s, float v)
{
    int i;
    float f, p, q, t;

    if (s == 0) {
        *r = *g = *b = v;   // achromatic (grey)
        return;
    }

    h /= 60.0;			// sector 0 to 5
    i = (int)floor(h);
    f = h - i;			// factorial part of h
    p = v * (1 - s);
    q = v * (1 - s * f);
    t = v * (1 - s * (1 - f));

    switch (i) {
    case 0:
        *r = v;
        *g = t;
        *b = p;
        break;
    case 1:
        *r = q;
        *g = v;
        *b = p;
        break;
    case 2:
        *r = p;
        *g = v;
        *b = t;
        break;
    case 3:
        *r = p;
        *g = q;
        *b = v;
        break;
    case 4:
        *r = t;
        *g = p;
        *b = v;
        break;
    default:		// case 5:
        *r = v;
        *g = p;
        *b = q;
        break;
    }
}
