#pragma once

namespace DirectUI
{
	class Value;
	struct PropertyInfo;

	struct DECLSPEC_NOVTABLE IElementListener
	{
		//0
		virtual void OnListenerAttach(Element* peFrom) = 0;
		//1
		virtual void OnListenerDetach(Element* peFrom) = 0;
		//2 returns false to cancel
		virtual bool OnListenedPropertyChanging(Element* peFrom, const PropertyInfo* ppi, int iIndex, Value* pvOld, Value* pvNew) = 0;
		//3
		virtual void OnListenedPropertyChanged(Element* peFrom, const PropertyInfo* ppi, int iIndex, Value* pvOld, Value* pvNew) = 0;
		//4
		virtual void OnListenedInput(Element* peFrom, InputEvent* pInput) = 0;
		//5
		virtual void OnListenedEvent(Element* peFrom, Event* pEvent) = 0;
	};

	struct UILIB_API IClassInfo
	{
		IClassInfo& operator=(const IClassInfo&) = delete;

		virtual void AddRef() = 0;
		virtual int Release() = 0;
		virtual HRESULT CreateInstance(Element*, ULONG*, Element**) = 0;
		virtual const PropertyInfo* EnumPropertyInfo(UINT) = 0;
		virtual const PropertyInfo* GetByClassIndex(UINT) = 0;
		virtual unsigned int GetPICount() const = 0;
		virtual unsigned int GetGlobalIndex() const = 0;
		virtual IClassInfo* GetBaseClass() = 0;
		virtual const WCHAR* GetName() const = 0;
		virtual bool IsValidProperty(PropertyInfo const*) const = 0;
		virtual bool IsSubclassOf(IClassInfo*) const = 0;
		virtual void Destroy() = 0;
		virtual HMODULE GetModule() const = 0;
		virtual bool IsGlobal() const = 0;
		virtual void AddChild() = 0;
		virtual void RemoveChild() = 0;
		virtual int GetChildren() const = 0;
		virtual void AssertPIZeroRef() const = 0;

		//virtual ~IClassInfo();
	};

	struct UILIB_API IDataEntry
	{
		IDataEntry(const IDataEntry&);
		IDataEntry();
		virtual ~IDataEntry();

		virtual HRESULT GetProperty(const WCHAR*, WCHAR**, bool*) = 0;
		virtual void* GetActual() = 0;

		IDataEntry& operator=(const IDataEntry&);
	};

	class DECLSPEC_NOVTABLE IProxy
	{
	public:
		virtual long DoMethod(int, char*) = 0;

	protected:
		virtual void Init(Element*) = 0;
	};

	class UILIB_API Proxy
	{
	public:
		Proxy(const Proxy&);
		Proxy();
		virtual ~Proxy();
		Proxy& operator=(const Proxy&);

		static long __stdcall SyncCallback(HGADGET__*, void*, EventMsg*);

	protected:
		void Invoke(unsigned int, void*);
		virtual void OnInvoke(unsigned int, void*);
	};

	class UILIB_API ProviderProxy : public IProxy
	{
	public:
		ProviderProxy(const ProviderProxy&);
		ProviderProxy& operator=(const ProviderProxy&);

	protected:
		ProviderProxy();
		virtual void Init(Element*);
	};

	typedef ProviderProxy* (__stdcall*ProviderProxyCall)(Element*);

	class UILIB_API IProvider
	{
	public:
		IProvider(const IProvider&);
		IProvider();
		IProvider& operator=(const IProvider&);

		virtual ProviderProxyCall GetProxyCreator() = 0;
	};

	class UILIB_API RefcountBase
	{
	public:
		RefcountBase();
		RefcountBase(const RefcountBase&) = delete;
		RefcountBase& operator=(const RefcountBase&) = delete;

		virtual ~RefcountBase();

		long AddRef();
		long Release();
	};


	template <class X, class Y, int i>
	class PatternProvider
		: public RefcountBase
		  , public IProvider
		//, public Y
	{
	public:
		PatternProvider();
		PatternProvider(const PatternProvider&) = delete;
		PatternProvider& operator=(const PatternProvider&) = delete;
		virtual ~PatternProvider();

		static long WINAPI Create(class ElementProvider*, IUnknown**);
		virtual void Init(ElementProvider*);
		//IProvider
		virtual ProviderProxyCall GetProxyCreator();

	protected:
		long DoInvoke(int, ...);

	private:
	};


	struct UILIB_API ISBLeak
	{
	public:
		ISBLeak(const ISBLeak&);
		ISBLeak();
		ISBLeak& operator=(const ISBLeak&);

		virtual void T1() = 0;
		virtual void T2() = 0;
		virtual void T3() = 0;
	};

