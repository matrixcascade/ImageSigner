#include "imagesigner.h"

ImageSigner::ImageSigner(QWidget *parent, Qt::WFlags flags)
	: QMainWindow(parent, flags)
{
	ui.setupUi(this);
	about=new ProAbout();
	connect(ui.actionOpen_Source_Image,SIGNAL(triggered()),this,SLOT(SLOT_LoadResPixmap()));
	connect(ui.actionOpen_Sign_Image,SIGNAL(triggered()),this,SLOT(SLOT_LoadSigPixmap()));
	connect(ui.pushButton_DoSign,SIGNAL(clicked()),this,SLOT(SLOT_DoSign()));
	connect(ui.pushButton_SaveTo,SIGNAL(clicked()),this,SLOT(SLOT_SaveTo()));
	connect(ui.actionAbout_ImageSigner,SIGNAL(triggered()),this,SLOT(SLOT_About()));
}

ImageSigner::~ImageSigner()
{

}

bool isPow2(int x)
{
	return !(x&(x-1));
}

void ImageSigner::SignImage()
{
	complex *pcplx;
	int *power,Max;float *Amp;
	float *mapScale;
	int w,h;
	QImage RImage,GImage,BImage;
	QImage image,RedChannelImage,GreenChannelImage,BlueChannelImage,freqRedImage,freqGreenImage,freqBlueImage,AmpRedImage,AmpGreenImage,AmpBlueImage,SiImage,SiedImage;
	QImage disResImage,disRedChannelImage,disGreenChannelImage,disBlueChannelImage,disfreqRedImage,disfreqGreenImage,disfreqBlueImage,disAmpRedImage,disAmpGreenImage,disAmpBlueImage,disSiImage,disSiedImage;
	QColor rgb;
	
	if (!m_Resmap.isNull())
	{
		image=m_Resmap.toImage();
		
		RImage=QImage(m_Resmap.width(),m_Resmap.height(),QImage::Format_ARGB32);
		GImage=QImage(m_Resmap.width(),m_Resmap.height(),QImage::Format_ARGB32);
		BImage=QImage(m_Resmap.width(),m_Resmap.height(),QImage::Format_ARGB32);
		freqRedImage=QImage(m_Resmap.width(),m_Resmap.height(),QImage::Format_ARGB32);
		freqGreenImage=QImage(m_Resmap.width(),m_Resmap.height(),QImage::Format_ARGB32);
		freqBlueImage=QImage(m_Resmap.width(),m_Resmap.height(),QImage::Format_ARGB32);
		AmpRedImage=QImage(m_Resmap.width(),m_Resmap.height(),QImage::Format_ARGB32);
		AmpGreenImage=QImage(m_Resmap.width(),m_Resmap.height(),QImage::Format_ARGB32);
		AmpBlueImage=QImage(m_Resmap.width(),m_Resmap.height(),QImage::Format_ARGB32);

		SiedImage=QImage(m_Resmap.width(),m_Resmap.height(),QImage::Format_ARGB32);

		for (int y=0;y<m_Resmap.height();y++)
		{
			for (int x=0;x<m_Resmap.width();x++)
			{
				rgb=image.pixel(x,y);
				RImage.setPixel(QPoint(x,y),QColor(rgb.red(),0,0).rgba());
				GImage.setPixel(QPoint(x,y),QColor(0,rgb.green(),0).rgba());
				BImage.setPixel(QPoint(x,y),QColor(0,0,rgb.blue()).rgba());
			}
		}

		RedChannelImage=RImage;
		GreenChannelImage=GImage;
		BlueChannelImage=BImage;
	}

	
	
	power=(int *)malloc(sizeof(int)*m_Resmap.height()*m_Resmap.width());
	Amp=(float *)malloc(sizeof(float)*m_Resmap.height()*m_Resmap.width());
	pcplx=(complex *)malloc(sizeof(complex)*m_Resmap.height()*m_Resmap.width());
	mapScale=(float *)malloc(sizeof(float)*m_Resmap.height()*m_Resmap.width()/4);


	//Initialize Map Scale
	if (!m_Signmap.isNull())
	{
		SiImage=m_Signmap.scaled(m_Resmap.width()/2,m_Resmap.height()/2).toImage();
		w=SiImage.width();
		h=SiImage.height();
		if(ui.radioButton_Enlarge->isChecked())
		{
			for (int y=0;y<h;y++)
			{
			for (int x=0;x<w;x++)
			{
				mapScale[y*w+x]=SiImage.pixel(x,y)&0x00ffffff?ui.horizontalSlider_Power->value():1.f;
			}
			}
		}
		else if(ui.radioButton_Reduce->isChecked())
		{
			for (int y=0;y<h;y++)
			{
				for (int x=0;x<w;x++)
				{
					mapScale[y*w+x]=SiImage.pixel(x,y)&0x00ffffff?1.0f/ui.horizontalSlider_Power->value():1.f;
				}
			}
		}
		else
		{
			for (int y=0;y<h;y++)
			{
				for (int x=0;x<w;x++)
				{
					mapScale[y*w+x]=1.0f;
				}
			}
		}
	}

	//Sort R
	//////////////////////////////////////////////////////////////////////////
	Max=0;
	h=m_Resmap.height();
	w=m_Resmap.width();
	for (int y=0;y<h;y++)
	{
		for (int x=0;x<w;x++)
		{
			rgb=image.pixel(x,y);
			pcplx[y*h+x].im=0;
			pcplx[y*h+x].re=rgb.red();   
		}
	}
	FFT_2(pcplx,pcplx,h);

	if (!m_Resmap.isNull()&&!m_Signmap.isNull()&&ui.checkBox_R->isChecked())
	{
		for (int y=1;y<h/2-1;y++)
		{
			for (int x=1;x<w/2-1;x++)
			{
				pcplx[y*w+x].re*=mapScale[y*w/2+x];
				pcplx[y*w+x].im*=mapScale[y*w/2+x];

				pcplx[(h-y)*w+w-x].re*=mapScale[y*w/2+x];
				pcplx[(h-y)*w+w-x].im*=mapScale[y*w/2+x];
			}
		}
	}

	FFT_2_Shift(pcplx,pcplx,h);

	for (int y=0;y<h;y++)
	{
		for (int x=0;x<w;x++)
		{
			power[y*h+x]=sqrt(pcplx[y*h+x].im*pcplx[y*h+x].im+pcplx[y*h+x].re+pcplx[y*h+x].re);
			if(pcplx[y*h+x].re*pcplx[y*h+x].re<0.00000001)
				Amp[y*h+x]=0;
			else
				Amp[y*h+x]=atan(pcplx[y*h+x].im/pcplx[y*h+x].re);
			power[y*h+x]=log(long double(1+3*power[y*h+x]));
			if (power[y*h+x]>Max)
			{
				Max=power[y*h+x];
			}
		}
	}


	if (Max==0)
	{
		for (int y=0;y<h;y++)
		{
			for (int x=0;x<w;x++)
			{
				freqRedImage.setPixel(x,y,QColor(0,0,0).rgba());
				AmpRedImage.setPixel(x,y,QColor((Amp[y*h+x]+1.571)*255/3.1416,(Amp[y*h+x]+1.58)*255/3.1416,(Amp[y*h+x]+1.58)*255/3.1416).rgba());
			}
		}
	}
	else
	{
		for (int y=0;y<h;y++)
		{
			for (int x=0;x<w;x++)
			{
				freqRedImage.setPixel(x,y,QColor(power[y*h+x]*255/Max,power[y*h+x]*255/Max,power[y*h+x]*255/Max).rgba());
				AmpRedImage.setPixel(x,y,QColor((Amp[y*h+x]+1.571)*255/3.1416,(Amp[y*h+x]+1.58)*255/3.1416,(Amp[y*h+x]+1.58)*255/3.1416).rgba());
			}
		}
	}


	

	FFT_2_Shift(pcplx,pcplx,h);
	IFFT_2(pcplx,pcplx,h);

	for (int y=0;y<h;y++)
	{
			for (int x=0;x<w;x++)
			{
				if(pcplx[y*h+x].re>255)
				{
						RedChannelImage.setPixel(x,y,QColor(255,0,0).rgba());
						continue;
				}
				
				if(pcplx[y*h+x].re<0)
				{
						RedChannelImage.setPixel(x,y,QColor(0,0,0).rgba());
						continue;
				}

				RedChannelImage.setPixel(x,y,QColor(pcplx[y*h+x].re,0,0).rgba());
			}
	}
	

	//Sort G
	//////////////////////////////////////////////////////////////////////////
	Max=0;
	h=m_Resmap.height();
	w=m_Resmap.width();
	for (int y=0;y<h;y++)
	{
		for (int x=0;x<w;x++)
		{
			rgb=image.pixel(x,y);
			pcplx[y*h+x].im=0;
			pcplx[y*h+x].re=rgb.green();
		}
	}
	FFT_2(pcplx,pcplx,h);

	if (!m_Resmap.isNull()&&!m_Signmap.isNull()&&ui.checkBox_G->isChecked())
	{
		for (int y=1;y<h/2-1;y+=1)
		{
			for (int x=1;x<w/2-1;x+=1)
			{
				pcplx[y*w+x].re*=mapScale[y*w/2+x];
				pcplx[y*w+x].im*=mapScale[y*w/2+x];

				pcplx[(h-y)*w+w-x].re*=mapScale[y*w/2+x];
				pcplx[(h-y)*w+w-x].im*=mapScale[y*w/2+x];
			}
		}
	}

	FFT_2_Shift(pcplx,pcplx,h);
	for (int y=0;y<h;y++)
	{
		for (int x=0;x<w;x++)
		{
			power[y*h+x]=sqrt(pcplx[y*h+x].im*pcplx[y*h+x].im+pcplx[y*h+x].re+pcplx[y*h+x].re);
			if(pcplx[y*h+x].re*pcplx[y*h+x].re<0.00000001)
				Amp[y*h+x]=0;
			else
			Amp[y*h+x]=atan(pcplx[y*h+x].im/pcplx[y*h+x].re);
			power[y*h+x]=log(long double(1+3*power[y*h+x]));
			if (power[y*h+x]>Max)
			{
				Max=power[y*h+x];
			}
		}
	}

	if (Max==0)
	{
		for (int y=0;y<h;y++)
		{
			for (int x=0;x<w;x++)
			{
				freqGreenImage.setPixel(x,y,QColor(0,0,0).rgba());
				AmpGreenImage.setPixel(x,y,QColor((Amp[y*h+x]+1.571)*255/3.1416,(Amp[y*h+x]+1.58)*255/3.1416,(Amp[y*h+x]+1.58)*255/3.1416).rgba());
			}
		}
	}
	else
	{
		for (int y=0;y<h;y++)
		{
			for (int x=0;x<w;x++)
			{
				freqGreenImage.setPixel(x,y,QColor(power[y*h+x]*255/Max,power[y*h+x]*255/Max,power[y*h+x]*255/Max).rgba());
				AmpGreenImage.setPixel(x,y,QColor((Amp[y*h+x]+1.571)*255/3.1416,(Amp[y*h+x]+1.58)*255/3.1416,(Amp[y*h+x]+1.58)*255/3.1416).rgba());
			}
		}
	}
	
	FFT_2_Shift(pcplx,pcplx,h);
	IFFT_2(pcplx,pcplx,h);

	for (int y=0;y<h;y++)
	{
		for (int x=0;x<w;x++)
		{
			if(pcplx[y*h+x].re>255)
			{
				GreenChannelImage.setPixel(x,y,QColor(0,255,0).rgba());
				continue;
			}

			if(pcplx[y*h+x].re<0)
			{
				GreenChannelImage.setPixel(x,y,QColor(0,0,0).rgba());
				continue;
			}

			GreenChannelImage.setPixel(x,y,QColor(0,pcplx[y*h+x].re,0).rgba());
		}
	}

	//Sort B
	//////////////////////////////////////////////////////////////////////////
	Max=0;
	h=m_Resmap.height();
	w=m_Resmap.width();
	for (int y=0;y<h;y++)
	{
		for (int x=0;x<w;x++)
		{
			rgb=image.pixel(x,y);
			pcplx[y*h+x].im=0;
			pcplx[y*h+x].re=rgb.blue();
		}
	}
	FFT_2(pcplx,pcplx,h);
	if (!m_Resmap.isNull()&&!m_Signmap.isNull()&&ui.checkBox_B->isChecked())
	{
		for (int y=1;y<h/2-1;y+=1)
		{
			for (int x=1;x<w/2-1;x+=1)
			{
				pcplx[y*w+x].re*=mapScale[y*w/2+x];
				pcplx[y*w+x].im*=mapScale[y*w/2+x];

				pcplx[(h-y)*w+w-x].re*=mapScale[y*w/2+x];
				pcplx[(h-y)*w+w-x].im*=mapScale[y*w/2+x];
			}
		}
	}

	FFT_2_Shift(pcplx,pcplx,h);
	for (int y=0;y<h;y++)
	{
		for (int x=0;x<w;x++)
		{
			power[y*h+x]=sqrt(pcplx[y*h+x].im*pcplx[y*h+x].im+pcplx[y*h+x].re+pcplx[y*h+x].re);
			if(pcplx[y*h+x].re*pcplx[y*h+x].re<0.00000001)
				Amp[y*h+x]=0;
			else
				Amp[y*h+x]=atan(pcplx[y*h+x].im/pcplx[y*h+x].re);
			power[y*h+x]=log(long double(1+3*power[y*h+x]));
			if (power[y*h+x]>Max)
			{
				Max=power[y*h+x];
			}
		}
	}

	if (Max==0)
	{
		for (int y=0;y<h;y++)
		{
			for (int x=0;x<w;x++)
			{
				freqBlueImage.setPixel(x,y,QColor(0,0,0).rgba());
				AmpBlueImage.setPixel(x,y,QColor((Amp[y*h+x]+1.571)*255/3.1416,(Amp[y*h+x]+1.58)*255/3.1416,(Amp[y*h+x]+1.58)*255/3.1416).rgba());
			}
		}
	}
	else
	{
		for (int y=0;y<h;y++)
		{
			for (int x=0;x<w;x++)
			{
				freqBlueImage.setPixel(x,y,QColor(power[y*h+x]*255/Max,power[y*h+x]*255/Max,power[y*h+x]*255/Max).rgba());
				AmpBlueImage.setPixel(x,y,QColor((Amp[y*h+x]+1.571)*255/3.1416,(Amp[y*h+x]+1.58)*255/3.1416,(Amp[y*h+x]+1.58)*255/3.1416).rgba());
			}
		}
	}

	FFT_2_Shift(pcplx,pcplx,h);
	IFFT_2(pcplx,pcplx,h);

	for (int y=0;y<h;y++)
	{
		for (int x=0;x<w;x++)
		{
			if(pcplx[y*h+x].re>255)
			{
				BlueChannelImage.setPixel(x,y,QColor(0,0,255).rgba());
				continue;
			}

			if(pcplx[y*h+x].re<0)
			{
				BlueChannelImage.setPixel(x,y,QColor(0,0,0).rgba());
				continue;
			}

			BlueChannelImage.setPixel(x,y,QColor(0,0,pcplx[y*h+x].re).rgba());
		}
	}


	for (int y=0;y<h;y++)
	{
		for (int x=0;x<w;x++)
		{
			SiedImage.setPixel(x,y,QColor(QColor(RedChannelImage.pixel(x,y)).red(),QColor(GreenChannelImage.pixel(x,y)).green(),QColor(BlueChannelImage.pixel(x,y)).blue()).rgba());
		}
	}


	free(Amp);
	free(power);
	free(pcplx);
	free(mapScale);

	m_SignedMap=QPixmap::fromImage(SiedImage);

	//Transfer to 256*256 for display
	disResImage=m_Resmap.scaled(256,256).toImage();

	disRedChannelImage=RedChannelImage.scaled(256,256);
	disGreenChannelImage=GreenChannelImage.scaled(256,256);
	disBlueChannelImage=BlueChannelImage.scaled(256,256);

	disfreqRedImage=freqRedImage.scaled(256,256);
	disfreqGreenImage=freqGreenImage.scaled(256,256);
	disfreqBlueImage=freqBlueImage.scaled(256,256);

	disAmpRedImage=AmpRedImage.scaled(256,256);
	disAmpGreenImage=AmpGreenImage.scaled(256,256);
	disAmpBlueImage=AmpBlueImage.scaled(256,256);

	disSiImage=m_Signmap.scaled(128,128).toImage();
	disSiedImage=SiedImage.scaled(256,256);

	ui.widget_Res->setStyleSheet("");
	ui.widget_RColor->setStyleSheet("");
	ui.widget_GColor->setStyleSheet("");
	ui.widget_BColor->setStyleSheet("");
	ui.widget_RSpec->setStyleSheet("");
	ui.widget_GSpec->setStyleSheet("");
	ui.widget_BSpec->setStyleSheet("");
	ui.widget_RAmp->setStyleSheet("");
	ui.widget_GAmp->setStyleSheet("");
	ui.widget_BAmp->setStyleSheet("");
	
	QPalette palette;

	palette.setBrush(QPalette::Background,QBrush(disResImage));
	ui.widget_Res->setPalette(palette);
	ui.widget_Res->setAutoFillBackground(true);
	ui.widget_Res->update();

	palette.setBrush(QPalette::Background,QBrush(disRedChannelImage));
	ui.widget_RColor->setPalette(palette);
	ui.widget_RColor->setAutoFillBackground(true);
	ui.widget_RColor->update();

	palette.setBrush(QPalette::Background,QBrush(disGreenChannelImage));
	ui.widget_GColor->setPalette(palette);
	ui.widget_GColor->setAutoFillBackground(true);
	ui.widget_GColor->update();

	palette.setBrush(QPalette::Background,QBrush(disBlueChannelImage));
	ui.widget_BColor->setPalette(palette);
	ui.widget_BColor->setAutoFillBackground(true);
	ui.widget_BColor->update();


	palette.setBrush(QPalette::Background,QBrush(disfreqRedImage));
	ui.widget_RSpec->setPalette(palette);
	ui.widget_RSpec->setAutoFillBackground(true);
	ui.widget_RSpec->update();

	palette.setBrush(QPalette::Background,QBrush(disfreqGreenImage));
	ui.widget_GSpec->setPalette(palette);
	ui.widget_GSpec->setAutoFillBackground(true);
	ui.widget_GSpec->update();

	palette.setBrush(QPalette::Background,QBrush(disfreqBlueImage));
	ui.widget_BSpec->setPalette(palette);
	ui.widget_BSpec->setAutoFillBackground(true);
	ui.widget_BSpec->update();


	palette.setBrush(QPalette::Background,QBrush(disAmpRedImage));
	ui.widget_RAmp->setPalette(palette);
	ui.widget_RAmp->setAutoFillBackground(true);
	ui.widget_RAmp->update();

	palette.setBrush(QPalette::Background,QBrush(disAmpGreenImage));
	ui.widget_GAmp->setPalette(palette);
	ui.widget_GAmp->setAutoFillBackground(true);
	ui.widget_GAmp->update();

	palette.setBrush(QPalette::Background,QBrush(disAmpBlueImage));
	ui.widget_BAmp->setPalette(palette);
	ui.widget_BAmp->setAutoFillBackground(true);
	ui.widget_BAmp->update();

	
	ui.widget_Sign->setStyleSheet("");
	ui.widget_SignedImage->setStyleSheet("");

	palette.setBrush(QPalette::Background,QBrush(disSiImage));
	ui.widget_Sign->setPalette(palette);
	ui.widget_Sign->setAutoFillBackground(true);
	ui.widget_Sign->update();

	palette.setBrush(QPalette::Background,QBrush(disSiedImage));
	ui.widget_SignedImage->setPalette(palette);
	ui.widget_SignedImage->setAutoFillBackground(true);
	ui.widget_SignedImage->update();

	

}

