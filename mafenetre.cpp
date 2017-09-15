/*
 * Auteur : Marah Poos
 * Date de création: 01/01/2016
 * Modifiée par: Van Cuong KIEU
 * Date de modification: 30/09/2016
 * Modifié par: Raouf AISSA
 * Date de modification: 01/03/2017
 */
#include "mafenetre.h"
//modifié
// List of the algorithms
std::string folder[] = {"Noir_et_Blanc", "Contours", "Flouter", "Negatif",
                        "Rouge", "Vert", "Bleu", "Enlever_Teinte", "Saturation",
                        "Brillance", "HSV", "Special16", "Special64",
                        "Contours_Gras", "GrabCut", "Inpainting_Telea", "Criminisi" ,
                        "Inpainting_Telea_Image", "Inpainting_Criminisi_Image", "LucasKanade",
                        "LucasKanade_Direction_de_deplacement", "LucasKanade_Intensite_du_deplacement",
                        "LucasKanade_Direction_Intensite", "GrabCut_LucasKanade", "Inpainting_Inverse","Analyse_de_Lucas_et_Kanade","Binarisation","Etoile","Etoile_Kmeans","Evaluation"};
//modifié
int lis[]={50,100,300,500,1000};
int listr[]={1,3,5,10,20,30};
int listr1[]={0,1,2,3};
int listr2[]={3,5,7,9,10,12,13,15,21,25,30,35,40,45,49,75,100,150};
int listr5[]={2,3,4,5,6,7,8,9,10,11,12};
MaFenetre::MaFenetre() : QWidget(){
    positionSlider = 1;
    height_video1 = 0;
    height_video2 = 0;
    height_image = 0;

    setFixedSize(1850,1000);
    imaFolder = std::vector<std::string>(folder, folder +  sizeof(folder) / sizeof(std::string));
    // Construction du bouton "ouvrir"
    bouton_ouvrir = new QPushButton("open a video", this);
    bouton_ouvrir->setFont(QFont("Liberation Serif", 14));
    bouton_ouvrir->setCursor(Qt::PointingHandCursor);
    bouton_ouvrir->setFixedSize(100,30);

    //Ouverture de la boite de recherche de la vidéo
    QObject::connect(bouton_ouvrir, SIGNAL(clicked()), this, SLOT(ouvrirDialogue()));
    //Construction du bouton "lancer"
    bouton_lancer = new QPushButton("Launch");
    bouton_lancer->setFont(QFont("Liberation Serif", 14));
    bouton_lancer->setCursor(Qt::PointingHandCursor);
    bouton_lancer->setFixedSize(100,30);

    //Modifié


    // lecture direct des tifs
    bouton_tiff = new QPushButton("Open a TIF");
    bouton_tiff->setFont(QFont("Liberation Serif", 14));
    bouton_tiff->setCursor(Qt::PointingHandCursor);
    bouton_tiff->setFixedSize(100,30);

    QObject::connect(bouton_tiff, SIGNAL(clicked()), this, SLOT(ouvrirtiff()));
    //Liaison du bouton au slot qui permet de lancer le traitement de la video
    QObject::connect(bouton_lancer, SIGNAL(clicked()), this, SLOT(lancer()));
    //Construction du bouton "enregistrer"
    bouton_enregistrer = new QPushButton("Save");
    bouton_enregistrer->setFont(QFont("Liberation Serif", 14));
    bouton_enregistrer->setCursor(Qt::PointingHandCursor);
    bouton_enregistrer->setFixedSize(100,30);

    //Liaison du bouton au slot qui permet d'enregistrer la video
    QObject::connect(bouton_enregistrer, SIGNAL(clicked()), this, SLOT(enregistrer()));

    //Construction du bouton "jouer"
    bouton_play = new QPushButton("Play");
    bouton_play->setFont(QFont("Liberation Serif", 14));
    bouton_play->setCursor(Qt::PointingHandCursor);

    //Liaison du bouton au slot qui permet d'enregistrer la video
    QObject::connect(bouton_play, SIGNAL(clicked()), this, SLOT(play()));

    //Construction du bouton "ouvrir image"
    bouton_ouvrirImage = new QPushButton("Open a picture");
    bouton_ouvrirImage->setFont(QFont("Liberation Serif", 14));
    bouton_ouvrirImage->setCursor(Qt::PointingHandCursor);
    bouton_ouvrirImage->setFixedSize(100,30);

    //Liaison du bouton au slot qui permet d'enregistrer la video
    QObject::connect(bouton_ouvrirImage, SIGNAL(clicked()), this, SLOT(ouvrirImage()));

    //modifié
    //   checkbox = new QCheckBox("TIF", this);
    //   QObject::connect(checkbox, SIGNAL(stateChanged(int)), this, SLOT(verif()));
    //   checkbox->setChecked(false);

    //Construction du bouton "Ouvrir video"
    bouton_ouvrirVideo = new QPushButton("Open a video");
    bouton_ouvrirVideo->setFont(QFont("Liberation Serif", 14));
    bouton_ouvrirVideo->setCursor(Qt::PointingHandCursor);
        bouton_ouvrirVideo->setFixedSize(100,30);

    //Liaison du bouton au slot qui permet d'ouvrir la video pour inpainitng
    QObject::connect(bouton_ouvrirVideo, SIGNAL(clicked()), this, SLOT(ouvrirVideoInpainting()));

    //Construction des labels pour les videos initiale et traitee
    image_initiale = QImage(100, 100, QImage::Format_ARGB32);
    image_initiale.fill(qRgb(0, 0, 0));
    label_videoInitiale = new QLabel("Vidéo initiale",this);
    label_videoInitiale->setPixmap(QPixmap::fromImage(image_initiale));


    image_evaluation = QImage(100, 100, QImage::Format_ARGB32);
    image_evaluation.fill(qRgb(0, 0, 0));
    label_image_evaluation = new QLabel("Vidéo_évaluation",this);
    label_image_evaluation->setPixmap(QPixmap::fromImage(image_evaluation));



//    label_videoInitiale->setScaledContents(true);
//    label_videoInitiale->adjustSize();


    // label_videoInitiale->geometry().x
    image_traitee = QImage(100, 100, QImage::Format_ARGB32);
    image_traitee.fill(qRgb(0, 0, 0));
    label_videoTraitee = new QLabel("Vidéo traitée",this);
    label_videoTraitee->setPixmap(QPixmap::fromImage(image_traitee));


    image_flot_optique = QImage(100, 100, QImage::Format_ARGB32);
    image_flot_optique.fill(qRgb(0, 0, 0));

      label_flot_optique = new QLabel("Vidéo f_optique",this);
      label_flot_optique->setPixmap(QPixmap::fromImage(image_flot_optique));


      image_K_means_nD_t = QImage(100, 100, QImage::Format_ARGB32);
      image_K_means_nD_t.fill(qRgb(0, 0, 0));
        label_K_means_nD_t = new QLabel("K_means",this);
        label_K_means_nD_t->setPixmap(QPixmap::fromImage(image_K_means_nD_t));

    //Construction du slider de la vidéo
    lcd = new QLCDNumber(this);
    lcd->setSegmentStyle(QLCDNumber::Flat);
    slider = new QSlider(Qt::Horizontal, this);
    slider->setRange(0, 0);

    //slider_gauche->setGeometry(10, 60, 150, 20);
    QObject::connect(slider, SIGNAL(valueChanged(int)), lcd, SLOT(display(int))) ;
    QObject::connect(slider, SIGNAL(sliderMoved(int)), this, SLOT(sliderMovedslot(int)));
    image_inpainting = QImage(100, 100, QImage::Format_ARGB32);
    image_inpainting.fill(qRgb(0, 0, 0));
    label_image_inpainting = new QLabel("Vidéo traitée",this);
    label_image_inpainting->setPixmap(QPixmap::fromImage(image_inpainting));

    //Construction des Qlabel qui cont   liste1->addItem("500");iennent la position du pixel sur lequel lutilisateur a clique
    label_positionPremierPoint = new QLabel("",this);
    label_positionSecondPoint = new QLabel("",this);

    //Construction des Qlabel qui contiennent la position du pixel de limpage pour linpainting sur lequel lutilisateur a clique
    label_positionPremierPointImage = new QLabel("",this);
    label_positionSecondPointImage = new QLabel("",this);

    //Construction des Qlabel qui contiennent la position du pixel de la video pour vinverser linpainting sur lequel lutilisateur a clique
    label_positionPremierPointVideo = new QLabel("",this);
    label_positionSecondPointVideo = new QLabel("",this);

    //Video permettant de faire de linpainting en inversant objets
    video_inpainting = QImage(100, 100, QImage::Format_ARGB32);
    video_inpainting.fill(qRgb(0, 0, 0));
    label_videoInpainting = new QLabel("Vidéo pour inpainting",this);
    label_videoInpainting->setPixmap(QPixmap::fromImage(video_inpainting));

    //Construction de la liste deroulante
    liste = new QComboBox(this);
    liste->setFont(QFont("Liberation Serif", 12));

    liste->addItem("Noir et Blanc");
    liste->addItem("Contours");
    liste->addItem("Flouter");
    liste->addItem("Negatif");
    liste->addItem("Rouge");
    liste->addItem("Vert");
    liste->addItem("Bleu");
    liste->addItem("Enlever Teinte");
    liste->addItem("Saturation");
    liste->addItem("Brillance");
    liste->addItem("HSV");
    liste->addItem("Special16");
    liste->addItem("Special64");
    liste->addItem("Contours Gras");
    liste->addItem("GrabCut");
    liste->addItem("Inpainting Telea");
    liste->addItem("Inpainting Criminisi");
    liste->addItem("Inpainting Telea Image");
    liste->addItem("Inpainting Criminisi Image");
    liste->addItem("Lucas Kanade");
    liste->addItem("Direction de deplacement");
    liste->addItem("Intensite du deplacement");
    liste->addItem("Direction & Intensite");
    liste->addItem("GrabCut Lucas Kanade");
    liste->addItem("Inpainting Inverse");
    //modifié
    liste->addItem("Analyse de Lucas et Kanade");
    liste->addItem("Binaire");
    liste->addItem("Etoile");
    liste->addItem("Etoile_Kmeans");
    liste->addItem("Evaluation");
    //

    QObject::connect(liste, SIGNAL(currentIndexChanged(int)),this, SLOT(afficher(int)));

    //Modifié
    liste1 = new QComboBox(this);
    liste1->setFont(QFont("Liberation Serif", 14));
    bouton_ouvrirVideo->setFixedSize(120,30);
    liste1->addItem("50 Trames");
    liste1->addItem("100");
    liste1->addItem("300");
    liste1->addItem("500");
    liste1->addItem("1000");
    QObject::connect(liste1, SIGNAL(currentIndexChanged(int)),this, SLOT(afficher1(int)));

    //modifié
    liste2 = new QComboBox(this);
    liste2->setFont(QFont("Liberation Serif", 14));
    liste2->addItem("Tracking/1 pixel");
    liste2->addItem("Tracking/3 pixel");
    liste2->addItem("Tracking/5 pixels");
    liste2->addItem("Tracking/10 pixels");
    liste2->addItem("Tracking/20 pixels");
    liste2->addItem("Tracking/30 pixels");
    QObject::connect(liste2, SIGNAL(currentIndexChanged(int)),this, SLOT(afficher2(int)));

    liste3 = new QComboBox(this);
    liste3->setFont(QFont("Liberation Serif", 14));
    liste3->addItem("No overlap");
    liste3->addItem("Overlap 1 trame");
    liste3->addItem("overlap 2 trame");
    liste3->addItem("overlap 3 trame");
    QObject::connect(liste3, SIGNAL(currentIndexChanged(int)),this, SLOT(afficher3(int)));
    liste4 = new QComboBox(this);
    //int listr2[]={3,5,7,9,15,21,25,30,35,40,45,49,100};
    liste4->setFont(QFont("Liberation Serif", 14));
    liste4->setFixedSize(120,30);
    liste4->addItem("winsize:3");
    liste4->addItem("5");
    liste4->addItem("7");
    liste4->addItem("9");
    liste4->addItem("10");
    liste4->addItem("11");
    liste4->addItem("13");
    liste4->addItem("15");
    liste4->addItem("21");
    liste4->addItem("25");
    liste4->addItem("30");
    liste4->addItem("35");
    liste4->addItem("40");
    liste4->addItem("45");
    liste4->addItem("49");
    liste4->addItem("75");
    liste4->addItem("100");
    liste4->addItem("150");

    QObject::connect(liste4, SIGNAL(currentIndexChanged(int)),this, SLOT(afficher4(int)));
     liste5 = new QComboBox(this);
      liste5->setFont(QFont("Liberation Serif", 14));
    liste5->addItem("Kmeans Index:2");

    liste5->addItem("3");
    liste5->addItem("4");
    liste5->addItem("5");
    liste5->addItem("6");
    liste5->addItem("7");
    liste5->addItem("8");
    liste5->addItem("9");
    liste5->addItem("10");
    liste5->addItem("11");
    liste5->addItem("12");
     QObject::connect(liste5, SIGNAL(currentIndexChanged(int)),this, SLOT(afficher5(int)));


//   onglets
     onglets = new QTabWidget(this);
     onglets->addTab(label_videoInitiale, "Image Originale");
     onglets->addTab(label_videoTraitee, "Image_traitée");
     onglets->addTab(label_image_inpainting, "Image inpaité");
     onglets->addTab(label_videoInpainting, "Vidéo inpaintée");
     onglets->addTab(label_flot_optique, "Flot optique");
     onglets->addTab(label_K_means_nD_t, "Temporel resultat");
     onglets->addTab(label_image_evaluation, "Evaluation");

    //Ajout des widgets au layout

     layout = new QGridLayout;
     layout->addWidget(bouton_ouvrir,0,0);
     layout->addWidget(liste,0,1);
     layout->addWidget(bouton_lancer,0,2);
     layout->addWidget(bouton_ouvrirImage, 0,3);
     layout->addWidget(bouton_ouvrirVideo, 0,4);
     layout->addWidget(bouton_tiff, 0,5);

     layout1 = new QGridLayout;
     onglets->setGeometry(5,50, 1840, 800);
     layout1->addWidget(onglets);

//    layout->addWidget(label_videoInitiale, 1,0);
//    layout->addWidget(label_videoTraitee, 1,1);
//    layout->addWidget(label_image_inpainting, 1, 3);
//    layout->addWidget(label_videoInpainting, 1,4);

    layout->addWidget(label_positionPremierPoint,2,0);
    layout->addWidget(label_positionPremierPointImage, 2, 3);
    layout->addWidget(label_positionPremierPointVideo, 2,4);

    layout->addWidget(label_positionSecondPoint,3,0);
    layout->addWidget(label_positionSecondPointImage, 3, 3);
    layout->addWidget(label_positionSecondPointVideo, 3,4);
    layout->addWidget(liste3, 3,5);

    layout->addWidget(slider,4,0);
    layout->addWidget(lcd, 4, 1);
    layout->addWidget(bouton_enregistrer, 4, 2);
    layout->addWidget(bouton_play,4 ,3);
    layout->addWidget(liste1, 4,4);
    layout->addWidget(liste2, 4,5);
    layout->addWidget(liste5, 4,6);
    layout->addWidget(liste4,5,0);

    this->setWindowTitle("Analyse de l'impact du contenu d'une video sur l'impression visuelle:analyse du mouvement");
    //Ajout du layout a la fenetre
    setLayout(layout);
}

