#include "UI.h"
UI::UI()
{
	AppMode = DESIGN;	//Design Mode is the startup mode

	//Initilaize interface colors
	DrawColor = BLACK;
	SelectColor = BLUE;
	ConnColor = RED;
	MsgColor = BLUE;
	BkGrndColor = WHITE;
	
	//Create the drawing window
	pWind = new window(width, height, wx, wy);	


	ChangeTitle("Electric Circuit Simulator Project");

	CreateDesignToolBar();	//Create the desgin toolbar
	CreateStatusBar();		//Create Status bar
	CreateDrawingArea();
}


int UI::getCompWidth() const
{
	return COMP_WIDTH;
}

int UI::getCompHeight() const
{
	return COMP_HEIGHT;
}

//======================================================================================//
//								Input Functions 										//
//======================================================================================//

void UI::GetPointClicked(int &x, int &y)
{
	pWind->WaitMouseClick(x, y);	//Wait for mouse click
}

void UI::GetLastPointClicked(int& x, int& y)
{
	pWind->GetMouseCoord(x, y);	// Retrieves the current location of the mouse (x and y).

}


string UI::GetSrting()
{
	//Reads a complete string from the user until the user presses "ENTER".
	//If the user presses "ESCAPE". This function should return an empty string.
	//"BACKSPACE" is also supported
	//User should see what he is typing at the status bar


	string userInput;
	char Key;
	while(1)
	{
		pWind->WaitKeyPress(Key);

		switch(Key)
		{
		case 27: //ESCAPE key is pressed
			PrintMsg("");
			return ""; //returns nothing as user has cancelled the input
		
		case 13:		//ENTER key is pressed
			return userInput;
		
		case 8:		//BackSpace is pressed
			if(userInput.size() > 0)
				userInput.resize(userInput.size() -1 );
			break;
		
		default:
			userInput+= Key;
		};
		
		PrintMsg(userInput);
	}

}

