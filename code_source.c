#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<stdlib.h>
#define MaxIdentifiant 6 //le nbr maximum de caracteres de l'identifiant
#define MaxEnfant 10 //le nbr maximum d'enfants d'un personnel
#define MaxAnne 1936
#define MiniAnne 2001
#define AnneCourante 2019
char NomFichier[]="personne.txt"; //le fichier ou sera stoke les donnees
int main_exit;
//***************** Les Structures**********************************************
typedef struct{//structure du date
	int j;
	int m;
	int a;
}dat;


typedef char chaine[MaxIdentifiant];

typedef struct{     //structure pour les enfants d'une personne
	chaine id[MaxEnfant];
	int NbEnfant;
}enfant;

typedef struct{
char m_ID[MaxIdentifiant];// structure pour les identifiants des parents
char p_ID[MaxIdentifiant];
}parent;

typedef struct{  // structure pour les identifiants d'une personne
	char nom[25];
	char prenom[25];
	char sexe;
	dat date;
	char id[MaxIdentifiant];
	enfant enfants;
	parent parentss;
}personne;

typedef struct cellule{ ////chaine de personne
	personne valeur;
	struct cellule *suivant;
	struct cellule *precedent;
}cellule;

typedef struct { // structure pour le nom de l'utilisateur et le mot de passe
char user[10];
char pass[10];}admin;
typedef cellule *liste;
//--------------------------------Les Fonctions------------------------------------------

//**************************Creer Liste Vide**********************************************
liste CreerListeVide() // creer une liste vide qu'on rempliepar la suite
{
	liste l;
	l=NULL;
	return l;
}
//*********************** login ****************************************
//****************************Inserer Tete************************************************
liste InsererTete(liste l,personne per)
{
	cellule *nc;// creer une chaine *nc
    nc=(cellule*)malloc(sizeof(struct cellule));// reserve de la memoire
	nc->valeur=per;//affecte per a la valeur de *nc
	nc->suivant=l;//permet de pointer sur une autre cellule
	l=nc;
	return(l);//retourne la cellule voulue
}
//****************************Supprimer Position*******************************************
liste SupprimerPosition(liste l,liste p)//cette fonction nous premet de supprimer une seul cellue d'une liste chainé
{
	liste q,r;//declaration de deux variables local de type liste
	q=l;//affectation du l à q
	while((q->suivant!=NULL)&&(q!=p))//tant que la cellule suivante est non nulle  et que la cellule q est diff de p
	{	r=q;
		q=q->suivant;//incrementation du q
	}
	r->suivant=q->suivant;//et puit une incrementation de l'indice du r qui ^porte q
	free(q);
	return l;
}

