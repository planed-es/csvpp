#ifndef  CSV_TYPES_HPP
# define CSV_TYPES_HPP

# include <vector>
# include <string>

namespace Csv
{
  typedef std::vector<std::string> Row;
  typedef std::vector<Row>         Rows;
  typedef std::vector<std::string> Columns;
}

#endif
