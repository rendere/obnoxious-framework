#include "Esp.h"
#include "../Setup.h"

void CEsp::Draw()
{
	if (Enable)
	{
		CEntityPlayer* Local = GP_EntPlayers->EntityLocal;
		auto LDraw = [&]()->void
		{
			if (SoundEspEnable)
				SoundEsp.Draw(Local);

			WorldEsp();
			PlayerEsp(Local);
		};
		LDraw();
	}
}

void CEsp::Reset()
{
	if (SoundEsp.Sounds.size() > 0)
		SoundEsp.Sounds.clear();
}
vector<Vector> AddedPos;
void CEsp::PlaySounds(Vector _Pos, int EntityIdx)
{
	CEntityPlayer* Entity = GP_EntPlayers->FindByIdx(EntityIdx);
	if (Entity)
	{
		if (!Entity->IsLocal)
		{
			for (size_t i(0); i < AddedPos.size(); i++)
				if (AddedPos[i] == _Pos)
					return;

			if (AddedPos.size() > 100)
				AddedPos.clear();

			if (_Pos.DistTo(Entity->AbsOrigin) < 10.f)
			{
				GP_Esp->SoundEsp.Add(_Pos, Entity->Team, EntityIdx);
			}

			AddedPos.push_back(_Pos);
		}
	}
}

void CSoundEsp::Add(Vector _Pos, PLAYER_TEAM _Team, int idx)
{
	SoundInfo Sound;
	Sound.EndTime = I::GlobalVars()->curtime + 1.0f;
	Sound.Pos = _Pos;
	Sound.EntIdx = idx;
	if (GP_Esp)
	{
		if (GP_Esp->SoundEspStyle == 1)
			Sound.Size = 1.f;
		else
			Sound.Size = GP_Esp->SoundEspSize;
	}
	Sound.Team = _Team;

	Sounds.push_back(Sound);
}

void CSoundEsp::Draw(CEntityPlayer* Local)
{
	if (Local && GP_Esp)
	{
		for (size_t i = 0; i < Sounds.size(); i++)
		{
			Vector ScreenPos;

			if (Sounds[i].Team != Local->Team ? GP_Esp->Enemy : GP_Esp->Team)
			{
				if (CGlobal::WorldToScreen(Sounds[i].Pos, ScreenPos))
				{
					float Size = GP_Esp->SoundEspSize;

					switch (GP_Esp->SoundEspStyle)
					{
					case 0: GP_Render->DrawRing3D(Sounds[i].Pos.x, Sounds[i].Pos.y, Sounds[i].Pos.z, Size, 32, GP_Esp->SoundColor); break;
					case 1:
					{
						if (Sounds[i].Size < Size)
							Sounds[i].Size += 0.4f;

						GP_Render->DrawRing3D(Sounds[i].Pos.x, Sounds[i].Pos.y, Sounds[i].Pos.z, Sounds[i].Size, 32, GP_Esp->SoundColor);
						break;
					}
					case 2:
					{
						if (Sounds[i].Size > 1.f)
							Sounds[i].Size -= 0.4f;

						GP_Render->DrawRing3D(Sounds[i].Pos.x, Sounds[i].Pos.y, Sounds[i].Pos.z, Sounds[i].Size, 32, GP_Esp->SoundColor);
						break;
					}
					case 3: GP_Render->DrawBox((int)ScreenPos.x - (Size / 2), (int)ScreenPos.y - (Size / 2), (int)Size, (int)Size, 1, GP_Esp->SoundColor); break;
					case 4: GP_Render->DrawFilledBox((int)ScreenPos.x - (Size / 2), (int)ScreenPos.y - (Size / 2), (int)Size, (int)Size, GP_Esp->SoundColor); break;
					case 5:
					{
						GP_Render->DrawLine((int)ScreenPos.x - (int)Size, (int)ScreenPos.y, (int)ScreenPos.x + (int)Size + 1, (int)ScreenPos.y, GP_Esp->SoundColor);
						GP_Render->DrawLine((int)ScreenPos.x, (int)ScreenPos.y - (int)Size, (int)ScreenPos.x, (int)ScreenPos.y + (int)Size + 1, GP_Esp->SoundColor);
						GP_Render->DrawLine((int)ScreenPos.x + (int)Size, (int)ScreenPos.y - (int)Size, (int)ScreenPos.x - (int)Size, (int)ScreenPos.y + Size, GP_Esp->SoundColor);
						GP_Render->DrawLine((int)ScreenPos.x - (int)Size, (int)ScreenPos.y - (int)Size, (int)ScreenPos.x + (int)Size, (int)ScreenPos.y + Size, GP_Esp->SoundColor);
						break;
					}
					default: break;
					}

					if (GP_Esp->SoundEspDistance)
					{
						GP_Render->DrawString(GP_Esp->TextSoundSize, Vec2((int)ScreenPos.x, (int)ScreenPos.y),
							GP_Esp->SoundDistanceColor, true, true, __xor("%6.1lfm"), Sounds[i].Pos.DistTo(Local->AbsOrigin) / 33);
					}
				}
			}

			if (Sounds[i].EndTime <= I::GlobalVars()->curtime)
				if (CGlobal::IsGameReady)
					Sounds.erase(Sounds.begin() + i);
		}
	}
}

