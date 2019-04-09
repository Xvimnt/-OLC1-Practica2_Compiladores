/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.0.4"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 1 "sintactico.y" /* yacc.c:339  */

#include "scanner.h"//se importa el header del analisis sintactico
#include "node.h"
#include "qdebug.h"
#include <iostream>
#include <map>
#include "error.h"
extern int yylineno; //linea actual donde se encuentra el parser (analisis lexico) lo maneja BISON
extern int columna; //columna actual donde se encuentra el parser (analisis lexico) lo maneja BISON
extern char *yytext; //lexema actual donde esta el parser (analisis lexico) lo maneja BISON
extern node *root; // Raiz del arbol
extern QList<error*> errores;

int yyerror(const char* msj)
{
    std::cout << msj << " " << yytext << std::endl;
    errores.append(new error(yytext,"Error Sintactico", yylineno, columna,msj) );
    return 0;
}

#line 87 "parser.cpp" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 1
#endif

/* In a future release of Bison, this section will be replaced
   by #include "parser.h".  */
#ifndef YY_YY_PARSER_H_INCLUDED
# define YY_YY_PARSER_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    tint = 258,
    tstring = 259,
    tbool = 260,
    tchar = 261,
    tdouble = 262,
    timprimir = 263,
    tshow = 264,
    tsi = 265,
    tarreglo = 266,
    tsino = 267,
    tpara = 268,
    trepetir = 269,
    iden = 270,
    number = 271,
    boolean = 272,
    String = 273,
    caracter = 274,
    integer = 275,
    openPar = 276,
    closePar = 277,
    comma = 278,
    plus = 279,
    minus = 280,
    by = 281,
    slash = 282,
    power = 283,
    tnot = 284,
    equal = 285,
    greaterThan = 286,
    lessThan = 287,
    greaterThanEqual = 288,
    lessThanEqual = 289,
    doubleEqual = 290,
    different = 291,
    tor = 292,
    tand = 293,
    openB = 294,
    closeB = 295,
    openCB = 296,
    closeCB = 297,
    semicolon = 298,
    decrease = 299,
    increase = 300
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 27 "sintactico.y" /* yacc.c:355  */

  char TEXT [256];
  class node *Node;

#line 178 "parser.cpp" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif

/* Location type.  */
#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE YYLTYPE;
struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
};
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif


extern YYSTYPE yylval;
extern YYLTYPE yylloc;
int yyparse (void);

#endif /* !YY_YY_PARSER_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 209 "parser.cpp" /* yacc.c:358  */

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif


#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL \
             && defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
  YYLTYPE yyls_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE) + sizeof (YYLTYPE)) \
      + 2 * YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  37
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   520

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  46
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  31
/* YYNRULES -- Number of rules.  */
#define YYNRULES  80
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  183

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   300

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   112,   112,   115,   120,   127,   128,   129,   130,   131,
     132,   133,   134,   137,   145,   149,   156,   164,   168,   176,
     177,   178,   179,   180,   183,   200,   219,   220,   221,   224,
     233,   240,   243,   250,   253,   254,   257,   259,   262,   264,
     267,   272,   279,   280,   281,   282,   283,   286,   289,   292,
     303,   304,   308,   311,   318,   325,   326,   329,   330,   333,
     334,   348,   352,   355,   360,   361,   362,   363,   364,   365,
     366,   367,   368,   369,   370,   371,   372,   373,   374,   375,
     376
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 1
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "tint", "tstring", "tbool", "tchar",
  "tdouble", "timprimir", "tshow", "tsi", "tarreglo", "tsino", "tpara",
  "trepetir", "iden", "number", "boolean", "String", "caracter", "integer",
  "openPar", "closePar", "comma", "plus", "minus", "by", "slash", "power",
  "tnot", "equal", "greaterThan", "lessThan", "greaterThanEqual",
  "lessThanEqual", "doubleEqual", "different", "tor", "tand", "openB",
  "closeB", "openCB", "closeCB", "semicolon", "decrease", "increase",
  "$accept", "START", "START2", "BODY", "ASSIGNATION", "ASSIGN2",
  "DECLARATION", "DECLARATION2", "DATATYPE", "OBJECTS", "ASSIGN", "ARRAY",
  "ARRAY2", "ARRAY3", "ARRAYASIGN", "ARRAYASIGN2", "ARRAYASIGN3",
  "ARRAYLIST", "NATIVE", "PRINT", "SHOW", "IF", "ELSE", "FOR", "WHILE",
  "VARMANAGMENT", "UPDATE", "ESINGLE", "INDEX", "ID", "E", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300
};
# endif

#define YYPACT_NINF -112

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-112)))

