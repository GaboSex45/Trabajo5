//Video
//https://youtu.be/QXyr9273Xrs
//https://youtu.be/QXyr9273Xrs
//Video

#include <string>
#include <iostream>
#include <cstring>

using namespace std;

typedef struct nodo{

    string dato;
    int frecuencia;
    nodo *izq;
    nodo *der;

}Nodo;

typedef Nodo * AB;


typedef struct estructura{

    char letra;
    AB Arbolito;
    int cantidad;

}Estructura[27];


void BuscarPalabras(AB &,string);
void BuscarPalabrasIni(Estructura &);
void printBT(const std::string&, AB &, bool );
void printBT(AB &);
Nodo  *CrearNodo(string);
void Incializar(Estructura &);
void Agregar(AB &, string);
void AgregarAlDiccionario(Estructura &);
void repetidos(AB &);
void RecorrerRepetidos(Estructura &);




AB FindMin(AB &root)
{
	while(root->izq != NULL) root = root->izq;
	return root;
}


struct nodo* Delete(AB &root, string data) {
	if(root == NULL) return root; 
	else if(data < root->dato) root->izq = Delete(root->izq,data);
	else if (data > root->dato) root->der = Delete(root->der,data);
	
	else {
		// caso 1:  Sin Hijos
		if(root->izq == NULL && root->der == NULL) { 
			delete root;
			root = NULL;
		}
		//caso 2: un hijo 
		else if(root->izq == NULL) {
			struct nodo *temp = root;
			root = root->der;
			delete temp;
		}
		else if(root->der == NULL) {
			struct nodo *temp = root;
			root = root->izq;
			delete temp;
		}
		// caso 3: Tiene 2 hijos
		else { 
			struct nodo *temp = FindMin(root->der);
			root->dato = temp->dato;
			root->der = Delete(root->der,temp->dato);
		}
	}
	return root;
}


void Borrar(Estructura &MiDiccionario){
    string eliminarpalabra;
    cout<<"Ingrese una palabra para eliminar: ";
    cin>>eliminarpalabra;
    cout<<endl;
    
    for(int i=0; i<27; i++){
        if(MiDiccionario[i].letra == eliminarpalabra[0]){
        Delete(MiDiccionario[i].Arbolito,eliminarpalabra);
        
        break;
        }
        
    }
    
    
}



void BuscarPalabras(AB &Tree,string Buscada){
    
    
        char * cstr1 = new char [Buscada.length()+1];
        strcpy(cstr1, Buscada.c_str());

        char * cstr2 = new char [Tree ->dato.length()+1];
        strcpy(cstr2, Tree ->dato.c_str());
    
    if(Tree == NULL){
        
        
    }
    
    
    
    else if(Tree ->dato == Buscada){
        cout<< "La palabra " << Tree ->dato <<" se repite : "<<Tree ->frecuencia <<endl;
       
    }

    else if(strcmp(cstr1,cstr2)>0){
                
             BuscarPalabras(Tree ->izq,Buscada);
            }

    else if (strcmp(cstr1,cstr2)<0){
              BuscarPalabras(Tree ->der,Buscada);  
                   
            }
    else{
        cout<<"La palabra no se encuentra en el arbol"<<endl;
    }
    
    
}


void BuscarPalabrasIni(Estructura &MiDiccionario)
{
    string Palabra;
    cout<<"Ingrese una palabra que quiera buscar:"<<endl;
    cin>>Palabra;
    
    for(int i = 0; i<27; i++ ){
        if(MiDiccionario[i].letra == Palabra[0]){
            BuscarPalabras(MiDiccionario[i].Arbolito,Palabra);
            break;
        }
        
        
    }
}





void printBT(const std::string& prefix,  AB &node, bool isLeft)
{
    
    
    if( node != nullptr )
    {
        std::cout << prefix;

        std::cout << (isLeft ? "├──" : "└──" );

        // print the value of the node
        std::cout << node->dato <<"->"<<node -> frecuencia << std::endl;

        // enter the next tree level - left and right branch
        printBT( prefix + (isLeft ? "│   " : "    "), node->der, true);
        printBT( prefix + (isLeft ? "│   " : "    "), node->izq, false);
    }
}

void printBT(AB &node)
{
    printBT("", node, false);    
}


Nodo  *CrearNodo(string Dato_Ingresado){

        Nodo *nodo = new Nodo();
        nodo -> dato = Dato_Ingresado;
        nodo -> frecuencia = 1;
        nodo -> izq = NULL;
        nodo -> der = NULL;
        return nodo;

}


void Incializar(Estructura &Diccionario){

    cout<<"Inicializando diccionario ..."<<endl;


    for(int i = 0, j = 97; i<28 && j<124;i++, j++){

        Diccionario[i].letra = char(j);
        Diccionario[i].Arbolito = NULL;
        Diccionario[i].cantidad = 0;

        cout<<"Asignando Letra "<<Diccionario[i].letra<<" a la posicion "<<i<<endl;
    }

    cout<<"Diccionario Inicializado..."<<endl;
}




