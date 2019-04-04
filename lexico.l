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
	//Declaraciones para los comentarios
	<INITIAL> ">>" {  BEGIN SIMPLE_COMMENT; }
	<INITIAL> "<-" {  BEGIN MULTI_COMMENT; }
	//Declaraciones de palabras reservadas
	<INITIAL> "int"  	   {columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext);return(tint);}
	<INITIAL> "string"   {columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext);return(tstring);}
	<INITIAL> "bool" 	   {columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext);return(tbool);}
	<INITIAL> "char" 	   {columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext);return(tchar);}
	<INITIAL> "double"   {columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext);return(tdouble);}
	<INITIAL> "imprimir" {columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext);return(timprimir);}
	<INITIAL> "show"	   {columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext);return(tshow);}
	<INITIAL> "si"	   {columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext);return(tsi);}
	<INITIAL> "sino"	   {columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext);return(tsino);}
	<INITIAL> "para"	   {columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext);return(tpara);}
	<INITIAL> "repetir"  {columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext);return(trepetir);}
	//Reconoce expresiones regulares
	<INITIAL> {number}   {yylval.real=atof(yytext); return(number);}
	<INITIAL> {boolean}  {yylval.condicion=atof(yytext); return(boolean);}
	<INITIAL> {String}   {yylval.texto=atof(yytext); return(String);}
	<INITIAL> {caracter} {yylval.letra=atof(yytext); return(caracter);}
	<INITIAL> {integer}  {yylval.numero=atof(yytext); return(integer);}
	<INITIAL> {iden}     {yylval.texto=atof(yytext); return(iden);}
	//Reconoce Tokens del lenguaje
	<INITIAL> "(" 	{columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext); return(openPar);}
	<INITIAL> ")" 	{columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext);return(closePar);}
	<INITIAL> "[" 	{columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext);return(openB);}
	<INITIAL> "]" 	{columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext);return(closeB);}
	<INITIAL> "{" 	{columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext);return(openCB);}
	<INITIAL> "}" 	{columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext);return(closeCB);}
	<INITIAL> "," 	{columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext);return(comma);}
	<INITIAL> "=" 	{columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext);return(equal);}
	<INITIAL> "==" 	{columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext);return(doubleEqual);}
	<INITIAL> "!=" 	{columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext);return(different);}
	<INITIAL> ">" 	{columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext);return(greaterThan);}
	<INITIAL> ">=" 	{columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext);return(greaterThanEqual);}
	<INITIAL> "<" 	{columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext);return(lessThan);}
	<INITIAL> "<=" 	{columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext);return(lessThanEqual);}
	<INITIAL> "||" 	{columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext);return(or);}
	<INITIAL> "&&" 	{columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext);return(and);}
	<INITIAL> "!" 	{columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext);return(not);}
	<INITIAL> "+" 	{columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext);return(plus);}
	<INITIAL> "++" 	{columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext);return(increase);}
	<INITIAL> "-" 	{columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext);return(minus);}
	<INITIAL> "--" 	{columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext);return(decrement);}
	<INITIAL> "*" 	{columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext);return(by);}
	<INITIAL> "/" 	{columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext);return(divided);}
	<INITIAL> "^" 	{columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext);return(power);}
	//Aqui se manejan los espacios encontrados
	<INITIAL> "\n" 	 	 {linea++; columna = 0; anterior = 0;}
	<INITIAL> [\t\r\f] 	 {}
	<INITIAL> [[:blank:]]	 {columna++;}
	//Aqui se manejan los errores lexicos
	<INITIAL>	.{
					columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext);

					/*  
						errorT *nuevoE = new errorT("Lexico",yytext,linea, columna);
						listaErrores->append(*nuevoE);
					*/

					std::cout <<yytext <<" Error Lexico en la linea "<< linea << " Columna:"<< columna<<  std::endl;
				}

	<MULTI_COMMENT> "->" { BEGIN INITIAL; }
	<MULTI_COMMENT> "\n" {linea++; columna = 0; anterior=0;}
	<SIMPLE_COMMENT> "\n" { linea++; columna = 0; anterior = 0; BEGIN INITIAL; }
%%
/*********************
 * Codigo de Usuario *
*********************/