//This function reads the position where the user clicks to determine the desired action
ActionType UI::GetUserAction() const
{	
	int x,y;
	pWind->WaitMouseClick(x, y);	//Get the coordinates of the user click

	if(AppMode == DESIGN )	//application is in design mode
	{
		// [1] If user clicks on the Toolbar
		if ( y >= 0 && y < ToolBarHeight)
		{	
			//Check whick Menu item was clicked
			//==> This assumes that menu items are lined up horizontally <==
			int ClickedItemOrder = (x / ToolItemWidth);
			//Divide x coord of the point clicked by the menu item width (int division)
			//if division result is 0 ==> first item is clicked, if 1 ==> 2nd item and so on

			switch (ClickedItemOrder)
			{
			case ITM_RES:	return ADD_RESISTOR;
			case ITM_BULB:	return ADD_BULB;
			case ITM_BATTERY:	return ADD_BATTERY;
			case ITM_SWITCH:	return ADD_SWITCH;
			case ITM_GROUND:	return ADD_GROUND;
			case ITM_BUZZER:	return ADD_BUZZER;
			case ITM_FUSE:	return ADD_FUSE;
			case ITM_MODULE: return ADD_MODULE;
			case ITM_CONNECTION: return ADD_CONNECTION;
			case ITM_PASTE: return PASTE;
			case ITM_SAVE: return SAVE;
			case ITM_LOAD: return LOAD;
			case ITM_DELETE: return DEL;
			case ITM_UNDO: return UNDO;
			case ITM_REDO: return REDO;
			case ITM_SIM: return SIM_MODE;
			case ITM_EXIT:	return EXIT;	
			
			default: return DSN_TOOL;	//A click on empty place in desgin toolbar
			}
		}
	
		// [2] User clicks on the drawing area
		if ( y >= ToolBarHeight && y < height - StatusBarHeight && x < width - EditMenuWidth)
		{
			return SELECT;	//user wants to select/unselect a statement in the flowchart
		}

		// [3] User clicks on the edit menu area
		if (y >= ToolBarHeight && y < height - StatusBarHeight && x >= width - EditMenuWidth)
		{
			if (y >= height - StatusBarHeight - 200 && y < height - StatusBarHeight - 150) {
				return EDIT_Copy;	// user wants to copy the component
			}
			if (y >= height - StatusBarHeight - 150 && y <= height - StatusBarHeight - 100) {
				return EDIT_Cut;	// user user wants to cut the component
			}
			if (y >= height - StatusBarHeight - 100 && y < height - StatusBarHeight - 50) {
				return EDIT_Value;	// user wants to edit the component's value
			}
			if (y >= height - StatusBarHeight - 50 && y <= height - StatusBarHeight) {
				return EDIT_Label;	// user wants to edit the component's label
			}
		}
		
		// [3] User clicks on the status bar
		return STATUS_BAR;
	}
	else if (AppMode == SIMULATION)	//Application is in Simulation mode
	{
		if (y >= 0 && y < ToolBarHeight)
		{
			//Check whick Menu item was clicked
			//==> This assumes that menu items are lined up horizontally <==
			int ClickedItemOrder = (x / ToolItemWidth);
			//Divide x coord of the point clicked by the menu item width (int division)
			//if division result is 0 ==> first item is clicked, if 1 ==> 2nd item and so on

			switch (ClickedItemOrder)
			{
			case ITM_SIM_DSN: return DSN_MODE;
			case ITM_SIM_EXIT:	return EXIT;
			case ITM_AMP:	return CURR_MEASURE;
			case ITM_VOLT: return VOLT_MEASURE;
			case ITM_LOG: return LOG;
			default: return DSN_TOOL;	//A click on empty place in desgin toolbar
			}
		}

		if (y >= ToolBarHeight && y < height - StatusBarHeight && x < width - EditMenuWidth)
		{
			return SELECT;	//user wants to select/unselect a statement in the flowchart
		}

	}
	else if (AppMode == MODULE)	//Application is in Simulation mode
	{
		if (y >= 0 && y < ToolBarHeight)
		{
			//Check whick Menu item was clicked
			//==> This assumes that menu items are lined up horizontally <==
			int ClickedItemOrder = (x / ToolItemWidth);
			//Divide x coord of the point clicked by the menu item width (int division)
			//if division result is 0 ==> first item is clicked, if 1 ==> 2nd item and so on

			switch (ClickedItemOrder)
			{
			case ITM_MOD_DESIGN: return DSN_MODE;
			//case ITM_MOD_DEFAULT: return ADD_DEFAULT_MOD;
			case ITM_MOD_RESISTOR: return ADD_RESISTOR;
			case ITM_MOD_CONNECTION: return ADD_CONNECTION;
			case ITM_MOD_PASTE: return PASTE;
			case ITM_MOD_DELETE: return DEL;
			case ITM_MOD_SAVE: return SAVE;
			case ITM_MOD_LOAD: return LOAD;
			default: return DSN_TOOL;	//A click on empty place in desgin toolbar
			}
		}

		// [2] User clicks on the drawing area
		if (y >= ToolBarHeight && y < height - StatusBarHeight && x < width - EditMenuWidth)
		{
			return SELECT;	//user wants to select/unselect a statement in the flowchart
		}

		// [3] User clicks on the edit menu area
		if (y >= ToolBarHeight && y < height - StatusBarHeight && x >= width - EditMenuWidth)
		{
			if (y >= height - StatusBarHeight - 200 && y < height - StatusBarHeight - 150) {
				return EDIT_Copy;	// user wants to copy the component
			}
			if (y >= height - StatusBarHeight - 150 && y <= height - StatusBarHeight - 100) {
				return EDIT_Cut;	// user user wants to cut the component
			}
			if (y >= height - StatusBarHeight - 100 && y < height - StatusBarHeight - 50) {
				return EDIT_Value;	// user wants to edit the component's value
			}
			if (y >= height - StatusBarHeight - 50 && y <= height - StatusBarHeight) {
				return EDIT_Label;	// user wants to edit the component's label
			}
		}
	}


}



