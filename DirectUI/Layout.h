/*
 * DirectUI::Layout
 * File: Layout.h
 * Author: Olivia "Olive6841"
 * Description: Contains the class definition for DirectUI::Layout
 * History:
 * 	2025-April-21: (Olivia) Redo the class definition
 */


#pragma once

namespace DirectUI
{
	class UILIB_API Layout
	{
	public:
		static HRESULT WINAPI Create(Layout** ppLayout);
		void Destroy();

		virtual void DoLayout(Element* pec, int dWidth, int dHeight);
		virtual SIZE UpdateDesiredSize(Element* pec, int dConstW, int dConstH, Surface* psrf);
		virtual void OnAdd(Element* pec, Element** ppeAdd, UINT cCount);
		virtual void OnRemove(Element* pec, Element** ppeRemove, UINT cCount);
		virtual void OnLayoutPosChanged(Element* pec, Element* peChanged, int dOldLP, int dNewLP);
		virtual void Attach(Element* pec);
		virtual void Detach(Element* pec);

		UINT GetLayoutChildCount(Element* pec);
		int GetLayoutIndexFromChild(Element* pec, Element* peChild);
		Element* GetChildFromLayoutIndex(Element* pec, int iLayoutIdx, DynamicArray<Element*>* peList);
		virtual Element* GetAdjacent(Element* pec, Element* peFrom, int iNavDir, const NavReference* pnr, DWORD dwFlags);

		Layout();
		Layout(const Layout& other) = delete;

		void Initialize();

		virtual ~Layout();

		static void WINAPI UpdateLayoutRect(Element* pec, int cxContainer, int cyContainer, Element* peChild, int xElement, int yElement, int cxElement, int cyElement);

	protected:
		bool IsCacheDirty();
		void SetCacheDirty();
		void ClearCacheDirty();

		Element* _peClient;
		DynamicArray<Element*>* _pdaIgnore;

	private:
		bool _fCacheDirty;
	};
}
