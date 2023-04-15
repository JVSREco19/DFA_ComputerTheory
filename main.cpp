#include <iostream>
#include <unordered_map>
#include <fstream>
#include <string>


using namespace std;


struct estado
{
    bool estadoInicial, estadoFinal;

    estado()
    {
        estadoInicial = false;
        estadoFinal = false;
    }

};


int main()
{
    for(int z = 1; z <6;z++){
    unordered_map <string, estado*> states; // <nomeEstado,estado>
    unordered_map <int, string> statesNames; // <int,nomeEstado>
    unordered_map <int, string> alphabetNames; // <int,SimboloDoAlfabeto>
    unordered_map <string, unordered_map<string, string>> D; // <Estado,<entrada,proxEstado>>
    string stateName,line,spc=" ";
    int numEstados = 0,numAlphabet = 0;
    string auxName = "teste" +to_string(z);
    string filename = "teste";
    filename = auxName+".txt";
    ifstream file(filename);// abre o arquivo
    if(!file.is_open()) // Verifica se o Arquivo está aberto
    {
        cout<<"Erro ao abrir arquivo!"<<endl;
    }
    getline(file,line);//Pega uma linha
    for(int i=0; i<line.length(); i++) // Pega os estados da linha e guarda em uma variavel e cria os estados da struct
    {
        if(line[i]!=spc[0])
        {
            stateName=line[i];
            states[stateName] = new estado;
            statesNames[numEstados] = stateName;
            numEstados++;
        }

    }
    getline(file,line);
    for(int i=0; i<line.length(); i++)// Pega o alfabeto e guarda em um map
    {
        if(line[i]!=spc[0])
        {

            alphabetNames[numAlphabet]=line[i];
            numAlphabet++;
        }

    }
    for(int i =0; i<numEstados; i++) // preenche a matriz de transições
    {
        getline(file,line);
        int k = 0;
        for(int j=0; j<line.length(); j++)
        {
            if(line[j]!=spc[0])
            {

                D[statesNames[i]][alphabetNames[k]]=line[j];
                k++;
            }

        }
    }
    getline(file,line);
    states[line]->estadoInicial = true; // seta o estado inicial
    string initialState = line;
    getline(file,line);
    for(int j=0; j<line.length(); j++) // Pega os estados finais
    {
        if(line[j]!=spc[0])
        {
            string aux = " ";
            aux[0] = line[j];
            states[aux]->estadoFinal = true;
        }

    }
cout<<"Matriz de transicoes:"<<endl<<endl;// Apresenta a matriz de transições para o usuário
cout<<"  ";
for(int i = 0;i<numEstados;i++){
    cout<<statesNames[i]<<" ";
}
cout<<endl;
 for(int j=0; j<numAlphabet ;j++){
       for(int k =0;k<numEstados;k++){

            if(k ==0){
                cout<<alphabetNames[j]<<" ";
            }
                cout<<D[statesNames[k]][alphabetNames[j]]<<" ";


        }
        cout<<endl;
    }
cout<<endl;
// Termina a apresentação da matriz

    int numPalavras;
    file >> numPalavras; //Recebe o numero de palavras a serem testadas
    getline(file,line);
    for(int j=0; j<numPalavras; j++)// Testa as palavras fazendo uma verificação se a entrada existe na matriz de transições
                                    // e se termina em um estado final
    {
        string e,prox;
        e = initialState;
        getline(file,line);
        for(int i = 0; i<line.length(); i++)
        {
            string aux = " ";
            aux[0]=line[i];

            prox = D[e][aux];
            if(prox[0])// Verifica se a entrada existe na matriz
            {
                cout<<"D["<<e<<","<<aux<<"]"<<"->"<<prox<<";";
                e = prox;
                prox[0]=0;
            }
            else
            {
                cout<<endl<<"Entrada Invalida, palavra nao aceita!";
                i = line.length();
            }
            if(i == line.length() -1)//Verifica se terminou a palavra e se ela está no estado final
            {
                if(states[e]->estadoFinal == true && e!="e")
                {
                    cout<<endl<<"Palavra aceita! "<<e<<" e um estado final!";
                }
                else if(e == "e"){
                    cout<<endl<<"Palavra nao aceita! " <<"Caimos no estado de erro!";
                }
                else

                {
                    cout<<endl<<"Palavra nao aceita! " <<e<<" nao e um estado final!";
                }
            }


        }
        cout<<endl;


    }


    file.close();
    cout<<endl<<endl;
    }
    return 0;
}