//****************************Valide Nom***************************************************
int ValideNom(char nom[25])
{
	int i=0;
	while(nom[i])// tant que nom[i] est different de \0
	{
		if(((nom[i]<'a')||(nom[i]>'z'))&&((nom[i]<'A')||(nom[i]>'Z')))//si nom[i] n'est pas un alphabet
			return -1;
			i++;//passage a l'element suivant
			if (i>23) return -1;//le dernier element du chaine ce trouve dans l'indice 24
	}
	return 1;

}
//**********************************Valide Identifiant************************************
int ValideIdentfiant(char id[MaxIdentifiant])
{
	int i;
	 for(i=1;i<5;i++)
		if((id[i]>'9')||(id[i]<'0')) //il faut que l'identifiant soit sous la forme d'un caractere puis de 4 chiffres
			return -1;
	if ((strlen(id)!=5)||((id[0]<'a')||(id[0]>'z'))&&((id[0]<'A')||(id[0]>'Z')))//if
		return -1;//si les conditions ne sont pas respecter
	return 1;
}
//********************************** Valide Date *******************************************
int ValideDate(int j,int m,int a)
{//valide si la date est correcte

	if((j<28)&&(j>=1)&&(m>0)&&(m<13)&&(a>MiniAnne)&&(a<MaxAnne))
	return 1;
	else

	if((j==29)&&(m==2)&&(a%4==0)&&(a>MiniAnne)&&(a<MaxAnne))
		return 1;
	else

	if((j==29)&&(m!=2)&&(a>MiniAnne)&&(a<MaxAnne))
		return 1;
	else

	if((j==28)&&(m==2)&&(a%4!=0)&&(a>MiniAnne)&&(a<MaxAnne))
		return 1;
	else
	if((j==28)&&(m!=2)&&(a>MiniAnne)&&(a<MaxAnne))
		return 1;
	else

	if((j==31)&&(m!=4)&&(m!=2)&&(m!=6)&&(m!=9)&&(m!=11)&&(a>MiniAnne)&&(a<MaxAnne))
		return 1;
	else
		return -1;
}
//**********************************Saisie Date*******************************************
dat SaisieDate()
{//cette fonction permet de prendre la date de naissanced'une personne
	personne pp;
	printf("Donner la date de naissance\n");//stoque l'identifiant de a mere dans &pp.parents.m_ID
	do
	{
	printf("Jour:(jj)\t");
	scanf("%d",&pp.date.j);
	}while((pp.date.j<=0)||(pp.date.j>31));// de la stoquer dans &pp.date et de la retourner
	do
	{
	printf("Mois:(mm)\t");
	scanf("%d",&pp.date.m);
	}while((pp.date.m<=0)||(pp.date.m>12));
	do
	{
	printf("Annee:(aaaa)\t");
	scanf("%d",&pp.date.a);
	}while((pp.date.a<=1930)||(pp.date.a>1995));
	return pp.date;
}
//*************************** Parents ***********************
parent SaisieParent(){//stoque l'identifiant de a mere dans &pp.parents.m_ID
 personne pp;
 do {printf("ID du mere:\n");
 scanf("%s",&pp.parentss.m_ID);   //le if est fait pour ecrire prenom invalide
	if(ValideIdentfiant(pp.parentss.m_ID)==-1)
		printf("\tPRENOM INVALIDE\a\n");
	}while(ValideIdentfiant(pp.parentss.m_ID)==-1);//la boucle while est faite pour reboucler a chaque foi que l'identifiant est invalide'
	 do {printf("ID du pere:\n");
 scanf("%s",&pp.parentss.p_ID);
	if(ValideIdentfiant(pp.parentss.p_ID)==-1)
		printf("\tPRENOM INVALIDE\a\n");
	}while(ValideIdentfiant(pp.parentss.p_ID)==-1);//la fonction retourne pp.parents
  return pp.parentss;
}
//************************************Saisie Personne*************************************
personne SaisiePersonne()//la fonction suivante nous permet d'entrer les infos d'un personnel pour la premier fois
{
	int i;
	personne pp;//notre structure
	system("cls");
	printf("AJOUT PERSONNE\n\n\n");
	printf("Saisir les informations suivantes sur l'employe:\n");
	printf("\t\t\tATTENTION:NE FAITE PAS DES ESPACES DANS LA SAISIE\n");
	do
	{
	printf("Nom:\t");//des testes pour assurer un bon saisie
	scanf("%s",&pp.nom);
	if(ValideNom(pp.nom)==-1)
		printf("\tNOM INVALIDE\a\n");
	}while(ValideNom(pp.nom)==-1);
	do
	{
	printf("Prenom:\t");
	scanf("%s",&pp.prenom);
	if(ValideNom(pp.prenom)==-1)
		printf("\tPRENOM INVALIDE\a\n");
	}while(ValideNom(pp.prenom)==-1);

	do
	{
	printf("Sexe (M:male/F:female):\t");
	scanf("%s",&pp.sexe);
	if ((pp.sexe!='m')&&(pp.sexe!='f')&&(pp.sexe!='M')&&(pp.sexe!='F'))
		printf("\tCHOIX INVALIDE\a\n");
	}while((pp.sexe!='m')&&(pp.sexe!='f')&&(pp.sexe!='M')&&(pp.sexe!='F'));
	system("cls");
	do
	{
	pp.date=SaisieDate();
	printf("\nDate invalide\n");
	}while(ValideDate(pp.date.j,pp.date.m,pp.date.a)==-1);
	system("cls");
	printf("Identifiant:\t");
	do
	{
	scanf("%s",&pp.id);
	if(ValideIdentfiant(pp.id)!=1)
		printf("\t\aIDENTIFIANT NON VALIDE\nVEUILLEZ ENTRER UN IDENTIFIANNT DE LA FORME P0000:\t");

	}while (ValideIdentfiant(pp.id)!=1);
	printf("Nombre d'enfants:\t");
	scanf("%d",&pp.enfants.NbEnfant);
	if (pp.enfants.NbEnfant>0)
		for(i=0;i<pp.enfants.NbEnfant;i++)
		{
			printf("Identifiant de l'enfant %d:\t",i+1);
		  do
			{
			  scanf("%s",&pp.enfants.id[i]);
	    if(ValideIdentfiant(pp.enfants.id[i])!=1)
		printf("\t\aIDENTIFIANT NON VALIDE\nVEUILLEZ ENTRER UN IDENTIFIANNT DE LA FORME P0000:\t");
			}while (ValideIdentfiant(pp.enfants.id[i])!=1);
		}
    	system("cls");
	pp.parentss=SaisieParent();
    system("cls");
		return pp;
}

