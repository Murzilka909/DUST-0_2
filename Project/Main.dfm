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
  object FNameLabel: TLabel
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
    ActivePage = AutoTab
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
        object AutoLabel: TLabel
          Left = 583
          Top = 88
          Width = 64
          Height = 19
          Caption = 'AutoLabel'
        end
        object AutoResLabel: TLabel
          Left = 583
          Top = 200
          Width = 64
          Height = 19
          Caption = 'AutoLabel'
        end
        object AutoListBox: TListBox
          Left = 8
          Top = 20
          Width = 561
          Height = 557
          TabStop = False
          ItemHeight = 19
          TabOrder = 0
          TabWidth = 15
        end
        object AutoSpectraButton: TButton
          Left = 583
          Top = 528
          Width = 506
          Height = 49
          Caption = 'Get spectra'
          Enabled = False
          TabOrder = 1
          OnClick = AutoSpectraButtonClick
        end
        object AutoFNameButton: TButton
          Left = 583
          Top = 20
          Width = 506
          Height = 49
          Caption = 'First file selection'
          TabOrder = 2
          OnClick = AutoFNameButtonClick
        end
        object AutoClearButton: TButton
          Left = 583
          Top = 464
          Width = 506
          Height = 51
          Caption = 'Clear all'
          TabOrder = 3
          OnClick = AutoClearButtonClick
        end
        object StartButton: TButton
          Left = 583
          Top = 128
          Width = 506
          Height = 57
          Caption = 'StartButton'
          Enabled = False
          TabOrder = 4
          OnClick = StartButtonClick
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
          Left = 535
          Top = 447
          Width = 52
          Height = 19
          Caption = 'File data'
        end
        object HandListBox: TListBox
          Left = 6
          Top = 16
          Width = 339
          Height = 561
          TabStop = False
          Font.Charset = RUSSIAN_CHARSET
          Font.Color = clWindowText
          Font.Height = -13
          Font.Name = 'Times New Roman'
          Font.Style = []
          ItemHeight = 15
          ParentFont = False
          TabOrder = 0
          TabWidth = 15
        end
        object HandFNameButton: TButton
          Left = 351
          Top = 528
          Width = 162
          Height = 49
          Caption = 'File selection'
          TabOrder = 1
          OnClick = HandFNameButtonClick
        end
        object HandCheckBox: TCheckBox
          Left = 351
          Top = 487
          Width = 186
          Height = 17
          Caption = 'Files one at a time'
          TabOrder = 2
        end
        object YesButton: TButton
          Left = 912
          Top = 503
          Width = 180
          Height = 75
          Caption = 'Record speed and charge'
          Enabled = False
          TabOrder = 3
          OnClick = YesButtonClick
        end
        object NoButton: TButton
          Left = 726
          Top = 503
          Width = 180
          Height = 75
          Caption = 'Ignore chart'
          Enabled = False
          TabOrder = 4
          OnClick = NoButtonClick
        end
        object HandSpectraButton: TButton
          Left = 535
          Top = 528
          Width = 170
          Height = 49
          Caption = 'Get spectra'
          Enabled = False
          TabOrder = 5
          OnClick = HandSpectraButtonClick
        end
        object HandChart: TChart
          Left = 351
          Top = 16
          Width = 741
          Height = 425
          Title.Font.Height = -16
          Title.Font.Name = 'Terminal'
          Title.Text.Strings = (
            'Oscilloscope data')
          BottomAxis.Title.Caption = 'ms'
          BottomAxis.Title.Font.Color = clBlue
          BottomAxis.Title.Font.Height = -13
          BottomAxis.Title.Font.Name = 'Terminal'
          BottomAxis.Title.Color = clBlue
          LeftAxis.Title.Caption = 'mV'
          LeftAxis.Title.Font.Color = clBlue
          LeftAxis.Title.Font.Height = -13
          LeftAxis.Title.Font.Name = 'Terminal'
          View3D = False
          TabOrder = 6
          DefaultCanvas = 'TGDIPlusCanvas'
          ColorPaletteIndex = 13
          object Series1: TLineSeries
            Title = 'A'
            Brush.BackColor = clDefault
            LinePen.Width = 2
            Pointer.InflateMargins = True
            Pointer.Style = psRectangle
            XValues.Name = 'X'
            XValues.Order = loAscending
            YValues.Name = 'Y'
            YValues.Order = loNone
          end
          object Series2: TLineSeries
            Title = 'B'
            Brush.BackColor = clDefault
            LinePen.Width = 2
            Pointer.InflateMargins = True
            Pointer.Style = psRectangle
            XValues.Name = 'X'
            XValues.Order = loAscending
            YValues.Name = 'Y'
            YValues.Order = loNone
          end
        end
        object HandClearButton: TButton
          Left = 912
          Top = 445
          Width = 180
          Height = 36
          Caption = 'Clear all'
          TabOrder = 7
          OnClick = HandClearButtonClick
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
          Width = 111
          Height = 19
          Caption = 'Speed spectra file:'
        end
        object SpeedChart: TChart
          Left = 8
          Top = 7
          Width = 809
          Height = 546
          Legend.Visible = False
          Title.Font.Height = -16
          Title.Font.Name = 'Terminal'
          Title.Text.Strings = (
            'Speed distribution')
          BottomAxis.Automatic = False
          BottomAxis.AutomaticMaximum = False
          BottomAxis.Maximum = 24.000000000000000000
          BottomAxis.Title.Caption = 'Speed, m/s'
          BottomAxis.Title.Font.Color = clBlue
          BottomAxis.Title.Font.Height = -13
          BottomAxis.Title.Font.Name = 'Terminal'
          LeftAxis.Automatic = False
          LeftAxis.AutomaticMinimum = False
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
          object Series3: TLineSeries
            SeriesColor = clBlue
            Title = 'SpectraVSeries'
            Brush.BackColor = clDefault
            LinePen.Width = 6
            Pointer.InflateMargins = True
            Pointer.Style = psRectangle
            XValues.Name = 'X'
            XValues.Order = loAscending
            YValues.Name = 'Y'
            YValues.Order = loNone
          end
        end
        object SpeedSaveButton: TButton
          Left = 823
          Top = 504
          Width = 266
          Height = 49
          Caption = 'Save speed spectra'
          TabOrder = 1
        end
        object SpeedListBox: TListBox
          Left = 823
          Top = 7
          Width = 266
          Height = 426
          ItemHeight = 19
          TabOrder = 2
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
          Width = 116
          Height = 19
          Caption = 'Charge spectra file:'
        end
        object ChargeChart: TChart
          Left = 8
          Top = 7
          Width = 809
          Height = 546
          Legend.Visible = False
          Title.Font.Height = -16
          Title.Font.Name = 'Terminal'
          Title.Text.Strings = (
            'Charge distribution')
          BottomAxis.Automatic = False
          BottomAxis.AutomaticMaximum = False
          BottomAxis.Maximum = 24.000000000000000000
          BottomAxis.Title.Caption = 'Charge, Q'
          BottomAxis.Title.Font.Color = clBlue
          BottomAxis.Title.Font.Height = -13
          BottomAxis.Title.Font.Name = 'Terminal'
          LeftAxis.Automatic = False
          LeftAxis.AutomaticMinimum = False
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
          object Series4: TLineSeries
            SeriesColor = clBlue
            Title = 'SpectraChargeSeries'
            Brush.BackColor = clDefault
            LinePen.Width = 6
            Pointer.InflateMargins = True
            Pointer.Style = psRectangle
            XValues.Name = 'X'
            XValues.Order = loAscending
            YValues.Name = 'Y'
            YValues.Order = loNone
          end
        end
        object ChargeSaveButton: TButton
          Left = 823
          Top = 504
          Width = 266
          Height = 49
          Caption = 'Save charge spectra'
          TabOrder = 1
        end
        object ChargeListBox: TListBox
          Left = 823
          Top = 7
          Width = 266
          Height = 402
          ItemHeight = 19
          TabOrder = 2
        end
      end
    end
    object SettingsTab: TTabSheet
      Caption = 'Settings'
      ImageIndex = 4
      object Panel5: TPanel
        Left = -4
        Top = -4
        Width = 1101
        Height = 587
        Color = clCream
        UseDockManager = False
        ParentBackground = False
        TabOrder = 0
        object SetValButton: TButton
          Left = 4
          Top = 520
          Width = 173
          Height = 57
          Caption = 'Set values'
          TabOrder = 0
          OnClick = SetValButtonClick
        end
        object GroupBox1: TGroupBox
          Left = 192
          Top = 48
          Width = 353
          Height = 513
          Caption = 'Common '
          Font.Charset = RUSSIAN_CHARSET
          Font.Color = clWindowText
          Font.Height = -16
          Font.Name = 'Times New Roman'
          Font.Style = []
          ParentFont = False
          TabOrder = 1
          object StaticText15: TStaticText
            Left = 202
            Top = 340
            Width = 79
            Height = 23
            Caption = '10^(-16) '#1057';'
            TabOrder = 0
          end
          object MaxChargeEdit: TEdit
            Left = 151
            Top = 336
            Width = 50
            Height = 27
            TabOrder = 1
            Text = '5000'
          end
          object StaticText14: TStaticText
            Left = 70
            Top = 340
            Width = 79
            Height = 23
            Caption = 'Max charge:'
            TabOrder = 2
          end
          object StaticText12: TStaticText
            Left = 70
            Top = 292
            Width = 75
            Height = 23
            Caption = 'Max speed:'
            TabOrder = 3
          end
          object MaxSpeedEdit: TEdit
            Left = 151
            Top = 288
            Width = 50
            Height = 27
            TabOrder = 4
            Text = '5000'
          end
          object StaticText13: TStaticText
            Left = 207
            Top = 292
            Width = 29
            Height = 23
            Caption = 'm/s;'
            TabOrder = 5
          end
          object StaticText11: TStaticText
            Left = 202
            Top = 242
            Width = 79
            Height = 23
            Caption = '10^(-16) '#1057';'
            TabOrder = 6
          end
          object DistrStepQEdit: TEdit
            Left = 151
            Top = 238
            Width = 50
            Height = 27
            TabOrder = 7
            Text = '100'
          end
          object StaticText9: TStaticText
            Left = 131
            Top = 242
            Width = 16
            Height = 23
            Caption = 'Q'
            TabOrder = 8
          end
          object DistrStepVEdit: TEdit
            Left = 151
            Top = 190
            Width = 50
            Height = 27
            TabOrder = 9
            Text = '100'
          end
          object StaticText10: TStaticText
            Left = 207
            Top = 194
            Width = 29
            Height = 23
            Caption = 'm/s;'
            TabOrder = 10
          end
          object StaticText8: TStaticText
            Left = 130
            Top = 194
            Width = 15
            Height = 23
            Caption = 'V'
            TabOrder = 11
          end
          object StaticText7: TStaticText
            Left = 32
            Top = 194
            Width = 88
            Height = 23
            Caption = 'Step on distr.:'
            TabOrder = 12
          end
          object StaticText5: TStaticText
            Left = 131
            Top = 148
            Width = 14
            Height = 23
            Caption = 'B'
            TabOrder = 13
          end
          object GainBEdit: TEdit
            Left = 151
            Top = 144
            Width = 50
            Height = 27
            TabOrder = 14
            Text = '2.6'
          end
          object StaticText6: TStaticText
            Left = 187
            Top = 121
            Width = 94
            Height = 23
            Caption = '10^(-13) '#1057'/V;'
            TabOrder = 15
          end
          object GainAEdit: TEdit
            Left = 151
            Top = 96
            Width = 50
            Height = 27
            TabOrder = 16
            Text = '1'
          end
          object StaticText3: TStaticText
            Left = 32
            Top = 100
            Width = 80
            Height = 23
            Caption = 'Gain factors:'
            TabOrder = 17
          end
          object StaticText4: TStaticText
            Left = 130
            Top = 100
            Width = 15
            Height = 23
            Caption = 'A'
            TabOrder = 18
          end
          object StaticText1: TStaticText
            Left = 32
            Top = 52
            Width = 97
            Height = 23
            Caption = 'Limit of voltage'
            TabOrder = 19
          end
          object LimVEdit: TEdit
            Left = 151
            Top = 48
            Width = 50
            Height = 27
            TabOrder = 20
            Text = '5000'
          end
          object StaticText2: TStaticText
            Left = 207
            Top = 52
            Width = 30
            Height = 23
            Caption = 'mV;'
            TabOrder = 21
          end
        end
        object GroupBox2: TGroupBox
          Left = 592
          Top = 48
          Width = 457
          Height = 513
          Caption = 'Auto mode'
          Font.Charset = RUSSIAN_CHARSET
          Font.Color = clWindowText
          Font.Height = -16
          Font.Name = 'Times New Roman'
          Font.Style = []
          ParentFont = False
          TabOrder = 2
          object GroupBox3: TGroupBox
            Left = 3
            Top = 98
            Width = 347
            Height = 141
            Caption = 'Two channels'
            TabOrder = 0
            object StaticText18: TStaticText
              Left = 16
              Top = 28
              Width = 110
              Height = 23
              Caption = 'Delta speed A-B:'
              TabOrder = 0
            end
            object DeltaSpeedABEdit: TEdit
              Left = 145
              Top = 24
              Width = 50
              Height = 27
              TabOrder = 1
              Text = '0.2'
            end
            object StaticText19: TStaticText
              Left = 201
              Top = 26
              Width = 8
              Height = 23
              Caption = ';'
              TabOrder = 2
            end
            object StaticText20: TStaticText
              Left = 16
              Top = 68
              Width = 124
              Height = 23
              Caption = 'Delta speed comm.:'
              TabOrder = 3
            end
            object DeltaSpeedCommEdit: TEdit
              Left = 145
              Top = 64
              Width = 50
              Height = 27
              TabOrder = 4
              Text = '0.4'
            end
            object StaticText21: TStaticText
              Left = 201
              Top = 66
              Width = 8
              Height = 23
              Caption = ';'
              TabOrder = 5
            end
            object DeltaChargeABEdit: TEdit
              Left = 145
              Top = 104
              Width = 50
              Height = 27
              TabOrder = 6
              Text = '0.2'
            end
            object StaticText22: TStaticText
              Left = 16
              Top = 108
              Width = 114
              Height = 23
              Caption = 'Delta charge A-B:'
              TabOrder = 7
            end
            object StaticText23: TStaticText
              Left = 201
              Top = 106
              Width = 8
              Height = 23
              Caption = ';'
              TabOrder = 8
            end
          end
          object GroupBox4: TGroupBox
            Left = 3
            Top = 245
            Width = 430
            Height = 252
            Caption = 'One channel'
            TabOrder = 1
            object StaticText27: TStaticText
              Left = 16
              Top = 36
              Width = 141
              Height = 23
              Caption = 'Max delta integral 1-2:'
              TabOrder = 0
            end
            object StaticText29: TStaticText
              Left = 16
              Top = 116
              Width = 131
              Height = 23
              Caption = 'Max delta ampl. 1-2:'
              TabOrder = 1
            end
            object StaticText28: TStaticText
              Left = 16
              Top = 76
              Width = 137
              Height = 23
              Caption = 'Min delta integral 2-3:'
              TabOrder = 2
            end
            object StaticText24: TStaticText
              Left = 16
              Top = 156
              Width = 127
              Height = 23
              Caption = 'Min delta ampl. 2-3:'
              TabOrder = 3
            end
            object StaticText25: TStaticText
              Left = 16
              Top = 196
              Width = 130
              Height = 23
              Caption = 'Baseline points num.:'
              TabOrder = 4
            end
            object DeltaI12Edit: TEdit
              Left = 163
              Top = 31
              Width = 50
              Height = 27
              TabOrder = 5
              Text = '0.4'
            end
            object DeltaI23Edit: TEdit
              Left = 163
              Top = 72
              Width = 50
              Height = 27
              TabOrder = 6
              Text = '0.8'
            end
            object DeltaA12Edit: TEdit
              Left = 163
              Top = 112
              Width = 50
              Height = 27
              TabOrder = 7
              Text = '0.4'
            end
            object StaticText26: TStaticText
              Left = 219
              Top = 114
              Width = 8
              Height = 23
              Caption = ';'
              TabOrder = 8
            end
            object StaticText30: TStaticText
              Left = 219
              Top = 74
              Width = 8
              Height = 23
              Caption = ';'
              TabOrder = 9
            end
            object StaticText31: TStaticText
              Left = 219
              Top = 34
              Width = 8
              Height = 23
              Caption = ';'
              TabOrder = 10
            end
            object BaseNumEdit: TEdit
              Left = 163
              Top = 192
              Width = 50
              Height = 27
              TabOrder = 11
              Text = '100'
            end
            object StaticText32: TStaticText
              Left = 219
              Top = 194
              Width = 8
              Height = 23
              Caption = ';'
              TabOrder = 12
            end
            object StaticText33: TStaticText
              Left = 219
              Top = 154
              Width = 8
              Height = 23
              Caption = ';'
              TabOrder = 13
            end
            object DeltaA23Edit: TEdit
              Left = 163
              Top = 152
              Width = 50
              Height = 27
              TabOrder = 14
              Text = '0.8'
            end
            object StaticText34: TStaticText
              Left = 288
              Top = 196
              Width = 38
              Height = 23
              Caption = 'Coef.'
              TabOrder = 15
            end
            object CoefEdit: TEdit
              Left = 332
              Top = 191
              Width = 50
              Height = 27
              TabOrder = 16
              Text = '1.35'
            end
            object StaticText35: TStaticText
              Left = 388
              Top = 194
              Width = 8
              Height = 23
              Caption = ';'
              TabOrder = 17
            end
          end
          object StaticText16: TStaticText
            Left = 16
            Top = 36
            Width = 137
            Height = 23
            Caption = 'Range of file numbers:'
            TabOrder = 2
          end
          object MinFNumEdit: TEdit
            Left = 15
            Top = 65
            Width = 50
            Height = 27
            TabOrder = 3
            Text = '2'
          end
          object StaticText17: TStaticText
            Left = 71
            Top = 69
            Width = 10
            Height = 23
            Caption = '-'
            TabOrder = 4
          end
          object MaxFNumEdit: TEdit
            Left = 87
            Top = 65
            Width = 50
            Height = 27
            TabOrder = 5
            Text = '100'
          end
          object FBaseCheckBox: TCheckBox
            Left = 176
            Top = 36
            Width = 209
            Height = 17
            Caption = 'process the null file'
            TabOrder = 6
          end
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
