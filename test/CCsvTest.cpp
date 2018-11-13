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
  bool        allowComments   = true;
  char        separator       = ',';
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
      else if (arg == "allow_comments")
        allowComments = true;
      else if (arg == "no_allow_comments")
        allowComments = false;
      else if (arg == "separator") {
        if (i < argc - 1)
          separator = argv[++i][0];
      }
      else if (arg == "quote")
        quote = true;
      else
        std::cerr << "Unhandled option: " << arg << std::endl;
    }
    else
      filename = argv[i];
  }

  if (filename == "") {
    std::cerr << "CCsvTest [-columns <inds>] [-comment_header|-first_line_header] "
                 "[-allow_comments|-no_allow_comments] [-separator <char>] [-quote] "
                 "<filename>" << std::endl;
    exit(1);
  }

  //---

  CCsv csv(filename);

  csv.setCommentHeader  (commentHeader);
  csv.setFirstLineHeader(firstLineHeader);
  csv.setAllowComments  (allowComments);
  csv.setSeparator      (separator);

  CCsv::Inds inds;

  if (columns != "") {
    std::vector<std::string> words;

    CStrUtil::addFields(columns, words, ",");

    for (const auto &w : words)
      inds.push_back(stoi(w));
  }

  //---

  if (! csv.load()) {
    std::cerr << "Failed to load '" << filename << "'\n";
    exit(1);
  }

  //---

  const CCsv::Fields &header = csv.header();

  if (! header.empty()) {
    bool first = true;

    std::string headerStr;

    for (const auto &field : header) {
      if (! first)
        headerStr += "|";

      if (quote)
        headerStr += "\"" + field + "\"";
      else
        headerStr += field;

      first = false;
    }

    std::cout << headerStr << "\n";

    int headerLen = headerStr.size();

    for (int i = 0; i < headerLen; ++i)
      std::cout << "-";

    std::cout << "\n";
  }

  //---

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

    std::cout << "\n";
  }

  //---

  if (csv.hasMeta()) {
    std::cout << "-- META --\n";

    for (const auto &fields : csv.meta()) {
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

      std::cout << "\n";
    }
  }

  //---

  exit(0);
}
