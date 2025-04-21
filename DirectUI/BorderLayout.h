/*
 * DirectUI::BorderLayout
 * File: BorderLayout.h
 * Author: Olivia "Olive6841"
 * Description: Contains the class definition for DirectUI::BorderLayout
 * History:
 * 	2025-04-21: (Olivia) Redo the class definition
 */

#pragma once

namespace DirectUI
{
	class UILIB_API BorderLayout : public Layout
	{
	public:
		static HRESULT WINAPI Create(int dNumParams, int* pParams, Value** ppValue);
		static HRESULT WINAPI Create(Layout** ppLayout);

		void DoLayout(Element* pec, int cx, int cy) override;
		SIZE UpdateDesiredSize(Element* pec, int cxConstraint, int cyConstraint, Surface* psrf) override;
		void OnAdd(Element* pec, Element** ppeAdd, UINT cCount) override;
		void OnRemove(Element* pec, Element** ppeRemove, UINT cCount) override;
		void OnLayoutPosChanged(Element* pec, Element* peChanged, int dOldLP, int dNewLP) override;
		Element* GetAdjacent(Element* pec, Element* peFrom, int iNavDir, const NavReference* pnr, DWORD dwFlags) override;

		BorderLayout();
		BorderLayout(const BorderLayout& other) = delete;

		void Initialize();

		~BorderLayout() override;

		Element* _peClientPos;
		SIZE _sizeDesired;

		SIZE GetMaxCenter(Element* pec, int x, int y, int cw, int ch, int mTop, int mLeft, int mRight, int mBottom, bool setValues, HDC hDC);
		SIZE GetMaxLeftRight(Element* pec, int current, int x, int y, int cw, int ch, int mTop, int mLeft, int mRight, int mBottom, bool setValues, HDC hDC);
		SIZE GetMaxTopBottom(Element* pec, int current, int x, int y, int cw, int ch, int mTop, int mLeft, int mRight, int mBottom, bool setValues, HDC hDC);
		int NextChild(int i, Element* pec, Element** ppeCurrent, int* playoutPos);

	private:
		void SetClient(Element* pe);
	};
}
