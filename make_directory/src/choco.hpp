#pragma once

#include <exception>
#include <iostream>
#include <queue>
#include <cstdint>
#include <optional>
#include <filesystem>
#include <print>
#include <cstdlib>

#define CHOCO_TRUE true
#define CHOCO_FALSE false

namespace Filesystem{

    const bool is_running = true;

    enum DirectoryFlags : std::uint32_t

    {
	NO_FLAG = (1 << 0),
	VERBOSE_FLAG = (1 << 1),
	QUIET_FLAG = (1 << 2)

    };

    struct ParsedArgs{

	std::vector<std::string> arguements;
	std::optional<std::uint32_t> flags;

    };

    std::uint32_t dispatchFlag(std::string buffers){

	std::uint32_t flags;

	for (int i = 1; i < static_cast<int> (buffers.size()); i++){

	    switch(buffers.at(i)){

		case 'v':

		    flags |= VERBOSE_FLAG;
		    break;

		case 'q':

		    flags |= QUIET_FLAG;
		    break;

		default:
		    break;

	    }

	}

	return flags;

    }

    std::vector<ParsedArgs> dispatchParsedArgs(std::vector<std::string> unParsedArgs){

	ParsedArgs args = {};
	std::vector<ParsedArgs> parsedArguements;
	const char flag_initialization = '-';

	for (std::string currentArgs : unParsedArgs){

	    if (currentArgs.front() == flag_initialization){

		args.flags = dispatchFlag(currentArgs);

		if (!args.arguements.empty()){

		    parsedArguements.push_back(args);
		    args.arguements.clear();

		}

		args.flags.reset();
		continue;

	    }

	    args.arguements.push_back(currentArgs);

	}

	if (!args.arguements.empty()){

	    args.flags = NO_FLAG;
	    parsedArguements.push_back(args);

	}

	return parsedArguements;

    }

    std::filesystem::path getPath(){

	return std::filesystem::current_path();
    }

    bool fileExist(std::filesystem::path path){

	return std::filesystem::exists(path);

    }

    std::vector<std::basic_string<char>> rmPattern(std::basic_string<char> sPath, const char linux_separator){

	std::vector<std::basic_string<char>> parent_path;
	std::basic_string<char> temp_container;

	for (char &current_char : sPath){

	    if (current_char == linux_separator){

		if (!temp_container.empty()){

		    parent_path.push_back(temp_container);
		    temp_container.clear();
		    continue;
		}

		continue;

	    }

	    temp_container.push_back(current_char);

	}

	if (!temp_container.empty()) parent_path.push_back(temp_container);

	if (parent_path.empty()){

	    throw std::runtime_error("somethings wrong here");

	}

	return parent_path;

    }

    void tree(std::filesystem::path path){

	std::basic_string<char> sPath = path.string();

	if (!path.has_parent_path()){

	    std::filesystem::path current_path = getPath();
	    current_path /= path;
	    sPath = current_path.string();
	}

	const char linux_separator = '/';

	std::vector<std::basic_string<char>> parent_path = rmPattern(sPath, linux_separator);

	int initial_space = 3;
	std::string symbol;

	for (auto &current_dir : parent_path){

	    std::cout << symbol << current_dir << std::endl;
	    symbol.clear();

	    for (int i = 1; i < initial_space; i++){

		symbol.push_back(' ');

	    }

	    symbol += "\u2514\u2574";

	    initial_space += 3;

	}

    }

    void ftree(std::filesystem::path path){

	//temporary solution
	
	std::basic_string<char> str_tree;

	std::filesystem::path current_path = getPath();
	current_path /= path;
	auto pathIterBegin = current_path.begin();
	auto pathIterEnd = current_path.end();

	if (path.has_parent_path()){

	    std::filesystem::path pPath = path.parent_path();
	    auto pathIterBegin = path.begin();
	    auto pathIterEnd = path.end();

	}

	int max = 2;

	auto i = pathIterBegin;

	i++;
	i++;
	i++;

	for (; i != pathIterEnd; i++){
	    std::cout << str_tree << *i << std::endl;
	    str_tree.clear();

	    for (int j = 1; j < max; j++){

		str_tree.push_back(' ');

	    }

	    str_tree+= "\u2514\u2574";

	    max+=3;

	}

    }

}
