#include "Esp.h"
#include "../Setup.h"

using namespace HookTables;

void CEsp::DrawPlayerEx(CEntityPlayer* Entity, CEntityPlayer* Local, bool IsDormant)
{
	auto LDrawPlayerEx = [&]()->void
	{
		Vector OriginScreen;
		Vector HeadScreen, HeadScreenOrig;

		Vector OrignWorld = Entity->RenderOrigin;
		Vector HeadWorld, HeadWorldOrig;

		HeadWorld = Entity->HitBoxes[HITBOX_HEAD];

		if (HeadWorld.IsZero() && !IsDormant)
			return;

		if (IsDormant)
		{
			OrignWorld = Entity->OldRenderOrigin;
			HeadWorld = Entity->OldHead;
		}
		else
		{
			Entity->OldRenderOrigin = OrignWorld;
			Entity->OldHead = HeadWorld;
		}

		if (!Local->IsLocal)
			return;

		if (!Team && Entity->Team == Local->Team)
			return;

		if (!Enemy && Entity->Team != Local->Team)
			return;

		if ((BoxVisibleOnly && !Local->IsDead) && !Entity->IsVisble)
			return;

		HeadWorldOrig = HeadWorld;
		HeadWorld.z += BoxSize;
		OrignWorld.z -= BoxSize;

		if (CGlobal::WorldToScreen(HeadWorld, HeadScreen) && CGlobal::WorldToScreen(OrignWorld, OriginScreen))
		{
			float Height = OriginScreen.y - HeadScreen.y;
			if (Height < 18)
				Height = 18;

			float Width = Height / 2.f;
			Vector BoxScreen = Vector(HeadScreen.x - (Width / 2.f), HeadScreen.y, 0);

			if (Skeleton)
			{
				DrawSkeletonLine(0, 1, Entity);
				DrawSkeletonLine(1, 6, Entity);
				DrawSkeletonLine(6, 5, Entity);
				DrawSkeletonLine(5, 4, Entity);
				DrawSkeletonLine(4, 3, Entity);

				DrawSkeletonLine(6, 15, Entity);
				DrawSkeletonLine(15, 16, Entity);
				DrawSkeletonLine(16, 13, Entity);
				DrawSkeletonLine(6, 17, Entity);
				DrawSkeletonLine(17, 18, Entity);
				DrawSkeletonLine(18, 14, Entity);

				DrawSkeletonLine(3, 8, Entity);
				DrawSkeletonLine(8, 10, Entity);
				DrawSkeletonLine(10, 12, Entity);
				DrawSkeletonLine(3, 7, Entity);
				DrawSkeletonLine(7, 9, Entity);
				DrawSkeletonLine(9, 11, Entity);
			}

			if (Line)
				GP_Render->DrawLine(CGlobal::iScreenWidth / 2.f, CGlobal::iScreenHeight, BoxScreen.x + Width / 2, OriginScreen.y, LineColor);

			if (FillBox && BoxStyle != 2)
				GP_Render->DrawFilledBox((int)BoxScreen.x, (int)BoxScreen.y, (int)Width, (int)Height, FillBoxColor, BoxStyle != 3 ? 0.0f : Width / 5.f);

			if (BoxEnable)
			{
				Color BoxColor = Color::White();

				if (Entity->IsVisble)
				{
					switch (Entity->Team)
					{
					case PLAYER_TEAM::TEAM_CT: BoxColor = BoxVisibleCT; break;
					case PLAYER_TEAM::TEAM_TT: BoxColor = BoxVisibleTT; break;
					default: break;
					}
				}
				else
				{
					switch (Entity->Team)
					{
					case PLAYER_TEAM::TEAM_CT: BoxColor = BoxCT; break;
					case PLAYER_TEAM::TEAM_TT: BoxColor = BoxTT; break;
					default: break;
					}
				}

				Color Black = Color::Black();
				Black[3] = BoxColor[3];

				switch (BoxStyle)
				{
				case 0:
				{
					GP_Render->DrawBox((int)BoxScreen.x, (int)BoxScreen.y, (int)Width, (int)Height, 1, BoxColor);
					if (BoxOutline)
					{
						GP_Render->DrawBox((int)BoxScreen.x + 1, (int)BoxScreen.y + 1, (int)Width - 2, (int)Height - 2, 1, Black);
						GP_Render->DrawBox((int)BoxScreen.x - 1, (int)BoxScreen.y - 1, (int)Width + 2, (int)Height + 2, 1, Black);
					}
					break;
				}
				case 1:
				{
					GP_Render->DrawCoalBox((int)BoxScreen.x, (int)BoxScreen.y, (int)Width, (int)Height, 1, BoxColor, BoxOutline);
					break;
				}
				case 2:
				{
					Draw3DBox(Entity, BoxColor);
					break;
				}
				case 3:
				{
					GP_Render->DrawBox((int)BoxScreen.x, (int)BoxScreen.y, (int)Width, (int)Height, 1, BoxColor, Width / 5.f);
					if (BoxOutline)
					{
						GP_Render->DrawBox((int)BoxScreen.x + 1, (int)BoxScreen.y + 1, (int)Width - 2, (int)Height - 2, 1, Black, Width / 5.f);
						GP_Render->DrawBox((int)BoxScreen.x - 1, (int)BoxScreen.y - 1, (int)Width + 2, (int)Height + 2, 1, Black, Width / 5.f);
					}
					break;
				}
				default:break;
				}
			}

			if (HeadEsp)
			{
				float radius = (Height / 13.4);
				if (radius >= 140)
					radius = 140;

				if (CGlobal::WorldToScreen(HeadWorldOrig, HeadScreenOrig))
					GP_Render->DrawRing(HeadScreenOrig.x, HeadScreenOrig.y, radius, 64, HeadEspColor);
			}

			//��� ��� ���� ��������� ��� ��� ���

			static MoveStruct *MV_Hp = &MVItemList[MI_HEALTH_BAR];
			static MoveStruct *MV_Armor = &MVItemList[MI_ARMOR_BAR];

			static MoveStruct *MV_Hp_Text = &MVItemList[MI_HEALTH_TEXT];
			static MoveStruct *MV_Armor_Text = &MVItemList[MI_ARMOR_TEXT];

			static MoveStruct *MV_Distance = &MVItemList[MI_DISTANCE_TEXT];
			static MoveStruct *MV_Money = &MVItemList[MI_MONEY_TEXT];

			static MoveStruct *MV_Weapon = &MVItemList[MI_WEAPON_TEXT];
			static MoveStruct *MV_Ammo = &MVItemList[MI_AMMO_TEXT];
			static MoveStruct *MV_Scoped = &MVItemList[MI_SCOPE_TEXT];
			static MoveStruct *MV_Flashed = &MVItemList[MI_FLASHED_TEXT];
			static MoveStruct *MV_Name = &MVItemList[MI_NAME_TEXT];

			int y = BoxScreen.y;
			int x = BoxScreen.x;

			auto ChangeSidePosText = [](MoveStruct* Curt, Vec2 Size, Vec2 BoxPos, int boxSizeX, int boxSizeY) -> Vec2
			{
				switch (Curt->Side)
				{
				case LEFT_S: return Vec2(BoxPos.x - Size.x - Curt->CorrectPadding.x, BoxPos.y + Curt->CorrectPadding.y);
				case RIGHT_S:return Vec2(BoxPos.x + boxSizeX + Curt->CorrectPadding.x, BoxPos.y + Curt->CorrectPadding.y);
				case TOP_S:  return Vec2(BoxPos.x + (boxSizeX / 2) - (Size.x / 2), BoxPos.y - Size.y - Curt->CorrectPadding.y);
				case DOWN_S: return Vec2(BoxPos.x + (boxSizeX / 2) - (Size.x / 2), BoxPos.y + boxSizeY + Curt->CorrectPadding.y);
				case LEFT_TOP_S:  return Vec2(BoxPos.x, BoxPos.y - Size.y - Curt->CorrectPadding.y);
				case RIGHT_TOP_S: return Vec2(BoxPos.x + boxSizeX - Size.x, BoxPos.y - Size.y - Curt->CorrectPadding.y);
				case LEFT_DOWN_S: return Vec2(BoxPos.x, BoxPos.y + boxSizeY + Curt->CorrectPadding.y);
				case RIGHT_DOWN_S:return Vec2(BoxPos.x + boxSizeX - Size.x, BoxPos.y + boxSizeY + Curt->CorrectPadding.y);
				case CENTER_LEFT_S:    return Vec2(BoxPos.x - Size.x - Curt->CorrectPadding.x, BoxPos.y + (boxSizeY / 2 + Curt->CorrectPadding.y));
				case CENTER_RIGHT_S:   return Vec2(BoxPos.x + boxSizeX + Curt->CorrectPadding.x, BoxPos.y + (boxSizeY / 2) + Curt->CorrectPadding.y);
				case DOWN_LEFT_DOWN_S: return Vec2(BoxPos.x - Size.x - Curt->CorrectPadding.x, BoxPos.y + boxSizeY - Size.y + Curt->CorrectPadding.y);
				case DOWN_RIGHT_DOWN_S:return Vec2(BoxPos.x + boxSizeX + Curt->CorrectPadding.x, BoxPos.y + boxSizeY - Size.y + Curt->CorrectPadding.y);
				default: return Vec2(0, 0);
				}
			};


			if (Name && MV_Name)
			{
				Color f1 = NameColorBack;
				Color f2(255, 255, 255, 0);

				float Name_X = 0;
				float Name_Y = 0;

				Vec2 TextPos = ChangeSidePosText(MV_Name, GP_Render->CalcTextSize(Entity->Name, GP_Render->SzFonts[TextNameSize]), Vec2(x, y), Width, Height);

				TextPos.x -= (Width / MV_Name->CorrectOfst.x);
				TextPos.y -= (Height / MV_Name->CorrectOfst.y);

				TextPos.x = int(TextPos.x);
				TextPos.y = int(TextPos.y);

				if (NameBackground)
				{
					Vec2 TextSize = GP_Render->CalcTextSize(Entity->Name, GP_Render->SzFonts[TextNameSize]);

					Rect BackLeft = Rect(Vec2(TextPos.x - 15, TextPos.y), Vec2(TextPos.x + TextSize.x / 3, TextPos.y + TextSize.y));
					Rect BackCenter = Rect(Vec2(BackLeft.max.x, BackLeft.min.y), Vec2(BackLeft.max.x + TextSize.x / 3, BackLeft.max.y));
					Rect BackRight = Rect(Vec2(BackCenter.max.x, BackLeft.min.y), Vec2(BackCenter.max.x + (TextSize.x / 3) + 15, BackLeft.max.y));

					GP_Render->DrawGradientBox(BackLeft.min, BackLeft.max, Color(0, 0, 0, 0), NameColorBack, false);
					GP_Render->DrawGradientBox(BackCenter.min, BackCenter.max, NameColorBack, NameColorBack, false);
					GP_Render->DrawGradientBox(BackRight.min, BackRight.max, NameColorBack, Color(0, 0, 0, 0), false);
				}

				GP_Render->DrawString(TextPos.x, TextPos.y, TextNameSize, NameColor, true, false, Entity->Name.c_str());
			}

			if (Health && MV_Hp && MV_Hp_Text)
			{
				Color Minus;
				Color DinColor;
				int iHealth = Entity->Health;
				if (iHealth)
				{
					float health_tik = MV_Hp->NumParam2;

					int healthpos_X = 0;
					int healthpos_Y = 0;

					switch (MV_Hp->Side)
					{
					case LEFT_S:
						healthpos_X = x - (Width / MV_Hp->CorrectOfst.x) - health_tik - MV_Hp->CorrectPadding.x;
						healthpos_Y = y - (Height / MV_Hp->CorrectOfst.y);
						break;
					case RIGHT_S:
						healthpos_X = x - (Width / MV_Hp->CorrectOfst.x) + MV_Hp->CorrectPadding.x;
						healthpos_Y = y - (Height / MV_Hp->CorrectOfst.y);
						break;
					case TOP_S:
						healthpos_X = x - (Width / MV_Hp->CorrectOfst.x);
						healthpos_Y = y - (Height / MV_Hp->CorrectOfst.y) - health_tik - MV_Hp->CorrectPadding.y;
						break;
					case DOWN_S:
						healthpos_X = x - (Width / MV_Hp->CorrectOfst.x);
						healthpos_Y = y - (Height / MV_Hp->CorrectOfst.y) + Height + MV_Hp->CorrectPadding.y;
						break;
					}

					switch (HealthStyle)
					{
					case 0:
					{
						bool vertical = (MV_Hp->Side == LEFT_S || MV_Hp->Side == RIGHT_S);
						DrawBar(
							vertical ? VERTICAL : HORIZONTAL, healthpos_X, healthpos_Y,
							vertical ? health_tik : Width, vertical ? Height : health_tik,
							iHealth, MV_Hp->boolParam2, HealthColor, HealthColor2,
							MV_Hp->boolParam1, MV_Hp->NumParam1, MV_Hp->boolParam3, HealthColor3);
						break;
					}
					case 1:
					{
						string HPText = to_string(iHealth) + __xor("HP");
						Vec2 TextPos = ChangeSidePosText(MV_Hp_Text, GP_Render->CalcTextSize(
							HPText, GP_Render->SzFonts[TextHealthSize]), Vec2(x, y), Width, Height);
						GP_Render->DrawString(
							(int)TextPos.x - (Width / MV_Hp_Text->CorrectOfst.x),
								(int)TextPos.y - (Height / MV_Hp_Text->CorrectOfst.y),
								TextHealthSize, HealthColor, true, false, HPText.c_str());
						break;
					}
					}
				}
			}		

			if (Armor && MV_Armor &&  MV_Armor_Text)
			{
				int iArmor = Entity->Armor;

				if (iArmor)
				{
					float health_tik = MV_Armor->NumParam2;

					int healthpos_X = 0;
					int healthpos_Y = 0;

					switch (MV_Armor->Side)
					{
					case LEFT_S:
						healthpos_X = x - (Width / MV_Armor->CorrectOfst.x) - health_tik - MV_Armor->CorrectPadding.x;
						healthpos_Y = y - (Height / MV_Armor->CorrectOfst.y);
						break;
					case RIGHT_S:
						healthpos_X = x - (Width / MV_Armor->CorrectOfst.x) + MV_Armor->CorrectPadding.x;
						healthpos_Y = y - (Height / MV_Armor->CorrectOfst.y);
						break;
					case TOP_S:
						healthpos_X = x - (Width / MV_Armor->CorrectOfst.x);
						healthpos_Y = y - (Height / MV_Armor->CorrectOfst.y) - health_tik - MV_Armor->CorrectPadding.y;
						break;
					case DOWN_S:
						healthpos_X = x - (Width / MV_Armor->CorrectOfst.x);
						healthpos_Y = y - (Height / MV_Armor->CorrectOfst.y) + Height + MV_Armor->CorrectPadding.y;
						break;
					}

					switch (ArmorStyle)
					{
					case 0:
					{
						bool vertical = (MV_Armor->Side == LEFT_S || MV_Armor->Side == RIGHT_S);
						DrawBar(
							vertical ? VERTICAL : HORIZONTAL, healthpos_X, healthpos_Y,
							vertical ? health_tik : Width, vertical ? Height : health_tik,
							iArmor, MV_Armor->boolParam2, ArmorColor, ArmorColor2,
							MV_Armor->boolParam1, MV_Armor->NumParam1, MV_Armor->boolParam3, ArmorColor3);
						break;
					}
					case 1:
					{
						string AText = to_string(iArmor) + __xor("A");
						Vec2 TextPos = ChangeSidePosText(MV_Armor_Text, GP_Render->CalcTextSize(
							AText, GP_Render->SzFonts[TextHealthSize]), Vec2(x, y), Width, Height);
						GP_Render->DrawString(
							(int)TextPos.x - (Width / MV_Armor_Text->CorrectOfst.x),
								(int)TextPos.y - (Height / MV_Armor_Text->CorrectOfst.y),
								TextHealthSize, ArmorColor, true, false, AText.c_str());
						break;
					}
					}				
				}
			}

			if (Distance && MV_Distance)
			{
				char bufDist[246];
				std::sprintf(bufDist, __xor("%6.1lfm"), Entity->Distance);
				string distm = bufDist;

				Vec2 TextPos = ChangeSidePosText(MV_Distance, GP_Render->CalcTextSize(distm, GP_Render->SzFonts[TextDistanceSize]), Vec2(x, y), Width, Height);
				GP_Render->DrawString((int)TextPos.x - 7 - (Width / MV_Distance->CorrectOfst.x),
					(int)TextPos.y - (Height / MV_Distance->CorrectOfst.y), TextDistanceSize, DistanceColor, true, false, distm.c_str());
			}

			if (Weapon && MV_Weapon)
			{
				const char* WeaponStr = Entity->WeaponName.c_str();
				Vec2 TextPos = ChangeSidePosText(MV_Weapon, GP_Render->CalcTextSize(WeaponStr, GP_Render->SzFonts[TextWeaponSize]), Vec2(x, y), Width, Height);

				switch (WeaponStyle)
				{
				case 0:
				{
					GP_Render->DrawString((int)TextPos.x - (Width / MV_Weapon->CorrectOfst.x),
						(int)TextPos.y - (Height / MV_Weapon->CorrectOfst.y), TextWeaponSize, WeaponColor, true, false, WeaponStr); break;
				}
				case 1:
				{
					string ico = __xor("def");
					if (strstr(WeaponStr, __xor("HE_Grenade")))
						ico = __xor("j");
					else if (strstr(WeaponStr, __xor("Smoke_Grenade")))
						ico = __xor("k");
					else if (strstr(WeaponStr, __xor("FLASHBANG")))
						ico = __xor("i");
					else if (strstr(WeaponStr, __xor("MOLOTOV")))
						ico = __xor("l");
					else if (strstr(WeaponStr, __xor("DECOY")))
						ico = __xor("m");
					else if (strstr(WeaponStr, __xor("IncGrenade")))
						ico = __xor("n");
					else if (strstr(WeaponStr, __xor("Taser")))
						ico = __xor("h");
					else if (strstr(WeaponStr, __xor("Knife_T")))
						ico = __xor("[");
					else if (strstr(WeaponStr, __xor("Knife")))
						ico = __xor("]");
					else if (strstr(WeaponStr, __xor("C4")))
						ico = __xor("o");
					else
					{
						switch (CGlobal::GetWeaponSettingsSelectID(Entity->WeaponIdx))
						{
						case 0:  ico = __xor("A"); break;
						case 1:  ico = __xor("B"); break;
						case 2:  ico = __xor("C"); break;
						case 3:  ico = __xor("D"); break;
						case 4:  ico = __xor("F"); break;
						case 5:  ico = __xor("F"); break;
						case 6:  ico = __xor("G"); break;
						case 7:  ico = __xor("I"); break;
						case 8:  ico = __xor("J"); break;
						case 9:  ico = __xor("H"); break;
						case 10: ico = __xor("W"); break;
						case 11: ico = __xor("U"); break;
						case 12: ico = __xor("R"); break;
						case 13: ico = __xor("Q"); break;
						case 14: ico = __xor("g"); break;
						case 15: ico = __xor("S"); break;
						case 16: ico = __xor("T"); break;
						case 17: ico = __xor("K"); break;
						case 18: ico = __xor("P"); break;
						case 19: ico = __xor("L"); break;
						case 20: ico = __xor("L"); break;
						case 21: ico = __xor("b"); break;
						case 22: ico = __xor("M"); break;
						case 23: ico = __xor("d"); break;
						case 24: ico = __xor("f"); break;
						case 25: ico = __xor("c"); break;
						case 26: ico = __xor("N"); break;
						case 27: ico = __xor("O"); break;
						case 28: ico = __xor("e"); break;
						case 29: ico = __xor("V"); break;
						case 30: ico = __xor("X"); break;
						case 31: ico = __xor("Y"); break;
						case 32: ico = __xor("Z"); break;
						case 33: ico = __xor("a"); break;
						default: break;
						}
					}
					if (ico.length() == 1)
					{
						TextPos = ChangeSidePosText(MV_Weapon, GP_Render->CalcTextSize(ico, GP_Render->SzFontsIcon[TextWeaponSize]), Vec2(x, y), Width, Height);
						GP_Render->DrawIcon((int)TextPos.x - (Width / MV_Weapon->CorrectOfst.x),
							(int)TextPos.y - (Height / MV_Weapon->CorrectOfst.y), TextWeaponSize, WeaponColor, true, false, ico.c_str());
					}
					break;
				}
				default:
					break;
				}
			}
			if (Ammo && MV_Ammo)
			{
				char ammo_format[64];

				switch (AmmoStyle)
				{
				case 0:sprintf(ammo_format, __xor("[%i]"), Entity->Ammo1); break;
				case 1:sprintf(ammo_format, __xor("[%i\\%i]"), Entity->Ammo1, Entity->Ammo2); break;
				case 2:sprintf(ammo_format, __xor("[%i]"), Entity->Ammo1 + Entity->Ammo2); break;
				default:
					break;
				}
				
				string Ammo = string(ammo_format);

				Vec2 TextPos = ChangeSidePosText(MV_Ammo, GP_Render->CalcTextSize(Ammo, GP_Render->SzFonts[TextAmmoSize]), Vec2(x, y), Width, Height);

				GP_Render->DrawString((int)TextPos.x - (Width / MV_Ammo->CorrectOfst.x),
					(int)TextPos.y - (Height / MV_Ammo->CorrectOfst.y), TextAmmoSize, AmmoColor, true, false, Ammo.c_str());
			}

			if (Money && MV_Money)
			{
				string MoneyStr = to_string(Entity->Money) + __xor("$");

				Vec2 TextPos = ChangeSidePosText(MV_Money, GP_Render->CalcTextSize(MoneyStr, GP_Render->SzFonts[TextMoneySize]), Vec2(x, y), Width, Height);
				GP_Render->DrawString((int)TextPos.x - (Width / MV_Money->CorrectOfst.x),
					(int)TextPos.y - (Height / MV_Money->CorrectOfst.y), TextMoneySize, MoneyColor, true, false, MoneyStr.c_str());
			}


			if (Scope && MV_Scoped)
			{
				if (Entity->ZoomLevel == 1 || Entity->ZoomLevel == 2)
				{
					string DefStr = __xor("SCOPED");
					Vec2 TextPos = ChangeSidePosText(MV_Scoped, GP_Render->CalcTextSize(DefStr, GP_Render->SzFonts[TextScopedSize]), Vec2(x, y), Width, Height);

					GP_Render->DrawString((int)TextPos.x - (Width / MV_Scoped->CorrectOfst.x),
						(int)TextPos.y - (Height / MV_Scoped->CorrectOfst.y), TextScopedSize, ScopeColor, true, false, DefStr.c_str());
				}
			}

			if (Flashing && MV_Flashed)
			{
				if (Entity->IsFlashed)
				{
					string DefStr = __xor("FLASHED");
					Vec2 TextPos = ChangeSidePosText(MV_Flashed, GP_Render->CalcTextSize(DefStr, GP_Render->SzFonts[TextFlashedSize]), Vec2(x, y), Width, Height);

					GP_Render->DrawString((int)TextPos.x - (Width / MV_Flashed->CorrectOfst.x),
						(int)TextPos.y - (Height / MV_Flashed->CorrectOfst.y), TextFlashedSize, FlashingColor, true, false, DefStr.c_str());
				}
			}
		}
	};
	LDrawPlayerEx();
}

