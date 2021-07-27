#include "Misc.h"
#include  "../Setup.h"
#include "../../GUI/Gui.h"
#include "../../Engine/EnginePrediction.h"

#define KEY_DOWN(VK_NNM) ((FastCall::G().t_GetAsyncKeyState(VK_NNM) & 0x8000) ? 1 : 0)

using namespace HookTables;

void CMisc::Draw()
{
	if (Enable)
	{
		if (CGlobal::LocalPlayer)
		{
			CBaseWeapon* pWeapon = CGlobal::LocalPlayer->GetBaseWeapon();
			if (pWeapon)
			{
				if (Crosshair)
				{
					if (CGlobal::GWeaponType != WEAPON_TYPE_SNIPER)
					{
						float punch_x = !CrosshairRecoil ? (CGlobal::iScreenWidth / 2.f) : 
							((CGlobal::iScreenWidth / 2) - (int)((CGlobal::iScreenWidth / CGlobal::GFovView) * (CGlobal::LocalPlayer->GetAimPunchAngle().y * 0.9)));
						float punch_y = !CrosshairRecoil ? (CGlobal::iScreenHeight / 2.f) :
							((CGlobal::iScreenHeight / 2) + (int)((CGlobal::iScreenHeight / CGlobal::GFovView) * (CGlobal::LocalPlayer->GetAimPunchAngle().x * 0.9)));

						switch (CrosshairStyle)
						{
						case 0:
						{
							GP_Render->DrawFilledBox(punch_x - CrosshairSize / 2, punch_y - CrosshairSize / 2, CrosshairSize, CrosshairSize, CrosshairColor);
							if (CrosshairOutline)
								GP_Render->DrawBox((punch_x - CrosshairSize / 2) - 1, (punch_y - CrosshairSize / 2) - 1, CrosshairSize + 1, CrosshairSize + 1, 1, Color::Black());
							break;
						}
						case 1:
						{
							GP_Render->DrawLine(punch_x - CrosshairSize, punch_y, punch_x + CrosshairSize + 1, punch_y, CrosshairColor);
							GP_Render->DrawLine(punch_x, punch_y - CrosshairSize, punch_x, punch_y + CrosshairSize + 1, CrosshairColor);

							if (CrosshairOutline)
							{
								GP_Render->DrawLine(punch_x - CrosshairSize - 1, punch_y - 1, punch_x, punch_y - 1, Color::Black());
								GP_Render->DrawLine(punch_x + 1, punch_y - 1, punch_x + CrosshairSize + 1, punch_y - 1, Color::Black());

								GP_Render->DrawLine(punch_x - CrosshairSize - 1, punch_y + 1, punch_x, punch_y + 1, Color::Black());
								GP_Render->DrawLine(punch_x + 1, punch_y + 1, punch_x + CrosshairSize + 1, punch_y + 1, Color::Black());

								GP_Render->DrawLine(punch_x - CrosshairSize - 1, punch_y - 1, punch_x - CrosshairSize - 1, punch_y + 1, Color::Black());
								GP_Render->DrawLine(punch_x + CrosshairSize + 1, punch_y - 1, punch_x + CrosshairSize + 1, punch_y + 2, Color::Black());


								GP_Render->DrawLine(punch_x - 1, punch_y - CrosshairSize - 1, punch_x - 1, punch_y - 1, Color::Black());
								GP_Render->DrawLine(punch_x + 1, punch_y - CrosshairSize - 1, punch_x + 1, punch_y - 1, Color::Black());

								GP_Render->DrawLine(punch_x - 1, punch_y + CrosshairSize + 1, punch_x - 1, punch_y + 1, Color::Black());
								GP_Render->DrawLine(punch_x + 1, punch_y + CrosshairSize + 1, punch_x + 1, punch_y + 1, Color::Black());

								GP_Render->DrawLine(punch_x - 1, punch_y + CrosshairSize + 1, punch_x + 1, punch_y + CrosshairSize + 1, Color::Black());
								GP_Render->DrawLine(punch_x - 1, punch_y - CrosshairSize - 1, punch_x + 1, punch_y - CrosshairSize - 1, Color::Black());

							}
							break;
						}
						case 2:
						{
							auto lineSize = CrosshairSize;
							int screenCenterX = punch_x;
							int screenCenterY = punch_y;
							GP_Render->DrawLine(screenCenterX - lineSize, screenCenterY - lineSize, screenCenterX - (lineSize / 4), screenCenterY - (lineSize / 4), CrosshairColor);
							GP_Render->DrawLine(screenCenterX - lineSize, screenCenterY + lineSize, screenCenterX - (lineSize / 4), screenCenterY + (lineSize / 4), CrosshairColor);
							GP_Render->DrawLine(screenCenterX + lineSize, screenCenterY + lineSize, screenCenterX + (lineSize / 4), screenCenterY + (lineSize / 4), CrosshairColor);
							GP_Render->DrawLine(screenCenterX + lineSize, screenCenterY - lineSize, screenCenterX + (lineSize / 4), screenCenterY - (lineSize / 4), CrosshairColor);
							break;
						}
						default:
							break;
						}
					}
				}

				if (SnipCrosshair)
				{
					if (CGlobal::GWeaponType == WEAPON_TYPE_SNIPER && CGlobal::GWeaponID != WEAPON_AUG && CGlobal::GWeaponID != WEAPON_SG553)
					{
						CBaseWeapon* Wep = CGlobal::LocalPlayer->GetBaseWeapon();
						if (Wep)
						{
							if (Wep->GetZoomLevel() != 1 && Wep->GetZoomLevel() != 2)
							{
								float punch_x = !SnipCrosshairRecoil ? (CGlobal::iScreenWidth / 2.f) :
									((CGlobal::iScreenWidth / 2) - (int)((CGlobal::iScreenWidth / CGlobal::GFovView) * (CGlobal::LocalPlayer->GetAimPunchAngle().y * 0.9)));
								float punch_y = !SnipCrosshairRecoil ? (CGlobal::iScreenHeight / 2.f) :
									((CGlobal::iScreenHeight / 2) + (int)((CGlobal::iScreenHeight / CGlobal::GFovView) * (CGlobal::LocalPlayer->GetAimPunchAngle().x * 0.9)));

								switch (SnipCrosshairStyle)
								{
								case 0:
								{
									GP_Render->DrawFilledBox(punch_x - CrosshairSize / 2, punch_y - CrosshairSize / 2, CrosshairSize, CrosshairSize, SnipCrosshairColor);
									if (SnipCrosshairOutline)
										GP_Render->DrawBox((punch_x - CrosshairSize / 2) - 1, (punch_y - CrosshairSize / 2) - 1, CrosshairSize + 1, CrosshairSize + 1, 1, Color::Black());
									break;
								}
								case 1:
								{
									GP_Render->DrawLine(punch_x - CrosshairSize, punch_y, punch_x + CrosshairSize + 1, punch_y, SnipCrosshairColor);
									GP_Render->DrawLine(punch_x, punch_y - CrosshairSize, punch_x, punch_y + CrosshairSize + 1, SnipCrosshairColor);

									if (SnipCrosshairOutline)
									{
										GP_Render->DrawLine(punch_x - CrosshairSize - 1, punch_y - 1, punch_x, punch_y - 1, Color::Black());
										GP_Render->DrawLine(punch_x + 1, punch_y - 1, punch_x + CrosshairSize + 1, punch_y - 1, Color::Black());

										GP_Render->DrawLine(punch_x - CrosshairSize - 1, punch_y + 1, punch_x, punch_y + 1, Color::Black());
										GP_Render->DrawLine(punch_x + 1, punch_y + 1, punch_x + CrosshairSize + 1, punch_y + 1, Color::Black());

										GP_Render->DrawLine(punch_x - CrosshairSize - 1, punch_y - 1, punch_x - CrosshairSize - 1, punch_y + 1, Color::Black());
										GP_Render->DrawLine(punch_x + CrosshairSize + 1, punch_y - 1, punch_x + CrosshairSize + 1, punch_y + 2, Color::Black());


										GP_Render->DrawLine(punch_x - 1, punch_y - CrosshairSize - 1, punch_x - 1, punch_y - 1, Color::Black());
										GP_Render->DrawLine(punch_x + 1, punch_y - CrosshairSize - 1, punch_x + 1, punch_y - 1, Color::Black());

										GP_Render->DrawLine(punch_x - 1, punch_y + CrosshairSize + 1, punch_x - 1, punch_y + 1, Color::Black());
										GP_Render->DrawLine(punch_x + 1, punch_y + CrosshairSize + 1, punch_x + 1, punch_y + 1, Color::Black());

										GP_Render->DrawLine(punch_x - 1, punch_y + CrosshairSize + 1, punch_x + 1, punch_y + CrosshairSize + 1, Color::Black());
										GP_Render->DrawLine(punch_x - 1, punch_y - CrosshairSize - 1, punch_x + 1, punch_y - CrosshairSize - 1, Color::Black());
									}
									break;
								}
								case 2:
								{
									auto lineSize = SnipCrosshairSize;
									int screenCenterX = punch_x;
									int screenCenterY = punch_y;
									GP_Render->DrawLine(screenCenterX - lineSize, screenCenterY - lineSize, screenCenterX - (lineSize / 4), screenCenterY - (lineSize / 4), SnipCrosshairColor);
									GP_Render->DrawLine(screenCenterX - lineSize, screenCenterY + lineSize, screenCenterX - (lineSize / 4), screenCenterY + (lineSize / 4), SnipCrosshairColor);
									GP_Render->DrawLine(screenCenterX + lineSize, screenCenterY + lineSize, screenCenterX + (lineSize / 4), screenCenterY + (lineSize / 4), SnipCrosshairColor);
									GP_Render->DrawLine(screenCenterX + lineSize, screenCenterY - lineSize, screenCenterX + (lineSize / 4), screenCenterY - (lineSize / 4), SnipCrosshairColor);
									break;
								}
								default:
									break;
								}
							}
						}
					}
				}

				if (SpreadCircel)
				{
					WEAPON_TYPE WeapType = CGlobal::GWeaponType;

					if (!CGlobal::LocalPlayer->IsDead() &&
						WeapType != WEAPON_TYPE_GRENADE &&
						WeapType != WEAPON_TYPE_KNIFE &&
						WeapType != WEAPON_TYPE_C4 &&
						WeapType != WEAPON_TYPE_UNKNOWN)
					{
						GP_Render->DrawRing(
							(CGlobal::iScreenWidth / 2) - (int)((CGlobal::iScreenWidth / CGlobal::GFovView) * (CGlobal::LocalPlayer->GetAimPunchAngle().y * 0.9)),
							(CGlobal::iScreenHeight / 2) + (int)((CGlobal::iScreenHeight / CGlobal::GFovView) * (CGlobal::LocalPlayer->GetAimPunchAngle().x * 0.9)),
							pWeapon->GetInaccuracy() * 550.f, 42, SpreadColor);
					}
				}
			}
		}

		if (CGlobal::IsGameReady)

		HitWorker.Draw();
	}
}

