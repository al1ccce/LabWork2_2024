#include "header.h"

int main(int argc, char* argv[]){
    if (argc != 5){
        cout << "Неверная команда!";
        return 0;
    }
    cout << "-> ";
    string arg = argv[1];
    if (arg != "--file"){
        cout << "Отсутствует ключ --file!";
        return 0;
    }
    string file = argv[2];
    arg = argv[3];
    if (arg != "--query"){
        cout << "Отсутствует ключ --query!";
        return 0;
    }
    string command = argv[4];
    stringstream iss(command);
    string word;
    while (iss >> word){
        if (word == "SETADD"){
            iss >> word;
            string namestruct = '@' + word;
            addStructName(file, word);

            set Set(11);
            hashFromFile(file, Set);

            iss >> word;
            Set.insert(word);
            Set.print(file, namestruct);
            return 0;
        }
        if (word == "SETDEL"){
            iss >> word;
            string namestruct = '@' + word;
            addStructName(file, word);

            set Set(11);
            hashFromFile(file, Set);

            iss >> word;
            
            if (Set.remove(word)){
                Set.print(file, namestruct);
            }
            
            return 0;
        }
        if (word == "SETFIND"){
            iss >> word;
            string namestruct = '@' + word;
            addStructName(file, word);

            set Set(11);
            hashFromFile(file, Set);

            iss >> word;
            cout << boolalpha << Set.find(word) << endl;
            return 0;
        }
        if (word == "SETPRINT"){
            iss >> word;
            string namestruct = '@' + word;
            addStructName(file, word);

            set Set(11);
            hashFromFile(file, Set);

            Set.printbash();
            return 0;
        }
        if (word == "SETUNI"){ // Объединение
            string secretword = "UNION";
            iss >> word;
            string namestruct = '@' + word;
            addStructName(file, word);

            set Set(11);
            hashFromFile(file, Set);

            string file2;
            cout << "--file2 ";
            cin >> file2;

            set Set2(11);
            hashFromFile(file2, Set2);

            string resname = getResName(namestruct, file2, secretword);
            string resfile = resname + ".data";

            set Union = Set.unification(Set2);
            Union.print(resfile, resname);
            return 0;
        }
        if (word == "SETDIFF"){ // Пересечение
            string secretword = "DIFF";
            iss >> word;
            string namestruct = '@' + word;
            addStructName(file, word);

            set Set(11);
            hashFromFile(file, Set);

            string file2;
            cout << "--file2 ";
            cin >> file2;

            set Set2(11);
            hashFromFile(file2, Set2);

            string resname = getResName(namestruct, file2, secretword);
            string resfile = resname + ".data";

            set Diff = Set.difference(Set2);
            Diff.print(resfile, resname);
            return 0;
        }
    }
}