#ifndef ASCIIART_H
#define ASCIIART_H
namespace tetrisart {

const char* menuScreen = R"""( 
             _________  ______  _________  _____    ___     ___
             | /| |\ |  | |\ |  | /| |\ |  | |_ \   | |  /\ \ | TM
             |/ | | \|  | | \|  |/ | | \|  | |_| |  | |  \ \ \|
                | |     | |/|      | |     | |__/   | |   \ \  
                | |     | |\|      | |     | |\     | |    \ \
                | |     | | /|     | |     | | \    | |  |\ \ \
                |_|     |_|/_|     |_|     |_|__\   |_|  |_\ \/


                                  PUSH START


                                   Controls:          
                     UP : W / UP         ROTATE LEFT : Z / K
                   DOWN : S / DOWN      ROTATE RIGHT : X / L
                   LEFT : A / LEFT     START / PAUSE : SPACEBAR
                  RIGHT : D / RIGHT           SELECT : B
                             TOGGLE ENHANCEMENTS: E

)""";

const char* levelSelect = R"""(

                                    LEVEL:          
                          +------------------------+
                          | 00 | 01 | 02 | 03 | 04 |
                          +------------------------+
                          | 05 | 06 | 07 | 08 | 09 |
                          +------------------------+
                          | 10 | 11 | 12 | 13 | 14 |
                          +------------------------+
                          | 15 | 16 | 17 | 18 | 19 |
                          +------------------------+
 
                          +------------------------+
                          |      SCORE  LINES   LV |
                          | 1.                     |
                          | 2.                     |
                          | 3.                     |
                          +------------------------+
)""";

const char* launchpad = R"""(


                                SCORE





     
          
         __AAA             
         \ AAA--     tt  
          \AAA       tt 
nnnnnnnnnnnAAA       tt 
     unnnnnAAA       tt 
nnnnnh   MMMMMMMMMMMMMMMM 
..............................................................................
..............................................................................
..............................................................................
)""";

const char* cathedral = R"""(
           a       aa
 aa    aa /$\     /NN\
/HH\  /NN\   aa   \NN/
\HH/  \NN/  /HH\   NN
 HH    NN   \HH/   NN
EEEE  EEEE  EEEE  EEEE
######################
######################
 /\ ^^ /\ ^^ /\ ^^ /\ )""";

const char* gameover = R"""(                    
     GAME OVER!     
                    )""";
const char* paused = R"""(                    
       PAUSED       
                    )""";

const char* rocket1 = "i";
const char* rocket2 = " a \n/H\\\n|H|\n ^ ";
const char* rocket3 = R"""(  a  
 /H\
/|H|\
||H||
||H||
^ ^ ^)""";

const char* rocket4 = R"""(    a    
   /H\
  /|H|\
  ||*||
 /|/*\|\
 |/***\|
 ^^   ^^ )""";

const char* rocket5 = R"""( db
dhhb
 ^^ )""";

}
#endif
