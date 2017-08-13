#include <CCsv.h>
#include <CStrUtil.h>
#include <iostream>

int
main(int argc, char **argv)
{
  std::string filename;
  std::string columns;
  bool        skipFirst = false;
  bool        quote     = false;

  for (auto i = 1; i < argc; ++i) {
    if (argv[i][0] == '-') {
      std::string arg(&argv[i][1]);

      if      (arg == "columns") {
        if (i < argc - 1)
          columns = argv[++i];
      }
      else if (arg == "skip_first")
        skipFirst = true;
      else if (arg == "quote")
        quote = true;
      else
        std::cerr << "Unhandled option: " << arg << std::endl;
    }
    else
      filename = argv[i];
  }

  if (filename == "") {
    std::cerr << "CCsvTest [-columns <inds>] [-skip_first] [-quote] <filename>" << std::endl;
    exit(1);
  }

  CCsv csv(filename);

  csv.setSkipFirst(skipFirst);

  CCsv::Inds inds;

  if (columns != "") {
    std::vector<std::string> words;

    CStrUtil::addFields(columns, words, ",");

    for (const auto &w : words)
      inds.push_back(stoi(w));
  }

  CCsv::FieldsArray fieldsArray;

  csv.getFields(inds, fieldsArray);

  for (const auto &fields : fieldsArray) {
    bool first = true;

    for (const auto &field : fields) {
      if (! first)
        std::cout << "|";

      if (quote)
        std::cout << "\"" << field << "\"";
      else
        std::cout << field;

      first = false;
    }

    std::cout << std::endl;
  }

  exit(0);
}
