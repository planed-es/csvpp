#ifndef  CSV_WRITER_HPP
# define CSV_WRITER_HPP

# include "types.hpp"

namespace Csv
{
  class Writer
  {
  public:
    Writer(std::ostream&, char separator = ';');
    void insert(const Row& row);

  private:
    std::ostream& out;
    const char    separator;
  };
}

#endif
