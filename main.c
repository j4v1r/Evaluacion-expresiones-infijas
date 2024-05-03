/*
AUTOR: Edgardo Adri√°n Franco Mart√≠nez (C) Noviembre 2022
VERSI√ìN: 1.5

DESCRIPCI√ìN: Ejemplo de la aplicaci√≥n de la pila, 
el cu√°l resuelve el problema de la evaluacione de los 
parentesis escritos de manera correcta en una expresi√≥n.

OBSERVACIONES: Se emplea la libreria pila_est.h o pila_din.h implementadas
en clase. Ambas estructuras elemento, ya sea la de la implementaci√≥n est√°tica o din√°mica deber√°n tener un campo char c;

COMPILACI√ìN: 	gcc -o EvaluaParentesis EvaluaParentesis.c pila_(din|est).o (Si se tiene el objeto de la implementaci√≥n)
				gcc -o EvaluaParentesis EvaluaParentesis.c pila_(din|est).c (Si se tiene el fuente de la implementaci√≥n)

EJECUCI√ìN: EvaluaParentesis.exe (En Windows) - ./EvaluaParentesis (En Linux)
*/
/*
main.c
V 1.0 Mayo 2024
Grupo: 2CM2
Autores: Colunga Aguilar Javier Alejandro
		 V·squez AndrÈs Rajiv Eduardo

Programa que define las funciones que fueron declaradas en "TADPilaEst.h"

CompilaciÛn:
gcc main.c TADPila(Est/Din).c -o expinfijas (Dependiendo si se desea usar una pila Est·tica o Din·mica)

EjecuciÛn:
expinfijas.exe
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "TADPilaEst.h"
int evaluar_parentesis(char cadena[], int tam_cadena, pila *s);
int conversion_posfijo(char cadena[], int tam_cadena, char resultado[]);
int operador_potencia(char operador, char top, pila *s, char resultado[], int j, elemento aux);

int operador_suma_resta(char operador, char top, pila *s, char resultado[], int j, elemento aux);

int main(){
	char cadena[100], aux;
	int i,tam_cadena, num_parentesis, tam_resultado;
	pila mi_pila;
	
	Initialize(&mi_pila);
	
	scanf("%s",cadena);
	
	tam_cadena=strlen(cadena);
	
	num_parentesis = evaluar_parentesis(cadena, tam_cadena, &mi_pila);
	
	tam_resultado=tam_cadena-(num_parentesis*2);
	printf("\nEl tamano del resultado es %i", tam_resultado);
	char resultado[tam_resultado];
	
	tam_resultado=conversion_posfijo(cadena, tam_cadena, resultado);
	
	//printf("\nEl tamano del resultado es %i", tam_resultado);
	
	printf("\nLa expresion posfija es: %s", resultado);
	
	
	printf("\n-----Imprimiendo Cadena Posfija----");
	for(i=0;i<tam_cadena-(num_parentesis*2);i++){
		printf("\n%c",resultado[i]);
	}
	
	Destroy(&mi_pila);
	return 0;
}

int evaluar_parentesis(char cadena[], int tam_cadena,  pila *s){
	
	int i, num_parentesis=0;
	elemento e1;
	
	for(i=0;i<tam_cadena;i++){
		if(cadena[i]=='('){
			e1.c=cadena[i];
			Push(s,e1);
			num_parentesis++;
			//printf("El elemento top es: %c\n", Top(&mi_pila));
		}else if(cadena[i]==')'){
			if(Empty(s))
			{
				printf("\nExpresion no valida, intentas cerrar expresiones que no aperturaron"),
				exit(1);
			}
			else
			{
				e1=Pop(s);
			}
		}
	}
	
	
	if(Empty(s)){
		printf("\nExpresion valida");
	}
	else{
		printf("\nExpresion no valida, hay expresiones que no han cerrado");
		exit(1);
	}
	
	//printf("\nTamanio de pila antesde salir=%d",Size(s));
	
	return num_parentesis;
}


int conversion_posfijo(char cadena[], int tam_cadena, char resultado[]){
	
	int i, j=0, valor, tam_pila, tam;
	pila s;
	elemento aux;
	char top;
	printf("\nEl tamano INICIAL del resultado es: %i", strlen(resultado));
	printf("\n La cadena INICIAL es: %s", resultado);
	
	Initialize(&s);
	
	for(i=0;i<tam_cadena;i++){
		printf("\nEl elemento es: %c", cadena[i]);
		
		//Condicional que revisa el tipo de caracter que se est· revisando
		
		if(cadena[i]=='('){
			//El caracter es un parentÈsis de apertura, por lo que se guarda en la pila autom·ticamente
			aux.c=cadena[i];
			Push(&s, aux);
		}
		else if(cadena[i]==')')
		{
			for(int i=1; i<=Size(&s); i++){
				printf("El elemento %i de la pila es: %c\n", i, Element(&s, i));
			}
			//El caracter es un parentÈsis de cierre, por lo que se vacia la pila hasta encontrar uno de apertura
			printf("\nLa cadena Al ENCONTRAR PARENTESIS DE CERRAR HASTA arriba es: %c", Top(&s).c);
			do{
				top=Pop(&s).c;
				resultado[j]=top;
				j++;
				printf("\n La cadena es: %s", resultado);
				printf("\nLa cadena Al Entar al while HASTA arriba es: %c", Top(&s).c);
			}while(Top(&s).c!='(');
			
			
			printf("\nLa cadena DESPUES DE Salir del while HASTA arriba es: %c", Top(&s).c);
			
			if(Size(&s)==1){
				Pop(&s);
				s.tope=Size(&s);
			}else{
				Pop(&s);
				Pop(&s);
				s.tope=Size(&s);
			}
			
			printf("\nLa cadena DESPUES DE CERRAR PARENTESIS HASTA arriba es: %c", Top(&s).c);
			printf("\nEl tamano de la pila es: %i", Size(&s));
			
		}else if(cadena[i]>='A' && cadena[i]<='Z'){
			
			//El caracter es un operando, por lo que se agrega directamente a la cadena de la expresiÛn posfija
			resultado[j]=cadena[i];
			j++;
			printf("\nJ es: %i", j);
			printf("\nEl tamano del resultado es: %i", strlen(resultado));
			printf("\n La cadena es: %s", resultado);
		}else{
			
			//El caracter es un operador, por lo que dependiendo su jerarquÌa se decide quÈ hacer
			
			printf("\nEntra a comparacion de operadores");
			printf("\nEl tope de la pila es: %i", s.tope);
			printf("\nLa cadena Al Pasar al siguiente elemento HASTA arriba es: %c", Top(&s).c);
			/*El char "top" es el del tope en la pila y con base en este se decide quÈ hacer
			con el operador actual*/
			top=Top(&s).c;
			/*El elemento "aux" define el elemento que se agregara a la pila*/
			aux.c=cadena[i];
			
			printf("\nEl operador es: %c", cadena[i]);
			
			for(int i=1; i<=Size(&s); i++){
				printf("El elemento %i de la pila es: %c\n", i, Element(&s, i));
			}
			
			if(cadena[i]=='^'){	
			
				//El operador es una potencia por lo que entra a la toma de decisiÛn de potencia
				printf("\nEntra a comparacion de POTENCIA");
				j+=operador_potencia(cadena[i], top, &s, resultado, j, aux);
				
			}else if(cadena[i]=='*' || cadena[i]=='/'){
				printf("\nEntra a comparacion de MULT/DIV");
				if(top=='*' || top=='/'){
					resultado[j]=Pop(&s).c;
					j++;
					printf("\nJ es: %i", j);
					printf("\nEl tamano del resultado es: %i", strlen(resultado));
					printf("\n La cadena es: %s", resultado);
					Push(&s, aux);
				}else if(top=='^'){
					resultado[j]=Pop(&s).c;
					j++;
					printf("\nJ es: %i", j);
					printf("\nEl tamano del resultado es: %i", strlen(resultado));
					printf("\n La cadena es: %s", resultado);
					top=Top(&s).c;
					if(top=='*' || top=='/'){
						resultado[j]=Pop(&s).c;
						j++;
						printf("\nJ es: %i", j);
						printf("\nEl tamano del resultado es: %i", strlen(resultado));
						printf("\n La cadena es: %s", resultado);
						Push(&s, aux);
					}else{
						Push(&s, aux);
					}
				}else{
					Push(&s, aux);
				}
				printf("\nEl caracter hasta arriba es: %c", Top(&s).c);
			}else{
				printf("\nEntra a comparacion de SUMA/RESTA");
				j+=operador_suma_resta(cadena[i], top, &s, resultado, j, aux);
				printf("\nLa cadena hasta arriba es: %c", Top(&s).c);
			}
		}
	}
	
	//printf("\n-----Sacando operadores----");
	tam_pila=s.tope;
	printf("\nEl tamano de la pila es: %i", tam_pila);
	printf("\nJ ANTES DE VACIAR LA PILA es: %i", j);
	printf("\nEl tamano del resultado ANTES DE VACIAR LA PILA: %i", strlen(resultado));
	printf("\n La cadena ANTES DE VACIAR LA PILA ES: %s", resultado);
	if(tam_pila>0){
		for(i=0;i<tam_pila;i++){
			top=Pop(&s).c;
			//printf("\n%c", top);
			resultado[j]=top;
			j++;
			printf("\nJ es: %i", j);
			printf("\nEl tamano del resultado AL VACIAR LA PILA: %i", strlen(resultado));
			printf("\n La cadena es: %s", resultado);
		}
	}
	
	printf("\nEl tamano del resultado al final es: %i", strlen(resultado));
	printf("\n La cadena es: %s", resultado);
	tam=strlen(resultado);
	return tam;
}




