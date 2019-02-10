unit MainUnit;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, StdCtrls, ExtCtrls, GR32, GR32_Image, GR32_Transforms;

type
  TForm1 = class(TForm)
    Image32: TImage32;
    RadioGroup1: TRadioGroup;
    CheckBox1: TCheckBox;
    procedure FormCreate(Sender: TObject);
    procedure RadioGroup1Click(Sender: TObject);
    procedure CheckBox1Click(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
  end;

var
  Form1: TForm1;

implementation

{$R *.dfm}

procedure TForm1.FormCreate(Sender: TObject);
var
  I, J: Integer;
begin
  Image32.Bitmap.SetSize(16, 16);
  for I := 0 to 15 do
    for J := 0 to 15 do
      if (I + J) mod 2 = 0 then Image32.Bitmap.Pixel[I, J] := clBlack32
      else Image32.Bitmap.Pixel[I, J] := clWhite32;
  for I := 0 to 15 do
  begin
    Image32.Bitmap.Pixel[I, 9] := Gray32(I * 255 div 15);
    Image32.Bitmap.Pixel[I, 10] := Gray32(I * 255 div 15);
  end;

  for I := 0 to 7 do
  begin
    Image32.Bitmap.Pixel[I * 2, 11] := Gray32(I * 255 div 7);
    Image32.Bitmap.Pixel[I * 2 + 1, 11] := Gray32(I * 255 div 7);
    Image32.Bitmap.Pixel[I * 2, 12] := Gray32(I * 255 div 7);
    Image32.Bitmap.Pixel[I * 2 + 1, 12] := Gray32(I * 255 div 7);
    Image32.Bitmap.Pixel[I * 2, 13] := Gray32(I * 255 div 7);
    Image32.Bitmap.Pixel[I * 2 + 1, 13] := Gray32(I * 255 div 7);
  end;

  with Image32.Bitmap do
  begin
    for I := 1 to 4 do
      for J := 1 to 4 do
        Pixels[I, J] := $FF5F5F5F;
    for I := 2 to 3 do
      for J := 2 to 3 do
        Pixels[I, J] := $FFAFAFAF;
  end;
end;

procedure TForm1.RadioGroup1Click(Sender: TObject);
begin
  Image32.Bitmap.StretchFilter := TStretchFilter(RadioGroup1.ItemIndex);
end;

procedure TForm1.CheckBox1Click(Sender: TObject);
begin
  GR32_Transforms.FullEdge := CheckBox1.Checked;
  Image32.Bitmap.Changed;
end;

end.
