#ifndef CQCsvTest_H
#define CQCsvTest_H

#include <QFrame>

class CQCsvTable;
class CQCsvModel;

class CQCsvTest : public QFrame {
  Q_OBJECT

 public:
  CQCsvTest();

  bool isHeader() const { return header_; }
  void setHeader(bool b) { header_ = b; }

  void load(const QString &filename);

 private:
  bool        header_ { false };
  CQCsvTable *table_  { nullptr };
  CQCsvModel *model_  { nullptr };
};

#endif
