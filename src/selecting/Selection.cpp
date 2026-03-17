#include "Selection.h"
#include "Selector.h"
#include "../image/Image.h"

#pragma region Constructors/Destructors
Selection::Selection(BitMask* selection_mask) : select(this),m_selection_mask(selection_mask) {}
Selection::~Selection() {
	delete m_selection_mask;
}
#pragma endregion
#pragma region Selection
Image Selection::getImageFromSelection() const
{
	return Image(m_selection_mask->getImageData(), m_selection_mask->getWidth(), m_selection_mask->getHeight());
}
#pragma endregion


