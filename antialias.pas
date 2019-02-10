unit AntiAlias;

interface

uses graphics;

function AntiAliasing(Bitmap : TBitmap) : TBitmap;
procedure CountRGB(EenCanvas : TCanvas; x,y : Integer; Hoeveelheid : Byte;var TotRood,TotGroen,TotBlauw : Real);

implementation

procedure CountRGB(EenCanvas : TCanvas; x,y : Integer; Hoeveelheid : Byte;var TotRood,TotGroen,TotBlauw : Real);
var
  Kleur : LongInt;
  Rood, Groen, Blauw : Integer;
begin
  Kleur:=ColorToRGB(EenCanvas.Pixels[x,y]);
  Blauw:=Kleur shr 16;
  Groen:=(Kleur shr 8) and $00FF;
  Rood:=Kleur and $0000FF;
  TotRood:=TotRood+Rood/Hoeveelheid;
  TotGroen:=TotGroen+Groen/Hoeveelheid;
  TotBlauw:=TotBlauw+Blauw/Hoeveelheid;
end;

function AntiAliasing(Bitmap : TBitmap) : TBitmap;
var
  x,y, Hoeveelheid : integer;
  NieuweBitmap : TBitmap;
  Rood, Blauw, Groen : integer;
  TotRood,TotGroen,TotBlauw : Real;
begin
  NieuweBitmap:=TBitmap.Create;
  NieuweBitmap.Assign(Bitmap);
  TotRood:=0;
  TotGroen:=0;
  TotBlauw:=0;
  for x:=0 to Bitmap.Width-1 do
  begin
    for y:=0 to Bitmap.Height-1 do
    begin
      TotRood:=0; TotGroen:=0; TotBlauw:=0;
      CountRGB(Bitmap.Canvas,x,y,2,TotRood,TotGroen,TotBlauw);
      CountRGB(Bitmap.Canvas,x-1,y,8,TotRood,TotGroen,TotBlauw);
      CountRGB(Bitmap.Canvas,x,y-1,8,TotRood,TotGroen,TotBlauw);
      CountRGB(Bitmap.Canvas,x+1,y,8,TotRood,TotGroen,TotBlauw);
      CountRGB(Bitmap.Canvas,x,y+1,8,TotRood,TotGroen,TotBlauw);
      NieuweBitmap.Canvas.Pixels[x,y]:=RGB(round(TotRood),round(TotGroen),round(TotBlauw));
    end;
  end;
  result:=NieuweBitmap;
end;

End.