void CMisc::CreateMove(bool& bSendPacket, float flInputSampleTime, CUserCmd* pCmd)
{
	if (CGlobal::LocalPlayer && CGlobal::IsGameReady)
	{
		if (CGlobal::LocalPlayer->GetBaseWeapon())
		{
			CGlobal::GWeaponType = CGlobal::GetWeaponType(CGlobal::LocalPlayer->GetBaseWeapon());
			if (CGlobal::LocalPlayer->GetBaseWeapon()->GeteAttributableItem())
				CGlobal::GWeaponID = (WEAPON_ID)*CGlobal::LocalPlayer->GetBaseWeapon()->GeteAttributableItem()->GetItemDefinitionIndex();
		}
	}

	if (Enable && CGlobal::IsGameReady && !CGlobal::FullUpdateCheck)
	{
		if (CGlobal::LocalPlayer)
		{
			if (BHop)
			{
				if (!CGlobal::LocalPlayer->IsDead() && !JumpBugBind.Check()) // so that we don't interfere
				{
					if ((CGlobal::LocalPlayer->GetMoveType() & MOVETYPE_LADDER))
						return;

					switch (BHopType)
					{
					case 0:
					{
						if (!(CGlobal::LocalPlayer->GetFlags() & FL_ONGROUND))
						{
							static bool bLastJumped = false;
							static bool bShouldFake = false;

							if (!bLastJumped && bShouldFake)
							{
								bShouldFake = false;
								pCmd->buttons |= IN_JUMP;
							}
							else if (pCmd->buttons & IN_JUMP)
							{
								if (CGlobal::LocalPlayer->GetFlags() & FL_ONGROUND)
								{
									bLastJumped = true;
									bShouldFake = true;
								}
								else
								{
									pCmd->buttons &= ~IN_JUMP;
									bLastJumped = false;
								}
							}
							else
							{
								bLastJumped = false;
								bShouldFake = false;
							}
						}
						break;
					}
					case 1:
					{
						static int HopsRestricted = 0;
						static int HopsHit = 0;

						if (!(CGlobal::LocalPlayer->GetFlags() & FL_ONGROUND))
						{
							pCmd->buttons &= ~IN_JUMP;
							HopsRestricted = 0;
						}
						else if ((rand() % 100 > BHopChance
							&& HopsRestricted < BHopLimit) || (BHopMaxHit > 0 && HopsHit > BHopMaxHit))
						{
							pCmd->buttons &= ~IN_JUMP;
							HopsRestricted++;
							HopsHit = 0;
						}
						else
							HopsHit++;
						break;
					}
					default:
						break;
					}
					if (AutoStrafe && !(CGlobal::LocalPlayer->GetFlags() & FL_ONGROUND))
					{
						if (!KEY_DOWN(VK_SPACE) ||
							KEY_DOWN(VK_KEY_A) ||
							KEY_DOWN(VK_KEY_D) ||
							KEY_DOWN(VK_KEY_S) ||
							KEY_DOWN(VK_KEY_W))
							return;

						bool on_ground = (CGlobal::LocalPlayer->GetFlags() & FL_ONGROUND) && !(pCmd->buttons & IN_JUMP);
						if (on_ground)
							return;

						static auto side = 1.0f;
						side = -side;

						auto velocity = CGlobal::LocalPlayer->GetVelocity();
						velocity.z = 0.0f;

						QAngle wish_angle = pCmd->viewangles;

						auto speed = velocity.Length2D();
						auto ideal_strafe = clamp(RAD2DEG(atan(15.f / speed)), 0.0f, 90.0f);

						if (pCmd->forwardmove > 0.0f)
							pCmd->forwardmove = 0.0f;

						static float old_yaw = 0.f;
						auto yaw_delta = remainderf(wish_angle.y - old_yaw, 360.0f);
						auto abs_angle_delta = abs(yaw_delta);
						old_yaw = wish_angle.y;

						static ConVar* cl_sidespeed = I::GetCvar()->FindVar(__xor("cl_sidespeed"));
						if (abs_angle_delta <= ideal_strafe || abs_angle_delta >= 30.0f)
						{
							QAngle velocity_direction;
							VectorAngles(velocity, velocity_direction);
							auto velocity_delta = remainderf(wish_angle.y - velocity_direction.y, 360.0f);
							auto retrack = clamp(RAD2DEG(atan(30.0f / speed)), 0.0f, 90.0f) * AutoStrafeSpeed;
							if (velocity_delta <= retrack || speed <= 15.0f)
							{
								if (-(retrack) <= velocity_delta || speed <= 15.0f)
								{
									wish_angle.y += side * ideal_strafe;
									pCmd->sidemove = cl_sidespeed->GetFloat() * side;
								}
								else
								{
									wish_angle.y = velocity_direction.y - retrack;
									pCmd->sidemove = cl_sidespeed->GetFloat();
								}
							}
							else
							{
								wish_angle.y = velocity_direction.y + retrack;
								pCmd->sidemove = -cl_sidespeed->GetFloat();
							}

							MovementFix(pCmd, wish_angle, pCmd->viewangles);
						}
						else if (yaw_delta > 0.0f)
							pCmd->sidemove = -cl_sidespeed->GetFloat();
						else if (yaw_delta < 0.0f)
							pCmd->sidemove = cl_sidespeed->GetFloat();
					}
				}
			}
			if (InfiniteCrouch)
			{
				if (!CGlobal::LocalPlayer->IsDead())
				{
					pCmd->buttons |= IN_BULLRUSH;
				}
			}

			static bool NoFlashReset = false;
			if (AntiFlash)
			{
				float* maxAlpha = CGlobal::LocalPlayer->GetFlashMaxAlpha();
				if (maxAlpha)
					*maxAlpha = (float)AntiFlashAlpha;

				NoFlashReset = true;
			}
			if (!AntiFlash && NoFlashReset)
			{
				float* maxAlpha = CGlobal::LocalPlayer->GetFlashMaxAlpha();
				if (maxAlpha)
					*maxAlpha = 255.f;
				NoFlashReset = false;
			}
			vector<const char*> smoke_materials =
			{
				lolc("particle/vistasmokev1/vistasmokev1_smokegrenade"),
				lolc("particle/vistasmokev1/vistasmokev1_emods"),
				lolc("particle/vistasmokev1/vistasmokev1_emods_impactdust"),
				lolc("particle/vistasmokev1/vistasmokev1_fire"),
			};
			static auto smoke_count = *reinterpret_cast<uint32_t**>(offsets["SmokeCount"]);
			static bool NoSmokeReset = false;
			if (NoSmoke)
			{
				for (auto mat : smoke_materials)
				{
					auto material = I::MaterialSystem()->FindMaterial(mat, TEXTURE_GROUP_CLIENT_EFFECTS);
					material->SetMaterialVarFlag(NoSmokeStyle ? MATERIAL_VAR_WIREFRAME : MATERIAL_VAR_NO_DRAW, true);
					material->SetMaterialVarFlag(!NoSmokeStyle ? MATERIAL_VAR_WIREFRAME : MATERIAL_VAR_NO_DRAW, false);
					if (NoSmoke)
						*(int*)smoke_count = 0;
				}
				NoSmokeReset = true;
			}
			if (!NoSmoke && NoSmokeReset)
			{
				for (auto mat : smoke_materials)
				{
					auto material = I::MaterialSystem()->FindMaterial(mat, TEXTURE_GROUP_CLIENT_EFFECTS);
					material->SetMaterialVarFlag(NoSmokeStyle ? MATERIAL_VAR_WIREFRAME : MATERIAL_VAR_NO_DRAW, false);
					if (!NoSmoke && NoSmokeReset)
						*(int*)smoke_count = 1;
				}
				NoSmokeReset = false;
			}
			if (ShowCompetitiveRank && pCmd->buttons & IN_SCORE)
			{
				I::Client()->DispatchUserMessage(CS_UM_ServerRankRevealAll, 0, 0, nullptr);
			}
			if (NameStealer)
			{
				auto ChangeName = [&](bool reconnect, const char* newName, float delay)-> bool
				{
					static auto exploitInitialized = false;

					if (reconnect)
					{
						exploitInitialized = false;
						return false;
					}

					static ConVar* name = I::GetCvar()->FindVar(__xor("name"));
					if (!exploitInitialized && CGlobal::IsGameReady)
					{
						PlayerInfo playerInfo;
						if (CGlobal::LocalPlayer && I::Engine()->GetPlayerInfo(CGlobal::LocalPlayer->EntIndex(), &playerInfo) && (!strcmp(playerInfo.szName, __xor("?empty")) ||
							!strcmp(playerInfo.szName, __xor("\n\xAD\xAD\xAD"))))
						{
							exploitInitialized = true;
						}
						else
						{
							*(int*)((DWORD)&name->fnChangeCallback + 0xC) = NULL;
							name->SetValue(__xor("\n\xAD\xAD\xAD"));
							return false;
						}
					}
					static auto nextChangeTime = 0.0f;
					if (nextChangeTime <= I::GlobalVars()->realtime)
					{
						name->SetValue(newName);
						nextChangeTime = I::GlobalVars()->realtime + delay;
						return true;
					}
					return false;
				};
				static std::vector<int> stolenIds;
				for (int EntIndex = 1; EntIndex <= I::Engine()->GetMaxClients(); ++EntIndex)
				{
					const auto entity = I::EntityList()->GetClientEntity(EntIndex);

					if (!entity || entity == CGlobal::LocalPlayer)
						continue;

					PlayerInfo playerInfo;
					if (!I::Engine()->GetPlayerInfo(entity->EntIndex(), &playerInfo))
						continue;

					if (playerInfo.fakeplayer || std::find(stolenIds.cbegin(), stolenIds.cend(), playerInfo.userId) != stolenIds.cend())
						continue;

					if (ChangeName(I::Engine()->IsConnected(), (std::string(playerInfo.szName) +'\x1').c_str(), 1.0f))
						stolenIds.push_back(playerInfo.userId);

					return;
				}
				stolenIds.clear();
			}
			static bool ClanTagReset = false;
			auto SetNewClan = [&](string New, string Name)-> void
			{
				static auto pSetClanTag = reinterpret_cast<void(__fastcall*)(const char*, const char*)>(offsets["SetClanTag"]);

				if (pSetClanTag)
					pSetClanTag(New.c_str(), Name.c_str());
			};
			if (ClanTagChanger)
			{
				static string old_tag = "";
				static int oldvalue = 0;
				static int old_setting_mode = -1;
				string tag = ClanTagChangerText;
				int setting_mode = ClanTagChangerStyle;
				static int str_size = tag.size();

				if (old_setting_mode != setting_mode)
				{
					old_tag = "";
					old_setting_mode = setting_mode;
				}

				if (old_tag != tag && setting_mode > 1)
				{
					oldvalue = 0;
					old_tag = tag;
					str_size = tag.size();
				}

				int ServerTime = (float)I::Engine()->GetServerTick() * I::GlobalVars()->interval_per_tick;
				if (tag.c_str() && tag.c_str()[0])
				{
					switch (setting_mode)
					{
					case 0:
					{
						if (old_tag != tag)
						{
							old_tag = tag;
							SetNewClan("", " ");
						}
						break;
					}
					case 1:
					{
						if (old_tag != tag)
						{
							old_tag = tag;
							SetNewClan(tag.c_str(), " ");
						}
						break;
					}
					case 2:
					{
						int value = (ServerTime % (str_size * 2)) + 1;
						if (oldvalue != value)
						{
							if (value > str_size)
								value = str_size - (value - str_size);

							tag.erase(value);
							SetNewClan(tag.c_str(), " ");
							oldvalue = value;
						}
						break;
					}
					case 3:
					{
						int value = ServerTime % str_size + 1;
						if (oldvalue != value)
						{
							std::string tag_now = "";

							tag_now.append(tag, value);

							tag.erase(value);
							tag_now += tag;

							SetNewClan(tag_now.c_str(), " ");
							oldvalue = value;
						}
						break;
					}
					case 4:
					{
						int value = str_size - (ServerTime % str_size + 1);
						if (oldvalue != value)
						{
							std::string tag_now = "";

							tag_now.append(tag, value);

							tag.erase(value);
							tag_now += tag;

							SetNewClan(tag_now.c_str(), " ");
							oldvalue = value;
						}
						break;
					}
					case 5:
					{
						int value = (ServerTime % (str_size * 2)) + 1;
						if (oldvalue != value)
						{
							if (value > str_size)
							{
								value -= str_size;
								tag.erase(0, value);
							}
							else
								tag.erase(value);

							SetNewClan(tag.c_str(), " ");
							oldvalue = value;
						}
						break;
					}
					default:
						break;
					}
				}
				ClanTagReset = true;
			}
			if (!ClanTagChanger && ClanTagReset)
			{
				SetNewClan("", "");
				ClanTagReset = false;
			}
			if (KnifeBot && KnifeBotBind.Check())
			{
				if (CGlobal::GWeaponType == WEAPON_TYPE_KNIFE)
				{
					CBaseWeapon* pLocalWeapon = CGlobal::LocalPlayer->GetBaseWeapon();
					if (pLocalWeapon)
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

							float Distance = Entity->Distance * 33;

							if (Distance > KnifeBotDistance)
								continue;

							if (KnifeBotFilter == 1)
							{
								if ((int)Entity->Team != CGlobal::LocalPlayer->GetTeam())
									continue;
							}
							else if (KnifeBotFilter == 2)
							{
								if ((int)Entity->Team == CGlobal::LocalPlayer->GetTeam())
									continue;
							}

							Vector OrignWorld = Entity->RenderOrigin;
							Vector OrignScreen;

							if (!CGlobal::WorldToScreen(OrignWorld, OrignScreen))
								continue;

							switch (KnifeBotMode)
							{
							case 0:
							{
								static int cur_attack = 0;

								if (Distance > 60.f)
									pCmd->buttons |= IN_ATTACK;
								else
								{
									if ((CGlobal::LocalPlayer->GetTickBase() * I::GlobalVars()->interval_per_tick) - pLocalWeapon->GetNextPrimaryAttack() > 0)
									{
										if (Entity->Armor > 0)
										{
											if (Entity->Health - 21 <= 0)
												pCmd->buttons |= IN_ATTACK;
											else
												pCmd->buttons |= IN_ATTACK2;
										}
										else
										{
											if (Entity->Health - 34 <= 0)
												pCmd->buttons |= IN_ATTACK;
											else
												pCmd->buttons |= IN_ATTACK2;
										}
									}

								}
								break;
							}
							case 1:
							{
								static int cur_attack = 0;

								if (Distance > 60.f)
								{
									pCmd->buttons |= IN_ATTACK;
									cur_attack = 1;
								}
								else
								{
									float TimeSinceFire = (CGlobal::LocalPlayer->GetTickBase() * I::GlobalVars()->interval_per_tick) - pLocalWeapon->GetNextPrimaryAttack();

									if (cur_attack > 0 && TimeSinceFire > 0)
									{
										pCmd->buttons |= IN_ATTACK2;
										TimeSinceFire = -1;
										cur_attack = 0;
									}

									if (cur_attack == 0 && TimeSinceFire > 0)
									{
										pCmd->buttons |= IN_ATTACK;
										cur_attack++;
									}
								}
								break;
							}
							case 2: pCmd->buttons |= IN_ATTACK2; break;
							case 3: pCmd->buttons |= IN_ATTACK; break;
							default: break;
							}
						}
					}
				}
			}
		}
	}
}

