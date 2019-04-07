%{
#include "scanner.h"//se importa el header del analisis sintactico
#include "node.h"
#include "qdebug.h"
#include <iostream>
#include <map>
extern int yylineno; //linea actual donde se encuentra el parser (analisis lexico) lo maneja BISON
extern int columna; //columna actual donde se encuentra el parser (analisis lexico) lo maneja BISON
extern char *yytext; //lexema actual donde esta el parser (analisis lexico) lo maneja BISON
extern node *root; // Raiz del arbol

int yyerror(const char* msj)
{
    std::cout << msj << " " << yytext << std::endl;
    return 0;
}
%}
%defines "parser.h"
%output "parser.cpp"
%error-verbose
%locations

%union
{
  char TEXT [256];
  class node *Node;
}

%start START;

%token <TEXT>tint
%token <TEXT>tstring
%token <TEXT>tbool
%token <TEXT>tchar
%token <TEXT>tdouble
%token <TEXT>timprimir
%token <TEXT>tshow
%token <TEXT>tsi tarreglo
%token <TEXT>tsino
%token <TEXT>tpara
%token <TEXT>trepetir
%token <TEXT>iden
%token <TEXT>number
%token <TEXT>boolean
%token <TEXT>String
%token <TEXT>caracter
%token <TEXT>integer
%token <TEXT>openPar
%token <TEXT>closePar
%token <TEXT>comma
%token <TEXT>plus
%token <TEXT>minus
%token <TEXT>by
%token <TEXT>slash
%token <TEXT>power
%token <TEXT>tnot
%token <TEXT>equal
%token <TEXT>greaterThan
%token <TEXT>lessThan
%token <TEXT>greaterThanEqual
%token <TEXT>lessThanEqual
%token <TEXT>doubleEqual
%token <TEXT>different
%token <TEXT>tor
%token <TEXT>tand
%token <TEXT>openB
%token <TEXT>closeB
%token <TEXT>openCB
%token <TEXT>closeCB
%token <TEXT>semicolon
%token <TEXT>decrease
%token <TEXT>increase

%type <Node> START 
%type <Node> START2
%type <Node> BODY
%type <Node> DECLARATION DECLARATION2
%type <Node> ASSIGNATION
%type <Node> ASSIGN2 INDEX
%type <Node> DATATYPE
%type <Node> OBJECTS
%type <Node> ASSIGN  
%type <Node> ARRAY ARRAY2 ARRAY3
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

%left tor
%left tand
%left tnot
%left doubleEqual different lessThan lessThanEqual greaterThan greaterThanEqual
%left plus minus
%left by slash
%left power

%%
START: START2 { root = $1; }
;

START2: START2 BODY 
      {
        $$ = $1;
        $$->add(*$2);
      }
      | BODY
      {
        $$ = new node(yylineno, columna,"cuerpo","cuerpo");
        $$->add(*$1);
      }
;

BODY: DECLARATION {$$ = $1;}
      | ASSIGNATION {$$ = $1;}
      | UPDATE {$$ = $1;}
      | PRINT {$$ = $1;}
      | SHOW {$$ = $1;}
      | IF {$$ = $1;}
      | FOR {$$ = $1;}
      | WHILE {$$ = $1;}
;

ASSIGNATION: iden ASSIGN2 semicolon 
        { 
          $$ = new node(yylineno, columna,"asignacion","asignacion"); 
          node *res = new node(yylineno, columna,"id",$1);
          $$->add(*res);
          $$->add(*$2);
        }
;

ASSIGN2: equal E
        {
          $$ = new node(yylineno, columna,"igual",$1);
          $$->add(*$2);
        }
       | openB E closeB ASSIGN2
        { 
          $$ = new node(yylineno, columna,"indice",$2->valor);
          $$->add(*$4);
        }
;

DECLARATION: DATATYPE DECLARATION2
        {
          $$ = new node(yylineno, columna,"declaracion","declaracion");
          $$->add(*$1);
          $$->add(*$2);
        }
;

DECLARATION2: OBJECTS semicolon
              {
                $$ = $1;
              }
              | tarreglo iden ARRAY
              {
                $$ = $3;
              }
;

