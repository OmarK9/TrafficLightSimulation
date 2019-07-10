
#include <stdlib.h>
#include <stdio.h>

#include "file.h"

void enfiler(File *file, int numero,float heure)
{

    Vehicule *nouveau = malloc(sizeof(*nouveau));
    if (file == NULL || nouveau == NULL)
    {
        exit(EXIT_FAILURE);
    }



    nouveau->numeroVehicule = numero;
	




    nouveau->suivant = NULL;

    if (file->premier != NULL) 
    {

        Vehicule *VehiculeActuel = file->premier;
        while (VehiculeActuel->suivant != NULL)
        {
            VehiculeActuel = VehiculeActuel->suivant;
        }
        VehiculeActuel->suivant = nouveau;

    }
    else 
    {
        file->premier = nouveau;

    }

    	(file->nombreVehicule)++;
}

int defiler(File *file)
{
    if (file == NULL)
    {
        exit(EXIT_FAILURE);
    }

    int numeroDefile = 1;

    if (file->premier != NULL)
    {
        Vehicule *vehiculeDefile = file->premier;

        numeroDefile = vehiculeDefile->numeroVehicule;
        file->premier = vehiculeDefile->suivant;
        free(vehiculeDefile);

	file->nombreDefile++;	

    }
		file->nombreVehicule--;




    
   
    return numeroDefile;
}
File *initialisation()
{

    File *file = malloc(sizeof(*file));
    Vehicule *vehicule = malloc(sizeof(*vehicule));

    if (file == NULL || vehicule== NULL)
    {
        exit(EXIT_FAILURE);
    }


    vehicule->numeroVehicule=0;

    
    vehicule->suivant = NULL;
    file->premier = vehicule;
	file->nombreVehicule=1;


    return file;
} 