void CEsp::PlayerEsp(CEntityPlayer* Local)
{
	auto LPlayerEsp = [&]()->void
	{
		if ((Skeleton || FillBox || BoxEnable || HeadEsp ||
			Name || Health || Armor || Ammo || Distance ||
			Weapon || Money || Scope || Flashing || Line) && BindEnable.Check())
		{
			for (int EntIndex = 0; EntIndex < I::Engine()->GetMaxClients(); EntIndex++)
			{
				CEntityPlayer* Entity = &GP_EntPlayers->EntityPlayer[EntIndex];

				if (!Entity->IsUpdated)
					continue;

				if (Entity->IsLocal)
					continue;

				if (!Entity->IsPlayer)
					continue;

				if (Entity->IsDead)
					continue;

				if (Entity->HitBoxes[HITBOX_HEAD].IsZero())
				{
					if (Entity->Alpha == 255.f)
					{
						Entity->HideEndTime = I::GlobalVars()->curtime + DORMANT_TIME;
						Entity->Alpha -= 1.f;
					}

					if (Entity->Alpha != 0.f)
					{
						Entity->Alpha = (255.f * ((((Entity->HideEndTime - I::GlobalVars()->curtime) * 100.f) / DORMANT_TIME) / 100.f));

						if (Entity->Alpha <= 1.f)
							Entity->Alpha = 0.f;
					}
				}

				SetPlayerAlpha(Entity->Alpha);
				if (Entity->Alpha != 0.f)
				{
					DrawPlayerEx(Entity, Local, Entity->HitBoxes[HITBOX_HEAD].IsZero());
				}
				ResetPlayerAlpha();
			}
		}
	};
	LPlayerEsp();
}