//modifié
void MaFenetre::verif(){
       checkbox->setChecked(true);
}

//Slot qui permet de choisir la video initiale
void MaFenetre::ouvrirDialogue(){
    //Ouverture de la boite de selection de video
    allImages.clear();
    QString fichier = QFileDialog::getOpenFileName(this, "Ouvrir un fichier", QDir::homePath(), "Videos (*.mov *.avi *.mp4 *.VOB )");
    //Obtention le nom du chemin et du fichier sans l'extension
    QFileInfo fileInfo(fichier);
    // Path vers le fichier
    dirPath = fileInfo.absolutePath();
    // Nom du fichier (sans le path)
    fileName = fileInfo.fileName();
    nomChemin = dirPath.toStdString();
    nomFichier = fileName.toStdString();
    //Enlevement de l'extension du fichier
    nomFichier = nomFichier.substr(0, nomFichier.find_last_of("."));
    //--------
    nomFichier.erase(std::remove(nomFichier.begin(),nomFichier.end(),' '),nomFichier.end());// remove space between words
    cout << "Path vers le fichier : " << nomChemin << endl;
    cout << "Nom du fichier : " << nomFichier << endl;
    nouveauDossier = (nomChemin + "/" + nomFichier);
    cout << "Chemin du nouveau dossier : " << nouveauDossier << endl;
    //Creation du nouveau dossier
    Dossier::creerDossier(nouveauDossier);
    //Creation du nouveau dossier
    Dossier::creerDossier(nouveauDossier + "/PNG");
    //Lecture de la vidéo
    cv::VideoCapture inputVideo(fichier.toStdString().c_str());
    inputVideo.set(CV_CAP_PROP_CONVERT_RGB, 3);
    cout << inputVideo.isOpened()<< endl;
    //En cas de non-ouverture de la video, sortir du program
    if (!inputVideo.isOpened())
    {
        cout << "Imposible d'ouvrir la video" << endl;
        //return -1;
        cout << "4" << endl;
    }
    taillevideo = 1;
    allImages.clear();
    QFileInfo photo(cv::format((nouveauDossier+ "/frame%d.tif").c_str(),taillevideo).c_str());
    if( !photo.exists()){
     while(true){
         Mat frame;
            //Lecture de la nouvelle trame de la video
            if (!inputVideo.read(frame))
            {
                cout << "Fin de la lecture de la vidéo" << endl;
                break;
            }
            // allImages.push_back(frame);
            // Sauvegarde de la trame dans un fichier
            imwrite(cv::format((nouveauDossier + "/frame%d.tif").c_str(),taillevideo).c_str(), frame);
            imwrite(cv::format((nouveauDossier + "/PNG/frame%d.png").c_str(),taillevideo).c_str(), frame);
            label_videoInitiale->setPixmap(QPixmap(QPixmap((nouveauDossier + "/frame1.tif").c_str())));
            //Sans succes, sortir de la boucle
            taillevideo++;
        }
     }else{
    while(true){
    QFileInfo photo(cv::format((nouveauDossier+ "/frame%d.tif").c_str(),taillevideo).c_str());
        if(!photo.exists()){
            cout<<"cette image n existe"<<endl;
            break;
        }
        taillevideo++;
    }
    }
    taillevideo--;
    cout << "Taille de la video : " << taillevideo << endl;
    label_videoInitiale->setPixmap(QPixmap(QPixmap((nouveauDossier + "/frame1.tif").c_str())));
    label_videoInitiale->setGeometry(5, 70, 200, 200);
    slider->setRange(1, taillevideo);
}

