#include "Component.h"
#include <iostream>

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


void Component::setGraphicsInfo(GraphicsInfo* m_pGfxInfo) {
	this->m_pGfxInfo = m_pGfxInfo;
}

void Component::setClick(bool clickStatus) {
	m_pGfxInfo->isClicked = clickStatus;
	clicked = clickStatus;
}

bool Component::isClicked() {
	return this->clicked;
}

void Component::setClosed(bool state)
{
	this->m_pGfxInfo->closed = state;
}

bool Component::isClosed() const
{
	return this->m_pGfxInfo->closed;
}

void Component::setExceededLimit(bool value)
{
	this->m_pGfxInfo->exceeded_limit = value;
}
 
string Component::getLabel() const {
	return this->m_Label;
}

void Component::setLabel(string label) {
	this->m_Label = label;
}

double Component::getValue() const {
	return this->value;
}

void Component::setValue(double value) {
	this->value = value;
}


string Component::GetItemType() const {
	switch (this->itemType) {
		case RES: return "RES";
		case BLB: return "BLB";
		case BAT: return "BAT";
		case SWT: return "SWT";
		case GND: return "GND";
		case BUZ: return "BUZ";
		case FUS: return "FUS";
		case MOD: return "MOD";
		default: return "NAN";
	}
}

Connection* Component::getTerm1Conn() const
{
	return term_connections[0];
}

void Component::setTerm1Conn(Connection *conn)
{
	term_connections[0] = conn;
}

Connection* Component::getTerm2Conn() const
{
	return term_connections[1];
}

void Component::setTerm2Conn(Connection *conn)
{
	term_connections[1] = conn;
}
