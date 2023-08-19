#include <iostream>
using namespace std;

//Mini analizador léxico

#include <cstdlib>
#include <string>

class TipoSimbolo{
public:
	static const int ERROR= -1;       
	static const int IDENTIFICADOR= 0;
	static const int OPADIC= 1;
	static const int OPMULT= 2;
	static const int PESOS= 3;       
	static const int ENTERO= 4;
};

class Lexico{
private:
	string fuente;
	
	int ind;       
	bool continua;
	char c;
	int estado;
	
	char sigCaracter();       
	void sigEstado(int estado);
	void aceptacion(int estado);
	bool esLetra(char c);
	bool esDigito(char c);
	bool esEspacio(char c);
	void retroceso();
	
public:
	string simbolo;
	int tipo;
	
	Lexico(string fuente);             
	Lexico();
	
	void entrada(string fuente);              
	string tipoAcad(int tipo);
	
	int sigSimbolo();
	bool terminado();
	
};

Lexico::Lexico(string fuente){
	ind= 0;                  
	this->fuente= fuente;
}      

Lexico::Lexico(){
	ind= 0;                  
}      

string Lexico::tipoAcad(int tipo){
	string cad= "";
	
	switch (tipo){
	case TipoSimbolo::IDENTIFICADOR:
		cad= "Identificador";
	break;
	
	case TipoSimbolo::OPADIC:
		cad= "Op. Adicion";
	break;
	
	case TipoSimbolo::OPMULT:
		cad= "Op. Multiplicacion";
	break;            
	
	case TipoSimbolo::PESOS:
		cad= "Fin de la Entrada";
	break;            
	
	case TipoSimbolo::ENTERO:
		cad= "Entero";
	break;
	
	}
	
	return cad;
}

void Lexico::entrada(string fuente){
	ind= 0;                  
	this->fuente= fuente;
}

int Lexico::sigSimbolo(){
	
	estado=0;
	continua= true;
	simbolo= "";
	
	//Inicio del Automata
	while (continua){
		c= sigCaracter();
		
		switch (estado){
		case 0:
			if ( c == '+' || c=='-') aceptacion(2);
			else
				if ( c == '$' ) aceptacion(3);
			
			break;
			
		}  
		
	}    
	//Fin del Automata
	
	switch (estado){
		
	case 2:
		tipo= TipoSimbolo::OPADIC;
		break; 
		
		
	default:                 
		tipo= TipoSimbolo::ERROR;
	}
	
	return tipo;
}

char Lexico::sigCaracter(){
	if (terminado()) return '$';
	
	return fuente[ind++];
}

void Lexico::sigEstado(int estado){
	this->estado= estado;
	simbolo+= c;
}

void Lexico::aceptacion(int estado){
	sigEstado(estado);
	continua= false;
}

bool Lexico::terminado(){//fin de cadena
	return ind >= fuente.length();
}

bool Lexico::esLetra(char c){
	return isalpha(c) || c=='_';
}


bool Lexico::esDigito(char c){
	return isdigit(c);
}

bool Lexico::esEspacio(char c){
	return c== ' ' || c== '\t';        
}


void Lexico::retroceso(){
	if ( c != '$') ind--;
	continua= false;
}

int main(int argc, char *argv[]){
	

	
	char cad[200];
	cout << "Ingrese cadena: " << endl;
	cin.getline(cad, 200, '\n');
	
	Lexico lexico;
	lexico.entrada(cad);
	
	cout << "Resultado del Analisis Lexico" << endl << endl;
	cout << "Simbolo\t\tTipo" << endl;
	
	while ( lexico.simbolo.compare("$") != 0 ){
		lexico.sigSimbolo();
		
		cout <<  lexico.simbolo << "\t\t" << lexico.tipoAcad(lexico.tipo) << endl;          
	}
	
	cin.get();
	
	return 0;
}
	


	
	