//======================================================================================//
//								Output Functions										//
//======================================================================================//

//////////////////////////////////////////////////////////////////////////////////
void UI::ChangeTitle(string Title) const
{
	pWind->ChangeTitle(Title);
}
//////////////////////////////////////////////////////////////////////////////////
void UI::CreateStatusBar() const
{
	pWind->SetPen(RED,3);
	pWind->DrawLine(0, height-StatusBarHeight, width, height-StatusBarHeight);
}
//////////////////////////////////////////////////////////////////////////////////
void UI::PrintMsg(string msg) const
{
	ClearStatusBar();	//Clear Status bar to print message on it
	// Set the Message offset from the Status Bar
	int MsgX = 25;
	int MsgY = StatusBarHeight - 10;

	// Print the Message
    pWind->SetFont(20, BOLD | ITALICIZED, BY_NAME, "Arial"); 
	pWind->SetPen(MsgColor); 
	pWind->DrawString(MsgX, height - MsgY, msg);
}
//////////////////////////////////////////////////////////////////////////////////
void UI::ClearStatusBar()const
{
	// Set the Message offset from the Status Bar
	int MsgX = 25;
	int MsgY = StatusBarHeight - 10;

	//Overwrite using bachground color to erase the message
	pWind->SetPen(BkGrndColor);
	pWind->SetBrush(BkGrndColor);
	pWind->DrawRectangle(MsgX, height - MsgY, width, height);
}
//////////////////////////////////////////////////////////////////////////////////////////
//Clears the drawing (degin) area
void UI::ClearDrawingArea() const
{
	pWind->SetPen(RED, 1);
	pWind->SetBrush(WHITE);
	pWind->DrawRectangle(0, ToolBarHeight, width, height - StatusBarHeight);
	
}

