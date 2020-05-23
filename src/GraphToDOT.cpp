//
// Created by nrx on 21.05.2020.
//

#include "GraphToDOT.h"
#include <cstdlib>
#include <fstream>

bool saveImageGV(std::string dot_str, std::string file_path){
    std::ofstream file;
    std::string fp = file_path + std::string(".dot");
    file.open(fp);
    if(!file.is_open()) {
        std::cout << "error open file: " << file_path;
        return false;
    }
    file << dot_str;
    file.flush();
    file.close();
    int r = system((std::string("dot -Tsvg -o ") + file_path + std::string(".svg ") + fp).c_str());
    std::cout << r << std::endl;
}