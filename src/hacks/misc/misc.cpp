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
			}
		}
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
				}
			}
			if (InfiniteCrouch)
			{
				if (!CGlobal::LocalPlayer->IsDead())
				{
					pCmd->buttons |= IN_BULLRUSH;
				}
			}
			if (ShowCompetitiveRank && pCmd->buttons & IN_SCORE)
			{
				I::Client()->DispatchUserMessage(CS_UM_ServerRankRevealAll, 0, 0, nullptr);
			}
			CGlobal::SlowWalking = false; // i dont know if it'll work like this tbh.
			if (SlowWalk && SlowWalkBind.Check()) {
				if ((CGlobal::LocalPlayer->GetFlags() & FL_ONGROUND))
				{
					
					CCSWeaponInfo* chrisgay = CGlobal::LocalPlayer->GetBaseWeapon()->GetWeaponInfo();
					auto max_speed = 0.3f * (CGlobal::LocalPlayer->GetIsScoped() ? chrisgay->flMaxSpeedAlt : chrisgay->flMaxSpeed);

					if (!CGlobal::GWeaponType == WEAPON_TYPE_GRENADE ||
						!CGlobal::GWeaponType == WEAPON_TYPE_KNIFE ||
						!CGlobal::GWeaponType == WEAPON_TYPE_C4 ||
						!CGlobal::GWeaponType == WEAPON_TYPE_UNKNOWN)
					{
						auto move_length = sqrt(pCmd->sidemove * pCmd->sidemove + pCmd->forwardmove * pCmd->forwardmove);
						auto forwardmove = pCmd->forwardmove / move_length;
						auto sidemove = pCmd->sidemove / move_length;

						if (move_length > max_speed)
						{
							if (max_speed + 1.0f < CGlobal::LocalPlayer->GetVelocity().Length2D())
							{
								pCmd->forwardmove = 0.0f;
								pCmd->sidemove = 0.0f;
							}
							else
							{
								pCmd->sidemove = max_speed * sidemove;
								pCmd->forwardmove = max_speed * forwardmove;
							}
						}
					}
					else

					{
						auto forwardmove = pCmd->forwardmove;
						auto sidemove = pCmd->sidemove;

						auto move_length = sqrt(sidemove * sidemove + forwardmove * forwardmove);
						auto move_length_backup = move_length;

						if (move_length > 110.0f)
						{
							pCmd->forwardmove = forwardmove / move_length_backup * 110.0f;
							move_length = sidemove / move_length_backup * 110.0f;
							pCmd->sidemove = sidemove / move_length_backup * 110.0f;
						}
					}
					CGlobal::SlowWalking = true;
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
}
void CMisc::CreateMoveEP(bool& bSendPacket, CUserCmd* pCmd)
{
	if (Enable && CGlobal::IsGameReady && !CGlobal::FullUpdateCheck)
	{
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
			if (Stage == FRAME_RENDER_START)
			{
				if (LRHandKnife)
				{
					if (CGlobal::GWeaponType == WEAPON_TYPE_KNIFE)
						cl_righthand->SetValue(0);
					else
						cl_righthand->SetValue(1);
				}
			}
			else
			{
				cl_righthand->SetValue(CGlobal::OrigRightHand);
			}				
		}
	}
}

void CMisc::OverrideView(CViewSetup* pSetup)
{
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