void CMisc::CreateMoveEP(bool& bSendPacket, CUserCmd* pCmd)
{
	if (Enable && CGlobal::IsGameReady && !CGlobal::FullUpdateCheck)
	{
		auto MaxChokeTicks = [&]()-> int
		{
			int maxticks = I::GameRules() && I::GameRules()->IsValveDS() ? 11 : 14;
			static int max_choke_ticks = 0;
			static int latency_ticks = 0;
			float fl_latency = I::Engine()->GetNetChannelInfo()->GetLatency(FLOW_OUTGOING);
			int latency = TIME_TO_TICKS(fl_latency);
			if (I::ClientState()->chokedcommands <= 0)
				latency_ticks = latency;
			else latency_ticks = max(latency, latency_ticks);

			if (fl_latency >= I::GlobalVars()->interval_per_tick)
				max_choke_ticks = 11 - latency_ticks;
			else max_choke_ticks = 11;
			return max_choke_ticks;
		};
		if (CGlobal::LocalPlayer)
		{
			if (CGlobal::LocalPlayer->IsDead())
				return;

			if (EdgeJump && EdgeJumpBind.Check())
			{
				if (CGlobal::LocalPlayer->GetMoveType() == MOVETYPE_LADDER ||
					CGlobal::LocalPlayer->GetMoveType() == MOVETYPE_NOCLIP)
					return;

				if ((EnginePrediction::GetFlags() & FL_ONGROUND) && !(CGlobal::LocalPlayer->GetFlags() & FL_ONGROUND))
					pCmd->buttons |= IN_JUMP;
			}

			if (JumpBug && JumpBugBind.Check())
			{
				{
					if (!CGlobal::LocalPlayer->IsDead())
					{
						if (CGlobal::LocalPlayer->GetFlags() & FL_ONGROUND)
						{
							pCmd->buttons &= ~IN_JUMP;
							if (!(EnginePrediction::GetFlags() & FL_ONGROUND))
								pCmd->buttons |= IN_DUCK;
						}
					}
				}
			}

			if (EdgeBug && EdgeBugBind.Check())
			{
				EdgeBugging = false;
				{
					if (!CGlobal::LocalPlayer->IsDead())
					{
						EdgeBugging = true;
						if (CGlobal::LocalPlayer->GetFlags() & FL_ONGROUND)
						{

							if ((CGlobal::LocalPlayer->GetFlags() & FL_ONGROUND) &&
								!(EnginePrediction::GetFlags() & FL_ONGROUND))
								pCmd->buttons |= IN_DUCK;
						}
					}
				}
			}

		}
	}
}