void CEsp::SoundFrameStage(ClientFrameStage_t Stage)
{
	if (Enable && SoundEspEnable)
	{
		if (Stage == FRAME_NET_UPDATE_END)
		{
			CUtlVector<SndInfo_t> sndList;
			sndList.RemoveAll();
			I::Sound()->GetActiveSounds(sndList);
			if (sndList.Count() < 1)
				return;

			for (int i = 0; i < sndList.Count(); i++)
			{
				SndInfo_t& sound = sndList.Element(i);

				if (sound.m_nSoundSource < 1)
					continue;

				if (!sndList[i].m_pOrigin || !sndList[i].m_nSoundSource || !sndList[i].m_bUpdatePositions || sndList[i].m_nChannel != 4)
					continue;

				if (CGlobal::LocalPlayer->GetAbsOrigin().DistTo(*sndList[i].m_pOrigin) > 900)
					continue;

				GP_Esp->PlaySounds(*sndList[i].m_pOrigin, sndList[i].m_nSoundSource);
			}
		}
	}
}

void CEsp::InitMaterials()
{
	if (!Texture)
		Texture = I::MaterialSystem()->CreateMaterial("Texture", KeyValues::FromString("VertexLitGeneric", nullptr));

	if (!Flat)
		Flat = I::MaterialSystem()->CreateMaterial("Flat", KeyValues::FromString("UnlitGeneric", nullptr));

	if (!Metallic)
		Metallic = I::MaterialSystem()->CreateMaterial("Mettalic", KeyValues::FromString("VertexLitGeneric",
			"$basetexture white $envmap env_cubemap $normalmapalphaenvmapmask 1 $envmapcontrast 1 $nofog 1 $model 1 $nocull 0 $selfillum 1 $halfambert 1 $znearer 0 $flat 1"));

	if (!MetallicPlus)
		MetallicPlus = I::MaterialSystem()->CreateMaterial("Mettalic", KeyValues::FromString("VertexLitGeneric",
			"$envmap env_cubemap $envmapcontrast 1 $envmapsaturation 1.0 $phong 1 $phongexponent 15.0 $normalmapalphaenvmask 1 $phongboost 6.0"));

	if (!Pearlescent)
		Pearlescent = I::MaterialSystem()->CreateMaterial("Pearlescent", KeyValues::FromString("VertexLitGeneric",
			"$ambientonly 1 $phong 1 $pearlescent 3 $basemapalphaphongmask 1"));

	if (!Animated)
	{
		const auto kv = KeyValues::FromString("VertexLitGeneric", 
			"$basetexture white $envmap editor/cube_vertigo $envmapcontrast 1 $basetexture dev/zone_warning proxies\
			 { texturescroll { texturescrollvar $basetexturetransform texturescrollrate 0.6 texturescrollangle 90 } }");
		kv->SetString("$envmaptint", "[.7 .7 .7]");
		Animated = I::MaterialSystem()->CreateMaterial("Animated", kv);
	}

	if (!GlowDef)
		GlowDef = I::MaterialSystem()->CreateMaterial("GlowDefault", KeyValues::FromString("VertexLitGeneric",
			"$additive 1 $envmap models/effects/cube_white $envmapfresnel 1"));

	if (!GlowSPulse)
		GlowSPulse = I::MaterialSystem()->FindMaterial("dev/glow_armsrace.vmt");

	if (!GlowDPulse)
		GlowDPulse = I::MaterialSystem()->CreateMaterial("GlowDPulse", KeyValues::FromString("VertexLitGeneric",
			"$additive 1 $envmap models/effects/cube_white $envmapfresnel 1"));
}