//*******************************Creer Liste******************************************
liste InsererPersonne(liste l,personne e)//cette fonction nous permet de cree une liste vide pour la remplire pmlus tard
{
	cellule  *nc,*pc;
	nc=(cellule*)malloc(sizeof(struct cellule));// allocation dynamique du memoire pour cette cellule
	pc=l;
	nc->valeur=e;
	nc->suivant=l;//chaque cellule point vers la suivante;
	l=nc;
    return(l);
}
//*************************Affiche Liste*********************************************
void AfficherListe(liste l)//cette fonction nous affiche une list contenant tous les infos dans la database
{
	liste pc;
	pc=l;char x;
	if (pc==NULL){system("cls");
		printf("\nFichier vide\n");// au cas ou le fichier est vide
		printf("frapper une touche pour retourner aux MENU");
			getch();}
			error://un label pour retourner si il y'avait une erreur
				system("cls");
        printf("AFFICHAGE DE TOUS LES PERSONNEL\n\n\n");
        printf("\t\t1.page par page\n\t\t2.dans une seul page");//l'utilisateur  a le choix entre afficher les resultats comme une
        scanf("%s",&x);//seul page ou bien plusieurs
if (x == '2'){//s'il veus une seul page
    	while(pc!=NULL)
	{
	int i;
	printf("°°°°°°°°°°°°°°°°°°°°°°°°°°°\n");
	printf("%s\t",pc->valeur.nom);
	printf("%s\t(nom prenom)\n",pc->valeur.prenom);
	printf("%c\t(Sexe)\n",pc->valeur.sexe);
	printf("%d\\%d\\%d\t(date de naissance)\n",pc->valeur.date.j,pc->valeur.date.m,pc->valeur.date.a);
	printf("%s\t(l'identifiant)\n",pc->valeur.id);
	printf("%d (nombre d'enfants)\n",pc->valeur.enfants.NbEnfant);
	if (pc->valeur.enfants.NbEnfant>0)
	  {
		for(i=0;i<pc->valeur.enfants.NbEnfant;i++)
		{
			printf("%s ",pc->valeur.enfants.id[i]);
		}
		printf("(Identifiants des enfants de %s)\n",pc->valeur.nom);
        printf("%s\t (les editifiants des parents\n",pc->valeur.parentss.m_ID,pc->valeur.parentss.p_ID);

	  }
		printf("°°°°°°°°°°°°°°°°°°°°°°°°°°°\n");
		pc=pc->suivant;//passage au suivant
	}getch();//attendre que l'utilisateur tape qlq button
}
else if (x=='1'){//s'il veus qu'ils soient dans plusieurs pages
    	while(pc!=NULL)
	{//chaque fois que l'utilisateur tape entrer la console affiche un nouveau personnel
	int i;
					system("cls");
					        printf("AFFICHAGE DE TOUS LES PERSONNEL\n\n\n");
	printf("°°°°°°°°°°°°°°°°°°°°°°°°°°°\n");
	printf("%s\t",pc->valeur.nom);
	printf("%s\t(nom prenom)\n",pc->valeur.prenom);
	printf("%c\t(Sexe)\n",pc->valeur.sexe);
	printf("%d\\%d\\%d\t(date de naissance)\n",pc->valeur.date.j,pc->valeur.date.m,pc->valeur.date.a);
	printf("%s\t(l'identifiant)\n",pc->valeur.id);
	printf("%d (nombre d'enfants)\n",pc->valeur.enfants.NbEnfant);
	if (pc->valeur.enfants.NbEnfant>0)
	  {
		for(i=0;i<pc->valeur.enfants.NbEnfant;i++)
		{
			printf("%s ",pc->valeur.enfants.id[i]);
		}
		printf("(Identifiants des enfants de %s)\n",pc->valeur.nom);
        printf("%s\t (les editifiants des parents\n",pc->valeur.parentss.m_ID,pc->valeur.parentss.p_ID);

	  }
		printf("°°°°°°°°°°°°°°°°°°°°°°°°°°°\n");
		if(pc->suivant!=NULL)//tant qu'il y a une cellule suivante
			{
			printf("\nfrapper une touche pour voir la personne suivant\n\n");
			getch();
			system("cls");
			}
		if(pc->suivant==NULL)//si on arrive a la fin
			{
			printf("frapper une touche pour retourner aux MENU");
			getch();
			system("cls");
			}
		pc=pc->suivant;
	}getch();
}
else goto error;// le cas ou en retourne en haut
}

