#include <CQCsvTable.h>
#include <CQCsvModel.h>
#include <CQHeaderView.h>

CQCsvTable::
CQCsvTable(QWidget *parent) :
 QTableView(parent)
{
  setObjectName("table");

  setAlternatingRowColors(true);

  header_ = new CQHeaderView(this);

  setHorizontalHeader(header_);
}

void
CQCsvTable::
setModel(CQCsvModel *model)
{
  QTableView::setModel(model);
}
