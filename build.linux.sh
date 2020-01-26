# compile mais ne link pas
g++ -c *.cpp

# link les fichiers *.o de compilation
# link sous le nom de puzzle
g++ *.o -o ./bin/aftest-shader -lsfml-graphics -lsfml-window -lsfml-system
./bin/aftest-shader