void CEsp::SetPlayerAlpha(float NewAlph)
{
	auto LSetPlayerAlpha = [&]()->void
	{
		OldAlphs.clear();

		OldAlphs.push_back(BoxCT[3]);
		OldAlphs.push_back(BoxTT[3]);
		OldAlphs.push_back(BoxVisibleCT[3]);
		OldAlphs.push_back(BoxVisibleTT[3]);
		OldAlphs.push_back(FillBoxColor[3]);
		OldAlphs.push_back(HeadEspColor[3]);
		OldAlphs.push_back(LineColor[3]);
		OldAlphs.push_back(SkeletonColor[3]);
		OldAlphs.push_back(HealthColor[3]);
		OldAlphs.push_back(HealthColor2[3]);
		OldAlphs.push_back(HealthColor3[3]);
		OldAlphs.push_back(ArmorColor[3]);
		OldAlphs.push_back(ArmorColor2[3]);
		OldAlphs.push_back(ArmorColor3[3]);
		OldAlphs.push_back(DistanceColor[3]);
		OldAlphs.push_back(WeaponColor[3]);
		OldAlphs.push_back(AmmoColor[3]);
		OldAlphs.push_back(NameColor[3]);
		OldAlphs.push_back(NameColorBack[3]);
		OldAlphs.push_back(MoneyColor[3]);
		OldAlphs.push_back(FlashingColor[3]);
		OldAlphs.push_back(DefusingColor[3]);

		BoxCT.SetAlph(NewAlph);
		BoxTT.SetAlph(NewAlph);
		BoxVisibleCT.SetAlph(NewAlph);
		BoxVisibleTT.SetAlph(NewAlph);
		FillBoxColor.SetAlph(NewAlph);
		HeadEspColor.SetAlph(NewAlph);
		LineColor.SetAlph(NewAlph);
		SkeletonColor.SetAlph(NewAlph);
		HealthColor.SetAlph(NewAlph);
		HealthColor2.SetAlph(NewAlph);
		HealthColor3.SetAlph(NewAlph);
		ArmorColor.SetAlph(NewAlph);
		ArmorColor2.SetAlph(NewAlph);
		ArmorColor3.SetAlph(NewAlph);
		DistanceColor.SetAlph(NewAlph);
		WeaponColor.SetAlph(NewAlph);
		AmmoColor.SetAlph(NewAlph);
		NameColor.SetAlph(NewAlph);
		NameColorBack.SetAlph(NewAlph);
		MoneyColor.SetAlph(NewAlph);
		FlashingColor.SetAlph(NewAlph);
		DefusingColor.SetAlph(NewAlph);
	};
	LSetPlayerAlpha();
}

