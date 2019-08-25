// litehtml_dll.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "litehtml_dll.h"

namespace litehtml {

	DocumentContainerAdapter::DocumentContainerAdapter(IDocumentContainer * doc_container_intf, IDocument* doc) : m_docintf(doc_container_intf), m_doc(doc)
	{
	}
	litehtml::uint_ptr DocumentContainerAdapter::create_font(const litehtml::tchar_t * faceName, int size, int weight, litehtml::font_style italic, unsigned int decoration, litehtml::font_metrics * fm)
	{
		return m_docintf->CreateFont(faceName, size, weight, italic, decoration, fm);;
	}
	void DocumentContainerAdapter::delete_font(litehtml::uint_ptr hFont)
	{
		m_docintf->DeleteFont(hFont);
	}
	int DocumentContainerAdapter::text_width(const litehtml::tchar_t * text, litehtml::uint_ptr hFont)
	{
		return m_docintf->TextWidth(text, hFont);
	}
	void DocumentContainerAdapter::draw_text(litehtml::uint_ptr hdc, const litehtml::tchar_t * text, litehtml::uint_ptr hFont, litehtml::web_color color, const litehtml::position & pos)
	{
		m_docintf->DrawText(text, hFont, color, pos);
	}
	int DocumentContainerAdapter::pt_to_px(int pt)
	{
		return m_docintf->PtToPx(pt);
	}
	int DocumentContainerAdapter::get_default_font_size() const
	{
		return m_docintf->GetDefaultFontSize();
	}
	const litehtml::tchar_t * DocumentContainerAdapter::get_default_font_name() const
	{
		return m_docintf->GetDefaultFontName();
	}
	void DocumentContainerAdapter::draw_list_marker(litehtml::uint_ptr hdc, const litehtml::list_marker & marker)
	{
        Microsoft::WRL::ComPtr<IListMarker> obj = Microsoft::WRL::Make<ListMarkerAdapter>(marker);
		m_docintf->DrawListMarker(obj.Get());
	}
	void DocumentContainerAdapter::load_image(const litehtml::tchar_t * src, const litehtml::tchar_t * baseurl, bool redraw_on_ready)
	{
		m_docintf->LoadImage(src, baseurl, redraw_on_ready);
	}
	void DocumentContainerAdapter::get_image_size(const litehtml::tchar_t * src, const litehtml::tchar_t * baseurl, litehtml::size & sz)
	{
		return m_docintf->GetImageSize(src, baseurl, sz);
	}
	void DocumentContainerAdapter::draw_background(litehtml::uint_ptr hdc, const litehtml::background_paint & bg)
	{
        Microsoft::WRL::ComPtr<IBackgroundPaint> obj = Microsoft::WRL::Make<BackgroundPaintAdapter>(bg);
		m_docintf->DrawBackground(obj.Get());
	}
	void DocumentContainerAdapter::draw_borders(litehtml::uint_ptr hdc, const litehtml::borders & borders, const litehtml::position & draw_pos, bool root)
	{
		m_docintf->DrawBorders(borders, draw_pos, root);
	}
	void DocumentContainerAdapter::set_caption(const litehtml::tchar_t * caption)
	{
		m_docintf->SetCaption(caption);
	}
	void DocumentContainerAdapter::set_base_url(const litehtml::tchar_t * base_url)
	{
		m_docintf->SetBaseUrl(base_url);
	}
	void DocumentContainerAdapter::link(const std::shared_ptr<litehtml::document>& doc, const litehtml::element::ptr & el)
	{
		m_docintf->Link(m_doc);
	}
	void DocumentContainerAdapter::on_anchor_click(const litehtml::tchar_t * url, const litehtml::element::ptr & el)
	{
		m_docintf->OnAnchorClick(url);
	}
	void DocumentContainerAdapter::set_cursor(const litehtml::tchar_t * cursor)
	{
		m_docintf->SetCursor(cursor);
	}
	void DocumentContainerAdapter::transform_text(litehtml::tstring & text, litehtml::text_transform tt)
	{
		//todo
	}
	void DocumentContainerAdapter::import_css(litehtml::tstring & text, const litehtml::tstring & url, litehtml::tstring & baseurl)
	{
		//todo
	}
	void DocumentContainerAdapter::set_clip(const litehtml::position & pos, const litehtml::border_radiuses & bdr_radius, bool valid_x, bool valid_y)
	{
		m_docintf->SetClip(pos, bdr_radius, valid_x, valid_y);
	}
	void DocumentContainerAdapter::del_clip()
	{
		m_docintf->DelClip();
	}
	void DocumentContainerAdapter::get_client_rect(litehtml::position & client) const
	{
		m_docintf->GetClientRect(client);
	}
	std::shared_ptr<litehtml::element> DocumentContainerAdapter::create_element(const litehtml::tchar_t * tag_name, const litehtml::string_map & attributes, const std::shared_ptr<litehtml::document>& doc)
	{
		return std::shared_ptr<litehtml::element>();
	}
	void DocumentContainerAdapter::get_media_features(litehtml::media_features & media) const
	{
		//todo
	}
	void DocumentContainerAdapter::get_language(litehtml::tstring & language, litehtml::tstring & culture) const
	{
		//todo
	}
	int DocumentAdapter::Render(int max_width, litehtml::render_type rt)
	{
		return m_doc->render(max_width, rt);
	}
	void DocumentAdapter::Draw(int x, int y, const litehtml::position * clip)
	{
		m_doc->draw(0, x, y, clip);
	}
	int DocumentAdapter::Width() const
	{
		return m_doc->width();
	}
	int DocumentAdapter::Height() const
	{
		return m_doc->height();
	}
	void DocumentAdapter::AddStylesheet(const tchar_t * str, const tchar_t * baseurl, const tchar_t * media)
	{
		m_doc->add_stylesheet(str, baseurl, media);
	}
	bool DocumentAdapter::OnMouseOver(int x, int y, int client_x, int client_y)
	{
		position::vector boxes;
		return m_doc->on_mouse_over(x, y, client_x, client_y, boxes);
	}
	bool DocumentAdapter::OnLButtonDown(int x, int y, int client_x, int client_y)
	{
		position::vector boxes;
		return m_doc->on_lbutton_down(x, y, client_x, client_y, boxes);
	}
	bool DocumentAdapter::OnLButtonUp(int x, int y, int client_x, int client_y)
	{
		position::vector boxes;
		return m_doc->on_lbutton_up(x, y, client_x, client_y, boxes);
	}
	bool DocumentAdapter::OnMouseLeave()
	{
		position::vector boxes;
		return m_doc->on_mouse_leave(boxes);
	}
	HRESULT LightBrowser::CreateDocumentFromUTF8(const char * text, IDocumentContainer * container, IDocument ** result)
	{
		if (*result) {
			(*result)->Release();
			result = nullptr;
		}
		Microsoft::WRL::ComPtr<IDocument> doc = Microsoft::WRL::Make<DocumentAdapter>(text, container, &m_ctx);
		(*result) = doc.Get();
		(*result)->AddRef();
		return S_OK;
	}