void CEsp::OverrideMaterial(bool IgnoreZ, int dMaterial, int Type, Color RGBA, bool Glow, const float Pulse)
{
	if (!Glow)
	{
		IMaterial* ChamsMaterial = nullptr;
		switch (Type)
		{
		case 0: ChamsMaterial = Texture; break;
		case 1: ChamsMaterial = Flat; break;
		case 2: ChamsMaterial = Metallic; break;
		case 3: ChamsMaterial = MetallicPlus; break;
		case 4: ChamsMaterial = Pearlescent; break;
		case 5: ChamsMaterial = Animated; break;
		default: 
			break;
		}

		if (!ChamsMaterial || ChamsMaterial->IsErrorMaterial())
			return;

		if (ChamsMaterial == MetallicPlus)
		{
			static bool bFoundColor = false;
			IMaterialVar* pMatColor = ChamsMaterial->FindVar("$envmaptint", &bFoundColor);
			if (bFoundColor)
				pMatColor->SetVecValue(RGBA.G1R(), RGBA.G1G(), RGBA.G1B());
		}
		else
			ChamsMaterial->ColorModulate(RGBA.G1R(), RGBA.G1G(), RGBA.G1B());

		ChamsMaterial->AlphaModulate(RGBA.G1A());

		ChamsMaterial->SetMaterialVarFlag(MATERIAL_VAR_WIREFRAME, (dMaterial == 1) ? true : false);
		ChamsMaterial->SetMaterialVarFlag(MATERIAL_VAR_IGNOREZ, IgnoreZ);
		ChamsMaterial->IncrementReferenceCount();

		I::ModelRender()->ForcedMaterialOverride(ChamsMaterial);
	}
	else
	{
		IMaterial* GlowMaterial = nullptr;
		switch (Type)
		{
		case 0: GlowMaterial = GlowDef; break;
		case 1: GlowMaterial = GlowSPulse; break;
		case 2: GlowMaterial = GlowDPulse; break;
		default: 
			break;
		}

		if (!GlowMaterial || GlowMaterial->IsErrorMaterial())
			return;

		if (GlowMaterial == GlowDPulse)
		{
			static bool bFoundPulse = false;
			IMaterialVar* pMatPulse = GlowMaterial->FindVar("$envmapfresnelminmaxexp", &bFoundPulse);
			if (bFoundPulse)
				pMatPulse->SetVecComponentValue(0.5f * (1.2f - Pulse), 2);
		}

		static bool bFoundColor = false;
		IMaterialVar* pMatColor = GlowMaterial->FindVar("$envmaptint", &bFoundColor);
		if (bFoundColor)
			pMatColor->SetVecValue(RGBA.G1R(), RGBA.G1G(), RGBA.G1B());

		GlowMaterial->AlphaModulate(RGBA.G1A());

		GlowMaterial->SetMaterialVarFlag(MATERIAL_VAR_IGNOREZ, IgnoreZ);
		GlowMaterial->IncrementReferenceCount();

		I::ModelRender()->ForcedMaterialOverride(GlowMaterial);
	}
}

