Рабочая среда Linux

Инструкция:  
sudo apt update  
sudo apt install git cmake g++ uuid-dev pkg-config  
git clone https://github.com/antlr/antlr4.git  
cd antlr4  
cd runtime/Cpp  
mkdir build  
cd build  
cmake ..  
make  
sudo make install  
export CPLUS_INCLUDE_PATH=/usr/local/include/antlr4-runtime:$CPLUS_INCLUDE_PATH  
export LIBRARY_PATH=/usr/local/lib:$LIBRARY_PATH  
export LD_LIBRARY_PATH=/usr/local/lib:$LD_LIBRARY_PATH  

Для генерации лексера и парсера  
curl -O https://www.antlr.org/download/antlr-4.13.1-complete.jar  
export CLASSPATH=".:/path/to/antlr-4.13.1-complete.jar:$CLASSPATH"  
alias antlr4='java -jar /path/to/antlr-4.13.1-complete.jar'  
alias grun='java org.antlr.v4.gui.TestRig'  

Генерация лексера и парсера  
antlr4 -Dlanguage=Cpp myGrammar.g4 -visitor   

Компиляция программы  
g++ main.cpp -o main -lantlr4-runtime DoWhileLoopLexer.cpp DoWhileLoopParser.cpp  

Запуск примера  
./main  
