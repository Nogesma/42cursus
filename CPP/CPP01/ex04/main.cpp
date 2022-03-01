#include <iostream>
#include <fstream>

std::string* replace_str(std::string *buffer, std::string s1, std::string s2)
{
	size_t i;

	i = buffer->find(s1);
	while (i != std::string::npos)
	{
		buffer->erase(i, s1.length());
		buffer->insert(i, s2);
		i = buffer->find(s1);
	}
	return (buffer);
}

int		main( int ac, char **av )
{
	if (ac != 4) return (1);

	std::string filename = av[1];
	std::string s1 = av[2];
	std::string s2 = av[3];

	std::string buffer;
	std::string line;

	std::ifstream file (filename);
	std::ofstream replace (filename + ".replace");

	if ( file.is_open() )
	{
		buffer = "";
		while ( true )
		{
			std::getline(file, line);
			buffer += line;
			if( file.eof() ) break;
			buffer += '\n';
		}
		replace_str(&buffer, s1, s2);
		replace << buffer;
		file.close();
		replace.close();
	}
}
