#pragma once

#include <memory>
#include <wrl.h>
#include "..\html.h"
#include "..\document.h"

namespace litehtml {

	interface IDocument;

    interface DECLSPEC_UUID("BE8C16FF-7FD6-4F38-9D8F-847A098BD072")
    IListMarker: public IUnknown{
        virtual const tchar_t* STDMETHODCALLTYPE Image() = 0;
        virtual const tchar_t* STDMETHODCALLTYPE BaseUrl() = 0;
        virtual litehtml::web_color STDMETHODCALLTYPE Color() = 0;
        virtual const litehtml::position& STDMETHODCALLTYPE Position() = 0;
    };

    interface DECLSPEC_UUID("C1730CBD-6772-4A74-8078-7102A2EADB83")
    IBackgroundPaint : public IUnknown {
        virtual const tchar_t* STDMETHODCALLTYPE Image() = 0;
        virtual const tchar_t* STDMETHODCALLTYPE BaseUrl() = 0;
        virtual background_attachment STDMETHODCALLTYPE Attachment() = 0;
        virtual background_repeat STDMETHODCALLTYPE Repeat() = 0;
        virtual web_color STDMETHODCALLTYPE Color() = 0;
        virtual position* STDMETHODCALLTYPE ClipBox() = 0;
        virtual position* STDMETHODCALLTYPE OriginBox() = 0;
        virtual position* STDMETHODCALLTYPE BorderBox() = 0;
        virtual border_radiuses* STDMETHODCALLTYPE BorderRadius() = 0;
        virtual size STDMETHODCALLTYPE ImageSize() = 0;
        virtual int STDMETHODCALLTYPE PositionX() = 0;
        virtual int STDMETHODCALLTYPE PositionY() = 0;
        virtual bool STDMETHODCALLTYPE IsRoot() = 0;
    };

	interface DECLSPEC_UUID("5B906FFC-624F-41DF-9CCB-46FEC73A3F4F")
	IDocumentContainer : public IUnknown{
    public:
	    virtual litehtml::uint_ptr	STDMETHODCALLTYPE CreateFont(const litehtml::tchar_t* faceName, int size, int weight, litehtml::font_style italic, unsigned int decoration, litehtml::font_metrics* fm) = 0;
	    virtual void				STDMETHODCALLTYPE DeleteFont(litehtml::uint_ptr hFont) = 0;

	    virtual int					STDMETHODCALLTYPE TextWidth(const litehtml::tchar_t* text, litehtml::uint_ptr hFont) = 0;
	    virtual void				STDMETHODCALLTYPE DrawText(const litehtml::tchar_t* text, litehtml::uint_ptr hFont, litehtml::web_color color, const litehtml::position& pos) = 0;
	    virtual int					STDMETHODCALLTYPE PtToPx(int pt) = 0;
	    virtual int					STDMETHODCALLTYPE GetDefaultFontSize() const = 0;
	    virtual const litehtml::tchar_t* STDMETHODCALLTYPE GetDefaultFontName() const = 0;
	    virtual void				STDMETHODCALLTYPE DrawListMarker(const IListMarker* marker) = 0;
	    virtual void				STDMETHODCALLTYPE LoadImage(const litehtml::tchar_t* src, const litehtml::tchar_t* baseurl, bool redraw_on_ready) = 0;
	    virtual void				STDMETHODCALLTYPE GetImageSize(const litehtml::tchar_t* src, const litehtml::tchar_t* baseurl, litehtml::size& sz) = 0;
	    virtual void				STDMETHODCALLTYPE DrawBackground(IBackgroundPaint* bg) = 0;
	    virtual void				STDMETHODCALLTYPE DrawBorders(const litehtml::borders& borders, const litehtml::position& draw_pos, bool root) = 0;

	    virtual	void				STDMETHODCALLTYPE SetCaption(const litehtml::tchar_t* caption) = 0;
	    virtual	void				STDMETHODCALLTYPE SetBaseUrl(const litehtml::tchar_t* base_url) = 0;
	    virtual void				STDMETHODCALLTYPE Link(IDocument* doc) = 0;//, const litehtml::element::ptr& el) = 0;
	    virtual void				STDMETHODCALLTYPE OnAnchorClick(const litehtml::tchar_t* url) = 0;// , const litehtml::element::ptr& el) = 0;
	    virtual	void				STDMETHODCALLTYPE SetCursor(const litehtml::tchar_t* cursor) = 0;
	    //virtual	void				TransformText(litehtml::tstring& text, litehtml::text_transform tt) = 0;
	    //virtual void				ImportCss(litehtml::tstring& text, const litehtml::tstring& url, litehtml::tstring& baseurl) = 0;
	    virtual void				STDMETHODCALLTYPE SetClip(const litehtml::position& pos, const litehtml::border_radiuses& bdr_radius, bool valid_x, bool valid_y) = 0;
	    virtual void				STDMETHODCALLTYPE DelClip() = 0;
	    virtual void				STDMETHODCALLTYPE GetClientRect(litehtml::position& client) const = 0;
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
	    virtual int	 STDMETHODCALLTYPE Render(int max_width, litehtml::render_type rt = litehtml::render_all) = 0;
	    virtual void STDMETHODCALLTYPE Draw(int x, int y, const litehtml::position* clip) = 0;
	    virtual int	 STDMETHODCALLTYPE Width() const = 0;
	    virtual int	 STDMETHODCALLTYPE Height() const = 0;
	    virtual void STDMETHODCALLTYPE AddStylesheet(const tchar_t* str, const tchar_t* baseurl, const tchar_t* media) = 0;
	    virtual bool STDMETHODCALLTYPE OnMouseOver(int x, int y, int client_x, int client_y) = 0;
	    virtual bool STDMETHODCALLTYPE OnLButtonDown(int x, int y, int client_x, int client_y) = 0;
	    virtual bool STDMETHODCALLTYPE OnLButtonUp(int x, int y, int client_x, int client_y) = 0;
	    virtual bool STDMETHODCALLTYPE OnMouseLeave() = 0;
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
		int	 STDMETHODCALLTYPE Render(int max_width, litehtml::render_type rt = litehtml::render_all) override;
		void STDMETHODCALLTYPE Draw(int x, int y, const litehtml::position* clip) override;
		int	 STDMETHODCALLTYPE Width() const override;
		int	 STDMETHODCALLTYPE Height() const override;
		void STDMETHODCALLTYPE AddStylesheet(const tchar_t* str, const tchar_t* baseurl, const tchar_t* media) override;
		bool STDMETHODCALLTYPE OnMouseOver(int x, int y, int client_x, int client_y) override;
		bool STDMETHODCALLTYPE OnLButtonDown(int x, int y, int client_x, int client_y) override;
		bool STDMETHODCALLTYPE OnLButtonUp(int x, int y, int client_x, int client_y) override;
		bool STDMETHODCALLTYPE OnMouseLeave() override;
	public:
		DocumentAdapter(const char* text, IDocumentContainer* container, litehtml::context* ctx) : m_doc_container(container, this), m_ctx(ctx) {
			m_doc = litehtml::document::createFromUTF8(text, &m_doc_container, m_ctx);
		}
	};

