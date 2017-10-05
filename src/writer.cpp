#include "csv/writer.hpp"
#include <ostream>

using namespace Csv;
using namespace std;

Writer::Writer(std::ostream& out, char separator) : out(out), separator(separator)
{
}

void Writer::insert(const Row& row)
{
  for (auto it = row.begin() ; it != row.end() ; ++it)
  {
    if (it != row.begin())
      out << separator;
    out << '"';
    for (auto char_it = it->begin() ; char_it != it->end() ; ++char_it)
    {
      switch (*char_it)
      {
	case '"':  out << "\"\""; break ;
	case '\n': out << " "; break ;
        default:   out << *char_it; break ;
      }
    }
    out << '"';
  }
  out << endl;
}

