#include <CQCsvTable.h>
#include <CQCsvModel.h>

#include <QHeaderView>
#include <QSortFilterProxyModel>

CQCsvTable::
CQCsvTable(QWidget *parent) :
 CQTableView(parent)
{
  setObjectName("table");

  setSortingEnabled(true);

  horizontalHeader()->setSectionsClickable(true);

  proxy_ = new QSortFilterProxyModel;
}

CQCsvTable::
~CQCsvTable()
{
  delete proxy_;
}

void
CQCsvTable::
setModel(CQCsvModel *model)
{
  proxy_->setSourceModel(model);

  CQTableView::setModel(proxy_);
}