void CMisc::FrameStageNotify(ClientFrameStage_t Stage)
{
	if (Enable && CGlobal::IsGameReady && !CGlobal::FullUpdateCheck)
	{
		if (CGlobal::LocalPlayer)
		{
			static ConVar* cl_righthand = I::GetCvar()->FindVar(__xor("cl_righthand"));
			static ConVar* viewmodel_offset_x = I::GetCvar()->FindVar(__xor("viewmodel_offset_x"));
			static ConVar* viewmodel_offset_y = I::GetCvar()->FindVar(__xor("viewmodel_offset_y"));
			static ConVar* viewmodel_offset_z = I::GetCvar()->FindVar(__xor("viewmodel_offset_z"));
			static ConVar* r_aspectratio = I::GetCvar()->FindVar(__xor("r_aspectratio"));

			if (Stage == FRAME_RENDER_START)
			{
				static bool LeftHandKnifeReset = false;
				if (LRHandKnife)
				{
					if (CGlobal::GWeaponType == WEAPON_TYPE_KNIFE)
						cl_righthand->SetValue(!CGlobal::OrigRightHand);
					else
						cl_righthand->SetValue(CGlobal::OrigRightHand);
					LeftHandKnifeReset = true;
				}
				if (!LRHandKnife && LeftHandKnifeReset)
				{
					cl_righthand->SetValue(CGlobal::OrigRightHand);
					LeftHandKnifeReset = false;
				}
				static bool ViewModelXYZReset = false;
				if (ViewModelXYZ)
				{
					if (ViewModelX > 0 || ViewModelX < 0)
					{
						*(float*)((DWORD)&viewmodel_offset_x->fnChangeCallback + 0xC) = NULL;
						viewmodel_offset_x->SetValue(ViewModelX);
					}
					if (ViewModelY > 0 || ViewModelY < 0)
					{
						*(float*)((DWORD)&viewmodel_offset_y->fnChangeCallback + 0xC) = NULL;
						viewmodel_offset_y->SetValue(ViewModelY);
					}
					if (ViewModelZ > 0 || ViewModelZ < 0)
					{
						*(float*)((DWORD)&viewmodel_offset_z->fnChangeCallback + 0xC) = NULL;
						viewmodel_offset_z->SetValue(ViewModelZ);
					}

					ViewModelXYZReset = true;
				}
				if (!ViewModelXYZ && ViewModelXYZReset)
				{
					viewmodel_offset_x->SetValue(CGlobal::OrigViewModelX);
					viewmodel_offset_y->SetValue(CGlobal::OrigViewModelY);
					viewmodel_offset_z->SetValue(CGlobal::OrigViewModelZ);
					ViewModelXYZReset = false;
				}
				static bool AspectRatioReset = false;
				if (Aspect)
				{
					float AspectRation = I::Engine()->GetScreenAspectRatio(AspectWidth, AspectHeight);
					*(int*)((DWORD)&r_aspectratio->fnChangeCallback + 0xC) = NULL;
					r_aspectratio->SetValue(AspectRation);
					AspectRatioReset = true;
				}
				if (!Aspect && AspectRatioReset)
				{
					r_aspectratio->SetValue(CGlobal::OrigAspectRatio);
					AspectRatioReset = false;
				}
			}
			else
			{
				cl_righthand->SetValue(CGlobal::OrigRightHand);
				viewmodel_offset_x->SetValue(CGlobal::OrigViewModelX);
				viewmodel_offset_y->SetValue(CGlobal::OrigViewModelY);
				viewmodel_offset_z->SetValue(CGlobal::OrigViewModelZ);
				r_aspectratio->SetValue(CGlobal::OrigAspectRatio);
			}				
		}
	}
}

