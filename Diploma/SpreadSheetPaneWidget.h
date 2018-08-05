#ifndef SPREADSHEETPANEWIDGET
#define SPREADSHEETPANEWIDGET

#include <QTableView>
#include "SpreadSheetModel.h"

class SpreadSheetPaneWidget : public QTableView
{
	Q_OBJECT
public:
	SpreadSheetPaneWidget(QWidget *parent = 0);
	~SpreadSheetPaneWidget();

private:
	SpreadSheetModel *m_pModel;
};

#endif
