#include <stdint.h>
#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <ios>
#include <cstdio>
#include <unordered_set>
#include <unordered_map>

#include <regex>

std::istream* input;

std::unordered_set<std::string> vt_coords;
std::unordered_map<int, int> vt_coord_index_mapping;
int vt_coord_in_index = 1;
int vt_coord_out_index = 1;
int v_coord_in_index = 1;
int v_coord_out_index = 1;

bool handleVCoord(const std::string& line)
{
    std::regex point_matrix_regex("v [^ ]+ [^ ]+ [^ ]+");
    std::cmatch sub_matches;    // same as std::match_results<const char*> cm;
    std::regex_match(line.c_str(), sub_matches, point_matrix_regex);
    
    if (sub_matches.size() == 1)
    {
        // skip the first because the first submatch is the whole string
//         vt_coord_index_mapping.emplace(vt_coord_in_index, vt_coord_out_index);
//         if (vt_coords.emplace(line).second)
        { // only output vt coord if it's a new one
            v_coord_out_index++;
            std::cout << line << "\n";
        }
    }
    else
    {
        return false;
    }
    v_coord_in_index++;
    return true;
}

bool handleVtCoord(const std::string& line)
{
    std::regex point_matrix_regex("vt [^ ]+ [^ ]+");
    std::cmatch sub_matches;    // same as std::match_results<const char*> cm;
    std::regex_match(line.c_str(), sub_matches, point_matrix_regex);
    
    if (sub_matches.size() == 1)
    {
        // skip the first because the first submatch is the whole string
        vt_coord_index_mapping.emplace(vt_coord_in_index, vt_coord_out_index);
        if (vt_coords.emplace(line).second)
        { // only output vt coord if it's a new one
            vt_coord_out_index++;
            std::cout << line << "\n";
        }
    }
    else
    {
        return false;
    }
    vt_coord_in_index++;
    return true;
}

bool handleFace(const std::string& line)
{
//     char regex_buffer[64];
//     std::string int_regex = "([0-9]*)";
//     const char* ir = int_regex.c_str();
//     std::sprintf(regex_buffer, "f %s\\\\%s\\\\%s %s\\\\%s\\\\%s %s\\\\%s\\\\%s", ir, ir, ir, ir, ir, ir, ir, ir, ir); 
//     std::regex point_matrix_regex(regex_buffer);
    std::regex point_matrix_regex("f ([0-9]*)/([0-9]*)/([0-9]*) ([0-9]*)/([0-9]*)/([0-9]*) ([0-9]*)/([0-9]*)/([0-9]*)");
    std::cmatch sub_matches;    // same as std::match_results<const char*> cm;
    std::regex_match(line.c_str(), sub_matches, point_matrix_regex);
    
    
    if (sub_matches.size() == 10) // one match for the whole string
    {
        const long int vt1 = vt_coord_index_mapping[std::strtol(sub_matches[2].str().c_str(), nullptr, 0)];
        const long int vt2 = vt_coord_index_mapping[std::strtol(sub_matches[5].str().c_str(), nullptr, 0)];
        const long int vt3 = vt_coord_index_mapping[std::strtol(sub_matches[8].str().c_str(), nullptr, 0)];
        if (vt1 <= 0 || vt2 <= 0 || vt3 <= 0)
        {
            std::cout << "error! outputting bad vt coords!\n";
            std::exit(0);
        }
        bool same_vt = vt1 == vt2 && vt2 == vt3;
        std::cout << "f " << sub_matches[1] << "/";
        if (!same_vt) std::cout << vt1;
        std::cout << "/" << sub_matches[3] << " " << sub_matches[4] << "/";
        if (!same_vt) std::cout << vt2;
        std::cout << "/" << sub_matches[6] << " " << sub_matches[7] << "/";
        if (!same_vt) std::cout << vt3;
        std::cout << "/" << sub_matches[9];
        std::cout << "\n";
        if (vt1 > 10 || vt2 > 10 || vt3 > 10)
        {
            std::cerr << "error!!\n";
            std::exit(1);
        }
    }
    else
    {
        return false;
    }
    return true;
}

int main(int argc, char **argv)
{
    input = &std::cin;
    
    
    std::string line;
    while (!input->eof())
    {
        std::getline(*input, line);

        if (!handleVtCoord(line)
            && !handleFace(line)
            && !handleVCoord(line)
        )
        {
            std::cout << line << "\n";
        }
    }
    return 0;
}