void CMisc::OverrideView(CViewSetup* pSetup)
{
	if (Enable && CGlobal::IsGameReady && !CGlobal::FullUpdateCheck)
	{
		if (!pSetup)
			return;

		if (CGlobal::LocalPlayer)
		{
			CGlobal::GFovViewExt = pSetup->fov;
			if (FovChanger)
			{
				if (CGlobal::LocalPlayer->IsDead())
				{
					if (CGlobal::LocalPlayer->GetObserverMode() == ObserverMode_t::OBS_MODE_IN_EYE && CGlobal::LocalPlayer->GetObserverTarget())
						CGlobal::LocalPlayer = (CBaseEntity*)I::EntityList()->GetClientEntityFromHandle(CGlobal::LocalPlayer->GetObserverTarget());

					if (!CGlobal::LocalPlayer)
						return;
				}
				bool ChangeFov = true;
				CBaseWeapon* Wep = CGlobal::LocalPlayer->GetBaseWeapon();
				if (Wep)
				{
					if (((WEAPON_ID)*Wep->GeteAttributableItem()->GetItemDefinitionIndex() == WEAPON_AWP ||
						(WEAPON_ID)*Wep->GeteAttributableItem()->GetItemDefinitionIndex() == WEAPON_SSG08) &&
						(CGlobal::GFovViewExt == 90 || CGlobal::GFovViewExt == FovView) && !CGlobal::LocalPlayer->IsDead())
					{
						ChangeFov = true;
					}
					else
					{
						WEAPON_TYPE WeapType = CGlobal::GWeaponType;
						if ((WeapType != WEAPON_TYPE_GRENADE &&
							WeapType != WEAPON_TYPE_KNIFE) &&
							(Wep->GetZoomLevel() == 1 ||
								Wep->GetZoomLevel() == 2))
						{
							ChangeFov = false;
						}
					}
				}

				if (ChangeFov)
					pSetup->fov = (float)FovView;
			}

			if (NoVisualRecoil)
			{
				pSetup->angles.x -= ((CGlobal::LocalPlayer->GetViewPunchAngle().x * 2.f) * 0.45f);
				pSetup->angles.y -= ((CGlobal::LocalPlayer->GetViewPunchAngle().y * 2.f) * 0.45f);
			}

			if (FreeCam)
			{
				static Vector newOrigin;

				float freecamspeed = FreeCamSpeed;

				if (!FreeCamBind.Check())
				{
					newOrigin = pSetup->origin;
				}
				else
				{
					float fSpeed = freecamspeed; //5.f;
					if (KEY_DOWN(VK_CONTROL))
						fSpeed = fSpeed * 0.45f;
					if (KEY_DOWN(VK_SHIFT))
						fSpeed = fSpeed * 1.65f;
					if (KEY_DOWN(VK_KEY_W))
						newOrigin += pSetup->angles.Forward() * fSpeed;
					if (KEY_DOWN(VK_KEY_A))
						newOrigin += pSetup->angles.Right() * fSpeed;
					if (KEY_DOWN(VK_KEY_D))
						newOrigin -= pSetup->angles.Right() * fSpeed;
					if (KEY_DOWN(VK_KEY_S))
						newOrigin -= pSetup->angles.Forward() * fSpeed;
					if (KEY_DOWN(VK_SPACE))
						newOrigin += pSetup->angles.Up() * fSpeed;
					pSetup->origin = newOrigin;
				}
			}
			static bool ThirdPersonReset = false;
			if (ThirdPerson)
			{
				if (!CGlobal::LocalPlayer->IsDead())
				{
					I::Input()->m_fCameraInThirdPerson = ThirdPersonBind.Check();

					auto GetCorrectDistance = [](float ideal_distance) -> float
					{
						/* vector for the inverse angles */
						QAngle inverseAngles;
						I::Engine()->GetViewAngles(inverseAngles);

						/* inverse angles by 180 */
						inverseAngles.x *= -1.f, inverseAngles.y += 180.f;

						/* vector for direction */
						Vector direction;
						AngleVectors(inverseAngles, direction);

						/* ray, trace & filters */
						Ray_t ray;
						trace_t trace;
						CTraceFilter filter;

						/* dont trace local player */
						filter.pSkip = CGlobal::LocalPlayer;

						/* create ray */
						ray.Init(CGlobal::LocalPlayer->GetEyePosition(), CGlobal::LocalPlayer->GetEyePosition() + (direction * ideal_distance));

						/* trace ray */
						I::EngineTrace()->TraceRay(ray, MASK_SHOT, &filter, &trace);

						/* return the ideal distance */
						return (ideal_distance * trace.fraction) - 10.f;
					};
					Vector angles;
					I::Engine()->GetViewAngles(angles);
					angles.z = GetCorrectDistance(ThirdPersonDistance); // 150 is better distance
					I::Input()->m_vecCameraOffset = Vector(angles.x, angles.y, angles.z);

					ThirdPersonReset = true;
				}
				else
					I::Input()->m_fCameraInThirdPerson = false;
			}
			if (!ThirdPerson && ThirdPersonReset)
			{
				I::Input()->m_fCameraInThirdPerson = false;
				ThirdPersonReset = false;
			}
		}
	}

	if (CGlobal::LocalPlayer && !CGlobal::FullUpdateCheck)
	{
		if (GP_LegitAim)
		{
			if (GP_LegitAim->CanRCSStandelone && GP_LegitAim->CanRCS)
			{
				pSetup->angles.x -= ((CGlobal::LocalPlayer->GetViewPunchAngle().x * 2.f) * 0.2f);
				pSetup->angles.y -= ((CGlobal::LocalPlayer->GetViewPunchAngle().y * 2.f) * 0.2f);
			}
		}
	}
	
	CGlobal::GFovView = pSetup->fov;
}

