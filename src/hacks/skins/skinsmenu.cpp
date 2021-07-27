#include "Skins.h"
#include "../Setup.h"
#include "../../GUI/Gui.h"

#define KITS_LIST_X 229
#define KITS_LIST_Y 363

#define ITEM_LIST_X 231
#define ITEM_LIST_Y 409

#define lol(e) __xor(e)

string GlovesModels[49] =
{
	lol("default"),
	lol("Sport Superconductor"),
	lol("Sport Pandora's Box"),
	lol("Sport Hedge Maze"),
	lol("Sport Arid"),
	lol("Sport Vice"),
	lol("Sport Omega"),
	lol("Sport Bronze Morph"),
	lol("Sport Amphibious"),
	lol("Moto Eclipse"),
	lol("Moto Spearmint"),
	lol("Moto Boom!"),
	lol("Moto Cool Mint"),
	lol("Moto Polygon"),
	lol("Moto Transport"),
	lol("Moto Turtle"),
	lol("Moto Pow"),
	lol("Specialist Crimson Kimono"),
	lol("Specialist Emerald Web"),
	lol("Specialist Foundation"),
	lol("Specialist Forest DDPAT"),
	lol("Specialist Mogul"),
	lol("Specialist Fade"),
	lol("Specialist Buckshot"),
	lol("Specialist Crimson Web"),
	lol("Driver Lunar Weave"),
	lol("Driver Convoy"),
	lol("Driver Crimson Weave"),
	lol("Driver Diamondback"),
	lol("Driver Racing Green"),
	lol("Driver Overtake"),
	lol("Driver Imperial Plad"),
	lol("Driver King Snake"),
	lol("Hand Wraps Leather"),
	lol("Hand Wraps Spruce DDPAT"),
	lol("Hand Wraps Badlands"),
	lol("Hand Wraps Slaughter"),
	lol("Hand Wraps Aboreal"),
	lol("Hand Wraps Duct Tape"),
	lol("Hand Wraps Overprint"),
	lol("Hand Wraps Cobalt Skulls"),
	lol("Bloodhound Charred"),
	lol("Bloodhound Snakebite"),
	lol("Bloodhound Bronzed"),
	lol("Bloodhound Guerrilla"),
	lol("Hydra Case Hardened"),
	lol("Hydra Rattler"),
	lol("Hydra Mangrove"),
	lol("Hydra Emerald")
};


int Page = 0;

static bool FindLower(string data, string find)
{
	if (find.empty())
		return true;
	transform(data.begin(), data.end(), data.begin(), ::tolower);
	transform(find.begin(), find.end(), find.begin(), ::tolower);

	if (data.find(find) != string::npos)
		return true;

	return false;
}

void CSkins::ItemsList(const vector<ItemSettings> &Items, int &var, const Vec2 Size, const string Name)
{
	if (tahaGUI().ListBoxHeader(Name.c_str(), Size))
	{
		for (int i = 0; i < (int)Items.size(); i++)
		{
			bool selected = i == var;
			if (tahaGUI().SelectLabel((string(Items[i].Name) + __xor("##") + to_string(i)).c_str(), selected))
				var = i;
		}
	}
	tahaGUI().ListBoxFooter();
}

void CSkins::SkinsList(const vector<paint_kit> &Skins, int &var, const Vec2 Size, const string Name, const string Find)
{
	if (tahaGUI().ListBoxHeader(Name.c_str(), Size))
	{
		for (size_t i = 0; i < Skins.size(); i++)
		{
			if (!FindLower((true ? Skins[i].name_eng : Skins[i].name), Find))
				continue;

			bool selected = i == var;

			if (tahaGUI().SelectLabel(((true ? Skins[i].name_eng : Skins[i].name) + __xor("##") + to_string(i)).c_str(), selected, Vec2(151, 0)))
				var = i;
			tahaGUI().SameLine(149);
			if (tahaGUI().SelectLabel((__xor("| ") + to_string(Skins[i].id)).c_str(), selected, Vec2(75, 0)))
				var = i;

		}
	}
	tahaGUI().ListBoxFooter();
}

