//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Viewer.h"
#include <graphics.hpp>
#include <jpeg.hpp>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "G32_Image"
#pragma resource "*.dfm"


#include <GR32_Transforms.hpp>

#include <math.h>
#include <SysUtils.hpp>

TFViewer *FViewer;

void CountRGB(TCanvas *EenCanvas ,int  x, int y, int  Hoeveelheid ,double & TotRood,double &TotGroen,double &TotBlauw )
{
  int Kleur;
  int Rood, Groen, Blauw ;

  Kleur=ColorToRGB(EenCanvas->Pixels[x][y]);
  Blauw=Kleur << 16;
  Groen=(Kleur >> 8) & 0x00FF;
  Rood=Kleur & 0x0000FF;
  TotRood=TotRood+Rood/Hoeveelheid;
  TotGroen=TotGroen+Groen/Hoeveelheid;
  TotBlauw=TotBlauw+Blauw/Hoeveelheid;
};

int round(double aVal)
{
  return (int)(aVal);
}

fAntiAliasing(TImage *apImage,double aFacteur)
{
int   x,y, Hoeveelheid ,oldx,oldy;
Graphics::TBitmap  *NieuweBitmap ;
int   Rood, Blauw, Groen ;
double   TotRood,TotGroen,TotBlauw ;

  Graphics::TBitmap *Bitmap=apImage->Picture->Bitmap;
  NieuweBitmap=new Graphics::TBitmap;
  NieuweBitmap->Assign(Bitmap);
  NieuweBitmap->Width=apImage->Width*aFacteur;
  NieuweBitmap->Height=apImage->Height*aFacteur;
  TotRood=0;
  TotGroen=0;
  TotBlauw=0;
  for (x=0 ;x< NieuweBitmap->Width;x++)
  {
    for (y=0;y<NieuweBitmap->Height;y++)
    {
      oldx=x/aFacteur;
      oldx=y/aFacteur;
      TotRood=0; TotGroen=0; TotBlauw=0;
      CountRGB(Bitmap->Canvas,oldx,oldy,2,TotRood,TotGroen,TotBlauw);
      CountRGB(Bitmap->Canvas,oldx-1,oldy,8,TotRood,TotGroen,TotBlauw);
      CountRGB(Bitmap->Canvas,oldx,oldy-1,8,TotRood,TotGroen,TotBlauw);
      CountRGB(Bitmap->Canvas,oldx+1,oldy,8,TotRood,TotGroen,TotBlauw);
      CountRGB(Bitmap->Canvas,oldx,oldy+1,8,TotRood,TotGroen,TotBlauw);
      NieuweBitmap->Canvas->Pixels[x][y]=RGB(round(TotRood),round(TotGroen),round(TotBlauw));
    };
  };
  apImage->Picture->Bitmap=NieuweBitmap;
};

fRotate(TImage32 *apImage,int aAngle)
{
int   x,y, Hoeveelheid ,oldx,oldy;
TBitmap32  *NieuweBitmap ;

  TBitmap32 *Bitmap=apImage->Bitmap;
  NieuweBitmap=new TBitmap32;
  NieuweBitmap->Assign(Bitmap);
  //NieuweBitmap->Width=apImage->Width*aFacteur;
  //NieuweBitmap->Height=apImage->Height*aFacteur;
  apImage->ScaleMode=smNormal;
  //NieuweBitmap->Width=mImgWidthOri;
  //NieuweBitmap->Height=mImgHeightOri;

  NieuweBitmap->Width=apImage->Bitmap->Height;
  NieuweBitmap->Height=apImage->Bitmap->Width;
  int lError=0;
  try
  {
    for (x=0 ;x< Bitmap->Width;x++)
    {
      for (y=0;y<Bitmap->Height;y++)
      {
        TColor32 lPixel=Bitmap->Pixel[x][y];
        if (aAngle==90)
        {
          NieuweBitmap->Pixel[Bitmap->Height-y-1][x]=lPixel;
        }
        else
        {
           NieuweBitmap->Pixel[y][Bitmap->Width-x-1]=lPixel;
        }
      };
    };
  }
  catch(...)
  {
    lError=1;
  }
  apImage->Width=NieuweBitmap->Width;
  apImage->Height=NieuweBitmap->Height;


  apImage->Bitmap=NieuweBitmap;
  try
  {
    delete NieuweBitmap;
  }
  catch(...)
  {
  }

};