#define YYTABLE_NINF -1

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     243,  -112,  -112,  -112,  -112,  -112,    -6,    31,    34,    41,
      45,  -112,  -112,  -112,  -112,  -112,  -112,    54,   243,  -112,
    -112,  -112,     2,  -112,  -112,  -112,  -112,  -112,  -112,  -112,
       5,   -25,   478,   478,   478,   101,   478,  -112,  -112,     8,
    -112,   -13,   -23,  -112,  -112,   478,   478,    25,  -112,   478,
     478,   478,  -112,    44,   242,   424,   259,  -112,  -112,   478,
     -19,   276,    55,     8,  -112,   478,   478,  -112,  -112,   439,
     291,  -112,   308,    33,   484,   478,    52,   478,   478,   478,
     478,   478,   478,   478,   478,   478,   478,   478,   478,   478,
     478,    43,   200,   478,    68,  -112,   -23,   439,   323,   -19,
    -112,   340,  -112,    33,    33,    84,    84,  -112,   127,   127,
     127,   127,   127,   127,   454,   484,   357,   243,   183,   372,
     243,  -112,    14,  -112,  -112,    71,    83,    89,   -19,   155,
      74,   478,    79,  -112,  -112,   116,    93,  -112,   478,   389,
    -112,    -7,  -112,   243,   -15,   439,    17,   243,  -112,   173,
     478,  -112,    94,   478,  -112,  -112,   203,  -112,   439,    95,
     406,  -112,   478,   107,   -11,    98,  -112,   105,   125,   478,
     478,    -2,     6,   142,   126,  -112,   478,    22,   144,   478,
      23,   152,  -112
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,    19,    21,    20,    23,    22,     0,     0,     0,     0,
       0,    63,    46,    45,    44,    43,    42,     0,     2,     4,
       6,     5,     0,    59,     8,     9,    10,    11,    12,     7,
       0,    62,     0,     0,     0,     0,     0,     1,     3,     0,
      16,     0,    28,    58,    57,     0,     0,     0,    60,     0,
       0,     0,    78,    62,     0,     0,     0,    56,    55,     0,
       0,     0,     0,     0,    17,     0,     0,    25,    27,    14,
       0,    13,     0,    80,    77,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    18,    28,    26,     0,    61,
      79,     0,    47,    64,    65,    66,    67,    68,    72,    71,
      74,    73,    69,    70,    75,    76,     0,     0,     0,     0,
       0,    24,    35,    15,    61,     0,     0,     0,     0,     0,
       0,     0,     0,    31,    48,    52,     0,    54,     0,     0,
      29,     0,    49,     0,     0,    41,    37,     0,    50,     0,
       0,    34,     0,     0,    30,    33,     0,    53,    40,     0,
       0,    51,     0,    39,     0,     0,    32,     0,     0,     0,
       0,     0,     0,     0,     0,    36,     0,     0,     0,     0,
       0,     0,    38
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -112,  -112,  -111,   -16,   160,   -95,   161,  -112,  -112,  -112,
     108,   143,  -112,  -112,  -112,  -112,  -112,   -38,  -112,  -112,
    -112,    73,  -112,  -112,  -112,  -112,   111,     1,  -112,     0,
      -8
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    17,    18,    19,    20,    47,    21,    40,    22,    41,
      67,    68,   132,   154,   133,   155,   166,   144,    23,    24,
      25,    26,   142,    27,    28,    59,    29,    52,    48,    53,
     145
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      31,    30,    38,     8,   123,    45,   126,    65,   150,   129,
      63,    45,   150,    39,    46,    32,    66,    11,    31,    30,
      93,   150,    42,    11,    54,    55,    56,   151,    61,   150,
      64,   167,   149,   123,   147,    60,   156,    69,    70,    62,
     173,    72,    73,    74,   130,   150,   150,   152,   174,    43,
      44,    92,    33,   131,    37,    34,   153,    97,    98,    79,
      80,    81,    35,    96,   178,   181,    36,   101,    71,   103,
     104,   105,   106,   107,   108,   109,   110,   111,   112,   113,
     114,   115,   116,    75,   117,   119,     1,     2,     3,     4,
       5,     6,     7,     8,    66,   102,     9,    10,    11,    12,
      13,    14,    15,    16,     1,     2,     3,     4,     5,   120,
      38,   136,    81,    38,   134,   138,    11,    31,    30,    30,
      31,    30,   140,   139,   164,   135,    31,    30,   141,    31,
      30,   171,   172,    38,   143,   159,   162,   165,   177,   168,
      38,   180,   158,    31,    30,   160,   169,    31,    30,    31,
      30,    77,    78,    79,    80,    81,    31,    30,     1,     2,
       3,     4,     5,     6,     7,     8,   170,   176,     9,    10,
      11,    12,    13,    14,    15,    16,     1,     2,     3,     4,
       5,     6,     7,     8,   175,   179,     9,    10,    11,    12,
      13,    14,    15,    16,   182,    57,    58,   137,    11,    12,
      13,    14,    15,    16,   121,    95,     1,     2,     3,     4,
       5,     6,     7,     8,   148,   157,     9,    10,    11,    12,
      13,    14,    15,    16,    77,    78,    79,    80,    81,   127,
       0,    82,    83,    84,    85,    86,    87,    88,    89,     0,
       0,     0,     0,   118,     0,   161,     1,     2,     3,     4,
       5,     6,     7,     8,     0,     0,     9,    10,    11,    12,
      13,    14,    15,    16,    76,     0,    77,    78,    79,    80,
      81,     0,     0,    82,    83,    84,    85,    86,    87,    88,
      89,    91,     0,    77,    78,    79,    80,    81,     0,     0,
      82,    83,    84,    85,    86,    87,    88,    89,    94,     0,
      77,    78,    79,    80,    81,     0,     0,    82,    83,    84,
      85,    86,    87,    88,    89,    77,    78,    79,    80,    81,
       0,     0,    82,    83,    84,    85,    86,    87,    88,    89,
     100,    99,    77,    78,    79,    80,    81,     0,     0,    82,
      83,    84,    85,    86,    87,    88,    89,    77,    78,    79,
      80,    81,     0,     0,    82,    83,    84,    85,    86,    87,
      88,    89,     0,   122,    77,    78,    79,    80,    81,     0,
       0,    82,    83,    84,    85,    86,    87,    88,    89,   125,
     124,    77,    78,    79,    80,    81,     0,     0,    82,    83,
      84,    85,    86,    87,    88,    89,    77,    78,    79,    80,
      81,     0,     0,    82,    83,    84,    85,    86,    87,    88,
      89,     0,   128,    77,    78,    79,    80,    81,     0,     0,
      82,    83,    84,    85,    86,    87,    88,    89,     0,   146,
      77,    78,    79,    80,    81,     0,     0,    82,    83,    84,
      85,    86,    87,    88,    89,     0,   163,    90,    77,    78,
      79,    80,    81,     0,     0,    82,    83,    84,    85,    86,
      87,    88,    89,    77,    78,    79,    80,    81,     0,     0,
      82,    83,    84,    85,    86,    87,    88,    89,    77,    78,
      79,    80,    81,     0,     0,    82,    83,    84,    85,    86,
      87,     0,    89,    11,    12,    13,    14,    15,    16,    49,
       0,     0,     0,    50,     0,     0,     0,    51,    77,    78,
      79,    80,    81,     0,     0,    82,    83,    84,    85,    86,
      87
};