	class UILIB_API IXProviderCP
	{
	public:
		IXProviderCP(const IXProviderCP&);
		IXProviderCP();
		IXProviderCP& operator=(const IXProviderCP&);

		virtual long CreateDUICP(class HWNDElement*, HWND, HWND, Element**, class DUIXmlParser**) = 0;
		virtual long CreateParserCP(DUIXmlParser**) = 0;
		virtual void DestroyCP() = 0;
	};

	class UILIB_API IXElementCP
	{
	public:
		IXElementCP(const IXElementCP&);
		IXElementCP();
		IXElementCP& operator=(const IXElementCP&);

		virtual HWND GetNotificationSinkHWND() = 0;
	};

	struct UILIB_API IDataEngine
	{
	public:
		IDataEngine(const IDataEngine&);
		IDataEngine();
		IDataEngine& operator=(const IDataEngine&);

		virtual ~IDataEngine();

		virtual UINT GetSize() = 0;
		virtual IDataEntry* GetEntry(UINT) = 0;
	};

	class UILIB_API StyleSheet
	{
	public:
		StyleSheet(const StyleSheet&);
		StyleSheet();
		StyleSheet& operator=(const StyleSheet&);

		static long __stdcall Create(StyleSheet**);

		virtual void T1() = 0;
		virtual void T2() = 0;
		virtual void T3() = 0;
		virtual void T4() = 0;
		virtual void T5() = 0;
		virtual void T6() = 0;
		virtual void T7() = 0;
		virtual void T8() = 0;
	};
}

class CSafeElementListenerCB : public DirectUI::IElementListener
{
public:
	void OnListenerAttach(DirectUI::Element* peFrom) override {}
	void OnListenerDetach(DirectUI::Element* peFrom) override {}
	bool OnListenedPropertyChanging(DirectUI::Element* peFrom, const DirectUI::PropertyInfo* ppi, int iIndex, DirectUI::Value* pvOld, DirectUI::Value* pvNew) override { return true; }
	void OnListenedPropertyChanged(DirectUI::Element* peFrom, const DirectUI::PropertyInfo* ppi, int iIndex, DirectUI::Value* pvOld, DirectUI::Value* pvNew) override {}
	void OnListenedInput(DirectUI::Element* peFrom, DirectUI::InputEvent* pInput) override {}
	void OnListenedEvent(DirectUI::Element* peFrom, DirectUI::Event* pEvent) override {}
};

namespace DuiBehaviorFilters
{
	enum Flags
	{
		None = 0x0,
		Hosted = 0x1,
		UnHosted = 0x2,
		PropertyChanging = 0x4,
		PropertyChanged = 0x8,
		Input = 0x10,
		KeyFocusMoved = 0x20,
		Events = 0x40,
		Layout = 0x80,
		Paint = 0x100,
		GetAdjacent = 0x200,
		DisplayNodeCallback = 0x400,
	};
}

DEFINE_ENUM_FLAG_OPERATORS(DuiBehaviorFilters::Flags);

namespace DirectUI
{
	struct UILIB_API NavReference
	{
		void Init(Element* pe, RECT* prc);

		UINT cbSize;
		Element* pe;
		RECT* prc;
	};
}

