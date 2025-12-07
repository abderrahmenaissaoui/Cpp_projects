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

    virtual ~ecole(){
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
            "Élèves de 1ère année = %i\n"
            "Élèves de 2éme année = %i\n"
            "Élèves de 3éme année = %i\n"
            "Élèves de 4éme année = %i\n"
            "Élèves de 5éme année = %i\n"
            "Élèves de 6éme année = %i\n",
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
            cout << "nombre d'étudiants de niveau numéro" << i+1 << " = " << eleve[i] << endl;
        }
    }

    //view avec virtual (dynamic binding)
    virtual void view_virtual(){
        cout << "--------------affichage école -------------" << endl;
        cout << "nom = " << nom << endl;
        cout << "adresse = " << adresse << endl;
        cout << "nombre d'enseignants= " << ne << endl;
        for( int i= 0 ; i < 6 ; i++){
            cout << "nombre d'étudiants de niveau numéro " << i+1 << " = " << eleve[i] << endl;
        }
    }
};

class ecole_privee : public ecole
{
    char * gerant;
    float capital;
    public:
    ecole_privee(char *n=nullptr,char * a=nullptr, int ne=0,int* eleve=nullptr, char * g=nullptr, float c=0):ecole(n,a,ne,eleve){
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
    void view() {
        ecole::view();
        cout << "Gérant = " << gerant << endl;
        cout << "capital = " << capital << endl;
    }

    void view_virtual() override{
        ecole::view_virtual();
        cout << "Gérant = " << gerant << endl;
        cout << "capital = " << capital << endl;
    }
};

int main() {
     int tab1[6] = {20, 25, 30, 22, 18, 15};
    int tab2[6] = {10, 11, 12, 13, 14, 15};
    char* temp = new char[256];
    
    ecole *e1 = new ecole{"aschool", "Tunis", 25, tab1};
    e1->view();
    cout << "\n-----------test operator char*-----------\n";
    strcpy(temp,e1->operator char *());
    for (size_t i = 0 ; i < strlen(temp); i++){
        cout << temp[i];
    }
    
    ecole *e2 = new ecole_privee{"Prive Excellence","Tunis",20,tab2,"Mr.Houssem",5000.5};
    cout << "\n-----------------------------------------\n";
    cout << "sans utiliser virtual: " << endl;
    e2->view();
    cout << "en utilisant virtual: " << endl;
    e2->view_virtual();
    cout << "\n-----------test operator char*-----------\n";
    strcpy(temp,e2->operator char *());
    for (size_t i = 0 ; i < strlen(temp); i++){
        cout << temp[i];
    }
    cout << "\n-----------------------------------------\n";
    
    cout<<"\n-------------test operator +-------------\n"<<endl;
    ecole *e3 = new ecole{*e1+*e2};

    ++(*e3);
    (*e3)++;
    cout << "-----------------------------------------";
    e3->view();
    cout << "\n-----------------------------------------\n";
    
    try{
        ecole *e4 = new ecole{"aschool", "Tunis", -25, tab1};
    }
    catch(int n){
        cout << "erreur numéro " << n << endl;
    }

    cout << "\n-----------------------------------------\n";
    
    try{
        int tab3[6] = {20, 25, 30, -22, 18, 15};
        ecole *e5 = new ecole{"aschool", "Tunis", 25, tab3};
    }
    catch( int n){
        cout << "erreur numéro " << n << endl;
    }


    delete e1;
    delete e2;
    delete e3;
    delete [] temp;

    return 0;
}
