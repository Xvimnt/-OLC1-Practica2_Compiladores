%{
/********************** 
 * Declaraciones en C *
 **********************/
  #include "scanner.h"
  #include "node.h"
  #include "qdebug.h"
  #include <iostream>
  #include <stdio.h>
  #include <stdlib.h>
  #include <math.h>
  #include <QtGui/QLineEdit>
  #include <QString>
  #include "string.h"
  #include <map>
  #include <variant>
  using namespace std

  extern int yylex(void);
  extern char *yytext;
  extern int linea;
  extern int columna;
  extern node *root;

  QLineEdit *expresion;
  void yyerror(char *errorString);
  void inicializa(QLineEdit *lineEdit);
  std::map<std::string, 
  std:variant<char*, int, float, char, bool>> variables; 

  int yyerror(const char* msj)
  {
    std::cout << msj << " " << yytext << std::endl;
    return 0;
  }

%}
/*************************
  Declaraciones de Bison *
 *************************/
%defines "parser.h"
%output "parser.cpp"
%error-verbose
%locations

%union
{
  char texto [256];
  node *Node;
}

%start START;

%token <texto>tint
%token <texto>tstring
%token <texto>tbool
%token <texto>tchar
%token <texto>tdouble
%token <texto>timprimir
%token <texto>tshow
%token <texto>tsi
%token <texto>tsino
%token <texto>tpara
%token <texto>trepetir
%token <texto>iden
%token <texto>number
%token <texto>boolean
%token <texto>String
%token <texto>caracter
%token <texto>integer
%token <texto>openPar
%token <texto>closePar
%token <texto>comma
%token <texto>plus
%token <texto>minus
%token <texto>by
%token <texto>slash
%token <texto>power
%token <texto>not
%token <texto>equal
%token <texto>greaterThan
%token <texto>lessThan
%token <texto>greaterThanEqual
%token <texto>lessThanEqual
%token <texto>doubleEqual
%token <texto>different
%token <texto>or
%token <texto>and
%token <texto>openB
%token <texto>closeB
%token <texto>openCB
%token <texto>closeCB
%token <texto>semicolon
%token <texto>decrease
%token <texto>increase

%type <Node> START
%type <Node> INICIO
%type <Node> BODY
%type <Node> DECLARATION
%type <Node> ASSIGNATION
%type <Node> ASSIGN2
%type <Node> DATATYPE
%type <Node> OBJECTS
%type <Node> ASSIGN  
%type <Node> ARRAY  
%type <Node> ARRAYASIGN  
%type <Node> ARRAYASIGN2   
%type <Node> ARRAYASIGN3   
%type <Node> ARRAYASIGN4   
%type <Node> ARRAYLIST   
%type <Node> NATIVE   
%type <Node> PRINT   
%type <Node> SHOW   
%type <Node> IF   
%type <Node> ELSE   
%type <Node> FOR   
%type <Node> WHILE   
%type <Node> VARMANAGMENT   
%type <Node> UPDATE   
%type <Node> ESINGLE   
%type <Node> E   

%left or
%left and
%left not
%left doubleEqual different lessThan lessThanEqual greaterThan greaterThanEqual
%left plus minus
%left by slash
%left power

%%
/***********************
 * Reglas Gramaticales *
 ***********************/

START: INICIO { root = $1; }
;

INICIO: INICIO BODY 
      { 
        node nod = new node(@1.first_line, @1.first_column,"cuerpo","cuerpo");  
        nod->add(*$1); 
        nod->add(*$2); 
        $$ = nod;
      }
      BODY {$$ = $1;}
;

BODY: DECLARATION {$$ = $1;}
      | ASSIGNATION {$$ = $1;}
      | UPDATE {$$ = $1;}
      
;

ASSIGNATION: iden ASSIGN2 semicolon 
        { 
          $$ = new node(@1.first_line, @1.first_column,"asignacion","asignacion"); 
          $$->add( new node(@1.first_line, @1.first_column,"identificador",$1)); 
          $$->add(*$2); 
        }
;

ASSIGN2: equal E { 
          $$ = new node(@1.first_line, @1.first_column,"igual",$1);  
          $$->add(*$2); 
        }
       | openB E closeB equal E 
        { 
          $$ = new node(@1.first_line, @1.first_column,"indice",$2); 
          node *temp =  new node(@1.first_line, @1.first_column,"igual",$1);
          temp->add(*$5); 
          $$->add(*$2); 
          $$->add(temp); 
        }
       | equal openB E closeB { 
          $$ = new node(@1.first_line, @1.first_column,"igual",$1);  
          //aqui devolver el valor del indice
          $$->add(*$3); 
        }