MIDL_INTERFACE("70650A6D-8987-4D93-9B1D-ACEB9D92F485")
IDuiBehavior : IUnknown
{
	virtual HRESULT STDMETHODCALLTYPE Init(DirectUI::Value* pvArgs) = 0;
	virtual HRESULT STDMETHODCALLTYPE GetCallbackFilters(DuiBehaviorFilters::Flags* pFilters) = 0;
	virtual HRESULT STDMETHODCALLTYPE OnAttach(DirectUI::Element* pe) = 0;
	virtual HRESULT STDMETHODCALLTYPE OnDetach(DirectUI::Element* pe) = 0;
	virtual HRESULT STDMETHODCALLTYPE OnHosted(DirectUI::Element* peFrom, DirectUI::Element* pe) = 0;
	virtual HRESULT STDMETHODCALLTYPE OnUnHosted(DirectUI::Element* peFrom, DirectUI::Element* peOldHost) = 0;
	virtual HRESULT STDMETHODCALLTYPE OnPropertyChanging(DirectUI::Element* peFrom, const DirectUI::PropertyInfo* ppi, int iIndex, DirectUI::Value* pvOld, DirectUI::Value* pvNew, BOOL* pfAllowProcess) = 0;
	virtual HRESULT STDMETHODCALLTYPE OnPropertyChanged(DirectUI::Element* peFrom, const DirectUI::PropertyInfo* ppi, int iIndex, DirectUI::Value* pvOld, DirectUI::Value* pvNew) = 0;
	virtual HRESULT STDMETHODCALLTYPE OnInput(DirectUI::Element* peFrom, DirectUI::InputEvent* pInput) = 0;
	virtual HRESULT STDMETHODCALLTYPE OnKeyFocusMoved(DirectUI::Element* peFrom, DirectUI::Element* peOld, DirectUI::Element* peNew) = 0;
	virtual HRESULT STDMETHODCALLTYPE OnEvent(DirectUI::Element* peFrom, DirectUI::Event* pEvent) = 0;
	virtual HRESULT STDMETHODCALLTYPE OnDoLayout(DirectUI::Element* peFrom, int dWidth, int dHeight) = 0;
	virtual HRESULT STDMETHODCALLTYPE OnUpdateDesiredSize(DirectUI::Element* peFrom, int dConstW, int dConstH, DirectUI::Surface* psrf, SIZE* pszDesired) = 0;
	virtual HRESULT STDMETHODCALLTYPE OnPaint(DirectUI::Element* peFrom, HDC hdc, const RECT* prcGadgetPxl, const RECT* prcInvalidPxl) = 0;
	virtual HRESULT STDMETHODCALLTYPE OnGetAdjacent(DirectUI::Element* peFrom, int iNavDir, const DirectUI::NavReference* pnr, DWORD dwFlags, DirectUI::Element** ppeTo) = 0;
	virtual HRESULT STDMETHODCALLTYPE OnDisplayNodeCallback(DirectUI::Element* peFrom, EventMsg* pGMsg) = 0;
};

MIDL_INTERFACE("2D97ED04-C05F-4302-9462-8A9EC79F1464")
ITouchTooltipEventSink : IUnknown
{
	virtual HRESULT STDMETHODCALLTYPE OnTooltipTimerFired(DirectUI::TOUCHTOOLTIP_INPUT touchTooltipInput, DirectUI::TOUCHTOOLTIP_TYPE touchTooltipType, DirectUI::TOUCHTOOLTIP_DELAY touchTooltipDelay) = 0;
	virtual HRESULT STDMETHODCALLTYPE OnTooltipHidden() = 0;
};

MIDL_INTERFACE("13450B2E-1819-49A5-B997-800D02CC0980")
ITouchTooltip : IUnknown
{
	virtual HRESULT STDMETHODCALLTYPE SetText(const WCHAR* pszText) = 0;
	virtual HRESULT STDMETHODCALLTYPE SetTextWithMaxLines(const WCHAR* pszText, UINT cLinesMax) = 0;
	virtual HRESULT STDMETHODCALLTYPE SetRichTooltip(DirectUI::Element* pe) = 0;
	virtual HRESULT STDMETHODCALLTYPE GetOptions(DirectUI::TOUCHTOOLTIP_OPTION_FLAGS* ptouchTooltipOptionFlags) = 0;
	virtual HRESULT STDMETHODCALLTYPE SetOptions(DirectUI::TOUCHTOOLTIP_OPTION_FLAGS touchTooltipOptionFlags) = 0;
	virtual HRESULT STDMETHODCALLTYPE SetDirection(DirectUI::TOUCHTOOLTIP_LAYOUT_DIRECTION touchTooltipLayoutDirection) = 0;
	virtual HRESULT STDMETHODCALLTYPE SetProgrammaticOffset(int cRPOffset) = 0;
	virtual HRESULT STDMETHODCALLTYPE StartShowTimer(DirectUI::TOUCHTOOLTIP_INPUT touchTooltipInput, DirectUI::TOUCHTOOLTIP_TYPE touchTooltipType) = 0;
	virtual HRESULT STDMETHODCALLTYPE Show(DirectUI::TOUCHTOOLTIP_INPUT touchTooltipInput, const RECT* prcTool, DirectUI::TOUCHTOOLTIP_PLACEMENT touchTooltipPlacementPreferred) = 0;
	virtual HRESULT STDMETHODCALLTYPE ShowNearTouchPoint(const POINT* pptTouch, DirectUI::TOUCHTOOLTIP_PLACEMENT touchTooltipPlacementPreferred) = 0;
	virtual HRESULT STDMETHODCALLTYPE ShowNearMousePoint(const POINT* pptMouse, DirectUI::TOUCHTOOLTIP_PLACEMENT touchTooltipPlacementPreferred) = 0;
	virtual HRESULT STDMETHODCALLTYPE Hide() = 0;
	virtual HRESULT STDMETHODCALLTYPE IsVisible() = 0;
	virtual HRESULT STDMETHODCALLTYPE Advise(ITouchTooltipEventSink* pEventSink) = 0;
	virtual HRESULT STDMETHODCALLTYPE Unadvise() = 0;
};