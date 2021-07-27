#include "aimbot.h"
#include "../../GUI/Gui.h"

#define GetWeap(a) ((a < 0) ? 0 : (a >= GP_LegitAim->Weapons.size() ? GP_LegitAim->Weapons.size()-1 : a))

void CAimbot::Menu()
{
	if (SelectedWeapon == -1)
		SelectedWeapon = 0;

	if (SelectedWeapon >= (int)Weapons.size())
		SelectedWeapon = 0;

	DCheckBox("Enabled", Enable);

	float long_item_w = tahaGUI().GetThis()->Info.Size.x - (tahaGUI().GetStyle().wndPadding.x * 2);
	VectorEx<const char*> CustomTypes = { lolc("One weapon"),lolc("Standard subsections") , lolc("Custom subsections"), lolc("All weapons") };

	static int old_type = WeaponCustomTypes;
	tahaGUI().SameLine(126);
	tahaGUI().PushItemWidth(194);
	DComboBox("##pods", WeaponCustomTypes, CustomTypes);

	if (old_type != WeaponCustomTypes)
		SetSelectedWeapon(false);

	old_type = WeaponCustomTypes;

	string A_WeaponList_L = __xor("Weapon list");
	string A_Subsections_L = __xor("Subsections");

	if (WeaponCustomTypes == 0)
	{
		if (false)
			tahaGUI().SameLine(331);
		else
			tahaGUI().SameLine(351);

		if (tahaGUI().Button(ShowWeaponList ? (A_WeaponList_L + __xor(" <<<")).c_str() : (A_WeaponList_L + __xor(" >>>")).c_str()))
			ShowWeaponList = !ShowWeaponList;
	}
	else if (WeaponCustomTypes == 1 || WeaponCustomTypes == 2)
	{
		if (false)
			tahaGUI().SameLine(349);
		else
			tahaGUI().SameLine(355);

		if (tahaGUI().Button(ShowWeaponList ? (A_Subsections_L + __xor(" <<<")).c_str() : (A_Subsections_L + __xor(" >>>")).c_str()))
			ShowWeaponList = !ShowWeaponList;
	}
	else if (WeaponCustomTypes == 3)
	{
		ShowWeaponList = false;
	}

	tahaGUI().Spacing();

	if (tahaGUI().BeginChild(__xor("MainChild"), Vec2(0, 180), true))
	{
		VectorEx<const char*> AimP = { lolc("Page 1"), lolc("Page 2") };
		static int SubtabAimMiscSelected = 0;

		TabsLabels(SubtabAimMiscSelected, AimP, Vec2(long_item_w - 12, 0), false);
		if (SubtabAimMiscSelected == 0)
		{
			tahaGUI().Spacing();
			DCheckBox("Aim at teammates##LegitAim", Deathmatch);

			tahaGUI().SameLine(246);
			DCheckBox("Automatic fire##LegitAim", AutoFire);
			DCheckBox("Flash check##LegitAim", FlashCheck);

			tahaGUI().SameLine(246);
			DCheckBox("Jump check##LegitAim", JumpCheck);
			DCheckBox("Smoke check##LegitAim", SmokeCheck);
			tahaGUI().SameLine(246);
			DCheckBox("Enemy jump check##LegitAim", JumpEnemyCheck);

			tahaGUI().Spacing();
			tahaGUI().Spacing();
			tahaGUI().Spacing();
			tahaGUI().Separator();
			tahaGUI().Spacing();
			tahaGUI().Spacing();
			tahaGUI().Spacing();

			DCheckBox("Draw FOV", DrawFov);

			tahaGUI().SameLine(185.f);
			DColorEdit("Color##FovClr", FovColor);
			tahaGUI().SameLine(246);

			DCheckBox("Show target", ShowSpot);

			DCheckBox("Draw silent FOV", DrawSilentFov);

			tahaGUI().SameLine(185.f);
			DColorEdit("Color##SFovClr", SilentFovColor);

			tahaGUI().SameLine(246);

			DCheckBox("Wall Check", WallCheck);
			
			if (SelectedWeapon <= 9 || WeaponCustomTypes == 3 || WeaponCustomTypes == 2 || WeaponCustomTypes == 1)
			{
				DCheckBox("Automatic pistol", Weapons[GetWeap(SelectedWeapon)].AutoPistol);
			}
			if (SelectedWeapon >= 30 || WeaponCustomTypes == 3 || WeaponCustomTypes == 2 || WeaponCustomTypes)
			{
				DCheckBox("Fast zoom", Weapons[GetWeap(SelectedWeapon)].FastZoom);
				tahaGUI().SameLine(246);
				DCheckBox("Only Zoom", Weapons[GetWeap(SelectedWeapon)].OnlyZoom);
			}

		}
		else if (SubtabAimMiscSelected == 1)
		{
			tahaGUI().Spacing();
			DCheckBox("Aim bind", AimBind.Enable);
			if (AimBind.Enable)
			{
				tahaGUI().SameLine();
				DCheckBox("Hold", AimBind.Hold);
				tahaGUI().Spacing();
				HotsKey("Button", AimBind.Button);
			}
			tahaGUI().Spacing();
			tahaGUI().Separator();
			tahaGUI().Spacing();
			tahaGUI().PushItemWidth(250.f);
			DCheckBox("FACEIT Server AC", FaceIt);
			if (FaceIt)
			{
				tahaGUI().SameLine();
				SliderFloats("RCS fix", MouseSense, 0.0001, 8);
			}
			tahaGUI().PushItemWidth(379);
			tahaGUI().Spacing();
			tahaGUI().Separator();
			tahaGUI().Spacing();

			DCheckBox("Entity aim", EntityAim);
			if (EntityAim)
			{
				tahaGUI().SameLine();
				DCheckBox("Show entity name", ShowEntitysName);
				static char ModelN[64] = { 0 };
				TextEdit("Target entity name", EntityTargetName, ModelN, 64);
			}
		}
	}
	tahaGUI().EndChild();

	VectorEx<const char*> AimPSettings = { lolc("Basic"), lolc("RCS"), lolc("Silent"), lolc("Backtrack"), lolc("Delays") };

	TabsLabels(SubTabAimSelected, AimPSettings, Vec2(long_item_w - 9, 0), false);

	if (tahaGUI().BeginChild(__xor("Main2Child4"), Vec2(0, 200), true))
	{
		tahaGUI().PushItemWidth(369.f);

		if (SubTabAimSelected == 0)
		{
			VectorEx<const char*> itemsSM = { lolc("Constant smooth") , lolc("Variable smooth") };
			DComboBox("Smooth method", Weapons[GetWeap(SelectedWeapon)].SmoothMethod, itemsSM);

			VectorEx<const char*> itemsSMF = { lolc("Deceleration of speed") , lolc("Constant speed") };
			DComboBox("Smooth factor", Weapons[GetWeap(SelectedWeapon)].SmoothMoveFactor, itemsSMF);

			if (Weapons[GetWeap(SelectedWeapon)].SmoothMethod == 0)
			{
				SliderFloats("Smooth", Weapons[GetWeap(SelectedWeapon)].Smooth, 0, 100);
			}
			else if (Weapons[GetWeap(SelectedWeapon)].SmoothMethod == 1)
			{
				SliderFloats("Start Smooth", Weapons[GetWeap(SelectedWeapon)].StartAcceleration, 1, 100);
				SliderFloats("End Smooth", Weapons[GetWeap(SelectedWeapon)].EndAcceleration, 1, 100);
			}

			tahaGUI().Spacing();
			tahaGUI().Separator();
			tahaGUI().Spacing();

			SliderFloats("Fov", Weapons[GetWeap(SelectedWeapon)].Fov, 0, 300);

			VectorEx<const char*> itemsFP = { lolc("Screen center") , lolc("Recoil"), lolc("On player") };
			DComboBox("FOV Pos", Weapons[GetWeap(SelectedWeapon)].FovPos, itemsFP);

			if (!EntityAim)
			{
				tahaGUI().Spacing();
				tahaGUI().Separator();
				tahaGUI().Spacing();

				DCheckBox("Nearest", Weapons[GetWeap(SelectedWeapon)].Nearest);

				if (!Weapons[GetWeap(SelectedWeapon)].Nearest)
				{
					VectorEx<const char*> itemsHB = { lolc("Head"), lolc("Neck"), lolc("Low neck"), 
						lolc("Body"), lolc("Thorax"), lolc("Chest") };
					DComboBox("Hitbox", Weapons[GetWeap(SelectedWeapon)].HitBox, itemsHB);
				}
			}
		}
		else if (SubTabAimSelected == 1)
		{
			SliderFloats("RCS X", Weapons[GetWeap(SelectedWeapon)].RcsY, 0, 150);
			SliderFloats("RCS Y", Weapons[GetWeap(SelectedWeapon)].RcsX, 0, 150);

			tahaGUI().Spacing();
			tahaGUI().Separator();
			tahaGUI().Spacing();

			SliderFloats("Smooth", Weapons[GetWeap(SelectedWeapon)].SmoothRcs, 0, 100);
			SliderFloats("FOV", Weapons[GetWeap(SelectedWeapon)].FovRcs, 0, 300);

			tahaGUI().Spacing();
			tahaGUI().Separator();
			tahaGUI().Spacing();

			SliderInts("Start bullet##RCS", Weapons[GetWeap(SelectedWeapon)].RcsStartBullet, 0, 100);
			SliderInts("End bullet##RCS", Weapons[GetWeap(SelectedWeapon)].RcsEndBullet, 0, 100);

			tahaGUI().Spacing();
			tahaGUI().Separator();
			tahaGUI().Spacing();

			DCheckBox("Standalone RCS", Weapons[GetWeap(SelectedWeapon)].RcsStandelone);

			if (!EntityAim)
			{
				tahaGUI().Spacing();
				tahaGUI().Separator();
				tahaGUI().Spacing();

				DCheckBox("Hitbox after first bullet", Weapons[GetWeap(SelectedWeapon)].HitBoxAfter1B);

				if (Weapons[GetWeap(SelectedWeapon)].HitBoxAfter1B)
				{
					DCheckBox("Nearest RCS", Weapons[GetWeap(SelectedWeapon)].NearestRcs);

					if (!Weapons[GetWeap(SelectedWeapon)].NearestRcs)
					{
						VectorEx<const char*> itemsHB = { lolc("Head"), lolc("Neck"), lolc("Low neck"),
							lolc("Body"), lolc("Thorax"), lolc("Chest") };
						DComboBox("Hitbox", Weapons[GetWeap(SelectedWeapon)].HitBoxRcs, itemsHB);
					}
				}
			}
			tahaGUI().PushItemWidth(333.f);
		}
		else if (SubTabAimSelected == 2)
		{
			if (!FaceIt)
			{
				DCheckBox("Silent", Weapons[GetWeap(SelectedWeapon)].Silent);

				SliderInts("% chance", Weapons[GetWeap(SelectedWeapon)].SilentHitchance, 0, 100);
				SliderFloats("FOV", Weapons[GetWeap(SelectedWeapon)].SilentFov, 0, 30,);

				tahaGUI().Spacing();
				tahaGUI().Separator();
				tahaGUI().Spacing();

				SliderInts("Start bullet##Silent", Weapons[GetWeap(SelectedWeapon)].SilentStartBullet, 0, 100);
				SliderInts("End bullet##Silent", Weapons[GetWeap(SelectedWeapon)].SilentEndBullet, 0, 100);

				if (!EntityAim)
				{
					tahaGUI().Spacing();
					tahaGUI().Separator();
					tahaGUI().Spacing();

					DCheckBox("Nearest", Weapons[GetWeap(SelectedWeapon)].SilentNearest);

					if (!Weapons[GetWeap(SelectedWeapon)].SilentNearest)
					{
						VectorEx<const char*> itemsHB = { lolc("Head"), lolc("Neck"), lolc("Low neck"),
							lolc("Body"), lolc("Thorax"), lolc("Chest") };
						DComboBox("Hitbox", Weapons[GetWeap(SelectedWeapon)].SilentHitBox, itemsHB);
					}

					tahaGUI().Spacing();
					tahaGUI().Spacing();
				}
			}
		}
		else if (SubTabAimSelected == 3)
		{
			if (!FaceIt)
			{
				DCheckBox("Backtrack", Weapons[GetWeap(SelectedWeapon)].Backtrack);
				tahaGUI().SameLine();
				DCheckBox("Ignore smoke##Backtrack", Weapons[GetWeap(SelectedWeapon)].BacktrackIgnoreSmoke);

				SliderInts("Time (Ms)##Backtrack", Weapons[GetWeap(SelectedWeapon)].BacktrackTimeLimit, 0, 200);

				tahaGUI().Spacing();
				tahaGUI().Separator();
				tahaGUI().Spacing();
				DCheckBox("Show Backtrack", ShowBacktrack);
				if (ShowBacktrack)
				{
					tahaGUI().SameLine();
					DCheckBox("Visible Only##ShowBacktrack", SBVisibleOnly);

					VectorEx<const char*> itemsSBT = { lolc("All Ticks"), lolc("Last Tick") };
					DComboBox("Tick##ShowBacktrack", SBTick, itemsSBT);

					VectorEx<const char*>itemsSBS = { lolc("Textured"), lolc("Flat"), lolc("Metallic"), lolc("Metallic Plus"), lolc("Pearlescent"), lolc("Animated") };
					DComboBox("Style##ShowBacktrack", SBStyle, itemsSBS);

					VectorEx<const char*>itemsSBD = { lolc("None"), lolc("Wireframe") };
					DComboBox("Double##ShowBacktrack", SBDouble, itemsSBD);

					DColorEdit("Color##ShowBacktrack", ShowBactrackColor);
				}
			}
		}
		else if (SubTabAimSelected == 4)
		{
			DCheckBox("Target switch delay", Weapons[GetWeap(SelectedWeapon)].TargetSwitchDelayEnable);

			if (Weapons[GetWeap(SelectedWeapon)].TargetSwitchDelayEnable)
				SliderFloats("Delay##tsw", Weapons[GetWeap(SelectedWeapon)].TargetSwitchDelay, 0, 1.f);

			tahaGUI().Spacing();
			tahaGUI().Separator();
			tahaGUI().Spacing();

			DCheckBox("First bullet delay", Weapons[GetWeap(SelectedWeapon)].FirstFireDelayEnable);

			if (Weapons[GetWeap(SelectedWeapon)].FirstFireDelayEnable)
			{
				DCheckBox("One click delay", Weapons[GetWeap(SelectedWeapon)].FirstFireDelayOneClick);

				if (!EntityAim)
				{
					tahaGUI().SameLine();
					DCheckBox("Auto", Weapons[GetWeap(SelectedWeapon)].FirstFireDelayAuto);
				}

				if (!FaceIt)
				{
					tahaGUI().SameLine();
					DCheckBox("Silent auto delay", Weapons[GetWeap(SelectedWeapon)].FirstFireDelaySilentAuto);
				}

				SliderFloats("Delay##ffdef", Weapons[GetWeap(SelectedWeapon)].FirstFireDelay, 0, 1.f);
			}

			tahaGUI().Spacing();
			tahaGUI().Separator();
			tahaGUI().Spacing();

			DCheckBox("Kill stop", Weapons[GetWeap(SelectedWeapon)].KillStop);
		}
	}
	tahaGUI().EndChild();

	tahaGUI().Spacing();
	tahaGUI().Spacing();
	tahaGUI().Spacing();
	
	if (tahaGUI().BeginChild(__xor("TriggerChild"), Vec2(0, 215), true))
	{
		static int SubtabTrigMiscSelected = 0;

		VectorEx<const char*> AimTrigSettings = { lolc("Basic##trigger"),  lolc("Bind##trigger") };

		TabsLabels(SubtabTrigMiscSelected, AimTrigSettings, Vec2(long_item_w - 12, 0), false);

		tahaGUI().Spacing();
		tahaGUI().PushItemWidth(240.f);

		if (SubtabTrigMiscSelected == 0)
		{
			DCheckBox("Trigger", TriggerEnable);
			tahaGUI().SameLine(163);
			DCheckBox("Aim at teammates", TriggerDeathmatch);

			tahaGUI().SameLine(360);
			tahaGUI().BeginGroup();
			{
				vector<string> TrigHitboxes =
				{
					lols("Head"), //0
					lols("Chest"), //1
					lols("Stomach"), //2
					lols("Left arm"), //3
					lols("Right arm"), //4
					lols("Left leg"), //5
					lols("Right leg") //6
				};
				if (tahaGUI().ListBoxHeader("##TrigHitboxes", Vec2(90, 142)))
				{
					for (int i = 0; i < 7; i++)
					{
						bool selected = ((i == 0) && Weapons[GetWeap(SelectedWeapon)].TRIG_HITGROUP_HEAD) ||
							((i == 1) && Weapons[GetWeap(SelectedWeapon)].TRIG_HITGROUP_CHEST) ||
							((i == 2) && Weapons[GetWeap(SelectedWeapon)].TRIG_HITGROUP_STOMACH) ||
							((i == 3) && Weapons[GetWeap(SelectedWeapon)].TRIG_HITGROUP_LEFTARM) ||
							((i == 4) && Weapons[GetWeap(SelectedWeapon)].TRIG_HITGROUP_RIGHTARM) ||
							((i == 5) && Weapons[GetWeap(SelectedWeapon)].TRIG_HITGROUP_LEFTLEG) ||
							((i == 6) && Weapons[GetWeap(SelectedWeapon)].TRIG_HITGROUP_RIGHTLEG);

						if (tahaGUI().SelectLabel(TrigHitboxes.at(i).c_str(), selected))
						{
							switch (i)
							{
							case 0: Weapons[GetWeap(SelectedWeapon)].TRIG_HITGROUP_HEAD = !Weapons[GetWeap(SelectedWeapon)].TRIG_HITGROUP_HEAD; break;
							case 1: Weapons[GetWeap(SelectedWeapon)].TRIG_HITGROUP_CHEST = !Weapons[GetWeap(SelectedWeapon)].TRIG_HITGROUP_CHEST; break;
							case 2: Weapons[GetWeap(SelectedWeapon)].TRIG_HITGROUP_STOMACH = !Weapons[GetWeap(SelectedWeapon)].TRIG_HITGROUP_STOMACH; break;
							case 3: Weapons[GetWeap(SelectedWeapon)].TRIG_HITGROUP_LEFTARM = !Weapons[GetWeap(SelectedWeapon)].TRIG_HITGROUP_LEFTARM; break;
							case 4: Weapons[GetWeap(SelectedWeapon)].TRIG_HITGROUP_RIGHTARM = !Weapons[GetWeap(SelectedWeapon)].TRIG_HITGROUP_RIGHTARM; break;
							case 5: Weapons[GetWeap(SelectedWeapon)].TRIG_HITGROUP_LEFTLEG = !Weapons[GetWeap(SelectedWeapon)].TRIG_HITGROUP_LEFTLEG; break;
							case 6: Weapons[GetWeap(SelectedWeapon)].TRIG_HITGROUP_RIGHTLEG = !Weapons[GetWeap(SelectedWeapon)].TRIG_HITGROUP_RIGHTLEG; break;
							default: break;
							}
						}
					}
				}
				tahaGUI().ListBoxFooter();

				DCheckBox("All", Weapons[GetWeap(SelectedWeapon)].TriggerAllHitboxes);
			}
			tahaGUI().EndGroup(true);

			DCheckBox("Flash check##Trigger", TriggerFlashCheck);
			tahaGUI().SameLine(163);
			DCheckBox("Smoke check##Trigger", TriggerSmokeCheck);
			DCheckBox("Jump check##Trigger", TriggerJumpCheck);
			tahaGUI().SameLine(163);
			DCheckBox("Enemy jump check##Trigger", TriggerJumpEnemyCheck);
			if (SelectedWeapon >= 30 || WeaponCustomTypes == 3 || WeaponCustomTypes == 2 || WeaponCustomTypes)
				DCheckBox("Only Zoom##Trigger", TriggerOnlyZoom);

			tahaGUI().Spacing();

			SliderInts("RCS X##Trigger", Weapons[GetWeap(SelectedWeapon)].TriggerRcsX, 0, 150);
			SliderInts("RCS Y##Trigger", Weapons[GetWeap(SelectedWeapon)].TriggerRcsY, 0, 150);

			tahaGUI().Spacing();

			SliderIntsProc("Hit chance##Trigger", Weapons[GetWeap(SelectedWeapon)].TriggerChanse, 0, 100);
			SliderFloats("Delay##Trigger", Weapons[GetWeap(SelectedWeapon)].TriggerDelay, 0, 1.f);
		}
		else if (SubtabTrigMiscSelected == 1)
		{
			DCheckBox("Bind##triggg", TriggerBind.Enable);
			if (TriggerBind.Enable)
			{
				tahaGUI().SameLine();
				DCheckBox("Hold##triggg", TriggerBind.Hold);
				HotsKey("Button##triggg", TriggerBind.Button);
			}
		}
	}
	tahaGUI().EndChild();
}