;

DECLARATION:	DATATYPE OBJECTS semicolon 
        { 
          $$ = new node(@1.first_line, @1.first_column,"declaracion","declaracion"); 
          $$->add(*$1); 
          $$->add(*$2); 
        }
;

DATATYPE: tint { $$ = new node(@1.first_line, @1.first_column,"reservada",$1);}
        | tbool { $$ = new node(@1.first_line, @1.first_column,"reservada",$1);}
        | tstring { $$ = new node(@1.first_line, @1.first_column,"reservada",$1);}
        | tdouble { $$ = new node(@1.first_line, @1.first_column,"reservada",$1);}
        | tchar{ $$ = new node(@1.first_line, @1.first_column,"reservada",$1);}
;

OBJECTS: OBJECTS comma iden ASSIGN 
        { 
          $$ = new node(@1.first_line, @1.first_column,"asignacion","asignacion"); 
          node *nod = new node(@1.first_line, @1.first_column,"asignacion",$3); nod->add(*$4);
          $$->add(*$1); 
          $$->add(nod); 
        }
      | iden ASSIGN 
      { 
        $$ = new node(@1.first_line, @1.first_column,"asignacion","asignacion"); 
        $$->add(*$2); 
        $$->add(new node(@1.first_line, @1.first_column,"id",$1)); 
      }
;

ASSIGN: equal E { $$ = new node(@1.first_line, @1.first_column,"igual",$1); $$->add(*$2); }
      | ARRAY { $$ = $1; }
      | { $$ = new node(); }
;

ARRAY: ARRAY openB E closeB ARRAYASIGN
      { 
        $$ = new node(@1.first_line, @1.first_column,"asignacion","asignacion"); 
        $$->add(*$1); 
        node nod = new node(@1.first_line, @1.first_column,"asignacionAIndex","asignacionAIndex");
        nod->add(*$3);
        nod->add(*$5);
        $$->add(*nod);
      }
    | openB E closeB ARRAYASIGN
    {
      $$ = new node(@1.first_line, @1.first_column,"asignacionAIndex","asignacionAIndex");
      $$->add(*$2);
      $$->add(*$4);
    }
;

ARRAYASIGN: openCB ARRAYASIGN2 closeCB { $$ = $2; }
;

ARRAYASIGN2: ARRAYASIGN3 { $$ = $1; }
          |  ARRAYLIST  { $$ = $1; }
;

ARRAYASIGN3: openCB ARRAYLIST closeCB comma openCB ARRAYLIST closeCB ARRAYASIGN4
      { 
        $$ = new node(@1.first_line, @1.first_column,"array","array"); 
        $$->add(*$2); 
        $$->add(*$6); 
        if($8 != nullptr)
          $$->add(*$8); 
      }
;

ARRAYASIGN4: comma openCB ARRAYLIST closeCB {$$ = $3;}
            | {$$ = nullptr;}
;

ARRAYLIST: ARRAYLIST comma E 
        {
            $$= new node(@2.first_line, @2.first_column,"lista","lista");
            $$->add(*$1);
            $$->add(*$3);
        }
        | E {$$=$1;}
;

NATIVE: integer { $$ = new node(@1.first_line, @1.first_column,"int",$1);}
    | caracter { $$ = new node(@1.first_line, @1.first_column,"char",$1);}
    | String  { $$ = new node(@1.first_line, @1.first_column,"string",$1);}
    | boolean { $$ = new node(@1.first_line, @1.first_column,"bool",$1);}
    | number { $$ = new node(@1.first_line, @1.first_column,"double",$1);}
;

PRINT: timprimir openPar E closePar semicolon  {node *nod = new node(@1.first_line, @1.first_column,"print",$1); nod->add(*$3); $$=nod;}
;

SHOW: tshow openPar E comma E closePar semicolon {node *nod = new node(@1.first_line, @1.first_column,"show",$1); nod->add(*$3); nod->add(*$5); $$=nod;}
;

