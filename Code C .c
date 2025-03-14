#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int Nbr_niveau=0;
int Nbr_enseignant=0;
int Nbr_etudiant=0;

typedef struct Niveau{
    char*  Nom;
    char*  horaire;
    float  Duree;
    int    nbr;
    char   nom_enseignant[100];
    struct Niveau* suiv;
}niveau;

typedef struct Etudiant{
  char*  Nom_Prenom;
  char*  CIN;
  char*  Email;
  char*  nom_niveau;
  float  paiement;
  struct Etudiant* suiv;
}etudiant;

typedef struct Enseignant{
  char*  Nom_Prenom;
  char*  CIN;
  char*  Email;
  char*  nom_niveau;
  struct Enseignant* suiv;
}enseignant;

etudiant*         Liste_etudiant= NULL;
enseignant*       Liste_enseignant=NULL;
niveau*           Liste_niveau=NULL;



char*  Allocation()
{
    char* chaine=(char*)malloc(100);
    if(chaine == NULL){ exit(0);}

    fgets(chaine,100,stdin);
    return chaine;
}


void clearConsole(){
    system("cls");
}

void viderTamponEntree() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}


niveau* creer_Niveau()
{
    niveau* Nv_niveau = (niveau*)malloc(sizeof(niveau));
    niveau* tmp1 = Liste_niveau;
    if(Nv_niveau == NULL){exit(0);}


    printf("\nsaisir le nom de niveau:");
    Nv_niveau->Nom = Allocation();


    printf("\nsaisir l'horaire:");
    Nv_niveau->horaire = Allocation();


    printf("\nsaisir la duree en heure:");
    scanf("%f",&Nv_niveau->Duree);
    viderTamponEntree();

    Nv_niveau->nbr = 0;

    Nv_niveau->suiv = NULL;

    while(tmp1!= NULL)
    {
        //est ce que le niveau deja existe
        if(strcmp(tmp1->Nom,Nv_niveau->Nom) == 0 )
        {
        printf("\nle niveau deja existe");
         return NULL;
        }
        tmp1 = tmp1->suiv;
    }
    Nbr_niveau++;
    return Nv_niveau;
}

enseignant* creer_Enseignant()
{
    enseignant* tmp1 = Liste_enseignant;
    niveau* tmp2 = Liste_niveau;
    enseignant* Nv_enseignant=(enseignant*)malloc(sizeof(enseignant));
    int x=0;
    if( Nv_enseignant == NULL){ exit(0);}

    printf("\nsaisir le Nom et Prenom d'enseignant:");
    Nv_enseignant->Nom_Prenom = Allocation();

    printf("\nsaisir le CIN d'enseignant:");
    Nv_enseignant->CIN = Allocation();

    printf("\nsaisir le Email d'enseignant:");
    Nv_enseignant->Email = Allocation();

    printf("\nsaisir le nom de niveau a enseigne:");
    Nv_enseignant->nom_niveau= Allocation();

    while(tmp1 != NULL && tmp2 != NULL)
    {

        //CIN deja existe ou niveau introuvable ou niveau deja enseigne
        if(strcmp(Nv_enseignant->CIN,tmp1->CIN) == 0 || (strcmp(Nv_enseignant->nom_niveau,tmp2->Nom)==0 && strlen(tmp2->nom_enseignant)!=0))
        {
            printf("\nl'enseignant est insere  ou le niveau deja enseigne");
            return NULL;
        }


        tmp1 = tmp1->suiv;
        tmp2 = tmp2->suiv;
    }
    //verification si le niveau est introuvable
    tmp2 = Liste_niveau;
    while(tmp2 !=NULL)
    {
      if(strcmp(Nv_enseignant->nom_niveau,tmp2->Nom) == 0 ){
                x++;
        }
        tmp2=tmp2->suiv;
    }
    if(x == 0)
        {
         printf("\nle niveau introuvable");
         getchar();
         return NULL;
       }

    Nv_enseignant->suiv = NULL;

    // inserer les informations sur le niveau
    tmp2 = Liste_niveau;
    while(tmp2 != NULL)
    {
        if(strcmp(tmp2->Nom,Nv_enseignant->nom_niveau) == 0 )
        {
            strcpy(tmp2->nom_enseignant,Nv_enseignant->Nom_Prenom);
        }
        tmp2 = tmp2->suiv ;
    }
    return Nv_enseignant;
}