void CAimbot::SubsectionsMenu()
{
	if (WeaponCustomTypes == 0)
	{
		if (SelectedWeapon == -1)
			SelectedWeapon = 0;

		static int selectedItem = SelectedWeapon;
		if (tahaGUI().ListBoxHeader(__xor("##0"), Vec2(154, 665 - 7)))
		{
			for (int i = 0; i < (sizeof(CGlobal::WeaponNames) / sizeof(*CGlobal::WeaponNames)); i++)
			{
				bool selected = i == SelectedWeapon;
				if (tahaGUI().SelectLabel(CGlobal::WeaponNames[i].c_str(), selected, Vec2(144, 0)))
					SelectedWeapon = i;
			}
		}
		tahaGUI().ListBoxFooter();
	}
	else if (WeaponCustomTypes == 1)
	{
		static int tabOrderCs[] = { 0 , 1 , 2 , 3 };

		VectorEx<const char*>tabNamesCs = { lolsc("Rifles"), lolsc("Pistols"), lolsc("Shotguns"), lolsc("Snipers") };

		Vec2 Pos = Vec2(0, 0);

		TabsLabels(StandardSubSelected, tabNamesCs, Vec2(tahaGUI().GetCurWindowSize().x - (tahaGUI().GetStyle().wndPadding.x * 2),
			tahaGUI().GetCurWindowSize().y - (tahaGUI().GetStyle().wndPadding.y * 2)), true);


		if (StandardSubSelected == 0)
			SelectedWeapon = 34;
		else if (StandardSubSelected == 1)
			SelectedWeapon = 35;
		else if (StandardSubSelected == 2)
			SelectedWeapon = 36;
		else if (StandardSubSelected == 3)
			SelectedWeapon = 37;
	}
	else if (WeaponCustomTypes == 2)
	{
		static char NewSubName[64] = { 't','e','s','t' };

		tahaGUI().PushItemWidth(300);

		tahaGUI().InputText(__xor("Name"), NewSubName, 64);

		if (CustomSubs.size() < 33)
		{
			tahaGUI().SameLine(365);
			if (tahaGUI().Button(__xor("Add"), Vec2(89, 0)) && string(NewSubName).length() > 0)
			{
				CustomSub  CustomEntry;
				CustomEntry.Idx = Weapons.size();
				CustomEntry.Name = NewSubName;
				CustomEntry.Name += __xor("##") + to_string(CustomEntry.Idx);

				WeaponSettings WeaponEntry;
				WeaponEntry.WeaponName = CustomEntry.Name;
				WeaponEntry.IsCustomSub = true;

				CustomSubs.push_back(CustomEntry);
				Weapons.push_back(WeaponEntry);

				SelectedSub = CustomSubs.size() - 1;

				strcpy(NewSubName, "");
			}
		}

		if (SelectedSub < (int)CustomSubs.size() && SelectedSub >= 0)
		{
			if (tahaGUI().Button(__xor("Rename")))
			{
				if (string(NewSubName).length() > 0)
				{
					CustomSubs[SelectedSub].Name = NewSubName;
					strcpy(NewSubName, "");
				}
			}

			tahaGUI().SameLine();
			if (tahaGUI().Button(__xor("Remove")))
			{
				for (size_t i = 0; i < CustomSubs[SelectedSub].AllocatedWeapon.size(); i++)
					UnallocatedWeapons.push_back(CustomSubs[SelectedSub].AllocatedWeapon[i]);

				for (size_t i = 0; i < Weapons.size(); i++)
					if (i == CustomSubs[SelectedSub].Idx)
					{
						for (size_t j(SelectedSub); j < CustomSubs.size(); j++)
							CustomSubs[j].Idx--;
						Weapons.erase(Weapons.begin() + i);
					}

				CustomSubs.erase(CustomSubs.begin() + SelectedSub);
			}

			tahaGUI().Spacing();
			tahaGUI().Separator();
			tahaGUI().Spacing();

			if ((int)CustomSubs.size() <= SelectedSub)
				SelectedSub = CustomSubs.size() - 1;

			if (CustomSubs.size() > 0 && SelectedSub > -1)
			{
				if (SelectedSubAlloc < (int)CustomSubs[SelectedSub].AllocatedWeapon.size())
				{
					tahaGUI().SameLine(155);
					if (tahaGUI().Button(__xor(">>>"), Vec2(148, 0)))
					{
						UnallocatedWeapons.push_back(CustomSubs[SelectedSub].AllocatedWeapon[SelectedSubAlloc]);
						CustomSubs[SelectedSub].AllocatedWeapon.erase(CustomSubs[SelectedSub].AllocatedWeapon.begin() + SelectedSubAlloc);
						if (SelectedSubAlloc > 0)
							SelectedSubAlloc--;
					}
				}

				if ((int)UnallocatedWeapons.size() > 0 && SelectedSubUnAlloc < (int)UnallocatedWeapons.size() && SelectedSubUnAlloc >= 0)
				{
					tahaGUI().SameLine(310);
					if (tahaGUI().Button(__xor("<<<"), Vec2(144, 0)))
					{
						CustomSubs[SelectedSub].AllocatedWeapon.push_back(UnallocatedWeapons[SelectedSubUnAlloc]);
						UnallocatedWeapons.erase(UnallocatedWeapons.begin() + SelectedSubUnAlloc);

						if (SelectedSubUnAlloc > 0)
							SelectedSubUnAlloc--;
					}
				}
			}
		}

		if (CustomSubs.size() > 0)
		{
			if (tahaGUI().ListBoxHeader(__xor("##Subsections"), Vec2(149, 583)))
			{
				for (size_t i = 0; i < CustomSubs.size(); i++)
				{
					bool selected = i == SelectedSub;
					if (tahaGUI().SelectLabel(CustomSubs[i].Name.c_str(), selected))
						SelectedSub = i;
				}
			}
			tahaGUI().ListBoxFooter();

			tahaGUI().SameLine();
			if (tahaGUI().ListBoxHeader(__xor("##SubsectionWeapons"), Vec2(149, 583)))
			{
				if (SelectedSub < (int)CustomSubs.size())
				{
					for (size_t i = 0; i < CustomSubs[SelectedSub].AllocatedWeapon.size(); i++)
					{
						bool selected = i == SelectedSubAlloc;
						if (tahaGUI().SelectLabel(CustomSubs[SelectedSub].AllocatedWeapon[i].c_str(), selected))
							SelectedSubAlloc = i;
					}
				}
			}
			tahaGUI().ListBoxFooter();

			tahaGUI().SameLine();

			if (tahaGUI().ListBoxHeader(__xor("UnallocatedWeapons"), Vec2(146, 583)))
			{
				if (SelectedSubUnAlloc < (int)UnallocatedWeapons.size())
				{
					for (size_t i = 0; i < UnallocatedWeapons.size(); i++)
					{
						bool selected = i == SelectedSubUnAlloc;
						if (tahaGUI().SelectLabel(UnallocatedWeapons[i].c_str(), selected))
							SelectedSubUnAlloc = i;
					}
				}
			}
			tahaGUI().ListBoxFooter();

			if (SelectedSub < (int)CustomSubs.size())
				if (CustomSubs[SelectedSub].Idx < (int)Weapons.size())
					SelectedWeapon = CustomSubs[SelectedSub].Idx;
				else
					SelectedWeapon = 0;
			else
				SelectedWeapon = 0;
		}
	}
}




























