void ImageSigner::DisplaySourceImage()
{
	complex *pcplx;
	int *power,Max;float *Amp;
	int w,h;
	QImage RImage,GImage,BImage;
	QImage image,RedChannelImage,GreenChannelImage,BlueChannelImage,freqRedImage,freqGreenImage,freqBlueImage,AmpRedImage,AmpGreenImage,AmpBlueImage,SiImage,SiedImage;
	QImage disResImage,disRedChannelImage,disGreenChannelImage,disBlueChannelImage,disfreqRedImage,disfreqGreenImage,disfreqBlueImage,disAmpRedImage,disAmpGreenImage,disAmpBlueImage,disSiImage,disSiedImage;
	QColor rgb;

	if (!m_Resmap.isNull())
	{
		image=m_Resmap.toImage();

		RImage=QImage(m_Resmap.width(),m_Resmap.height(),QImage::Format_ARGB32);
		GImage=QImage(m_Resmap.width(),m_Resmap.height(),QImage::Format_ARGB32);
		BImage=QImage(m_Resmap.width(),m_Resmap.height(),QImage::Format_ARGB32);
		freqRedImage=QImage(m_Resmap.width(),m_Resmap.height(),QImage::Format_ARGB32);
		freqGreenImage=QImage(m_Resmap.width(),m_Resmap.height(),QImage::Format_ARGB32);
		freqBlueImage=QImage(m_Resmap.width(),m_Resmap.height(),QImage::Format_ARGB32);
		AmpRedImage=QImage(m_Resmap.width(),m_Resmap.height(),QImage::Format_ARGB32);
		AmpGreenImage=QImage(m_Resmap.width(),m_Resmap.height(),QImage::Format_ARGB32);
		AmpBlueImage=QImage(m_Resmap.width(),m_Resmap.height(),QImage::Format_ARGB32);

		SiedImage=QImage(m_Resmap.width(),m_Resmap.height(),QImage::Format_ARGB32);

		for (int y=0;y<m_Resmap.height();y++)
		{
			for (int x=0;x<m_Resmap.width();x++)
			{
				rgb=image.pixel(x,y);
				RImage.setPixel(QPoint(x,y),QColor(rgb.red(),0,0).rgba());
				GImage.setPixel(QPoint(x,y),QColor(0,rgb.green(),0).rgba());
				BImage.setPixel(QPoint(x,y),QColor(0,0,rgb.blue()).rgba());
			}
		}

		RedChannelImage=RImage;
		GreenChannelImage=GImage;
		BlueChannelImage=BImage;
	}



	power=(int *)malloc(sizeof(int)*m_Resmap.height()*m_Resmap.width());
	Amp=(float *)malloc(sizeof(float)*m_Resmap.height()*m_Resmap.width());
	pcplx=(complex *)malloc(sizeof(complex)*m_Resmap.height()*m_Resmap.width());


	//Sort R
	//////////////////////////////////////////////////////////////////////////
	Max=0;
	h=m_Resmap.height();
	w=m_Resmap.width();
	for (int y=0;y<h;y++)
	{
		for (int x=0;x<w;x++)
		{
			rgb=image.pixel(x,y);
			pcplx[y*h+x].im=0;
			pcplx[y*h+x].re=rgb.red();   
		}
	}
	FFT_2(pcplx,pcplx,h);
	FFT_2_Shift(pcplx,pcplx,h);

	for (int y=0;y<h;y++)
	{
		for (int x=0;x<w;x++)
		{
			power[y*h+x]=sqrt(pcplx[y*h+x].im*pcplx[y*h+x].im+pcplx[y*h+x].re+pcplx[y*h+x].re);
			if(pcplx[y*h+x].re*pcplx[y*h+x].re<0.00000001)
				Amp[y*h+x]=0;
			else
				Amp[y*h+x]=atan(pcplx[y*h+x].im/pcplx[y*h+x].re);
			power[y*h+x]=log(long double(1+3*power[y*h+x]));
			if (power[y*h+x]>Max)
			{
				Max=power[y*h+x];
			}
		}
	}


	if (Max==0)
	{
		for (int y=0;y<h;y++)
		{
			for (int x=0;x<w;x++)
			{
				freqRedImage.setPixel(x,y,QColor(0,0,0).rgba());
				AmpRedImage.setPixel(x,y,QColor((Amp[y*h+x]+1.571)*255/3.1416,(Amp[y*h+x]+1.58)*255/3.1416,(Amp[y*h+x]+1.58)*255/3.1416).rgba());
			}
		}
	}
	else
	{
		for (int y=0;y<h;y++)
		{
			for (int x=0;x<w;x++)
			{
				freqRedImage.setPixel(x,y,QColor(power[y*h+x]*255/Max,power[y*h+x]*255/Max,power[y*h+x]*255/Max).rgba());
				AmpRedImage.setPixel(x,y,QColor((Amp[y*h+x]+1.571)*255/3.1416,(Amp[y*h+x]+1.58)*255/3.1416,(Amp[y*h+x]+1.58)*255/3.1416).rgba());
			}
		}
	}




	FFT_2_Shift(pcplx,pcplx,h);
	IFFT_2(pcplx,pcplx,h);

	for (int y=0;y<h;y++)
	{
		for (int x=0;x<w;x++)
		{
			if(pcplx[y*h+x].re>255)
			{
				RedChannelImage.setPixel(x,y,QColor(255,0,0).rgba());
				continue;
			}

			if(pcplx[y*h+x].re<0)
			{
				RedChannelImage.setPixel(x,y,QColor(0,0,0).rgba());
				continue;
			}

			RedChannelImage.setPixel(x,y,QColor(pcplx[y*h+x].re,0,0).rgba());
		}
	}


	//Sort G
	//////////////////////////////////////////////////////////////////////////
	Max=0;
	h=m_Resmap.height();
	w=m_Resmap.width();
	for (int y=0;y<h;y++)
	{
		for (int x=0;x<w;x++)
		{
			rgb=image.pixel(x,y);
			pcplx[y*h+x].im=0;
			pcplx[y*h+x].re=rgb.green();
		}
	}
	FFT_2(pcplx,pcplx,h);
	FFT_2_Shift(pcplx,pcplx,h);
	for (int y=0;y<h;y++)
	{
		for (int x=0;x<w;x++)
		{
			power[y*h+x]=sqrt(pcplx[y*h+x].im*pcplx[y*h+x].im+pcplx[y*h+x].re+pcplx[y*h+x].re);
			if(pcplx[y*h+x].re*pcplx[y*h+x].re<0.00000001)
				Amp[y*h+x]=0;
			else
				Amp[y*h+x]=atan(pcplx[y*h+x].im/pcplx[y*h+x].re);
			power[y*h+x]=log(long double(1+3*power[y*h+x]));
			if (power[y*h+x]>Max)
			{
				Max=power[y*h+x];
			}
		}
	}

	if (Max==0)
	{
		for (int y=0;y<h;y++)
		{
			for (int x=0;x<w;x++)
			{
				freqGreenImage.setPixel(x,y,QColor(0,0,0).rgba());
				AmpGreenImage.setPixel(x,y,QColor((Amp[y*h+x]+1.571)*255/3.1416,(Amp[y*h+x]+1.58)*255/3.1416,(Amp[y*h+x]+1.58)*255/3.1416).rgba());
			}
		}
	}
	else
	{
		for (int y=0;y<h;y++)
		{
			for (int x=0;x<w;x++)
			{
				freqGreenImage.setPixel(x,y,QColor(power[y*h+x]*255/Max,power[y*h+x]*255/Max,power[y*h+x]*255/Max).rgba());
				AmpGreenImage.setPixel(x,y,QColor((Amp[y*h+x]+1.571)*255/3.1416,(Amp[y*h+x]+1.58)*255/3.1416,(Amp[y*h+x]+1.58)*255/3.1416).rgba());
			}
		}
	}

	FFT_2_Shift(pcplx,pcplx,h);
	IFFT_2(pcplx,pcplx,h);

	for (int y=0;y<h;y++)
	{
		for (int x=0;x<w;x++)
		{
			if(pcplx[y*h+x].re>255)
			{
				GreenChannelImage.setPixel(x,y,QColor(0,255,0).rgba());
				continue;
			}

			if(pcplx[y*h+x].re<0)
			{
				GreenChannelImage.setPixel(x,y,QColor(0,0,0).rgba());
				continue;
			}

			GreenChannelImage.setPixel(x,y,QColor(0,pcplx[y*h+x].re,0).rgba());
		}
	}

	//Sort B
	//////////////////////////////////////////////////////////////////////////
	Max=0;
	h=m_Resmap.height();
	w=m_Resmap.width();
	for (int y=0;y<h;y++)
	{
		for (int x=0;x<w;x++)
		{
			rgb=image.pixel(x,y);
			pcplx[y*h+x].im=0;
			pcplx[y*h+x].re=rgb.blue();
		}
	}
	FFT_2(pcplx,pcplx,h);
	FFT_2_Shift(pcplx,pcplx,h);
	for (int y=0;y<h;y++)
	{
		for (int x=0;x<w;x++)
		{
			power[y*h+x]=sqrt(pcplx[y*h+x].im*pcplx[y*h+x].im+pcplx[y*h+x].re+pcplx[y*h+x].re);
			if(pcplx[y*h+x].re*pcplx[y*h+x].re<0.00000001)
				Amp[y*h+x]=0;
			else
				Amp[y*h+x]=atan(pcplx[y*h+x].im/pcplx[y*h+x].re);
			power[y*h+x]=log(long double(1+3*power[y*h+x]));
			if (power[y*h+x]>Max)
			{
				Max=power[y*h+x];
			}
		}
	}

	if (Max==0)
	{
		for (int y=0;y<h;y++)
		{
			for (int x=0;x<w;x++)
			{
				freqBlueImage.setPixel(x,y,QColor(0,0,0).rgba());
				AmpBlueImage.setPixel(x,y,QColor((Amp[y*h+x]+1.571)*255/3.1416,(Amp[y*h+x]+1.58)*255/3.1416,(Amp[y*h+x]+1.58)*255/3.1416).rgba());
			}
		}
	}
	else
	{
		for (int y=0;y<h;y++)
		{
			for (int x=0;x<w;x++)
			{
				freqBlueImage.setPixel(x,y,QColor(power[y*h+x]*255/Max,power[y*h+x]*255/Max,power[y*h+x]*255/Max).rgba());
				AmpBlueImage.setPixel(x,y,QColor((Amp[y*h+x]+1.571)*255/3.1416,(Amp[y*h+x]+1.58)*255/3.1416,(Amp[y*h+x]+1.58)*255/3.1416).rgba());
			}
		}
	}

	FFT_2_Shift(pcplx,pcplx,h);
	IFFT_2(pcplx,pcplx,h);

	for (int y=0;y<h;y++)
	{
		for (int x=0;x<w;x++)
		{
			if(pcplx[y*h+x].re>255)
			{
				BlueChannelImage.setPixel(x,y,QColor(0,0,255).rgba());
				continue;
			}

			if(pcplx[y*h+x].re<0)
			{
				BlueChannelImage.setPixel(x,y,QColor(0,0,0).rgba());
				continue;
			}

			BlueChannelImage.setPixel(x,y,QColor(0,0,pcplx[y*h+x].re).rgba());
		}
	}


	for (int y=0;y<h;y++)
	{
		for (int x=0;x<w;x++)
		{
			SiedImage.setPixel(x,y,QColor(QColor(RedChannelImage.pixel(x,y)).red(),QColor(GreenChannelImage.pixel(x,y)).green(),QColor(BlueChannelImage.pixel(x,y)).blue()).rgba());
		}
	}


	free(Amp);
	free(power);
	free(pcplx);

	//Transfer to 256*256 for display
	disResImage=m_Resmap.scaled(256,256).toImage();

	disRedChannelImage=RedChannelImage.scaled(256,256);
	disGreenChannelImage=GreenChannelImage.scaled(256,256);
	disBlueChannelImage=BlueChannelImage.scaled(256,256);

	disfreqRedImage=freqRedImage.scaled(256,256);
	disfreqGreenImage=freqGreenImage.scaled(256,256);
	disfreqBlueImage=freqBlueImage.scaled(256,256);

	disAmpRedImage=AmpRedImage.scaled(256,256);
	disAmpGreenImage=AmpGreenImage.scaled(256,256);
	disAmpBlueImage=AmpBlueImage.scaled(256,256);

	disSiImage=m_Signmap.scaled(256,256).toImage();
	disSiedImage=SiedImage.scaled(256,256);

	ui.widget_Res->setStyleSheet("");
	ui.widget_RColor->setStyleSheet("");
	ui.widget_GColor->setStyleSheet("");
	ui.widget_BColor->setStyleSheet("");
	ui.widget_RSpec->setStyleSheet("");
	ui.widget_GSpec->setStyleSheet("");
	ui.widget_BSpec->setStyleSheet("");
	ui.widget_RAmp->setStyleSheet("");
	ui.widget_GAmp->setStyleSheet("");
	ui.widget_BAmp->setStyleSheet("");

	QPalette palette;

	palette.setBrush(QPalette::Background,QBrush(disResImage));
	ui.widget_Res->setPalette(palette);
	ui.widget_Res->setAutoFillBackground(true);
	ui.widget_Res->update();

	palette.setBrush(QPalette::Background,QBrush(disRedChannelImage));
	ui.widget_RColor->setPalette(palette);
	ui.widget_RColor->setAutoFillBackground(true);
	ui.widget_RColor->update();

	palette.setBrush(QPalette::Background,QBrush(disGreenChannelImage));
	ui.widget_GColor->setPalette(palette);
	ui.widget_GColor->setAutoFillBackground(true);
	ui.widget_GColor->update();

	palette.setBrush(QPalette::Background,QBrush(disBlueChannelImage));
	ui.widget_BColor->setPalette(palette);
	ui.widget_BColor->setAutoFillBackground(true);
	ui.widget_BColor->update();


	palette.setBrush(QPalette::Background,QBrush(disfreqRedImage));
	ui.widget_RSpec->setPalette(palette);
	ui.widget_RSpec->setAutoFillBackground(true);
	ui.widget_RSpec->update();

	palette.setBrush(QPalette::Background,QBrush(disfreqGreenImage));
	ui.widget_GSpec->setPalette(palette);
	ui.widget_GSpec->setAutoFillBackground(true);
	ui.widget_GSpec->update();

	palette.setBrush(QPalette::Background,QBrush(disfreqBlueImage));
	ui.widget_BSpec->setPalette(palette);
	ui.widget_BSpec->setAutoFillBackground(true);
	ui.widget_BSpec->update();


	palette.setBrush(QPalette::Background,QBrush(disAmpRedImage));
	ui.widget_RAmp->setPalette(palette);
	ui.widget_RAmp->setAutoFillBackground(true);
	ui.widget_RAmp->update();

	palette.setBrush(QPalette::Background,QBrush(disAmpGreenImage));
	ui.widget_GAmp->setPalette(palette);
	ui.widget_GAmp->setAutoFillBackground(true);
	ui.widget_GAmp->update();

	palette.setBrush(QPalette::Background,QBrush(disAmpBlueImage));
	ui.widget_BAmp->setPalette(palette);
	ui.widget_BAmp->setAutoFillBackground(true);
	ui.widget_BAmp->update();

}

