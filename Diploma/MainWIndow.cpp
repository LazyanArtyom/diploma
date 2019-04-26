#include <QIcon>
#include <QToolBar>
#include <QSplitter>
#include <QScrollArea>
#include <QElapsedTimer>

// Local includes
#include "MainWIndow.h"
#include "ChartReviewPane.h"

////////////////////////////////////////////////////////////////////////////////
//
//	CMainWindow
//
CMainWindow::CMainWindow(QWidget *parent) : QMainWindow(parent)
{
	setupUi();
}

CMainWindow::~CMainWindow()
{
	delete m_pChartContorller;
}

void CMainWindow::setBinCount(int nBinCount)
{
	m_nBinCount = nBinCount;
}

int CMainWindow::getBinCount() const
{
	return m_nBinCount;
}

void CMainWindow::setupUi()
{
	QSplitter* pMain = new QSplitter(this);
	setCentralWidget(pMain);

	m_pChartContorller = new CChartController(this);

	// Set View
	CChartViewPane* pChartView = new CChartViewPane(this);
	m_pChartContorller->setView(pChartView);

	// Add Histogram model
	IChartModel* pHistoModel = new CHistogramModel();
	m_pChartContorller->addModel(EChartType::Histogram, pHistoModel);
	
	// Review Pane
	ChartReviewPane* pChartReviewPane = new ChartReviewPane(this);
	QObject::connect(pChartView, &CChartViewPane::sigChartChecked,
		pChartReviewPane, &ChartReviewPane::onChartChecked);

	QScrollArea* pScrollArea = new QScrollArea();
	pScrollArea->setWidgetResizable(true);
	pScrollArea->setWidget(pChartView);
	pScrollArea->setMinimumWidth(900);

	pMain->addWidget(pScrollArea);
	pMain->addWidget(pChartReviewPane);

	pMain->setStretchFactor(0, 1);
	pMain->setStretchFactor(1, 8);
	pMain->setStretchFactor(2, 2);

	QObject::connect(this, SIGNAL(sigStopTimer()), this, SLOT(onStopTimer()));

	setMinimumSize(1024, 768);
	setWindowIcon(QIcon(":/Resources/icons/histogram.png"));
	setWindowTitle("Histogram");
	showMaximized();

	m_pToolBar = new QToolBar(tr("Toolbar"));
	m_pToolBar->setFixedHeight(100);
	m_pToolBar->setIconSize(QSize(50, 50));
	addToolBar(m_pToolBar);

	const QIcon iconOpen = QIcon(":/Resources/icons/open.png");
	m_pOpenAct = new QAction(iconOpen, tr("Open"), this);
	m_pToolBar->addAction(m_pOpenAct);

	m_pToolBar->addSeparator();

	const QIcon iconRun = QIcon(":/Resources/icons/run.png");
	m_pRunAct = new QAction(iconRun, tr("Run"), this);
	QObject::connect(m_pRunAct, SIGNAL(triggered()), this, SLOT(onRun()));

	m_pToolBar->addAction(m_pRunAct);

	m_pToolBar->addSeparator();

	m_pTimer = new CTimer(this);
	m_pTimer->setMinimumWidth(90);
	m_pTimer->setStyleSheet("border:2px solid gray; font-size:20px;");
	m_pToolBar->addWidget(m_pTimer);

	m_pToolBar->addSeparator();

	QLabel* plblBinCount = new QLabel(" Bin count: ", this);
	plblBinCount->setStyleSheet("font-size:20px;");
	m_pToolBar->addWidget(plblBinCount);

	m_pcboBinCount = new QComboBox(this);
	m_pcboBinCount->setMinimumWidth(90);
	m_pcboBinCount->setStyleSheet("border:2px solid gray; font-size:20px;");
	m_pToolBar->addWidget(m_pcboBinCount);

	m_pcboBinCount->addItems(QStringList {"Auto", "3", "5", "7", "10"} );

	QObject::connect(m_pcboBinCount, 
		static_cast<void (QComboBox::*)(QString const&)>(&QComboBox::currentIndexChanged),
		this, &CMainWindow::onBinCountChanged);
}

void CMainWindow::onRun()
{
	QElapsedTimer oTimer;
	oTimer.start();

	QVector<double> aNumericValues;

	for (int i = 0; i < 10; i++)
		aNumericValues << qrand() % 20;

	m_pChartContorller->run(aNumericValues, "Second Chart", EChartType::Histogram);

	aNumericValues.clear();
	for (int i = 0; i < 20; i++)
		aNumericValues << qrand() % 7;

	m_pChartContorller->run(aNumericValues, "First Chart", EChartType::Histogram);

	int nCalculationTime = (int)oTimer.elapsed();

	int nMSeconds = nCalculationTime % 1000;
	int nSeconds = nCalculationTime / 1000;

	m_pTimer->setText(" " + QString::number(nSeconds) + " : " + QString::number(nMSeconds));
}

void CMainWindow::onBinCountChanged(const QString& sText)
{
	if (sText.compare(QString("Auto"), Qt::CaseInsensitive) == 0)
		setBinCount(0);
	else
		setBinCount(sText.toInt());

	m_pChartContorller->clear();
	onRun();
}
////////////////////////////////////////////////////////////////////////////////