DATATYPE: tint { $$ = new node(yylineno, columna,"reservada",$1);}
        | tbool { $$ = new node(yylineno, columna,"reservada",$1);}
        | tstring { $$ = new node(yylineno, columna,"reservada",$1);}
        | tdouble { $$ = new node(yylineno, columna,"reservada",$1); }
        | tchar{ $$ = new node(yylineno, columna,"reservada",$1);}
;

OBJECTS: OBJECTS comma iden ASSIGN 
        { 
          $$ = $1;
          node *nod;
          if($4 == nullptr)
          {
              nod = new node(yylineno, columna,"declaracion","declaracion");
              node *res = new node(yylineno, columna,"id",$3);
              nod->add(*res);
          }
          else
          {
              nod = new node(yylineno, columna,"asignacion","asignacion");
              node *res = new node(yylineno, columna,"id",$3);
              nod->add(*res);
              nod->add(*$4);
          }
          $$->add(*nod);
        }
      | iden ASSIGN 
      { 
        $$ = new node(yylineno, columna,"asignaciones","asignaciones");
        node *nod;
        if($2 == nullptr)
        {
            nod = new node(yylineno, columna,"declaracion","declaracion");
            node *res = new node(yylineno, columna,"id",$1);
            nod->add(*res);
        }
        else
        {
            nod = new node(yylineno, columna,"asignacion","asignacion");
            node *res = new node(yylineno, columna,"id",$1);
            nod->add(*res);
            nod->add(*$2);
        }
        $$->add(*nod);
      }
;

ASSIGN: equal E { $$ = new node(yylineno, columna,"igual",$1); $$->add(*$2); }
      | ARRAY { $$ = $1; }
      | { $$ = nullptr; }
;

ARRAY: openB E closeB ARRAY2 ARRAYASIGN
    {
      if($4 == nullptr)
      {
          $$ = new node(yylineno, columna,"dimensiones","dimensiones");
          node *nod = new node(yylineno, columna,"nueva dimension","nueva dimension");
          nod->add(*$2);
          $$->add(*nod);
      }
      else
      {
          $$ = $4;
          node *nod = new node(yylineno, columna,"nueva dimension","nueva dimension");
          nod->add(*$2);
          $$->add(*nod);
      }
      if($5 == nullptr)
      {
          node *nod = $$;
          $$ = new node(yylineno, columna,"Declaracion de Arreglo","Declaracion de Arreglo");
          $$->add(*nod);
      }
      else
      {
          node *nod = $$;
          $$ = new node(yylineno, columna,"Asignacion de Arreglo","Asignacion de Arreglo");
          $$->add(*nod);
          $$->add(*$5);
      }
    }
;

ARRAY2: openB E closeB ARRAY3
      {
        if($4 == nullptr)
        {
            $$ = new node(yylineno, columna,"dimensiones","dimensiones");
            node *nod = new node(yylineno, columna,"nueva dimension","nueva dimension");
            nod->add(*$2);
            $$->add(*nod);
        }
        else
        {
            $$ = $4;
            node *nod = new node(yylineno, columna,"nueva dimension","nueva dimension");
            nod->add(*$2);
            $$->add(*nod);
        }
      }
      | {$$ = nullptr;}
;

ARRAY3:openB E closeB
      {
        $$ = new node(yylineno, columna,"dimensiones","dimensiones");
        node *nod = new node(yylineno, columna,"nueva dimension","nueva dimension");
        nod->add(*$2);
        $$->add(*nod);
      }
      | {$$ = nullptr;}
;

ARRAYASIGN: openCB ARRAYASIGN2 closeCB { $$ = $2; }
            | { $$ = nullptr; }
;

ARRAYASIGN2: ARRAYASIGN3 { $$ = $1; }
          |  ARRAYLIST  { $$ = $1; }
;

ARRAYASIGN3: openCB ARRAYLIST closeCB comma openCB ARRAYLIST closeCB ARRAYASIGN4
      { 
            $$ = new node(yylineno, columna,"Asignaciones","Asignaciones");
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
            $$= $1;
            $$->add(*$3);
        }
        | E
        {
            $$= new node(yylineno, columna,"lista","lista");
            $$->add(*$1);
        }
;

NATIVE: integer { $$ = new node(yylineno, columna,"int",yytext);}
    | caracter { $$ = new node(yylineno, columna,"char",yytext);}
    | String  { $$ = new node(yylineno, columna,"string",yytext);}
    | boolean { $$ = new node(yylineno, columna,"bool",yytext);}
    | number { $$ = new node(yylineno, columna,"double",yytext);}
