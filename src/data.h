# include "swap.h"

typedef struct {
    object *obj;		/* inherited object */
    unsigned short funcoffset;	/* function call offset */
    unsigned short varoffset;	/* variable offset */
} dinherit;

typedef struct {
    char class;			/* function class */
    char inherit;		/* function name inherit index */
    unsigned short index;	/* function name index */
    unsigned short offset;	/* offset in program text */
} dfuncdef;

typedef struct {
    char class;			/* variable class */
    char type;			/* variable type */
    char inherit;		/* variable name inherit index */
    unsigned short index;	/* variable name index */
} dvardef;

typedef struct {
    char inherit;		/* function object index */
    char index;			/* function index */
    unsigned short next;	/* next in hash table */
} dsymbol;

typedef struct _control_ {
    struct _control_ *prev, *next;

    uindex nsectors;		/* o # of sectors */
    sector *sectors;		/* o vector with sectors */

    char ninherits;		/* i/o # inherited objects */
    char nvirtuals;		/* i/o # virtually inherited objects */
    dinherit *inherits;		/* i/o inherit objects */

    char *prog;			/* i program text */
    unsigned short progsize;	/* i/o program text size */
    long progoffset;		/* o program text offset */

    unsigned short nstrings;	/* i/o # strings */
    string **strings;		/* i/o? string table */
    struct _sstrconst_ *sstrings;/* o sstrings */
    char *stext;		/* o sstrings text */
    long strsize;		/* o sstrings text size */
    long stroffset;		/* o offset of string index table */

    unsigned short nfuncdefs;	/* i/o # function definitions */
    dfuncdef *funcdefs;		/* i/o? function definition table */
    long funcdoffset;		/* o offset of function definition table */

    unsigned short nvardefs;	/* i/o # variable definitions */
    dvardef *vardefs;		/* i/o? variable definitions */
    long vardoffset;		/* o offset of variable definition table */

    uindex nfuncalls;		/* i/o # function calls */
    char *funcalls;		/* i/o? function calls */
    long funccoffset;		/* o offset of function call table */

    unsigned short nsymbols;	/* i/o # symbols */
    dsymbol *symbols;		/* i/o? symbol table */
    long symboffset;		/* o offset of symbol table */

    unsigned short nvariables;	/* i/o # variables */
} control;

typedef struct _strref_ {
    string *string;		/* string value */
    struct _dataspace_ *data;	/* dataspace this string is in */
    uindex ref;			/* # of refs */
} strref;

typedef struct _arrref_ {
    array *array;		/* array value */
    struct _dataspace_ *data;	/* dataspace this array is in */
    long index;			/* selts index */
    uindex ref;			/* # of refs */
} arrref;

typedef struct _dataspace_ {
    struct _dataspace_ *prev, *next;

    long achange;		/* # array changes */
    long schange;		/* # string changes */
    char modified;		/* has a variable or array elt been modified */

    object *obj;		/* object this dataspace belongs to */
    control *ctrl;		/* control block */

    uindex nsectors;		/* o # sectors */
    sector *sectors;		/* o vector of sectors */

    unsigned short nvariables;	/* o # variables */
    value *variables;		/* i/o variables */
    struct _svalue_ *svariables;/* o svariables */
    long varoffset;		/* o offset of variables in data space */

    uindex narrays;		/* i/o # arrays */
    long eltsize;		/* o total size of array elements */
    arrref *arrays;		/* i/o? arrays */
    struct _sarray_ *sarrays;	/* o sarrays */
    struct _svalue_ *selts;	/* o sarray elements */
    long arroffset;		/* o offset of array table in data space */

    uindex nstrings;		/* i/o # string constants */
    long strsize;		/* o total size of string text */
    strref *strings;		/* i/o? string constant table */
    struct _sstring_ *sstrings;	/* o sstrings */
    char *stext;		/* o sstrings text */
    long stroffset;		/* o offset of string table */
} dataspace;

extern control	 *d_new_control		P((void));
extern dataspace *d_new_dataspace	P((object*));

extern control	 *d_load_control	P((sector));
extern dataspace *d_load_dataspace	P((object*, sector));

extern char	 *d_get_prog		P((control*));
extern string	 *d_get_strconst	P((control*, char, unsigned short));
extern dfuncdef  *d_get_funcdefs	P((control*));
extern dvardef	 *d_get_vardefs		P((control*));
extern char	 *d_get_funcalls	P((control*));
extern dsymbol	 *d_get_symbols		P((control*));

extern value	 *d_get_variable	P((dataspace*, unsigned short));
extern value	 *d_get_elts		P((array*));

extern void	  d_assign_var		P((dataspace*, value*, value*));
extern void	  d_assign_elt		P((array*, unsigned short, value*));
extern void	  d_change_map		P((array*));

extern void	  d_clean		P((void));

extern void	  d_del_control		P((control*));
extern void	  d_del_dataspace	P((dataspace*));