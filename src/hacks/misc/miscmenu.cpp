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

	DCheckBox("Slow Walk", SlowWalk);
	if (SlowWalk)
	{
		tahaGUI().SameLine(SAME_LINE_1);
		tahaGUI().PushItemWidth(PUSH_1);
		HotsKey("Button##slowwalk", SlowWalkBind.Button);
		tahaGUI().SameLine();
	DCheckBox("Hold##slowwalk", SlowWalkBind.Hold);
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
	DCheckBox("Show competitive rank", ShowCompetitiveRank);
	tahaGUI().Spacing();
	tahaGUI().Separator();
	tahaGUI().Spacing();
	DCheckBox("Auto-accept matchmaking", AutoAccept);
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