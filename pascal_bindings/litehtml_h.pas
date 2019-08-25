unit litehtml_h;

{$IfDef FPC}
  {$mode objfpc}{$H+}
{$EndIf}

interface

uses
  Classes, SysUtils, mutils;

type
  IDocument = interface;

  {$ScopedEnums On}
    TRenderType = (render_all, render_no_fixed, render_fixed_only);
    TFontStyle = (Normal, Italic);
    TBackgroundAttachment = (Scroll, Fixed);
    TBackgroundRepeat = (All, X, Y, NoRepeat);
  	TBorderStyle = (none, hidden, dotted, dashed, solid, double, groove, ridge, inset, outset);
  {$ScopedEnums Off}

  TPosition = record
		x: Integer;
		y: Integer;
		width: Integer;
		height: Integer;
  end;
  PPosition = ^TPosition;

  TSize = record
    width : Integer;
    height: Integer;
  end;

	TFontMetrics = record
    height: Integer;
    ascent: Integer;
    descent: Integer;
    x_height: Integer;
    draw_spaces: Boolean;
  end;
  PFontMetrics = ^TFontMetrics;

	TWebColor = packed record
		blue : Byte;
		green: Byte;
		red  : Byte;
		alpha: Byte;
  end;

  TBorderRadiuses = record
    TopLeftX: Integer;
    TopLeftY: Integer;
    TopRightX: Integer;
    TopRightY: Integer;
    BottomRightX: Integer;
    BottomRightY: Integer;
    BottomLeftX: Integer;
    BottomLeftY: Integer;
  end;

	TBorder = record
    Width: Integer;
    Style: TBorderStyle;
    Color: TWebColor;
  end;

  TBorders = record
    Left  : TBorder;
    Top   : TBorder;
    Right : TBorder;
    Bottom: TBorder;
    Radius: TBorderRadiuses;
  end;

  IListMarker = interface
  ['{BE8C16FF-7FD6-4F38-9D8F-847A098BD072}']
      function Image(): PAnsiChar; stdcall;
      function BaseUrl(): PAnsiChar; stdcall;
      function Color(): TWebColor; stdcall;
      function Position(): PPosition; stdcall;
  end;

  IBackgroundPaint = interface
  ['{C1730CBD-6772-4A74-8078-7102A2EADB83}']
      function Image(): PAnsiChar; stdcall;
      function BaseUrl(): PAnsiChar; stdcall;
      function Attachment(): TBackgroundAttachment; stdcall;
      function BkRepeat(): TBackgroundRepeat; stdcall;
      function Color(): TWebColor; stdcall;
      function ClipBox(): PPosition; stdcall;
      function OriginBox(): PPosition; stdcall;
      function BorderBox(): PPosition; stdcall;
      function BorderRadius(): PPosition; stdcall;
      function ImageSize(): TSize; stdcall;
      function PositionX(): Integer; stdcall;
      function PositionY(): Integer; stdcall;
      function IsRoot(): Boolean; stdcall;
  end;

  IDocumentContainer = interface
  ['{5B906FFC-624F-41DF-9CCB-46FEC73A3F4F}']
      function CreateFont(const AName: PAnsiChar; ASize, AWeight: Integer; AItalic: TFontStyle; ADecoration: Cardinal; AMetrics: PFontMetrics): Pointer; stdcall;
      procedure DeleteFont(hFont: Pointer); stdcall;

      function TextWidth(const AText: PAnsiChar; hFont: Pointer): Integer; stdcall;
      procedure DrawText(const AText: PAnsiChar; hFont: Pointer; AColor: TWebColor; const APosition: TPosition); stdcall;
      function PtToPx(APt: Integer): Integer; stdcall;
      function GetDefaultFontSize(): Integer; stdcall;
      function GetDefaultFontName(): PAnsiChar; stdcall;
      procedure DrawListMarker(const AListMarker: IListMarker); stdcall;
      procedure LoadImage(const ASrc, ABaseUrl: PAnsiChar; ARedrawOnReady: Boolean); stdcall;
      procedure GetImageSize(const ASrc, ABaseUrl: PAnsiChar; out ASize: TSize); stdcall;
      procedure DrawBackground(const APaintInfo: IBackgroundPaint); stdcall;
      procedure DrawBorders(const ABorders: TBorders; const ADrawPos: TPosition; ARoot: Boolean); stdcall;

      procedure SetCaption(const ACaption: PAnsiChar); stdcall;
      procedure SetBaseUrl(const ABaseUrl: PAnsiChar); stdcall;

      procedure Link(const ADoc: IDocument); stdcall;
      procedure OnAnchorClick(const AUrl: PAnsiChar); stdcall;
      procedure SetCursor(const ACursor: PAnsiChar); stdcall;
	    //virtual	void				TransformText(litehtml::tstring& text, litehtml::text_transform tt) = 0;
	    //virtual void				ImportCss(litehtml::tstring& text, const litehtml::tstring& url, litehtml::tstring& baseurl) = 0;
      procedure SetClip(const APosition: TPosition; const ABrdRadius: TBorderRadiuses; valid_x, valid_y: Boolean); stdcall;
      procedure DelClip(); stdcall;
	    procedure GetClientRect(out AClient: TPosition); stdcall;
	    //virtual std::shared_ptr<litehtml::element>	create_element(const litehtml::tchar_t *tag_name,
	    //		const litehtml::string_map &attributes,
	    //const std::shared_ptr<litehtml::document> &doc) = 0;

	    //virtual void				GetMediaFeatures(litehtml::media_features& media) const = 0;
	    //virtual void				GetLanguage(litehtml::tstring& language, litehtml::tstring & culture) const = 0;
	    //virtual litehtml::tstring	ResolveColor(const litehtml::tstring& color) const  { return litehtml::tstring(); }
  end;

  IDocument = interface
  ['{76A40C63-CA8B-497B-AAF0-1B4A1BDFC21E}']
      function Render(max_width: Integer; rt: TRenderType = TRenderType.render_all): Integer; stdcall;
      procedure Draw(x, y: Integer; const clip: TPosition); stdcall;
      function Width(): Integer; stdcall;
      function Height(): Integer; stdcall;
      procedure AddStylesheet(str, baseurl, media: PAnsiChar); stdcall;
      function OnMouseOver(x, y: Integer; client_x, client_y: Integer): Boolean; stdcall;
      function OnLButtonDown(x, y: Integer; client_x, client_y: Integer): Boolean; stdcall;
      function OnLButtonUp(x, y: Integer; client_x, client_y: Integer): Boolean; stdcall;
      function OnMouseLeave(): Boolean; stdcall;
  end;

  ILightBrowser = interface
  ['{F3A82827-CBA0-44A2-B672-CAE270A05460}']
      function CreateDocumentFromUTF8(const text: PAnsiChar; const container: IDocumentContainer): IDocument; safecall;
  end;

function Create_ILightBrowser: ILightBrowser; cdecl; external 'litehtml64.dll';

implementation

end.

