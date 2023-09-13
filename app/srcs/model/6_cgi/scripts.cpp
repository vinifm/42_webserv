#include <Request.hpp>

std::string	show_aws_directory_in_delete_table(std::string response)
{
	std::string		new_response="";
	std::size_t		start = response.find("[__MILIONARIO__]");

	new_response = response.substr(0, start);

	DIR				*directory = opendir("./srcs/view/www/aws");
	std::string		rows="";
	struct dirent	*file;

	int index = 1;
	while ((file = readdir(directory)) != NULL)
	{
		if (std::string(file->d_name) == "." || std::string(file->d_name) == "..")
			continue ;
		std::stringstream buffer;
		std::string url = "/";
		url.append(std::string(file->d_name));
		buffer << "<tr>"
			   << "<td>"<< index << "</td>"
			   << "<td>"<< file->d_name <<"</td>"
			   << "<td class=\"text-center\">"
			   << "<a href=\"/aws/" << file->d_name << "\" class=\"btn btn-primary mx-1\">Abrir</a>"
			   << "<input type=\"submit\" onclick=\"changeFileToDelete("<< index <<");\"<<" << file->d_name << " class=\"btn btn-danger mx-1\" value=\"Deletar\" \\>"
			   << "</td></tr>";
		rows.append(buffer.str());
		index++;
	}
	closedir(directory);
	new_response.append(rows);
	new_response.append(response.substr(std::size_t (start + 16), response.length()));
	return (new_response);
}

void	execute_scripts(Request &request, Response &response)
{
	if (del_final_bar(request.getRoute()) == "/delete")
	{
		response.setBody(show_aws_directory_in_delete_table(response.getBody()));
	}
}