//---------------------------------------------------------------------------
__fastcall TFViewer::TFViewer(TComponent* Owner)
  : TForm(Owner)
{
  //mNum=-1;
  mFullScreen=false;
  //OnMouseWheel = FormMouseWheel;
  mZoom = 100.0;
}
//---------------------------------------------------------------------------


void TFViewer::LoadImage(AnsiString aFile)
{
  AnsiString lMsg;
  if (aFile==mFileName)
  {
    return;
  }
  try
  {
      mZoom=100;
      mZoomX=0;
      mZoomY=0;
      TGraphic *lpGraph=NULL;
      AnsiString lN=aFile.UpperCase();
      int lIsJpeg=(lN.Pos(".JPG")>0)||(lN.Pos(".JPEG")>0);
      int lIsBitmap=((lN.Pos(".BMP")>0)||(lN.Pos(".GIF")>0));

      if ((!lIsJpeg)&&(!lIsBitmap))
        return;
      Caption=aFile;

      Image321->Visible = false;

      if (lIsJpeg)
      {
        TJPEGImage *lpJpeg = new TJPEGImage;
        lpJpeg->LoadFromFile(aFile);
        lpJpeg->DIBNeeded();
        lpGraph = lpJpeg;
      }
      else
      {
        Graphics::TBitmap *lpBitmap = new Graphics::TBitmap();
        //lpGraph = new TGraphic();

        lpBitmap->LoadFromFile(aFile);
        lpGraph = lpBitmap;
      }

       mImgWidthOri=lpGraph->Width;
       mImgHeightOri=lpGraph->Height;


      //delete Image321->Picture->Graphic;
      //Image321->Picture->Graphic=NULL;
      if (!mFullScreen)
      {
        Width=lpGraph->Width+10;
        Height=lpGraph->Height+10;
      }
      //mImgWidth=lpJpeg->Width;
      //mImgHeight=lpJpeg->Height;

      //Image321->Picture->Graphic =lpGraph;
      //Image321->Assign(Image321->Picture);

      //delete Image321->Bitmap;
      //Image321->Bitmap=NULL;
      Image321->Bitmap->Assign(lpGraph);
      delete lpGraph;
      lpGraph=NULL;
      //Img32V->Bitmap->Graphic =lpGraph;
      // ne marche pas
      //if (false && MenAntialias->Checked && mFullScreen)
      //{
      //  double lRap1=double(Screen->Width-10)/lpGraph->Width;
      //  double lRap2=double(Screen->Height-10)/lpGraph->Height;
       // double   lRap=(lRap1<lRap2) ? lRap1 : lRap2;
        //AntiAliasing(Image321,lRap);


     // }

      fRefreshScreen();



      Image321->Visible = true;
      //mNum=aNum;
      mFileName=aFile;
      LabFileName->Caption=mFileName;


  }
  catch(Exception &Ex)
  {
    lMsg = Ex.Message;
    return;
  }
}

