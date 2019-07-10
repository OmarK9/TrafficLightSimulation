#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include "file.h"
#include "projet.h"
#include "constantes.h"



float Expo(float lambda){
	return (-1* log(1-( rand()/(float)RAND_MAX )))/lambda;
	
}





float lambda(float temps){/*On règle la fréquence d'apparition des voitures en fonction des horaires et des affluences*/
	if(temps>=7.5*3600.0 && temps<=9*3600.0)
		return 0.1;/*2 voitures chaque 10 secondes*/
	if(temps>=12*3600.0 && temps<=14*3600.0)
		return 0.1;
	if(temps>=17*3600.0 && temps<=19*3600.0)
		return 0.1;
	if((temps>9*3600.0&& temps<12*3600.0 )||(temps>14*3600.0 && temps<17*3600.0)||temps>19*3600.0)
		return 0.05;
return 0.0;
}




File *simulationTraffic(float heure,informationsRoute *informationsRoute){/*Cette fonction s'occupe de charger les routes 1 et 2 des véhicules*/

	int vehicule=1;

	File *Route;

	Route=initialisation();/*initialise la file Route avec 1 véhicule*/
	float T;/* T est l'intervalle entre l'arrivée de 2 voitures successives*/


	float FinHeure=finHeure*3600.0;/*on convertit les heures en secondes*/


	while( Route->nombreVehicule<NBR_MAX && heure<FinHeure){ /*Tant qu'on a pas atteint le nombre maximal de vehicules et tant que la simulation n'est pas finie*/	


    	float lbd;/*=lambda*/

		lbd=lambda(heure);

		T=(Expo(lbd));
		enfiler(Route,vehicule,heure);/*On charge le vehicule dans la route*/
		
		informationsRoute[vehicule].numeroVehicule=vehicule;
		informationsRoute[vehicule].positionFile=vehicule;
		informationsRoute[vehicule].dateArrivee=heure;
		informationsRoute[vehicule].frequenceApparition=lbd;
	/*On met dans la structure informationsRoute les informations relative au vehicule*/
		heure=heure+T;
		vehicule++;





}

	return Route;
}



















