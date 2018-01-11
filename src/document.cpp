#include "csv/document.hpp"
#include <sstream>
#include <fstream>
#include <boost/algorithm/string.hpp>
#include <boost/filesystem.hpp>
#include <boost/tokenizer.hpp>

using namespace Csv;
using namespace std;

static vector<string> csv_split(const string& str, char c)
{
  vector<string> ret;
  bool           in_quotes = false;
  short          i;
  string         word;

  for (i = 0 ; str[i] ; ++i)
  {
    if (word.length() == 0 && str[i] == '"' && !in_quotes)
      in_quotes = true;
    else
    {
      if (in_quotes == false && str[i] == c)
      {
        ret.push_back(word);
        word      = "";
      }
      else if (in_quotes == true && str[i] == '"')
      {
        if (str[i + 1] == '"')
        {
          word += '"';
          ++i;
        }
        else
          in_quotes = false;
      }
      else
        word += str[i];
    }
  }
  ret.push_back(word);
  return (ret);
}

bool Document::load_from_string(std::string src)
{
  boost::erase_all(src, "\r");
  {
    boost::char_separator<char> sep("\n");
    boost::tokenizer<boost::char_separator<char> > lines(src, sep);

    for (const string& line : lines)
    {
      auto row = csv_split(line, separator);

      if (columns.size() == 0)
        columns = row;
      else
        rows.push_back(row);
    }
  }
  return true;
}

bool Document::load_from_file(const std::string& path)
{
  if (boost::filesystem::exists(path.c_str()))
  {
    ifstream     input(path.c_str());
    stringstream stream;

    while (input >> stream.rdbuf());
    return load_from_string(stream.str());
  }
  else
    throw std::runtime_error(("File does not exist: " + path).c_str());
}

int Document::get_column_from_name(const std::string& name) const
{
  size_t column_it = 0;

  while (column_it < columns.size())
  {
    if (columns[column_it] == name)
      break ;
    column_it++;
  }
  if (column_it == columns.size())
    return -1;
  return column_it;
}

bool Document::has_column(const std::string& column_name) const
{
  return get_column_from_name(column_name) != -1;
}

const Row& Document::get(unsigned int row) const
{
  return rows[row];
}

const string& Document::get(unsigned int row, unsigned int column) const
{
  return rows[row][column];
}

const string& Document::get(unsigned int row, const string& column) const
{
  int column_it = get_column_from_name(column);

  if (column_it == -1)
    throw ColumnNotFound(column);
  return get(row, column_it);
}