void __fastcall TFViewer::FormKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
  if (Key==VK_ADD&& Shift.Empty())
  {
    FHistory->ViewImg(1);
    return;
  }
  if (Key==VK_SUBTRACT&& Shift.Empty())
  {
    FHistory->ViewImg(-1);
    return;
  }
  if(Key=='P' && Shift.Empty())
  {
    //Image321->Canvas->TextOut(0,0,mFileName);
    //Canvas->TextOut(20,20,mFileName);

    LabFileName->Visible=!LabFileName->Visible;
    if( LabFileName->Visible)
    {
      //Canvas->Font=Label1->Font;
      //Canvas->Pen=Label1->Canvas->Pen;
      //Canvas->TextOut(0,0,mFileName);
    }
  }
  if ((Key==VK_NEXT) || (Key==VK_DOWN && Shift.Empty()))
  {
    FHistory->ViewImgFiles(1);
    return;
  }
  if ((Key==VK_PRIOR) || (Key==VK_UP&& Shift.Empty()))
  {
    FHistory->ViewImgFiles(-1);
    return;
  }

  if ((Key==VK_RIGHT && Shift.Empty()))
  {
    FHistory->ViewImgFiles(20);
    return;
  }
  if ((Key==VK_LEFT && Shift.Empty()))
  {
    FHistory->ViewImgFiles(-20);
    return;
  }

  if((Key==VK_LEFT) &&Shift.Contains(ssCtrl) )
  {
    if(mZoom>20)
    {
      mZoom=mZoom*0.8;
      if(mZoom>99 && mZoom<101)
      {
        mZoom=100;
      }
      fRefreshScreen();
    }
    return;
  }
  if((Key==VK_RIGHT) &&Shift.Contains(ssCtrl) )
  {
    if(mZoom<2000)
    {
      mZoom=mZoom/0.8;
      if(mZoom>99 && mZoom<101)
      {
        mZoom=100;
      }
    }
    fRefreshScreen();
    return;

  }
  if(Shift.Contains(ssShift) )
  {
    if((Key==VK_LEFT) )
    {
      mZoomX-=50;
      fRefreshScreen();
    }
    if((Key==VK_RIGHT) )
    {
      mZoomX+=50;
      fRefreshScreen();
    }
    if((Key==VK_UP) )
    {
      mZoomY-=50;
      fRefreshScreen();
    }
    if((Key==VK_DOWN) )
    {
      mZoomY+=50;
      fRefreshScreen();
    }
  }
  if ((Key=='F')&&Shift.Contains(ssCtrl))
  {
    mFullScreen=!mFullScreen;
    fRefreshScreen();
    return;
  }
  double Alpha=0;
  if ((Key=='R')&&(Shift.Contains(ssCtrl)))
  {
    Alpha=90;
    fRotate(Image321,90);
    mImgWidthOri=Image321->Bitmap->Width;
    mImgHeightOri=Image321->Bitmap->Height;

    fRefreshScreen();
    return;
  }

  if ((Key=='S')&&(Shift.Contains(ssCtrl)))
  {
    TJPEGImage *lpJpeg = new TJPEGImage;
    Graphics::TBitmap *lpBitmap = new Graphics::TBitmap();
        //lpGraph = new TGraphic();


    TMemoryStream *lpStream = new TMemoryStream;
    //AnsiString lTmpBmp=AnsiString(getenv("TMP"))+"\\"+"tmpimg.bmp";
    AnsiString lTmpJpg=AnsiString(getenv("TMP"))+"\\"+"tmpimg.jpg";

    Image321->Bitmap->SaveToStream(lpStream);
    lpStream->Seek(0,soFromBeginning )	;
    //Image321->Bitmap->SaveToFile(lTmpBmp);
    //lpJpeg->DIBNeeded();
    //lpJpeg->LoadFromStream(lpStream);
    lpBitmap->LoadFromStream(lpStream);
    //lpBitmap->LoadFromFile(lTmpBmp);
    lpJpeg->Assign(lpBitmap);
    lpJpeg->JPEGNeeded();
    //SaveToStream
    //lpJpeg->Assign(Image321->Bitmap);
    try
    {
      int lAge=FileAge(mFileName);
      lpJpeg->SaveToFile(mFileName);
      if (lAge!=-1)
      {
        FileSetDate(mFileName,lAge);
      }
    }
    catch(...)
    {
      1;
    }
    //Image321->Bitmap->SaveToFile(2"c:\\temp\\Test.Jpg");
    delete lpStream;
    delete lpJpeg;
    delete lpBitmap;
  }
  if (Key==VK_DELETE)
  {
    try
    {
      DeleteFile(mFileName);
    }
    catch(...)
    {
      1;
    }
    return;
  }

  if ((Key=='L')&&(Shift.Contains(ssCtrl)))
  {
    Alpha=270;
    fRotate(Image321,270);
    mImgWidthOri=Image321->Bitmap->Width;
    mImgHeightOri=Image321->Bitmap->Height;

    fRefreshScreen();
    return;
  }

  if ((Key=='M')&&(Shift.Contains(ssCtrl)))
  {
    Alpha=180;
  }

  if (Alpha!=0)
  {
    TAffineTransformation *T= new TAffineTransformation();
    TImage32 *Src=Image321;
    //TImage32 *Dst=Image321;
    TBitmap32 *NieuweBitmap=new TBitmap32;
    //NieuweBitmap->Assign(Bitmap);
    //NieuweBitmap->Width=apImage->Width*aFacteur;
    //NieuweBitmap->Height=apImage->Height*aFacteur;

    int SrcR = Src->Bitmap->Width - 1;
    int SrcB = Src->Bitmap->Height - 1;

    double Sx,Sy,scale;
    int lTailleM=(Src->Bitmap->Width>Src->Bitmap->Height) ?Src->Bitmap->Width :Src->Bitmap->Height;
    T->SrcRect = FloatRect(0, 0, SrcR + 1, SrcB + 1);
    int lCenterX=SrcR/2;
    int lCenterY=SrcB/2;
    try
    {
      // shift the origin
      T->Clear();

      // move the origin to a center for scaling and rotation
      //T->Translate(-SrcR / 2, -SrcB / 2);
      T->Rotate(lCenterX, lCenterY, Alpha);
      Alpha = Alpha * 3.14159265358979 / 180;

      // get the width and height of rotated image (without scaling)
      Sx = abs(SrcR * cos(Alpha)) + abs(SrcB * sin(Alpha));
      Sy = abs(SrcR * sin(Alpha)) + abs(SrcB * cos(Alpha));

      // calculate a new scale so that the image fits in original boundaries
      //Sx = Src->Bitmap->Width / Sx;
      //Sy = Src->Bitmap->Height / Sy;
      //scale = (Sx< Sy) ? Sx : Sy;
      //int lNewWidth=

      NieuweBitmap->Width=lTailleM;
      NieuweBitmap->Height=lTailleM;

      //NieuweBitmap->Width=Sx;
      //NieuweBitmap->Height=Sy;
      //T->Scale(scale, scale);

      // move the origin back
      //T->Translate(SrcR / 2, SrcB / 2);

      // transform the bitmap
      Src->BeginUpdate();
      //Src->Width=
      NieuweBitmap->Clear(clGray32);
      //Transform(Dst->Bitmap, Src->Bitmap, T);
      Transform(NieuweBitmap, Src->Bitmap, T);
      Src->Bitmap=NieuweBitmap;

      /*
      Src->Bitmap->Width=NieuweBitmap->Width;
      Src->Bitmap->Height=NieuweBitmap->Height;
      Src->Width=Src->Bitmap->Width;
      Src->Height=Src->Bitmap->Height;
      Src->Bitmap->Assign(NieuweBitmap);
      //Src->Bitmap->Width=Sx;
      //Src->Bitmap->Height=Sy;
      */
      Src->EndUpdate();
      Src->Repaint();
      delete T;
      delete NieuweBitmap;
      fRefreshScreen();

    }
    catch(...)
    {
      1;
    }
  }

}
//---------------------------------------------------------------------------