void UI::CreateDrawingArea() const {
	pWind->SetPen(BLUE, 3);
	pWind->DrawLine(0,90,1150,90);
	pWind->DrawLine(0, 590, 1150, 590);
	pWind->DrawLine(0, 90, 0, 590);
	pWind->DrawLine(1150, 90, 1150, 590);
}
//////////////////////////////////////////////////////////////////////////////////////////
//Draws the menu (toolbar) in the Design mode
void UI::CreateDesignToolBar() 
{
	AppMode = DESIGN;	//Design Mode

	//You can draw the tool bar icons in any way you want.

	//First prepare List of images for each menu item
	string MenuItemImages[ITM_DSN_CNT];
	MenuItemImages[ITM_RES] = "images\\Menu\\Menu_Resistor.jpg";
	MenuItemImages[ITM_BULB] = "images\\Menu\\Menu_Bulb.jpg";
	MenuItemImages[ITM_BATTERY] = "images\\Menu\\Menu_Battery.jpg";
	MenuItemImages[ITM_SWITCH] = "images\\Menu\\Menu_Switch.jpg";
	MenuItemImages[ITM_GROUND] = "images\\Menu\\Menu_Ground.jpg";
	MenuItemImages[ITM_BUZZER] = "images\\Menu\\Menu_Buzzer.jpg";
	MenuItemImages[ITM_FUSE] = "images\\Menu\\Menu_Fuse.jpg";
	MenuItemImages[ITM_MODULE] = "images\\Menu\\Menu_Module.jpg";
	MenuItemImages[ITM_CONNECTION] = "images\\Menu\\Menu_Connection.jpg";
	MenuItemImages[ITM_PASTE] = "images\\Menu\\Menu_Paste.jpg";
	MenuItemImages[ITM_SAVE] = "images\\Menu\\Menu_Save.jpg";
	MenuItemImages[ITM_LOAD] = "images\\Menu\\Menu_Load.jpg";
	MenuItemImages[ITM_DELETE] = "images\\Menu\\Menu_Delete.jpg";
	MenuItemImages[ITM_UNDO] = "images\\Menu\\Menu_Undo.jpg";
	MenuItemImages[ITM_REDO] = "images\\Menu\\Menu_Redo.jpg";
	MenuItemImages[ITM_SIM] = "images\\Menu\\Menu_Simulate.jpg";
	MenuItemImages[ITM_EXIT] = "images\\Menu\\Menu_Exit.jpg";

	//TODO: Prepare image for each menu item and add it to the list

	//Draw menu item one image at a time
	for(int i=0; i<ITM_DSN_CNT; i++)
		pWind->DrawImage(MenuItemImages[i],i*ToolItemWidth,0,ToolItemWidth, ToolBarHeight);


	//Draw a line under the toolbar
	pWind->SetPen(RED,3);
	pWind->DrawLine(0, ToolBarHeight, width, ToolBarHeight);	

}
//////////////////////////////////////////////////////////////////////////////////////////
//Draws the menu (toolbar) in the simulation mode
void UI::CreateSimulationToolBar()
{
	AppMode = SIMULATION;	//Simulation Mode

	//TODO: Write code to draw the simualtion toolbar (similar to that of design toolbar drawing)
	pWind->SetBrush(WHITE);
	pWind->DrawRectangle(0, 0, pWind->GetWidth(), ToolBarHeight);
	string MenuItemImages[ITM_SIM_CNT];
	MenuItemImages[ITM_SIM_DSN] = "images\\Menu\\Menu_Stop.jpg";
	MenuItemImages[ITM_VOLT] = "images\\Menu\\Menu_Voltmeter.jpg";
	MenuItemImages[ITM_AMP] = "images\\Menu\\Menu_Ammeter.jpg";
	MenuItemImages[ITM_LOG] = "images\\Menu\\Circuit_Log.jpg";
	MenuItemImages[ITM_SIM_EXIT] = "images\\Menu\\Menu_Exit.jpg";

	for (int i = 0; i < ITM_SIM_CNT; i++)
		pWind->DrawImage(MenuItemImages[i], i * ToolItemWidth, 0, ToolItemWidth-5, ToolBarHeight-5);

	ClearEditMenu();

	pWind->SetPen(RED, 3);
	pWind->DrawLine(0, ToolBarHeight, width, ToolBarHeight);
	pWind->DrawLine(0, 0, width, 0);


}
//////////////////////////////////////////////////////////////////////////////////////////
//Draws the menu (toolbar) in the module mode
void UI::CreateModuleToolBar()
{
	AppMode = MODULE;	//Module Mode

	//TODO: Write code to draw the module toolbar (similar to that of design toolbar drawing)
	pWind->SetBrush(WHITE);
	pWind->DrawRectangle(0, 0, pWind->GetWidth(), ToolBarHeight);
	string MenuItemImages[ITM_MOD_CNT];

	MenuItemImages[ITM_MOD_DESIGN] = "images\\Menu\\Menu_Stop.jpg";
	MenuItemImages[ITM_MOD_DEFAULT] = "images\\Menu\\Menu_Default.jpg";
	MenuItemImages[ITM_MOD_RESISTOR] = "images\\Menu\\Menu_Resistor.jpg";
	MenuItemImages[ITM_MOD_CONNECTION] = "images\\Menu\\Menu_Connection.jpg";
	MenuItemImages[ITM_MOD_PASTE] = "images\\Menu\\Menu_Paste.jpg";
	MenuItemImages[ITM_MOD_DELETE] = "images\\Menu\\Menu_Delete.jpg";
	MenuItemImages[ITM_MOD_SAVE] = "images\\Menu\\Menu_Save.jpg";
	MenuItemImages[ITM_MOD_LOAD] = "images\\Menu\\Menu_Load.jpg";

	for (int i = 0; i < ITM_MOD_CNT; i++)
		pWind->DrawImage(MenuItemImages[i], i * ToolItemWidth, 0, ToolItemWidth - 5, ToolBarHeight - 5);

	ClearEditMenu();

	pWind->SetPen(RED, 3);
	pWind->DrawLine(0, ToolBarHeight, width, ToolBarHeight);
	pWind->DrawLine(0, 0, width, 0);


}

