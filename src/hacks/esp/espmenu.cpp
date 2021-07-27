#include "Esp.h"
#include  "../../GUI/Gui.h"

#define SAME_LINE_1 115
#define SAME_LINE_2 230

#define PUSH_1 200
#define PUSH_2 400

void CEsp::Menu()
{
	auto LMenu = [&]()->void
	{
		static int VisType = 0;

		VectorEx<const char*>VisArr = { lolc("Player ESP"), lolc("Other ESP") };
		TabsLabels(VisType, VisArr, Vec2(320, 19), false);

		tahaGUI().SameLine(325);

		if (tahaGUI().Button(ShowPreview ? __xor("Preview >>>") :
			__xor("Preview <<<"), Vec2(136, 19)))
			ShowPreview = !ShowPreview;

		tahaGUI().Spacing();
		tahaGUI().Separator();
		tahaGUI().Spacing();

		if (VisType == 1)
		{
			tahaGUI().PushItemWidth(PUSH_1);

			DCheckBox("Grenades", WorldGrenade);
			if (WorldGrenade)
			{
				tahaGUI().SameLine(SAME_LINE_1);
				tahaGUI().PushItemWidth(PUSH_1);
				VectorEx<const char*>itemsGS = { lolc("Text") , lolc("Circle"), lolc("Icon") };
				DComboBox("Style##grenade", WorldGrenadeStyle, itemsGS);

				if (WorldGrenadeStyle != 1)
				{
					tahaGUI().PushItemWidth(PUSH_2);
					SliderInts("Text size##gre", TextGrenadeSize, 9, MAX_FONT_SIZE);
				}
				tahaGUI().Spacing();

				DColorEdit("High explosive grenade", HEGrenadeColor);
				tahaGUI().SameLine(SAME_LINE_2);
				DColorEdit("Molotov", MolotovGrenadeColor);

				DColorEdit("Flashbang", FlashGrenadeColor);
				tahaGUI().SameLine(SAME_LINE_2);
				DColorEdit("Incendiary grenade", IncGrenadeColor);

				DColorEdit("Smoke grenade", SmokeGrenadeColor);
				tahaGUI().SameLine(SAME_LINE_2);
				DColorEdit("Decoy grenade", DecoyGrenadeColor);
			}
			tahaGUI().Spacing();
			tahaGUI().Separator();
			tahaGUI().Spacing();
			DCheckBox("Weapons", WorldWeapons);
			if (WorldWeapons)
			{
				tahaGUI().SameLine(SAME_LINE_1);
				tahaGUI().PushItemWidth(PUSH_1);
				VectorEx<const char*>itemsWS = { lolc("Text"), lolc("Icon") };
				DComboBox("Style##weapon", WorldWeaponsStyle, itemsWS);

				tahaGUI().PushItemWidth(PUSH_2);
				SliderInts("Text size##weapon",TextWorldWeaponSize, 9, MAX_FONT_SIZE);

				tahaGUI().Spacing();
				DColorEdit("Color##weapon", WorldWeaponsColor);
			}
			tahaGUI().Spacing();
			tahaGUI().Separator();
			tahaGUI().Spacing();
			DCheckBox("Bomb", WorldBomb);
			if (WorldBomb)
			{
				tahaGUI().SameLine(SAME_LINE_1);
				tahaGUI().PushItemWidth(PUSH_1);
				VectorEx<const char*>itemsBS = { lolc("Text"), lolc("Icon") };
				DComboBox("Style##bomb", WorldBombStyle, itemsBS);

				tahaGUI().PushItemWidth(PUSH_2);
				SliderInts("Text size##bomb", TextBombSize, 9, MAX_FONT_SIZE);

				tahaGUI().Spacing();
				DColorEdit("Color##bomb", WorldBombColor);
			}
			DCheckBox("Bomb info", WorldBombInfo);
			tahaGUI().Spacing();
			tahaGUI().Separator();
			tahaGUI().Spacing();
			DCheckBox("Grenade trajectory", GranadePrediction);
			if (GranadePrediction)
			{
				tahaGUI().Spacing();
				DColorEdit("Color##trajgr", GranadePredictionColor);
			}
		}
		else if (VisType == 0)
		{

			DCheckBox("Enemy##Esp", Enemy);
			tahaGUI().SameLine(SAME_LINE_1);
			DCheckBox("Team##Esp", Team);
			tahaGUI().SameLine(SAME_LINE_2);
			DCheckBox("Visible only##Esp", BoxVisibleOnly);
			tahaGUI().PushItemWidth(100);
			DCheckBox("Bind##Esp", BindEnable.Enable);
			if (BindEnable.Enable)
			{
				tahaGUI().SameLine(SAME_LINE_1);
				DCheckBox("Hold##Esp", BindEnable.Hold);
				tahaGUI().SameLine(SAME_LINE_2);
				HotsKey("Button##Esp", BindEnable.Button);
			}

			tahaGUI().Spacing();
			tahaGUI().Separator();
			tahaGUI().Spacing();

			tahaGUI().PushItemWidth(PUSH_1);

			DCheckBox("Box", BoxEnable);
			if (BoxEnable)
			{
				tahaGUI().SameLine(SAME_LINE_1);
				tahaGUI().PushItemWidth(PUSH_1);
				VectorEx<const char*>itemsBS = { lolc("Full") , lolc("Angular"), lolc("3D"), lolc("Circled") };
				DComboBox("Style##Box", BoxStyle, itemsBS);
				if (BoxStyle != 2)
				{
					tahaGUI().Spacing();
					tahaGUI().PushItemWidth(PUSH_2);
					SliderInts("Size##Box", BoxSize, 1, 20);
				}
				tahaGUI().PushItemWidth(PUSH_1);
				tahaGUI().Spacing();
				DCheckBox("Outline##Box", BoxOutline);
				tahaGUI().Spacing();

				DColorEdit("CT color##Box", BoxCT);
				tahaGUI().SameLine(100);
				DColorEdit("T color##Box", BoxTT);

				tahaGUI().SameLine(200);

				DColorEdit("Visible CT color##Box", BoxVisibleCT);
				tahaGUI().SameLine(340);
				DColorEdit("Visible T color##Box", BoxVisibleTT);
			}

			tahaGUI().Spacing();
			tahaGUI().Separator();
			tahaGUI().Spacing();

			DCheckBox("Fill box", FillBox);
			if (FillBox)
			{
				tahaGUI().SameLine(SAME_LINE_2);
				DColorEdit("Color##fillbox", FillBoxColor);
			}

			tahaGUI().Spacing();
			tahaGUI().Separator();
			tahaGUI().Spacing();

			DCheckBox("Chams", Chams);
			if (Chams)
			{
				tahaGUI().SameLine(SAME_LINE_1);
				tahaGUI().PushItemWidth(PUSH_1);
				VectorEx<const char*>itemsCSVis = { lolc("Textured"), lolc("Flat"), lolc("Metallic"), lolc("Metallic Plus"), lolc("Pearlescent"), lolc("Animated") };
				DComboBox("Style##Chams", ChamsStyle, itemsCSVis);
				tahaGUI().SameLine(SAME_LINE_1 + PUSH_1 + 40);
				DCheckBox("Visible only##Chams", ChamsVisibleOnly);
				tahaGUI().Spacing();
				tahaGUI().SameLine(SAME_LINE_1);
				tahaGUI().PushItemWidth(PUSH_1);
				VectorEx<const char*>itemsCSd = { lolc("None"), lolc("Wireframe")};
				DComboBox("Double##Chams", ChamsDouble, itemsCSd);

				DColorEdit("CT color##Chams", ChamsCT);
				tahaGUI().SameLine(100);
				DColorEdit("T color##Chams", ChamsTT);
				tahaGUI().SameLine(200);
				DColorEdit("Visible CT color##Chams", ChamsVisibleCT);
				tahaGUI().SameLine(340);
				DColorEdit("Visible T color##Chams", ChamsVisibleTT);
			}

			tahaGUI().Spacing();
			tahaGUI().Separator();
			tahaGUI().Spacing();

			DCheckBox("Glow", Glow)
				if (Glow)
				{
					tahaGUI().SameLine(SAME_LINE_1);
					tahaGUI().PushItemWidth(PUSH_1);
					VectorEx<const char*>itemsCS = { lolc("Default"), lolc("Static pulse"), lolc("Dynamic pulse") };
					DComboBox("Style##Glow", GlowStyle, itemsCS);
					tahaGUI().SameLine(SAME_LINE_1 + PUSH_1 + 40);
					DCheckBox("Visible only##Glow", GlowVisibleOnly);

					DColorEdit("CT color##Glow", GlowCT);
					tahaGUI().SameLine(100);
					DColorEdit("T color##Glow", GlowTT);
					tahaGUI().SameLine(200);
					DColorEdit("Visible CT color##Glow", GlowVisibleCT);
					tahaGUI().SameLine(340);
					DColorEdit("Visible T color##Glow", GlowVisibleTT);
					if (GlowStyle == 2)
					{
						tahaGUI().PushItemWidth(PUSH_2);
						SliderInts("Speed", GlowPulseSpeed, 1, 15);
						SliderFloats("Range", GlowPulseRange, 0.1, 1, "%.2f");
					}
				}

			tahaGUI().Spacing();
			tahaGUI().Separator();
			tahaGUI().Spacing();

			DCheckBox("Health", Health);
			tahaGUI().SameLine(SAME_LINE_1);
			DCheckBox("Armor", Armor);
			tahaGUI().Spacing();
			tahaGUI().Separator();
			tahaGUI().Spacing();
			DCheckBox("Name", Name);
			DCheckBox("Distance", Distance);
			DCheckBox("Weapon", Weapon);
			tahaGUI().SameLine(SAME_LINE_1);
			DCheckBox("Ammo", Ammo);
			DCheckBox("Money", Money);
			tahaGUI().Spacing();
			tahaGUI().Separator();
			tahaGUI().Spacing();
			DCheckBox("Flashed", Flashing);
			tahaGUI().SameLine(SAME_LINE_1);
			DCheckBox("Defusing", Defusing);
			tahaGUI().SameLine(SAME_LINE_2);
			DCheckBox("Scoped", Scope);
			tahaGUI().Spacing();
			tahaGUI().Separator();
			tahaGUI().Spacing();

			DCheckBox("Head", HeadEsp);
			if (HeadEsp)
			{
				tahaGUI().SameLine(SAME_LINE_1);
				DColorEdit("Color##head", HeadEspColor);
			}

			DCheckBox("Line", Line);
			if (Line)
			{
				tahaGUI().SameLine(SAME_LINE_1);
				DColorEdit("Color##line", LineColor);
			}

			DCheckBox("Skeleton", Skeleton);
			if (Skeleton)
			{
				tahaGUI().SameLine(SAME_LINE_1);
				DColorEdit("Color##skel", SkeletonColor);
			}
			tahaGUI().Spacing();
			tahaGUI().Separator();
			tahaGUI().Spacing();
			DCheckBox("Sound Esp", SoundEspEnable);
			if (SoundEspEnable)
			{
				tahaGUI().SameLine(SAME_LINE_1);
				DColorEdit("Color##Sound", SoundColor);
				tahaGUI().SameLine(200);
				VectorEx<const char*>itemsSE = { lolc("Circle") , lolc("Dynamic Circle(+)"), lolc("Dynamic Circle(-)"), lolc("Box"),lolc("Filled Box"), lolc("Star") };
				tahaGUI().PushItemWidth(PUSH_1);
				DComboBox("Style##Sound", SoundEspStyle, itemsSE);

				tahaGUI().Spacing();
				tahaGUI().PushItemWidth(PUSH_2);
				SliderInts("Size##Sound", SoundEspSize, 1, 100);
				tahaGUI().PushItemWidth(PUSH_1);
				tahaGUI().Spacing();
				DCheckBox("Distance Text##sound", SoundEspDistance);
				if (SoundEspDistance)
				{
					tahaGUI().SameLine(SAME_LINE_2);
					DColorEdit("Color##SoundDistance", SoundDistanceColor);

					tahaGUI().PushItemWidth(PUSH_2);
					SliderInts("Text Size##Sound", TextSoundSize, 9, MAX_FONT_SIZE);

				}
			}
		}
	};
	LMenu();
}

