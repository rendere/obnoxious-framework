#include "Esp.h"
#include "../Setup.h"

void CEsp::WorldEsp()
{
	auto LWorldEsp = [&]()->void
	{
		if (WorldGrenade || WorldWeapons || WorldBomb || WorldBombInfo)
		{
			int max_e = I::EntityList()->GetHighestEntityIndex();
			if (CGlobal::LocalPlayer)
			{
				for (int EntIndex = 0; EntIndex < max_e; EntIndex++)
				{
					CBaseEntity* pEntity = (CBaseEntity*)I::EntityList()->GetClientEntity(EntIndex);

					if (!pEntity || pEntity->IsPlayer())
						continue;

					if (pEntity == (CBaseEntity*)0xE || pEntity == (CBaseEntity*)0xB)
						continue;

					const model_t* pModel = pEntity->GetModel();

					if (!pModel)
						continue;

					const char* pModelName = I::ModelInfo()->GetModelName(pModel);

					if (!pModelName)
						continue;

					Vector EntityScreen;

					if (WorldGrenade)
					{
						if ((strstr(pModelName, __xor("_dropped.mdl")) && !strstr(pModelName, __xor("models/weapons/w_ied"))) || strstr(pModelName, __xor("smokegrenade_thrown.mdl")))
						{
							if (CGlobal::WorldToScreen(pEntity->GetRenderOrigin(), EntityScreen))
							{

								string  GrenadeName = "";
								Color GrenadeColor = Color::White();
								bool Finded = false;

								if (strstr(pModelName, __xor("fraggrenade")))
								{
									GrenadeColor = HEGrenadeColor;
									if (WorldGrenadeStyle == 2) GrenadeName = __xor("j");
									else GrenadeName = __xor("HE GRENADE");
									Finded = true;
								}
								else if (strstr(pModelName, __xor("molotov")))
								{
									GrenadeColor = MolotovGrenadeColor;
									if (WorldGrenadeStyle == 2) GrenadeName = __xor("l");
									else GrenadeName = __xor("MOLOTOV");
									Finded = true;
								}
								else if (strstr(pModelName, __xor("flashbang")))
								{
									GrenadeColor = FlashGrenadeColor;
									if (WorldGrenadeStyle == 2) GrenadeName = __xor("i");
									else GrenadeName = __xor("FLASHBANG");
									Finded = true;
								}
								else if (strstr(pModelName, __xor("incendiarygrenade")))
								{
									GrenadeColor = IncGrenadeColor;
									if (WorldGrenadeStyle == 2) GrenadeName = __xor("n");
									else GrenadeName = __xor("INCENDIARY");
									Finded = true;
								}
								else if (strstr(pModelName, __xor("smokegrenade_thrown.mdl")))
								{
									GrenadeColor = SmokeGrenadeColor;
									if (WorldGrenadeStyle == 2) GrenadeName = __xor("k");
									else GrenadeName = __xor("SMOKE");
									Finded = true;
								}
								else if (strstr(pModelName, __xor("decoy")))
								{
									GrenadeColor = DecoyGrenadeColor;
									if (WorldGrenadeStyle == 2) GrenadeName = __xor("m");
									else GrenadeName = __xor("DECOY");
									Finded = true;
								}

								if (Finded)
								{
									switch (WorldGrenadeStyle)
									{
									case 0: GP_Render->DrawString(TextGrenadeSize, Vec2((int)EntityScreen.x, (int)EntityScreen.y), GrenadeColor, true, true, GrenadeName.c_str()); break;
									case 1: GP_Render->DrawRing((int)EntityScreen.x, (int)EntityScreen.y, 10, 32, GrenadeColor, 2.f); break;
									case 2: GP_Render->DrawStringIcon(TextGrenadeSize, Vec2((int)EntityScreen.x, (int)EntityScreen.y), GrenadeColor, true, true, GrenadeName.c_str()); break;
									default:
										break;
									}
								}
							}
						}
					}

					if (WorldWeapons)
					{
						if (strstr(pModelName, __xor("models/weapons/w_")) && strstr(pModelName, __xor("_dropped.mdl")) &&
							!strstr(pModelName, __xor("models/weapons/w_eq_")) && !strstr(pModelName, __xor("models/weapons/w_ied")))
						{
							if (CGlobal::WorldToScreen(pEntity->GetRenderOrigin(), EntityScreen))
							{
								string WeaponName = pModelName + 17;
								WeaponName[WeaponName.size() - 12] = '\0';
								if (WorldWeaponsStyle == 0)
								{
									if (strstr(WeaponName.c_str(), __xor("rif_ak47"))) WeaponName = M_WEAPON_AK47_STR;
									else if (strstr(WeaponName.c_str(), __xor("rif_aug"))) WeaponName = M_WEAPON_AUG_STR;
									else if (strstr(WeaponName.c_str(), __xor("rif_famas")))WeaponName = M_WEAPON_FAMAS_STR;
									else if (strstr(WeaponName.c_str(), __xor("rif_galilar"))) WeaponName = M_WEAPON_GALILAR_STR;
									else if (strstr(WeaponName.c_str(), __xor("rif_m4a1_s"))) WeaponName = M_WEAPON_M4A1_S_STR;
									else if (strstr(WeaponName.c_str(), __xor("rif_m4a1"))) WeaponName = M_WEAPON_M4A4_STR;
									else if (strstr(WeaponName.c_str(), __xor("rif_sg556"))) WeaponName = M_WEAPON_SG553_STR;
									else if (strstr(WeaponName.c_str(), __xor("pist_223"))) WeaponName = M_WEAPON_USP_S_STR;
									else if (strstr(WeaponName.c_str(), __xor("pist_revolver"))) WeaponName = M_WEAPON_REVOLVER_STR;
									else if (strstr(WeaponName.c_str(), __xor("pist_cz_75"))) WeaponName = M_WEAPON_CZ75A_STR;
									else if (strstr(WeaponName.c_str(), __xor("pist_deagle"))) WeaponName = M_WEAPON_DEAGLE_STR;
									else if (strstr(WeaponName.c_str(), __xor("pist_elite"))) WeaponName = M_WEAPON_ELITE_STR;
									else if (strstr(WeaponName.c_str(), __xor("pist_fiveseven"))) WeaponName = M_WEAPON_FIVESEVEN_STR;
									else if (strstr(WeaponName.c_str(), __xor("pist_glock18"))) WeaponName = M_WEAPON_GLOCK_STR;
									else if (strstr(WeaponName.c_str(), __xor("pist_hkp2000"))) WeaponName = M_WEAPON_HKP2000_STR;
									else if (strstr(WeaponName.c_str(), __xor("pist_p250"))) WeaponName = M_WEAPON_P250_STR;
									else if (strstr(WeaponName.c_str(), __xor("pist_tec9"))) WeaponName = M_WEAPON_TEC9_STR;
									else if (strstr(WeaponName.c_str(), __xor("snip_awp"))) WeaponName = M_WEAPON_AWP_STR;
									else if (strstr(WeaponName.c_str(), __xor("snip_g3sg1"))) WeaponName = M_WEAPON_G3SG1_STR;
									else if (strstr(WeaponName.c_str(), __xor("snip_scar20"))) WeaponName = M_WEAPON_SCAR20_STR;
									else if (strstr(WeaponName.c_str(), __xor("snip_ssg08"))) WeaponName = M_WEAPON_SSG08_STR;
									else if (strstr(WeaponName.c_str(), __xor("smg_mac10"))) WeaponName = M_WEAPON_MAC10_STR;
									else if (strstr(WeaponName.c_str(), __xor("smg_mp7"))) WeaponName = M_WEAPON_MP7_STR;
									else if (strstr(WeaponName.c_str(), __xor("smg_mp9"))) WeaponName = M_WEAPON_MP9_STR;
									else if (strstr(WeaponName.c_str(), __xor("smg_ump45"))) WeaponName = M_WEAPON_UMP45_STR;
									else if (strstr(WeaponName.c_str(), __xor("smg_mp5sd"))) WeaponName = M_WEAPON_MP5_STR;
									else if (strstr(WeaponName.c_str(), __xor("smg_p90"))) WeaponName = M_WEAPON_P90_STR;
									else if (strstr(WeaponName.c_str(), __xor("shot_mag7"))) WeaponName = M_WEAPON_MAG7_STR;
									else if (strstr(WeaponName.c_str(), __xor("smg_bizon"))) WeaponName = M_WEAPON_BIZON_STR;
									else if (strstr(WeaponName.c_str(), __xor("shot_nova"))) WeaponName = M_WEAPON_NOVA_STR;
									else if (strstr(WeaponName.c_str(), __xor("shot_sawedoff"))) WeaponName = M_WEAPON_SAWEDOFF_STR;
									else if (strstr(WeaponName.c_str(), __xor("shot_xm1014"))) WeaponName = M_WEAPON_XM1014_STR;
									else if (strstr(WeaponName.c_str(), __xor("mach_m249"))) WeaponName = M_WEAPON_M249_STR;
									else if (strstr(WeaponName.c_str(), __xor("mach_negev"))) WeaponName = M_WEAPON_NEGEV_STR;
									else WeaponName = WeaponName;

									GP_Render->DrawString(TextWorldWeaponSize, Vec2((int)EntityScreen.x, (int)EntityScreen.y), WorldWeaponsColor, true, true, WeaponName.c_str());
								}
								else if (WorldWeaponsStyle == 1)
								{
									if (strstr(WeaponName.c_str(), __xor("rif_ak47"))) WeaponName = __xor("W");
									else if (strstr(WeaponName.c_str(), __xor("rif_aug"))) WeaponName = __xor("U");
									else if (strstr(WeaponName.c_str(), __xor("rif_famas"))) WeaponName = __xor("R");
									else if (strstr(WeaponName.c_str(), __xor("rif_galilar"))) WeaponName = __xor("Q");
									else if (strstr(WeaponName.c_str(), __xor("rif_m4a1_s"))) WeaponName = __xor("T");
									else if (strstr(WeaponName.c_str(), __xor("rif_m4a1"))) WeaponName = __xor("S");
									else if (strstr(WeaponName.c_str(), __xor("rif_sg556"))) WeaponName = __xor("V");
									else if (strstr(WeaponName.c_str(), __xor("pist_223"))) WeaponName = __xor("G");
									else if (strstr(WeaponName.c_str(), __xor("pist_revolver"))) WeaponName = __xor("J");
									else if (strstr(WeaponName.c_str(), __xor("pist_cz_75"))) WeaponName = __xor("I");
									else if (strstr(WeaponName.c_str(), __xor("pist_deagle"))) WeaponName = __xor("A");
									else if (strstr(WeaponName.c_str(), __xor("pist_elite"))) WeaponName = __xor("B");
									else if (strstr(WeaponName.c_str(), __xor("pist_fiveseven"))) WeaponName = __xor("C");
									else if (strstr(WeaponName.c_str(), __xor("pist_glock18"))) WeaponName = __xor("D");
									else if (strstr(WeaponName.c_str(), __xor("pist_hkp2000"))) WeaponName = __xor("F");
									else if (strstr(WeaponName.c_str(), __xor("pist_p250"))) WeaponName = __xor("F");
									else if (strstr(WeaponName.c_str(), __xor("pist_tec9"))) WeaponName = __xor("H");
									else if (strstr(WeaponName.c_str(), __xor("snip_awp"))) WeaponName = __xor("Z");
									else if (strstr(WeaponName.c_str(), __xor("snip_g3sg1"))) WeaponName = __xor("X");
									else if (strstr(WeaponName.c_str(), __xor("snip_scar20"))) WeaponName = __xor("Y");
									else if (strstr(WeaponName.c_str(), __xor("snip_ssg08"))) WeaponName = __xor("a");
									else if (strstr(WeaponName.c_str(), __xor("smg_mac10"))) WeaponName = __xor("K");
									else if (strstr(WeaponName.c_str(), __xor("smg_mp7"))) WeaponName = __xor("N");
									else if (strstr(WeaponName.c_str(), __xor("smg_mp9"))) WeaponName = __xor("O");
									else if (strstr(WeaponName.c_str(), __xor("smg_ump45"))) WeaponName = __xor("L");
									else if (strstr(WeaponName.c_str(), __xor("smg_p90"))) WeaponName = __xor("P");
									else if (strstr(WeaponName.c_str(), __xor("shot_mag7"))) WeaponName = __xor("d");
									else if (strstr(WeaponName.c_str(), __xor("smg_bizon"))) WeaponName = __xor("M");
									else if (strstr(WeaponName.c_str(), __xor("shot_nova"))) WeaponName = __xor("e");
									else if (strstr(WeaponName.c_str(), __xor("shot_sawedoff"))) WeaponName = __xor("c");
									else if (strstr(WeaponName.c_str(), __xor("shot_xm1014"))) WeaponName = __xor("b");
									else if (strstr(WeaponName.c_str(), __xor("mach_m249"))) WeaponName = __xor("g");
									else if (strstr(WeaponName.c_str(), __xor("mach_negev"))) WeaponName = __xor("f");
									else WeaponName = WeaponName;

									if (WeaponName.size() == 1)
										GP_Render->DrawStringIcon(TextWorldWeaponSize, Vec2((int)EntityScreen.x, (int)EntityScreen.y), WorldWeaponsColor, true, true, WeaponName.c_str());
									else
										GP_Render->DrawString(TextWorldWeaponSize, Vec2((int)EntityScreen.x, (int)EntityScreen.y), WorldWeaponsColor, true, true, WeaponName.c_str());
								}
							}
						}
					}

					if (WorldBomb)
					{
						if (pEntity->GetClientClass()->m_ClassID == (int)CLIENT_CLASS_ID::CC4 || pEntity->GetClientClass()->m_ClassID == (int)CLIENT_CLASS_ID::CPlantedC4)
						{
							if (pEntity != (CBaseEntity*)0xB && CGlobal::WorldToScreen(pEntity->GetRenderOrigin(), EntityScreen))
							{
								if (WorldBombStyle == 0)
									GP_Render->DrawString(TextBombSize, Vec2((int)EntityScreen.x, (int)EntityScreen.y), WorldBombColor, true, true, __xor("BOMB"));
								else if (WorldBombStyle == 1)
									GP_Render->DrawStringIcon(TextBombSize, Vec2((int)EntityScreen.x, (int)EntityScreen.y), WorldBombColor, true, true, __xor("o"));
							}
						}
					}

					if (WorldBombInfo)
					{
						if (pEntity != (CBaseEntity*)0xB)
							DrawBombInfo(pEntity, CGlobal::LocalPlayer);
					}
				}
			}
		}
	};
	LWorldEsp();
}