etudiant* creer_Etudiant()
{
    etudiant* tmp1 = Liste_etudiant;
    niveau* tmp2 = NULL;
    int i,x=0;
    etudiant* Nv_etudiant=(etudiant*)malloc(sizeof(etudiant));
    if( Nv_etudiant == NULL){ exit(0);}

    printf("\nsaisir le Nom et Prenom d'etudiant:");
    Nv_etudiant->Nom_Prenom = Allocation();

    printf("\nsaisir le CIN d'etudiant:");
    Nv_etudiant->CIN = Allocation();

    printf("\nsaisir le Email d'etudiant:");
    Nv_etudiant->Email= Allocation();

    printf("\nsaisir le nom de niveau d'etudiant:");
    Nv_etudiant->nom_niveau = Allocation();

    printf("\nsaisir le paiement:");
    scanf("%f",&Nv_etudiant->paiement);


    //verification que le CIN est unique et Niveau existe
    while(tmp1 != NULL )
    {
        if(strcmp(Nv_etudiant->CIN,tmp1->CIN) == 0 )
        {
            printf("\nl'etudiant est deja insere ");
            return NULL;
        }
        tmp1 = tmp1->suiv;
    }

   tmp2 = Liste_niveau;

    if(tmp2 != NULL){

        while(tmp2 != NULL){
        if(strcmp(tmp2->Nom,Nv_etudiant->nom_niveau) == 0)
        {
            x++;
            break;
        }
        tmp2 = tmp2->suiv ;
    }
    if(x == 0)
    {
        printf("Niveau introuvable!!");
        return NULL;
    }
    }


    Nv_etudiant->suiv=NULL;

    //nbr d'etudiants par niveau<=capacite
    tmp2 = Liste_niveau;
    while(tmp2 != NULL)
    {
        if(strcmp(tmp2->Nom,Nv_etudiant->nom_niveau) == 0 )
        {

            // verification si l'ajout est disponible
                   if(tmp2->nbr == 20)
                   {
                    printf("les places sont limites");
                    return NULL;
                   }
            tmp2->nbr ++;
        }
        tmp2 = tmp2->suiv ;
    }
    return Nv_etudiant;
}

void Ajout_Enseignant()
{
    enseignant* Nv_enseignant = creer_Enseignant();
    enseignant* tmp = Liste_enseignant;
    if(Nv_enseignant == NULL){
            printf("\nEnseignant non insere");
            getchar();
            return ;}

    if(Liste_enseignant == NULL){
      Liste_enseignant = Nv_enseignant;
      printf("\nEnseignant ajoute");
      getchar();
    }

    else{
       while(tmp->suiv!=NULL){
        tmp = tmp->suiv;
       }
       tmp->suiv = Nv_enseignant;
       printf("\nEnseignant ajoute");
       getchar();
    }
   Nbr_enseignant++;
}

void Ajout_Etudiant()
{
    etudiant* Nv_etudiant = creer_Etudiant();
    etudiant* tmp = Liste_etudiant;
    if(Nv_etudiant == NULL){
            printf("\nEtudiant non insere");
            getchar();
            return ;}
  else{
     if(Liste_etudiant == NULL){
      Liste_etudiant = Nv_etudiant;
      printf("\nEtudiant ajoute");
      getchar();
    }
    else{
       while(tmp->suiv!=NULL){
        tmp = tmp->suiv;
       }
       tmp->suiv = Nv_etudiant;
       printf("\nEtudiant ajoute");
       getchar();
    }
    Nbr_etudiant++;
  }
}

void Ajout_Niveau()
{
    niveau* Nv_niveau = creer_Niveau();
    niveau* tmp = Liste_niveau;
    if(Nv_niveau == NULL){
            printf("\nNiveau non ajoute");
            getchar();
            return;}

     if(Liste_niveau== NULL){
      Liste_niveau = Nv_niveau;
      printf("\nNiveau ajoute");
      getchar();
    }

    else{
       while(tmp->suiv!=NULL){
        tmp = tmp->suiv;
       }
       tmp->suiv = Nv_niveau;
       printf("\nNiveau ajoute");
       getchar();
    }
}