//Modifié ouvrir Tiff
void MaFenetre::ouvrirtiff(){


//    string commande = "python /home/aissa/Bureau/from_armand/courbe.py";
//     system(commande.c_str());
    allImages.clear();
    QString fichier1 = QFileDialog::getOpenFileName(this, "Ouvrir une image",QDir::homePath()+"/Téléchargements/", "Images (*.jpg *.png *.tif)");
    //Obtention le nom du chemin et du fichier avec l'extension
    QFileInfo fileInfo(fichier1);
    // Path vers l'image
    dirPath = fileInfo.absolutePath();
    // Nom du fichier (sans le path)
    fileName = fileInfo.fileName();
    nomChemin = dirPath.toStdString();
    nomFichier = fileName.toStdString();
    //Enlevement de l'extension du fichier
    nomFichier = nomFichier.substr(0, nomFichier.find_last_of("."));
    //--------
    nomFichier.erase(std::remove(nomFichier.begin(),nomFichier.end(),' '),nomFichier.end());
    nouveauDossier = dirPath.toStdString();
    taillevideo = 1;
while(true){
    QFileInfo photo(cv::format((nouveauDossier+ "/frame%d.tif").c_str(),taillevideo).c_str());
    if(!photo.exists()){
        cout<<"cette image n existe"<<endl;
        break;
    }
    taillevideo++;
}
taillevideo--;
cout<<"taille video:" +taillevideo<<endl;
// height_image = (QPixmap(dirPathImage2).height());
//    height_difference = ((dHeight-height_imag

//    height_image = img.rows;
label_videoInitiale->setPixmap(QPixmap((nouveauDossier+"/frame1.tif").c_str()));
label_videoInitiale->setGeometry(5, 5,500,500);
slider->setRange(1, taillevideo);
}

    //Slot qui permet de choisir la video inpainting
    void MaFenetre::ouvrirVideoInpainting(){
    //Ouverture de la boite de selection de video
    QString fichier = QFileDialog::getOpenFileName(this, "Ouvrir un fichier", QString(), "Videos (*.mov *.avi *.mp4)");
    //Obtention le nom du chemin et du fichier sans l'extension
    QFileInfo fileInfo(fichier);
    // Path vers le fichier
    dirPath = fileInfo.absolutePath();
    // Nom du fichier (sans le path)
    fileName = fileInfo.fileName();
    nomCheminVideo = dirPath.toStdString();
    nomFichierVideo = fileName.toStdString();
    //Enlevement de l'extension du fichier
    size_t lastindex = nomFichierVideo.find_last_of(".");
    nomFichierVideo = nomFichierVideo.substr(0, lastindex);
    //--------
    nomFichierVideo.erase(std::remove(nomFichierVideo.begin(),nomFichierVideo.end(),' '),nomFichierVideo.end());
    cout << "Path vers le fichier Video : " << nomCheminVideo << endl;
    cout << "Nom du fichier Video : " << nomFichierVideo << endl;
    //Creation du chemin pour le nouveau dossier avec le nom de la video
    nouveauDossierVideo = (nomCheminVideo + "/" + nomFichierVideo);
    cout << "Chemin du nouveau dossier Video : " << nouveauDossierVideo << endl;
    //Creation du nouveau dossier
    Dossier::creerDossier(nouveauDossierVideo);
    Dossier::creerDossier(nouveauDossier + "/PNG");
    //Lecture de la vidéo
    cv::VideoCapture inputVideo(fichier.toStdString().c_str());
    taillevideo2 = 1;
    //Lecture de la video trame par trame
    while(inputVideo.isOpened())
    {
        Mat frame;
        //Lecture de la nouvelle trame de la video
        bool bSuccess = inputVideo.read(frame);
        if (!bSuccess)
        {
            cout << "Fin de la lecture de la vidéo" << endl;
            break;
        }
        // Sauvegarde de la trame dans un fichieouton_ouvrirVideo->setFixedSize(150,30);r
        imwrite(cv::format((nouveauDossierVideo + "/frame%d.tif").c_str(),taillevideo2).c_str(), frame);
        imwrite(cv::format((nouveauDossierVideo + "/PNG/frame%d.png").c_str(),taillevideo2).c_str(), frame);
        cout<<"a5"<<endl;  cout<<"Z2"<<endl;
        //Sans succes, sortir de la boucle
        taillevideo2++;
    }
    taillevideo2--;
    Mat img = imread(cv::format((nouveauDossierVideo + "/" + traitement + "/frame%d.tif").c_str(), taillevideo2).c_str(), CV_LOAD_IMAGE_COLOR);
    height_video2 = img.rows;
    if(taillevideo2 < taillevideo + 1){
        for(int z = taillevideo2 ; z < taillevideo + 1 ; z++){
            imwrite(cv::format((nouveauDossierVideo + "/frame%d.tif").c_str(),z).c_str(), img);
            imwrite(cv::format((nouveauDossierVideo + "/PNG/frame%d.png").c_str(),z).c_str(), img);
        }
    }
    //Lecture de la premiere trame enregistree dans le dossier
    dWidth = img.cols;
    dHeight = img.rows;
    cout << "Taille de la fenetre = " << dWidth << "x" << dHeight << endl;
    cout << "Taille de la video : " << taillevideo2 << endl;
    label_videoInpainting->setPixmap(QPixmap((nouveauDossierVideo + "/frame1.tif").c_str()));
    label_videoInitiale->setGeometry(30, 70,100,100);
}

