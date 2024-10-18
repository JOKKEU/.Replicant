#include "class_file.h"

file::file(const std::string namefile, std::string path_to_file) noexcept
: path_to_file(path_to_file)
{
	for (auto c : namefile)
	{
		c = tolower(c);
	}
	name_file = namefile;
}

file::file(const file& other) : name_file(other.name_file), path_to_file(other.path_to_file)
{}

bool file::operator == (std::string const& str) const
{
	return name_file == str;
}

std::string file::get_name() const
{
	return name_file;
}
std::string file::get_path() const
{
	return path_to_file;
}