void CMisc::GetViewModelFOV(float &Fov)
{
	if (Enable && CGlobal::IsGameReady && !CGlobal::FullUpdateCheck)
	{
		if (CGlobal::LocalPlayer)
		{
			if (FovModelChanger)
			{
				if (CGlobal::LocalPlayer->IsDead())
				{
					if (CGlobal::LocalPlayer->GetObserverMode() == ObserverMode_t::OBS_MODE_IN_EYE && CGlobal::LocalPlayer->GetObserverTarget())
						CGlobal::LocalPlayer = (CBaseEntity*)I::EntityList()->GetClientEntityFromHandle(CGlobal::LocalPlayer->GetObserverTarget());

					if (!CGlobal::LocalPlayer)
						return;
				}

				bool ChangeFov = true;
				CBaseWeapon* Wep = CGlobal::LocalPlayer->GetBaseWeapon();
				if (Wep)
				{
					if (((WEAPON_ID)*Wep->GeteAttributableItem()->GetItemDefinitionIndex() == WEAPON_AWP ||
						(WEAPON_ID)*Wep->GeteAttributableItem()->GetItemDefinitionIndex() == WEAPON_SSG08) &&
						(CGlobal::GFovViewExt == 90 || CGlobal::GFovViewExt == FovView) && !CGlobal::LocalPlayer->IsDead())
					{
						ChangeFov = true;
					}
					else
					{
						WEAPON_TYPE WeapType = CGlobal::GWeaponType;
						if ((WeapType != WEAPON_TYPE_GRENADE &&
							WeapType != WEAPON_TYPE_KNIFE) &&
							(Wep->GetZoomLevel() == 1 ||
								Wep->GetZoomLevel() == 2))
						{
							ChangeFov = false;
						}
					}

				}

				if (ChangeFov)
					Fov = (float)FovModel;
			}
		}
	}
}