static const yytype_int16 yycheck[] =
{
       0,     0,    18,    10,    99,    30,   117,    30,    23,   120,
      23,    30,    23,    11,    39,    21,    39,    15,    18,    18,
      39,    23,    22,    15,    32,    33,    34,    42,    36,    23,
      43,    42,   143,   128,    41,    35,   147,    45,    46,    39,
      42,    49,    50,    51,    30,    23,    23,    30,    42,    44,
      45,    59,    21,    39,     0,    21,    39,    65,    66,    26,
      27,    28,    21,    63,    42,    42,    21,    75,    43,    77,
      78,    79,    80,    81,    82,    83,    84,    85,    86,    87,
      88,    89,    90,    39,    41,    93,     3,     4,     5,     6,
       7,     8,     9,    10,    39,    43,    13,    14,    15,    16,
      17,    18,    19,    20,     3,     4,     5,     6,     7,    41,
     126,    22,    28,   129,    43,    41,    15,   117,   117,   118,
     120,   120,    43,   131,   162,    42,   126,   126,    12,   129,
     129,   169,   170,   149,    41,    41,    41,    30,   176,    41,
     156,   179,   150,   143,   143,   153,    41,   147,   147,   149,
     149,    24,    25,    26,    27,    28,   156,   156,     3,     4,
       5,     6,     7,     8,     9,    10,    41,    41,    13,    14,
      15,    16,    17,    18,    19,    20,     3,     4,     5,     6,
       7,     8,     9,    10,    42,    41,    13,    14,    15,    16,
      17,    18,    19,    20,    42,    35,    35,    42,    15,    16,
      17,    18,    19,    20,    96,    62,     3,     4,     5,     6,
       7,     8,     9,    10,   141,    42,    13,    14,    15,    16,
      17,    18,    19,    20,    24,    25,    26,    27,    28,   118,
      -1,    31,    32,    33,    34,    35,    36,    37,    38,    -1,
      -1,    -1,    -1,    43,    -1,    42,     3,     4,     5,     6,
       7,     8,     9,    10,    -1,    -1,    13,    14,    15,    16,
      17,    18,    19,    20,    22,    -1,    24,    25,    26,    27,
      28,    -1,    -1,    31,    32,    33,    34,    35,    36,    37,
      38,    22,    -1,    24,    25,    26,    27,    28,    -1,    -1,
      31,    32,    33,    34,    35,    36,    37,    38,    22,    -1,
      24,    25,    26,    27,    28,    -1,    -1,    31,    32,    33,
      34,    35,    36,    37,    38,    24,    25,    26,    27,    28,
      -1,    -1,    31,    32,    33,    34,    35,    36,    37,    38,
      22,    40,    24,    25,    26,    27,    28,    -1,    -1,    31,
      32,    33,    34,    35,    36,    37,    38,    24,    25,    26,
      27,    28,    -1,    -1,    31,    32,    33,    34,    35,    36,
      37,    38,    -1,    40,    24,    25,    26,    27,    28,    -1,
      -1,    31,    32,    33,    34,    35,    36,    37,    38,    22,
      40,    24,    25,    26,    27,    28,    -1,    -1,    31,    32,
      33,    34,    35,    36,    37,    38,    24,    25,    26,    27,
      28,    -1,    -1,    31,    32,    33,    34,    35,    36,    37,
      38,    -1,    40,    24,    25,    26,    27,    28,    -1,    -1,
      31,    32,    33,    34,    35,    36,    37,    38,    -1,    40,
      24,    25,    26,    27,    28,    -1,    -1,    31,    32,    33,
      34,    35,    36,    37,    38,    -1,    40,    23,    24,    25,
      26,    27,    28,    -1,    -1,    31,    32,    33,    34,    35,
      36,    37,    38,    24,    25,    26,    27,    28,    -1,    -1,
      31,    32,    33,    34,    35,    36,    37,    38,    24,    25,
      26,    27,    28,    -1,    -1,    31,    32,    33,    34,    35,
      36,    -1,    38,    15,    16,    17,    18,    19,    20,    21,
      -1,    -1,    -1,    25,    -1,    -1,    -1,    29,    24,    25,
      26,    27,    28,    -1,    -1,    31,    32,    33,    34,    35,
      36
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,     4,     5,     6,     7,     8,     9,    10,    13,
      14,    15,    16,    17,    18,    19,    20,    47,    48,    49,
      50,    52,    54,    64,    65,    66,    67,    69,    70,    72,
      73,    75,    21,    21,    21,    21,    21,     0,    49,    11,
      53,    55,    75,    44,    45,    30,    39,    51,    74,    21,
      25,    29,    73,    75,    76,    76,    76,    50,    52,    71,
      75,    76,    75,    23,    43,    30,    39,    56,    57,    76,
      76,    43,    76,    76,    76,    39,    22,    24,    25,    26,
      27,    28,    31,    32,    33,    34,    35,    36,    37,    38,
      23,    22,    76,    39,    22,    57,    75,    76,    76,    40,
      22,    76,    43,    76,    76,    76,    76,    76,    76,    76,
      76,    76,    76,    76,    76,    76,    76,    41,    43,    76,
      41,    56,    40,    51,    40,    22,    48,    72,    40,    48,
      30,    39,    58,    60,    43,    42,    22,    42,    41,    76,
      43,    12,    68,    41,    63,    76,    40,    41,    67,    48,
      23,    42,    30,    39,    59,    61,    48,    42,    76,    41,
      76,    42,    41,    40,    63,    30,    62,    42,    41,    41,
      41,    63,    63,    42,    42,    42,    41,    63,    42,    41,
      63,    42,    42
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    46,    47,    48,    48,    49,    49,    49,    49,    49,
      49,    49,    49,    50,    51,    51,    52,    53,    53,    54,
      54,    54,    54,    54,    55,    55,    56,    56,    56,    57,
      58,    58,    59,    59,    60,    60,    61,    61,    62,    62,
      63,    63,    64,    64,    64,    64,    64,    65,    66,    67,
      68,    68,    68,    69,    70,    71,    71,    72,    72,    73,
      73,    74,    74,    75,    76,    76,    76,    76,    76,    76,
      76,    76,    76,    76,    76,    76,    76,    76,    76,    76,
      76
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     2,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     3,     2,     4,     2,     2,     3,     1,
       1,     1,     1,     1,     4,     2,     2,     1,     0,     5,
       4,     1,     4,     1,     4,     0,     9,     0,    12,     0,
       3,     1,     1,     1,     1,     1,     1,     5,     7,     8,
       2,     4,     0,    10,     7,     1,     1,     2,     2,     1,
       2,     3,     0,     1,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     2,     1,     3,
       2
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
do                                                              \
  if (yychar == YYEMPTY)                                        \
    {                                                           \
      yychar = (Token);                                         \
      yylval = (Value);                                         \
      YYPOPSTACK (yylen);                                       \
      yystate = *yyssp;                                         \
      goto yybackup;                                            \
    }                                                           \
  else                                                          \
    {                                                           \
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;                                                  \
    }                                                           \
while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)                                \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;        \
          (Current).first_column = YYRHSLOC (Rhs, 1).first_column;      \
          (Current).last_line    = YYRHSLOC (Rhs, N).last_line;         \
          (Current).last_column  = YYRHSLOC (Rhs, N).last_column;       \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).first_line   = (Current).last_line   =              \
            YYRHSLOC (Rhs, 0).last_line;                                \
          (Current).first_column = (Current).last_column =              \
            YYRHSLOC (Rhs, 0).last_column;                              \
        }                                                               \
    while (0)
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K])


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL

/* Print *YYLOCP on YYO.  Private, do not rely on its existence. */

YY_ATTRIBUTE_UNUSED
static unsigned
yy_location_print_ (FILE *yyo, YYLTYPE const * const yylocp)
{
  unsigned res = 0;
  int end_col = 0 != yylocp->last_column ? yylocp->last_column - 1 : 0;
  if (0 <= yylocp->first_line)
    {
      res += YYFPRINTF (yyo, "%d", yylocp->first_line);
      if (0 <= yylocp->first_column)
        res += YYFPRINTF (yyo, ".%d", yylocp->first_column);
    }
  if (0 <= yylocp->last_line)
    {
      if (yylocp->first_line < yylocp->last_line)
        {
          res += YYFPRINTF (yyo, "-%d", yylocp->last_line);
          if (0 <= end_col)
            res += YYFPRINTF (yyo, ".%d", end_col);
        }
      else if (0 <= end_col && yylocp->first_column < end_col)
        res += YYFPRINTF (yyo, "-%d", end_col);
    }
  return res;
 }

#  define YY_LOCATION_PRINT(File, Loc)          \
  yy_location_print_ (File, &(Loc))

# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value, Location); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  YYUSE (yylocationp);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  YY_LOCATION_PRINT (yyoutput, *yylocationp);
  YYFPRINTF (yyoutput, ": ");
  yy_symbol_value_print (yyoutput, yytype, yyvaluep, yylocationp);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, YYLTYPE *yylsp, int yyrule)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                       , &(yylsp[(yyi + 1) - (yynrhs)])                       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, yylsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen (const char *yystr)
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            /* Fall through.  */
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, YYLTYPE *yylocationp)
{
  YYUSE (yyvaluep);
  YYUSE (yylocationp);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Location data for the lookahead symbol.  */
YYLTYPE yylloc
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
  = { 1, 1, 1, 1 }
# endif
;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.
       'yyls': related to locations.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    /* The location stack.  */
    YYLTYPE yylsa[YYINITDEPTH];
    YYLTYPE *yyls;
    YYLTYPE *yylsp;

    /* The locations where the error started and ended.  */
    YYLTYPE yyerror_range[3];

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yylsp = yyls = yylsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  yylsp[0] = yylloc;
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        YYSTYPE *yyvs1 = yyvs;
        yytype_int16 *yyss1 = yyss;
        YYLTYPE *yyls1 = yyls;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yyls1, yysize * sizeof (*yylsp),
                    &yystacksize);

        yyls = yyls1;
        yyss = yyss1;
        yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yytype_int16 *yyss1 = yyss;
        union yyalloc *yyptr =
          (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
        YYSTACK_RELOCATE (yyls_alloc, yyls);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END
  *++yylsp = yylloc;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];

  /* Default location.  */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
#line 112 "sintactico.y" /* yacc.c:1646  */
    { root = (yyvsp[0].Node); }
#line 1576 "parser.cpp" /* yacc.c:1646  */
    break;

  case 3:
#line 116 "sintactico.y" /* yacc.c:1646  */
    {
        (yyval.Node) = (yyvsp[-1].Node);
        (yyval.Node)->add((yyvsp[0].Node));
      }
#line 1585 "parser.cpp" /* yacc.c:1646  */
    break;

  case 4:
#line 121 "sintactico.y" /* yacc.c:1646  */
    {
        (yyval.Node) = new node(yylineno, columna,"cuerpo","cuerpo");
        (yyval.Node)->add((yyvsp[0].Node));
      }
#line 1594 "parser.cpp" /* yacc.c:1646  */
    break;

  case 5:
#line 127 "sintactico.y" /* yacc.c:1646  */
    {(yyval.Node) = (yyvsp[0].Node);}
#line 1600 "parser.cpp" /* yacc.c:1646  */
    break;

  case 6:
