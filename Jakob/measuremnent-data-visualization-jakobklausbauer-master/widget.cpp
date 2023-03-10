#include "widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    m_prov = new SinusDataProvider();
    QChartView* chartV = new QChartView();
    m_viewer = new DataViewer(m_prov, chartV);
    m_viewer->setWindowSize(1000);
    m_prov->start();
    m_prov->setAutoRefresh(true);
    m_prov->setRefreshIntervall(25);
    m_prov->setSampleRate(100);

    QChart* chart = m_viewer->getChart();
    m_tbl = new QTableWidget(10, 2);
    m_ui_amp = new QSpinBox();
    m_ui_amp->setRange(1, 100);
    m_ui_amp->setValue(1);
    m_ui_frequency = new QSpinBox();
    m_ui_frequency->setRange(1, 100);
    m_ui_frequency->setValue(1);
    m_ui_samplerate = new QSpinBox();
    m_ui_samplerate->setRange(1, 999);
    m_ui_samplerate->setValue(100);
    m_ui_updaterate = new QSpinBox();
    m_ui_updaterate->setRange(1, 999);
    m_ui_updaterate->setValue(100);
    m_ui_winSize = new QSpinBox();
    m_ui_winSize->setRange(500, 10000);
    m_ui_winSize->setValue(1000);
    m_ui_winSize->setSingleStep(500);

    QGridLayout* layout = new QGridLayout();

    chart->setTitle("Sinus DataProvider");
    chartV->setChart(chart);
    chartV->setRenderHint(QPainter::Antialiasing);
    layout->addWidget(chartV, 0, 0, 1, 2);

    layout->addWidget(m_ui_amp, 1, 1, 1, 1);
    layout->addWidget(new QLabel("Amplitude [-]"), 1, 0, 1, 1);
    layout->addWidget(m_ui_frequency, 2, 1, 1, 1);
    layout->addWidget(new QLabel("Frequenz [Hz]"), 2, 0, 1, 1);
    layout->addWidget(m_ui_samplerate, 3, 1, 1, 1);
    layout->addWidget(new QLabel("Sample Rate [Hz]"), 3, 0, 1, 1);
    layout->addWidget(m_ui_updaterate, 4, 1, 1, 1);
    layout->addWidget(new QLabel("Update Rate [Hz]"), 4, 0, 1, 1);
    layout->addWidget(m_ui_winSize, 5, 1, 1, 1);
    layout->addWidget(new QLabel("Window Size [ms]"), 5, 0, 1, 1);

    connect(m_ui_amp, &QSpinBox::valueChanged, this, &Widget::onAmpChanged);
    connect(m_ui_amp, &QSpinBox::editingFinished, this, &Widget::onAmpChanged);
    connect(m_ui_frequency, &QSpinBox::valueChanged, this, &Widget::onFrequencyChanged);
    connect(m_ui_frequency, &QSpinBox::editingFinished, this, &Widget::onFrequencyChanged);
    connect(m_ui_samplerate, &QSpinBox::valueChanged, this, &Widget::onSampleRateChanged);
    connect(m_ui_samplerate, &QSpinBox::editingFinished, this, &Widget::onSampleRateChanged);
    connect(m_ui_updaterate, &QSpinBox::valueChanged, this, &Widget::onUpdateRateChanged);
    connect(m_ui_updaterate, &QSpinBox::editingFinished, this, &Widget::onUpdateRateChanged);
    connect(m_ui_winSize, &QSpinBox::valueChanged, this, &Widget::onWinSizeChanged);
    connect(m_ui_winSize, &QSpinBox::editingFinished, this, &Widget::onWinSizeChanged);

    onAmpChanged();
    onFrequencyChanged();
    onSampleRateChanged();
    onUpdateRateChanged();
    onWinSizeChanged();

    this->setLayout(layout);
}

Widget::~Widget()
{
    m_prov->terminate();
    delete m_viewer;
    delete m_prov;
}

void Widget::onAmpChanged()
{
    double amp = m_ui_amp->value();
    if(amp == m_prov->getAmplitude()) return;
    m_prov->setAmplitude(amp);
}

void Widget::onFrequencyChanged()
{
    double period = m_ui_frequency->value();
    if(period == m_prov->getFrequency()) return;
    m_prov->setFrequency(period);
}

void Widget::onSampleRateChanged()
{
    int sampleRate = m_ui_samplerate->value();
    if(sampleRate == m_prov->getSampleRate()) return;
    m_prov->setSampleRate(sampleRate);
}

void Widget::onUpdateRateChanged()
{
    int updateRate = 1000 / m_ui_updaterate->value();
    if(updateRate == m_prov->getRefreshIntervall()) return;
    m_prov->setRefreshIntervall(updateRate);
}

void Widget::onWinSizeChanged()
{
    int winSize = m_ui_winSize->value();
    if(winSize == m_viewer->getWindowSize()) return;
    m_viewer->setWindowSize(winSize);
}