void CEsp::ResetPlayerAlpha()
{
	auto LResetPlayerAlpha = [&]()->void
	{
		BoxCT[3] = OldAlphs[0];
		BoxTT[3] = OldAlphs[1];
		BoxVisibleCT[3] = OldAlphs[2];
		BoxVisibleTT[3] = OldAlphs[3];
		FillBoxColor[3] = OldAlphs[4];
		HeadEspColor[3] = OldAlphs[5];
		LineColor[3] = OldAlphs[6];
		SkeletonColor[3] = OldAlphs[7];
		HealthColor[3] = OldAlphs[8];
		HealthColor2[3] = OldAlphs[9];
		HealthColor3[3] = OldAlphs[10];
		ArmorColor[3] = OldAlphs[11];
		ArmorColor2[3] = OldAlphs[12];
		ArmorColor3[3] = OldAlphs[13];
		DistanceColor[3] = OldAlphs[14];
		WeaponColor[3] = OldAlphs[15];
		AmmoColor[3] = OldAlphs[16];
		NameColor[3] = OldAlphs[17];
		NameColorBack[3] = OldAlphs[18];
		MoneyColor[3] = OldAlphs[19];
		FlashingColor[3] = OldAlphs[20];
		DefusingColor[3] = OldAlphs[21];
	};
	LResetPlayerAlpha();
}