//********************************Afficher Personne*******************************
liste AfficherPersonne(liste l)//cette fonction nous permet d'afficher tous les infos sur un person
{	liste p,pc;//en declare deux listes locaux
	int i;//un entier
	char ide[6], nom[25];//et deux chaines de caracteres
	p=l;
	system("cls");//en clean notre console
	printf("Afficher Personne\n");
	do
	{
		printf("nom de personnel a afficher:\t");//le program demande le nom de l'utilisateur
		scanf("%s",&nom);
	if(ValideNom(nom)==-1)
		printf("\tNOM INVALIDE\a\n");
	}while(ValideNom(nom)==-1);

				 printf("identifiant de personnel a afficher:\t");// au cas ou le nom et compatible il pass a demander son ID
				 	do
						{
						scanf("%s",&ide);
						if(ValideIdentfiant(ide)!=1)
						printf("\t\aIDENTIFIANT NON VALIDE\nVEUILLEZ ENTRER UN IDENTIFIANNT DE LA FORME P0000:\t");

						}while (ValideIdentfiant(ide)!=1);//verifier seulement si la foction valideidentifiant nous retourne un 1
	if(p==NULL)
	{
		printf("\npersonne introuve\n");
		return l;//si la list est vide on aura aucune information
	}
	while(p!=NULL)//tant que la list n'est pas vide
		{
			if((strcmp(p->valeur.id,ide)==0)&&strcmp(p->valeur.nom,nom)==0)//et que le nom et l'ID sont compatibles
				{pc=p;
				printf("°°°°°°°°°°°°°°°°°°°°°°°°°°°\n");//le program pass a afficher tous ce qu'il a sur cette person
				printf("%s\t",pc->valeur.nom);
				printf("%s\t(nom prenom)\n",pc->valeur.prenom);
				printf("%c\t(Sexe)\n",pc->valeur.sexe);
				printf("%d\\%d\\%d\t(date de naissance)\n",pc->valeur.date.j,pc->valeur.date.m,pc->valeur.date.a);
				printf("%s\t(l'identifiant)\n",pc->valeur.id);
				printf("%d (nombre d'enfants)\n",pc->valeur.enfants.NbEnfant);
				if (pc->valeur.enfants.NbEnfant>0)
					{
					for(i=0;i<pc->valeur.enfants.NbEnfant;i++)//selon le nombre de ces enfants l'affichage ce fait
						{
						printf("%s ",pc->valeur.enfants.id[i]);
						}
					printf("(Identifiants des enfants de %s)\n",pc->valeur.nom);
					}
               printf("%s\t(l'identifiant du mere\n",pc->valeur.parentss.m_ID);
               printf("%s\t(l'identifiant du pere\n",pc->valeur.parentss.p_ID);

		printf("°°°°°°°°°°°°°°°°°°°°°°°°°°°\n");
		return l;
	}
			p=p->suivant;
		}
	printf("\npersonne introuve\n");//au cas ou les infos ne sont pas compatible
	return l;

}
//******************************************** Retourner les parents du personnel ********************************
void parents (liste l){  //cette fonction nous permet de retourner les ID des parents d'un personnel
 liste p;
 char ide[6], nom[25];
 liste pc;
 p=l;
 system("cls");
 printf("\nAFFICHER les parents du personnel\n");
do
 {
 printf("nom de personnel a AFFICHER leur parents:\t");//le program demande d'insere les infos principal du personnel
  scanf("%s",&nom);//le test est fait sur le now et l'ID du personeel
 if(ValideNom(nom)==-1)//si les deux sont compatibles donc il passe a nous afficher notre resultat voulu
  printf("\tNOM INVALIDE\a\n");
 }while(ValideNom(nom)==-1);
 printf("identifiant de personnel a AFFICHER leur parents:\t");
 do
 {
  scanf("%s",&ide);
  if(ValideIdentfiant(ide)!=1)
  printf("\t\aIDENTIFIANT NON VALIDE\nVEUILLEZ ENTRER UN IDENTIFIANNT DE LA FORME P0000:\t");
 }while (ValideIdentfiant(ide)!=1);
  while ((p!=NULL)&&((strcmp(p->valeur.id,ide)!=0)||strcmp(p->valeur.nom,nom)!=0))
{
   p=p->suivant;};
   if(p==NULL)
   {
    printf("\npersonne introuve\n");
    return l;
   }
   if((strcmp(p->valeur.id,ide)==0)&&strcmp(p->valeur.nom,nom)==0)
				{pc=p;
 printf("l'ID du mere est %s \n le ID du pere est %s",pc->valeur.parentss.m_ID,pc->valeur.parentss.p_ID);//un simple affichage
 getch();}
}
//********************************* Retourner Age Personnel *******************************
/*list AgePersonnel(liste l)
{
  liste p;
 char ide[6], nom[25];
 p=l;
 system("cls");
 printf("\nAFFICHER AGE\n");
do
 {
 printf("nom de personnel a AFFICHER leur age:\t");
  scanf("%s",&nom);
 if(ValideNom(nom)==-1)
  printf("\tNOM INVALIDE\a\n");
 }while(ValideNom(nom)==-1);
 printf("identifiant de personnel a AFFICHER leur age:\t");
 do
 {
  scanf("%s",&ide);
  if(ValideIdentfiant(ide)!=1)
  printf("\t\aIDENTIFIANT NON VALIDE\nVEUILLEZ ENTRER UN IDENTIFIANNT DE LA FORME P0000:\t");
 }while (ValideIdentfiant(ide)!=1);
  while ((p!=NULL)&&((strcmp(p->valeur.id,ide)!=0)||strcmp(p->valeur.nom,nom)!=0))
{
   p=p->suivant;};
   if(p==NULL)
   {
    printf("\npersonne introuve\n");
    return l;
   }

 printf("l'age de ce personnel est :%d ans \n\n",AnneCourante-p->valeur.date.a) ;
 return l;

}*/
//********************************Rechercher Nombre D'enfant*******************************
liste RechercherNbenfant(liste l)//cette fonction pour savoir  le nombre des enfants d'un employer quelconque
{
	liste p;
	char ide[6], nom[25];
	p=l;
	system("cls");
	printf("\n NOMBRE D'ENFANT\n");
do
	{
	printf("nom de personnel a cherche le nombre d'enfants:\t");//notre test normal pour savoir si le nom et l'identifiant sont compatibles
		scanf("%s",&nom);
	if(ValideNom(nom)==-1)
		printf("\tNOM INVALIDE\a\n");
	}while(ValideNom(nom)==-1);
	printf("identifiant de personnel cherche:\t");
	do
	{
		scanf("%s",&ide);
		if(ValideIdentfiant(ide)!=1)
		printf("\t\aIDENTIFIANT NON VALIDE\nVEUILLEZ ENTRER UN IDENTIFIANNT DE LA FORME P0000:\t");

	}while (ValideIdentfiant(ide)!=1);
		while ((p!=NULL)&&((strcmp(p->valeur.id,ide)!=0)||strcmp(p->valeur.nom,nom)!=0))
{
			p=p->suivant;};
			if(p==NULL)//au cas ou la list est vide
			{
				printf("\npersonne introuve\n");
				return l;
			}
printf("\n\nle nombre d'enfant de %s est=%d\n\n",p->valeur.nom,p->valeur.enfants.NbEnfant);//un affichage du resultat trouver
		return l;

}