;

PRINT: timprimir openPar E closePar semicolon  {node *nod = new node(yylineno, columna,"print",$1); nod->add(*$3); $$=nod;}
;

SHOW: tshow openPar E comma E closePar semicolon {node *nod = new node(yylineno, columna,"show",$1); nod->add(*$3); nod->add(*$5); $$=nod;}
;

IF: tsi openPar E closePar openCB START2 closeCB ELSE
{
  node *nod = new node(yylineno, columna,"if",$3->valor);
  if($3->valor == "true")
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
    | tsino openCB START2 closeCB {$$ = $3;}
    | {$$ = nullptr;}
;

FOR: tpara openPar VARMANAGMENT E semicolon UPDATE closePar openCB START2 closeCB {
  node *nod = new node(yylineno, columna,"for","for");
  nod->add(*$3); nod->add(*$4); nod->add(*$6); nod->add(*$9);
  $$=nod;
}
;

WHILE: trepetir openPar E closePar openCB START2 closeCB{
  node *nod = new node(yylineno, columna,"while","while"); 
  nod->add(*$3); nod->add(*$6);
  $$=nod;
}
;

VARMANAGMENT: DECLARATION { $$ = $1; }
            | ASSIGNATION { $$ = $1; }
;

UPDATE:ESINGLE increase{ $$ = new node(yylineno, columna,"increase",$2); $$->add(*$1);}
      |ESINGLE decrease{ $$ = new node(yylineno, columna,"decrease",$2); $$->add(*$1);}
;

ESINGLE:NATIVE { $$ = $1; }
  |iden INDEX{
    if($2==nullptr)
    {
        $$ = new node(yylineno, columna,"id",$1);
    }
    else
    {
        $$ = new node(yylineno, columna,"arregloIndex",$1);
        //Devolver el valor del index
    }
  }
;

INDEX: openB E closeB
        {
           $$=$2;
        }
        | {$$=nullptr;}
;

E: E plus E{node *nod = new node(yylineno, columna,"suma",$2);  nod->add(*$1); nod->add(*$3); $$=nod;}
  |E minus E{node *nod = new node(yylineno, columna,"resta",$2);  nod->add(*$1); nod->add(*$3); $$=nod;}
  |E by E{node *nod = new node(yylineno, columna,"multi",$2);  nod->add(*$1); nod->add(*$3); $$=nod;}
  |E slash E{node *nod = new node(yylineno, columna,"div",$2);  nod->add(*$1); nod->add(*$3); $$=nod;}
  |E power E{node *nod = new node(yylineno, columna,"potencia",$2);  nod->add(*$1); nod->add(*$3); $$=nod;}
  |E doubleEqual E{node *nod = new node(yylineno, columna,"igualacion",$2);  nod->add(*$1); nod->add(*$3); $$=nod;}
  |E different E{node *nod = new node(yylineno, columna,"dif",$2);  nod->add(*$1); nod->add(*$3); $$=nod;}
  |E lessThan E{node *nod = new node(yylineno, columna,"menque",$2);  nod->add(*$1); nod->add(*$3); $$=nod;}
  |E greaterThan E{node *nod = new node(yylineno, columna,"mayque",$2);  nod->add(*$1); nod->add(*$3); $$=nod;}
  |E lessThanEqual E{node *nod = new node(yylineno, columna,"menoig",$2);  nod->add(*$1); nod->add(*$3); $$=nod;}
  |E greaterThanEqual E{node *nod = new node(yylineno, columna,"mayoig",$2);  nod->add(*$1); nod->add(*$3); $$=nod;}
  |E tor E{node *nod = new node(yylineno, columna,"tor",$2);  nod->add(*$1); nod->add(*$3); $$=nod;}
  |E tand E{node *nod = new node(yylineno, columna,"tand",$2);  nod->add(*$1); nod->add(*$3); $$=nod;}
  |tnot E{ $$ = new node(yylineno, columna,$1,$1); $$->add(*$2);}
  |ESINGLE{ $$ = $1; }
  |openPar E closePar{ $$ = $2; }
  |minus E { $$ = new node(yylineno, columna,$1,$1); $$->add(*$2);}
;

%%