	HRESULT Create_ILightBrowser(ILightBrowser** result)
	{
		Microsoft::WRL::ComPtr<ILightBrowser> obj = Microsoft::WRL::Make<LightBrowser>();
		(*result) = obj.Get();
		(*result)->AddRef();
		return S_OK;
	}
    const tchar_t * __stdcall ListMarkerAdapter::Image()
    {
        return m_data.image.c_str();
    }
    const tchar_t * __stdcall ListMarkerAdapter::BaseUrl()
    {
        return m_data.baseurl;
    }
    litehtml::web_color __stdcall ListMarkerAdapter::Color()
    {
        return m_data.color;
    }
    const litehtml::position & __stdcall ListMarkerAdapter::Position()
    {
        return m_data.pos;
    }
    ListMarkerAdapter::ListMarkerAdapter(const litehtml::list_marker& data) : m_data(data)
    {
    }
    const tchar_t * __stdcall BackgroundPaintAdapter::Image()
    {
        return m_data.image.c_str();
    }
    const tchar_t * __stdcall BackgroundPaintAdapter::BaseUrl()
    {
        return m_data.baseurl.c_str();
    }
    background_attachment __stdcall BackgroundPaintAdapter::Attachment()
    {
        return m_data.attachment;
    }
    background_repeat __stdcall BackgroundPaintAdapter::Repeat()
    {
        return m_data.repeat;
    }
    web_color __stdcall BackgroundPaintAdapter::Color()
    {
        return m_data.color;
    }
    position * __stdcall BackgroundPaintAdapter::ClipBox()
    {
        return &m_data.clip_box;
    }
    position * __stdcall BackgroundPaintAdapter::OriginBox()
    {
        return &m_data.origin_box;
    }
    position * __stdcall BackgroundPaintAdapter::BorderBox()
    {
        return &m_data.border_box;
    }
    border_radiuses * __stdcall BackgroundPaintAdapter::BorderRadius()
    {
        return &m_data.border_radius;
    }
    size __stdcall BackgroundPaintAdapter::ImageSize()
    {
        return m_data.image_size;
    }
    int __stdcall BackgroundPaintAdapter::PositionX()
    {
        return m_data.position_x;
    }
    int __stdcall BackgroundPaintAdapter::PositionY()
    {
        return m_data.position_y;
    }
    bool __stdcall BackgroundPaintAdapter::IsRoot()
    {
        return m_data.is_root;
    }
    BackgroundPaintAdapter::BackgroundPaintAdapter(const background_paint & data) : m_data(data)
    {
    }
}

