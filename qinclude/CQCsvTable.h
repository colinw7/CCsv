#ifndef CQCsvTable_H
#define CQCsvTable_H

#include <QTableView>

class CQCsvModel;
class CQHeaderView;

class CQCsvTable : public QTableView {
  Q_OBJECT

 public:
  CQCsvTable(QWidget *parent=nullptr);

  void setModel(CQCsvModel *model);

 private:
  CQCsvModel*   model_  { nullptr };
  CQHeaderView* header_ { nullptr };
};

#endif
