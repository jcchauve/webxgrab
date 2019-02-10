object FViewer: TFViewer
  Left = 154
  Top = 334
  Caption = 'Image Viewer'
  ClientHeight = 506
  ClientWidth = 775
  Color = clBlack
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  OnKeyDown = FormKeyDown
  OnMouseDown = FormMouseDown
  OnMouseMove = FormMouseMove
  PixelsPerInch = 96
  TextHeight = 13
  object Image321: TImage32
    Left = 8
    Top = 8
    Width = 561
    Height = 417
    BitmapAlign = baTopLeft
    PopupMenu = PopupMenu1
    Scale = 1.000000000000000000
    ScaleMode = smResize
    TabOrder = 0
    OnMouseDown = Image321MouseDown
    OnMouseMove = Image321MouseMove
    OnMouseUp = Image321MouseUp
    object LabFileName: TLabel
      Left = 0
      Top = 0
      Width = 62
      Height = 13
      Caption = 'LabFileName'
      Color = clYellow
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clHotLight
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentColor = False
      ParentFont = False
      Visible = False
    end
  end
  object PopupMenu1: TPopupMenu
    Left = 120
    Top = 32
    object Next1: TMenuItem
      Caption = 'Next'
    end
    object Prev1: TMenuItem
      Caption = 'Prev'
    end
    object N1: TMenuItem
      Caption = '-'
    end
    object MenNoAntialias: TMenuItem
      Caption = 'No Antialias'
      RadioItem = True
      OnClick = MenNoAntialiasClick
    end
    object MenLinearAntialias: TMenuItem
      Caption = 'Linear Antialias'
      RadioItem = True
      OnClick = MenLinearAntialiasClick
    end
    object MenSplineAntialias: TMenuItem
      Caption = 'spline Antialias'
      RadioItem = True
      OnClick = MenSplineAntialiasClick
    end
    object N2: TMenuItem
      Caption = '-'
    end
    object MenPrintFileName: TMenuItem
      Caption = 'Display file name'
      OnClick = MenPrintFileNameClick
    end
  end
end
