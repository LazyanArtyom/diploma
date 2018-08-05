#ifndef COLSELECTORWIDGET_H
#define COLSELECTORWIDGET_H

#include <QListView>
#include "ColSelectorModel.h"

class ColSelectorWidget : public QListView
{
	Q_OBJECT
public:
	ColSelectorWidget(QWidget *parent = 0);
	~ColSelectorWidget();

private:
	ColSelectorModel *m_pColSelectorModel;
};

#endif