//*********************************Ajouter Enfant************************************
liste AjouterEnfant(liste l)//cette fonction nous permet d'ajouter les enfants de chaque utilisateur
{
	liste p;
	char ide[6], nom[25];
	p=l;
	system("cls");
	printf("\nAJOUTER ENFANT\n");
do
	{
	printf("nom de personnel a ajoute enfant:\t");//en demande le nom de l'utilisateur et puis son ID pour les verifier ensuite
		scanf("%s",&nom);
	if(ValideNom(nom)==-1)
		printf("\tNOM INVALIDE\a\n");
	}while(ValideNom(nom)==-1); // la valeur retourner par validenom doit etre egale a 1 pour passer
	printf("identifiant:\t");
	do
	{
		scanf("%s",&ide);
		if(ValideIdentfiant(ide)!=1)
		printf("\t\aIDENTIFIANT NON VALIDE\nVEUILLEZ ENTRER UN IDENTIFIANNT DE LA FORME P0000:\t");

	}while (ValideIdentfiant(ide)!=1);
		while ((p!=NULL)&&((strcmp(p->valeur.id,ide)!=0)||strcmp(p->valeur.nom,nom)!=0))
{
			p=p->suivant;};
			if(p==NULL)//si la liste est vide
			{
				printf("\npersonne introuve\n");
				return l;
			}
			p->valeur.enfants.NbEnfant++;

				printf("Identifiant de l'enfant a ajoute:\t");//l'ajoute des identifications de chaque enfant
		  do
			{
			scanf("%s",p->valeur.enfants.id[p->valeur.enfants.NbEnfant]);
	    if(ValideIdentfiant(p->valeur.enfants.id[p->valeur.enfants.NbEnfant])!=1)
		printf("\t\aIDENTIFIANT NON VALIDE\nVEUILLEZ ENTRER UN IDENTIFIANNT DE LA FORME P0000:\t");
			}while (ValideIdentfiant(p->valeur.enfants.id[p->valeur.enfants.NbEnfant])!=1);
						 printf("\n Ajout effectue\n");
			return l;//le retour de la list modifier comportant les id des enfants
		}

