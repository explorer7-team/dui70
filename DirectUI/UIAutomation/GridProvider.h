#pragma once

namespace DirectUI
{
	class UILIB_API GridProvider
		: public PatternProvider<GridProvider, IGridProvider, Schema::Pattern::Grid>
		, public IGridProvider
	{
	public:
		GridProvider(void);
		virtual ~GridProvider(void);;

		virtual unsigned long __stdcall AddRef(void);
		virtual long __stdcall GetItem(int, int, IRawElementProviderSimple * *);
		virtual PfnCreateProxy GetProxyCreator(void);
		virtual long __stdcall QueryInterface(GUID const &, void * *);
		virtual unsigned long __stdcall Release(void);
		virtual long __stdcall get_ColumnCount(int *);
		virtual long __stdcall get_RowCount(int *);

	};

	class UILIB_API GridProxy : public ProviderProxy
	{
	public:
		GridProxy(GridProxy const &);
		GridProxy();
		GridProxy & operator=(GridProxy const &);

		static GridProxy * __stdcall Create(Element *);
		static bool __stdcall IsPatternSupported(Element *);

		virtual long DoMethod(int, char *);

	protected:
		virtual void Init(Element *);

	private:
		long GetColumnCount(int *);
		long GetItem(unsigned int, unsigned int, IRawElementProviderSimple * *);
		long GetRowCount(int *);
	};
}