void Afficher_Enseignant(enseignant* tmp)
{
      printf("\nNom et Prenom d'enseignant:%s", tmp->Nom_Prenom);
      printf("\nCIN d'enseignant:%s", tmp->CIN);
      printf("\nle Email d'enseignant:%s", tmp->Email);
      printf("\nle nom de niveau enseigne:%s",tmp->nom_niveau);
      printf("\n");
}

void Afficher_Enseignants(enseignant* Liste_enseignant)
{
    if(Liste_enseignant != NULL)
    {
        Afficher_Enseignant(Liste_enseignant);
        Afficher_Enseignants(Liste_enseignant->suiv);
    }
}

void Afficher_Etudiant(etudiant* tmp)
{
      printf("\nNom et Prenom d'etudiant:%s", tmp->Nom_Prenom);
      printf("\nCIN d'etudiant:%s", tmp->CIN);
      printf("\nle Email d'etudiant:%s", tmp->Email);
      printf("\nle nom de niveau d'etudiant:%s",tmp->nom_niveau);
      printf("\nle paiement:%.2f", tmp->paiement);
      printf("\n");
}

void Afficher_Etudiants( etudiant* Liste_etudiant)
{
    if(Liste_etudiant != NULL)
    {
        Afficher_Etudiant(Liste_etudiant);
        Afficher_Etudiants(Liste_etudiant->suiv);
    }
}

void Afficher_Niveau(niveau* tmp)
{
      enseignant* ens = Liste_enseignant;
      etudiant* etu = Liste_etudiant;
      int count = 0;
      printf("\nNom de niveau:%s", tmp->Nom);
      printf("\nL'horaire:%s", tmp->horaire);
      printf("\nLa duree:%.2f h\n", tmp->Duree);


      // Recherche de l'enseignant dans la liste des enseignants

      while (ens != NULL) {
        if (strcmp(ens->nom_niveau, tmp->Nom) == 0) {
            printf("\nEnseignant responsable: %s", ens->Nom_Prenom);
            break;
        }
        ens = ens->suiv;
      }

    // Compter le nombre d'étudiants dans ce niveau

    while (etu != NULL) {
        if (strcmp(etu->nom_niveau, tmp->Nom) == 0) {
            count++;
        }
        etu = etu->suiv;
    }
    printf("\nNombre d'etudiants: %d\n", count);
    printf("\n");
}

void Afficher_Niveaux(niveau* Liste_niveau)
{
    if(Liste_niveau != NULL)
    {
        Afficher_Niveau(Liste_niveau);
        Afficher_Niveaux(Liste_niveau->suiv);
    }
}

void Paiement_Complet(etudiant* Liste_etudiant)
{
  if(Liste_etudiant!=NULL)
  {
    if(Liste_etudiant->paiement == 5000.00)
    {
        printf("\n");
        Afficher_Etudiant(Liste_etudiant);
    }
   Paiement_Complet( Liste_etudiant->suiv);
  }
}

void Paiement_Incomplet(etudiant* Liste_etudiant)
{
  if(Liste_etudiant!=NULL)
  {
    if(Liste_etudiant->paiement < 5000.00)
    {
        printf("\n");
        Afficher_Etudiant(Liste_etudiant);
    }
   Paiement_Incomplet( Liste_etudiant->suiv);
  }
}

void supprimer_etudiant( char* cni,char* Nom_prenom)
{
    etudiant *tmp = Liste_etudiant;
    etudiant *aide = NULL;
    if(tmp == NULL)
    {
        printf("Aucun etudiant n'est insere");
        viderTamponEntree();
        return ;
    }
    while(tmp != NULL)
    {
        if((strcmp(tmp->CIN, cni) == 0) && (strcmp(tmp->Nom_Prenom, Nom_prenom) == 0) )
        {
            printf("\nEtudiant existe !!!");
           if(tmp == Liste_etudiant)
           {
             Liste_etudiant = Liste_etudiant->suiv;
             free(tmp);
             tmp = NULL;
             printf("\nL'etudiant est supprime !!!");
              Nbr_etudiant--;
             viderTamponEntree();
            return;
           }
           else
           {
             aide = Liste_etudiant;

             while(aide->suiv!=tmp)
             { aide = aide->suiv;}

             aide->suiv = NULL;
             free(tmp);
             tmp = NULL;
             printf("\nL'etudiant est supprime !!!");
              Nbr_etudiant--;
             getchar();
             return;
           }

        }
        tmp = tmp->suiv;
    }
}