void CEsp::Draw3DBox(CEntityPlayer* Entity, Color color)
{
	auto LDraw3DBox = [&]()->void
	{
		ICollideable* coll = Entity->BaseEntity->GetCollideable();

		Vector min = coll->OBBMins();
		Vector max = coll->OBBMaxs();

		Vector corners[8] =
		{
			Vector(min.x,min.y,min.z + 10),
			Vector(min.x,max.y,min.z + 10),
			Vector(max.x,max.y,min.z + 10),
			Vector(max.x,min.y,min.z + 10),
			Vector(min.x,min.y,max.z + 10),
			Vector(min.x,max.y,max.z + 10),
			Vector(max.x,max.y,max.z + 10),
			Vector(max.x,min.y,max.z + 10)
		};

		float ang = Entity->EyeAngle.y;

		for (int i = 0; i <= 7; i++)
			corners[i].Rotate2D(ang);

		Vector _corners[8];

		Vector bufCorners;

		for (int i = 0; i <= 7; i++)
		{
			Vector Orig = Entity->RenderOrigin;
			Orig.z -= 7;
			if (CGlobal::WorldToScreen(Orig + corners[i], bufCorners))
			{
				_corners[i] = bufCorners;
			}
		}

		float x1 = CGlobal::iScreenWidth * 2, y1 = CGlobal::iScreenHeight * 2, x2 = -CGlobal::iScreenWidth, y2 = -CGlobal::iScreenHeight;

		for (int i = 0; i <= 7; i++)
		{
			x1 = (min(x1, _corners[i].x));
			y1 = (min(y1, _corners[i].y));
			x2 = (max(x2, _corners[i].x));
			y2 = (max(y2, _corners[i].y));
		}

		float diff = x2 - x1;
		float diff2 = y2 - y1;


		for (int i = 1; i <= 4; i++)
		{
			if (BoxOutline)
			{
				GP_Render->DrawLine((float)(_corners[i - 1].x), (float)(_corners[i - 1].y) + 1, (float)(_corners[i % 4].x), (float)(_corners[i % 4].y) + 1, Color::Black());// ���
				GP_Render->DrawLine((float)(_corners[i - 1].x), (float)(_corners[i - 1].y) - 1, (float)(_corners[i % 4].x), (float)(_corners[i % 4].y) - 1, Color::Black());// ���

				GP_Render->DrawLine((float)(_corners[i + 3].x), (float)(_corners[i + 3].y) - 1, (float)(_corners[i % 4 + 4].x), (float)(_corners[i % 4 + 4].y) - 1, Color::Black());//����
				GP_Render->DrawLine((float)(_corners[i + 3].x), (float)(_corners[i + 3].y) + 1, (float)(_corners[i % 4 + 4].x), (float)(_corners[i % 4 + 4].y) + 1, Color::Black());//����

				GP_Render->DrawLine((float)(_corners[i - 1].x) - 1, (float)(_corners[i - 1].y), (float)(_corners[i + 3].x) - 1, (float)(_corners[i + 3].y), Color::Black());//��������
				GP_Render->DrawLine((float)(_corners[i - 1].x) + 1, (float)(_corners[i - 1].y), (float)(_corners[i + 3].x) + 1, (float)(_corners[i + 3].y), Color::Black());//��������
			}

			GP_Render->DrawLine((_corners[i - 1].x), (_corners[i - 1].y), (_corners[i % 4].x), (_corners[i % 4].y), color);// ���

			GP_Render->DrawLine((_corners[i + 3].x), (_corners[i + 3].y), (_corners[i % 4 + 4].x), (_corners[i % 4 + 4].y), color);//����

			GP_Render->DrawLine((_corners[i - 1].x), (_corners[i - 1].y), (_corners[i + 3].x), (_corners[i + 3].y), color); //��������
		}
	};
	LDraw3DBox();
}