//********************************Supprimer Personne************************************
liste SupprimerPersonne(liste l)//cette fonction nous permet de suprimer un seul compte
{
liste p,pre;
	char ide[6], nom[25];
	p=l;
	system("cls");
	printf("\nSUPPRIMER PERSONNE\n");
		do
	{
	printf("nom de personnel a supprimer:\t");//l'utilisateur doit insere le nom et le ID du person qui veus la suprimer
		scanf("%s",&nom);
	if(ValideNom(nom)==-1)
		printf("\tNOM INVALIDE\a\n");//le nom et le ID doivent obligatoirement qu'il soit compatible
	}while(ValideNom(nom)==-1);
	printf("identifiant :\t");
		do
			{
				scanf("%s",&ide);
				if(ValideIdentfiant(ide)!=1)
				printf("\t\aIDENTIFIANT NON VALIDE\nVEUILLEZ ENTRER UN IDENTIFIANNT DE LA FORME P0000:\t");
			}while (ValideIdentfiant(ide)!=1);
		while ((p!=NULL)&&((strcmp(p->valeur.id,ide)!=0)||strcmp(p->valeur.nom,nom)!=0))
		{
			pre=p;
			p=p->suivant;//le passage a la cellule suivante
		};
			if(p==NULL)//au cas ou la liste est vide
			{
				printf("\npersonne introuve\n");
				return l;
			}
			if(p==l)
			{
				l=l->suivant;//l'affectatin du cellule suivante pour liberer p
				free(p);
				printf("\nFICHE SUPPRIME\n\n");
				return l;
			}
			pre->suivant=p->suivant;
			free(p);
			printf("\nFICHE SUPPRIME\n\n");
		return l;
}
//********************************* Tri Par Nom *******************************************
liste TriNom(liste l)//cette fonction nous permet de trier notre liste par nom
{
	personne aux;


	liste p,q;//on declare deux listes locaux
	p=l;

	if (l==NULL)//si la list est vide
	return l;//la fonction ce termine isi
	system("cls");

	while(p!=NULL)//tant que notre liste n'est pas vide
	{
			q=p->suivant;//q est affecter par ma cellule suivante
			while(q!=NULL)
				{
					if(strcmp(p->valeur.nom,q->valeur.nom)>0)//verifier au cas ou notre valeurs sont egaux
					{
					 aux=q->valeur;
                     q->valeur=p->valeur;//permutation entre les deux
                     p->valeur=aux;
					}
					q=q->suivant;//incrementation
				}
	p=p->suivant;
	}
	return l;//le retourne du list trier
}

//********************************* Tri Par Identifiant *******************************************

liste TriIdentifiant(liste l)//cette fois le tri est par identifiant
{
	personne aux;
	liste p,q;
	p=l;

	if (l==NULL)
	return l;
	system("cls");

	while(p!=NULL)
	{
			q=p->suivant;//chaque fois en pass au cellule suivante
			while(q!=NULL)
				{
					if(strcmp(p->valeur.id,q->valeur.id)>0) // la condition est verifie ssi la valeur d'id dans q esr plus grand que dans p
					{//et voici sidessous une permutation entre les deux listes
					 aux=q->valeur;
                     q->valeur=p->valeur;
                     p->valeur=aux;
					}
					q=q->suivant; //l'incrementation du liste q
				}
	p=p->suivant; //l'incrementation du liste p
	}
	return l;
}
//************************** Mise a Jour **************************************************

/*liste MiseAjour(liste l,personne per)
{

 personne p;
 char ide[6], nom[25];
 system("cls");
 printf("\nMISE A JOUR\n");
do
 {
 printf("nom de personnel a faire la mise a jour:\t");
  scanf("%s",&nom);
 if(ValideNom(nom)==-1)
  printf("\tNOM INVALIDE\a\n");
 }while(ValideNom(nom)==-1);
 printf("identifiant a faire la mise a jour:\t");
 do
 {
  scanf("%s",&ide);
  if(ValideIdentfiant(ide)!=1)
  printf("\t\aIDENTIFIANT NON VALIDE\nVEUILLEZ ENTRER UN IDENTIFIANNT DE LA FORME P0000:\t");
 }while (ValideIdentfiant(ide)!=1);
{

p.parentss=SaisieParent(liste l);

return p;
}*/