void CSkins::SortSkinsList(const vector<SortedKits_s> &Skins, int &var, const Vec2 Size, const string Name, const string Find)
{
	if (tahaGUI().ListBoxHeader(Name.c_str(), Size))
	{
		for (size_t i = 0; i < Skins.size(); i++)
		{
			if (!FindLower((true ? Skins[i].name : Skins[i].name_rus), Find))
				continue;

			bool selected = i == var;

			if (tahaGUI().SelectLabel(((true ? Skins[i].name : Skins[i].name_rus) + __xor("##") + to_string(i)).c_str(), selected, Vec2(151, 0)))
				var = i;
			tahaGUI().SameLine(149);
			if (tahaGUI().SelectLabel((__xor("| ") + to_string(Skins[i].kit)).c_str(), selected, Vec2(75, 0)))
				var = i;

		}
	}
	tahaGUI().ListBoxFooter();

}

void CSkins::Menu()
{
	float long_item_w = tahaGUI().GetThis()->Info.Size.x - (tahaGUI().GetStyle().wndPadding.x * 2);

	auto SkinParams = [&](SkinSettings &Item) -> void
	{
		tahaGUI().PushItemWidth(400);
		SliderFloats("Seed", Item.seed, 0.f, 2.f);
		SliderFloats("Wear", Item.wear, 0.f, 1.f, __xor("%.9f"));
		tahaGUI().PushItemWidth(270);
		SliderInts("StatTrak", Item.stat_track, 0, 5000);
		tahaGUI().SameLine();
		DCheckBox("Auto StatTrak", Item.auto_stat_track);

		tahaGUI().PushItemWidth(400);

		vector<string> ItemsQuality = { lolc("Default"), lolc("Genuine"), lolc("Vintage"), lolc("Knife Star"), lolc("Tournament"), lolc("Community") ,
			lolc("Valve"), lolc("Prototype"), lolc("Customized"), lolc("StatTrak"), lolc("Complited") };

		VectorEx<const char* > ItemsQQ = { ItemsQuality[0].c_str(), ItemsQuality[1].c_str(), ItemsQuality[2].c_str(), ItemsQuality[3].c_str(), ItemsQuality[4].c_str(), ItemsQuality[5].c_str(),
			ItemsQuality[6].c_str(), ItemsQuality[7].c_str(), ItemsQuality[8].c_str(), ItemsQuality[9].c_str(), ItemsQuality[10].c_str() };

		DComboBox("Quality", Item.quality, ItemsQQ);

		tahaGUI().InputText(__xor("Name##custom_name"), Item.custom_name, 32);
	};

	VectorEx<const char*> SkinArr = { lolc("Weapon"), lolc("Knife"), lolc("Gloves") };

	static int SkinSettingsMode = 0;

	TabsLabels(SkinSettingsMode, SkinArr, Vec2(long_item_w - 6, 0), false);
	tahaGUI().Spacing();
	if (SkinSettingsMode == 0)
	{
		VectorEx<const char*> WeapSkinArr = { lolc("Skin##Changer"), lolc("Stickers##Changer") };
		static int WeapSkinSettingsMode = 0;

		TabsLabels(WeapSkinSettingsMode, WeapSkinArr, Vec2(long_item_w, 0), false);

		tahaGUI().Spacing();
		tahaGUI().Separator();
		tahaGUI().Spacing();

		if (tahaGUI().Button(__xor("Update"), Vec2(long_item_w, 22)))
		{
			UpdateSkins();
			Message::Get().Start(__xor("Updated!"));
		}

		tahaGUI().Spacing();

		if (WeapSkinSettingsMode == 0)
		{
			ItemsList(WeaponNames, SelectedWeapon, Vec2(ITEM_LIST_X, ITEM_LIST_Y), __xor("##AllWeapons"));

			tahaGUI().SameLine();

			ItemSettings* WItem = &WeaponNames[SelectedWeapon];

			//WeaponPreview = WItem->CdnName;

			tahaGUI().BeginGroup();
			{
				tahaGUI().PushItemWidth(185);
				VectorEx<const char*> itemssm = { lolc("All") , lolc("Distributed") };
				DComboBox("Skins##vod", WItem->Skin.skins_mode, itemssm);
				static char FindBuf[128] = { 0 };
				static string FindSkin = "";
				TextEdit("Find", FindSkin, FindBuf, 128);
				tahaGUI().Spacing();
				if (WItem->Skin.skins_mode == 0)
				{
					SkinsList(skin_kits, WItem->Skin.paint_kit_menu, Vec2(KITS_LIST_X, KITS_LIST_Y), __xor("##AllSkins"), FindSkin);
					WItem->Skin.paint_kit_id = skin_kits[WItem->Skin.paint_kit_menu].id;
					//SkinPreview = skin_kits[WItem->Skin.paint_kit_menu].cdn_name;
				}
				else if (WItem->Skin.skins_mode == 1)
				{
					if (AllSkinsLoaded)
					{
						SortSkinsList(SortedWeapons[SelectedWeapon].kits, WItem->Skin.paint_kit_menu, Vec2(KITS_LIST_X, KITS_LIST_Y), __xor("##AllSkins"), FindSkin);
						if (WItem->Skin.paint_kit_menu < (int)SortedWeapons[SelectedWeapon].kits.size())
						{
							WItem->Skin.paint_kit_id = SortedWeapons[SelectedWeapon].kits[WItem->Skin.paint_kit_menu].kit;
							//SkinPreview = SortedWeapons[SelectedWeapon].kits[WItem->Skin.paint_kit_menu].cdn_name;
						}
					}
					else
					{
						tahaGUI().ListBoxHeader(__xor("##AllSkinsEmpty"), Vec2(KITS_LIST_X, KITS_LIST_Y));
						tahaGUI().Text(__xor("Loading Skins..."));
						tahaGUI().ListBoxFooter();
					}

				}
			}
			tahaGUI().EndGroup();

			tahaGUI().Spacing();

			SkinParams(WItem->Skin);
		}
		else if (WeapSkinSettingsMode == 1)
		{
			tahaGUI().Spacing();
			tahaGUI().PushItemWidth(192);
			tahaGUI().Spacing();

			tahaGUI().PushItemWidth(320);

			static int iSlot = 0;

			VectorEx<const char*> Slots = { lolc("1"),lolc("2"), lolc("3"), lolc("4"), lolc("5") };
			DComboBox("Slot##Stickers", iSlot, Slots, Slots);

			static int StikersMode = 1;
			static int SortSelectedS = 0;

			VectorEx<const char*> itemssm = { lolc("All") ,lolc("Distributed") };
			DComboBox("Stickers##vodStickers", StikersMode, itemssm);
			static char FindBuf[128] = { 0 };
			static string FindSticker = "";

			tahaGUI().Spacing();

			StickerSettings* SItem = &WeaponNames[SelectedWeapon].Skin.Stickers[iSlot];

			if (StikersMode == 0)
			{
				TextEdit("Find", FindSticker, FindBuf, 128);
				tahaGUI().ListBoxHeader(__xor("##StikerSerials"), Vec2(453, 380));
				for (size_t i = 0; i < sticker_kits.size(); i++)
				{
					if (!FindLower(sticker_kits[i].name, FindSticker))
						continue;

					bool selected = i == SItem->kit_menu_index;
					if (tahaGUI().SelectLabel(sticker_kits[i].name.c_str(), selected))
						SItem->kit_menu_index = i;
				}
				tahaGUI().ListBoxFooter();
				SItem->kit = sticker_kits[SItem->kit_menu_index].id;
			}
			else if (StikersMode == 1)
			{
				if (AllSkinsLoaded)
				{
					tahaGUI().ListBoxHeader(__xor("##SortStikerSerials"), Vec2(71, 402));
					for (size_t i = 0; i < SortedStickers.size(); i++)
					{
						bool selected = i == SortSelectedS;
						if (tahaGUI().SelectLabel(SortedStickers[i].sub_name.c_str(), selected))
							SortSelectedS = i;
					}
					tahaGUI().ListBoxFooter();
					tahaGUI().SameLine();
					tahaGUI().BeginGroup();
					{
						TextEdit("Find", FindSticker, FindBuf, 128);
						tahaGUI().ListBoxHeader(__xor("##StikerSerials"), Vec2(386, 380));
						for (size_t i = 0; i < SortedStickers[SortSelectedS].Stickers.size(); i++)
						{
							if (!FindLower(SortedStickers[SortSelectedS].Stickers[i].name, FindSticker))
								continue;

							bool selected = i == SItem->kit_menu_index;

							if (tahaGUI().SelectLabel(SortedStickers[SortSelectedS].Stickers[i].name.c_str(), selected))
								SItem->kit_menu_index = i;
						}
						tahaGUI().ListBoxFooter();
					}
					tahaGUI().EndGroup();

					if (SItem->kit_menu_index > 0 && SItem->kit_menu_index < (int)SortedStickers[SortSelectedS].Stickers.size())
						SItem->kit = SortedStickers[SortSelectedS].Stickers[SItem->kit_menu_index].id;
				}
				else
				{
					tahaGUI().Text(__xor("Loading Stickers..."));
				}
			}

			tahaGUI().PushItemWidth(400);
			SliderFloats("Wear", SItem->wear, 0.f, 1.f);
			SliderFloats("Scale", SItem->scale, 0.f, 1.f);
			SliderFloats("Rotation", SItem->rotation, 0.f, 360);
		}
	}
	else if (SkinSettingsMode == 1)
	{
		VectorEx<const char*> KnfTeamArr = { lolc("CT"), lolc("T") };
		static int KnfTeamSettingsMode = 0;

		TabsLabels(KnfTeamSettingsMode, KnfTeamArr, Vec2(long_item_w, 0), false);

		tahaGUI().Spacing();
		tahaGUI().Separator();
		tahaGUI().Spacing();

		if (tahaGUI().Button(__xor("Update"), Vec2(long_item_w, 22)))
		{
			UpdateSkins();
			Message::Get().Start(__xor("Updated!"));
		}

		tahaGUI().Spacing();

		if (KnfTeamSettingsMode == 0)
		{
			ItemsList(KnifeNames, SelectedKnifeModelCT, Vec2(ITEM_LIST_X, ITEM_LIST_Y), __xor("##AllKnifes"));
			tahaGUI().SameLine();
			ItemSettings* WItem = &KnifeNames[SelectedKnifeModelCT];

			//WeaponPreview = WItem->CdnName;

			tahaGUI().BeginGroup();
			{
				tahaGUI().PushItemWidth(185);
				VectorEx<const char*> itemssm = { lolc("All"), lolc("Distributed") };
				DComboBox("Skins##vod", WItem->Skin.skins_mode, itemssm);
				static char FindBuf[128] = { 0 };
				static string FindSkin = "";
				TextEdit("Find", FindSkin, FindBuf, 128);
				tahaGUI().Spacing();
				if (WItem->Skin.skins_mode == 0)
				{
					SkinsList(skin_kits, WItem->Skin.paint_kit_menu, Vec2(KITS_LIST_X, KITS_LIST_Y), __xor("##AllKnifSkins"), FindSkin);
					WItem->Skin.paint_kit_id = skin_kits[WItem->Skin.paint_kit_menu].id;
					//SkinPreview = skin_kits[WItem->Skin.paint_kit_menu].cdn_name;
				}
				else if (WItem->Skin.skins_mode == 1)
				{
					if (AllSkinsLoaded)
					{
						SortSkinsList(SortedKnives[SelectedKnifeModelCT].kits, WItem->Skin.paint_kit_menu, Vec2(KITS_LIST_X, KITS_LIST_Y), __xor("##AllKnifSkins"), FindSkin);
						if (WItem->Skin.paint_kit_menu < (int)SortedKnives[SelectedKnifeModelCT].kits.size())
						{
							WItem->Skin.paint_kit_id = SortedKnives[SelectedKnifeModelCT].kits[WItem->Skin.paint_kit_menu].kit;
							//SkinPreview = SortedKnives[SelectedKnifeModelCT].kits[WItem->Skin.paint_kit_menu].cdn_name;
						}
					}
					else
					{
						tahaGUI().ListBoxHeader(__xor("##AllSkinsEmpty"), Vec2(KITS_LIST_X, KITS_LIST_Y));
						tahaGUI().Text(__xor("Loading Skins..."));
						tahaGUI().ListBoxFooter();
					}
				}
			}
			tahaGUI().EndGroup();
			tahaGUI().Spacing();

			SkinParams(WItem->Skin);

			//WeaponPreview = KnifeNames[SelectedKnifeModelCT].CdnName;
			//SkinPreview = skin_kits[KnifeNames[SelectedKnifeModelCT].Skin.paint_kit_menu].cdn_name;
		}
		else if (KnfTeamSettingsMode == 1)
		{
			ItemsList(KnifeNamesTT, SelectedKnifeModelTT, Vec2(ITEM_LIST_X, ITEM_LIST_Y), __xor("##AllKnifes"));
			tahaGUI().SameLine();
			ItemSettings* WItem = &KnifeNamesTT[SelectedKnifeModelTT];

			//WeaponPreview = WItem->CdnName;

			tahaGUI().BeginGroup();
			{
				tahaGUI().PushItemWidth(185);
				VectorEx<const char*> itemssm = { lolc("All"), lolc("Distributed") };
				DComboBox("Skins##vod", WItem->Skin.skins_mode, itemssm);
				static char FindBuf[128] = { 0 };
				static string FindSkin = "";
				TextEdit("Find", FindSkin, FindBuf, 128);
				tahaGUI().Spacing();
				if (WItem->Skin.skins_mode == 0)
				{
					SkinsList(skin_kits, WItem->Skin.paint_kit_menu, Vec2(KITS_LIST_X, KITS_LIST_Y), __xor("##AllKnifSkins"), FindSkin);
					WItem->Skin.paint_kit_id = skin_kits[WItem->Skin.paint_kit_menu].id;
					//SkinPreview = skin_kits[WItem->Skin.paint_kit_menu].cdn_name;
				}
				else if (WItem->Skin.skins_mode == 1)
				{
					if (AllSkinsLoaded)
					{
						SortSkinsList(SortedKnives[SelectedKnifeModelTT].kits, WItem->Skin.paint_kit_menu, Vec2(KITS_LIST_X, KITS_LIST_Y), __xor("##AllKnifSkins"), FindSkin);
						if (WItem->Skin.paint_kit_menu < (int)SortedKnives[SelectedKnifeModelTT].kits.size())
						{
							WItem->Skin.paint_kit_id = SortedKnives[SelectedKnifeModelTT].kits[WItem->Skin.paint_kit_menu].kit;
							//SkinPreview = SortedKnives[SelectedKnifeModelTT].kits[WItem->Skin.paint_kit_menu].cdn_name;
						}
					}
					else
					{
						tahaGUI().ListBoxHeader(__xor("##AllSkinsEmpty"), Vec2(KITS_LIST_X, KITS_LIST_Y));
						tahaGUI().Text(__xor("Loading Skins..."));
						tahaGUI().ListBoxFooter();
					}
				}
			}
			tahaGUI().EndGroup();
			tahaGUI().Spacing();

			SkinParams(WItem->Skin);

			//WeaponPreview = KnifeNamesTT[SelectedKnifeModelTT].CdnName;
			//SkinPreview = skin_kits[KnifeNamesTT[SelectedKnifeModelTT].Skin.paint_kit_menu].cdn_name;
		}
	}
	else if (SkinSettingsMode == 2)
	{
		VectorEx<const char*> glvTeamArr = { lolc("CT"), lolc("T") };
		static int glvTeamSettingsMode = 0;

		TabsLabels(glvTeamSettingsMode, glvTeamArr, Vec2(long_item_w, 0), false);

		tahaGUI().Spacing();
		tahaGUI().Separator();
		tahaGUI().Spacing();

		if (tahaGUI().Button(__xor("Update"), Vec2(long_item_w, 22)))
		{
			UpdateSkins();
			Message::Get().Start(__xor("Updated!"));
		}

		tahaGUI().Spacing();

		if (glvTeamSettingsMode == 0)
		{
			tahaGUI().ListBoxHeader(__xor("##Gloves"), Vec2(long_item_w, 527));
			for (int i = 0; i < sizeof(GlovesModels) / sizeof(GlovesModels[0]); i++)
			{
				bool selected = i == SelectedGloveCT;
				if (tahaGUI().SelectLabel(GlovesModels[i].c_str(), selected))
					SelectedGloveCT = i;
			}
			tahaGUI().ListBoxFooter();

			//if (SelectedGloveCT > 0)
			//{
			//	SkinPreview = GlovesSkin_Array[SelectedGloveCT - 1].Url;
			//	WeaponPreview = GlovesSkin_Array[SelectedGloveCT - 1].Url;
			//}

			tahaGUI().PushItemWidth(400);

			if (SelectedGloveCT > 0)
			{
				SliderFloats("Wear", GloveCTWear, 0.f, 1.f, __xor("%.9f"));
				//tahaGUI().InputText(__xor("Name##Glove"), GloveCTName, 32);
			}
		}
		
		else if (glvTeamSettingsMode == 1)
		{
			tahaGUI().ListBoxHeader(__xor("##Gloves"), Vec2(long_item_w, 527));
			for (int i = 0; i < sizeof(GlovesModels) / sizeof(GlovesModels[0]); i++)
			{
				bool selected = i == SelectedGloveTT;
				if (tahaGUI().SelectLabel(GlovesModels[i].c_str(), selected))
					SelectedGloveTT = i;
			}
			tahaGUI().ListBoxFooter();

			//if (SelectedGloveTT > 0)
			//{
			//	SkinPreview = GlovesSkin_Array[SelectedGloveTT - 1].Url;
			//	WeaponPreview = GlovesSkin_Array[SelectedGloveTT - 1].Url;
			//}

			tahaGUI().PushItemWidth(400);

			if (SelectedGloveTT > 0)
			{
				SliderFloats("Wear", GloveTTWear, 0.f, 1.f, __xor("%.9f"));
			//	tahaGUI().InputText(__xor("Name##Glove"), GloveTTName, 32);
			}
		}	
	}
}