void supprimer_enseignant(char* CIN, char* nom_prenom) {
    enseignant* tmp_enseignant = Liste_enseignant;
    enseignant* prev_enseignant = NULL;
    enseignant* next_enseignant;

    while (tmp_enseignant != NULL) {
        if (strcmp(tmp_enseignant->CIN, CIN) == 0 && strcmp(tmp_enseignant->Nom_Prenom, nom_prenom) == 0) {
            next_enseignant = tmp_enseignant->suiv;
            free(tmp_enseignant->Nom_Prenom);
            free(tmp_enseignant->CIN);
            free(tmp_enseignant->Email);
            free(tmp_enseignant->nom_niveau);
            free(tmp_enseignant);
            if (prev_enseignant != NULL) {
                prev_enseignant->suiv = next_enseignant;
            } else {
                Liste_enseignant = next_enseignant;
            }
            Nbr_enseignant--;
            printf("\nL'enseignant avec le CIN \"%s\" et le nom et prénom \"%s\" est supprime.", CIN, nom_prenom);
            getchar();
            return;
        }

        prev_enseignant = tmp_enseignant;
        tmp_enseignant = tmp_enseignant->suiv;
    }

    printf("L'enseignant avec le CIN \"%s\" et le nom et prénom \"%s\" n'a pas ete trouve.\n", CIN, nom_prenom);
    getchar();
}

void supprimerEtudiantNiveau(char* nom_niveau) {
    etudiant* tmp_etudiant = Liste_etudiant;
    etudiant* prev_etudiant = NULL;
    etudiant* next_etudiant;

    while (tmp_etudiant != NULL) {
        if (strcmp(tmp_etudiant->nom_niveau, nom_niveau) == 0) {
            next_etudiant = tmp_etudiant->suiv;
            free(tmp_etudiant->Nom_Prenom);
            free(tmp_etudiant->CIN);
            free(tmp_etudiant->Email);
            free(tmp_etudiant->nom_niveau);
            free(tmp_etudiant);
            if (prev_etudiant != NULL) {
                prev_etudiant->suiv = next_etudiant;
            } else {
                Liste_etudiant = next_etudiant;
            }
            Nbr_etudiant--;
            tmp_etudiant = next_etudiant;
        } else {
            prev_etudiant = tmp_etudiant;
            tmp_etudiant = tmp_etudiant->suiv;
        }
    }
}

void supprimerEnseignantNiveau(char* nom_niveau) {
    enseignant* tmp_enseignant = Liste_enseignant;
    enseignant* prev_enseignant = NULL;
    enseignant* next_enseignant;

    while (tmp_enseignant != NULL) {
        if (strcmp(tmp_enseignant->nom_niveau, nom_niveau) == 0) {
            next_enseignant = tmp_enseignant->suiv;
            free(tmp_enseignant->Nom_Prenom);
            free(tmp_enseignant->CIN);
            free(tmp_enseignant->Email);
            free(tmp_enseignant->nom_niveau);
            free(tmp_enseignant);
            if (prev_enseignant != NULL) {
                prev_enseignant->suiv = next_enseignant;
            } else {
                Liste_enseignant = next_enseignant;
            }
            Nbr_enseignant--;
            tmp_enseignant = next_enseignant;
        } else {
            prev_enseignant = tmp_enseignant;
            tmp_enseignant = tmp_enseignant->suiv;
        }
    }
}

