#include  "Gui.h"
#include "../Hacks/Setup.h"
#include "../Hacks/Settings.h"

#ifdef NOT_PERSONAL_USE
#define WINDOW1_SIZE_Y 305  
#define WINDOW1_SIZE_X 170
#else //OWN
#define WINDOW1_SIZE_Y 260   
#define WINDOW1_SIZE_X 165
#endif

#define WINDOW2_SIZE_X 470
#define WINDOW2_SIZE_Y 665

#define LABEL_WIN_SPEED_DELTA  310.f
#define LABEL_WIN_SPEED  0.006079f

#define MAIN_WIN_SPEED_DELTA  330.f
#define MAIN_WIN_SPEED  0.006239f

#define PREW_WIN_SPEED_DELTA  360.f
#define PREW_WIN_SPEED  0.006279f

class CMenu
{
private:
	int SelectedTab = -1;

	void SettingsMenu()
	{
		static int SelectedSettings = 0;

		VectorEx<const char*>MenuTabs = { lolc("configs"), lolc("settings") };
		TabsLabels(SelectedSettings, MenuTabs, Vec2(tahaGUI().GetCurWindowSize().x - (tahaGUI().GetStyle().wndPadding.x * 2), 0), false);

		tahaGUI().Spacing();
		tahaGUI().Separator();
		tahaGUI().Spacing();

		if (SelectedSettings == 0)
		{
			CGSettings::G().Menu();
			GP_Main->SetMenuColors();
		}
		else if (SelectedSettings == 1)
		{
			HotsKey("menu key", GP_Main->MenuButton);
			tahaGUI().Spacing();
			tahaGUI().Separator();
			tahaGUI().Spacing();
			DCheckBox("menu animation", tahaGUI().GetStyle().AnimationEnable);
			tahaGUI().Spacing();
			tahaGUI().Separator();
			tahaGUI().Spacing();
			DColorEdit("bgcolor", GP_Main->BackgroundColor);
			DColorEdit("titlecolor", GP_Main->TitleColor);
			DColorEdit("textcolor",  GP_Main->TextColor);
			DColorEdit("framecolor", GP_Main->FrameColor);
			DColorEdit("btncolor", GP_Main->ButtonColor);
			tahaGUI().SameLine();
			DColorEdit("disabled-btncolor", GP_Main->DisableButtonColor);
			DColorEdit("linecolor", GP_Main->LineColor);
			tahaGUI().Spacing();
			tahaGUI().Separator();
			tahaGUI().Spacing();
			if (tahaGUI().Button(__xor("reset colors")))
			{
				GP_Main->BackgroundColor.brainbow = false;
				GP_Main->TitleColor.brainbow = false;
				GP_Main->TextColor.brainbow = false;
				GP_Main->FrameColor.brainbow = false;
				GP_Main->ButtonColor.brainbow = false;
				GP_Main->DisableButtonColor.brainbow = false;
				GP_Main->LineColor.brainbow = false;

				GP_Main->BackgroundColor = Color(18, 18, 22, 255);
				GP_Main->TitleColor = Color(112, 112, 116, 255);
				GP_Main->TextColor = Color(255, 255, 255, 255);
				GP_Main->FrameColor = Color(34, 35, 37, 255);
				GP_Main->ButtonColor = Color(128, 135, 140, 255);
				GP_Main->DisableButtonColor = Color(225, 0, 0, 255);
				GP_Main->LineColor = Color(120, 121, 123, 255);
			}
			GP_Main->SetMenuColors();
		}
	}

public:

	int ChangerMode = 0;

	void Changers()
	{
#ifdef ENABLE_INVENTORY
		vector<string> ItemsCSS = { lolc("skins"), lolc("inventory") };
		VectorEx<const char*> ChaArr = { ItemsCSS[0].c_str(), ItemsCSS[1].c_str() };
		TabsLabels(ChangerMode, ChaArr, Vec2(328, 20), false);
		tahaGUI().SameLine(331);
		if (ChangerMode == 0)
		{
			if (tahaGUI().Button(GP_Skins->ShowSkinPreview ? __xor("preview <<<") : __xor("preview >>>"), Vec2(129, 20)))
            	GP_Skins->ShowSkinPreview = !GP_Skins->ShowSkinPreview;
		}

		if (ChangerMode == 1)
			if (tahaGUI().Button(GP_Inventory->ShowInventoryList ? __xor("inv list <<<") : __xor("inv list >>>"), Vec2(129, 20)))
				GP_Inventory->ShowInventoryList = !GP_Inventory->ShowInventoryList;

		tahaGUI().Spacing();
		tahaGUI().Separator();
		tahaGUI().Spacing();
#endif

		if (ChangerMode == 0)
			DCheckBox("enable skins", GP_Skins->SkinsEnable);
#ifdef ENABLE_INVENTORY
		if (ChangerMode == 1)
			DCheckBox("inventory sync", GP_Inventory->SkinsSyncEnable);
#endif

		tahaGUI().Spacing();
		tahaGUI().Separator();
		tahaGUI().Spacing();

		if (ChangerMode == 0)
			GP_Skins->Menu();
#ifdef ENABLE_INVENTORY
		if (ChangerMode == 1)
			GP_Inventory->Menu();
#endif
	}

