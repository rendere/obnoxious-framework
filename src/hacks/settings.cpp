#include "Settings.h"
#include "Setup.h"
#include "../GUI/Gui.h"

//bool isDirectoryExists(const char *filename)
//{
//	DWORD dwFileAttributes = FastCall::G().t_GetFileAttributesA(filename);
//	if (dwFileAttributes == 0xFFFFFFFF)
//		return false;
//	return dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY;
//}

void CGSettings::SaveEx(nlohmann::json &j)
{
	if (GP_Esp)
	{
		GP_Esp->Config.Save(j);
		GP_Esp->SaveVisuals(j);
	}

	if (GP_GHelper)
		GP_GHelper->Config.Save(j);
#ifdef ENABLE_INVENTORY
	if (GP_Inventory)
	{
		GP_Inventory->Config.Save(j);
		GP_Inventory->SaveInventory(j);
	}
#endif
	if (GP_LegitAim)
	{
		GP_LegitAim->Config.Save(j);
		GP_LegitAim->SaveWeapons(j);
	}

	if (GP_Misc)
		GP_Misc->Config.Save(j);

	if (GP_Skins)
	{
		GP_Skins->Config.Save(j);
		GP_Skins->SaveSkins(j);
	}

	if (GP_Main)
		GP_Main->Config.Save(j);
}

void CGSettings::LoadEx(nlohmann::json &j)
{
	if (GP_Esp)
	{
		GP_Esp->Config.Load(j);
		GP_Esp->LoadVisuals(j);
	}

	if (GP_GHelper)
		GP_GHelper->Config.Load(j);
#ifdef ENABLE_INVENTORY
	if (GP_Inventory)
	{
		GP_Inventory->Config.Load(j);
		GP_Inventory->LoadInventory(j);
	}
#endif
	if (GP_LegitAim)
	{
		GP_LegitAim->Config.Load(j);
		GP_LegitAim->LoadWeapons(j);
	}

	if (GP_Misc)
		GP_Misc->Config.Load(j);

	if (GP_Skins)
	{
		GP_Skins->Config.Load(j);
		GP_Skins->LoadSkins(j);
	}

	if (GP_Main)
		GP_Main->Config.Load(j);
}

bool CGSettings::Save(string name)
{
	nlohmann::json JFile;

	SaveEx(JFile);

	std::ofstream o(config_name);

	if (!o)
	{
		o.clear();
		JFile.clear();
		return false;
	}

	o << std::setw(4) << JFile << std::endl;

	JFile.clear();
	return true;
}

bool CGSettings::Load()
{
	string JCont = readFile(config_name);

	if (JCont == string(__xor("Read Error")))
		return false;

	nlohmann::json JFile = nlohmann::json::parse(JCont);

	LoadEx(JFile);

	JFile.clear();
#ifdef ENABLE_INVENTORY
	GP_Inventory->SendClientHello();
#endif
	GP_Skins->UpdateSkins();

	return true;
}

void CGSettings::UpdateColors()
{
	if (GP_Esp)
		GP_Esp->Config.UpdateColors();

	if (GP_LegitAim)
		GP_LegitAim->Config.UpdateColors();

	if (GP_Misc)
		GP_Misc->Config.UpdateColors();

	if (GP_Main)
		GP_Main->Config.UpdateColors();
}

void CGSettings::SetName(const string _name)
{
	config_name = _name;
}

void CGSettings::UpdateList()
{
	AllSettings.clear();
	CGlobal::CreateFolderCFG();
	CGlobal::RefreshConfigs();

	if (CGlobal::ConfigList.size())
	{
		for (auto &v : CGlobal::ConfigList)
		{
			CfgInfo_s cfg_entry;
			cfg_entry.name = v;
			cfg_entry.id = "";
			AllSettings.push_back(cfg_entry);
		}
	}

	if (!AllSettings.empty())
	{
		vector<CfgInfo_s> TempSettings = AllSettings;
		vector<int> skip_idx;
		AllSettings.clear();

		for (int i(0); i < (int)TempSettings.size(); i++)
		{
			bool cont = false;
			for (int j(0); j < (int)skip_idx.size(); j++)
			{
				if (skip_idx[j] == i)
				{
					cont = true;
					break;
				}
			}
			if (cont)
				continue;
			AllSettings.push_back(TempSettings[i]);
		}
	}
}

