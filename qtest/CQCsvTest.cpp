#include <CQCsvTest.h>
#include <CQCsvTable.h>
#include <CQCsvModel.h>

#include <QApplication>
#include <QToolButton>
#include <QVBoxLayout>
#include <iostream>

int
main(int argc, char **argv)
{
  QApplication app(argc, argv);

  std::vector<QString> filenames;

  bool header = false;

  for (int i = 1; i < argc; ++i) {
    if (argv[i][0] == '-') {
      std::string arg = &argv[i][1];

      if (arg == "header")
        header = true;
      else
        std::cerr << "Invalid option '" << arg << "'" << std::endl;
    }
    else
      filenames.push_back(argv[i]);
  }

  if (filenames.empty())
    exit(1);

  //---

  CQCsvTest test;

  test.setHeader(header);

  test.load(filenames[0]);

  test.show();

  app.exec();

  return 0;
}

//-----

CQCsvTest::
CQCsvTest()
{
  QVBoxLayout *layout = new QVBoxLayout(this);

  table_ = new CQCsvTable;

  layout->addWidget(table_);
}

void
CQCsvTest::
load(const QString &filename)
{
  model_ = new CQCsvModel;

  if (isHeader())
    model_->setColumnHeaders(true);

  model_->load(filename);

  table_->setModel(model_);
}
