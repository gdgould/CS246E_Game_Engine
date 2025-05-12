CXX = g++
CXXFLAGS = -std=c++14 -Wall -MMD -lncurses -g
EXEC = game1 game2
OBJECTS = engine/location.o engine/controller.o engine/cursescontrol.o engine/cursesview.o engine/texture.o engine/entity.o engine/moveline.o engine/movePlayerControlled.o engine/moveToBorder.o engine/game.o     tetris/pieceDrop.o tetris/piecelr.o tetris/rocketmovement.o tetris/piece.o tetris/grid.o  tetris/tetris.o   arlg/keytype.o arlg/arlgentity.o arlg/boss.o arlg/enemyProjectile.o arlg/exit.o arlg/fire.o arlg/health.o arlg/playerMove.o arlg/player.o arlg/playerProjectile.o arlg/popup.o arlg/snake.o arlg/stalkerMove.o arlg/stalker.o arlg/walker.o arlg/arlg.o
DEPENDS = ${OBJECTS:.o=.d}

all: game1 game2

game1: tetris/main.o ${OBJECTS}
	${CXX} tetris/main.o ${OBJECTS} ${GIVEN} -o game1 ${CXXFLAGS}

game2: arlg/main.o ${OBJECTS}
	${CXX} arlg/main.o ${OBJECTS} ${GIVEN} -o game2 ${CXXFLAGS}

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
