#pragma once

#include <memory>
#include <wrl.h>
#include "..\html.h"
#include "..\document.h"

namespace litehtml {

	interface IDocument;

	interface DECLSPEC_UUID("5B906FFC-624F-41DF-9CCB-46FEC73A3F4F")
	IDocumentContainer : public IUnknown{
public:
	virtual litehtml::uint_ptr	CreateFont(const litehtml::tchar_t* faceName, int size, int weight, litehtml::font_style italic, unsigned int decoration, litehtml::font_metrics* fm) = 0;
	virtual void				DeleteFont(litehtml::uint_ptr hFont) = 0;

	virtual int					TextWidth(const litehtml::tchar_t* text, litehtml::uint_ptr hFont) = 0;
	virtual void				DrawText(const litehtml::tchar_t* text, litehtml::uint_ptr hFont, litehtml::web_color color, const litehtml::position& pos) = 0;
	virtual int					PtToPx(int pt) = 0;
	virtual int					GetDefaultFontSize() const = 0;
	virtual const litehtml::tchar_t* GetDefaultFontName() const = 0;
	virtual void				DrawListMarker(const litehtml::list_marker& marker) = 0;
	virtual void				LoadImage(const litehtml::tchar_t* src, const litehtml::tchar_t* baseurl, bool redraw_on_ready) = 0;
	virtual void				GetImageSize(const litehtml::tchar_t* src, const litehtml::tchar_t* baseurl, litehtml::size& sz) = 0;
	virtual void				DrawBackground(const litehtml::background_paint& bg) = 0;
	virtual void				DrawBorders(const litehtml::borders& borders, const litehtml::position& draw_pos, bool root) = 0;

	virtual	void				SetCaption(const litehtml::tchar_t* caption) = 0;
	virtual	void				SetBaseUrl(const litehtml::tchar_t* base_url) = 0;
	virtual void				Link(IDocument* doc) = 0;//, const litehtml::element::ptr& el) = 0;
	virtual void				OnAnchorClick(const litehtml::tchar_t* url) = 0;// , const litehtml::element::ptr& el) = 0;
	virtual	void				SetCursor(const litehtml::tchar_t* cursor) = 0;
	//virtual	void				TransformText(litehtml::tstring& text, litehtml::text_transform tt) = 0;
	//virtual void				ImportCss(litehtml::tstring& text, const litehtml::tstring& url, litehtml::tstring& baseurl) = 0;
	virtual void				SetClip(const litehtml::position& pos, const litehtml::border_radiuses& bdr_radius, bool valid_x, bool valid_y) = 0;
	virtual void				DelClip() = 0;
	virtual void				GetClientRect(litehtml::position& client) const = 0;
	//virtual std::shared_ptr<litehtml::element>	create_element(const litehtml::tchar_t *tag_name,
	//		const litehtml::string_map &attributes,
	//const std::shared_ptr<litehtml::document> &doc) = 0;

	//virtual void				GetMediaFeatures(litehtml::media_features& media) const = 0;
	//virtual void				GetLanguage(litehtml::tstring& language, litehtml::tstring & culture) const = 0;
	//virtual litehtml::tstring	ResolveColor(const litehtml::tstring& color) const  { return litehtml::tstring(); }
	};

	interface DECLSPEC_UUID("76A40C63-CA8B-497B-AAF0-1B4A1BDFC21E")
	IDocument : public IUnknown{
public:
	virtual int	 Render(int max_width, litehtml::render_type rt = litehtml::render_all) = 0;
	virtual void Draw(int x, int y, const litehtml::position* clip) = 0;
	virtual int	 Width() const = 0;
	virtual int	 Height() const = 0;
	virtual void AddStylesheet(const tchar_t* str, const tchar_t* baseurl, const tchar_t* media) = 0;
	virtual bool OnMouseOver(int x, int y, int client_x, int client_y) = 0;
	virtual bool OnLButtonDown(int x, int y, int client_x, int client_y) = 0;
	virtual bool OnLButtonUp(int x, int y, int client_x, int client_y) = 0;
	virtual bool OnMouseLeave() = 0;
	};

	interface DECLSPEC_UUID("F3A82827-CBA0-44A2-B672-CAE270A05460")
	ILightBrowser : public IUnknown{
	virtual HRESULT STDMETHODCALLTYPE CreateDocumentFromUTF8(const char* text, IDocumentContainer* container, IDocument** result) = 0;
	};