	void SelectWindow()
	{
		VectorEx<const char*>MainTabs = { lolc("aim"), lolc("visuals"), lolc("changer"), lolc("misc"), lolc("nade helper"), lolc("configs") };
		TabsLabels(SelectedTab, MainTabs, Vec2(tahaGUI().GetCurWindowSize().x - (tahaGUI().GetStyle().wndPadding.x * 2), 220), true);

#ifdef NOT_PERSONAL_USE
		tahaGUI().Text(__xor("user:"));
		tahaGUI().Text(__xor("taha"));
		tahaGUI().Spacing();
		tahaGUI().Separator();
		tahaGUI().Spacing();
		tahaGUI().Text(__xor("days left:"));
		tahaGUI().Text(__xor("lifetime"));
#else //OWN
		tahaGUI().Text(__xor("improve it more!!"));
#endif
	}

	void DrawCurTab(int tab)
	{
		switch (tab)
		{
		case 0: if (GP_LegitAim) GP_LegitAim->Menu(); break;
		case 1: if (GP_Esp) GP_Esp->Menu(); break;
		case 2: if (GP_Skins) Changers(); break;
		case 3: if (GP_Misc) GP_Misc->Menu(); break;
		case 4: if (GP_GHelper) { GP_GHelper->Menu(); } break;
		case 5: SettingsMenu(); break;
		default: break;
		}
	}

	CAnimController AnimLabelsWin;
	CAnimController AnimMainWin;
	CAnimController AnimPrewWin;

	Vec2 LabelWinSize;
	Vec2 MainWinSize;
	Vec2 PrewWinSize;

	bool LabelWinEnd = false;
	bool MainWinEnd = false;
	bool PrewWinEnd = false;

	DWORD next_time_close = 0;

