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
        $$ = new node(@1.first_line, @1.first_column,"cuerpo","cuerpo");
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
          $$ = new node(@1.first_line, @1.first_column,"asignacion","asignacion"); 
          node *res = new node(@1.first_line, @1.first_column,"id",$1);
          $$->add(*res);
          $$->add(*$2);
        }
;

ASSIGN2: equal E
        {
          $$ = new node(@1.first_line, @1.first_column,"igual",$1);
          $$->add(*$2);
        }
       | openB E closeB ASSIGN2
        { 
          $$ = new node(@1.first_line, @1.first_column,"indice",$2->valor);
          $$->add(*$4);
        }
;

DECLARATION: DATATYPE DECLARATION2
        {
          $$ = new node(@1.first_line, @1.first_column,"declaracion","declaracion");
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

DATATYPE: tint { $$ = new node(@1.first_line, @1.first_column,"reservada",$1); std::cout << "Native: " << $1 << " en la linea " << yylineno << std::endl;}
        | tbool { $$ = new node(@1.first_line, @1.first_column,"reservada",$1); std::cout << "Native: " << $1 << std::endl;}
        | tstring { $$ = new node(@1.first_line, @1.first_column,"reservada",$1); std::cout << "Native: " << $1 << std::endl;}
        | tdouble { $$ = new node(@1.first_line, @1.first_column,"reservada",$1); std::cout << "Native: " << $1 << std::endl;}
        | tchar{ $$ = new node(@1.first_line, @1.first_column,"reservada",$1); std::cout << "Native: " << $1 << std::endl;}
;

OBJECTS: OBJECTS comma iden ASSIGN 
        { 
          $$ = $1;
          node *nod;
          if($4 == nullptr)
          {
              nod = new node(@1.first_line, @1.first_column,"declaracion","declaracion");
              node *res = new node(@1.first_line, @1.first_column,"id",$3);
              nod->add(*res);
          }
          else
          {
              nod = new node(@1.first_line, @1.first_column,"asignacion","asignacion");
              node *res = new node(@1.first_line, @1.first_column,"id",$3);
              nod->add(*res);
              nod->add(*$4);
          }
          $$->add(*nod);
        }
      | iden ASSIGN 
      { 
        $$ = new node(@1.first_line, @1.first_column,"asignaciones","asignaciones");
        node *nod;
        if($2 == nullptr)
        {
            nod = new node(@1.first_line, @1.first_column,"declaracion","declaracion");
            node *res = new node(@1.first_line, @1.first_column,"id",$1);
            nod->add(*res);
        }
        else
        {
            nod = new node(@1.first_line, @1.first_column,"asignacion","asignacion");
            node *res = new node(@1.first_line, @1.first_column,"id",$1);
            nod->add(*res);
            nod->add(*$2);
        }
        $$->add(*nod);
      }
;

ASSIGN: equal E { $$ = new node(@1.first_line, @1.first_column,"igual",$1); $$->add(*$2); }
      | ARRAY { $$ = $1; }
      | { $$ = nullptr; }
;

ARRAY: openB E closeB ARRAY2 ARRAYASIGN
    {
      if($4 == nullptr)
      {
          $$ = new node(@1.first_line, @1.first_column,"dimensiones","dimensiones");
          node *nod = new node(@1.first_line, @1.first_column,"nueva dimension","nueva dimension");
          nod->add(*$2);
          $$->add(*nod);
      }
      else
      {
          $$ = $4;
          node *nod = new node(@1.first_line, @1.first_column,"nueva dimension","nueva dimension");
          nod->add(*$2);
          $$->add(*nod);
      }
      if($5 == nullptr)
      {
          node *nod = $$;
          $$ = new node(@1.first_line, @1.first_column,"Declaracion de Arreglo","Declaracion de Arreglo");
          $$->add(*nod);
      }
      else
      {
          node *nod = $$;
          $$ = new node(@1.first_line, @1.first_column,"Asignacion de Arreglo","Asignacion de Arreglo");
          $$->add(*nod);
          $$->add(*$5);
      }
    }
;

ARRAY2: openB E closeB ARRAY3
      {
        if($4 == nullptr)
        {
            $$ = new node(@1.first_line, @1.first_column,"dimensiones","dimensiones");
            node *nod = new node(@1.first_line, @1.first_column,"nueva dimension","nueva dimension");
            nod->add(*$2);
            $$->add(*nod);
        }
        else
        {
            $$ = $4;
            node *nod = new node(@1.first_line, @1.first_column,"nueva dimension","nueva dimension");
            nod->add(*$2);
            $$->add(*nod);
        }
      }
      | {$$ = nullptr;}
;

ARRAY3:openB E closeB
      {
        $$ = new node(@1.first_line, @1.first_column,"dimensiones","dimensiones");
        node *nod = new node(@1.first_line, @1.first_column,"nueva dimension","nueva dimension");
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
            $$ = new node(@1.first_line, @1.first_column,"Asignaciones","Asignaciones");
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
            $$= new node(@1.first_line, @1.first_column,"lista","lista");
            $$->add(*$1);
        }
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

IF: tsi openPar E closePar openCB START2 closeCB ELSE
{
  node *nod = new node(@1.first_line, @1.first_column,"if",$3->valor);
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
  node *nod = new node(@1.first_line, @1.first_column,"for","for");
  nod->add(*$3); nod->add(*$4); nod->add(*$6); nod->add(*$9);
  $$=nod;
}
;

WHILE: trepetir openPar E closePar openCB START2 closeCB{
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
  |iden INDEX{
    if($2==nullptr)
    {
        $$ = new node(@1.first_line, @1.first_column,"id",$1);
    }
    else
    {
        $$ = new node(@1.first_line, @1.first_column,"arregloIndex",$1);
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
  |E tor E{node *nod = new node(@1.first_line, @1.first_column,"tor",$2);  nod->add(*$1); nod->add(*$3); $$=nod;}
  |E tand E{node *nod = new node(@1.first_line, @1.first_column,"tand",$2);  nod->add(*$1); nod->add(*$3); $$=nod;}
  |tnot E{ $$ = new node(@1.first_line, @1.first_column,$1,$1); $$->add(*$2);}
  |ESINGLE{ $$ = $1; }
  |openPar E closePar{ $$ = $2; }
  |minus E { $$ = new node(@1.first_line, @1.first_column,$1,$1); $$->add(*$2);}
;

%%