void supprimer_niveau() {
    niveau* tmp_niveau = Liste_niveau;
    niveau* prev_niveau = NULL;
    niveau* next_niveau;
    char* nom_niveau;
    viderTamponEntree();
    printf("Saisir le nom de niveau a supprimer:");
    nom_niveau = Allocation();

    while (tmp_niveau != NULL) {
        if (strcmp(tmp_niveau->Nom, nom_niveau) == 0) {
            supprimerEtudiantNiveau(nom_niveau);

            supprimerEnseignantNiveau(nom_niveau);

            next_niveau = tmp_niveau->suiv;
            free(tmp_niveau->Nom);
            free(tmp_niveau->horaire);
            free(tmp_niveau);
            if (prev_niveau != NULL) {
                prev_niveau->suiv = next_niveau;
            } else {
                Liste_niveau = next_niveau;
            }
            Nbr_niveau--;
            printf("\nLe niveau est supprime");
            return;
        }

        prev_niveau = tmp_niveau;
        tmp_niveau = tmp_niveau->suiv;
    }
    printf("Le niveau n'est pas insere!!");
}

void recherche_etudiant(char *cin,char *Nom_Prenom)
{
    etudiant *tmp = Liste_etudiant;
    while(tmp != NULL)
    {
        if(strcmp(tmp->CIN, cin) == 0 && strcmp(tmp->Nom_Prenom,Nom_Prenom) ==0)
        {
            Afficher_Etudiant(tmp);
        }
        tmp = tmp->suiv;
    }
    viderTamponEntree();
}

void recherche_enseignant()
{
    enseignant *tmp = Liste_enseignant;
    char *cin;
    char *Nom_Prenom;
    printf("saisir le nom_prenom d'enseignant:");
    Nom_Prenom = Allocation();
    printf("saisir CIN d'enseignant:");
    cin = Allocation();
    while(tmp != NULL)
    {
        if(strcmp(tmp->CIN, cin) == 0 && strcmp(tmp->Nom_Prenom,Nom_Prenom) ==0)
        {
            Afficher_Enseignant(tmp);
            getchar();
            return;
        }
        tmp = tmp->suiv;
    }
    printf("\n L'enseignant n'est pas insere!!!");
    viderTamponEntree();
}

void recherche_niveau() {
    niveau* tmp_niveau = Liste_niveau;
    char* nom_niveau;
    printf("saisir le nom de niveau a chercher:");
    nom_niveau = Allocation();
    while (tmp_niveau != NULL) {
        if (strcmp(tmp_niveau->Nom, nom_niveau) == 0) {
            Afficher_Niveau(tmp_niveau);
            return;
        }
        tmp_niveau = tmp_niveau->suiv;
    }
    printf("Le niveau \"%s\" n'a pas ete trouve.\n", nom_niveau);
}

void modification_etudiant(char* CIN)
{
   int choix,x=0;
   etudiant* tmp_etd = Liste_etudiant;
   etudiant* tmp = NULL;
   niveau* aide = Liste_niveau;

   while(tmp_etd!=NULL){
    if(strcmp(tmp_etd->CIN,CIN) == 0)
    {
        x++;
        tmp = tmp_etd ;
        break;
    }
    tmp_etd = tmp_etd->suiv ;
   }
   if(x == 0)
   {
       printf("\nCIN introuvable!!!");
       getchar();
       return ;
   }

   do{ clearConsole();
    printf("gestion modification etudiant:\n");
    printf("1.Modifier le nom_prenom:\n");
    printf("2.Modifier CIN:\n");
    printf("3.Modifier Email:\n");
    printf("4.Modifier le nom de niveau:\n");
    printf("5.Modifier le paiement:\n");
    printf("6.Retour\n");
    printf("Choix:");
    scanf("%d",&choix);
    clearConsole();

    switch (choix){

        case 1:printf("Modifier le nom_prenom:\n");

                tmp->Nom_Prenom = Allocation();
                printf("Nom_prenom ont bien ete modifie.\n");
                break;

         case 2:printf("Modifier CIN:\n");
                printf("saisir une CIN unique:");
                tmp->CIN = Allocation();
                printf("CIN modifie.\n");
                break;

         case 3: printf("Modifier Email:\n");

                tmp->Email = Allocation();
               printf("Email a bien ete change.\n");
                break;


         case 4:printf("Modifier le nom de niveau:\n");

                while(aide!=NULL)
                {
                    if(strcmp(aide->Nom,tmp->nom_niveau) == 0)
                    {
                        aide->nbr--;
                    }
                    aide= aide->suiv;
                }

                printf("saisir un niveau existe:");
                tmp->nom_niveau= Allocation();

               while(aide!=NULL)
                {
                    if(strcmp(aide->Nom,tmp->nom_niveau) == 0)
                    {
                        aide->nbr++;
                        printf("Niveau modifier");
                    }
                    aide= aide->suiv;
                }
         break;

         case 5: printf("Modifier le paiement:\n");

                scanf("%f",& tmp->paiement);
                printf("Paiement a bien ete modifier.");

        break;
        case 6:
        break;
        default:
        printf("choix invalide!!!");
        getchar();
    }
   }while(choix!=6);
}

