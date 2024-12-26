#include<stdio.h>
#include<stdlib.h>
#include "observateur.h"

Etat initial() { return INIT; }

Etat transition( Etat x , Alphabet a ){
  switch ( x ) {
    case INIT :
      switch (a) {
        case  A :
          return ERR ;
        case M :
          return MES ;
        case G :
        case D :
          return INIT;
        }
      case MES :
        switch (a) {
          case  M :
            return MES ;
          case A :
          case D :
          case G :
            return INIT;
          }
      case ERR :
        return ERR;
          }
      }

Etat transition2( Etat y , Alphabet a ){
  switch(y){
    case INIT :
      switch (a) {
        case M :
          return ERR ;
        case A :
        case G :
        case D :
          return INIT ;
      }
    default :
      switch (a) {
        case M :
          return ERR ;
        case A :
        case G :
        case D :
          return INIT ;
      }
  }
}
 




