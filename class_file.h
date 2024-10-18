#ifndef __CLASS_FILE_H__
#define __CLASS_FILE_H__

#include <string>

class file
{
public:

	explicit file(std::string file_name, std::string path_to_file) noexcept;
	~file() noexcept = default;
	file(file const&);
	file& operator=(file const&) = delete;
	bool operator == (std::string const& other) const;
	std::string get_name() const;
	std::string get_path() const;

private:
	std::string name_file;
	std::string path_to_file;
};

#endif
