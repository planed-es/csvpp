#ifndef  CSV_DOCUMENT_HPP
# define CSV_DOCUMENT_HPP

# include "types.hpp"
# include <stdexcept>

namespace Csv
{
  struct ColumnNotFound : public std::invalid_argument
  {
    ColumnNotFound(const std::string& name) : std::invalid_argument("column not found: " + name)
    {}
  };

  class Document
  {
  public:
    class DocumentRow
    {
    public:
      DocumentRow(const Document& document, std::size_t position) : document(document), position(position)
      {}

      std::size_t row_it() const          { return position; }
      std::string get(unsigned int column) const       { return document.get(position, column); }
      std::string get(const std::string& column) const { return document.get(position, column); }

    private:
      const Document& document;
      std::size_t     position;
    };

    struct iterator : public std::iterator_traits<std::size_t>
    {
    public:
      iterator(Document& document, std::size_t i) : document(document), i(i) {}
      bool operator==(iterator a) const { return i == a.i; }
      bool operator!=(iterator a) const { return i != a.i; }
      DocumentRow operator*()     const { return DocumentRow(document, i); }
      void        operator++() { ++i; }
      void        operator--() { --i; }

    private:
      Document&   document;
      std::size_t i;
    };

    struct const_iterator : public std::iterator_traits<std::size_t>
    {
    public:
      const_iterator(const Document& document, std::size_t i) : document(document), i(i) {}
      bool operator==(const_iterator a) const { return i == a.i; }
      bool operator!=(const_iterator a) const { return i != a.i; }
      DocumentRow operator*()     const { return DocumentRow(document, i); }
      void        operator++() { ++i; }
      void        operator--() { --i; }

    private:
      const Document& document;
      std::size_t     i;
    };

    iterator begin() { return iterator(*this, 0);           }
    iterator end()   { return iterator(*this, row_count()); }

    const_iterator const_begin() const { return const_iterator(*this, 0);           }
    const_iterator const_end()   const { return const_iterator(*this, row_count()); }

    Document() : separator(';') {}

    void set_separator(char separator) { this->separator = separator; }
    bool load_from_string(std::string src);
    bool load_from_file(const std::string& path);

    unsigned int       row_count() const { return rows.size(); }
    const Row&         get(unsigned int row) const;
    const std::string& get(unsigned int row, unsigned int column) const;
    const std::string& get(unsigned int row, const std::string& column) const;

    bool           has_column(const std::string&) const;
    const Columns& get_columns() const { return columns; }

  protected:
    int       get_column_from_name(const std::string& name) const;

  private:

    Columns columns;
    Rows    rows;
    char    separator;
  };
}

#endif
