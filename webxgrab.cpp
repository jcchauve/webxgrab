//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
USEFORM("histo.cpp", FHistory);
USEFORM("nopop1.cpp", FNoPop);
//---------------------------------------------------------------------------
bool gViewerOnly;

//---------------------------------------------------------------------------
WINAPI int WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
        try
        {
          Application->Initialize();
          Application->Title = "Web X Grabber";
          gViewerOnly=false;
		  if((_argc>1)&&(AnsiString(_argv[1])==AnsiString("-viewer")))
		  {
			gViewerOnly=true;

		  }
		  else
		  {
			Application->CreateForm(__classid(TFNoPop), &FNoPop);
		Application->CreateForm(__classid(TFHistory), &FHistory);
		Application->Run();
			}
		}
		catch (Exception &exception)
        {
                 Application->ShowException(&exception);
        }
        return 0;
}
//---------------------------------------------------------------------------