//*********************************Ecrire Fichier****************************************
//cerre fonction cree un backup d'une liste donner
void EcrireFichier(liste l){
	liste pc;
	FILE *fichier;
	pc=l;
	int i;
	fichier=fopen(NomFichier,"w");//la creation d'un fichier en mode ecriture
	if(l==NULL)
	{
		fclose(fichier);//si la liste est deja vide l'operation est annule
	}
while(pc!=NULL)
	{
		fprintf(fichier,"%s\n",pc->valeur.nom);
		fprintf(fichier,"%s\n",pc->valeur.prenom);
		fprintf(fichier,"%c\n",pc->valeur.sexe);
		fprintf(fichier,"%d\n",pc->valeur.date.j);
		fprintf(fichier,"%d\n",pc->valeur.date.m);
		fprintf(fichier,"%d\n",pc->valeur.date.a);
		fprintf(fichier,"%s\n",pc->valeur.id);
		fprintf(fichier,"%d\n",pc->valeur.enfants.NbEnfant);
		for(i=0;i<pc->valeur.enfants.NbEnfant;i++)
			fprintf(fichier,"%s\n",pc->valeur.enfants.id[i]);
		pc=pc->suivant;//passage a la liste suivante
	};
	fclose(fichier);
}
//********************************Lire fichier*******************************************
liste LireFichier(liste l)
{ // cette fonction nous permet de lire une liste donner
	cellule *pc;
	FILE *fichier;
	int i;
	fichier=fopen(NomFichier,"r");//ouverture d'un fichier en mode lecture
	if(!fichier) //si l'ouverture est échoué
	{system("color 1f");
		printf("le fichier:'personne.txt' n'existe pas ajoute personne pour creer le fichier\n");

		printf("\nfrapper une touche pour voir le MENU\n");
		getch();
return(l);
	}
	while(!feof(fichier))//pendant que le fichier existe et ouvrable
	{
		pc=(cellule *)malloc(sizeof(cellule));//allocation dynamique du memoire pour stocker la liste
		while(1)
		{    //la lecture des variables stocker dans le fichier
			fscanf(fichier,"%d\n",&pc->valeur.nom);
			fscanf(fichier,"%s\n",&pc->valeur.nom);
			fscanf(fichier,"%s\n",&pc->valeur.prenom);
			fscanf(fichier,"%s\n",&pc->valeur.sexe);
			fscanf(fichier,"%d\n",&pc->valeur.date.j);
			fscanf(fichier,"%d\n",&pc->valeur.date.m);
			fscanf(fichier,"%d\n",&pc->valeur.date.a);
			fscanf(fichier,"%s\n",&pc->valeur.id);
			fscanf(fichier,"%d\n",&pc->valeur.enfants.NbEnfant);
			for(i=0;i<pc->valeur.enfants.NbEnfant;i++)
			fscanf(fichier,"%s\n",&pc->valeur.enfants.id[i]);
			break;
		}
		pc->suivant=l;//passage a la liste suivante
		l=pc;
	};
	fclose(fichier);
	return(l);
}
int login(int n ){ //la fonction suivante test l'authentification d'administrateur responsable d'inserer les infos
    char admin_pass[10],admin_user[10];
char pass[10],user[10];
FILE *s;
s = fopen("logdb.dat","rw");//l'ouverture du fichier qui stock les infos du login en mode lecture et ecriture pour les modier en cas s'il est demander
fscanf(s,"%s %s",admin_user,admin_pass);
if(n == 1){
        if(s != NULL ){
rr://un tag pour reetre les credentials au cas d'une erreur
    printf("\n\n\t\tEnter le nom d'utilisateur:");scanf("%s",user);
    printf("\n\n\t\tEnter le mot de pass:");scanf("%s",pass);
//le program scan le nom d'utilisateur et son mot de pass
    if (strcmp(pass,admin_pass)==0 && strcmp(user,admin_user) ==0 )//et les comparer avec ceux qui sont deja stocker dans le fichier
               {
               system("cls");
                return 1;
       }
    else //au cas ou l'un des deux est incorrect
        {   system("color 4");
            printf("\n\n le nom de l'utilisateur ou le mot de pass est incorrect!!\a\a\a");
            login_try:
            printf("\nEnter 1 pour essayer encore une fois ou 0 pour quiter:");//l'utilisateur à le choix entre reesayer encore une fois ou quiter
            scanf("%d",&main_exit);
            if (main_exit==1)
                    {
                    system("cls");
                    system("color F");
                    goto rr;
                    }

            else if (main_exit==0)
                    {
                    system("cls");
                    return -1;}
            else
                    {printf("\nInvalid!");
                    system("cls");
                   goto login_try;}

       } }
       else if (s == NULL)
       {
           printf("le fichier logdb.dat n'est pas trouver ");// si l'ouverture du fichier n'etait pas successive le program ne commence jamais
           return (-1);
       }
         }

else if (n == 2){//dans cette deuxiem partie l'utilisateur a la posibilité de changer le nom d'utilisateur ou le mot de pass
             char ps[10];int m;char po[10];
    system("cls");
error:
     printf("\n\n\t\t1.changer le usernam\n\t\t2.changer le mot de pass\n\t\t3.se deconnecter\n\t\t Enter votre choix:");
    scanf("%d",&m);
    system("cls");
      if(m == 1){
      printf("entrer le nouveau nom d'utilisateur:");
      scanf("%s",po);
      strcpy(admin_user,po);}//le nouveau nom d'utilisateur est stocker dans la variable locale qui porte l'ancien username
      else if (m == 2){
        printf("\nentrer le nouveau mot de pass:");
        scanf("%s",ps);
        strcpy(admin_pass,ps);//le nouveau mot de pass est stocker dans la variable locale qui porte l'andcien mot de pass
      }
      else if(m==3){
        system("color F");
        main();}//au cas du deconnection l'utilisateur est redericter vers la partie principal du program
      else goto error;
      system("cls");
      return 1;
    }
    fprintf(s,"%s %s\n",admin_user,admin_pass);
    fclose(s);}//et enfin les nouveaux valeurs sont stocker dans le fichier

//**************************PROGRAMME PRINCIPALE*****************************************