void TFViewer::fRefreshScreen()
{
  //Image321->Stretch=mFullScreen;
  Image321->ScaleMode=(mFullScreen) ? smResize :smNormal;
  double lRap=1;
  if (mFullScreen)
  {
    Image321->Bitmap->StretchFilter=mStretchFilter;

    BorderStyle=bsNone;
    double lRap1=double(Screen->Width-10)/mImgWidthOri;
    double lRap2=double(Screen->Height-10)/mImgHeightOri;
    Left=0;
    Top=0;
    lRap=(lRap1<lRap2) ? lRap1 : lRap2;
    lRap=(lRap*mZoom)/100.0;
    Image321->Width=lRap*(mImgWidthOri);
    Image321->Height=lRap*(mImgHeightOri);


    Width=Screen->Width;
    Height=Screen->Height;
    int lRabW=Width-Image321->Width;
    int lRabH =Height-Image321->Height;
    if (lRabW<0)
    {
      lRabW=0;
    }
    if (lRabH<0)
    {
      lRabH=0;
    }
    Image321->Left=mZoomX+(lRabW/2);
    Image321->Top=mZoomY+(lRabH/2);

    //Align=alClient;
    //Position=poScreenCenter;

  }
  else
  {
    BorderStyle=bsSizeable;
    //Position=poDesigned;
    //Align=alNone;
    Image321->Left=0;
    Image321->Top=0;
    Width=mImgWidthOri+30;
    Height=mImgHeightOri+40;
    Image321->Bitmap->StretchFilter=sfNearest;
    Image321->Width=mImgWidthOri+5;
    Image321->Height=mImgHeightOri+5;


  }
}
void __fastcall TFViewer::MenLinearAntialiasClick(TObject *Sender)
{
  MenLinearAntialias->Checked=  true;
  mStretchFilter=sfLinear;
  if (mFullScreen)
  {
    Image321->Bitmap->StretchFilter=mStretchFilter;
  }
}
//---------------------------------------------------------------------------