void CMisc::AutoAcceptEmit()
{
	if (AutoAccept && !CGlobal::FullUpdateCheck)
	{
		static auto SetLocalPlayerReadyFn 
			= reinterpret_cast<bool(__stdcall*)(const char*)>(offsets["SetLocalPlayerReady"]);

		if (SetLocalPlayerReadyFn)
		{
			SetLocalPlayerReadyFn("");
			HWND window = FastCall::G().t_FindWindowA(__xor("Valve001"), 0);
			FLASHWINFO flash{ sizeof(FLASHWINFO), window, FLASHW_TRAY | FLASHW_TIMERNOFG, 0, 0 };
			FastCall::G().t_FlashWindowEx(&flash);
		}
	}
}

void CMisc::DrawModelExecute(void* thisptr, IMatRenderContext* ctx, const DrawModelState_t& state, const ModelRenderInfo_t& pInfo, matrix3x4_t* pCustomBoneToWorld)
{
	//if (Enable && LDesyncChams)
	//{
	//	static auto fnDME = HookTables::pDrawModelExecute->GetTrampoline();
	//	const char* ModelName = I::ModelInfo()->GetModelName((model_t*)pInfo.pModel);

	//	if (!ModelName)
	//		return;

	//	if (strstr(ModelName, __xor("models/player")))
	//	{
	//		CEntityPlayer* Entity = GP_EntPlayers->GetByIdx(pInfo.entity_index);
	//		CEntityPlayer* Local = GP_EntPlayers->EntityLocal;

	//		if (LDesyncChams && Local == Entity)
	//		{
	//			matrix3x4_t fake_matrix[128];
	//			Entity->BaseEntity->SetAbsAngles(real_angle);
	//			if (Entity->BaseEntity->SetupBones(fake_matrix, 128, 0x100, Local->BaseEntity->GetSimTime()))
	//			{
	//				LDesyncArrowsColor[4];
	//				GP_Esp->OverrideMaterial(false, 0, 0, LDesyncArrowsColor);
	//				fnDME(thisptr, ctx, state, pInfo, pCustomBoneToWorld);
	//			}
	//			Entity->BaseEntity->SetAbsAngles(Vector(0, fake_angle.y, 0));
	//		}
	//	}
	//}

	if (Enable && HandChams || HandGlow)
	{
		static auto fnDME = HookTables::pDrawModelExecute->GetTrampoline();
		const char* ModelName = I::ModelInfo()->GetModelName((model_t*)pInfo.pModel);

		if (!ModelName)
			return;

		IMaterial* Material = I::MaterialSystem()->FindMaterial(ModelName, TEXTURE_GROUP_MODEL);

		if (strstr(ModelName, __xor("arms")))
		{
			if (HandChams)
			{
				HandChamsColor[4];
				GP_Esp->OverrideMaterial(false, HCDouble, HCStyle, HandChamsColor);
				if (HCStyle == 6) //disable hand
				{
					Material->SetMaterialVarFlag(MATERIAL_VAR_NO_DRAW, true);
					I::ModelRender()->ForcedMaterialOverride(Material);
				}
				fnDME(thisptr, ctx, state, pInfo, pCustomBoneToWorld);
			}
			if (HandGlow)
			{
				HandGlowColor[4];
				const float Pulse = HandGlowColor[3] * (std::sin(I::GlobalVars()->curtime * HGPSpeed) * HGPRange + 0.5f + 0.5f);
				GP_Esp->OverrideMaterial(false, 0, HGStyle, HandGlowColor, true, Pulse);
				fnDME(thisptr, ctx, state, pInfo, pCustomBoneToWorld);
			}
		}
	}

	if (Enable && WeaponChams || WeaponGlow)
	{
		static auto fnDME = HookTables::pDrawModelExecute->GetTrampoline();
		const char* ModelName = I::ModelInfo()->GetModelName((model_t*)pInfo.pModel);

		if (!ModelName)
			return;

		IMaterial* Material = I::MaterialSystem()->FindMaterial(ModelName, TEXTURE_GROUP_MODEL);

		if (strstr(ModelName, ("models/weapons/v_")) && !strstr(ModelName, __xor("arms")))
		{
			if (WeaponChams)
			{
				WeaponChamsColor[4];
				GP_Esp->OverrideMaterial(false, WCDouble, WCStyle, WeaponChamsColor);
				if (WCStyle == 6) //disable weapon
				{
					Material->SetMaterialVarFlag(MATERIAL_VAR_NO_DRAW, true);
					I::ModelRender()->ForcedMaterialOverride(Material);
				}
				fnDME(thisptr, ctx, state, pInfo, pCustomBoneToWorld);
			}
			if (WeaponGlow)
			{
				WeaponGlowColor[4];
				const float Pulse = WeaponGlowColor[3] * (std::sin(I::GlobalVars()->curtime * WGPSpeed) * WGPRange + 0.5f + 0.5f);
				GP_Esp->OverrideMaterial(false, 0, WGStyle, WeaponGlowColor, true, Pulse);
				fnDME(thisptr, ctx, state, pInfo, pCustomBoneToWorld);
			}
		}
	}
}

void CMisc::Reset()
{
	if (!HitWorker.DamageVector.empty())
		HitWorker.DamageVector.clear();

	if (!HitImpacts.empty())
		HitImpacts.clear();

	HitWorker.HitMarkerEndTime = 0;
}


void ReadSounds(LPCTSTR lpszFileName)
{
	if (GP_Misc)
		GP_Misc->SoundList.push_back(lpszFileName);
}

void CMisc::UpdateSoundList()
{
	SoundList.clear();
	string SoundsDir = CGlobal::SystemDisk + __xor("obnoxious\\Resources\\Sounds\\*.wav");
	CGlobal::SearchFiles(SoundsDir.c_str(), ReadSounds, FALSE);
}

void CHitListener::RegListener()
{
	I::GameEvent()->AddListener(this, __xor("player_hurt"), false);
	I::GameEvent()->AddListener(this, __xor("bullet_impact"), false);
}

void CHitListener::UnRegListener()
{
	I::GameEvent()->RemoveListener(this);
}