//Slot du changement de la position du slider
void MaFenetre::sliderMovedslot(int position){
   positionSlider = position;
    //Affichage de l'image correspondant a la valeur du slider de la vidéo originale
    //modifié
    //   label_videoInitiale->setPixmap(QPixmap(cv::format((nouveauDossier + "/frame%d.tif").c_str(), position).c_str()));
   label_videoInitiale->setPixmap(QPixmap(cv::format((nouveauDossier + "/frame%d.tif").c_str(), position).c_str()));
    //Affichage de l'image correspondant a la valeur du slider de la vidéo traitée
   if(w>768&&h>576){
   label_videoTraitee->setPixmap(QPixmap(cv::format((nouveauDossier + "/" + imaFolder[positionSwitch] + "/resize/frame%d.tif").c_str(),position).c_str()));
   }else{
   label_videoTraitee->setPixmap(QPixmap(cv::format((nouveauDossier + "/" + imaFolder[positionSwitch] + "/frame%d.tif").c_str(),position).c_str()));
   }
    label_videoInpainting->setPixmap(QPixmap(cv::format((nouveauDossierVideo + "/" + "/frame%d.tif").c_str(),position).c_str()));
    if(((positionSwitch == 19) || (positionSwitch == 20) || (positionSwitch == 25)  || (positionSwitch == 21) || (positionSwitch == 22)) && (positionSlider == taillevideo)){
    label_videoInitiale->setPixmap(QPixmap(cv::format((nouveauDossier + "/frame%d.tif").c_str(), position-1).c_str()));
    if(w>768&&h>576){
    label_videoTraitee->setPixmap(QPixmap(cv::format((nouveauDossier + "/" + imaFolder[positionSwitch] + "/resize/frame%d.tif").c_str(),position-1).c_str()));
    }else{
    label_videoTraitee->setPixmap(QPixmap(cv::format((nouveauDossier + "/" + imaFolder[positionSwitch] + "/frame%d.tif").c_str(),position-1).c_str()));
    }
    }
}