int main()
{//dans notre fonction main nous avons la premier partie qui concerne la conection de l'utilisateur
    if(login(1) == 1){
	liste l=CreerListeVide();//la creatioin d'une nouvelle liste vide
	char choix,c;
	int i;
	char chaine[]="encadrer par Mr.mostafa Saadi";
	personne p;
	l=LireFichier(l);//pour la lecture du liste
	l=TriNom(l);//pour refaire le tri du liste
do
{
	system("color 1f");
	ret:
	system("cls");
printf("\n\n\t\t\tSYSTEM DE GESTION DES EMPLOYEES");
    printf("\n\n\n\t\t\t\xB2\xB2\xB2\xB2\xB2\xB2\xB2 BIENVENUE AU MENU PRINCIPAL \xB2\xB2\xB2\xB2\xB2\xB2\xB2");
    printf("\n\n\t\t1.Ajouter un compte\n\t\t2.Consulter tous les fiches\n\t\t3.Afficher personne\n\t\t4.Ajouter enfant\n\t\t5.Suprimer un compte\n\t\t6.Tri par identifiant\n\t\t7.Chercher nombre enfant\n\t\t8.afficher les parents\n\t\t9.espace administrative\n\t\tS.supprimer tous\n\t\tQ.Quiter\n\t\th.A propos\n\n\n\n\n\t\t Enter votre choix:");
    choix =getch();//l'utilisateur choisi l'un des options
	switch(choix)
		{
		case '1':p=SaisiePersonne();//la saisie d'un nouveau compte avec l'insertion de cette personne dans la liste existante
				l=InsererPersonne(l,p);
				l=TriNom(l);//le tri ce refait encore une fois pour guarder la list ordoner
				EcrireFichier(l);//les infos sont stocker dans le fichier
				printf("frapper une touche pour retourner aux MENU");
				break;
		case '2':AfficherListe(l);
//affichage simple d'une liste
				break;
		case '3':system("cls");//clear the screen
				 l=AfficherPersonne(l);//l'affichage des infos d'un seul employee
				printf("frapper une touche pour retourner aux MENU");
				getch();

				break;
		case '4':l=AjouterEnfant(l);//pour entrer les infos des enfants
				 EcrireFichier(l);//l'ecriture dans le fichier
				 printf("frapper une touche pour retourner aux MENU");
				 getch();//l'attend pour detecter une click du clavier
				break;
		case '5':l=SupprimerPersonne(l);//pour supprimer une seule personne
				 printf("frapper une touche pour retourner aux MENU");
				 getch();
				 EcrireFichier(l);//ecriture dans le fichier
				break;
		case '6':system("cls");
				 printf("\nTRI PAR IDENTIFIAN\n");//le tri ce fait par l'identifiant
				 l=TriIdentifiant(l);//la fonction retourne une list trie
				 printf("\n\nLISTE TRIE PAR IDENTIFIAN\n\n");
				 printf("tapez une touche pour voir la liste trie\n");
				 getch();
				 EcrireFichier(l);//l'ecriture dans le fichier et son affichage
				 AfficherListe(l);
				break;
		case '7':l=RechercherNbenfant(l);//la fontion suivante retourne le nomber des enfants de chaque personne
				 EcrireFichier(l);//l'ecriture dans le fichier
				 printf("frapper une touche pour retourner aux MENU");
				 getch();
				break;
		case '8':parents(l);//appelation du fonction du parents
				break;
	case '9':l=login(2);//pour changer le nom d'utilisateur et le mot de pass
    break;

		case 'h':	system("cls");
			 // afficher des informations sur le program
					for(i=0;i<30;i++)
						{
						printf("%c\a",chaine[i]);//affiche tous les elements du chaine
						}
					printf("\n");
					printf("frapper une touche pour retourner aux MENU");
					getch();
				break;

		case 'S':system("cls");
				 system("color c0");//cette partie permet de suprimer tous la database
				 printf("\n ETES VOUS SUR DE SUPPRIMER TOUTE LA LISTE(o\\n)?\t");
				 c=getch();
				 if (c=='o')
				{
				 l=CreerListeVide();
				 EcrireFichier(l);//la liste suprimer est remplacer part une autre vide
				 printf("\nSupprission effectue\n");
				 printf("\nfrapper une touche pour retourner aux MENU\n");
				 getch();
				}
				 system("cls");
				break;
		case 's':system("cls");
				 system("color c0");//c'est la meme fonction precedente sauf qu'il marche pour la forme miniscule du s
				 printf("\n ETES VOUS SUR DE SUPPRIMER TOUTE LA LISTE(o\\n)?\t");
				 c=getch();
				 if (c=='o')
				{
				 l=CreerListeVide();
				 EcrireFichier(l);
				 printf("\nSupprission effectue\n");
				 printf("\nfrapper une touche pour retourner aux MENU\n");
				 getch();
				}
				 system("cls");
				break;
		}
}while ((choix!='q') && (choix!='Q'));//si le choix est Q ou bien q le program s'arrete
system("cls");
printf("\n\nFermeture\n\n");
}
return 0;}
