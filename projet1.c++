#include <iostream>
#include <string.h>
using namespace std;

class ecole
{
    char * nom;
    char * adresse;
    int ne;
    int* eleve;

    public:
    ecole(char *n=nullptr,char * a=nullptr, int ne=0,int* eleve=nullptr){
        if(ne < 0)
            throw 1;

        if(n){
            nom= new char[strlen(n)+1];
            strcpy(nom,n);
        }
        else  nom=nullptr;

        if(a){
            adresse= new char[strlen(a)+1];
            strcpy(adresse,a);
        }
        else
            adresse=nullptr;

        this->ne =ne;

        this->eleve = new int[6];
        if(eleve){
            for(int i=0;i<6;i++){
                if(eleve[i]<0){
                    delete [] this->eleve;
                    if(nom) delete[] nom;
                    if(adresse) delete[] adresse;
                    throw 1;
                }
                this->eleve[i]=eleve[i];
            }
        }
        else{
            for(int i=0;i<6;i++){
                this->eleve[i]=0;
            }
        }

    }

    ecole(const ecole& e)
    {
        cout << "constructeur par recopie"<<endl;
        if(e.nom){
            nom=new char[strlen(e.nom)+1];
            strcpy(nom,e.nom);
        }
        else{
            nom=nullptr;
        }
        if(e.adresse){
            adresse=new char[strlen(e.adresse)+1];
            strcpy(adresse,e.adresse);
        }
        else adresse=nullptr;
        ne=e.ne;
        eleve=new int[6];
        memcpy(eleve,e.eleve, sizeof(int)*6);
    }
    ~ecole(){
        delete [] nom;
        delete [] adresse;
        delete [] eleve;
    }
    char* get_nom(){
        return nom; 
    }
    int get_eleve_niveau(int niveau)
    {
        if(niveau<6 && niveau>=0)
            return eleve[niveau];
    }

    
    ecole& operator++(){
        ne++;
        return *this;
    }
    
    //post-increment (ecole++)
    ecole operator++(int){
        ecole e=*this;
        ne ++;
        return e; 
    }

    ecole operator +(const ecole& e){
        cout << "enter name = ";
        char * name = new char[50];
        cin >> name;
        cout <<"enter adresse = ";
        char * adr=new char[100];
        cin >> adr;
        int nbe = ne+e.ne;
        int * students = new int[6];
        for(int i=0; i < 6; i++)

        {
            students[i] = e.eleve[i] + eleve[i];
        }
        ecole ecoleFusion(name,adr,nbe,students);
        delete [] name;
        delete [] adr;
        delete [] students;
        return ecoleFusion;
    }

    operator char*()
    {
        char *ecole_char = new char[800];
        sprintf(ecole_char, "nom:%s\nAdresse:%s\nnombre d'enseignants: %i\n" 
            "Élèves de 1ère année = %i"
            "Élèves de 2éme année = %i"
            "Élèves de 3éme année = %i"
            "Élèves de 4éme année = %i"
            "Élèves de 5éme année = %i"
            "Élèves de 6éme année = %i",
            nom ? nom : "sans nom",
            adresse?adresse:"sans adresse",
            ne,
            eleve[0],eleve[1],eleve[2],eleve[3],eleve[4],eleve[5]
        );
        return ecole_char;
    }

    //view basique (static binding)
    void view(){
        cout << "--------------affichage école -------------" << endl;
        cout << "nom = " << nom << endl;
        cout << "adresse = " << adresse << endl;
        cout << "nombre d'enseignants= " << ne << endl;
        for( int i= 0 ; i < 6 ; i++){
            cout << "nombre d'étudiants de niveau numéro" << i << endl;
        }
    }

    //view avec virtual (dynamic binding)
    virtual void view_virtual(){
        cout << "--------------affichage école -------------" << endl;
        cout << "nom = " << nom << endl;
        cout << "adresse = " << adresse << endl;
        cout << "nombre d'enseignants= " << ne << endl;
        for( int i= 0 ; i < 6 ; i++){
            cout << "nombre d'étudiants de niveau numéro" << i << endl;
        }
    }
};

class ecole_privee : public ecole
{
    char * gerant;
    float capital;
    public:
    ecole_privee(char *n=nullptr,char * a=nullptr, int ne=0,int* eleve=nullptr, char * g, float c):ecole(n,a,ne,eleve){
        if(g)
        {
            gerant = new char[strlen(g)+1];
            strcpy(gerant, g);
        }
        else 
            gerant = nullptr;
        capital=c;
    }

   
    operator char *(){
        char * ecole_privee_char = ecole::operator char *();
        
        char * extra_privee;
        sprintf(extra_privee, "\nGérant: %s\nCapital: %f \n",
                gerant ? gerant : "Sans gérant",
                capital);
        strcat(ecole_privee_char, extra_privee);
        
        return ecole_privee_char;
    }

    void view_virtual() override{
        ecole::view_virtual();
        cout << "Gérant = " << gerant << endl;
        cout << "capital = " << capital << endl;
    }
};

int main(){
    ecole e;
    ecole e1=e;
}