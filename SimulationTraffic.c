
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include "file.h"
#include <stdbool.h>
#include "deplacement.h"
#include "SimulationTraffic.h"
#include "constantes.h"


int AfficheHeure(int s){/*Permet d'afficher l'heure en format H M S*/
	int heure   = (s / 3600)% 24;
  	int minute  = (s / 60 )% 60;
  	int seconde = s % 60;
 
	printf("%dh %dm %ds \n",heure,minute,seconde);
 	return 1;
}	


int Heure(int s){/*extrait le nombre d'heure */

	int heure=(s / 3600)% 24;
	return heure;}

int Minute(int s){/*extrait le nombre de minutes */
	int minute= (s / 60 )% 60;
	return minute;}

int Seconde(int s){/*extrait le nombre de secondes */
	int seconde=s % 60;
	return seconde;}


int *Feu(void){/*Cette fonction permet de règler la temporisation des feux vert , rouge et orange*/
	int *EtatF1=(int *)malloc(sizeof(int)*6);
	EtatF1[3]=40;/*Tvert=40s*/
	EtatF1[4]=6;/*Torange=6s*/
	EtatF1[5]=EtatF1[3]+EtatF1[4]+1;/*Pour eviter la collision de deux voitures */
	

	return EtatF1;}


char *Etat1(int Switch,float date,int *Feu){/*Cette fonction indique l'état du feu tricolore à une date d*/
	date=date-debutHeure*3600.0;/*On prend le temps écoulé depuis le debut de la simulation*/
	int Date=floor(date);/*On prend la valeur entiere car c'est plus facile de manier un entier*/
	int cycle=floor(Feu[3]+Feu[5]+Feu[4]);/*Cycle=Tr+Tv+To*/

	char *feu=(char*)malloc(sizeof(float)*3);/*tableau de 3 caracteres */
	if (Switch==1){/*Switch==1 designe la route 1*/

		int reste=Date%cycle;
		if(   reste<Feu[5])

			strcpy(feu,"(R)");

		if(reste<Feu[5]+Feu[3] && reste>=Feu[5])
			strcpy(feu,"(V)");
		if(reste<Feu[5]+Feu[3]+Feu[4] && reste>=Feu[5]+Feu[3])		
			strcpy(feu,"(O)");

	}		
	else{
		

		int reste=Date%cycle;
		if( reste<Feu[3])
			strcpy(feu,"(V)");
		if(reste<Feu[3]+Feu[4] && reste>=Feu[3])
			strcpy(feu,"(O)");
		if(reste<Feu[5]+Feu[3]+Feu[4] && reste>=Feu[4]+Feu[3])		
			strcpy(feu,"(R)");
	}

	return feu;

  }



	
int *Etat(int Switch,float date,int *Feu){/*Cette fonction renvoie un tableau de 6 entiers decrivant l'etat du feu tricolore à un instant t*/
	date=date-debutHeure*3600.0;
	int Date=floor(date);

	int cycle=floor(Feu[3]+Feu[5]+Feu[4]);
			int reste=Date%cycle;
	if (Switch==1){/*S'il s'agit de la route1*/
		

		if( reste<Feu[5]){
			Feu[0]=0;
			Feu[1]=0;
			Feu[2]=1;}/*dans ce cas on met le feu au rouge*/

		if(reste<Feu[5]+Feu[3] && reste>=Feu[5])
			{
			Feu[0]=1;
			Feu[1]=0;
			Feu[2]=0;}/*le feu est au vert*/

		if(reste<Feu[5]+Feu[3]+Feu[4] && reste>=Feu[5]+Feu[3])	{	
			Feu[0]=0;
			Feu[1]=1;/*le feu est orange*/
			Feu[2]=0;}

	}

	else{/*S'il s'agit de la route 2*/
		

		int reste=Date%cycle;
		if( reste<Feu[3]){
			Feu[0]=1;
			Feu[1]=0;
			Feu[2]=0;}/*le feu est vert*/
		if(reste<Feu[3]+Feu[4] && reste>=Feu[3]){
			Feu[0]=0;
			Feu[1]=1;
			Feu[2]=0;}/*le feu est orange*/

		if(reste<Feu[5]+Feu[3]+Feu[4] && reste>=Feu[3]+Feu[4]){
			Feu[0]=0;
			Feu[1]=0;
			Feu[2]=1;}	/*le feu est rouge*/	
			
	}

	return Feu;




}







