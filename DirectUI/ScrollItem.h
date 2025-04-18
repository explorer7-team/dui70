#pragma once

namespace DirectUI
{
	class UILIB_API ScrollItemProvider
		: public PatternProvider<ScrollItemProvider, IScrollItemProvider, Schema::Pattern::ScrollItem>
		, public IScrollItemProvider
	{
	public:
		ScrollItemProvider(void);
		virtual ~ScrollItemProvider(void);

		virtual unsigned long __stdcall AddRef(void);
		virtual PfnCreateProxy GetProxyCreator(void);
		virtual long __stdcall QueryInterface(struct _GUID const &, void * *);
		virtual unsigned long __stdcall Release(void);
		virtual long __stdcall ScrollIntoView(void);

	};

	class UILIB_API ScrollItemProxy : public ProviderProxy
	{
	public:
		ScrollItemProxy(ScrollItemProxy const &);
		ScrollItemProxy(void);
		ScrollItemProxy & operator=(ScrollItemProxy const &);

		static ScrollItemProxy * __stdcall Create(Element *);
		static bool __stdcall IsPatternSupported(Element *);

		virtual long DoMethod(int, char *);
	protected:
		virtual void Init(Element *);
	};
}