	void Draw(CFont *MenuFont)
	{
		auto LDraw = [&]()->void
		{
			auto ResetAnim = [&](bool reset)->void
			{
				AnimLabelsWin.Reset();
				AnimMainWin.Reset();
				AnimPrewWin.Reset();
				LabelWinEnd = reset;
				MainWinEnd = reset;
				PrewWinEnd = reset;
			};

			tahaGUI().SetFont(MenuFont);

			bool AnimEnable = tahaGUI().GetStyle().AnimationEnable;
			bool GuiEnable = CGlobal::IsGuiVisible;

			if (AnimEnable)
			{
				if (GuiEnable)
				{
					AnimLabelsWin.Update(true, LABEL_WIN_SPEED, LABEL_WIN_SPEED_DELTA);
					LabelWinSize = Vec2(WINDOW1_SIZE_X, 25 + AnimLabelsWin.Get(WINDOW1_SIZE_Y - 25));
					LabelWinEnd = AnimLabelsWin.IsEnd();
				}
				else
				{
					LabelWinSize = Vec2(WINDOW1_SIZE_X, 25);
					ResetAnim(false);
				}
			}
			else
			{
				LabelWinSize = Vec2(WINDOW1_SIZE_X, WINDOW1_SIZE_Y);
				ResetAnim(true);
			}

			if (GuiEnable)
			{
				tahaGUI().GetStyle().ScrollEnable = LabelWinEnd && MainWinEnd;

				GP_Main->HintMsg = "";

				Vec2 oldWinPadding = tahaGUI().GetStyle().wndPadding;
				tahaGUI().GetStyle().wndPadding = Vec2(2, 1);

				if (tahaGUI().Begin(CHEAT_HEAD, GWF_NoTitleBar, LabelWinSize, Vec2(450, 50)))
				{
					SelectWindow();

					next_time_close = GetTickCount64() + 15000;
				}
				tahaGUI().End();

				tahaGUI().GetStyle().wndPadding = oldWinPadding;

				if (LabelWinEnd && SelectedTab != -1)
				{
					if (AnimEnable)
					{
						AnimMainWin.Update(true, MAIN_WIN_SPEED, MAIN_WIN_SPEED_DELTA);
						MainWinSize = Vec2(WINDOW2_SIZE_X, AnimMainWin.Get(WINDOW2_SIZE_Y));
						MainWinEnd = AnimMainWin.IsEnd();
					}
					else
					{
						MainWinSize = Vec2(WINDOW2_SIZE_X, WINDOW2_SIZE_Y);
					}

					Vec2 LabelWinPos = tahaGUI().GetPrevWindowPos();
					tahaGUI().SetNextWindowPos(Vec2(LabelWinPos.x + WINDOW1_SIZE_X + 4, LabelWinPos.y));

					if (tahaGUI().Begin(__xor("Main"), GWF_NoTitleBar, MainWinSize, Vec2(600, 400)))
					{
						DrawCurTab(SelectedTab);
					}
					tahaGUI().End();

					if (MainWinEnd)
					{
						Vec2 MainWinPos = tahaGUI().GetPrevWindowPos();

						bool IsVisualsTab = SelectedTab == 1 && GP_Esp->ShowPreview;
						bool IsLegitAimTab = SelectedTab == 0 && GP_LegitAim->ShowWeaponList;
						//bool IsSkinsTab = SelectedTab == 3 && ChangerMode == 0 && GP_Skins->ShowSkinPreview;
#ifdef ENABLE_INVENTORY
						bool IsInventTab = SelectedTab == 3 && ChangerMode == 1 && GP_Inventory->ShowInventoryList;
#endif

						static Vec2 TargetSize = Vec2(100, 100);
						static Vec2 CurSize = Vec2(100, 100);

						if (IsVisualsTab)
							TargetSize = Vec2(350 + (tahaGUI().GetStyle().wndPadding.x * 2) + 1, WINDOW2_SIZE_Y);

						//else if (IsSkinsTab)
						//	TargetSize = Vec2(320, 248);
#ifdef ENABLE_INVENTORY
						else if (IsInventTab)
							TargetSize = Vec2(365, WINDOW2_SIZE_Y);
#endif
						else if (IsLegitAimTab)
						{
							if (GP_LegitAim->WeaponCustomTypes == 0)
								TargetSize = Vec2(160, WINDOW2_SIZE_Y);
							else if (GP_LegitAim->WeaponCustomTypes == 1)
								TargetSize = Vec2(160, 135);
							else if (GP_LegitAim->WeaponCustomTypes == 2)
								TargetSize = Vec2(463, WINDOW2_SIZE_Y);
						}

						static bool ShowPrewWin = false;
#ifdef ENABLE_INVENTORY
						bool EnablePrewWin = IsVisualsTab || IsLegitAimTab /*|| IsSkinsTab*/ || IsInventTab;
#else
						bool EnablePrewWin = IsVisualsTab || IsLegitAimTab;
#endif

						if (AnimEnable)
						{
							AnimPrewWin.Update(EnablePrewWin, PREW_WIN_SPEED, PREW_WIN_SPEED_DELTA);
							CurSize.x = AnimPrewWin.Get(TargetSize.x);
							CurSize.y = TargetSize.y;
							ShowPrewWin = !AnimPrewWin.IsStart();
						}
						else
						{
							CurSize = TargetSize;
							ShowPrewWin = EnablePrewWin;
						}

						if (ShowPrewWin)
						{
							if (AnimEnable)
								tahaGUI().SetNextWindowPos(Vec2(MainWinPos.x + WINDOW2_SIZE_X + AnimPrewWin.Get(4), MainWinPos.y));
							else
								tahaGUI().SetNextWindowPos(Vec2(MainWinPos.x + WINDOW2_SIZE_X + 4, MainWinPos.y));

							if (tahaGUI().Begin(__xor("prew"), GWF_NoTitleBar, CurSize, Vec2(1, 1)))
							{
								if (SelectedTab == 0 && GP_LegitAim->WeaponCustomTypes != 3 && GP_LegitAim->ShowWeaponList)
									if (GP_LegitAim)
										GP_LegitAim->SubsectionsMenu();

								if (SelectedTab == 1)
									if (GP_Esp)
										GP_Esp->VisualPreview();

								if (SelectedTab == 3)	
								{
									//if (ChangerMode == 0)
									//	GP_Skins->Preview();
#ifdef ENABLE_INVENTORY
									if (ChangerMode == 1)
										GP_Inventory->InvListMenu();
#endif
								}
							}
							tahaGUI().End();
						}

						if (GP_Main->HintMsg != "")
						{
							int HintSizeY = tahaGUI().CalcTextSize(GP_Main->HintMsg).y + 9;
							tahaGUI().SetNextWindowPos(Vec2(MainWinPos.x, MainWinPos.y - HintSizeY - 4));
							if (tahaGUI().Begin(__xor("Hint"), GWF_NoTitleBar, Vec2(WINDOW2_SIZE_X, HintSizeY), Vec2(1, 1)))
							{

							}
							tahaGUI().End();
						}
					}
				}
			}
			else
			{
				if (SelectedTab != -1 && next_time_close <= GetTickCount64())
					SelectedTab = -1;
			}
		};
		LDraw();
	}
};