#define HIT_TRACE_SHOW_TIME 2.f
void CHitListener::FireGameEvent(IGameEvent *event)
{
	if (GP_Misc)
	{
		if (GP_Misc->Enable)
		{
			if (CGlobal::LocalPlayer)
			{
				if (!strcmp(event->GetName(), __xor("bullet_impact")))
				{
					int PlayerIdx = I::Engine()->GetPlayerForUserID(event->GetInt(__xor("userid")));

					if (PlayerIdx == I::Engine()->GetLocalPlayer())
					{
						Vector ImpactPos(event->GetFloat(__xor("x")), event->GetFloat(__xor("y")), event->GetFloat(__xor("z")));

						Ray_t ray;
						ray.Init(CGlobal::LocalPlayer->GetEyePosition(), ImpactPos);

						CTraceFilter filter;
						filter.pSkip = CGlobal::LocalPlayer;

						trace_t tr;
						I::EngineTrace()->TraceRay(ray, MASK_SHOT, &filter, &tr);

						if (tr.hit_entity && tr.DidHit())
						{
							if (reinterpret_cast<CBaseEntity*>(tr.hit_entity)->IsPlayer())
							{
								CMisc::HitImpact_t ImpEntry;
								ImpEntry.Pos = ImpactPos;
								ImpEntry.MyHeadPos = CGlobal::LocalPlayer->GetEyePosition();
								ImpEntry.EndTime = I::GlobalVars()->curtime + HIT_TRACE_SHOW_TIME;
								ImpEntry.Alpha = 255;
								GP_Misc->HitImpacts.push_back(ImpEntry);
							}
						}
					}
				}

				if (!strcmp(event->GetName(), __xor("player_hurt")))
				{
					if (I::Engine()->GetPlayerForUserID(event->GetInt(__xor("attacker"))) == I::Engine()->GetLocalPlayer())
					{

						if (GP_Misc->HitMarker)
						HitMarkerEndTime = I::GlobalVars()->curtime + 0.29f;

						if (GP_Misc->HitSound)
							if (!GP_Misc->SoundList.empty() && GP_Misc->HitSoundStyle >= 0 && GP_Misc->HitSoundStyle < (int)GP_Misc->SoundList.size())	
								FastCall::G().t_PlaySoundA((CGlobal::SystemDisk + __xor("obnoxious\\Resources\\Sounds\\") + GP_Misc->SoundList[GP_Misc->HitSoundStyle]).c_str(),
									NULL, SND_FILENAME | SND_ASYNC);

						if (GP_Misc->DamageInfo)
						{
							DamgeInfo_t BufInfo;

							CBaseEntity* pHurtEnt = (CBaseEntity*)I::EntityList()->GetClientEntity(I::Engine()->GetPlayerForUserID(event->GetInt(__xor("userid"))));
							if (pHurtEnt)
							{
								BufInfo.Pos = pHurtEnt->GetHitboxPosition(0);
								if (!BufInfo.Pos.IsZero())
								{
									if (GP_Misc->DamageInfoStyle == 0)
										BufInfo.Number = event->GetInt(__xor("dmg_health"));
									else if (GP_Misc->DamageInfoStyle == 1)
										BufInfo.Number = pHurtEnt->GetHealth() - event->GetInt(__xor("dmg_health"));

									BufInfo.EndTime = I::GlobalVars()->curtime + GP_Misc->DamageInfoShowTime;
									BufInfo.Pos.z += 20;
									BufInfo.Alpha = 255;
									BufInfo.OffsetZ = 1;
									DamageVector.push_back(BufInfo);
								}
							}
						}
					}
				}
			}
		}
	}
}

void CHitListener::Draw()
{
	auto HitMark = [&](const int& size, const int& tick, const int& pos_x, const int& pos_y, const Color& color)-> void
	{
		GP_Render->DrawLine(pos_x - size, pos_y - size, pos_x - (size / 4), pos_y - (size / 4), color, tick);
		GP_Render->DrawLine(pos_x - size, pos_y + size, pos_x - (size / 4), pos_y + (size / 4), color, tick);
		GP_Render->DrawLine(pos_x + size, pos_y + size, pos_x + (size / 4), pos_y + (size / 4), color, tick);
		GP_Render->DrawLine(pos_x + size, pos_y - size, pos_x + (size / 4), pos_y - (size / 4), color, tick);
	};

	if (GP_Misc)
	{
		if (GP_Misc->HitMarker)
		{
			if (HitMarkerEndTime > I::GlobalVars()->curtime)
			{
				HitMark(GP_Misc->HitMarkerSize, GP_Misc->HitMarkerTickness,
					CGlobal::iScreenWidth / 2, CGlobal::iScreenHeight / 2, GP_Misc->HitMarkerColor);
			}
		}

		if (GP_Misc->DamageInfo)
		{
			if (!DamageVector.empty())
			{
				if (GP_Misc->DamageInfoPosition == 0)
					GP_Render->DrawString(GP_Misc->TextDamageInfo, Vec2(GP_Misc->DamageInfoPosX, GP_Misc->DamageInfoPosY), GP_Misc->DamageInfoColor,
						to_string(DamageVector.back().Number).c_str());

				int Height = GP_Misc->DamageInfoHeight;
				int Speed = GP_Misc->DamageInfoSpeed;

				for (size_t i(0); i < DamageVector.size(); i++)
				{
					if (GP_Misc->DamageInfoPosition == 1)
					{
						if (DamageVector[i].OffsetZ < Height)
							DamageVector[i].OffsetZ += (Height - DamageVector[i].OffsetZ) * (Speed / 1195.f);

						if (DamageVector[i].OffsetZ > Height - (Height / 5))
							if (DamageVector[i].Alpha > 0)
								DamageVector[i].Alpha -= 10;

						if (DamageVector[i].Alpha < 0)
							DamageVector[i].Alpha = 0;

						Vector ScreenPosition;
						Vector WorldPosition = Vector(DamageVector[i].Pos.x,
							DamageVector[i].Pos.y,
							DamageVector[i].Pos.z + DamageVector[i].OffsetZ);

						Color DamageColor = Color(GP_Misc->DamageInfoColor.r(), GP_Misc->DamageInfoColor.g(), GP_Misc->DamageInfoColor.b(), DamageVector[i].Alpha);

						if (CGlobal::WorldToScreen(WorldPosition, ScreenPosition))
							GP_Render->DrawString(GP_Misc->TextDamageInfo, Vec2(ScreenPosition.x, ScreenPosition.y), DamageColor, false, true,
								to_string(DamageVector.back().Number).c_str());

						if (DamageVector[i].OffsetZ > Height - 1)
							DamageVector.erase(DamageVector.begin() + i);
					}

					if (GP_Misc->DamageInfoPosition == 0)
						if (DamageVector[i].EndTime < I::GlobalVars()->curtime)
							if (CGlobal::IsGameReady)
								DamageVector.erase(DamageVector.begin() + i);
				}
			}
		}
	}
}



























































