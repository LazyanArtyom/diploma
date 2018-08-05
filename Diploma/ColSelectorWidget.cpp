#include "ColSelectorWidget.h"

ColSelectorWidget::ColSelectorWidget(QWidget *parent)
	: QListView(parent)
{
	m_pColSelectorModel = new ColSelectorModel();
	setModel(m_pColSelectorModel);

	// prevent edit
	setEditTriggers(QAbstractItemView::NoEditTriggers);
}

ColSelectorWidget::~ColSelectorWidget()
{
}