//void CSkins::Preview()
//{
//	int ImageSzX = 304;
//	int ImageSzY = 231;
//
//	Vec2 BackMin = tahaGUI().GetCursorPos();
//	Vec2 BackMax = Vec2(BackMin.x + ImageSzX, BackMin.y + ImageSzY);
//
//	color_t BackColor = color_t(185.f, 183.f, 185.f, 183.f);
//	tahaGUI().DrawFilledBox(BackMin, BackMax, BackColor);
//
//	static IDirect3DTexture9* skinImg = nullptr;
//
//	static string OldKit = SkinPreview;
//	string link = "";
//
//	if (OldKit != SkinPreview)
//	{
//		skinImg = nullptr;
//
//		link = CGlobal::FindSkinURl(SkinPreview, WeaponPreview);
//		if (skinImg == nullptr)
//		{
//			std::string imData = CGlobal::DownloadSkinBytes(link.c_str());
//
//			D3DXCreateTextureFromFileInMemoryEx(GP_Render->m_pDevice, imData.data(), imData.length(), 512, 384, D3DX_DEFAULT,
//				0, D3DFMT_UNKNOWN, D3DPOOL_MANAGED, D3DX_DEFAULT, D3DX_DEFAULT, 0, NULL, NULL, &skinImg);
//		}
//	}
//
//	if (skinImg)
//		tahaGUI().DrawImage(skinImg, BackMin, BackMin + Vec2(ImageSzX, ImageSzY));
//
//	OldKit = SkinPreview;
//}



























