void CEsp::LoadVisuals(nlohmann::json &j)
{
#define LV(a,b) if(!j[__xor("Esp")][__xor("CustomVisuals")][MVItemList[i].Name][__xor(a)].is_null()) {b = j[__xor("Esp")][__xor("CustomVisuals")][MVItemList[i].Name][__xor(a)];}

	if (!j[__xor("Esp")].is_null())
	{
		if (!j[__xor("Esp")][__xor("CustomVisuals")].is_null())
		{
			for (int i(0); (MITypes)i < MI_MAX; i++)
			{
				LV("ZonePX", MVItemList[i].ZonePos.x);
				LV("ZonePY", MVItemList[i].ZonePos.y);

				LV("StartPX", MVItemList[i].StartPos.x);
				LV("StartPY", MVItemList[i].StartPos.y);

				LV("PositionPX", MVItemList[i].Position.x);
				LV("PositionPY", MVItemList[i].Position.y);

				LV("OffsetPX", MVItemList[i].Offset.x);
				LV("OffsetPY", MVItemList[i].Offset.y);

				LV("CorrectPX", MVItemList[i].Correct.x);
				LV("CorrectPY", MVItemList[i].Correct.y);

				LV("SizePX", MVItemList[i].Size.x);
				LV("SizePY", MVItemList[i].Size.y);

				LV("SizeVPX", MVItemList[i].SizeV.x);
				LV("SizeVPY", MVItemList[i].SizeV.y);

				LV("SizeHPX", MVItemList[i].SizeH.x);
				LV("SizeHPY", MVItemList[i].SizeH.y);

				LV("CenterPX", MVItemList[i].Center.x);
				LV("CenterPY", MVItemList[i].Center.y);

				LV("CorrectPaddingPX", MVItemList[i].CorrectPadding.x);
				LV("CorrectPaddingPY", MVItemList[i].CorrectPadding.y);

				LV("IsText", MVItemList[i].IsText);
				if (!MVItemList[i].IsText)
				{
					LV("Color1R", MVItemList[i].Color1[0]);
					LV("Color1G", MVItemList[i].Color1[1]);
					LV("Color1B", MVItemList[i].Color1[2]);

					LV("Color2R", MVItemList[i].Color2[0]);
					LV("Color2G", MVItemList[i].Color2[1]);
					LV("Color2B", MVItemList[i].Color2[2]);

					LV("Color3R", MVItemList[i].Color3[0]);
					LV("Color3G", MVItemList[i].Color3[1]);
					LV("Color3B", MVItemList[i].Color3[2]);



					LV("NumP1", MVItemList[i].NumParam1);
					LV("NumP2", MVItemList[i].NumParam2);

					LV("BoolP1", MVItemList[i].boolParam1);
					LV("BoolP2", MVItemList[i].boolParam2);
					LV("BoolP3", MVItemList[i].boolParam3);

				}
				else
				{
					LV("Color1R", MVItemList[i].Color1[0]);
					LV("Color1G", MVItemList[i].Color1[1]);
					LV("Color1B", MVItemList[i].Color1[2]);
				}
				LV("TexSZ", MVItemList[i].TextSize);
				LV("IsEnabled", MVItemList[i].IsEnabled);
				LV("Id", MVItemList[i].Id);

				LV("CorrectOfstPX", MVItemList[i].CorrectOfst.x);
				LV("CorrectOfstPY", MVItemList[i].CorrectOfst.y);

				MVItemList[i].Side = (Sides)(int)j[__xor("Esp")][__xor("CustomVisuals")][MVItemList[i].Name][__xor("Side")];

				LV("ActiveIdx", MVItemList[i].ActiveIdx);
				LV("LastActive", MVItemList[i].LastActive);
				LV("InitMItems", MVItemList[i].InitMItems);
			}
		}
	}
}
void CEsp::SaveVisuals(nlohmann::json &j)
{
#define SV(a,b) j[__xor("Esp")][__xor("CustomVisuals")][MVItemList[i].Name][__xor(a)] = b;

	for (int i(0); (MITypes)i < MI_MAX; i++)
	{
		SV("ZonePX", MVItemList[i].ZonePos.x);
		SV("ZonePY", MVItemList[i].ZonePos.y);

		SV("StartPX", MVItemList[i].StartPos.x);
		SV("StartPY", MVItemList[i].StartPos.y);

		SV("PositionPX", MVItemList[i].Position.x);
		SV("PositionPY", MVItemList[i].Position.y);

		SV("OffsetPX", MVItemList[i].Offset.x);
		SV("OffsetPY", MVItemList[i].Offset.y);

		SV("CorrectPX", MVItemList[i].Correct.x);
		SV("CorrectPY", MVItemList[i].Correct.y);

		SV("SizePX", MVItemList[i].Size.x);
		SV("SizePY", MVItemList[i].Size.y);

		SV("SizeVPX", MVItemList[i].SizeV.x);
		SV("SizeVPY", MVItemList[i].SizeV.y);

		SV("SizeHPX", MVItemList[i].SizeH.x);
		SV("SizeHPY", MVItemList[i].SizeH.y);

		SV("CenterPX", MVItemList[i].Center.x);
		SV("CenterPY", MVItemList[i].Center.y);

		SV("CorrectPaddingPX", MVItemList[i].CorrectPadding.x);
		SV("CorrectPaddingPY", MVItemList[i].CorrectPadding.y);

		SV("IsText", MVItemList[i].IsText);
		if (!MVItemList[i].IsText)
		{
			SV("Color1R", MVItemList[i].Color1[0]);
			SV("Color1G", MVItemList[i].Color1[1]);
			SV("Color1B", MVItemList[i].Color1[2]);

			SV("Color2R", MVItemList[i].Color2[0]);
			SV("Color2G", MVItemList[i].Color2[1]);
			SV("Color2B", MVItemList[i].Color2[2]);

			SV("Color3R", MVItemList[i].Color3[0]);
			SV("Color3G", MVItemList[i].Color3[1]);
			SV("Color3B", MVItemList[i].Color3[2]);



			SV("NumP1", MVItemList[i].NumParam1);
			SV("NumP2", MVItemList[i].NumParam2);

			SV("BoolP1", MVItemList[i].boolParam1);
			SV("BoolP2", MVItemList[i].boolParam2);
			SV("BoolP3", MVItemList[i].boolParam3);

		}
		else
		{
			SV("Color1R", MVItemList[i].Color1[0]);
			SV("Color1G", MVItemList[i].Color1[1]);
			SV("Color1B", MVItemList[i].Color1[2]);
		}
		SV("TexSZ", MVItemList[i].TextSize);
		SV("IsEnabled", MVItemList[i].IsEnabled);
		SV("Id", MVItemList[i].Id);

		SV("CorrectOfstPX", MVItemList[i].CorrectOfst.x);
		SV("CorrectOfstPY", MVItemList[i].CorrectOfst.y);

		SV("Side", (int)MVItemList[i].Side);

		SV("ActiveIdx", MVItemList[i].ActiveIdx);
		SV("LastActive", MVItemList[i].LastActive);
		SV("InitMItems", MVItemList[i].InitMItems);
	}
}



























































