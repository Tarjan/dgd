# ifndef H_HASH
# define H_HASH

typedef struct _hte_ {
    struct _hte_ *next;	/* next entry in hash table */
    char *name;		/* string to use in hashing */
} hte;

typedef struct {
    unsigned short size;	/* size of hash table */
    unsigned short maxlen;	/* max length of string to be used in hashing */
    hte *table[1];		/* hash table entries */
} hashtab;

extern unsigned short	hashstr	P((char*, unsigned short, unsigned short));

extern hashtab	       *ht_new		P((unsigned short, unsigned short));
extern void		ht_del		P((hashtab*, void P((hte*))));
extern hte	      **ht_lookup	P((hashtab*, char*));

# endif /* H_HASH */
