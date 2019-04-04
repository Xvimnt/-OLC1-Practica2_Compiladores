%option case-insensitive
%option yylineno
%option header-file="scanner.h"
%option outfile="scanner.cpp"
%option noyywrap
%option nounput

/*****************
 * Declaraciones *
 ****************/ 
%{
	#include <stdio.h>
	#include <stdlib.h>
	#include "sintactico.tab.h"	
	#include "parser.h"
	#include <QString>
	#include "node.h"
	int yylex();
	void yyerror(const char *s);
	int linea=0;
	int columna = 1;
	int anterior = 0;
	node *root;
%}
digit [0-9]
integer {digit}+
number {digit}+("."{digit}+)
letra [a-zñA-ZÑ]+
boolean ("true"|"false")
decimal [0-9]+"."[0-9]+
caracter "\'"("\\")?({letra}|{digit})"\'"
iden {letra}({letra}|{digit}|"_")*
String "\""[^"\""]*"\""

%x MULTI_COMMENT SIMPLE_COMMENT

%%
 /*********************
  * Reglas y Acciones *
 **********************/
INITIAL
{
	//Declaraciones para los comentarios
	">>" {  BEGIN SIMPLE_COMMENT; }
	"<-" {  BEGIN MULTI_COMMENT; }
	//Declaraciones de palabras reservadas
	"int"  	   {columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext);return(tint);}
	"string"   {columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext);return(tstring);}
	"bool" 	   {columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext);return(tbool);}
	"char" 	   {columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext);return(tchar);}
	"double"   {columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext);return(tdouble);}
	"imprimir" {columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext);return(timprimir);}
	"show"	   {columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext);return(tshow);}
	"si"	   {columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext);return(tsi);}
	"sino"	   {columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext);return(tsino);}
	"para"	   {columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext);return(tpara);}
	"repetir"  {columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext);return(trepetir);}
	//Reconoce expresiones regulares
	{number}   {yylval.real=atof(yytext); return(number);}
	{boolean}  {yylval.condicion=atof(yytext); return(boolean);}
	{String}   {yylval.texto=atof(yytext); return(String);}
	{caracter} {yylval.letra=atof(yytext); return(caracter);}
	{integer}  {yylval.numero=atof(yytext); return(integer);}
	{iden}     {yylval.texto=atof(yytext); return(iden);}
	//Reconoce Tokens del lenguaje
	"(" 	{columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext); return(openPar);}
	")" 	{columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext);return(closePar);}
	"[" 	{columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext);return(openB);}
	"]" 	{columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext);return(closeB);}
	"{" 	{columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext);return(openCB);}
	"}" 	{columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext);return(closeCB);}
	"," 	{columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext);return(comma);}
	"=" 	{columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext);return(equal);}
	"==" 	{columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext);return(doubleEqual);}
	"!=" 	{columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext);return(different);}
	">" 	{columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext);return(greaterThan);}
	">=" 	{columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext);return(greaterThanEqual);}
	"<" 	{columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext);return(lessThan);}
	"<=" 	{columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext);return(lessThanEqual);}
	"||" 	{columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext);return(or);}
	"&&" 	{columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext);return(and);}
	"!" 	{columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext);return(not);}
	"+" 	{columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext);return(plus);}
	"++" 	{columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext);return(increase);}
	"-" 	{columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext);return(minus);}
	"--" 	{columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext);return(decrement);}
	"*" 	{columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext);return(by);}
	"/" 	{columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext);return(divided);}
	"^" 	{columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext);return(power);}
	//Aqui se manejan los espacios encontrados
	"\n" 	 	 {linea++; columna = 0; anterior = 0;}
	[\t\r\f] 	 {}
	[[:blank:]]	 {columna++;}
	//Aqui se manejan los errores lexicos
		.	 	 {
					columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext);

					/*  
						errorT *nuevoE = new errorT("Lexico",yytext,linea, columna);
						listaErrores->append(*nuevoE);
					*/

					std::cout <<yytext <<" Error Lexico en la linea "<< linea << " Columna:"<< columna<<  std::endl;
				}
}

<MULTI_COMMENT> "->" { BEGIN INITIAL; }
<MUTI_COMMENT>"\n" {linea++;};
<MUTI_COMMENT>.;
<MUTI_COMMENT><<EOF>> { yyerror("unclosed comment"); }
<SIMPLE_COMMENT>"\n" { linea++; columna = 0; BEGIN INITIAL; };
<SIMPLE_COMMENT>.;
%%
/*********************
 * Codigo de Usuario *
*********************/