//======================================================================================//
//								Components Drawing Functions							//
//======================================================================================//

void UI::DrawResistor(const GraphicsInfo &r_GfxInfo) const
{
	string ResImage;
	if (AppMode != SIMULATION) {
		if (r_GfxInfo.isClicked)
			ResImage = "Images\\Comp\\Resistor_HI.jpg";	//use image of highlighted resistor
		else
			ResImage = "Images\\Comp\\Resistor.jpg";	//use image of the normal resistor
	}
	else {
		ResImage = "Images\\Comp\\Resistor.jpg";	//use image of the normal resistor
	}
	//Draw Resistor at Gfx_Info (1st corner)
	pWind->DrawImage(ResImage, r_GfxInfo.PointsList[0].x, r_GfxInfo.PointsList[0].y, COMP_WIDTH, COMP_HEIGHT);
}
void UI::DrawBulb(const GraphicsInfo &r_GfxInfo) const
{
	string BulbImage;
	if (AppMode != SIMULATION) {
		if (r_GfxInfo.isClicked)
			BulbImage = "Images\\Comp\\Bulb_HI.jpg";	//use image of highlighted bulb
		else
			BulbImage = "Images\\Comp\\Bulb.jpg";	//use image of the normal bulb
	}
	else {
		if (r_GfxInfo.closed) {
			BulbImage = "Images\\Comp\\Bulb_Light.jpg";
		}
		else {
			BulbImage = "Images\\Comp\\Bulb.jpg";
		}
	}
	//Draw Bulb at Gfx_Info (1st corner)
	pWind->DrawImage(BulbImage, r_GfxInfo.PointsList[0].x, r_GfxInfo.PointsList[0].y, COMP_WIDTH, COMP_HEIGHT);
}
void UI::DrawBattery(const GraphicsInfo &r_GfxInfo) const
{
	string BatImage;
	if (AppMode != SIMULATION) {
		if (r_GfxInfo.isClicked)
			BatImage = "Images\\Comp\\Battery_HI.jpg";	//use image of highlighted battery
		else
			BatImage = "Images\\Comp\\Battery.jpg";	//use image of the normal battery
	}
	else {
		BatImage = "Images\\Comp\\Battery.jpg";	//use image of the normal battery
	}
	//Draw Battery at Gfx_Info (1st corner)
	pWind->DrawImage(BatImage, r_GfxInfo.PointsList[0].x, r_GfxInfo.PointsList[0].y, COMP_WIDTH, COMP_HEIGHT);
}
void UI::DrawSwitch(const GraphicsInfo &r_GfxInfo) const
{
	string SwImage;
	if (AppMode != SIMULATION) {
		if (r_GfxInfo.isClicked)
			SwImage = "Images\\Comp\\Switch_HI.jpg";	//use image of highlighted switch
		else
			SwImage = "Images\\Comp\\Switch.jpg";	//use image of the normal switch
	}
	else {
		if (r_GfxInfo.closed) {SwImage = "Images\\Comp\\Switch_Closed.jpg";}
		else { SwImage = "Images\\Comp\\Switch.jpg"; }
	}
	//Draw Switch at Gfx_Info (1st corner)
	pWind->DrawImage(SwImage, r_GfxInfo.PointsList[0].x, r_GfxInfo.PointsList[0].y, COMP_WIDTH, COMP_HEIGHT);
}
void UI::DrawGround(const GraphicsInfo &r_GfxInfo) const
{
	string GrImage;
	if (AppMode != SIMULATION) {
		if (r_GfxInfo.isClicked)
			GrImage = "Images\\Comp\\Ground_HI.jpg";	//use image of highlighted ground
		else
			GrImage = "Images\\Comp\\Ground.jpg";	//use image of the normal ground
	}
	else {
		GrImage = "Images\\Comp\\Ground.jpg";	//use image of the normal ground
	}
	//Draw Ground at Gfx_Info (1st corner)
	pWind->DrawImage(GrImage, r_GfxInfo.PointsList[0].x, r_GfxInfo.PointsList[0].y, COMP_WIDTH, COMP_HEIGHT);
}
void UI::DrawBuzzer(const GraphicsInfo &r_GfxInfo) const
{
	string BuzImage;
	if (AppMode != SIMULATION) {
		if (r_GfxInfo.isClicked)
			BuzImage = "Images\\Comp\\Buzzer_HI.jpg";	//use image of highlighted buzzer
		else
			BuzImage = "Images\\Comp\\Buzzer.jpg";	//use image of the normal buzzer
	}
	else {
		BuzImage = "Images\\Comp\\Buzzer.jpg";	//use image of the normal buzzer
	}
	//Draw Buzzer at Gfx_Info (1st corner)
	pWind->DrawImage(BuzImage, r_GfxInfo.PointsList[0].x, r_GfxInfo.PointsList[0].y, COMP_WIDTH, COMP_HEIGHT);
}
void UI::DrawFuse(const GraphicsInfo &r_GfxInfo) const
{
	string FusImage;
	if (AppMode != SIMULATION) {
		if (r_GfxInfo.isClicked)
			FusImage = "Images\\Comp\\Fuse_HI.jpg";	//use image of highlighted fuse
		else
			FusImage = "Images\\Comp\\Fuse.jpg";	//use image of the normal fuse
	}
	else {
		if (r_GfxInfo.exceeded_limit) {
			FusImage = "Images\\Comp\\Burnt_Fuse.jpg";	//use image of highlighted fuse
		}
		else {
			FusImage = "Images\\Comp\\Fuse.jpg";	//use image of the normal fus
		}
	}
	//Draw Fuse at Gfx_Info (1st corner)
	pWind->DrawImage(FusImage, r_GfxInfo.PointsList[0].x, r_GfxInfo.PointsList[0].y, COMP_WIDTH, COMP_HEIGHT);
}