	class DocumentContainerAdapter : public document_container {
	private:
		IDocument * m_doc;
		Microsoft::WRL::ComPtr<IDocumentContainer> m_docintf;
	public:
		litehtml::uint_ptr	create_font(const litehtml::tchar_t* faceName, int size, int weight, litehtml::font_style italic, unsigned int decoration, litehtml::font_metrics* fm) override;
		void				delete_font(litehtml::uint_ptr hFont) override;
		int					text_width(const litehtml::tchar_t* text, litehtml::uint_ptr hFont) override;
		void				draw_text(litehtml::uint_ptr hdc, const litehtml::tchar_t* text, litehtml::uint_ptr hFont, litehtml::web_color color, const litehtml::position& pos) override;
		int					pt_to_px(int pt) override;
		int					get_default_font_size() const override;
		const litehtml::tchar_t*	get_default_font_name() const override;
		void				draw_list_marker(litehtml::uint_ptr hdc, const litehtml::list_marker& marker) override;
		void				load_image(const litehtml::tchar_t* src, const litehtml::tchar_t* baseurl, bool redraw_on_ready) override;
		void				get_image_size(const litehtml::tchar_t* src, const litehtml::tchar_t* baseurl, litehtml::size& sz) override;
		void				draw_background(litehtml::uint_ptr hdc, const litehtml::background_paint& bg) override;
		void				draw_borders(litehtml::uint_ptr hdc, const litehtml::borders& borders, const litehtml::position& draw_pos, bool root) override;

		void				set_caption(const litehtml::tchar_t* caption) override;
		void				set_base_url(const litehtml::tchar_t* base_url) override;
		void				link(const std::shared_ptr<litehtml::document>& doc, const litehtml::element::ptr& el) override;
		void				on_anchor_click(const litehtml::tchar_t* url, const litehtml::element::ptr& el) override;
		void				set_cursor(const litehtml::tchar_t* cursor) override;
		void				transform_text(litehtml::tstring& text, litehtml::text_transform tt) override;
		void				import_css(litehtml::tstring& text, const litehtml::tstring& url, litehtml::tstring& baseurl) override;
		void				set_clip(const litehtml::position& pos, const litehtml::border_radiuses& bdr_radius, bool valid_x, bool valid_y) override;
		void				del_clip() override;
		void				get_client_rect(litehtml::position& client) const override;
		std::shared_ptr<litehtml::element>	create_element(const litehtml::tchar_t *tag_name,
			const litehtml::string_map &attributes,
			const std::shared_ptr<litehtml::document> &doc) override;

		void				get_media_features(litehtml::media_features& media) const override;
		void				get_language(litehtml::tstring& language, litehtml::tstring & culture) const override;

		DocumentContainerAdapter(IDocumentContainer* doc_container_intf, IDocument* doc);
	};

	class DocumentAdapter : public Microsoft::WRL::RuntimeClass<Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::ClassicCom>, IDocument> {
	private:
		litehtml::document::ptr m_doc;
		DocumentContainerAdapter m_doc_container;
		litehtml::context* m_ctx;
	public: //IDocument
		int	 Render(int max_width, litehtml::render_type rt = litehtml::render_all) override;
		void Draw(int x, int y, const litehtml::position* clip) override;
		int	 Width() const override;
		int	 Height() const override;
		void AddStylesheet(const tchar_t* str, const tchar_t* baseurl, const tchar_t* media) override;
		bool OnMouseOver(int x, int y, int client_x, int client_y) override;
		bool OnLButtonDown(int x, int y, int client_x, int client_y) override;
		bool OnLButtonUp(int x, int y, int client_x, int client_y) override;
		bool OnMouseLeave() override;
	public:
		DocumentAdapter(const char* text, IDocumentContainer* container, litehtml::context* ctx) : m_doc_container(container, this), m_ctx(ctx) {
			m_doc = litehtml::document::createFromUTF8(text, &m_doc_container, m_ctx);
		}
	};

	class LightBrowser : public Microsoft::WRL::RuntimeClass<Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::ClassicCom>, ILightBrowser> {
	private:
		litehtml::context m_ctx;
	public:
		HRESULT STDMETHODCALLTYPE CreateDocumentFromUTF8(const char* text, IDocumentContainer* container, IDocument** result) override;
	};

	extern "C" __declspec(dllexport) HRESULT Create_ILightBrowser(ILightBrowser** result);
}