void modification_enseignant(char* CIN)
{
   int choix,x = 0;
   enseignant* tmp_ens = Liste_enseignant;
   enseignant* tmp = NULL;
   niveau* aide = Liste_niveau;

   while(tmp_ens!=NULL){
    if(strcmp(tmp_ens->CIN,CIN) == 0)
    {
        x++;
        tmp = tmp_ens;
        break;
    }
    tmp_ens = tmp_ens->suiv ;
   }
   if(x == 0)
   {
       printf("\nCIN introuvable!!!");
       getchar();
       return ;
   }

   do{ clearConsole();
    printf("gestion modification enseignant:\n");
    printf("1.Modifier le nom_prenom:\n");
    printf("2.Modifier CIN:\n");
    printf("3.Modifier Email:\n");
    printf("4.Retour\n");
    printf("Choix:");
    scanf("%d",&choix);
    clearConsole();


    switch (choix){
    case 1:printf("Modifier Nom_prenom:\n");
                tmp->Nom_Prenom = Allocation();
                printf("Nom_prenom modifie.");
                break;

         case 2: printf("Modifier CIN:\n");

                printf("saisir une CIN unique:");
                tmp->CIN = Allocation();
                printf("CIN modifie.");
                break;
         case 3:printf("Modifier Email:\n");

                tmp->Email = Allocation();
                printf("Email modifie.");
                break;
        case 4:
        break;
        default:
        printf("choix invalide!!!");
        getchar();
    }
   }while(choix!=4);
}


niveau* rechercherNiveau(char* nom_niveau) {
    niveau* tmp_niveau = Liste_niveau;

    while (tmp_niveau != NULL) {
        if (strcmp(tmp_niveau->Nom, nom_niveau) == 0) {
            // Le niveau a été trouvé, renvoie le pointeur vers ce niveau
            return tmp_niveau;
        }
        tmp_niveau = tmp_niveau->suiv;
    }

    // Le niveau n'a pas été trouvé, renvoie NULL
    return NULL;
}

void modification_niveau(char* Nom)
{
   int choix;
   niveau* tmp = rechercherNiveau(Nom);

   if (tmp == NULL) {
    printf("Le nom de ce niveau n'existe pas ! \n");
    getchar();
    return;
   }
   do{ clearConsole();
    printf("gestion modification de niveau:\n");
    printf("1.Modifier le nom:\n");
    printf("2.Modifier l'horaire:\n");
    printf("3.Modifier la duree:\n");
    printf("4.Retour\n");
    printf("Choix:");
    scanf("%d",&choix);
    viderTamponEntree();
    clearConsole();

    switch (choix){
        case 1:
            printf("Modifier le nom:\n");
            printf("saisir un nom unique:");
            tmp->Nom = Allocation();
            printf("Le nom a bien ete change");
            getchar();
            break;
         case 2:
            printf("Modifier l'horaire:\n");
            tmp->horaire = Allocation();
            printf("L'horaire a bien ete change");
            getchar();
            break;
         case 3:
            printf("Modifier la duree:\n");
            scanf("%f",&tmp->Duree);
            printf("La duree a bien ete change");
            getchar();
            break;
        case 4:
            break;
        default:
            printf("choix invalide!!!");
            getchar();
    }
   }while(choix!=4);

}

