#ifndef __OBSERVATEUR_H__
#define __OBSERVATEUR_H__


typedef enum {A , G , D , M } Alphabet ;

typedef enum {INIT , MES , ERR } Etat ;


Etat transition( Etat x , Alphabet a );
Etat transition2( Etat y , Alphabet a);
Etat initial();



#endif