void CEsp::DrawSkeletonLine(int point1, int point2, CEntityPlayer* Entity)
{
	Vector HitBoxScreen1;
	Vector HitBoxScreen2;

	if (CGlobal::WorldToScreen(Entity->HitBoxes[point1], HitBoxScreen1) && CGlobal::WorldToScreen(Entity->HitBoxes[point2], HitBoxScreen2))
		GP_Render->DrawLine(HitBoxScreen1.x, HitBoxScreen1.y, HitBoxScreen2.x, HitBoxScreen2.y, SkeletonColor);
}

void CEsp::DrawBar(Orent O, float x, float y, float w, float h, float val, bool Outline, Color MainC1, Color cBack, bool bBack, int Razd, bool Revers, Color OutlineCol)
{
	auto LDrawBar = [&]()->void
	{
		if (val > 100) val = 100;
		float size = (h * val) / 100;

		x = (int)x;
		y = (int)y;

		w = (int)w;
		h = (int)h;


		if (bBack)
			GP_Render->DrawFilledBox(x + 1, y + 1, w - 1, h - 1, cBack);


		if (O == VERTICAL)
		{

			if (Revers)
				GP_Render->DrawFilledBox(x + 1, y + 1, w - 1, size - 1, MainC1);
			else
				GP_Render->DrawFilledBox(x + 1, y + 1 + (h - size), w - 1, size, MainC1);


			if (Razd != 0)
			{
				Razd += 1;
				float DistL = h / Razd;

				if (Razd == 1)
					DistL = h / 2.f;

				for (int i(1); i < Razd; i++)
					GP_Render->DrawLine(int(x), int(y + h - (DistL*i)), int(x + w), int(y + h - (DistL*i)), OutlineCol);
			}
		}
		else
		{
			size = (w * val) / 100;

			if (Revers)
				GP_Render->DrawFilledBox(x + 1, y + 1, size - 1, h - 1, MainC1);
			else
				GP_Render->DrawFilledBox(x + 1 + (w - size), y + 1, size - 1, h - 1, MainC1);

			if (Razd != 0)
			{
				Razd += 1;
				float DistL = w / Razd;

				if (Razd == 1)
					DistL = w / 2.f;

				for (int i(1); i < Razd; i++)
					GP_Render->DrawLine(int(x + w - (DistL*i)), int(y), int(x + w - (DistL*i)), int(y + h), OutlineCol);
			}
		}

		if (Outline)
			GP_Render->DrawBox(x, y, w + 1, h + 1, 1, OutlineCol);
	};
	LDrawBar();
}