float Calc_Armor(float flDamage, int ArmorValue)
{
	float flArmorRatio = 0.5f;
	float flArmorBonus = 0.5f;
	if (ArmorValue > 0) {
		float flNew = flDamage * flArmorRatio;
		float flArmor = (flDamage - flNew) * flArmorBonus;

		if (flArmor > static_cast<float>(ArmorValue)) {
			flArmor = static_cast<float>(ArmorValue) * (1.f / flArmorBonus);
			flNew = flDamage - flArmor;
		}

		flDamage = flNew;
	}
	return flDamage;
}

void CEsp::DrawBombInfo(CBaseEntity* entity, CBaseEntity* Local)
{
	if (!entity)
		return;

	if (!(entity->GetClientClass()->m_ClassID == (int)CLIENT_CLASS_ID::CPlantedC4))
		return;

	static bool GetDamage = false;
	static bool IsDefusing = false;

	Color Back1(94, 102, 107, 229);
	Color Back2(15, 12, 17, 220);
	Color Back3(0, 0, 0, 0);

	int w_b = 5;
	int h_b = 20;

	if (GetDamage)
		h_b += 20;

	if (IsDefusing)
		h_b += 20;

	int Defus = GetDamage ? 40 : 20;

	GP_Render->DrawFilledBox(0, CGlobal::iScreenHeight / 2 + h_b / 2, w_b, h_b, Back1);
	GP_Render->DrawFilledBox(w_b, CGlobal::iScreenHeight / 2 + h_b / 2, 150, h_b, Back2);
	Vector vOrig; Vector vScreen;

	CBaseEntity* Bomb = (CBaseEntity*)entity;
	float flBlow = Bomb->GetC4BlowTime();
	float lifetime = flBlow - (I::GlobalVars()->interval_per_tick * Local->GetTickBase());

	std::string buf3;
	if (entity->GetBombSite() == 0)
		buf3 = __xor("A");
	else if (entity->GetBombSite() == 1)
		buf3 = __xor("B");
	else
		buf3 = __xor("C 0_o?");

	float flDistance = Local->GetEyePosition().DistTo(entity->GetEyePosition());
	float a = 450.7f;
	float b = 75.68f;
	float c = 789.2f;
	float d = ((flDistance - b) / c);
	float flDamage = a * exp(-d * d);

	float damage = float((std::max)((int)ceilf(Calc_Armor(flDamage, Local->GetArmor())), 0));
	Color EndHp;

	if (lifetime > -2.f && !CGlobal::LocalPlayer->IsDead())
	{
		if (damage >= Local->GetHealth() && !CGlobal::LocalPlayer->IsDead())
			GP_Render->DrawString(15, Vec2(w_b + 4, CGlobal::iScreenHeight / 2 + h_b / 2 + 20), NameColor, true, false, __xor("You will die"));
				
		else if (Local->GetHealth() > damage && !CGlobal::LocalPlayer->IsDead())
		{
			if (Local->GetHealth() - damage > 10)
				EndHp = Color::White();
			else
				EndHp = Color::Red();
			GP_Render->DrawString(15, Vec2(w_b + 4, CGlobal::iScreenHeight / 2 + h_b / 2 + 20), NameColor, true, false, __xor("Health left: %.0f"), Local->GetHealth() - damage);
		}
		GetDamage = true;
	}
	else
		GetDamage = false;

	Color EndTime;

	if (lifetime > 11)
		EndTime = Color::White();
	else
		EndTime = Color::Red();

	if (lifetime > 0)
		GP_Render->DrawString(15, Vec2(w_b + 4, CGlobal::iScreenHeight / 2 + h_b / 2 + 2), NameColor, true, false, __xor("Explosion time [%s]: %.1f"), buf3.c_str(), lifetime);
	else
		GP_Render->DrawString(15, Vec2(w_b + 4, CGlobal::iScreenHeight / 2 + h_b / 2 + 2), NameColor, true, false, __xor("Explosion time [%s]: 0"), buf3.c_str());

	Color EndDefuse;
	if (Bomb->GetBombDefuser() > 0)
	{
		float countdown = Bomb->GetC4DefuseCountDown() - (Local->GetTickBase() * I::GlobalVars()->interval_per_tick);
		if (countdown > 0.01f)
		{
			if (lifetime > countdown)
				EndDefuse = Color::Red();
			else
				EndDefuse = Color::White();

			GP_Render->DrawString(15, Vec2(w_b + 4, CGlobal::iScreenHeight / 2 + h_b / 2 + Defus), EndDefuse, true, false, __xor("Defuse time: %.1f"), countdown);

			IsDefusing = true;
		}
	}
	else
		IsDefusing = false;
}



























