IF: tsi openPar E closePar openCB BODY closeCB ELSE 
{
  node *nod = new node(@1.first_line, @1.first_column,"if",$3->valor);
  if(*$3->valor == "true")
  {
    nod->add(*$6);
  }
  else
  {
    if($8 != nullptr)
      nod->add(*$8);
  }
  $$ = nod;
}
;

ELSE: tsino IF {$$ = $2;}
    | tsino openCB BODY closeCB {$$ = $3;}
    | {$$ = nullptr;}
;

FOR: tpara openPar VARMANAGMENT semicolon E semicolon UPDATE closePar openCB BODY closeCB {
  node *nod = new node(@1.first_line, @1.first_column,"for","for"); 
  nod->add(*$3); nod->add(*$5); nod->add(*$7); nod->add(*$10);
  $$=nod;
}
;

WHILE: trepetir openPar E closePar openCB BODY closeCB{
  node *nod = new node(@1.first_line, @1.first_column,"while","while"); 
  nod->add(*$3); nod->add(*$6);
  $$=nod;
}
;

VARMANAGMENT: DECLARATION { $$ = $1; }
            | ASSIGNATION { $$ = $1; }
;

UPDATE:ESINGLE increase{ $$ = new node(@1.first_line, @1.first_column,"increase",$2); $$->add(*$1);}
      |ESINGLE decrease{ $$ = new node(@1.first_line, @1.first_column,"decrease",$2); $$->add(*$1);}
;

ESINGLE:NATIVE { $$ = $1; }
  |iden{
    $$ = new node(@1.first_line, @1.first_column,"identificador",$1); 
  }
;

E: E plus E{node *nod = new node(@1.first_line, @1.first_column,"suma",$2);  nod->add(*$1); nod->add(*$3); $$=nod;}
  |E minus E{node *nod = new node(@1.first_line, @1.first_column,"resta",$2);  nod->add(*$1); nod->add(*$3); $$=nod;}
  |E by E{node *nod = new node(@1.first_line, @1.first_column,"multi",$2);  nod->add(*$1); nod->add(*$3); $$=nod;}
  |E slash E{node *nod = new node(@1.first_line, @1.first_column,"div",$2);  nod->add(*$1); nod->add(*$3); $$=nod;}
  |E power E{node *nod = new node(@1.first_line, @1.first_column,"potencia",$2);  nod->add(*$1); nod->add(*$3); $$=nod;}
  |E doubleEqual E{node *nod = new node(@1.first_line, @1.first_column,"igualacion",$2);  nod->add(*$1); nod->add(*$3); $$=nod;}
  |E different E{node *nod = new node(@1.first_line, @1.first_column,"dif",$2);  nod->add(*$1); nod->add(*$3); $$=nod;}
  |E lessThan E{node *nod = new node(@1.first_line, @1.first_column,"menque",$2);  nod->add(*$1); nod->add(*$3); $$=nod;}
  |E greaterThan E{node *nod = new node(@1.first_line, @1.first_column,"mayque",$2);  nod->add(*$1); nod->add(*$3); $$=nod;}
  |E lessThanEqual E{node *nod = new node(@1.first_line, @1.first_column,"menoig",$2);  nod->add(*$1); nod->add(*$3); $$=nod;}
  |E greaterThanEqual E{node *nod = new node(@1.first_line, @1.first_column,"mayoig",$2);  nod->add(*$1); nod->add(*$3); $$=nod;}
  |E or E{node *nod = new node(@1.first_line, @1.first_column,"or",$2);  nod->add(*$1); nod->add(*$3); $$=nod;}
  |E and E{node *nod = new node(@1.first_line, @1.first_column,"and",$2);  nod->add(*$1); nod->add(*$3); $$=nod;}
  |not E{ $$ = new node(@1.first_line, @1.first_column,$1,$1); $$->add(*$2);}
  |ESINGLE{ $$ = $1; }
  |openPar E closePar{ $$ = $2; }
  |minus E { $$ = new node(@1.first_line, @1.first_column,$1,$1); $$->add(*$2);}
;

%%
/**********************
 * Codigo C Adicional *
 **********************/
void yyerror(char *errorString)
{
	printf("Error sintactico %s \n",errorString);
}

void inicializa(QLineEdit *lineEdit){
	expresion = lineEdit;
}

int main(int argc,char **argv)
{
	
	if (argc>1)
		yyin=fopen(argv[1],"rt");
	else
		//yyin=stdin;
		yyin=fopen("entrada.txt","rt");
		

	yyparse();
	return 0;
}