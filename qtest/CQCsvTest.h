#ifndef CQCsvTest_H
#define CQCsvTest_H

#include <QFrame>

class CQCsvTable;
class CQCsvModel;

class CQCsvTest : public QFrame {
  Q_OBJECT

 public:
  CQCsvTest();
 ~CQCsvTest();

  bool isCommentHeader() const { return commentHeader_; }
  void setCommentHeader(bool b) { commentHeader_ = b; }

  bool isFirstLineHeader() const { return firstLineHeader_; }
  void setFirstLineHeader(bool b) { firstLineHeader_ = b; }

  bool isFirstColumnHeader() const { return firstColumnHeader_; }
  void setFirstColumnHeader(bool b) { firstColumnHeader_ = b; }

  const QString &filter() const { return filter_; }
  void setFilter(const QString &v) { filter_ = v; }

  void load(const QString &filename);

  QSize sizeHint() const override { return QSize(800, 600); }

 private:
  bool        commentHeader_     { false };
  bool        firstLineHeader_   { false };
  bool        firstColumnHeader_ { false };
  QString     filter_;
  CQCsvTable* table_             { nullptr };
  CQCsvModel* model_             { nullptr };
};

#endif