void CEsp::DrawModelExecute(void* thisptr, IMatRenderContext* ctx, const DrawModelState_t& state, const ModelRenderInfo_t& pInfo, matrix3x4_t* pCustomBoneToWorld)
{
	auto LDrawModelExecute = [&]()->void
	{
		if (Enable && Chams && BindEnable.Check())
		{
			static auto fnDME = HookTables::pDrawModelExecute->GetTrampoline();

			const char* ModelName = I::ModelInfo()->GetModelName((model_t*)pInfo.pModel);

			if (!ModelName)
				return;

			if (!strstr(ModelName, __xor("models/player")))
				return;

			CEntityPlayer* Entity = GP_EntPlayers->GetByIdx(pInfo.entity_index);
			CEntityPlayer* Local = GP_EntPlayers->EntityLocal;

			if (!Entity || !Local)
				return;

			if (!Entity->IsUpdated)
				return;

			if (Entity->IsDead || Entity->Health <= 0)
				return;

			if (!Team && Entity->Team == Local->Team)
				return;

			if (!Enemy && Entity->Team != Local->Team)
				return;

			Color ChamsInvisColor = (Entity->Team == PLAYER_TEAM::TEAM_CT) ? ChamsCT : ChamsTT;
			Color ChamsVisbleColor = (Entity->Team == PLAYER_TEAM::TEAM_CT) ? ChamsVisibleCT : ChamsVisibleTT;

			if (!ChamsVisibleOnly)
			{
				ChamsInvisColor[4];
				OverrideMaterial(true, ChamsDouble, ChamsStyle, ChamsInvisColor);
				fnDME(thisptr, ctx, state, pInfo, pCustomBoneToWorld);
			}
			if (ChamsStyle >= 0)
			{
				ChamsVisbleColor[4];
				OverrideMaterial(false, ChamsDouble, ChamsStyle, ChamsVisbleColor);
				fnDME(thisptr, ctx, state, pInfo, pCustomBoneToWorld);
			}
		}

		if (Enable && Glow && BindEnable.Check())
		{
			static auto fnDME = HookTables::pDrawModelExecute->GetTrampoline();

			const char* ModelName = I::ModelInfo()->GetModelName((model_t*)pInfo.pModel);

			if (!ModelName)
				return;

			if (!strstr(ModelName, __xor("models/player")))
				return;

			CEntityPlayer* Entity = GP_EntPlayers->GetByIdx(pInfo.entity_index);
			CEntityPlayer* Local = GP_EntPlayers->EntityLocal;

			if (!Entity || !Local)
				return;

			if (!Entity->IsUpdated)
				return;

			if (Entity->IsDead || Entity->Health <= 0)
				return;

			if (!Team && Entity->Team == Local->Team)
				return;

			if (!Enemy && Entity->Team != Local->Team)
				return;

			Color GlowInvisColor = (Entity->Team == PLAYER_TEAM::TEAM_CT) ? GlowCT : GlowTT;
			Color GlowVisbleColor = (Entity->Team == PLAYER_TEAM::TEAM_CT) ? GlowVisibleCT : GlowVisibleTT;

			if (!GlowVisibleOnly)
			{
				GlowInvisColor[4];
				const float Pulse = GlowInvisColor[3] * (std::sin(I::GlobalVars()->curtime * GlowPulseSpeed) * GlowPulseRange + 0.5f + 0.5f);
				OverrideMaterial(true, 0, GlowStyle, GlowInvisColor, true, Pulse);
				fnDME(thisptr, ctx, state, pInfo, pCustomBoneToWorld);
			}
			if (GlowStyle >= 0)
			{
				GlowVisbleColor[4];
				const float Pulse = GlowVisbleColor[3] * (std::sin(I::GlobalVars()->curtime * GlowPulseSpeed) * GlowPulseRange + 0.5f + 0.5f);
				OverrideMaterial(false, 0, GlowStyle, GlowVisbleColor, true, Pulse);
				fnDME(thisptr, ctx, state, pInfo, pCustomBoneToWorld);
			}
		}
	};
	LDrawModelExecute();
}




























