void CGSettings::Menu()
{
	static int ConfigSelect = 0;
	static char NewConfigName[64] = { 0 };

	float long_item_w = tahaGUI().GetThis()->Info.Size.x - (tahaGUI().GetStyle().wndPadding.x * 2);

	if (tahaGUI().ListBoxHeader(__xor("##0"), Vec2(long_item_w, 250)))
	{
		tahaGUI().Spacing();
		tahaGUI().Separator();
		tahaGUI().Text(__xor("Name"));
		tahaGUI().Separator();

		for (int i = 0; i < (int)AllSettings.size(); i++)
		{
			bool selected = i == ConfigSelect;
			if (tahaGUI().SelectLabel(AllSettings[i].name.c_str(), selected, Vec2(225, 19)))
				ConfigSelect = i;
			tahaGUI().Separator();
		}
	}
	tahaGUI().ListBoxFooter();

	tahaGUI().Spacing();
	tahaGUI().Separator();
	tahaGUI().Spacing();

	tahaGUI().PushItemWidth(300.f);
	tahaGUI().InputText(__xor("##Name"), NewConfigName, 28);
	tahaGUI().SameLine();

	string SettignBaseDir = CGlobal::SystemDisk + __xor("obnoxious\\Configurations\\");
	string SettingsFormat = __xor(".json");

	if (tahaGUI().Button(__xor("create & save new config")))
	{
		string ConfigFileName = NewConfigName;

		if (ConfigFileName.size() < 1)
		{
			ConfigFileName = __xor("default");
		}

		SetName(SettignBaseDir + ConfigFileName + SettingsFormat);

		if (Save(ConfigFileName + SettingsFormat))
			Message::Get().Start(__xor("config saved"));
		else
			Message::Get().Start(__xor("save error"));

		UpdateList();
		strcpy(NewConfigName, "");
	}
	tahaGUI().Spacing();
	tahaGUI().Separator();
	tahaGUI().Spacing();

	if (tahaGUI().Button(__xor("update configs list"), Vec2(long_item_w, 0)))
	{
		UpdateList();
		Message::Get().Start(__xor("list updated"));
	}

	tahaGUI().Spacing();
	tahaGUI().Separator();
	tahaGUI().Spacing();

	if (tahaGUI().Button(__xor("load config"), Vec2(long_item_w, 0)))
	{
		if (ConfigSelect >= 0 && ConfigSelect < (int)AllSettings.size())
		{
			SetName(SettignBaseDir + AllSettings[ConfigSelect].name);
			if (Load())
				Message::Get().Start(__xor("config loaded"));
			else
				Message::Get().Start(__xor("load error"));
		}
	}
	tahaGUI().Spacing();
	if (tahaGUI().Button(__xor("Save config"), Vec2(long_item_w, 0)))
	{
		if (ConfigSelect >= 0 && ConfigSelect < (int)AllSettings.size())
		{
			SetName(SettignBaseDir + AllSettings[ConfigSelect].name);
			if (Save(AllSettings[ConfigSelect].name))
			{
				UpdateList();
				Message::Get().Start(__xor("Config saved"));
			}
			else
				Message::Get().Start(__xor("Save error"));
		}
	}
	tahaGUI().Spacing();
	tahaGUI().Separator();
	tahaGUI().Spacing();
	if (tahaGUI().Button(__xor("Delete config"), Vec2(long_item_w, 0)))
	{
		if (ConfigSelect >= 0 && ConfigSelect < (int)AllSettings.size())
		{
			string FulDel = SettignBaseDir + AllSettings[ConfigSelect].name;

			if (AllSettings.size() > 0)
			{
				FastCall::G().t_DeleteFileA(FulDel.c_str());
			}

			UpdateList();
			Message::Get().Start(__xor("Config deleted"));
		}
	}

	tahaGUI().Spacing();
	tahaGUI().Separator();
	tahaGUI().Spacing();
}

string CGSettings::readFile(const string& fileName)
{
	ifstream f(fileName);
	if (!f)
		return (__xor("Read error"));
	stringstream ss;
	ss << f.rdbuf();
	return ss.str();
}

void CMain::SetMenuColors()
{
	GuiStyle& style = tahaGUI().GetStyle();

	auto AutoChangeColor = [&](Color col, float ch) -> Color
	{
		Color entry;

		entry.SetR(((col.r() + ch < 0) ? 0 : ((col.r() + ch > 255) ? 255 : (col.r() + ch))));
		entry.SetG(((col.g() + ch < 0) ? 0 : ((col.g() + ch > 255) ? 255 : (col.g() + ch))));
		entry.SetB(((col.b() + ch < 0) ? 0 : ((col.b() + ch > 255) ? 255 : (col.b() + ch))));
		entry.SetA(col.a());

		return entry;
	};

	style.clrLine = LineColor;
	style.clrBackground = BackgroundColor;
	style.clrText = TextColor;

	style.clrFrame = FrameColor;
	style.clrFrameHover = AutoChangeColor(FrameColor, -5);
	style.clrFrameHold = AutoChangeColor(FrameColor, -9);

	style.clrTabLabel = color_t(ButtonColor.r(), ButtonColor.g(), ButtonColor.b(), 120);
	style.clrTabLabelText = color_t(TextColor.r(), TextColor.g(), TextColor.b(), 160);

	style.clrButton = ButtonColor;
	style.clrButtonHover = AutoChangeColor(ButtonColor, -10);
	style.clrButtonHold = AutoChangeColor(ButtonColor, -20);

	style.clrDisButton = DisableButtonColor;
	style.clrDisButtonHover = AutoChangeColor(DisableButtonColor, -10);
	style.clrDisButtonHold = AutoChangeColor(DisableButtonColor, -20);

	style.clrScroll = AutoChangeColor(ButtonColor, -20);
	style.clrScrollHover = AutoChangeColor(ButtonColor, -20);
	style.clrScrollHold = AutoChangeColor(ButtonColor, -20);
	style.clrTitle = TitleColor;
}

