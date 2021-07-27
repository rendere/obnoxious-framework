#include "Misc.h"
#include "../../GUI/Gui.h"

#define SAME_LINE_1 168

#define PUSH_1 200
#define PUSH_2 360
#define PUSH_3 240

void CMisc::Menu()
{
	DCheckBox("Bunny hop", BHop);
	if (BHop)
	{
		tahaGUI().SameLine(SAME_LINE_1);
		tahaGUI().PushItemWidth(PUSH_1);
		VectorEx<const char* >itemsCSS = { lolc("Default"), lolc("Legit") };
		DComboBox("Type##BHop", BHopType, itemsCSS);
		if (BHopType == 1)
		{
			tahaGUI().PushItemWidth(PUSH_2);
			SliderInts("Chance##LegitBHop", BHopChance, 0, 100);
			SliderInts("Hops limit##LegitBHop", BHopLimit, 0, 15);
			SliderInts("Max hops limit##LegitBHop", BHopMaxHit, 0, 15);

		}
		DCheckBox("Auto strafe", AutoStrafe);
		if (AutoStrafe)
		{
			tahaGUI().SameLine(SAME_LINE_1);
			tahaGUI().PushItemWidth(PUSH_1);
			SliderInts("Speed##AutoStrafe", AutoStrafeSpeed, 0, 15);
		}
	}
	tahaGUI().Spacing();
	tahaGUI().Separator();
	tahaGUI().Spacing();
	DCheckBox("Edge jump", EdgeJump);
	if (EdgeJump)
	{
		tahaGUI().SameLine(SAME_LINE_1);
		tahaGUI().PushItemWidth(PUSH_1);
		HotsKey("Button##edgejump", EdgeJumpBind.Button);
		tahaGUI().SameLine();
		DCheckBox("Hold##edgejump", EdgeJumpBind.Hold);
	}
	tahaGUI().Spacing();
	tahaGUI().Separator();
	tahaGUI().Spacing();
	DCheckBox("Jump bug", JumpBug);
	if (JumpBug)
	{
		tahaGUI().SameLine(SAME_LINE_1);
		tahaGUI().PushItemWidth(PUSH_1);
		HotsKey("Button##jumpbug", JumpBugBind.Button);
		tahaGUI().SameLine();
		DCheckBox("Hold##jumpbug", JumpBugBind.Hold);
	}
	tahaGUI().Spacing();
	tahaGUI().Separator();
	tahaGUI().Spacing();
	DCheckBox("Edge bug", EdgeBug);
	if (EdgeBug)
	{
		tahaGUI().SameLine(SAME_LINE_1);
		tahaGUI().PushItemWidth(PUSH_1);
		HotsKey("Button##edgebug", EdgeBugBind.Button);
		tahaGUI().SameLine();
		DCheckBox("Hold##edgebug", EdgeBugBind.Hold);
	}
	tahaGUI().Spacing();
	tahaGUI().Separator();
	tahaGUI().Spacing();
	DCheckBox("Opposite hand knife", LRHandKnife);
	tahaGUI().Spacing();
	tahaGUI().Separator();
	tahaGUI().Spacing();
	DCheckBox("Infinite crouch", InfiniteCrouch);
	tahaGUI().Spacing();
	tahaGUI().Separator();
	tahaGUI().Spacing();
	DCheckBox("Third person", ThirdPerson);
	if (ThirdPerson)
	{
		tahaGUI().SameLine(SAME_LINE_1);
		tahaGUI().PushItemWidth(PUSH_1);
		SliderInts("Distance##ThirdPerson", ThirdPersonDistance, 50, 300);
		tahaGUI().PushItemWidth(PUSH_1);
		HotsKey("Button##ThirdPerson", ThirdPersonBind.Button);
		tahaGUI().SameLine();
		DCheckBox("Hold##ThirdPerson", ThirdPersonBind.Hold);
	}
	tahaGUI().Spacing();
	tahaGUI().Separator();
	tahaGUI().Spacing();
	DCheckBox("Show competitive rank", ShowCompetitiveRank);
	tahaGUI().Spacing();
	tahaGUI().Separator();
	tahaGUI().Spacing();
	DCheckBox("Auto-accept matchmaking", AutoAccept);
	tahaGUI().Spacing();
	tahaGUI().Separator();
	tahaGUI().Spacing();
	DCheckBox("Override FOV", FovChanger);
	if (FovChanger)
	{
		tahaGUI().SameLine(SAME_LINE_1);
		tahaGUI().PushItemWidth(PUSH_1);
		SliderInts("FOV view", FovView, 1, 180);
	}
	tahaGUI().Spacing();
	tahaGUI().Separator();
	tahaGUI().Spacing();
	DCheckBox("Viewmodel FOV", FovModelChanger);
	if (FovModelChanger)
	{
		tahaGUI().SameLine(SAME_LINE_1);
		tahaGUI().PushItemWidth(PUSH_1);
		SliderInts("FOV model", FovModel, 1, 180);
	}
	tahaGUI().Spacing();
	tahaGUI().Separator();
	tahaGUI().Spacing();
	DCheckBox("Viewmodel XYZ", ViewModelXYZ);
	if (ViewModelXYZ)
	{
		tahaGUI().PushItemWidth(PUSH_2);
		SliderFloats("ViewModel X", ViewModelX, -30, 30);
		SliderFloats("ViewModel Y", ViewModelY, -30, 30);
		SliderFloats("ViewModel Z", ViewModelZ, -30, 30);
	}
	tahaGUI().Spacing();
	tahaGUI().Separator();
	tahaGUI().Spacing();
	DCheckBox("Aspect", Aspect);
	if (Aspect)
	{
		tahaGUI().PushItemWidth(PUSH_2);
		SliderInts("Width", AspectWidth, 1, CGlobal::iScreenWidth);
		SliderInts("Height", AspectHeight, 1, CGlobal::iScreenHeight);
	}
	tahaGUI().Spacing();
	tahaGUI().Separator();
	tahaGUI().Spacing();
	DCheckBox("No visual recoil", NoVisualRecoil);
	tahaGUI().Spacing();
	tahaGUI().Separator();
	tahaGUI().Spacing();
	DCheckBox("Free look", FreeCam);
	if (FreeCam)
	{
		tahaGUI().SameLine(SAME_LINE_1);
		tahaGUI().PushItemWidth(PUSH_1);
		SliderInts("Speed##frecam", FreeCamSpeed, 1, 40);

		HotsKey("Button##frcam", FreeCamBind.Button);
		tahaGUI().SameLine();
		DCheckBox("Hold##frcam", FreeCamBind.Hold);
	}
	tahaGUI().Spacing();
	tahaGUI().Separator();
	tahaGUI().Spacing();
	DCheckBox("Crosshair", Crosshair);
	if (Crosshair)
	{
		tahaGUI().SameLine(SAME_LINE_1);
		tahaGUI().PushItemWidth(PUSH_1);
		VectorEx<const char* >itemsCSS = { lolc("Type1") , lolc("Type2"), lolc("Type3") };
		DComboBox("Style##Crossh", CrosshairStyle, itemsCSS);

		tahaGUI().PushItemWidth(PUSH_2);
		SliderInts("Size##Crossh", CrosshairSize, 1, 100);

		DCheckBox("Recoil##Crossh", CrosshairRecoil);
		tahaGUI().SameLine(SAME_LINE_1);
		DCheckBox("Outline##Crossh", CrosshairOutline);

		DColorEdit("Color##Crossh", CrosshairColor);
	}
	tahaGUI().Spacing();
	tahaGUI().Separator();
	tahaGUI().Spacing();
	DCheckBox("Sniper crosshair", SnipCrosshair);
	if (SnipCrosshair)
	{
		tahaGUI().SameLine(SAME_LINE_1);

		tahaGUI().PushItemWidth(PUSH_1);
		VectorEx<const char* >itemsCSS = { lolc("Type 1") , lolc("Type 2"), lolc("Type 3") };
		DComboBox("Style##Crosshsnip", SnipCrosshairStyle, itemsCSS);

		tahaGUI().PushItemWidth(PUSH_2);
		if (SnipCrosshairStyle == 2)
		SliderInts("Size##Crosshsnip", SnipCrosshairSize, 1, 100);

		DCheckBox("Recoil##Crosshsnip", SnipCrosshairRecoil);
		tahaGUI().SameLine(SAME_LINE_1);
		if (SnipCrosshairStyle <= 1)
		DCheckBox("Outline##Crosshsnip", SnipCrosshairOutline);

		DColorEdit("Color##Crosshsnip", SnipCrosshairColor);
	}
	tahaGUI().Spacing();
	tahaGUI().Separator();
	tahaGUI().Spacing();
	DCheckBox("Spread circle", SpreadCircel);
	if (SpreadCircel)
	{
		DColorEdit("Color##spread", SpreadColor);
	}
	tahaGUI().Spacing();
	tahaGUI().Separator();
	tahaGUI().Spacing();
	DCheckBox("Hit marker", HitMarker);
	if (HitMarker)
	{
		tahaGUI().SameLine(SAME_LINE_1);
		tahaGUI().PushItemWidth(PUSH_3);
		SliderInts("Size##Hits", HitMarkerSize, 1, 10);
		tahaGUI().PushItemWidth(PUSH_2);
		SliderInts("Tickness##Hits", HitMarkerTickness, 1, 100);
		DColorEdit("Color##Hits", HitMarkerColor);
	}
	tahaGUI().Spacing();
	tahaGUI().Separator();
	tahaGUI().Spacing();
	DCheckBox("Hit marker sound", HitSound);
	if (HitSound)
	{
		if (!SoundList.empty())
		{
			tahaGUI().SameLine(SAME_LINE_1);
			tahaGUI().PushItemWidth(PUSH_1);

			VectorEx<const char*> itemsHSS;
			for (size_t i(0); i < SoundList.size(); i++)
			{
				itemsHSS.push_back(SoundList[i].c_str());
			}
			DComboBox("Style##Hts", HitSoundStyle, itemsHSS);
		}
	}
	tahaGUI().Spacing();
	tahaGUI().Separator();
	tahaGUI().Spacing();
	DCheckBox("Remove flashbang", AntiFlash);
	if (AntiFlash)
	{
		tahaGUI().SameLine(SAME_LINE_1);
		tahaGUI().PushItemWidth(PUSH_3);
		SliderInts("Alpha##flash", AntiFlashAlpha, 1, 255);
	}
	tahaGUI().Spacing();
	tahaGUI().Separator();
	tahaGUI().Spacing();
	DCheckBox("Remove smoke", NoSmoke);
	if (NoSmoke)
	{
		tahaGUI().SameLine(SAME_LINE_1);
		tahaGUI().PushItemWidth(PUSH_1);
		VectorEx<const char* >itemsCSS = { lolc("No draw"), lolc("Wireframe") };
		DComboBox("Type##NoSmoke", NoSmokeStyle, itemsCSS);
	}
	tahaGUI().Spacing();
	tahaGUI().Separator();
	tahaGUI().Spacing();
	DCheckBox("Name stealer", NameStealer);
	tahaGUI().Spacing();
	tahaGUI().Separator();
	tahaGUI().Spacing();
	DCheckBox("Clan tag spammer", ClanTagChanger);
	if (ClanTagChanger)
	{
		tahaGUI().SameLine(SAME_LINE_1);
		tahaGUI().PushItemWidth(PUSH_1);
		VectorEx<const char* >itemsCS = { lolc("None"),lolc("Static"), lolc("Dynamic 1"), lolc("Dynamic 2"), lolc("Dynamic 3"), lolc("Dynamic 4") };
		DComboBox("Type##ClanTag", ClanTagChangerStyle, itemsCS);
		static char ClanBuf[32] = { 0 };
		TextEdit("Text##ClanTag", ClanTagChangerText, ClanBuf, 32);
	}
	tahaGUI().Spacing();
	tahaGUI().Separator();
	tahaGUI().Spacing();
	DCheckBox("Hand chams", HandChams);
	if (HandChams)
	{
		tahaGUI().SameLine(SAME_LINE_1);
		tahaGUI().PushItemWidth(PUSH_1);
		VectorEx<const char* >itemsCS = { lolc("Textured"),lolc("Flat"), lolc("Metallic"), lolc("Metallic Plus"), lolc("Pearlescent"), lolc("Animated"), lolc("Disable") };
		DComboBox("Style##HandChams", HCStyle, itemsCS);
		if (HCStyle <= 5)
		{
			tahaGUI().Spacing();
			tahaGUI().SameLine(SAME_LINE_1);
			tahaGUI().PushItemWidth(PUSH_1);
			VectorEx<const char* >itemsCSd = { lolc("None"),lolc("Wireframe") };
			DComboBox("Double##HandChams", HCDouble, itemsCSd);
		}
		DColorEdit("Color##HandChams", HandChamsColor);
	}
	tahaGUI().Spacing();
	tahaGUI().Separator();
	tahaGUI().Spacing();
	DCheckBox("Hand glow", HandGlow);
	if (HandGlow)
	{
		tahaGUI().SameLine(SAME_LINE_1);
		tahaGUI().PushItemWidth(PUSH_1);
		VectorEx<const char*>itemsCS = { lolc("Default"), lolc("Static pulse"), lolc("Dynamic pulse") };
		DComboBox("Style##HandGlow", HGStyle, itemsCS);
		DColorEdit("Color##HandGlow", HandGlowColor);
		if (HGStyle == 2)
		{
			tahaGUI().PushItemWidth(PUSH_2);
			SliderInts("Speed##HandGlow", HGPSpeed, 1, 15);
			SliderFloats("Range##HandGlow", HGPRange, 0.1, 1)
		}
	}
	tahaGUI().Spacing();
	tahaGUI().Separator();
	tahaGUI().Spacing();
	DCheckBox("Weapon chams", WeaponChams);
	if (WeaponChams)
	{
		tahaGUI().SameLine(SAME_LINE_1);
		tahaGUI().PushItemWidth(PUSH_1);
		VectorEx<const char* >itemsCS = { lolc("Textured"),lolc("Flat"), lolc("Metallic"), lolc("Metallic Plus"), lolc("Pearlescent"), lolc("Animated"), lolc("Disable") };
		DComboBox("Style##WeaponChams", WCStyle, itemsCS);
		if (WCStyle <= 5)
		{
			tahaGUI().Spacing();
			tahaGUI().SameLine(SAME_LINE_1);
			tahaGUI().PushItemWidth(PUSH_1);
			VectorEx<const char* >itemsCSd = { lolc("None"),lolc("Wireframe") };
			DComboBox("Double##WeaponChams", WCDouble, itemsCSd);
		}
		DColorEdit("Color##WeaponChams", WeaponChamsColor);
	}
	tahaGUI().Spacing();
	tahaGUI().Separator();
	tahaGUI().Spacing();
	DCheckBox("Weapon glow", WeaponGlow);
	if (WeaponGlow)
	{
		tahaGUI().SameLine(SAME_LINE_1);
		tahaGUI().PushItemWidth(PUSH_1);
		VectorEx<const char*>itemsCS = { lolc("Default"), lolc("Static pulse"), lolc("Dynamic pulse") };
		DComboBox("Style##WeaponGlow", WGStyle, itemsCS);
		DColorEdit("Color##WeaponGlow", WeaponGlowColor);
		if (WGStyle == 2)
		{
			tahaGUI().PushItemWidth(PUSH_2);
			SliderInts("Speed##WeaponGlow", WGPSpeed, 1, 15);
			SliderFloats("Range##WeaponGlow", WGPRange, 0.1, 1)
		}
	}
	tahaGUI().Spacing();
	tahaGUI().Separator();
	tahaGUI().Spacing();
	DCheckBox("Damage info", DamageInfo);
	if (DamageInfo)
	{
		tahaGUI().SameLine(SAME_LINE_1);

		tahaGUI().PushItemWidth(PUSH_1);
		tahaGUI().PushItemWidth(PUSH_1);
		VectorEx<const char* >itemsCS = { lolc("On screen") , lolc("In world") };
		DComboBox("Position##damage", DamageInfoPosition, itemsCS);
		tahaGUI().Spacing();
		tahaGUI().SameLine(SAME_LINE_1);
		tahaGUI().PushItemWidth(PUSH_1);
		tahaGUI().PushItemWidth(PUSH_1);
		VectorEx<const char* >itemsDSS = { lolc("Damage"), lolc("Health") };
		DComboBox("Style##damage", DamageInfoStyle, itemsDSS);
		tahaGUI().PushItemWidth(PUSH_2);
		SliderInts("Text Size##damage", TextDamageInfo, 9, MAX_FONT_SIZE);
		if (DamageInfoPosition == 0)
		{
			SliderFloats("Show Time##damage", DamageInfoShowTime, 0.1, 10);
			SliderInts("Position X##damage", DamageInfoPosX, 1, CGlobal::iScreenWidth);
			SliderInts("Position Y##damage", DamageInfoPosY, 1, CGlobal::iScreenHeight);
		}
		else if (DamageInfoPosition == 1)
		{
			SliderInts("Height##damage", DamageInfoHeight, 1, 100);
			SliderInts("Speed##damage", DamageInfoSpeed, 1, 100);
		}
		DColorEdit("Color##damage", DamageInfoColor);
	}
	tahaGUI().Spacing();
	tahaGUI().Separator();
	tahaGUI().Spacing();
	DCheckBox("Knifebot", KnifeBot);
	if (KnifeBot)
	{
		tahaGUI().SameLine(SAME_LINE_1);
		tahaGUI().PushItemWidth(PUSH_1);
		SliderInts("Distance##knfb", KnifeBotDistance, 1, 100);
		tahaGUI().Spacing();
		tahaGUI().SameLine(SAME_LINE_1);
		tahaGUI().PushItemWidth(PUSH_1);
		VectorEx<const char* >itemsKNF = { lolc("All"), lolc("Team"), lolc("Enemy") };
		DComboBox("Attack##knfb", KnifeBotFilter, itemsKNF);
		tahaGUI().PushItemWidth(PUSH_2);
		VectorEx<const char* >itemsKNFM = { lolc("Auto"), lolc("Left, right"), lolc("Right"), lolc("Left") };
		DComboBox("Mode##knfb", KnifeBotMode, itemsKNFM);

		DCheckBox("Bind##knfb", KnifeBotBind.Enable);
		if (KnifeBotBind.Enable)
		{
			tahaGUI().SameLine(SAME_LINE_1);
			DCheckBox("Hold##knfb", KnifeBotBind.Hold);
			tahaGUI().PushItemWidth(PUSH_2);
			HotsKey("Button##knfb", KnifeBotBind.Button);
		}
	}
}




























