#line 128 "sintactico.y" /* yacc.c:1646  */
    {(yyval.Node) = (yyvsp[0].Node);}
#line 1606 "parser.cpp" /* yacc.c:1646  */
    break;

  case 7:
#line 129 "sintactico.y" /* yacc.c:1646  */
    {(yyval.Node) = (yyvsp[0].Node);}
#line 1612 "parser.cpp" /* yacc.c:1646  */
    break;

  case 8:
#line 130 "sintactico.y" /* yacc.c:1646  */
    {(yyval.Node) = (yyvsp[0].Node);}
#line 1618 "parser.cpp" /* yacc.c:1646  */
    break;

  case 9:
#line 131 "sintactico.y" /* yacc.c:1646  */
    {(yyval.Node) = (yyvsp[0].Node);}
#line 1624 "parser.cpp" /* yacc.c:1646  */
    break;

  case 10:
#line 132 "sintactico.y" /* yacc.c:1646  */
    {(yyval.Node) = (yyvsp[0].Node);}
#line 1630 "parser.cpp" /* yacc.c:1646  */
    break;

  case 11:
#line 133 "sintactico.y" /* yacc.c:1646  */
    {(yyval.Node) = (yyvsp[0].Node);}
#line 1636 "parser.cpp" /* yacc.c:1646  */
    break;

  case 12:
#line 134 "sintactico.y" /* yacc.c:1646  */
    {(yyval.Node) = (yyvsp[0].Node);}
#line 1642 "parser.cpp" /* yacc.c:1646  */
    break;

  case 13:
#line 138 "sintactico.y" /* yacc.c:1646  */
    { 
          (yyval.Node) = new node(yylineno, columna,"asignacion","asignacion"); 
          (yyval.Node)->add((yyvsp[-2].Node));
          (yyval.Node)->add((yyvsp[-1].Node));
        }
#line 1652 "parser.cpp" /* yacc.c:1646  */
    break;

  case 14:
#line 146 "sintactico.y" /* yacc.c:1646  */
    {
          (yyval.Node)= (yyvsp[0].Node);
        }
#line 1660 "parser.cpp" /* yacc.c:1646  */
    break;

  case 15:
#line 150 "sintactico.y" /* yacc.c:1646  */
    { 
          (yyval.Node) = new node(yylineno, columna,"indice",(yyvsp[-2].Node)->valor);
          (yyval.Node)->add((yyvsp[0].Node));
        }
#line 1669 "parser.cpp" /* yacc.c:1646  */
    break;

  case 16:
#line 157 "sintactico.y" /* yacc.c:1646  */
    {
          (yyval.Node) = new node(yylineno, columna,"declaracion","declaracion");
          (yyval.Node)->add((yyvsp[-1].Node));
          (yyval.Node)->add((yyvsp[0].Node));
        }
#line 1679 "parser.cpp" /* yacc.c:1646  */
    break;

  case 17:
#line 165 "sintactico.y" /* yacc.c:1646  */
    {
                (yyval.Node) = (yyvsp[-1].Node);
              }
#line 1687 "parser.cpp" /* yacc.c:1646  */
    break;

  case 18:
#line 169 "sintactico.y" /* yacc.c:1646  */
    {
                (yyval.Node) = new node(yylineno, columna,"arreglo","arreglo");
                (yyval.Node)->add((yyvsp[-1].Node));
                (yyval.Node)->add((yyvsp[0].Node));
              }
#line 1697 "parser.cpp" /* yacc.c:1646  */
    break;

  case 19:
#line 176 "sintactico.y" /* yacc.c:1646  */
    { (yyval.Node) = new node(yylineno, columna,"reservada",yytext);}
#line 1703 "parser.cpp" /* yacc.c:1646  */
    break;

  case 20:
#line 177 "sintactico.y" /* yacc.c:1646  */
    { (yyval.Node) = new node(yylineno, columna,"reservada",yytext);}
#line 1709 "parser.cpp" /* yacc.c:1646  */
    break;

  case 21:
#line 178 "sintactico.y" /* yacc.c:1646  */
    { (yyval.Node) = new node(yylineno, columna,"reservada",yytext);}
#line 1715 "parser.cpp" /* yacc.c:1646  */
    break;

  case 22:
#line 179 "sintactico.y" /* yacc.c:1646  */
    { (yyval.Node) = new node(yylineno, columna,"reservada",yytext); }
#line 1721 "parser.cpp" /* yacc.c:1646  */
    break;

  case 23:
#line 180 "sintactico.y" /* yacc.c:1646  */
    { (yyval.Node) = new node(yylineno, columna,"reservada",yytext);}
#line 1727 "parser.cpp" /* yacc.c:1646  */
    break;

  case 24:
#line 184 "sintactico.y" /* yacc.c:1646  */
    { 
          (yyval.Node) = (yyvsp[-3].Node);
          node *nod;
          if((yyvsp[0].Node) == nullptr)
          {
              nod = new node(yylineno, columna,"declaracion","declaracion");
              nod->add((yyvsp[-1].Node));
          }
          else
          {
              nod = new node(yylineno, columna,"asignacion","asignacion");
              nod->add((yyvsp[-1].Node));
              nod->add((yyvsp[0].Node));
          }
          (yyval.Node)->add(nod);
        }
#line 1748 "parser.cpp" /* yacc.c:1646  */
    break;

  case 25:
#line 201 "sintactico.y" /* yacc.c:1646  */
    { 
        (yyval.Node) = new node(yylineno, columna,"asignaciones","asignaciones");
        node *nod;
        if((yyvsp[0].Node) == nullptr)
        {
            nod = new node(yylineno, columna,"declaracion","declaracion");
            nod->add((yyvsp[-1].Node));
        }
        else
        {
            nod = new node(yylineno, columna,"asignacion","asignacion");
            nod->add((yyvsp[-1].Node));
            nod->add((yyvsp[0].Node));
        }
        (yyval.Node)->add(nod);
      }
