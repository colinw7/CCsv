#include <CCsv.h>
#include <CStrUtil.h>
#include <iostream>

int
main(int argc, char **argv)
{
  std::string filename;
  std::string columns;
  bool        commentHeader   = false;
  bool        firstLineHeader = false;
  bool        quote           = false;

  for (auto i = 1; i < argc; ++i) {
    if (argv[i][0] == '-') {
      std::string arg(&argv[i][1]);

      if      (arg == "columns") {
        if (i < argc - 1)
          columns = argv[++i];
      }
      else if (arg == "comment_header")
        commentHeader = true;
      else if (arg == "first_line_header")
        firstLineHeader = true;
      else if (arg == "quote")
        quote = true;
      else
        std::cerr << "Unhandled option: " << arg << std::endl;
    }
    else
      filename = argv[i];
  }

  if (filename == "") {
    std::cerr << "CCsvTest [-columns <inds>] [-comment_header|-first_line_header] [-quote] "
                 "<filename>" << std::endl;
    exit(1);
  }

  CCsv csv(filename);

  csv.setCommentHeader  (commentHeader);
  csv.setFirstLineHeader(firstLineHeader);

  CCsv::Inds inds;

  if (columns != "") {
    std::vector<std::string> words;

    CStrUtil::addFields(columns, words, ",");

    for (const auto &w : words)
      inds.push_back(stoi(w));
  }

  CCsv::Data fieldsArray;

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
