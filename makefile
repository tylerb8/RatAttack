app:precomp
	g++ -c main.cpp player.cpp game.cpp bullet.cpp enemy.cpp bg.cpp boost.cpp menu.cpp instruct.cpp
	g++ main.o player.o game.o bullet.o enemy.o bg.o boost.o menu.o instruct.o -o app -lsfml-graphics -lsfml-window -lsfml-system
	./app

precomp:
	touch app
	rm app

clean:
	rm *.o 
	rm app