void __fastcall TFViewer::MenNoAntialiasClick(TObject *Sender)
{
  MenNoAntialias->Checked=  true;
  mStretchFilter=sfNearest;
  Image321->Bitmap->StretchFilter=mStretchFilter;
}
//---------------------------------------------------------------------------

void __fastcall TFViewer::MenSplineAntialiasClick(TObject *Sender)
{
  MenSplineAntialias->Checked=  true;
  mStretchFilter=sfSpline;
  if (mFullScreen)
  {
    Image321->Bitmap->StretchFilter=mStretchFilter;
  }

}
//---------------------------------------------------------------------------


void __fastcall TFViewer::FormMouseWheel(TObject *Sender,
      TShiftState Shift, int WheelDelta, const TMyPoint &MousePos, bool &Handled)
{
  if (abs(WheelDelta)>=120)
  {
    WheelDelta=WheelDelta/120;
  }
  if (WheelDelta!=0)
  {
    FHistory->ViewImgFiles(-WheelDelta);
    Handled=true;
  }

}
//---------------------------------------------------------------------------



void __fastcall TFViewer::FormMouseMove(TObject *Sender, TShiftState Shift,
      int X, int Y)
{
  int lX=X;  
}
//---------------------------------------------------------------------------

void __fastcall TFViewer::FormMouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
  int lX=X;  
}
//---------------------------------------------------------------------------

void __fastcall TFViewer::Image321MouseMove(TObject *Sender,
      TShiftState Shift, int X, int Y, TCustomLayer *Layer)
{
  int lX=X;  
}
//---------------------------------------------------------------------------



void __fastcall TFViewer::Image321MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y,
      TCustomLayer *Layer)
{
  if (Button== mbLeft)
  {
   mMouseX=X;
   mMouseY=Y;
  }

}
//---------------------------------------------------------------------------

void __fastcall TFViewer::Image321MouseUp(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y,
      TCustomLayer *Layer)
{
  if(Button!= mbLeft)
        return;

  int dx=X-mMouseX;
  int dy=Y-mMouseY;
  if ((dx!=0)||(dy!=0))
  {
    mZoomX+=dx;
    mZoomY+=dy;
    fRefreshScreen();
  }
}
//---------------------------------------------------------------------------

void __fastcall TFViewer::MenPrintFileNameClick(TObject *Sender)
{
  MenPrintFileName->Checked=!MenPrintFileName->Checked;
   LabFileName->Visible=MenPrintFileName->Checked;
}
//---------------------------------------------------------------------------