int  gestion1(File*file,float *date,bool Switch,informationsRoute *info){/*Cette fonction gère la synchronisation des feus pour la route 1, elle prend en parametre l'adresse d'un tableau comportant un entier (date[0]) qui va etre modifie en mémoire pour etre utilise par la fonction deplacement la fonction GestionTraffic et  la fonction Etat*/
	int *EtatF2=Feu();/*Ce tableau contient la temporisation des différents feu*/
	int *EtatF1=(int *)malloc(sizeof(int)*6);/*Contient la temporisation +etat des feu*/

	if(date[0]<finHeure*3600.0){
		EtatF1=Etat(Switch,date[0],EtatF2);
		deplacement(file,EtatF1,date[0],info);}
	if(EtatF1[0]==1 )
		date[0]=date[0]+EtatF1[3];
	if(EtatF1[1]==1  )
		date[0]=date[0]+EtatF1[4];
	if(EtatF1[2]==1)
		date[0]=date[0]+EtatF1[5];

	/*On a mis a jour la date en rajoutant le temps correspondant à la durée de chaque feu*/
	

	return 0;}


int  gestion2(File*file,float *date,bool Switch,informationsRoute *info){/*Meme fonction que gestion1 , mais cette fois pour la route2*/
	
	int *EtatF2=Feu();
	int *EtatF1=(int *)malloc(sizeof(int)*6);
	if(date[0]<finHeure*3600.0){
		EtatF1=Etat(Switch,date[0],EtatF2);
		deplacement(file,EtatF1,date[0],info);}
	if(EtatF1[0]==1)
		date[0]=date[0]+EtatF1[3];
	if(EtatF1[1]==1)
		date[0]=date[0]+EtatF1[4];
	if(EtatF1[2]==1)
		date[0]=date[0]+EtatF1[5];


	

	return 0;}