    class ListMarkerAdapter : public Microsoft::WRL::RuntimeClass<Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::ClassicCom>, IListMarker> {
    private:
        litehtml::list_marker m_data;
    public:
        const tchar_t* STDMETHODCALLTYPE Image() override;
        const tchar_t* STDMETHODCALLTYPE BaseUrl() override;
        litehtml::web_color STDMETHODCALLTYPE Color() override;
        const litehtml::position& STDMETHODCALLTYPE Position() override;
        ListMarkerAdapter(const litehtml::list_marker& data);
    };

    class BackgroundPaintAdapter : public Microsoft::WRL::RuntimeClass<Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::ClassicCom>, IBackgroundPaint> {
    private:
        background_paint m_data;
    public:
        const tchar_t* STDMETHODCALLTYPE Image() override;
        const tchar_t* STDMETHODCALLTYPE BaseUrl() override;
        background_attachment STDMETHODCALLTYPE Attachment() override;
        background_repeat STDMETHODCALLTYPE Repeat() override;
        web_color STDMETHODCALLTYPE Color() override;
        position* STDMETHODCALLTYPE ClipBox() override;
        position* STDMETHODCALLTYPE OriginBox() override;
        position* STDMETHODCALLTYPE BorderBox() override;
        border_radiuses* STDMETHODCALLTYPE BorderRadius() override;
        size STDMETHODCALLTYPE ImageSize() override;
        int STDMETHODCALLTYPE PositionX() override;
        int STDMETHODCALLTYPE PositionY() override;
        bool STDMETHODCALLTYPE IsRoot() override;
        BackgroundPaintAdapter(const background_paint& data);
    };

	class LightBrowser : public Microsoft::WRL::RuntimeClass<Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::ClassicCom>, ILightBrowser> {
	private:
		litehtml::context m_ctx;
	public:
		HRESULT STDMETHODCALLTYPE CreateDocumentFromUTF8(const char* text, IDocumentContainer* container, IDocument** result) override;
	};

	extern "C" __declspec(dllexport) HRESULT Create_ILightBrowser(ILightBrowser** result);
}