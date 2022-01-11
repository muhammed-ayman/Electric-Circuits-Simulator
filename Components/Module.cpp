#include "Module.h"

Module::Module(GraphicsInfo *r_GfxInfo):Component(r_GfxInfo)
{
	this->itemType = MOD;
}

Module::Module() {

}

void Module::Draw(UI* pUI)
{
	//Call output class and pass battery drawing info to it.
	pUI->DrawBattery(*m_pGfxInfo); //update to draw battery

}

void Module::Operate()
{

}

void Module::Save(ofstream& saveFile, string id)
{
	GraphicsInfo* gInfo = getGraphicsInfo();

	saveFile << GetItemType() + ", ";
	saveFile << id + ", ";
	saveFile << getLabel() + ", ";
	saveFile << to_string(getValue()) + ", ";
	saveFile << to_string(gInfo->PointsList[0].x) + ", ";
	saveFile << to_string(gInfo->PointsList[0].y) + "\n";
}

void Module::Load(GraphicsInfo* r_GfxInfo, string label, double value) {
	this->m_pGfxInfo = r_GfxInfo;
	this->m_Label = label;
	this->value = value;
}

void Module::SetCompList(Component* CompListNew[]) {
	for (int i = 0; i < MaxCompCount; i++) {
		this->CompList[i] = CompListNew[i];
	}
}

void Module::SetConnList(Connection* ConnListNew[]) {
	for (int i = 0; i < MaxConnCount; i++) {
		this->ConnList[i] = ConnListNew[i];
	}
}

void Module::GetCompList(Component* CompListNew[]) {
	for (int i = 0; i < MaxCompCount; i++) {
		CompListNew[i] = CompList[i];
	}
}

void Module::GetConnList(Connection* ConnListNew[]) {
	for (int i = 0; i < MaxConnCount; i++) {
		ConnListNew[i] = ConnList[i];
	}
}

void Module::SetCompCount(int CompCount) {
	this->CompCount = CompCount;
}

void Module::SetConnCount(int ConnCount) {
	this->ConnCount = ConnCount;
}

int Module::GetCompCount() {
	return this->CompCount;
}

int Module::GetConnCount() {
	return this->ConnCount;
}