void CConfig::Save(nlohmann::json &j)
{
	for (auto &v : VecBool)
		j[SectionName][v.Key] = v.Var;

	for (auto &v : VecInt)
		j[SectionName][v.Key] = v.Var;

	for (auto &v : VecFloat)
		j[SectionName][v.Key] = v.Var;

	for (auto &v : VecDouble)
		j[SectionName][v.Key] = v.Var;

	for (auto &v : VecString)
		j[SectionName][v.Key] = v.Var;

	for (auto &v : VecColor)
	{
		j[SectionName][v.Key][__xor("R")] = v.Var.r();
		j[SectionName][v.Key][__xor("G")] = v.Var.g();
		j[SectionName][v.Key][__xor("B")] = v.Var.b();
		j[SectionName][v.Key][__xor("A")] = v.Var.a();
		j[SectionName][v.Key][__xor("Rainbow")] = v.Var.brainbow;
		j[SectionName][v.Key][__xor("flRainbow")] = v.Var.rainbow;
	}

	for (auto &v : VecBind)
	{
		j[SectionName][v.Key][__xor("Enable")] = v.Var.Enable;
		j[SectionName][v.Key][__xor("Button")] = v.Var.Button;
		j[SectionName][v.Key][__xor("Hold")] = v.Var.Hold;
	}

	debug_log("Settings: %s Saved\n", SectionName.c_str());
}

void CConfig::Load(nlohmann::json j)
{
	if (!j[SectionName].is_null())
	{
		for (auto &v : VecBool)
			if (!j[SectionName][v.Key].is_null())
				v.Var = j[SectionName][v.Key];

		for (auto &v : VecInt)
			if (!j[SectionName][v.Key].is_null())
				v.Var = j[SectionName][v.Key];

		for (auto &v : VecFloat)
			if (!j[SectionName][v.Key].is_null())
				v.Var = j[SectionName][v.Key];

		for (auto &v : VecDouble)
			if (!j[SectionName][v.Key].is_null())
				v.Var = j[SectionName][v.Key];

		for (auto &v : VecString)
			if (!j[SectionName][v.Key].is_null())
				v.Var = j[SectionName][v.Key].get<string>();

		for (auto &v : VecColor)
		{
			if (!j[SectionName][v.Key].is_null())
			{
				if (!j[SectionName][v.Key][__xor("R")].is_null())
					v.Var[0] = j[SectionName][v.Key][__xor("R")];

				if (!j[SectionName][v.Key][__xor("G")].is_null())
					v.Var[1] = j[SectionName][v.Key][__xor("G")];

				if (!j[SectionName][v.Key][__xor("B")].is_null())
					v.Var[2] = j[SectionName][v.Key][__xor("B")];

				if (!j[SectionName][v.Key][__xor("A")].is_null())
					v.Var[3] = j[SectionName][v.Key][__xor("A")];

				if (!j[SectionName][v.Key][__xor("Rainbow")].is_null())
					v.Var.brainbow = j[SectionName][v.Key][__xor("Rainbow")];

				if (!j[SectionName][v.Key][__xor("flRainbow")].is_null())
					v.Var.rainbow = j[SectionName][v.Key][__xor("flRainbow")];
			}
		}

		for (auto &v : VecBind)
		{
			if (!j[SectionName][v.Key].is_null())
			{
				if (!j[SectionName][v.Key][__xor("Enable")].is_null())
					v.Var.Enable = j[SectionName][v.Key][__xor("Enable")];

				if (!j[SectionName][v.Key][__xor("Button")].is_null())
					v.Var.Button = j[SectionName][v.Key][__xor("Button")];

				if (!j[SectionName][v.Key][__xor("Hold")].is_null())
					v.Var.Hold = j[SectionName][v.Key][__xor("Hold")];
			}
		}
		debug_log("Settings: %s Loaded\n", SectionName.c_str());
	}
}

void CConfig::UpdateColors()
{
	for (auto &v : VecColor)
		if (v.Var.brainbow)
			v.Var.UpdateRainbow(1.f, 1.f);
}



























