#line 1769 "parser.cpp" /* yacc.c:1646  */
    break;

  case 26:
#line 219 "sintactico.y" /* yacc.c:1646  */
    { (yyval.Node) = (yyvsp[0].Node); }
#line 1775 "parser.cpp" /* yacc.c:1646  */
    break;

  case 27:
#line 220 "sintactico.y" /* yacc.c:1646  */
    { (yyval.Node) = (yyvsp[0].Node); }
#line 1781 "parser.cpp" /* yacc.c:1646  */
    break;

  case 28:
#line 221 "sintactico.y" /* yacc.c:1646  */
    { (yyval.Node) = nullptr; }
#line 1787 "parser.cpp" /* yacc.c:1646  */
    break;

  case 29:
#line 225 "sintactico.y" /* yacc.c:1646  */
    {
      (yyval.Node) = new node(yylineno, columna,"newDimension","newDimension");;
      (yyval.Node)->add((yyvsp[-3].Node));
      if((yyvsp[-1].Node) != nullptr)
        (yyval.Node)->add((yyvsp[-1].Node));
    }
#line 1798 "parser.cpp" /* yacc.c:1646  */
    break;

  case 30:
#line 234 "sintactico.y" /* yacc.c:1646  */
    {
        (yyval.Node) = new node(yylineno, columna,"newDimension","newDimension");;
        (yyval.Node)->add((yyvsp[-2].Node));
        if((yyvsp[0].Node) != nullptr)
          (yyval.Node)->add((yyvsp[0].Node));
      }
#line 1809 "parser.cpp" /* yacc.c:1646  */
    break;

  case 31:
#line 240 "sintactico.y" /* yacc.c:1646  */
    {(yyval.Node) = (yyvsp[0].Node);}
#line 1815 "parser.cpp" /* yacc.c:1646  */
    break;

  case 32:
#line 244 "sintactico.y" /* yacc.c:1646  */
    {
        (yyval.Node) = new node(yylineno, columna,"newDimension","newDimension");;
        (yyval.Node)->add((yyvsp[-2].Node));
        if((yyvsp[0].Node) != nullptr)
          (yyval.Node)->add((yyvsp[0].Node));
      }
#line 1826 "parser.cpp" /* yacc.c:1646  */
    break;

  case 34:
#line 253 "sintactico.y" /* yacc.c:1646  */
    { (yyval.Node) = (yyvsp[-1].Node); }
#line 1832 "parser.cpp" /* yacc.c:1646  */
    break;

  case 35:
#line 254 "sintactico.y" /* yacc.c:1646  */
    { (yyval.Node) = nullptr; }
#line 1838 "parser.cpp" /* yacc.c:1646  */
    break;

  case 36:
#line 257 "sintactico.y" /* yacc.c:1646  */
    { (yyval.Node)= new node(yylineno, columna,"doubleList","doubleList");
            (yyval.Node)->add((yyvsp[-5].Node)); (yyval.Node)->add((yyvsp[-2].Node)); }
#line 1845 "parser.cpp" /* yacc.c:1646  */
    break;

  case 37:
#line 259 "sintactico.y" /* yacc.c:1646  */
    { (yyval.Node) = nullptr; }
#line 1851 "parser.cpp" /* yacc.c:1646  */
    break;

  case 38:
#line 262 "sintactico.y" /* yacc.c:1646  */
    { (yyval.Node)= new node(yylineno, columna,"tripleList","tripleList");
            (yyval.Node)->add((yyvsp[-8].Node)); (yyval.Node)->add((yyvsp[-5].Node)); (yyval.Node)->add((yyvsp[-2].Node));}
#line 1858 "parser.cpp" /* yacc.c:1646  */
    break;

  case 39:
#line 264 "sintactico.y" /* yacc.c:1646  */
    { (yyval.Node) = nullptr; }
#line 1864 "parser.cpp" /* yacc.c:1646  */
    break;

  case 40:
#line 268 "sintactico.y" /* yacc.c:1646  */
    {
            (yyval.Node)= (yyvsp[-2].Node);
            (yyval.Node)->add((yyvsp[0].Node));
        }
#line 1873 "parser.cpp" /* yacc.c:1646  */
    break;

  case 41:
#line 273 "sintactico.y" /* yacc.c:1646  */
    {
            (yyval.Node)= new node(yylineno, columna,"lista","lista");
            (yyval.Node)->add((yyvsp[0].Node));
        }
#line 1882 "parser.cpp" /* yacc.c:1646  */
    break;

  case 42:
#line 279 "sintactico.y" /* yacc.c:1646  */
    { (yyval.Node) = new node(yylineno, columna,"int",yytext);}
#line 1888 "parser.cpp" /* yacc.c:1646  */
    break;

  case 43:
#line 280 "sintactico.y" /* yacc.c:1646  */
    { (yyval.Node) = new node(yylineno, columna,"char",yytext);}
#line 1894 "parser.cpp" /* yacc.c:1646  */
    break;

  case 44:
#line 281 "sintactico.y" /* yacc.c:1646  */
    { (yyval.Node) = new node(yylineno, columna,"string",yytext);}
#line 1900 "parser.cpp" /* yacc.c:1646  */
    break;

  case 45:
#line 282 "sintactico.y" /* yacc.c:1646  */
    { (yyval.Node) = new node(yylineno, columna,"bool",yytext);}
#line 1906 "parser.cpp" /* yacc.c:1646  */
    break;

  case 46:
#line 283 "sintactico.y" /* yacc.c:1646  */
    { (yyval.Node) = new node(yylineno, columna,"double",yytext);}
#line 1912 "parser.cpp" /* yacc.c:1646  */
    break;

  case 47:
#line 286 "sintactico.y" /* yacc.c:1646  */
    {node *nod = new node(yylineno, columna,"print",(yyvsp[-4].TEXT)); nod->add((yyvsp[-2].Node)); (yyval.Node)=nod;}