void ImageSigner::DisplaySignImage()
{
	QPalette palette;
	QImage SiImage=m_Signmap.scaled(128,128).toImage();
	if (!m_Signmap.isNull())
	{
		ui.widget_Sign->setStyleSheet("");
		palette.setBrush(QPalette::Background,QBrush(SiImage));
		ui.widget_Sign->setPalette(palette);
		ui.widget_Sign->setAutoFillBackground(true);
		ui.widget_Sign->update();
	}
}

void ImageSigner::SLOT_LoadResPixmap()
{

	QString filename = QFileDialog::getOpenFileName(
		this,
		"Image",
		QDir::currentPath(),
		"Image file (*.*)");
	if (!filename.isNull()) 
	{ 
		if(!m_Resmap.load(filename))
		{
			QMessageBox::information(this,"Error","Could not load target file",QMessageBox::Ok);
			return;
		}

		if (!isPow2(m_Resmap.height())||!isPow2(m_Resmap.width()))
		{
			QMessageBox::information(this,"Error","Image Height/Width must be power of 2",QMessageBox::Ok);
			return;
		}

		if (m_Resmap.height()!=m_Resmap.width())
		{
			QMessageBox::information(this,"Error","Image Height/Width must be equaled.",QMessageBox::Ok);
			return;
		}
		DisplaySourceImage();
	} 

}