void gestion_enseignant()
{
    if(Liste_niveau!=NULL)
    {
        int choix;
        char* CIN;
        char* NOM_PRENOM;

    do {
        clearConsole();
        printf("Page des enseignants:\n");
        printf("1.Ajout d'enseignant:\n");
        printf("2.Supprimer un enseignant:\n");
        printf("3.Afficher les enseignants:\n");
        printf("4.modifier un enseignant:\n");
        printf("5.recherche d'un enseignant:\n");
        printf("6.Nbr total des enseignants:\n");
        printf("7.Quitter\n");
        printf("Choix:");
        scanf("%d", &choix);
        viderTamponEntree();
        clearConsole();
        switch (choix) {
            case 1:
                //il faut saisir au moins un niveau avant
               if(Nbr_enseignant < Nbr_niveau)
               {
                 Ajout_Enseignant();
                 getchar();
                 clearConsole();
               }
               else
               {
                 printf("Nbr_niveau est limite:\n");
                 getchar();
               }
                break;
            case 2:
            printf("saisir Cin d'enseignant a supprimer:\n");
            CIN = Allocation();
            printf("saisir le nom_prenom de l'enseignant a supprimer:\n");
            NOM_PRENOM = Allocation();
            supprimer_enseignant(CIN,NOM_PRENOM);
            getchar();
                break;
            case 3:
                if(Liste_enseignant == NULL){
                    printf("Liste est vide!!");
                }
                else{
                    Afficher_Enseignants(Liste_enseignant);
                }
                getchar();
                break;
            case 4:
                printf("saisir Cin d'enseignant a modifier:\n");
                CIN = Allocation();
                modification_enseignant(CIN);
                break;
             case 5:
                 recherche_enseignant();
                 getchar();
                break;
            case 6:
                printf("Nbr total des enseignent : %d",Nbr_enseignant);
                getchar();
                break;
            case 7:
                break;
            default:
                printf("Choix invalide. Veuillez réessayer.\n");
                getchar();
        }
        printf("\n");
    } while (choix != 7);
    }
    else{
        printf("\nIl faut saisir au moins un niveau!!!");
        getchar();
    }
}

void gestion_niveau()
{
    int choix,x;
    char* Nom;
    do {clearConsole();
        printf("Page des niveaux:\n");
        printf("1.Ajout un niveau:\n");
        printf("2.Supprimer un niveau:\n");
        printf("3.Afficher les  niveaux:\n");
        printf("4.modifier un niveau:\n");
        printf("5.Recherche d'un niveau:\n");
        printf("6.Nbr totale des niveaux:\n");
        printf("7.Quitter\n");
        printf("Choix:");
        scanf("%d", &choix);
        viderTamponEntree();
        clearConsole();

        switch (choix) {
            case 1:
               if(Nbr_niveau <= 20)
               {
                 Ajout_Niveau();
               }
               else
               {
                 printf("Nbr_niveau est limite:\n");
               }
              getchar();
                break;
            case 2:

            if(Liste_niveau != NULL)
            {
                printf("si vous supprimer un niveau ses etudiants et son enseignant seront supprimes!!!\n");
                printf("pour valider votre choix saisir 1:");
                scanf("%d",&x);
            if(x == 1)
            {
               supprimer_niveau();
            }
            }
            else{
             printf("Aucun niveau n'est insere");
            }
            getchar();
                break;
            case 3:
                if(Liste_niveau == NULL)
                {
                    printf("Aucun niveau n'est insere!!");
                }
                else{
                    Afficher_Niveaux(Liste_niveau);
                }
                getchar();
                break;
            case 4:
                if(Nbr_niveau == 0){
                    printf("Aucun niveau n'est insere!!");
                    break;
                }
                 printf("saisir le nom de niveau a modifier:");
                 Nom = Allocation();
                 modification_niveau(Nom);
                break;
            case 5:
                recherche_niveau();
                getchar();
                break;
            case 6:
                printf("Le nbr totale des niveaux : %d",Nbr_niveau);
                viderTamponEntree();
                break;
            case 7:
                break;
            default:
                printf("Choix invalide. Veuillez réessayer.\n");
                viderTamponEntree();
        }
        printf("\n");
    } while (choix != 7);
}

