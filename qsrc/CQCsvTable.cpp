#include <CQCsvTable.h>
#include <CQCsvModel.h>

CQCsvTable::
CQCsvTable(QWidget *parent) :
 QTableView(parent)
{
  setObjectName("table");
}

void
CQCsvTable::
setModel(CQCsvModel *model)
{
  QTableView::setModel(model);
}
