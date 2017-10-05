# csvpp
C++/Boost-based library for reading and writing CSV files

## Examples
### Reading a CSV file
```c++
#include <csv/document.hpp>
#include <iostream>

int main()
{
  Csv::Document my_document;
  
  my_document.load_from_file("input.csv");
  for (const auto& row : my_document)
  {
    std::cout << "Row content: "
              << row.get("id") << ": "
              << row.get("value") << std::endl;
  }
  return 0;
}
```

### Writing a CSV file
```c++
#include <csv/writer.hpp>
#include <ofstream>

int main()
{
  std::ofstream file;
  file.open("output.csv");

  Csv::Writer writer(file, ';');
  Csv::Row header, row;
  
  header.push_back("id");
  header.push_back("value");
  writer.insert(header);
  row.push_back("1");
  row.push_back("that's the value column content");
  writer.insert(row);
  file.close();
  return 0;
}
```