void Agregar(AB &Tree, string Dato_Ingresado){

    if(Tree == NULL){

        Nodo *nodo = CrearNodo(Dato_Ingresado);
        Tree = nodo;
        cout<<Dato_Ingresado<<" Ingresado con exito"<<endl;
    }

    else {
            if(Tree -> dato == Dato_Ingresado){
        
            Tree -> frecuencia += 1;
        
            }
        
        
        
            else{
            char * cstr1 = new char [Dato_Ingresado.length()+1];
            strcpy(cstr1, Tree -> dato.c_str());

            char * cstr2 = new char [Tree -> dato.length()+1];
            strcpy(cstr2, Dato_Ingresado.c_str());

            if(strcmp(cstr1,cstr2)<0){
                cout<<"Ingresando "<<cstr2<<" Por el lado izquierdo de "<<cstr1<<endl;
                Agregar (Tree -> izq, Dato_Ingresado);
            }

            else{
                cout<<"Ingresando "<<cstr2<<" Por el lado derecho de "<<cstr1<<endl;
                Agregar (Tree -> der, Dato_Ingresado);
            }

            }
        }
}

void AgregarAlDiccionario(Estructura &MiDiccionario)
{
    string Palabra;
    cout<<"Ingrese una palabra"<<endl;
    cin>>Palabra;
    
    for(int i = 0; i<27; i++ ){
        if(MiDiccionario[i].letra == Palabra[0]){
            Agregar(MiDiccionario[i].Arbolito,Palabra);
            break;
        }
        
    }
}

void repetidos(AB &Tree){
    

    
    
    if (Tree == NULL){
        return;
        
    }
    
    else{
        if(Tree -> frecuencia > 1){
        cout<<"-> "<<Tree ->dato<<" se repite "<<Tree ->frecuencia<<" veces"<<endl;  
        }
        
        
        
        repetidos(Tree -> izq);
        repetidos(Tree -> der);
        
        
    }
    
    
}


int main()
{
    Estructura MiDiccionario;
    AB BinaryTree = NULL;


    
    
    
    
    
    int opcion;
    bool repetir = true;
    
    do {
        
        cout << "\n\nMenu de Opciones" << endl;
        cout << "1. Inicializar diccionario" << endl;
        cout << "2. Agregar una palabra en el diccionario" << endl;
        cout << "3. Eliminar una palabra contenida en el diccionario" << endl;
        cout << "4. Mostrar toda la información del diccionario" << endl;
        cout << "5. Buscar  la  información  de  una  palabra" << endl;
        cout << "6. Mostrar todas las palabras repetidas" << endl;
        cout << "0. SALIR DE EL PROGRAMA" << endl;
        
        cout << "\nIngrese una opcion: ";
        cin >> opcion;
        
        switch (opcion) {
            case 1:
                system("cls||clear");
                
                Incializar(MiDiccionario);                
                
                
                break;
                
            case 2:
                system("cls||clear");
                
                if(MiDiccionario[0].letra == 'a'){
                AgregarAlDiccionario(MiDiccionario);
                }
                
                else{
                    cout<<"Inicialize el Diccionario antes de continuar"<<endl;
                }
                
                
                break;
                
            case 3:
                system("cls||clear");
                
                if(MiDiccionario[0].letra == 'a'){
                Borrar(MiDiccionario);
                }
                
                else{
                    cout<<"Inicialize el Diccionario antes de continuar"<<endl;
                }
                
                         
                break;
                
            case 4:
                system("cls||clear");
                if(MiDiccionario[0].letra == 'a'){
                for (int i = 0; i<26; i++){
                    
                        cout<<MiDiccionario[i].letra<<endl;
                        printBT(MiDiccionario[i].Arbolito); 
                    }
                
                
                }
                
                else{
                    cout<<"Inicialize el Diccionario antes de continuar"<<endl;
                }
                                
                break;
        
            case 5:
                system("cls||clear");
                
                if(MiDiccionario[0].letra == 'a'){
                
                    
                BuscarPalabrasIni(MiDiccionario);
                }
                else{
                    cout<<"Inicialize el Diccionario antes de continuar"<<endl;
                }
                break;
                
            case 6:
                system("cls||clear");
                if(MiDiccionario[0].letra == 'a'){
                for(int i =0; i<27; i++){
                  repetidos(MiDiccionario[i].Arbolito);  
                }
                
                }
                
                else{
                    cout<<"Inicialize el Diccionario antes de continuar"<<endl;
                }
                break;

                                
                break;

            
            case 0:
            	repetir = false;
            	break;
        }        
    } while (repetir);



    return 0;
}













