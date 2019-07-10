int AfficheHeure(int s);
int Heure(int s);
int Minute(int s);

int Seconde(int s);
int *Feu(void);
int  gestion1(File*file,float *date,bool Switch,informationsRoute *info);
int  gestion2(File*file,float *date,bool Switch,informationsRoute *info);
int GestionTraffic(File* route1,File *route2,informationsRoute *info,informationsRoute *info2,int T);
char *Etat1(int Switch,float date,int *Feu);
void lectureFichier(void);
int *Etat(int Switch,float date,int *Feu);
void test(void);
