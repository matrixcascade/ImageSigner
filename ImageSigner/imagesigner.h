#ifndef IMAGESIGNER_H
#define IMAGESIGNER_H

#include <QtGui/QMainWindow>
#include "ui_imagesigner.h"
#include <QFileDialog>
#include <QDir>
#include <QPainter>
#include <QMessageBox>
#include "Pt_FFT.h"

#include "Pt_FFT.h"

class ImageSigner : public QMainWindow
{
	Q_OBJECT

public:
	ImageSigner(QWidget *parent = 0, Qt::WFlags flags = 0);
	~ImageSigner();
	void SignImage();
	void DisplaySourceImage();
	void DisplaySignImage();
public slots:
	void SLOT_LoadResPixmap();
	void SLOT_LoadSigPixmap();
	void SLOT_DoSign();
	void SLOT_SaveTo();
	void SLOT_About();
private:
	QPixmap m_Signmap;
	QPixmap m_Resmap;
	QPixmap m_SignedMap;
	Ui::ImageSignerClass ui;
};

#endif // IMAGESIGNER_H