void UI::DrawModule(const GraphicsInfo& r_GfxInfo) const
{
	string ModImage;

	if (AppMode != SIMULATION) {
		if (r_GfxInfo.isClicked)
			ModImage = "Images\\Comp\\Module_HI.jpg";	//use image of highlighted battery
		else
			ModImage = "Images\\Comp\\Module.jpg";	//use image of the normal battery
	}
	else
		ModImage = "Images\\Comp\\Module.jpg";	//use image of the normal battery
	

	//Draw Battery at Gfx_Info (1st corner)
	pWind->DrawImage(ModImage, r_GfxInfo.PointsList[0].x, r_GfxInfo.PointsList[0].y, COMP_WIDTH, COMP_HEIGHT);
}


void UI::DrawConnection(const GraphicsInfo &r_GfxInfo) const
{
	if (AppMode != SIMULATION) {
		if (r_GfxInfo.isClicked)
			pWind->SetPen(RED, 2);
		else
			pWind->SetPen(BLACK, 2);
	}
	else {
		pWind->SetPen(BLACK, 2);
	}
	pWind->DrawLine(r_GfxInfo.PointsList[0].x, r_GfxInfo.PointsList[0].y, r_GfxInfo.PointsList[1].x, r_GfxInfo.PointsList[1].y);
}


UI::~UI()
{
	delete pWind;
	pWind = nullptr;
}


