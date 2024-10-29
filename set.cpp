#include "header.h"

bool isEmpty(string file){
    ifstream in;
    in.open(file);
    string data;
    getline(in, data);
    in.close();
    if (data.size() == 0){
        return true;
    }
    return false;
}

void addStructName(string file, string namestruct){
    ofstream out;
    if (isEmpty(file)){
        out.open(file);
        out << namestruct << endl;
        out.close();
    }    
}

void hashFromFile(string file,  set &table){
    fstream in;
    in.open(file);
    string data;
    getline(in, data); // Пропускаем строчку с именем
    getline(in, data);
    stringstream iss(data);
    while (iss >> data){
        table.insert(data);
    } 
    in.close(); 
}

string getResName(string namestruct, string file2, string secretword){
    string resname = namestruct + '_';
    ifstream in;
    string line;
    in.open(file2);
    getline(in, line);
    resname += line + '_' + secretword;
    return resname;
}