void MaFenetre::enregistrer(){
    //TODO
    //QString fichier = QFileDialog::getSave  cout<<"Z1"<<endl;FileName(this, "Enregistrer un fichier", QString(), "Videos (*.avi *.mp4)");
    Size frameSize(dWidth, dHeight);
    //HEI ENNEREN FIR INPAINTING DILATATION
    Video *v = new Video();
    v->creerVideo(nomChemin, nomFichier, taillevideo, nouveauDossier, imaFolder[positionSwitch], frameSize);
    delete v;
    cout << "Video enregistree" << endl;
}

//Slot qui permet de donner la position du slider a la variable du switch

void MaFenetre::afficher(int position){
    positionSwitch = position;
}
void MaFenetre::afficher1(int position1){
    positionSwitch1 = position1;
}
void MaFenetre::afficher2(int position2){
    positionSwitch2 = position2;
}
void MaFenetre::afficher3(int position3){
    positionSwitch3 = position3;
}
void MaFenetre::afficher4(int position4){
    positionSwitch4 = position4;
}
void MaFenetre::afficher5(int position5){
    positionSwitch5 = position5;
}
//Slot qui permet de lancer le traitement de la video

void MaFenetre::lancer(){



//    for(int u=3; u<4;u++){
//        for(int x=12; x<14;x++){
//            for(int z=0; z<2;z++){

cout<<sizeof(listr5)<<endl;
cout<<positionSwitch5<<endl;

    Mat Image1 =imread(nouveauDossier+ "/frame1.tif", CV_LOAD_IMAGE_COLOR);
    dWidth = Image1.cols, dHeight = Image1.rows;
    w = Image1.cols; h = Image1.rows;
    premiere_fois=true;
    slider->setValue(1);
    Traitement *trait = new Traitement();
    int positiona=1;
    int y=0;
    int ind=0;
    QFileInfo photo(cv::format((nouveauDossier+"/"+ imaFolder[positionSwitch]+"/frame%d.tif").c_str(),ind).c_str());
    if(photo.exists()==0){
        while(true){
            Mat Image=imread(cv::format((nouveauDossier+ "/frame%d.tif").c_str(),ind+1).c_str(), CV_LOAD_IMAGE_COLOR);
            int positionss=listr[positionSwitch2/*+u*/];
            int positionwinsize=listr2[positionSwitch4/*+x*/];
            int position_K=listr5[positionSwitch5/*+z*/];
            if(Image.data == NULL){
                trait->run(positionwinsize,positionss,positiona,allImages,premiere_fois,positionSwitch,taillevideo, nouveauDossier, positionSlider, label_videoInitiale, points, this,imaFolder,points_image, dirPathImage, *label_image_inpainting, nouveauDossierVideo, points_video2, label_videoInpainting,position_K);
                allImages.clear();
                break;
            }
            allImages.push_back(Image);
            if(ind==y+lis[positionSwitch1]){
                trait->run(positionwinsize,positionss,positiona,allImages,premiere_fois,positionSwitch, taillevideo, nouveauDossier, positionSlider, label_videoInitiale, points, this,imaFolder,points_image, dirPathImage, *label_image_inpainting, nouveauDossierVideo, points_video2, label_videoInpainting,position_K);
                allImages.clear();
                positiona=positiona +lis[positionSwitch1];
                ind=ind-listr1[positionSwitch3];
                y=y+lis[positionSwitch1];
                if(positionSwitch==14){
                    break;
                }
            }
            ind++;
        }
    }
//            }
//        }
//    }
    label_videoInitiale->setPixmap(QPixmap(cv::format((nouveauDossier + "/frame1.tif").c_str()).c_str()));


    if((positionSwitch==28)){

    if(w>768 && h>576){
        label_K_means_nD_t->setPixmap(QPixmap(cv::format((nouveauDossier + "/" + imaFolder[positionSwitch] + "/Kmeans2d/resize/frame0.tif").c_str()).c_str()));
        label_K_means_nD_t->repaint();
    }else{
        label_K_means_nD_t->setPixmap(QPixmap(cv::format((nouveauDossier + "/" + imaFolder[positionSwitch] + "/Kmeans2d/frame0.tif").c_str()).c_str()));
        label_K_means_nD_t->repaint();
    }

    }
    if((positionSwitch==25)){

    if(w>768 && h>576){
        label_K_means_nD_t->setPixmap(QPixmap(cv::format((nouveauDossier + "/" + imaFolder[positionSwitch] + "/Kmeans2d/resize/frame0.tif").c_str()).c_str()));
        label_K_means_nD_t->repaint();
        label_flot_optique->setPixmap(QPixmap(cv::format((nouveauDossier + "/" + imaFolder[positionSwitch] + "/FlotOptique/resize/frame1.tif").c_str()).c_str()));
        label_flot_optique->repaint();
    }else{
        label_K_means_nD_t->setPixmap(QPixmap(cv::format((nouveauDossier + "/" + imaFolder[positionSwitch] + "/Kmeans2d/frame0.tif").c_str()).c_str()));
        label_K_means_nD_t->repaint();
        label_flot_optique->setPixmap(QPixmap(cv::format((nouveauDossier + "/" + imaFolder[positionSwitch] + "/FlotOptique/frame1.tif").c_str()).c_str()));
        label_flot_optique->repaint();
    }

    }
        if(w>768 && h>576){
            label_videoTraitee->setPixmap(QPixmap(cv::format((nouveauDossier + "/" + imaFolder[positionSwitch] + "/resize/frame1.tif").c_str()).c_str()));
            label_videoTraitee->repaint();
        }else{
            label_videoTraitee->setPixmap(QPixmap(cv::format((nouveauDossier + "/" + imaFolder[positionSwitch] + "/frame1.tif").c_str()).c_str()));
            label_videoTraitee->repaint();
        }



    std::cout <<  nouveauDossier << "/" << imaFolder[positionSwitch] << std::endl;
    cout << "Fin du traitement" << endl;
}