void UI::DrawEditMenu(string ComponentLabel="Component", string ComponentValue = "1") {
	
	// Draw the left border
	this->ClearEditMenu();
	pWind->SetPen(RED, 3);
	pWind->DrawLine(width - EditMenuWidth, ToolBarHeight, width - EditMenuWidth, height - StatusBarHeight);

	// Draw the title and its borders
	pWind->SetFont(23, BOLD, BY_NAME, "Arial");
	pWind->SetPen(BLACK);
	pWind->DrawString(width - 205, ToolBarHeight + 40, "Edit Menu");
	pWind->SetPen(RED, 3);
	pWind->DrawLine(width - EditMenuWidth, ToolBarHeight + 90, width, ToolBarHeight + 90);
	
	// Draw the component's info
	pWind->SetFont(21, BOLD, BY_NAME, "Arial");
	pWind->SetPen(MsgColor);
	pWind->DrawString(width - 260, height - 400, "Label");
	pWind->DrawString(width - 260, height - 350, "Value");

	pWind->DrawString(width - 160, height - 400, ComponentLabel);
	pWind->DrawString(width - 160, height - 350, ComponentValue);


	// Draw the edit buttons & their borders
	pWind->SetPen(BLACK);
	pWind->DrawString(width - 200, height - StatusBarHeight - 185, "Copy");
	pWind->DrawString(width - 200, height - StatusBarHeight - 135, "Cut");
	pWind->DrawString(width - 200, height - StatusBarHeight - 85, "Edit Value");
	pWind->DrawString(width - 200, height - StatusBarHeight - 35, "Edit Label");


	pWind->SetPen(RED,3);
	pWind->DrawLine(width - EditMenuWidth, height - StatusBarHeight - 200, width, height - StatusBarHeight - 200);
	pWind->DrawLine(width - EditMenuWidth, height - StatusBarHeight - 150, width, height - StatusBarHeight - 150);
	pWind->DrawLine(width - EditMenuWidth, height - StatusBarHeight - 100, width, height - StatusBarHeight - 100);
	pWind->DrawLine(width - EditMenuWidth, height - StatusBarHeight - 50, width, height - StatusBarHeight - 50);
	
}


void UI::ClearEditMenu() const
{
	pWind->SetPen(BkGrndColor);
	pWind->SetBrush(BkGrndColor);
	pWind->DrawRectangle(width - 302, ToolBarHeight + 2, width, height - StatusBarHeight - 1);
}



void UI::DrawConnectionEditMenu(string ConnectionLabel = "Connection") {

	// Draw the left border
	this->ClearEditMenu();
	pWind->SetPen(RED, 3);
	pWind->DrawLine(width - EditMenuWidth, ToolBarHeight, width - EditMenuWidth, height - StatusBarHeight);

	// Draw the title and its borders
	pWind->SetFont(23, BOLD, BY_NAME, "Arial");
	pWind->SetPen(BLACK);
	pWind->DrawString(width - 260, ToolBarHeight + 40, "Connection Edit Menu");
	pWind->SetPen(RED, 3);
	pWind->DrawLine(width - EditMenuWidth, ToolBarHeight + 90, width, ToolBarHeight + 90);

	// Draw the component's info
	pWind->SetFont(21, BOLD, BY_NAME, "Arial");
	pWind->SetPen(MsgColor);
	pWind->DrawString(width - 260, height - 350, "Label");

	pWind->DrawString(width - 160, height - 350, ConnectionLabel);


	// Draw the edit buttons & their borders
	pWind->SetPen(BLACK);
	pWind->DrawString(width - 200, height - StatusBarHeight - 35, "Edit Label");

	pWind->SetPen(RED, 3);
	//pWind->DrawLine(width - EditMenuWidth, height - StatusBarHeight - 100, width, height - StatusBarHeight - 100);
	pWind->DrawLine(width - EditMenuWidth, height - StatusBarHeight - 50, width, height - StatusBarHeight - 50);

}

MODE UI::getAppMode() const {
	return AppMode;
}

