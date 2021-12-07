#include "Component.h"

Component::Component(GraphicsInfo *r_GfxInfo)
{
	m_pGfxInfo = r_GfxInfo;
}

Component::Component()
{
	m_pGfxInfo = nullptr;
	term1_volt = term2_volt = 0;
	term1_conn_count = term2_conn_count = 0;

}

Component::~Component()
{
	delete m_pGfxInfo;
	m_pGfxInfo = nullptr;
}

GraphicsInfo* Component::getGraphicsInfo() {
	return m_pGfxInfo;
}


void Component::setClick(bool clickStatus) {
	m_pGfxInfo->isClicked = clickStatus;
}

 
string Component::getLabel() const {
	return this->m_Label;
}

void Component::setLabel(string label) {
	this->m_Label = label;
}


Items Component::GetItemType() const {
	return this->itemType;
}