#line 1918 "parser.cpp" /* yacc.c:1646  */
    break;

  case 48:
#line 289 "sintactico.y" /* yacc.c:1646  */
    {node *nod = new node(yylineno, columna,"show",(yyvsp[-6].TEXT)); nod->add((yyvsp[-4].Node)); nod->add((yyvsp[-2].Node)); (yyval.Node)=nod;}
#line 1924 "parser.cpp" /* yacc.c:1646  */
    break;

  case 49:
#line 293 "sintactico.y" /* yacc.c:1646  */
    {
  (yyval.Node) = new node(yylineno, columna,"if","if");
  node *block = new node(yylineno, columna,"sentencia","sentencia");
  block->add((yyvsp[-5].Node));
  block->add((yyvsp[-2].Node));
  (yyval.Node)->add(block);
  (yyval.Node)->add((yyvsp[0].Node));
}
#line 1937 "parser.cpp" /* yacc.c:1646  */
    break;

  case 50:
#line 303 "sintactico.y" /* yacc.c:1646  */
    {(yyval.Node) = (yyvsp[0].Node);}
#line 1943 "parser.cpp" /* yacc.c:1646  */
    break;

  case 51:
#line 304 "sintactico.y" /* yacc.c:1646  */
    {
       (yyval.Node) = new node(yylineno, columna,"defaultSentence","defaultSentence");
       (yyval.Node)->add((yyvsp[-1].Node));
      }
#line 1952 "parser.cpp" /* yacc.c:1646  */
    break;

  case 52:
#line 308 "sintactico.y" /* yacc.c:1646  */
    {(yyval.Node) = nullptr;}
#line 1958 "parser.cpp" /* yacc.c:1646  */
    break;

  case 53:
#line 311 "sintactico.y" /* yacc.c:1646  */
    {
  node *nod = new node(yylineno, columna,"for","for");
  nod->add((yyvsp[-7].Node)); nod->add((yyvsp[-6].Node)); nod->add((yyvsp[-4].Node)); nod->add((yyvsp[-1].Node));
  (yyval.Node)=nod;
}
#line 1968 "parser.cpp" /* yacc.c:1646  */
    break;

  case 54:
#line 318 "sintactico.y" /* yacc.c:1646  */
    {
  node *nod = new node(yylineno, columna,"while","while"); 
  nod->add((yyvsp[-4].Node)); nod->add((yyvsp[-1].Node));
  (yyval.Node)=nod;
}
#line 1978 "parser.cpp" /* yacc.c:1646  */
    break;

  case 55:
#line 325 "sintactico.y" /* yacc.c:1646  */
    { (yyval.Node) = (yyvsp[0].Node); }
#line 1984 "parser.cpp" /* yacc.c:1646  */
    break;

  case 56:
#line 326 "sintactico.y" /* yacc.c:1646  */
    { (yyval.Node) = (yyvsp[0].Node); }
#line 1990 "parser.cpp" /* yacc.c:1646  */
    break;

  case 57:
#line 329 "sintactico.y" /* yacc.c:1646  */
    { (yyval.Node) = new node(yylineno, columna,"increase",(yyvsp[0].TEXT)); (yyval.Node)->add((yyvsp[-1].Node));}
#line 1996 "parser.cpp" /* yacc.c:1646  */
    break;

  case 58:
#line 330 "sintactico.y" /* yacc.c:1646  */
    { (yyval.Node) = new node(yylineno, columna,"decrease",(yyvsp[0].TEXT)); (yyval.Node)->add((yyvsp[-1].Node));}
#line 2002 "parser.cpp" /* yacc.c:1646  */
    break;

  case 59:
#line 333 "sintactico.y" /* yacc.c:1646  */
    { (yyval.Node) = (yyvsp[0].Node); }
#line 2008 "parser.cpp" /* yacc.c:1646  */
    break;

  case 60:
#line 334 "sintactico.y" /* yacc.c:1646  */
    {
    if((yyvsp[0].Node)==nullptr)
    {
        (yyval.Node) = (yyvsp[-1].Node);
    }
    else
    {
        (yyval.Node) = new node(yylineno, columna,"arregloIndex",yytext);
        (yyval.Node)->add((yyvsp[-1].Node));
        (yyval.Node)->add((yyvsp[0].Node));
    }
  }
#line 2025 "parser.cpp" /* yacc.c:1646  */
    break;

  case 61:
#line 349 "sintactico.y" /* yacc.c:1646  */
    {
           (yyval.Node)=(yyvsp[-1].Node);
        }
#line 2033 "parser.cpp" /* yacc.c:1646  */
    break;

  case 62:
#line 352 "sintactico.y" /* yacc.c:1646  */
    {(yyval.Node)=nullptr;}
#line 2039 "parser.cpp" /* yacc.c:1646  */
    break;

  case 63:
#line 355 "sintactico.y" /* yacc.c:1646  */
    {
  (yyval.Node) = new node(yylineno, columna,"identificador",yytext);
}
#line 2047 "parser.cpp" /* yacc.c:1646  */
    break;

  case 64:
#line 360 "sintactico.y" /* yacc.c:1646  */
    {node *nod = new node(yylineno, columna,"suma",(yyvsp[-1].TEXT));  nod->add((yyvsp[-2].Node)); nod->add((yyvsp[0].Node)); (yyval.Node)=nod;}
#line 2053 "parser.cpp" /* yacc.c:1646  */
    break;

  case 65:
#line 361 "sintactico.y" /* yacc.c:1646  */
    {node *nod = new node(yylineno, columna,"resta",(yyvsp[-1].TEXT));  nod->add((yyvsp[-2].Node)); nod->add((yyvsp[0].Node)); (yyval.Node)=nod;}
#line 2059 "parser.cpp" /* yacc.c:1646  */
    break;

  case 66:
#line 362 "sintactico.y" /* yacc.c:1646  */
    {node *nod = new node(yylineno, columna,"multi",(yyvsp[-1].TEXT));  nod->add((yyvsp[-2].Node)); nod->add((yyvsp[0].Node)); (yyval.Node)=nod;}
#line 2065 "parser.cpp" /* yacc.c:1646  */
    break;

  case 67:
#line 363 "sintactico.y" /* yacc.c:1646  */
    {node *nod = new node(yylineno, columna,"div",(yyvsp[-1].TEXT));  nod->add((yyvsp[-2].Node)); nod->add((yyvsp[0].Node)); (yyval.Node)=nod;}
#line 2071 "parser.cpp" /* yacc.c:1646  */
    break;

  case 68:
#line 364 "sintactico.y" /* yacc.c:1646  */
    {node *nod = new node(yylineno, columna,"potencia",(yyvsp[-1].TEXT));  nod->add((yyvsp[-2].Node)); nod->add((yyvsp[0].Node)); (yyval.Node)=nod;}
#line 2077 "parser.cpp" /* yacc.c:1646  */
    break;

  case 69:
#line 365 "sintactico.y" /* yacc.c:1646  */
    {node *nod = new node(yylineno, columna,"igualacion",(yyvsp[-1].TEXT));  nod->add((yyvsp[-2].Node)); nod->add((yyvsp[0].Node)); (yyval.Node)=nod;}
#line 2083 "parser.cpp" /* yacc.c:1646  */
    break;

  case 70:
#line 366 "sintactico.y" /* yacc.c:1646  */
    {node *nod = new node(yylineno, columna,"dif",(yyvsp[-1].TEXT));  nod->add((yyvsp[-2].Node)); nod->add((yyvsp[0].Node)); (yyval.Node)=nod;}
#line 2089 "parser.cpp" /* yacc.c:1646  */
    break;

  case 71:
#line 367 "sintactico.y" /* yacc.c:1646  */
    {node *nod = new node(yylineno, columna,"menque",(yyvsp[-1].TEXT));  nod->add((yyvsp[-2].Node)); nod->add((yyvsp[0].Node)); (yyval.Node)=nod;}
#line 2095 "parser.cpp" /* yacc.c:1646  */
    break;

  case 72:
#line 368 "sintactico.y" /* yacc.c:1646  */
    {node *nod = new node(yylineno, columna,"mayque",(yyvsp[-1].TEXT));  nod->add((yyvsp[-2].Node)); nod->add((yyvsp[0].Node)); (yyval.Node)=nod;}
#line 2101 "parser.cpp" /* yacc.c:1646  */
    break;

  case 73:
#line 369 "sintactico.y" /* yacc.c:1646  */
    {node *nod = new node(yylineno, columna,"menoig",(yyvsp[-1].TEXT));  nod->add((yyvsp[-2].Node)); nod->add((yyvsp[0].Node)); (yyval.Node)=nod;}
#line 2107 "parser.cpp" /* yacc.c:1646  */
    break;

  case 74:
#line 370 "sintactico.y" /* yacc.c:1646  */
    {node *nod = new node(yylineno, columna,"mayoig",(yyvsp[-1].TEXT));  nod->add((yyvsp[-2].Node)); nod->add((yyvsp[0].Node)); (yyval.Node)=nod;}
#line 2113 "parser.cpp" /* yacc.c:1646  */
    break;

  case 75:
#line 371 "sintactico.y" /* yacc.c:1646  */
    {node *nod = new node(yylineno, columna,"tor",(yyvsp[-1].TEXT));  nod->add((yyvsp[-2].Node)); nod->add((yyvsp[0].Node)); (yyval.Node)=nod;}
#line 2119 "parser.cpp" /* yacc.c:1646  */
    break;

  case 76:
#line 372 "sintactico.y" /* yacc.c:1646  */
    {node *nod = new node(yylineno, columna,"tand",(yyvsp[-1].TEXT));  nod->add((yyvsp[-2].Node)); nod->add((yyvsp[0].Node)); (yyval.Node)=nod;}
#line 2125 "parser.cpp" /* yacc.c:1646  */
    break;

  case 77:
#line 373 "sintactico.y" /* yacc.c:1646  */
    { (yyval.Node) = new node(yylineno, columna,(yyvsp[-1].TEXT),(yyvsp[-1].TEXT)); (yyval.Node)->add((yyvsp[0].Node));}
#line 2131 "parser.cpp" /* yacc.c:1646  */
    break;

  case 78:
#line 374 "sintactico.y" /* yacc.c:1646  */
    { (yyval.Node) = (yyvsp[0].Node); }
#line 2137 "parser.cpp" /* yacc.c:1646  */
    break;

  case 79:
#line 375 "sintactico.y" /* yacc.c:1646  */
    { (yyval.Node) = (yyvsp[-1].Node); }
#line 2143 "parser.cpp" /* yacc.c:1646  */
    break;

  case 80:
#line 376 "sintactico.y" /* yacc.c:1646  */
    { (yyval.Node) = new node(yylineno, columna,"minus",(yyvsp[-1].TEXT)); (yyval.Node)->add((yyvsp[0].Node));}
#line 2149 "parser.cpp" /* yacc.c:1646  */
    break;


#line 2153 "parser.cpp" /* yacc.c:1646  */
      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;
  *++yylsp = yyloc;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }

  yyerror_range[1] = yylloc;

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval, &yylloc);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  yyerror_range[1] = yylsp[1-yylen];
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;

      yyerror_range[1] = *yylsp;
      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp, yylsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  yyerror_range[2] = yylloc;
  /* Using YYLLOC is tempting, but would change the location of
     the lookahead.  YYLOC is available though.  */
  YYLLOC_DEFAULT (yyloc, yyerror_range, 2);
  *++yylsp = yyloc;

  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval, &yylloc);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[*yyssp], yyvsp, yylsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 379 "sintactico.y" /* yacc.c:1906  */