void gestion_des_etudiants()
{

    if(Liste_niveau != NULL)
    {   char* CIN;
        char* NOM_PRENOM;
        int choix;
    do {
        clearConsole();
        printf("Page des etudiants:\n");
        printf("1.Ajout un etudiant:\n");
        printf("2.Supprimer un etudiant:\n");
        printf("3.Afficher les etudiant:\n");
        printf("4.modifier un etudiant:\n");
        printf("5.Recherche d'un etudiant:\n");
        printf("6.Nbr totale des etudiants:\n");
        printf("7.Quitter\n");
        printf("Choix:");
        scanf("%d", &choix);
        clearConsole();

        switch (choix) {
            case 1:
               Ajout_Etudiant();
               viderTamponEntree();
                break;
            case 2:
            viderTamponEntree();
            printf("saisir Cin d'enseignant a supprimer:\n");
            CIN = Allocation();
            printf("saisir le nom_prenom de l'enseignant a supprimer:\n");
            NOM_PRENOM = Allocation();
            supprimer_etudiant(CIN,NOM_PRENOM);
            viderTamponEntree();
                break;
            case 3:
                if(Liste_etudiant == NULL)
                {
                    printf("Aucun etudiant n'est insere");
                    viderTamponEntree();
                }
                else{
                    Afficher_Etudiants(Liste_etudiant);
                    viderTamponEntree();
                }

                break;
            case 4:
                printf("saisir Cin d'etudiant a modifier:\n");
                CIN = Allocation();
                modification_etudiant(CIN);
                viderTamponEntree();
                break;
            case 5:
                viderTamponEntree();
                printf("saisir le nom_prenom d'etudiant:\n");
                NOM_PRENOM = Allocation();
                printf("saisir CIN d'etudiant:\n");
                CIN= Allocation();
                recherche_etudiant(CIN,NOM_PRENOM);
                viderTamponEntree();
                break;
            case 6:
                printf("Le nbr totale des etudiants : %d",Nbr_etudiant);
                viderTamponEntree();
                break;

            case 7:
                break;
            default:
                printf("Choix invalide. Veuillez réessayer.\n");
                viderTamponEntree();
        }
        printf("\n");
    } while (choix != 7);
    }
    else{
        printf("\nil faut saisir au moins un niveau");
        viderTamponEntree();
    }
}

void gestion_de_paiements()
{
    int choix;

    do{ clearConsole();
        printf("Page de paiement:\n");
        printf("1.Afficher les paiement complet:\n");
        printf("2.Afficher les paiement incomplet:\n");
        printf("3.Retour\n");
        printf("Choix:");
        scanf("%d", &choix);
        clearConsole();

        switch (choix) {
            case 1:
            if(Liste_etudiant == NULL){
            printf("Aucun etudiant n'est insere!!");}

            else{
            printf("Les etudiants a paiement complet:\n");
            Paiement_Complet(Liste_etudiant);}
            viderTamponEntree();
                break;
            case 2:
            if(Liste_etudiant == NULL){
            printf("Aucun etudiant n'est insere!!");}
            else{
                 printf("Les etudiants a paiement incomplet:\n");
                 Paiement_Incomplet(Liste_etudiant);
            }
            viderTamponEntree();
                break;
            case 3:
                break;
            default:
                printf("Choix invalide. Veuillez reessayer.\n");
                viderTamponEntree();
        }
        printf("\n");

    } while (choix != 3);
}

void main()
{
    int choix;
    do {
        printf("Page de gestion:\n");
        printf("1.Gestion de niveau:\n");
        printf("2.Gestion d'enseignant:\n");
        printf("3.Gestion des etudiants:\n");
        printf("4.Gestion de paiements:\n");
        printf("5.Quitter\n");
        printf("Choix:");
        scanf("%d", &choix);
        clearConsole();

        switch (choix) {
            case 1:
                gestion_niveau();
                break;
            case 2:
               gestion_enseignant();
                break;
            case 3:
               gestion_des_etudiants();
                break;
            case 4:
               gestion_de_paiements();
                break;
            case 5:
                printf("Au revoir !\n");
                break;
            default:
                printf("Choix invalide. Veuillez réessayer.\n");
        }
        printf("\n");

    } while (choix != 5);
}