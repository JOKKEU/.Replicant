#ifndef __FIND_H__
#define __FIND_H__

#include <vector>
#include <algorithm>
#include <iostream>
#include <filesystem>
#include <fstream>

#include "class_file.h"
#include "console_loading.h"


int jokkeu_find(file&, std::pair<int, std::string>&);
int jokkeu_find_and_path_to_file_first_result(file&, std::pair<int, std::string>&);
int jokkeu_all_finds_and_path(file&, std::pair<int, std::string>&);
int included_in_filename(file&, std::pair<int, std::string>&);
#endif