#define iText(text)

void CEsp::VisualPreview()
{
	static MoveStruct *MV_Hp = &MVItemList[MI_HEALTH_BAR];
	static MoveStruct *MV_Armor = &MVItemList[MI_ARMOR_BAR];
	static MoveStruct *MV_Hp_Text = &MVItemList[MI_HEALTH_TEXT];
	static MoveStruct *MV_Armor_Text = &MVItemList[MI_ARMOR_TEXT];
	static MoveStruct *MV_Name = &MVItemList[MI_NAME_TEXT];
	static MoveStruct *MV_Weapon = &MVItemList[MI_WEAPON_TEXT];
	static MoveStruct *MV_Ammo = &MVItemList[MI_AMMO_TEXT];
	static MoveStruct *MV_Distance = &MVItemList[MI_DISTANCE_TEXT];
	static MoveStruct *MV_Money = &MVItemList[MI_MONEY_TEXT];
	static MoveStruct *MV_Scope = &MVItemList[MI_SCOPE_TEXT];
	static MoveStruct *MV_Flashed = &MVItemList[MI_FLASHED_TEXT];
	static MoveStruct *MV_Defusing = &MVItemList[MI_DEFUSING_TEXT];

	Vec2 ZoneStartPos = tahaGUI().GetCursorPosEx();

	CustomVisuals(ZoneStartPos);

	if ((MITypes)MoveStruct::LastActive == MI_AMMO_TEXT)
	{
		iText("Selected: Ammo");

		tahaGUI().Spacing();
		tahaGUI().Separator();
		tahaGUI().Spacing();
		VectorEx<const char*>itemsGS = { lolc("Type 1") ,lolc("Type 2"), lolc("Type 3") };
		DComboBox("Style", AmmoStyle, itemsGS);
		tahaGUI().Spacing();
		tahaGUI().Separator();
		tahaGUI().Spacing();
		SliderInts("Text size", TextAmmoSize, 9, MAX_FONT_SIZE);
		tahaGUI().Spacing();
		tahaGUI().Separator();
		tahaGUI().Spacing();
		DColorEdit("Color", AmmoColor);
	}
	else if ((MITypes)MoveStruct::LastActive == MI_ARMOR_TEXT)
	{
		iText("Selected: Armor");

		tahaGUI().Spacing();
		tahaGUI().Separator();
		tahaGUI().Spacing();

		int OldStyle = ArmorStyle;

		VectorEx<const char*>NumStyle = { lolc("Line") , lolc("Text") };

		DComboBox("Style", ArmorStyle, NumStyle);
		tahaGUI().Spacing();
		tahaGUI().Separator();
		tahaGUI().Spacing();
		SliderInts("Text size", TextArmorSize, 9, MAX_FONT_SIZE);

		if (OldStyle != ArmorStyle)
			MoveStruct::LastActive = MI_ARMOR_BAR;

		tahaGUI().Spacing();
		tahaGUI().Separator();
		tahaGUI().Spacing();
		DColorEdit("Color", ArmorColor);
	}
	else if ((MITypes)MoveStruct::LastActive == MI_ARMOR_BAR)
	{
		iText("Selected: Armor");

		tahaGUI().Spacing();
		tahaGUI().Separator();
		tahaGUI().Spacing();

		int OldStyle = ArmorStyle;

		VectorEx<const char*>NumStyle = { lolc("Line") , lolc("Text") };

		DComboBox("Style", ArmorStyle, NumStyle);


		if (OldStyle != ArmorStyle)
			MoveStruct::LastActive = MI_ARMOR_TEXT;

		tahaGUI().Spacing();
		tahaGUI().Separator();
		tahaGUI().Spacing();

		DColorEdit("Main color", ArmorColor);
		DColorEdit("Background color", ArmorColor2);
		DColorEdit("Outline color", ArmorColor3);

		tahaGUI().Spacing();
		tahaGUI().Separator();
		tahaGUI().Spacing();

		SliderInts("Separators", MV_Armor->NumParam1, 0, 10);
		SliderInts("Tickness", MV_Armor->NumParam2, 0, 20);

		tahaGUI().Spacing();
		tahaGUI().Separator();
		tahaGUI().Spacing();
		DCheckBox("Background", MV_Armor->boolParam1);
		tahaGUI().SameLine();
		DCheckBox("Outline", MV_Armor->boolParam2);
		tahaGUI().SameLine();
		DCheckBox("Inverse", MV_Armor->boolParam3);
	}
	else if ((MITypes)MoveStruct::LastActive == MI_DISTANCE_TEXT)
	{
		iText("Selected: Selected");
		tahaGUI().Spacing();
		tahaGUI().Separator();
		tahaGUI().Spacing();

		SliderInts("Text size", TextDistanceSize, 9, MAX_FONT_SIZE);
		tahaGUI().Spacing();
		tahaGUI().Separator();
		tahaGUI().Spacing();
		DColorEdit("Color", DistanceColor);
	}
	else if ((MITypes)MoveStruct::LastActive == MI_HEALTH_TEXT)
	{
		iText("Selected: Health");

		tahaGUI().Spacing();
		tahaGUI().Separator();
		tahaGUI().Spacing();

		VectorEx<const char*>NumStyle = { lolc("Line"), lolc("Text") };

		int OldStyle = HealthStyle;

		DComboBox("Style", HealthStyle, NumStyle);
		tahaGUI().Spacing();
		tahaGUI().Separator();
		tahaGUI().Spacing();
		SliderInts("Text size", TextHealthSize, 9, MAX_FONT_SIZE);

		if (OldStyle != HealthStyle)
			MoveStruct::LastActive = MI_HEALTH_BAR;

		tahaGUI().Spacing();
		tahaGUI().Separator();
		tahaGUI().Spacing();
		DColorEdit("Color", HealthColor);
	}
	else if ((MITypes)MoveStruct::LastActive == MI_HEALTH_BAR)
	{
		iText("Selected: Health");

		tahaGUI().Spacing();
		tahaGUI().Separator();
		tahaGUI().Spacing();

		VectorEx<const char*>NumStyle = { lolc("Line"), lolc("Text") };

		int OldStyle = HealthStyle;

		DComboBox("Style", HealthStyle, NumStyle);

		if (OldStyle != HealthStyle)
			MoveStruct::LastActive = MI_HEALTH_TEXT;

		tahaGUI().Spacing();
		tahaGUI().Separator();
		tahaGUI().Spacing();

		DColorEdit("Main Color", HealthColor);
		DColorEdit("Background Color", HealthColor2);
		DColorEdit("Outline Color", HealthColor3);
		tahaGUI().Spacing();
		tahaGUI().Separator();
		tahaGUI().Spacing();

		SliderInts("Separators", MV_Hp->NumParam1, 0, 10);
		SliderInts("Tickness", MV_Hp->NumParam2, 0, 20);

		tahaGUI().Spacing();
		tahaGUI().Separator();
		tahaGUI().Spacing();
		DCheckBox("Background", MV_Hp->boolParam1);
		tahaGUI().SameLine();
		DCheckBox("Outline", MV_Hp->boolParam2);
		tahaGUI().SameLine();
		DCheckBox("Inverse", MV_Hp->boolParam3);
	}
	else if ((MITypes)MoveStruct::LastActive == MI_NAME_TEXT)
	{
		iText("Selected: Name");

		tahaGUI().Spacing();
		tahaGUI().Separator();
		tahaGUI().Spacing();

		SliderInts("Text size", TextNameSize, 9, MAX_FONT_SIZE);
		tahaGUI().Spacing();
		tahaGUI().Separator();
		tahaGUI().Spacing();
		DColorEdit("Color", NameColor);

		tahaGUI().Spacing();
		tahaGUI().Separator();
		tahaGUI().Spacing();

		DCheckBox("Background", NameBackground);

		tahaGUI().Spacing();
		tahaGUI().Separator();
		tahaGUI().Spacing();

		if (NameBackground)
		{
			tahaGUI().Spacing();
			DColorEdit("Background color", NameColorBack);
		}
	}
	else if ((MITypes)MoveStruct::LastActive == MI_WEAPON_TEXT)
	{
		iText("Selected: Weapon");
		tahaGUI().Spacing();
		tahaGUI().Separator();
		tahaGUI().Spacing();
		VectorEx<const char*>itemsGS = { lolc("Text"), lolc("Icon") };
		DComboBox("Style", WeaponStyle, itemsGS);
		tahaGUI().Spacing();
		tahaGUI().Separator();
		tahaGUI().Spacing();
		SliderInts("Text size", TextWeaponSize, 9, MAX_FONT_SIZE);
		tahaGUI().Spacing();
		tahaGUI().Separator();
		tahaGUI().Spacing();
		DColorEdit("Color", WeaponColor);
	}
	else if ((MITypes)MoveStruct::LastActive == MI_MONEY_TEXT)
	{
		iText("Selected: Money");
		tahaGUI().Spacing();
		tahaGUI().Separator();
		tahaGUI().Spacing();

		SliderInts("Text size", TextMoneySize, 9, MAX_FONT_SIZE);
		tahaGUI().Spacing();
		tahaGUI().Separator();
		tahaGUI().Spacing();
		DColorEdit("Color", MoneyColor);
	}
	else if ((MITypes)MoveStruct::LastActive == MI_SCOPE_TEXT)
	{
		iText("Selected: Scoped");
		tahaGUI().Spacing();
		tahaGUI().Separator();
		tahaGUI().Spacing();

		SliderInts("Text size", TextScopedSize, 9, MAX_FONT_SIZE);
		tahaGUI().Spacing();
		tahaGUI().Separator();
		tahaGUI().Spacing();
		DColorEdit("Color", ScopeColor);
	}
	else if ((MITypes)MoveStruct::LastActive == MI_FLASHED_TEXT)
	{
		iText("Selected: Flashed");
		tahaGUI().Spacing();
		tahaGUI().Separator();
		tahaGUI().Spacing();

		SliderInts("Text size", TextFlashedSize, 9, MAX_FONT_SIZE);
		tahaGUI().Spacing();
		tahaGUI().Separator();
		tahaGUI().Spacing();
		DColorEdit("Color", FlashingColor);

	}
	else if ((MITypes)MoveStruct::LastActive == MI_DEFUSING_TEXT)
	{
		iText("Selected: Defusing");
		tahaGUI().Spacing();
		tahaGUI().Separator();
		tahaGUI().Spacing();

		SliderInts("Text size", TextDefusingSize, 9, MAX_FONT_SIZE);
		tahaGUI().Spacing();
		tahaGUI().Separator();
		tahaGUI().Spacing();
		DColorEdit("Color", DefusingColor);
	}

	float long_item_w = tahaGUI().GetThis()->Info.Size.x - (tahaGUI().GetStyle().wndPadding.x * 2);
	tahaGUI().SetCursorPos(Vec2(tahaGUI().GetStyle().wndPadding.x, 638), 0);
	if (tahaGUI().Button(__xor("Reset"), Vec2(long_item_w, 22)))
		MoveStruct::InitMItems = false;
}




























































