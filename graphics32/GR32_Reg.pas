unit GR32_Reg;

{*********************************************}
{  This unit is a part of Graphics32 library  }
{  Copyright © 2000-2003 Alex Denisov         }
{  See License.txt for licence information    }
{*********************************************}
// $Id: GR32_Reg.pas,v 1.3 2003/02/23 20:10:17 Alex Exp $

interface

{$I GR32.INC}

uses
  Classes, TypInfo,
  DesignIntf;

procedure Register;

implementation

uses
  GR32,
  GR32_Dsgn_Color,
  GR32_Dsgn_Bitmap,
  GR32_Image,
  GR32_Layers,
  GR32_RangeBars;

{ Registration }
procedure Register;
begin
  RegisterComponents('Graphics32', [TPaintBox32, TImage32, TBitmap32List,
    TRangeBar, TGaugeBar, TImgView32]);
  RegisterPropertyEditor(TypeInfo(TColor32), nil, '', TColor32Property);
  RegisterPropertyEditor(TypeInfo(TBitmap32), nil, '', TBitmap32Property);
  RegisterComponentEditor(TCustomImage32, TImage32Editor);
end;

end.