int GestionTraffic(File* route1,File *route2,informationsRoute *info,informationsRoute *info2,int T){/*Cette fonction lance la simulation et gère la file d'attente de chaque route*/




	bool Rouge=true;/*A t=0, le feu est rouge chez route 1*/
	bool Vert=false;/*A t=0, le feu est vert chez route2*/
	float *Date1=(float *)malloc(sizeof(float)*1);
	float *Date2=(float *)malloc(sizeof(float)*1);
	Date1[0]=debutHeure*3600.0;
	Date2[0]=debutHeure*3600.0;
	while(Date1[0]<finHeure*3600.0 ){
 

		gestion1(route1,Date1,Rouge,info);
		}
	while(Date2[0]<finHeure*3600.0){
		gestion2(route2,Date2,Vert,info2);


}







	int j=0;//variable globale

/*Dans cette partie on va gérer la file d'attente de chaque route */
	while(j<NBR_MAX){
		if (info[j+1].dateArrivee>=info[j].dateFinPassage){/*Si le véhicule qui suit arrive apres que le véhicule actuel a fini de passé*/

					info[j+1].dateDebutPassage=info[j+1].dateArrivee;}/*alors le véhicule suivant commence son passage immédiatement après être arrivé*/
		else{/*sinon*/
				 	info[j+1].dateDebutPassage=info[j].dateFinPassage;/*Il attend que le véhicule précédent finit de passer*/


}
		info[j].compt_file=0;/*là on va mesurer la taille de la file*/
		int p;
		for ( p=0;p<j;p++) /*taille file d'attente pour le client i  = Nombre de clients précédents dont le temps de fin > temps d'arrivÃ©e du client i*/
		{
			if ((info[j].dateArrivee)<(info[p].dateFinPassage)){
				info[j].compt_file++;
			}

	}
	j++;
}

	int k=0;
/*Là on fait la même chose pour la route2*/
	while(k<NBR_MAX){
		if (info2[k+1].dateArrivee>=info2[k].dateFinPassage){

				info2[k+1].dateDebutPassage=info2[k+1].dateArrivee;}
		else{
				info2[k+1].dateDebutPassage=info2[k].dateFinPassage;}



				info2[k].compt_file=0;
		int c;
		for (c=0;c<k;c++) /*taille file d'attente pour le client i  = Nombre de clients prÃ©cÃ©dents dont le temps de fin > temps d'arrivÃ©e du client i*/
		{
				if ((info2[k].dateArrivee)<(info2[c].dateFinPassage)){
					info2[k].compt_file++;
			}

	}
	k++;
}


/*Ecriture du fichier stats.txt et files.txt*/
	FILE*fichier=NULL;
	fichier=fopen("stats.txt","w");
	if (fichier==NULL)
		printf("Erreur d'ouverture\n");
	else{
		fprintf(fichier,"\n\n\t\t\t\t\t\t\tTABLEAU DE BORD CARREFOUR:\n\n\n\nV:Vehicule\nDA: Date d'arrivée\nDFP:Date de fin de passage\nTS:Temps de service\nLF:Longueur file\n\n\n");
fprintf(fichier," V           DA            DFP             TS\t\t  V           DA           DFP           TS\t\t LF1     LF2\n\n\n\n");


		fprintf(fichier," Route1\t \t\t                               Route2\t \n\n " );           
		FILE*fichier2=NULL;
		fichier2=fopen("files.txt","w");
		if (fichier2==NULL)
			printf("Erreur d'ouverture du fichier2\n");
		else{



			int i=2;



			while(i<NBR_MAX && (info[i].dateFinPassage<=finHeure*3600.0 || info2[i].dateFinPassage<=finHeure*3600.0) && info[i].dateFinPassage!=0 &&  info2[i].dateFinPassage!=0  ){

	fprintf(fichier,"%d%s \t %dh %dm %ds \t  %dh %dm %ds  \t %dh %dm %ds  \t %d%s \t %dh %dm %ds\t  %dh %dm %ds  \t %dh %dm %ds  \t %d \t %d \n ",i-1,Etat1(1,info[i-1].dateArrivee,Feu()),Heure(info[i-1].dateArrivee),Minute(info[i-1].dateArrivee),Seconde(info[i-1].dateArrivee),Heure(info[i-1].dateFinPassage),Minute(info[i-1].dateFinPassage),Seconde(info[i-1].dateFinPassage),Heure(info[i-1].dateFinPassage-info[i-1].dateArrivee),Minute(info[i-1].dateFinPassage-info[i-1].dateArrivee),Seconde(info[i-1].dateFinPassage-info[i-1].dateArrivee),i-1,Etat1(0,info2[i-1].dateArrivee,Feu()),Heure(info2[i-1].dateArrivee),Minute(info2[i-1].dateArrivee),Seconde(info2[i-1].dateArrivee),Heure(info2[i-1].dateFinPassage),Minute(info2[i-1].dateFinPassage),Seconde(info2[i-1].dateFinPassage),Heure(info2[i-1].dateFinPassage-info2[i-1].dateArrivee),Minute(info2[i-1].dateFinPassage-info2[i-1].dateArrivee),Seconde(info2[i-1].dateFinPassage-info2[i-1].dateArrivee),info[i-1].compt_file,info2[i-1].compt_file);
fprintf(fichier2,"%f\t %f\t %d \t%d \t%f \t %f\n",info[i-1].dateFinPassage-info[i-1].dateArrivee,info2[i-1].dateFinPassage-info2[i-1].dateArrivee,info[i-1].compt_file,info2[i-1].compt_file,info[i-1].frequenceApparition,info2[i-1].frequenceApparition);
		

			i++;}}

		fclose(fichier2);
}
		fclose(fichier);
		




	return 1;
}