//#######################################################################################################################
//Slot qui permet de jouer la video dans l'application
void MaFenetre::play(){
    for(int i = 1 ; i < taillevideo+1; i++){
        slider->setValue(i);
        label_videoInitiale->setPixmap(QPixmap(cv::format((nouveauDossier+"/frame%d.tif").c_str(), i).c_str()));
        if(w>768 && h>576){
            label_videoTraitee->setPixmap(QPixmap(cv::format((nouveauDossier + "/" + imaFolder[positionSwitch] + "/resize/frame%d.tif").c_str(), i).c_str()));
        }else{
            label_videoTraitee->setPixmap(QPixmap(cv::format((nouveauDossier + "/" + imaFolder[positionSwitch] + "/frame%d.tif").c_str(), i).c_str()));
        }

        if(positionSwitch==25||positionSwitch==25){
      label_K_means_nD_t->setPixmap(QPixmap(cv::format((nouveauDossier+"/frame%d.tif").c_str(), i).c_str()));
        if(w>768 && h>576){
            label_K_means_nD_t->setPixmap(QPixmap(cv::format((nouveauDossier + "/" + imaFolder[positionSwitch] + "/Kmeans2d/resize/frame%d.tif").c_str(), i-1).c_str()));

        }else{
              label_K_means_nD_t->setPixmap(QPixmap(cv::format((nouveauDossier + "/" + imaFolder[positionSwitch] + "/Kmeans2d/frame%d.tif").c_str(), i-1).c_str()));

        }
        }
        if(positionSwitch==25){

        if(w>768 && h>576){
         label_flot_optique->setPixmap(QPixmap(cv::format((nouveauDossier + "/" + imaFolder[positionSwitch] + "/FlotOptique/resize/frame%d.tif").c_str(), i).c_str()));

        }else{
              label_flot_optique->setPixmap(QPixmap(cv::format((nouveauDossier + "/" + imaFolder[positionSwitch] + "/FlotOptique/frame%d.tif").c_str(), i).c_str()));

        }
        }

        
        if(((positionSwitch == 19) || (positionSwitch == 20) || (positionSwitch == 21) || (positionSwitch == 22)) && ((positionSlider == taillevideo))){
             label_videoInitiale->setPixmap(QPixmap(cv::format((nouveauDossier+"/frame%d.tif").c_str(), i-1).c_str()));
            if(w>768 && h>576){
                label_videoTraitee->setPixmap(QPixmap(cv::format((nouveauDossier + "/" + imaFolder[positionSwitch] + "/resize/frame%d.tif").c_str(), i-1).c_str()));
            }else{
                label_videoTraitee->setPixmap(QPixmap(cv::format((nouveauDossier + "/" + imaFolder[positionSwitch] + "/frame%d.tif").c_str(), i-1).c_str()));
            }
        }


        if(waitKey(30) == 27){
            cout << "L'utilisateur a stoppé la lecture de la vidéo" << endl;
            break;
        }
        //attendre 0.03 secondes avant d'afficher la trame suivante
        wait(0.03);
     }
}