int operador_potencia(char operador, char top, pila *s, char resultado[], int j, elemento aux){
	int contador=0;
	if(top=='^'){
		resultado[j]=Pop(s).c;
		j++;
		contador++;
		printf("\nJ es: %i", j);
		printf("\nEl tamano del resultado es: %i", strlen(resultado));
		printf("\n La cadena es: %s", resultado);
		Push(s, aux);
	}else{
		Push(s, aux);
	}	
	
	printf("\nEl caracter hasta arriba es: %c", Top(s).c);
	
	return contador;
}



int operador_suma_resta(char operador, char top, pila *s, char resultado[], int j, elemento aux){
	int contador=0;
	
	if(top=='+' || top=='-'){
		resultado[j]=Pop(s).c;
		j++;
		contador++;
		printf("\nJ es: %i", j);
		printf("\nEl tamano del resultado es: %i", strlen(resultado));
		printf("\n La cadena es: %s", resultado);
		Push(s, aux);
	}else if(top=='^'){
		resultado[j]=Pop(s).c;
		j++;
		contador++;
		printf("\nJ es: %i", j);
		printf("\nEl tamano del resultado es: %i", strlen(resultado));
		printf("\n La cadena es: %s", resultado);
		top=Top(s).c;
		if(top=='*' || top=='/'){
			resultado[j]=Pop(s).c;
			j++;
			contador++;
			printf("\nJ es: %i", j);
			printf("\nEl tamano del resultado es: %i", strlen(resultado));
			printf("\n La cadena es: %s", resultado);
			top=Top(s).c;
			if(top=='+' || top=='-'){
				resultado[j]=Pop(s).c;
				j++;
				contador++;
				printf("\nJ es: %i", j);
				printf("\nEl tamano del resultado es: %i", strlen(resultado));
				printf("\n La cadena es: %s", resultado);
				Push(s, aux);
			}else{
				Push(s, aux);
			}
		}else if(top=='+' || top=='-'){
			resultado[j]=Pop(s).c;
			j++;
			contador++;
			printf("\nJ es: %i", j);
			printf("\nEl tamano del resultado es: %i", strlen(resultado));
			printf("\n La cadena es: %s", resultado);
			Push(s, aux);
		}else{
			Push(s, aux);
		}
	}else if(top=='*' || top=='/'){
		resultado[j]=Pop(s).c;
		j++;
		contador++;
		printf("\nJ es: %i", j);
		printf("\nEl tamano del resultado es: %i", strlen(resultado));
		printf("\n La cadena es: %s", resultado);
		top=Top(s).c;
		if(top=='+' || top=='-'){
			resultado[j]=Pop(s).c;
			j++;
			contador++;
			printf("\nJ es: %i", j);
			printf("\nEl tamano del resultado es: %i", strlen(resultado));
			printf("\n La cadena es: %s", resultado);
			Push(s, aux);
		}else{
			Push(s, aux);
		}
	}else{
		printf("\nLa cadena hasta arriba es: %c", Top(s).c);
		Push(s, aux);
		printf("\nEl tope de la pila es: %i", s->tope);
	}
	
	return contador;
}