void test(void){
	float heure;
	for( heure=8*3600;heure<9*3600;heure++){
		printf("%s %s \n ",Etat1(1,heure, Feu()),Etat1(0,heure,Feu()));
		}
}
void lectureFichier(){/*Lecture du fichier files.txt qui permet de réaliser le fichier resultats.txt*/
	int totalFile1=0;
	int totalFile2=0;
	int tempsAttente1=0;/*sert a faire la somme des temps d'attentes pour ensuite faire la moyenne*/
	int tempsAttente2=0;
	int max1=0;/*sert a trouver la taille maximale de la liste d'attente,on l'initialise a 0*/
	int max2=0;
	int min1=NBR_MAX;/*sert a trouver la taille minimale de la liste d'attente,on l'initialise a 0*/
	int min2=NBR_MAX;
	int nbrfile1=0;
	int nbrfile2=0;
	float a;
	float b;
	float lbd1;
	float lbd2;
	float lambda1=0;/*sert a faire la somme des lambda pour ensuite en faire la moyenne (Loi de Little)*/
	float lambda2=0;

	FILE *fichier2=NULL;
	fichier2=fopen("files.txt","r");
	int tableau[2];
	if (fichier2==NULL)
		printf("Erreur d'ouverture du fichier\n");

	else{
		FILE*fichier3=NULL;
		fichier3=fopen("resultats.txt","w");


		while(!(feof(fichier2))){/*Tant qu'on a pas atteint la fin du fichier*/


			fscanf(fichier2,"%f %f %d %d  %f %f\n",&a,&b,&tableau[0],&tableau[1],&lbd1,&lbd2);

			totalFile1=totalFile1+tableau[0];
			tempsAttente1=tempsAttente1+a;
			tempsAttente2=tempsAttente2+b;
			lambda1=lambda1+lbd1;
			lambda2=lambda2+lbd2;
			nbrfile1++;
			nbrfile2++;
			if(max1<=tableau[0])
				max1=tableau[0];
			if(min1>=tableau[0])
				min1=tableau[0];
			totalFile2=totalFile2+tableau[1];
			if(max2<=tableau[1])
				max2=tableau[1];
			if(min2>=tableau[1])
				min2=tableau[1];


}
		if (fichier3==NULL)
			printf("Erreur d'ouverture du fichier3\n");
		else{
			int *feu=Feu();
			fprintf(fichier3,"\t\t\t\t\t \t\t\tTABLEAU DE BORD\n\n\n");
			fprintf(fichier3,"\t\t\t\t\t \t\t\tSimulation de %dh%dm à %dh%dm\n\n",Heure(debutHeure*3600),Minute(debutHeure*3600),Heure(finHeure*3600),Minute(finHeure*3600));
			fprintf(fichier3,"Le feu rouge s'est allumé %d fois , le feu vert %d fois et le feu orange %d\n\n",occRouge/2,occVert/2,occOrange/2);
			fprintf(fichier3,"%d vehicules sont passés aujourd'hui sur les deux routes \n\n",nbrfile1);

			fprintf(fichier3,"La taille moyenne de la file 1 est %d vehicules\n\n",totalFile1/(nbrfile1));
			fprintf(fichier3,"La taille moyenne de la file 2 %d vehicule \n\n",totalFile2/(nbrfile2));
			fprintf(fichier3,"Le temps moyen d'attente pour la file 1 est %dh %dm %ds\n\n",Heure(tempsAttente1/nbrfile1),Minute(tempsAttente1/nbrfile1),Seconde(tempsAttente1/nbrfile1));
			fprintf(fichier3,"Le temps moyen d'attente pour la file 2 est %dh %dm %ds\n\n",Heure(tempsAttente2/nbrfile2),Minute(tempsAttente2/nbrfile2),Seconde(tempsAttente2/nbrfile2));
			fprintf(fichier3,"La taille maximale de la file 1 est %d\n\n",max1);
			fprintf(fichier3,"La taille minimale de la file 1 est %d\n\n",min1+1);
			fprintf(fichier3,"La taille maximale de la file 2 est %d\n\n",max2);
			fprintf(fichier3,"La taille minimale de la file 2 est %d\n\n",min2+1);
			fprintf(fichier3,"Le débit moyen du traffic  est %.0f(véhicules/heure)\n\n",(nbrfile1/(finHeure-debutHeure)));
			fprintf(fichier3,"Le nombre moyen de clients de la file 1 calculé selon la loi de Little est N=lambda*Tmoyen=%.0f\n\n",(lambda1/nbrfile1)*(tempsAttente1/nbrfile1));
			fprintf(fichier3,"Le nombre moyen de clients de la file 2 calculé selon la loi de Little est N=lambda*Tmoyen=%.0f\n\n",(lambda2/nbrfile2)*(tempsAttente2/nbrfile2));
			fprintf(fichier3,"alpha = %.0f ,Tr=%ds ,Tv=%ds ,To=%ds \n\n\n\n",alpha,feu[5],feu[3],feu[4]);
			fprintf(fichier3,"\t\t\t\t\t\t\tISMIN EI17: Projet réalisé par KHATIB Omar \n\n\n");
}
		fclose(fichier3);



}
		fclose(fichier2);
}






