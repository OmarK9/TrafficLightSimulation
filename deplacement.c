#include <stdlib.h>
#include <stdio.h>
#include "constantes.h"
#include "file.h"
#include "deplacement.h"



/*Servent à compter combien de fois les trois feus se sont allumés*/
/*alpha coeffiscient déterminant le temps de passage des voitures selon la loi linéaire temps de passage=alpha*position*/

float  deplacement(File *file,int *EtatFeu ,float date,informationsRoute *info){

	if (date<=finHeure*3600.0){/*On verifie que la simulation n'est pas finie*/
		if(EtatFeu[2]==1){/*Si le feu est rouge*/

			occRouge++;		

/*On fait rien car le feu est rouge*/
	return 0;}}



if (date<=finHeure*3600.0){
	int position=1;
	float compteur=0.0;
	if (EtatFeu[0]==1){/*si le feu est vert */
		occVert++;		
 		while (compteur<EtatFeu[3] && file->nombreVehicule!=0){
        


			if (file->premier != NULL) /* La file n'est pas vide */
    {
        /* On se positionne à la fin de la file */
       				 Vehicule *VehiculeActuel = file->premier;/*On considere le vehicule en tête de file*/

			
				 if( info[VehiculeActuel->numeroVehicule].dateArrivee+compteur<=date+EtatFeu[3] ){/*Si le véhicule est  capable de traverser  avant que le feu  rouge ne s'allume;*/


							if( info[VehiculeActuel->numeroVehicule].dateArrivee>=date){/*Si la date d'arrivée du véhicule est supérieure à la date "actuelle"*/

								info[VehiculeActuel->numeroVehicule].dateDebutPassage=info[VehiculeActuel->numeroVehicule].dateArrivee;/*Alors le vehicule peut passer*/
					

								info[VehiculeActuel->numeroVehicule].dateFinPassage=info[VehiculeActuel->numeroVehicule].dateDebutPassage+compteur;
}
							else{/*sinon..*/
								info[VehiculeActuel->numeroVehicule].dateDebutPassage=date;/*Le vehicule le vehicule commencera son passage quand la date sera mise à jour*/	
					

								info[VehiculeActuel->numeroVehicule].dateFinPassage=info[VehiculeActuel->numeroVehicule].dateDebutPassage+compteur;
}
				defiler(file);  
				compteur=compteur+(alpha)*position; /*Le compteur est incrémenté du temps de passage de chaque vehicule*/
				position++;}





						


				else
						return 0.0;

}

}

}		

}
	
  
	 
if (date<=finHeure*3600.0){
	int position=1;
	float compteur=0.0;
	if (EtatFeu[1]==1){/*si le feu est  orange*/
		occOrange++;		
 		while (compteur<EtatFeu[3] && file->nombreVehicule!=0){
        


			if (file->premier != NULL){ /* La file n'est pas vide */
    
        /* On se positionne à la fin de la file */
       				 Vehicule *VehiculeActuel = file->premier;	

				 if( info[VehiculeActuel->numeroVehicule].dateArrivee+compteur<=date+EtatFeu[4] ){/*est ce qu'il serait capable de traverse Vert avant qu'il tourne rouge;*/

							if( info[VehiculeActuel->numeroVehicule].dateArrivee>=date+compteur){
									info[VehiculeActuel->numeroVehicule].dateDebutPassage=info[VehiculeActuel->numeroVehicule].dateArrivee;		
					

									info[VehiculeActuel->numeroVehicule].dateFinPassage=info[VehiculeActuel->numeroVehicule].dateDebutPassage+compteur;
}

  
							else{
									info[VehiculeActuel->numeroVehicule].dateDebutPassage=date;	
					

									info[VehiculeActuel->numeroVehicule].dateFinPassage=info[VehiculeActuel->numeroVehicule].dateDebutPassage+compteur;
		}



			
		



							defiler(file);  
							compteur=compteur+(alpha-0.7)*position; /*Le voiture passera plus rapidement que si le feu est vert*/
							position++;}


				else

						return 0.0;


		

}

    


return compteur;
}



}

}





	

return 0;
}






