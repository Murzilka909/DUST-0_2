object Form1: TForm1
  Left = 0
  Top = 0
  Caption = 'Dust 0_2'
  ClientHeight = 675
  ClientWidth = 1115
  Color = clInfoBk
  Font.Charset = RUSSIAN_CHARSET
  Font.Color = clWindowText
  Font.Height = -16
  Font.Name = 'Times New Roman'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 19
  object FName_Label: TLabel
    Left = 8
    Top = 624
    Width = 133
    Height = 19
    Caption = 'The file is not selected'
  end
  object PageControl1: TPageControl
    Left = 0
    Top = 0
    Width = 1107
    Height = 617
    ActivePage = HandTab
    TabOrder = 0
    object AutoTab: TTabSheet
      Caption = 'Auto mode'
      object Panel4: TPanel
        Left = -4
        Top = -4
        Width = 1101
        Height = 587
        Color = clCream
        ParentBackground = False
        TabOrder = 0
        object AutoListBox: TListBox
          Left = 8
          Top = 20
          Width = 561
          Height = 557
          ItemHeight = 19
          TabOrder = 0
        end
        object AutoSpectraButton: TButton
          Left = 583
          Top = 528
          Width = 506
          Height = 49
          Caption = 'Get spectra'
          TabOrder = 1
        end
      end
    end
    object HandTab: TTabSheet
      Caption = 'Hand mode'
      ImageIndex = 1
      object Panel3: TPanel
        Left = -2
        Top = -4
        Width = 1098
        Height = 587
        Color = clCream
        ParentBackground = False
        TabOrder = 0
        object FDataLabel: TLabel
          Left = 560
          Top = 463
          Width = 52
          Height = 19
          Caption = 'File data'
        end
        object HandListBox: TListBox
          Left = 6
          Top = 16
          Width = 339
          Height = 561
          ItemHeight = 19
          TabOrder = 0
        end
        object HandChart: TChart
          Left = 351
          Top = 16
          Width = 746
          Height = 441
          Title.Font.Height = -16
          Title.Font.Name = 'Terminal'
          Title.Text.Strings = (
            'Oscilloscope data')
          BottomAxis.Title.Caption = 'ms'
          BottomAxis.Title.Font.Color = clBlue
          BottomAxis.Title.Font.Height = -13
          BottomAxis.Title.Font.Name = 'Terminal'
          LeftAxis.Title.Caption = 'mV'
          LeftAxis.Title.Font.Color = clBlue
          LeftAxis.Title.Font.Height = -13
          LeftAxis.Title.Font.Name = 'Terminal'
          View3D = False
          TabOrder = 1
          DefaultCanvas = 'TGDIPlusCanvas'
          ColorPaletteIndex = 13
        end
        object HandFNameButton: TButton
          Left = 351
          Top = 528
          Width = 162
          Height = 49
          Caption = 'File selection'
          TabOrder = 2
        end
        object HandCheckBox: TCheckBox
          Left = 351
          Top = 487
          Width = 186
          Height = 17
          Caption = 'Files one at a time'
          TabOrder = 3
        end
        object YesButton: TButton
          Left = 912
          Top = 503
          Width = 180
          Height = 75
          Caption = 'Record speed and charge'
          TabOrder = 4
        end
        object NoButton: TButton
          Left = 726
          Top = 503
          Width = 180
          Height = 75
          Caption = 'Ignore chart'
          TabOrder = 5
        end
        object HandSpectraButton: TButton
          Left = 535
          Top = 528
          Width = 170
          Height = 49
          Caption = 'Get spectra'
          TabOrder = 6
        end
      end
    end
    object SpeedTab: TTabSheet
      Caption = 'Speed'
      ImageIndex = 2
      object Panel2: TPanel
        Left = -4
        Top = -4
        Width = 1101
        Height = 587
        Color = clCream
        ParentBackground = False
        TabOrder = 0
        object SpeedFLabel: TLabel
          Left = 8
          Top = 559
          Width = 809
          Height = 19
          Caption = 'Speed spectra file:'
        end
        object SpeedChart: TChart
          Left = 8
          Top = 7
          Width = 809
          Height = 546
          Title.Font.Height = -16
          Title.Font.Name = 'Terminal'
          Title.Text.Strings = (
            'Speed distribution')
          BottomAxis.Title.Caption = 'Speed, m/s'
          BottomAxis.Title.Font.Color = clBlue
          BottomAxis.Title.Font.Height = -13
          BottomAxis.Title.Font.Name = 'Terminal'
          LeftAxis.LabelsFormat.Font.Color = clBlue
          LeftAxis.LabelsFormat.Font.Height = -13
          LeftAxis.LabelsFormat.Font.Name = 'Terminal'
          LeftAxis.Title.Caption = 'Number of particles'
          LeftAxis.Title.Font.Color = clBlue
          LeftAxis.Title.Font.Height = -13
          LeftAxis.Title.Font.Name = 'Terminal'
          View3D = False
          TabOrder = 0
          DefaultCanvas = 'TGDIPlusCanvas'
          ColorPaletteIndex = 13
        end
        object SpeedSaveButton: TButton
          Left = 823
          Top = 504
          Width = 266
          Height = 49
          Caption = 'Save speed spectra'
          TabOrder = 1
        end
      end
    end
    object ChargeTab: TTabSheet
      Caption = 'Charge'
      ImageIndex = 3
      object Panel1: TPanel
        Left = -4
        Top = -4
        Width = 1101
        Height = 587
        Color = clCream
        ParentBackground = False
        TabOrder = 0
        object ChargeFLabel: TLabel
          Left = 8
          Top = 559
          Width = 809
          Height = 19
          Caption = 'Charge spectra file:'
        end
        object ChargeChart: TChart
          Left = 8
          Top = 7
          Width = 809
          Height = 546
          Title.Font.Height = -16
          Title.Font.Name = 'Terminal'
          Title.Text.Strings = (
            'Charge distribution')
          BottomAxis.Title.Caption = 'Charge, Q'
          BottomAxis.Title.Font.Color = clBlue
          BottomAxis.Title.Font.Height = -13
          BottomAxis.Title.Font.Name = 'Terminal'
          LeftAxis.LabelsFormat.Font.Color = clBlue
          LeftAxis.LabelsFormat.Font.Height = -13
          LeftAxis.LabelsFormat.Font.Name = 'Terminal'
          LeftAxis.Title.Caption = 'Number of particles'
          LeftAxis.Title.Font.Color = clBlue
          LeftAxis.Title.Font.Height = -13
          LeftAxis.Title.Font.Name = 'Terminal'
          View3D = False
          TabOrder = 0
          DefaultCanvas = 'TGDIPlusCanvas'
          ColorPaletteIndex = 13
        end
        object ChargeSaveButton: TButton
          Left = 823
          Top = 504
          Width = 266
          Height = 49
          Caption = 'Save charge spectra'
          TabOrder = 1
        end
      end
    end
  end
  object Exit_Button: TButton
    Left = 984
    Top = 623
    Width = 123
    Height = 44
    Caption = 'EXIT'
    TabOrder = 1
    OnClick = Exit_ButtonClick
  end
  object AutoTextFileDialog: TOpenTextFileDialog
    Left = 984
    Top = 2
  end
  object HandTextFileDialog: TOpenTextFileDialog
    Left = 873
    Top = 2
  end
end
