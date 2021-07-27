#include "Inventory.h"
#include "../Setup.h"
#include "../../GUI/Gui.h"

#define lol(e)  string(__xor(e))
#define lolc(e) __xor(e)

string IGlovesModels[49] =
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

int IPage = 0;

inline bool FindLower(string data, string find)
{
	if (find.empty())
		return true;
	transform(data.begin(), data.end(), data.begin(), ::tolower);
	transform(find.begin(), find.end(), find.begin(), ::tolower);

	if (data.find(find) != string::npos)
		return true;

	return false;
}
void CInventory::Menu()
{
	float long_item_w = tahaGUI().GetThis()->Info.Size.x - (tahaGUI().GetStyle().wndPadding.x * 2);
	auto SkinParams = [&](SkinSettings &Item) -> void
	{
		Inventory invBuffer;
		tahaGUI().PushItemWidth(400);
		SliderFloats("Seed", Item.seed, 0.f, 2.f);
		SliderFloats("Wear", Item.wear, 0.f, 2.f, "%.9f");
		tahaGUI().PushItemWidth(270);
		SliderInts("StatTrak", Item.stat_track, 0, 5000);
		tahaGUI().SameLine();
		DCheckBox("Auto StatTrak", Item.auto_stat_track);

		tahaGUI().PushItemWidth(400);

		vector<string> ItemsRarity = { lolc("Default"), lolc("Consumer"), lolc("Industrial"), lolc("Mil-Spec"), lolc("Restricted"), lolc("Classified") ,
	        lolc("Covert"), lolc("Contraband") };

		VectorEx<const char* > ItemsRR = { ItemsRarity[0].c_str(), ItemsRarity[1].c_str(), ItemsRarity[2].c_str(), ItemsRarity[3].c_str(), ItemsRarity[4].c_str(), ItemsRarity[5].c_str(),
			ItemsRarity[6].c_str(), ItemsRarity[7].c_str() };

		vector<string> ItemsQuality = { lolc("Default"), lolc("Genuine"), lolc("Vintage"), lolc("Knife Star"), lolc("Tournament"), lolc("Community") ,
	        lolc("Valve"), lolc("Prototype"), lolc("Customized"), lolc("StatTrak"), lolc("Complited") };

		VectorEx<const char* > ItemsQQ = { ItemsQuality[0].c_str(), ItemsQuality[1].c_str(), ItemsQuality[2].c_str(), ItemsQuality[3].c_str(), ItemsQuality[4].c_str(), ItemsQuality[5].c_str(),
			ItemsQuality[6].c_str(), ItemsQuality[7].c_str(), ItemsQuality[8].c_str(), ItemsQuality[9].c_str(), ItemsQuality[10].c_str() };

		DComboBox("Rarity", Item.rarity, ItemsRR);
		DComboBox("Quality", Item.quality, ItemsQQ);
		tahaGUI().InputText(__xor("Name##InvChr"), Item.custom_name, 32);
	};

	if (GP_Skins->WeaponNames.size() > 0)
	{
		VectorEx<const char* > InvArr = { lolc("Weapon"), lolc("Knife"),lolc("Gloves"), lolc("Medals"), lolc ("Profile") };
		static int InvSettingsMode = 0;

		TabsLabels(InvSettingsMode, InvArr, Vec2(long_item_w-10,20), false);
		tahaGUI().Spacing();

		if (InvSettingsMode == 0)
		{
			VectorEx<const char* > WeapSkinArr = { lolc("Skin##InventChanger"),lolc("Stickers##InventChanger") };
			static int WeapSkinSettingsMode = 0;

			TabsLabels(WeapSkinSettingsMode, WeapSkinArr, Vec2(long_item_w, 0), false);

			tahaGUI().Spacing();
			tahaGUI().Separator();
			tahaGUI().Spacing();

			ItemSettings* WItem = &GP_Skins->WeaponNames[InvSelectedWeapon];
			if (GP_Skins)
			{
				if (WeapSkinSettingsMode == 0)
				{
					ItemsList(GP_Skins->WeaponNames, InvSelectedWeapon, Vec2(231, 388), __xor("##AllWeapons"));
					GP_Skins->WeaponPreview = WItem->CdnName;
					tahaGUI().SameLine();
					tahaGUI().BeginGroup();
					{
						tahaGUI().PushItemWidth(185);
						VectorEx<const char* > ItemsSM = { lolc("All") , lolc("Distributed") };
						DComboBox("Skins##InventChanger", WItem->Skin.skins_mode, ItemsSM);
						static char FindBuf[128] = { 0 };
						static string FindSkin = "";
						TextEdit("Find##InventChanger", FindSkin, FindBuf, 128);
						tahaGUI().Spacing();
						if (WItem->Skin.skins_mode == 0)
						{
							SkinsList(GP_Skins->skin_kits, WItem->Skin.paint_kit_menu, Vec2(229, 342), __xor("##AllSkins"), FindSkin);
							WItem->Skin.paint_kit_id = GP_Skins->skin_kits[WItem->Skin.paint_kit_menu].id;
							GP_Skins->SkinPreview = GP_Skins->skin_kits[WItem->Skin.paint_kit_menu].cdn_name;
						}
						else if (WItem->Skin.skins_mode == 1)
						{
							if (GP_Skins->AllSkinsLoaded)
							{
								SortSkinsList(GP_Skins->SortedWeapons[InvSelectedWeapon].kits, WItem->Skin.paint_kit_menu, Vec2(229, 342), __xor("##AllSkins"), FindSkin);
								if (WItem->Skin.paint_kit_menu < (int)GP_Skins->SortedWeapons[InvSelectedWeapon].kits.size())
								{
									WItem->Skin.paint_kit_id = GP_Skins->SortedWeapons[InvSelectedWeapon].kits[WItem->Skin.paint_kit_menu].kit;
									GP_Skins->SkinPreview = GP_Skins->SortedWeapons[InvSelectedWeapon].kits[WItem->Skin.paint_kit_menu].cdn_name;
								}
							}
							else
							{
								tahaGUI().ListBoxHeader(__xor("##AllSkinsEmpty"), Vec2(229, 342));
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

					VectorEx<const char* > Slots = { lolc("1"),lolc("2"), lolc("3"), lolc("4") };
					DComboBox("Slot##InvChrSS", iSlot, Slots, Slots);

					static int StikersMode = 1;
					static int SortSelectedS = 0;

					VectorEx<const char* > ItemsSM = { lolc("All") ,lolc("Distributed") };
					DComboBox("Stickers##InvChrSS", StikersMode, ItemsSM);
					static char FindBuf[128] = { 0 };
					static string FindSticker = "";

					tahaGUI().Spacing();

					StickerSettings* SItem = &WItem->Skin.Stickers[iSlot];

					if (StikersMode == 0)
					{
						TextEdit("Find##InvChrSS", FindSticker, FindBuf, 128);
						tahaGUI().ListBoxHeader(__xor("##StikerSerials"), Vec2(453, 380));
						for (size_t i = 0; i < GP_Skins->sticker_kits.size(); i++)
						{
							if (!FindLower(GP_Skins->sticker_kits[i].name, FindSticker))
								continue;

							bool selected = i == SItem->kit_menu_index;
							if (tahaGUI().SelectLabel(GP_Skins->sticker_kits[i].name.c_str(), selected))
								SItem->kit_menu_index = i;
						}
						tahaGUI().ListBoxFooter();
						SItem->kit = GP_Skins->sticker_kits[SItem->kit_menu_index].id;
					}
					else if (StikersMode == 1)
					{
						if (GP_Skins->AllSkinsLoaded)
						{
							tahaGUI().ListBoxHeader(__xor("##SortStikerSerials"), Vec2(71, 402));
							for (size_t i = 0; i < GP_Skins->SortedStickers.size(); i++)
							{
								bool selected = i == SortSelectedS;
								if (tahaGUI().SelectLabel(GP_Skins->SortedStickers[i].sub_name.c_str(), selected))
									SortSelectedS = i;
							}
							tahaGUI().ListBoxFooter();
							tahaGUI().SameLine();
							tahaGUI().BeginGroup();
							{
								TextEdit("Find##InvChrSS", FindSticker, FindBuf, 128);
								tahaGUI().ListBoxHeader(__xor("##StikerSerials"), Vec2(386, 380));
								for (size_t i = 0; i < GP_Skins->SortedStickers[SortSelectedS].Stickers.size(); i++)
								{
									if (!FindLower(GP_Skins->SortedStickers[SortSelectedS].Stickers[i].name, FindSticker))
										continue;

									bool selected = i == SItem->kit_menu_index;

									if (tahaGUI().SelectLabel(GP_Skins->SortedStickers[SortSelectedS].Stickers[i].name.c_str(), selected))
										SItem->kit_menu_index = i;
								}
								tahaGUI().ListBoxFooter();
							}
							tahaGUI().EndGroup();

							if (SItem->kit_menu_index > 0 && SItem->kit_menu_index < (int)GP_Skins->SortedStickers[SortSelectedS].Stickers.size())
								SItem->kit = GP_Skins->SortedStickers[SortSelectedS].Stickers[SItem->kit_menu_index].id;
						}
						else
							tahaGUI().Text(__xor("Loading Stickers..."));
					}

					tahaGUI().PushItemWidth(400);
					SliderFloats("Wear", SItem->wear, 0.f, 1.f);
					SliderFloats("Scale", SItem->scale, 0.f, 1.f);
					SliderFloats("Rotation", SItem->rotation, 0.f, 360);
				}
				

				if (tahaGUI().Button(__xor("ADD##Sticker"), Vec2(long_item_w, 22)))
				{
					Inventory invBuffer;
					invBuffer.ItemType = IT_WEAPON;

					invBuffer.Index = InventoryList.size() == 0 ? Inventory::LastIndex + 1 : InventoryList.back().Index + 1;
					if (invBuffer.Index < Inventory::LastIndex)
						invBuffer.Index += Inventory::LastIndex - invBuffer.Index;

					if (invBuffer.Index == Inventory::LastIndex)
						invBuffer.Index = Inventory::LastIndex + 1;

					invBuffer.Weapon = WItem->ID;
					invBuffer.WeaponSkinId = WItem->Skin.paint_kit_id;
					invBuffer.Wear = WItem->Skin.wear;
					invBuffer.Seed = WItem->Skin.seed;
					invBuffer.StatTrack = WItem->Skin.stat_track;
					invBuffer.AutoStatTrack = WItem->Skin.auto_stat_track;
					invBuffer.Rarity = WItem->Skin.rarity;
					invBuffer.Quality = WItem->Skin.quality;

					if (WItem->Skin.custom_name)
						snprintf(invBuffer.Name, 32, "%s", WItem->Skin.custom_name);

					for (int si(0); si < 5; si++)
						invBuffer.Stickers[si] = WItem->Skin.Stickers[si];

					invBuffer.WeaponName = GP_Skins->WeaponNames[InvSelectedWeapon].Name;
					if (WItem->Skin.skins_mode == 0)
						invBuffer.SkinName = GP_Skins->skin_kits[GP_Skins->WeaponNames[InvSelectedWeapon].Skin.paint_kit_menu].name_eng;
					else if (WItem->Skin.skins_mode == 1)
						invBuffer.SkinName = GP_Skins->SortedWeapons[InvSelectedWeapon].kits[WItem->Skin.paint_kit_menu].name;

					InventoryList.push_back(invBuffer);

					SendClientHello();
				}
			}
		}
		else if (InvSettingsMode == 1)
		{
			ItemsList(GP_Skins->KnifeNames, InvSelectedKnife, Vec2(231, 392), __xor("##AllKnifes"));
			tahaGUI().SameLine();

			if (GP_Skins)
			{
				ItemSettings* WItem = &GP_Skins->KnifeNames[InvSelectedKnife];

				WeaponPreview = WItem->CdnName;

				tahaGUI().BeginGroup();
				{
					tahaGUI().PushItemWidth(185);
					VectorEx<const char* > ItemsSM = { "All" , "Distributed" };
					DComboBox("Skins##InvChr", WItem->Skin.skins_mode, ItemsSM);
					static char FindBuf[128] = { 0 };
					static string FindSkin = "";
					TextEdit("Find##InvChr", FindSkin, FindBuf, 128);
					tahaGUI().Spacing();
					if (WItem->Skin.skins_mode == 0)
					{
						SkinsList(GP_Skins->skin_kits, WItem->Skin.paint_kit_menu, Vec2(229, 346), __xor("##AllKnifSkins"), FindSkin);
						WItem->Skin.paint_kit_id = GP_Skins->skin_kits[WItem->Skin.paint_kit_menu].id;
						SkinPreview = GP_Skins->skin_kits[WItem->Skin.paint_kit_menu].cdn_name;
					}
					else if (WItem->Skin.skins_mode == 1)
					{
						if (GP_Skins->AllSkinsLoaded)
						{
							SortSkinsList(GP_Skins->SortedKnives[InvSelectedKnife].kits, WItem->Skin.paint_kit_menu, Vec2(229, 346), __xor("##AllKnifSkins"), FindSkin);
							if (WItem->Skin.paint_kit_menu < (int)GP_Skins->SortedKnives[InvSelectedKnife].kits.size())
							{
								WItem->Skin.paint_kit_id = GP_Skins->SortedKnives[InvSelectedKnife].kits[WItem->Skin.paint_kit_menu].kit;
								SkinPreview = GP_Skins->SortedKnives[InvSelectedKnife].kits[WItem->Skin.paint_kit_menu].cdn_name;
							}
						}
						else
						{
							tahaGUI().ListBoxHeader(__xor("##AllKnifSkinsEmpty"), Vec2(229, 346));
							tahaGUI().Text(__xor("Loading Skins..."));
							tahaGUI().ListBoxFooter();
						}
					}
				}
				tahaGUI().EndGroup();

				tahaGUI().Spacing();

				SkinParams(WItem->Skin);

				if (tahaGUI().Button(__xor("ADD##Skins"), Vec2(long_item_w, 22)))
				{

					Inventory invBuffer;
					invBuffer.ItemType = IT_KNIFE;

					invBuffer.Index = InventoryList.size() == 0 ? Inventory::LastIndex + 1 : InventoryList.back().Index + 1;
					if (invBuffer.Index < Inventory::LastIndex)
						invBuffer.Index += Inventory::LastIndex - invBuffer.Index;

					if (invBuffer.Index == Inventory::LastIndex)
						invBuffer.Index = Inventory::LastIndex + 1;

					invBuffer.Weapon = WItem->ID;
					invBuffer.WeaponSkinId = WItem->Skin.paint_kit_id;
					invBuffer.Wear = WItem->Skin.wear;
					invBuffer.Seed = WItem->Skin.seed;
					invBuffer.StatTrack = WItem->Skin.stat_track;
					invBuffer.AutoStatTrack = WItem->Skin.auto_stat_track;
					invBuffer.Rarity = WItem->Skin.rarity;
					invBuffer.Quality = WItem->Skin.quality;

					if (WItem->Skin.custom_name)
						snprintf(invBuffer.Name, 32, "%s", WItem->Skin.custom_name);

					invBuffer.WeaponName = GP_Skins->KnifeNames[InvSelectedKnife].Name;
					if (WItem->Skin.skins_mode == 0)
						invBuffer.SkinName = GP_Skins->skin_kits[GP_Skins->KnifeNames[InvSelectedKnife].Skin.paint_kit_menu].name_eng;
					else if (WItem->Skin.skins_mode == 1)
						invBuffer.SkinName = GP_Skins->SortedKnives[InvSelectedKnife].kits[WItem->Skin.paint_kit_menu].name;

					InventoryList.push_back(invBuffer);

					SendClientHello();
				}
			}	
		}
		else if (InvSettingsMode == 2)
		{
			tahaGUI().ListBoxHeader(__xor("##Gloves"), Vec2(long_item_w, 505));
			for (int i = 0; i < sizeof(IGlovesModels) / sizeof(IGlovesModels[0]); i++)
			{
				bool selected = i == InvSelectedGlove;
				if (tahaGUI().SelectLabel(IGlovesModels[i].c_str(), selected))
					InvSelectedGlove = i;
			}
			tahaGUI().ListBoxFooter();

			tahaGUI().PushItemWidth(400);

			if (InvSelectedGlove > 0)
			{
				SliderFloats("Wear", InvGloveWear, 0.f, 1.f, __xor("%.9f"));
				tahaGUI().InputText(__xor("Name##Glove"), InvGloveName, 32);
			}

			if (tahaGUI().Button(__xor("ADD##Gloves"), Vec2(long_item_w, 22)) && InvSelectedGlove != 0)
			{
				Inventory invBuffer;
				invBuffer.ItemType = IT_GLOVE;

				invBuffer.Index = InventoryList.size() == 0 ? Inventory::LastIndex + 1 : InventoryList.back().Index + 1;
				if (invBuffer.Index < Inventory::LastIndex)
					invBuffer.Index += Inventory::LastIndex - invBuffer.Index;

				if (invBuffer.Index == Inventory::LastIndex)
					invBuffer.Index = Inventory::LastIndex + 1;

				invBuffer.Weapon = GP_Skins->GlovesSkin_Array[InvSelectedGlove - 1].ItemIndex;
				invBuffer.WeaponSkinId = GP_Skins->GlovesSkin_Array[InvSelectedGlove - 1].PaintKit;
				invBuffer.Wear = InvGloveWear;

				if (InvGloveName)
					snprintf(invBuffer.Name, 32, "%s", InvGloveName);

				invBuffer.Rarity = 6; //Covert
				invBuffer.Quality = 3; //Knife Star

				invBuffer.WeaponName = IGlovesModels[InvSelectedGlove];

				InventoryList.push_back(invBuffer);

				SendClientHello();
			}
		}
		else if (InvSettingsMode == 3)
		{
			static int SelectedMedal = 0;
			if (GP_Skins->AllSkinsLoaded)
			{
				tahaGUI().ListBoxHeader(__xor("##Medals"), Vec2(long_item_w, 545));
				for (size_t i = 0; i < Medals.size(); i++)
				{
					bool selected = i == SelectedMedal;
					if (tahaGUI().SelectLabel(Medals[i].Name.c_str(), selected))
						SelectedMedal = i;
				}
				tahaGUI().ListBoxFooter();
			}
			else
			{
				tahaGUI().ListBoxHeader(__xor("##MedalsEmpty"), Vec2(long_item_w, 545));
				tahaGUI().Text(__xor("Loading Medals..."));
				tahaGUI().ListBoxFooter();
			}
			if (tahaGUI().Button(__xor("ADD##Medals"), Vec2(long_item_w, 22)))
			{
				Inventory invBuffer;
				invBuffer.ItemType = IT_MEDAL;

				invBuffer.Index = InventoryList.size() == 0 ? Inventory::LastIndex + 1 : InventoryList.back().Index + 1;
				if (invBuffer.Index < Inventory::LastIndex)
					invBuffer.Index += Inventory::LastIndex - invBuffer.Index;

				if (invBuffer.Index == Inventory::LastIndex)
					invBuffer.Index = Inventory::LastIndex + 1;

				invBuffer.WeaponName = Medals[SelectedMedal].Name;
				invBuffer.WeaponSkinId = Medals[SelectedMedal].Id;

				InventoryList.push_back(invBuffer);

				SendClientHello();
			}
		}
		else if (InvSettingsMode == 4)
		{
			VectorEx<const char* > RankList =
			{
				lolc("Unranked"),
				lolc("Silver - I"),
				lolc("Silver - II"),
				lolc("Silver - III"),
				lolc("Silver - IV"),
				lolc("Silver - Elite"),
				lolc("Silver - Elite Master"),
				lolc("Gold Nova - I"),
				lolc("Gold Nova - II"),
				lolc("Gold Nova - III"),
				lolc("Gold Nova - Master"),
				lolc("Master Guardian - I"),
				lolc("Master Guardian - II"),
				lolc("Master Guardian - Elite"),
				lolc("Distinguished Master Guardian"),
				lolc("Legendary Eagle"),
				lolc("Legendary Eagle Master"),
				lolc("Supreme Master First Class"),
				lolc("Global Elite")
			};

			DComboBox("Rank", ProfileRank, RankList);
			tahaGUI().Spacing();
			tahaGUI().Separator();
			tahaGUI().Spacing();

			SliderInts("Private LVL", ProfileLevel, 1, 40);
			SliderInts("XP", ProfileXP, 1, 10000);
			tahaGUI().Spacing();
			tahaGUI().Separator();
			tahaGUI().Spacing();
			SliderInts("Wins", ProfileWins, 1, 10000);
			tahaGUI().Spacing();
			tahaGUI().Separator();
			tahaGUI().Spacing();
			SliderInts("Friendly", ProfileFriendly, 1, 10000);
			SliderInts("Leader", ProfileLeader, 1, 10000);
			SliderInts("Teacher", ProfileTeacher, 1, 10000);
			tahaGUI().Spacing();
			tahaGUI().Separator();
			tahaGUI().Spacing();
			if (tahaGUI().Button(__xor("Update Profile"), Vec2(long_item_w, 22)))
			{
				SendMMHello();
			}
		}
	}
}

string GetStickerByIdx(int idx)
{
	string entry = "";
	if (GP_Skins->AllSkinsLoaded)
	{
		for (auto &v : GP_Skins->sticker_kits)
			if (v.id == idx)
				return v.name;
	}
	return entry;
}

void CInventory::InvListMenu()
{
	float long_item_w = tahaGUI().GetThis()->Info.Size.x - (tahaGUI().GetStyle().wndPadding.x * 2);
	static int InventSelectItem = 0;

	tahaGUI().Text((__xor("Items: ") + to_string(InventoryList.size())).c_str());

	tahaGUI().ListBoxHeader(__xor("##InventoryList"), Vec2(long_item_w, 390));
	for (size_t i = 0; i < InventoryList.size(); i++)
	{
		bool Select = i == InventSelectItem;

		if (tahaGUI().SelectLabel((InventoryList[i].WeaponName + "##" + to_string(i)).c_str(), Select, Vec2(157, 0)))
			InventSelectItem = i;

		tahaGUI().SameLine();

		if (tahaGUI().SelectLabel(("| " + InventoryList[i].SkinName + " (" + to_string(InventoryList[i].WeaponSkinId) + ")" + "##" + to_string(i)).c_str(), Select))
			InventSelectItem = i;

	}
	tahaGUI().ListBoxFooter();
	if (InventSelectItem >= (int)InventoryList.size())
		InventSelectItem = InventoryList.size() - 1;

	if ((int)InventoryList.size() > 0 && InventSelectItem > -1 && InventSelectItem < (int)InventoryList.size())
	{
		tahaGUI().PushItemWidth(171);
		if (InventoryList[InventSelectItem].ItemType == IT_WEAPON)
		{
			tahaGUI().Spacing();
			tahaGUI().Separator();
			tahaGUI().Spacing();

			tahaGUI().Text("Stickers:");
			tahaGUI().Text("Slot1: ");
			tahaGUI().SameLine();
			tahaGUI().Text(GetStickerByIdx(InventoryList[InventSelectItem].Stickers[0].kit).c_str());
			tahaGUI().Text("Slot2: ");
			tahaGUI().SameLine();
			tahaGUI().Text(GetStickerByIdx(InventoryList[InventSelectItem].Stickers[1].kit).c_str());
			tahaGUI().Text("Slot3: ");
			tahaGUI().SameLine();
			tahaGUI().Text(GetStickerByIdx(InventoryList[InventSelectItem].Stickers[2].kit).c_str());
			tahaGUI().Text("Slot4: ");
			tahaGUI().SameLine();
			tahaGUI().Text(GetStickerByIdx(InventoryList[InventSelectItem].Stickers[3].kit).c_str());

			tahaGUI().Spacing();
			tahaGUI().Separator();
			tahaGUI().Spacing();
		}

		if (tahaGUI().Button(__xor("Update Inventory"), Vec2(long_item_w, 22)))
		{
			SendClientHello();
			SendMMHello();
		}

		tahaGUI().Spacing();
		if (tahaGUI().Button(__xor("Remove"), Vec2(long_item_w, 22)))
		{
			InventoryList.erase(InventoryList.begin() + InventSelectItem);
			SendClientHello();
		}
		//tahaGUI().SameLine();
		//if (tahaGUI().Button(__xor("Remove all"), Vec2(176, 22)) && InventoryList.size() > 0) //need fix
		//{
		//	InventoryList.clear();
		//	SendClientHello();
		//}

	}
}



























