//calcul du temps pour afficher les trames l'une apres l'autre
void MaFenetre::wait(float seconds){
    clock_t endwait;
    endwait = clock() + seconds * CLOCKS_PER_SEC;
    while (clock() < endwait) {}
}

//Permet d'obtenir les points pour calculer le rectangle pour GrabCut
void MaFenetre::mousePressEvent(QMouseEvent *event){
    point = event->pos();
    int difference_video1 = 0;
    int difference_video2 = 0;
    int difference_image = 0;
    cout<<"difference_video2 "<<difference_video2<<endl;
    cout<<"height_video1 "<<height_video1<<endl;
    cout<<"height_image "<<height_image<<endl;
    cout<<"height_video2 "<<height_video2<<endl;
    if((height_video1 > height_video2) && (height_video1 > height_image)){
        difference_video2 = (height_video1 - height_video2)/2;
        cout<<"difference_video2"<<difference_video2<<endl;
        difference_image = (height_video1 - height_image)/2;
    }else if(height_video2 > height_image){
        difference_video1 = (height_video2 - height_video1)/2;
        difference_image = (height_video2 - height_image)/2;
    }else{
        difference_video1 = (height_image - height_video1)/2;
        difference_video2 = (height_image - height_video2)/2;
    }

    //    if(height_difference > 0){
    //        difference_droite = height_difference;
    //    }
    //    else {
    //        difference_gauche = (-height_difference);
    //    }

    //point d'une trame
    if((point.x() >= label_videoInitiale->geometry().x()) && (point.x() <= (label_videoInitiale->geometry().x() + label_videoInitiale->width())) && point.y() >= label_videoInitiale->geometry().y() && (point.y() <= (label_videoInitiale->geometry().y() + label_videoInitiale->height()))){
        //    cout << "Image GrabCut" <<endl;
        //    cout << "Point MouseEvent X avant outon_ouvrirVideo->setFixedSize(150,30);calcul : " << point.x() << endl;
        //    cout << "Point MouseEvent Y avant calcul : " << point.y() << endl;
        point.setX(point.x() - label_videoInitiale->geometry().x());
        point.setY(point.y() - label_videoInitiale->geometry().y() - difference_video1);
        points.push_back(point);
        if(points.size() == 1){
            QPoint p = points.back();
            String point1x = cv::format("%d",p.x()).c_str();
            String point1y = cv::format("%d",p.y()).c_str();
            //            cout << point1x<< endl;
            String chaine1 = "Point(" + point1x +"," +point1y + ")";
            QString qstr = QString::fromStdString(chaine1);
            label_positionPremierPoint->setText(qstr);
            label_positionSecondPoint->setText("Selectionner un autre point");
        }else{
            QPoint p = points.back();
            ////        Point p( 3,1);
            String point1x = cv::format("%d",p.x()).c_str();
            String point1y = cv::format("%d",p.y()).c_str();
            //            cout << point1x<< endl;
            String chaine1 = "Point(" + point1x +"," +point1y + ")";
            QString qstr = QString::fromStdString(chaine1);
            label_positionPremierPoint->setText(qstr);

            QPoint po = points.at(points.size()-2);
            String point2x = cv::format("%d",po.x()).c_str();
            String point2y = cv::format("%d",po.y()).c_str();
            //            cout << point2x<< endl;
            String chaine2 = "Point(" + point2x +"," +point2y + ")";
            QString qstre = QString::fromStdString(chaine2);
            label_positionSecondPoint->setText(qstre);
        }
        cout << "----------------------------------------------------------------------" << endl;
    }
    //point de l'image pour inpainting telea
    else  if((point.x() >= label_image_inpainting->geometry().x()) && (point.x() <= (label_image_inpainting->geometry().x() + label_image_inpainting->width())) && point.y() >= label_image_inpainting->geometry().y() && (point.y() <= (label_image_inpainting->geometry().y() + label_image_inpainting->height()))){
        cout << "Image Inpainting" <<endl;
        //    cout << "Point MouseEvent X avant calcul : " << point.x() << endl;
        //    cout << "Point MouseEvent Y avant calcul : " << point.y() << endl;
        point.setX(point.x() - label_image_inpainting->geometry().x());
        point.setY(point.y() - label_image_inpainting->geometry().y() - difference_image);
        points_image.push_back(point);
        cout << "----------------------------------------------------------------------" << endl;
        //affichage des coordonnees des points de limage
        if(points_image.size() == 1){
            cout << "marche" <<endl;
            QPoint pi = points_image.back();
            String point1xi = cv::format("%d",pi.x()).c_str();
            String point1yi = cv::format("%d",pi.y()).c_str();
            //                cout << point1xi<< endl;
            String chaine1 = "Point(" + point1xi +"," +point1yi + ")";
            QString qstr = QString::fromStdString(chaine1);
            label_positionPremierPointImage->setText(qstr);
            label_positionSecondPointImage->setText("Selectionner un autre point");
        }else{
            QPoint pi = points_image.back();
            String point1xi = cv::format("%d",pi.x()).c_str();
            String point1yi = cv::format("%d",pi.y()).c_str();
            //                cout << point1xi<< endl;
            String chaine1 = "Point(" + point1xi +"," +point1yi + ")";
            QString qstr = QString::fromStdString(chaine1);
            label_positionPremierPointImage->setText(qstr);
            QPoint poi = points_image.at(points_image.size()-2);
            String point2xi = cv::format("%d",poi.x()).c_str();
            String point2yi = cv::format("%d",poi.y()).c_str();
            //                cout << point2xi<< endl;
            String chaine2 = "Point(" + point2xi +"," +point2yi + ")";
            QString qstre = QString::fromStdString(chaine2);
            label_positionSecondPointImage->setText(qstre);
        }
    } else  if((point.x() >= label_videoInpainting->geometry().x()) && (point.x() <= (label_videoInpainting->geometry().x() + label_videoInpainting->width())) && point.y() >= label_videoInpainting->geometry().y() && (point.y() <= (label_videoInpainting->geometry().y() + label_videoInpainting->height())))
    {
        cout << "video 2"  <<endl;
        point.setX(point.x() - label_videoInpainting->geometry().x());
        point.setY(point.y() - label_videoInpainting->geometry().y() - difference_video2);
        points_video2.push_back(point);

        if(points_video2.size() == 1){
            QPoint p2 = points_video2.back();
            String point1x2 = cv::format("%d",p2.x()).c_str();
            String point1y2 = cv::format("%d",p2.y()).c_str();
            //            cout << point1x<< endl;
            String chaine1 = "Point(" + point1x2 +"," +point1y2 + ")";
            QString qstr = QString::fromStdString(chaine1);
            label_positionPremierPointVideo->setText(qstr);
            label_positionSecondPointVideo->setText("Selectionner un autre point");
        }else{
            QPoint p2 = points_video2.back();
            ////      Point p( 3,1);
            String point1x = cv::format("%d",p2.x()).c_str();
            String point1y = cv::format("%d",p2.y()).c_str();
            //            cout << point1x<< endl;
            String chaine1 = "Point(" + point1x +"," +point1y + ")";
            QString qstrr = QString::fromStdString(chaine1);
            label_positionPremierPointVideo->setText(qstrr);
                      QPoint po2 = points_video2.at(points_video2.size()-2);
                      String point2x2 = cv::format("%d",po2.x()).c_str();
                      String point2y2 = cv::format("%d",po2.y()).c_str();
                      //            cout << point2x<< endl;
                      String chaine2v = "Point(" + point2x2 +"," +point2y2 + ")";
                      QString qstrer = QString::fromStdString(chaine2v);
                      label_positionSecondPointVideo->setText(qstrer);
        }
    }
}

void MaFenetre::ouvrirImage(){
    //Ouverture de la boite de selection de video
    QString fichier = QFileDialog::getOpenFileName(this, "Ouvrir une image", QString(), "Images (*.jpg *.png *.tif)");
    //Obtention le nom du chemin et du fichier avec l'extension
    QFileInfo fileInfo(fichier);
    // Path vers l'image
    dirPathImage = fileInfo.absoluteFilePath();
    height_image = (QPixmap(dirPathImage).height());
    Mat frame;
    int w, h ;
    h = frame.rows;
    w = frame.cols;
    //    height_image = img.rows;
    label_image_inpainting->setPixmap(QPixmap(dirPathImage));
    label_image_inpainting->setGeometry(11, 11, w, h);
}