void ImageSigner::SLOT_LoadSigPixmap()
{
	QString filename = QFileDialog::getOpenFileName(
		this,
		"Image",
		QDir::currentPath(),
		"Image file (*.*)");
	if (!filename.isNull()) 
	{ 
		if(!m_Signmap.load(filename))
		{
			QMessageBox::information(this,"Error","Could not load target file",QMessageBox::Ok);
			return;
		}
		DisplaySignImage();
	} 
}

void ImageSigner::SLOT_DoSign()
{
	if(m_Resmap.isNull())
	{
		QMessageBox::information(this,"Error","You should load source image before do sign",QMessageBox::Ok);
		return;
	}

	if(m_Signmap.isNull())
	{
		QMessageBox::information(this,"Error","You should load sign image before do sign",QMessageBox::Ok);
		return;
	}
	this->SignImage();
}

void ImageSigner::SLOT_SaveTo()
{
	if(m_SignedMap.isNull())
	{
		QMessageBox::information(this,"Error","Not Signed image",QMessageBox::Ok);
		return;
	}
	QString filename = QFileDialog::getSaveFileName(
		this,
		"Bit map picture",
		QDir::currentPath(),
		"Image file (*.BMP)");
	if (!filename.isNull()) 
	{ 
		m_SignedMap.save(filename);
	} 
}

void ImageSigner::SLOT_About()
{
	about->show();
}
