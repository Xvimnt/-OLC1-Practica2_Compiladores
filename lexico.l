%option case-insensitive
%option yylineno
%{
    #include <cstdlib>
    #include "parser.h"
    #include <QString>
    #include <stdio.h>
    #include <iostream>
    #include <node.h>
    #include "qlist.h"
    #include "error.h"

    int yylex();
    QList<error*> errores;
	void yyerror(const char *s);
	int linea=0;
	int columna = 1;
	int anterior = 0;
	node *root;
%}

%option noyywrap
%option nounput
%option header-file= "scanner.h"
%option outfile="scanner.cpp"

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
INITIAL
{
    ">>" {  BEGIN SIMPLE_COMMENT; }
    "<-" {  BEGIN MULTI_COMMENT; }
    "int"  	   {std::cout<< "reconocido " << yytext << std::endl; columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext);return tint;}
    "string"   {std::cout<< "reconocido " << yytext << std::endl; columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext);return tstring;}
    "bool" 	   {std::cout<< "reconocido " << yytext << std::endl;columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext);return tbool;}
    "char" 	   {std::cout<< "reconocido " << yytext << std::endl;columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext);return tchar;}
    "double"   {std::cout<< "reconocido " << yytext << std::endl;columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext);return tdouble;}
    "imprimir" {std::cout<< "reconocido " << yytext << std::endl;columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext);return timprimir;}
    "show"	   {std::cout<< "reconocido " << yytext << std::endl;columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext);return tshow;}
    "si"	   {std::cout<< "reconocido " << yytext << std::endl;columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext);return tsi;}
    "sino"	   {std::cout<< "reconocido " << yytext << std::endl;columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext);return tsino;}
    "para"	   {std::cout<< "reconocido " << yytext << std::endl;columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext);return tpara;}
    "repetir"  {std::cout<< "reconocido " << yytext << std::endl;columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext);return trepetir;}
    "arreglo"  {std::cout<< "reconocido " << yytext << std::endl;columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext);return tarreglo;}
    "(" 	{std::cout<< "reconocido " << yytext << std::endl;columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext);return openPar;}
    ")" 	{std::cout<< "reconocido " << yytext << std::endl;columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext);return closePar;}
    "[" 	{std::cout<< "reconocido " << yytext << std::endl;columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext);return openB;}
    "]" 	{std::cout<< "reconocido " << yytext << std::endl;columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext);return closeB;}
    "{" 	{std::cout<< "reconocido " << yytext << std::endl;columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext);return openCB;}
    "}" 	{std::cout<< "reconocido " << yytext << std::endl;columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext);return closeCB;}
    "," 	{std::cout<< "reconocido " << yytext << std::endl;columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext);return comma;}
    ";" 	{std::cout<< "reconocido " << yytext << std::endl;columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext);return semicolon;}
    "=" 	{std::cout<< "reconocido " << yytext << std::endl;columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext);return equal;}
    "==" 	{std::cout<< "reconocido " << yytext << std::endl;columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext);return doubleEqual;}
    "!=" 	{std::cout<< "reconocido " << yytext << std::endl;columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext);return different;}
    ">" 	{std::cout<< "reconocido " << yytext << std::endl;columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext);return greaterThan;}
    ">=" 	{std::cout<< "reconocido " << yytext << std::endl;columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext);return greaterThanEqual;}
    "<" 	{std::cout<< "reconocido " << yytext << std::endl;columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext);return lessThan;}
    "<=" 	{std::cout<< "reconocido " << yytext << std::endl;columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext);return lessThanEqual;}
    "||" 	{std::cout<< "reconocido " << yytext << std::endl;columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext);return tor;}
    "&&" 	{std::cout<< "reconocido " << yytext << std::endl;columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext);return tand;}
    "!" 	{std::cout<< "reconocido " << yytext << std::endl;columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext);return tnot;}
    "+" 	{std::cout<< "reconocido " << yytext << std::endl;columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext);return plus;}
    "++" 	{std::cout<< "reconocido " << yytext << std::endl;columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext);return increase;}
    "-" 	{std::cout<< "reconocido " << yytext << std::endl;columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext);return minus;}
    "--" 	{std::cout<< "reconocido " << yytext << std::endl;columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext);return decrease;}
    "*" 	{std::cout<< "reconocido " << yytext << std::endl;columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext);return by;}
    "/" 	{std::cout<< "reconocido " << yytext << std::endl;columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext);return slash;}
    "^" 	{std::cout<< "reconocido " << yytext << std::endl;columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext);return power;}

        {number}   {std::cout<< "reconocido " << yytext << std::endl; return(number);}
        {boolean}  {std::cout<< "reconocido " << yytext << std::endl; return(boolean);}
        {String}   {std::cout<< "reconocido " << yytext << std::endl; return(String);}
        {caracter} {std::cout<< "reconocido " << yytext << std::endl; return(caracter);}
        {integer}  {std::cout<< "reconocido " << yytext << std::endl; return(integer);}
        {iden}     {std::cout<< "reconocido " << yytext << std::endl; return(iden);}


    "\t" 	 {strcpy(yylval.TEXT , yytext); columna = 26;}
    [[:blank:]]	 {columna++;}
    "\n" 	 	 {linea++; columna = 0; anterior = 0;}
    .   {
            columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext);
            errores.append(new error(yytext,"Error Lexico", yylineno, columna, "simbolo no reconocido") );
            std::cout <<yytext <<" Error Lexico en la linea "<< linea << " Columna:"<< columna<<  std::endl;
        }
}

    <MULTI_COMMENT>"->" { BEGIN INITIAL; }
    <MULTI_COMMENT>"\n" {linea++;}
    <MULTI_COMMENT>.;
    <MULTI_COMMENT><<EOF>> { yyerror("unclosed comment"); }
    <SIMPLE_COMMENT>"\n" { linea++; columna = 0; BEGIN INITIAL; }
    <SIMPLE_COMMENT>.;
%%
