
#ifndef H_FILE
#define H_FILE
typedef struct informationsRoute informationsRoute;
struct informationsRoute
{

int numeroVehicule;
int positionFile;
float tempsPassage;
float dateDebutPassage;
float dateFinPassage;
int compt_file;
float dateArrivee;
float frequenceApparition;
};

typedef struct Resultats Resultats;
struct Resultats
{
int nombreMoyen1;
int nombreMoyen2;
int tempsMoyenAttente1;
int tempsMoyenAttente2;
int tailleMaximale1;
int tailleMaximale2;
int tailleMinimale1;
int tailleMinimale2;
int debitMoyen1;
int debitMoyen2;
int dbitLittle1;
int dbitLittle2;
};



typedef struct Vehicule Vehicule;
struct Vehicule
{
	int numeroVehicule;/*identifie le vehicule sur la voie;*/
	float dateArrivee;/*date d'entrée du véhicule sur la route;*/
	float dateFinPassage;/*date d'arrivée du véhicule au feu rouge (le véhicule est en tête de file);*/
	float tempsPassage;
	float dateDebutPassage;

        int PositionFile;





	Vehicule *suivant;
		
};
	
typedef struct File File;
struct File
{
   int nombreVehicule;
   int nombreDefile;
    Vehicule *premier;
};


void enfiler(File *file, int numero,float heure);
int defiler(File *file);
File *initialisation();




#endif
