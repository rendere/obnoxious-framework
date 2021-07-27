#pragma once
#include "../../Engine/Engine.h"
#include "../../Render/DXOverlayManager.h"
#include "../Settings.h"
#include "../../Hooks/MinHook/hook.h"

#define DORMANT_TIME 0.37f

namespace HookTables
{
	using DrawModelExecuteFn = void(__thiscall*)(void*, IMatRenderContext*, const DrawModelState_t&,
		const ModelRenderInfo_t&, matrix3x4_t*);
	extern cDetour<DrawModelExecuteFn>* pDrawModelExecute;
}

class ISoundEsp
{
protected:
	virtual void Add(Vector _Pos, PLAYER_TEAM _Team, int idx) = 0;
	virtual void Draw(CEntityPlayer* Local) = 0;
};

class CSoundEsp : public ISoundEsp
{
public:
	struct SoundInfo
	{
		Vector Pos;
		float Size;
		float EndTime;
		int EntIdx;
		PLAYER_TEAM Team;
	};
	vector<SoundInfo> Sounds;

	virtual void Draw(CEntityPlayer* Local);
	virtual void Add(Vector _Pos, PLAYER_TEAM _Team, int idx);
};

class IEsp
{
public:
	virtual void SoundFrameStage(ClientFrameStage_t Stage) = 0;
	virtual void Draw() = 0;
	virtual void PlayerEsp(CEntityPlayer* Local) = 0;
	virtual void SetPlayerAlpha(float NewAlph) = 0;
	virtual void ResetPlayerAlpha() = 0;
	virtual void DrawPlayerEx(CEntityPlayer* Entity, CEntityPlayer* Local, bool IsDormant) = 0;
	virtual void DrawSkeletonLine(int point1, int point2, CEntityPlayer* Entity) = 0;
	virtual void Draw3DBox(CEntityPlayer* Entity, Color color) = 0;
	virtual void InitMaterials() = 0;

	vector<float> OldAlphs;
};

class CEsp : public IEsp
{
public:
	enum Sides
	{
		LEFT_S,
		RIGHT_S,
		TOP_S,
		DOWN_S,
		LEFT_TOP_S,
		RIGHT_TOP_S,
		LEFT_DOWN_S,
		RIGHT_DOWN_S,
		DOWN_LEFT_DOWN_S,
		DOWN_RIGHT_DOWN_S,
		CENTER_LEFT_S,
		CENTER_RIGHT_S,
	};

	struct MoveStruct
	{
		Vec2 ZonePos;

		Vec2 StartPos;
		Vec2 Position;
		Vec2 Offset;
		Vec2 Correct;
		Vec2 Size;
		Vec2 SizeV;
		Vec2 SizeH;
		Vec2 Center;
		Vec2 CorrectPadding;

		string Name;

		Color Color1;
		Color Color2;
		Color Color3;


		int NumParam1 = 4;
		int NumParam2 = 5;

		int TextSize = 17;

		bool boolParam1 = true;
		bool boolParam2 = true;
		bool boolParam3 = false;

		bool IsHover = false;
		bool Set = false;
		bool IsText = false;
		bool IsEnabled = false;

		int Id = -2;

		Vector CorrectOfst;

		Sides Side = LEFT_S;

		static int ActiveIdx;
		static int LastActive;
		static bool InitMItems;
	};//����������

	enum MITypes : int
	{
		MI_HEALTH_BAR = 0,
		MI_ARMOR_BAR = 1,
		MI_NAME_TEXT = 2,
		MI_WEAPON_TEXT = 3,
		MI_AMMO_TEXT = 4,
		MI_DISTANCE_TEXT = 5,
		MI_MONEY_TEXT = 6,
		MI_SCOPE_TEXT = 7,
		MI_FLASHED_TEXT = 8,
		MI_DEFUSING_TEXT = 9,
		MI_HEALTH_TEXT = 10,
		MI_ARMOR_TEXT = 11,
		MI_MAX
	};//����������

	vector<MoveStruct> MVItemList;
	void Move(MoveStruct &Cont, bool IsPressed, Vec2 MouseP, Vec2 StartP, Vec2 CLines, bool IsText = false); //����������
	enum Orent
	{
		HORIZONTAL,
		VERTICAL
	};

	CConfig Config = CConfig(__xor("Esp"));

	virtual void SoundFrameStage(ClientFrameStage_t Stage);
	virtual void Draw();
	virtual void PlayerEsp(CEntityPlayer* Local);
	virtual void WorldEsp();
	virtual void SetPlayerAlpha(float NewAlph);
	virtual void ResetPlayerAlpha();
	virtual void DrawPlayerEx(CEntityPlayer* Entity, CEntityPlayer* Local, bool IsDormant);
	virtual void DrawSkeletonLine(int point1, int point2, CEntityPlayer* Entity);
	virtual void Draw3DBox(CEntityPlayer* Entity, Color color);
	virtual void InitMaterials();
	virtual void OverrideMaterial(bool IgnoreZ, int dMaterial, int Type, Color RGBA, bool Glow = false, const float Pulse = 0);
	virtual void DrawModelExecute(void* thisptr, IMatRenderContext* ctx, const DrawModelState_t& state, const ModelRenderInfo_t& pInfo, matrix3x4_t* pCustomBoneToWorld);

	void PlaySounds(Vector _Pos, int EntityIdx);
	void Reset();

	void DrawBar(Orent O, float x, float y, float w, float h, float val, bool Outline, Color MainC1, Color cBack, bool bBack, int Razd, bool Revers, Color OutlineCol);//����������
	void InitVisuals();//����������
	void VisualPreview(); //����������
	void CustomVisuals(Vec2 Start); //����������

	virtual void DrawBombInfo(CBaseEntity* entity, CBaseEntity* Local);

	void SaveVisuals(nlohmann::json &j);
	void LoadVisuals(nlohmann::json &j);

	void Menu();

	/*Material for chams/glow*/
	IMaterial* Texture = nullptr;
	IMaterial* Flat = nullptr;
	IMaterial* Metallic = nullptr;
	IMaterial* MetallicPlus = nullptr;
	IMaterial* Pearlescent = nullptr;
	IMaterial* Animated = nullptr;
	IMaterial* GlowDef = nullptr;
	IMaterial* GlowSPulse = nullptr;
	IMaterial* GlowDPulse = nullptr;
	/*=======================*/

	bool ShowPreview = true;

	CBind BindEnable = CBind(0x4E);

	CSoundEsp SoundEsp;

	bool Enable = true;
	bool Enemy = false;
	bool Team = false;
	bool BoxEnable = false;
	bool BoxVisibleOnly = false;
	int BoxStyle = 0;
	int BoxSize = 10;
	bool BoxOutline = false;
	bool Glow = false;
    bool GlowVisibleOnly = false;
	int GlowStyle = 0;
	int GlowPulseSpeed = 0;
	float GlowPulseRange = 0;
	bool Chams = false;
	bool ChamsVisibleOnly = false;
	int  ChamsStyle = 0;
	int ChamsDouble = 0;
	bool FillBox = false;
	bool HeadEsp = false;
	bool Line = false;
	bool Skeleton = false;
	bool SoundEspEnable = false;
	int SoundEspStyle = 0;
	int SoundEspSize = 20;
	bool SoundEspDistance = false;
	bool WorldGrenade = false;
	int WorldGrenadeStyle = 0;
	bool WorldWeapons = false;
	int WorldWeaponsStyle = 0;
	bool WorldBomb = false;
	int WorldBombStyle = 0;
	bool WorldBombInfo = false;
	bool GranadePrediction = false;
	bool Health = false;
	int HealthStyle = 0;
	bool Armor = false;
	int ArmorStyle = 0;
	bool Distance = false;
	bool Weapon = false;
	int WeaponStyle = 0;
	bool Ammo = false;
	int AmmoStyle = 0;
	bool Name = false;
	bool NameBackground = false;
	bool Money = false;
	bool Flashing = false;
	bool Defusing = false;
	bool Scope = false;

	int TextNameSize = 15;
	int TextWeaponSize = 15;
	int TextAmmoSize = 15;
	int TextDistanceSize = 15;
	int TextMoneySize = 15;
	int TextScopedSize = 15;
	int TextFlashedSize = 15;
	int TextDefusingSize = 15;
	int TextHealthSize = 15;
	int TextArmorSize = 15;
	int TextSoundSize = 15;

	int TextGrenadeSize = 15;
	int TextBombSize = 15;
	int TextWorldWeaponSize = 15;


	Color BoxCT = Color(255, 0, 0, 255);
	Color BoxTT = Color(255, 0, 0, 255);
	Color BoxVisibleCT = Color(0, 255, 0, 255);
	Color BoxVisibleTT = Color(0, 255, 0, 255);
	Color GlowCT = Color(255, 0, 0, 255);
	Color GlowTT = Color(255, 0, 0, 255);
	Color GlowVisibleCT = Color(0, 255, 0, 255);
	Color GlowVisibleTT = Color(0, 255, 0, 255);
	Color ChamsCT = Color(255, 0, 0, 255);
	Color ChamsTT = Color(255, 0, 0, 255);
	Color ChamsVisibleCT = Color(0, 255, 0, 255);
	Color ChamsVisibleTT = Color(0, 255, 0, 255);
	Color FillBoxColor = Color(10, 255, 10, 40);
	Color HeadEspColor = Color(10, 255, 255, 255);
	Color LineColor = Color(10, 255, 255, 255);
	Color SkeletonColor = Color(100, 0, 255, 255);
	Color SoundColor = Color(255, 255, 255, 255);
	Color SoundDistanceColor = Color(255, 255, 255, 255);
	Color HEGrenadeColor = Color(255, 164, 0, 255);
	Color MolotovGrenadeColor = Color(255, 0, 0, 255);
	Color FlashGrenadeColor = Color(255, 255, 0, 255);
	Color IncGrenadeColor = Color(255, 0, 0, 255);
	Color SmokeGrenadeColor = Color(0, 141, 255, 255);
	Color DecoyGrenadeColor = Color(255, 255, 255, 255);
	Color WorldWeaponsColor = Color(255, 255, 255, 255);
	Color WorldBombColor = Color(50, 255, 0, 255);
	Color GranadePredictionColor = Color(228, 255, 0, 255);
	Color HealthColor = Color(0, 255, 0, 255);
	Color HealthColor2 = Color(255, 0, 0, 255);
	Color HealthColor3 = Color(0, 0, 0, 255);
	Color ArmorColor = Color(255, 255, 255, 255);
	Color ArmorColor2 = Color(255, 0, 0, 255);
	Color ArmorColor3 = Color(0, 0, 0, 255);
	Color DistanceColor = Color(255, 255, 255, 255);
	Color WeaponColor = Color(255, 255, 255, 255);
	Color AmmoColor = Color(255, 255, 255, 255);
	Color NameColor = Color(255, 255, 255, 255);
	Color NameColorBack = Color(10, 10, 10, 255);
	Color MoneyColor = Color(255, 255, 255, 255);
	Color FlashingColor = Color(255, 255, 255, 255);
	Color DefusingColor = Color(255, 255, 255, 255);
	Color ScopeColor = Color(255, 255, 255, 255);

	CEsp()
	{
		for (int i(0); (MITypes)i < MI_MAX; i++)
			MVItemList.push_back(MoveStruct());

		RV(Enable, "Enable");
		RV(BoxEnable, "BoxEnable");
		RV(BoxSize, "BoxSize");
		RV(BoxCT, "BoxCT");
		RV(BoxTT, "BoxTT");
		RV(BoxVisibleCT, "BoxVisibleCT");
		RV(BoxVisibleTT, "BoxVisibleTT");
		RV(GlowCT, "GlowCT");
		RV(GlowTT, "GlowTT");
		RV(GlowVisibleCT, "GlowVisbleCT");
		RV(GlowVisibleTT, "GlowVisbleTT");
		RV(ChamsCT, "ChamsCT");
		RV(ChamsTT, "ChamsTT");
		RV(ChamsVisibleCT, "ChamsVisibleCT");
		RV(ChamsVisibleTT, "ChamsVisibleTT");
		RV(FillBoxColor, "FillBoxColor");
		RV(HeadEspColor, "HeadEspColor");
		RV(LineColor, "LineColor");
		RV(SkeletonColor, "SkeletonColor");
		RV(SoundColor, "SoundColor");
		RV(HEGrenadeColor, "HEGrenadeColor");
		RV(MolotovGrenadeColor, "MolotovGrenadeColor");
		RV(FlashGrenadeColor, "FlashGrenadeColor");
		RV(IncGrenadeColor, "IncGrenadeColor");
		RV(SmokeGrenadeColor, "SmokeGrenadeColor");
		RV(DecoyGrenadeColor, "DecoyGrenadeColor");
		RV(WorldWeaponsColor, "WorldWeaponsColor");
		RV(WorldBombColor, "WorldBombColor");
		RV(GranadePredictionColor, "GranadePredictionColor");
		RV(HealthColor, "HealthColor");
		RV(HealthColor2, "HealthColor2");
		RV(HealthColor3, "HealthColor3");
		RV(ArmorColor, "ArmorColor");
		RV(ArmorColor2, "ArmorColor2");
		RV(ArmorColor3, "ArmorColor3");
		RV(DistanceColor, "DistanceColor");
		RV(WeaponColor, "WeaponColor");
		RV(AmmoColor, "AmmoColor");
		RV(NameColor, "NameColor");
		RV(NameColorBack, "NameColorBack");
		RV(MoneyColor, "MoneyColor");
		RV(FlashingColor, "FlashingColor");
		RV(DefusingColor, "DefusingColor");
		RV(ScopeColor, "ScopeColor");
		RV(SoundDistanceColor, "SoundDistanceColor");

		RV(Enemy, "Enemy");
		RV(Team, "Team");
		RV(BoxEnable, "BoxEnable");
		RV(BoxVisibleOnly, "BoxVisbleOnly");
		RV(BoxStyle, "BoxStyle");
		RV(BoxSize, "BoxSize");
		RV(BoxOutline, "BoxOutline");
		RV(Glow, "Glow");
		RV(GlowVisibleOnly, "GlowVisibleOnly");
		RV(GlowStyle, "GlowStyle");
		RV(GlowPulseSpeed, "GlowPulseSpeed");
		RV(GlowPulseRange, "GlowPulseRange");
		RV(Chams, "Chams");
		RV(ChamsVisibleOnly, "ChamsVisbleOnly");
		RV(ChamsStyle, "ChamsStyle");
		RV(ChamsDouble, "ChamsDouble");
		RV(FillBox, "FillBox");
		RV(HeadEsp, "HeadEsp");
		RV(Line, "Line");
		RV(Skeleton, "Skeleton");
		RV(SoundEspEnable, "SoundEspEnable");
		RV(SoundEspStyle, "SoundEspStyle");
		RV(SoundEspSize, "SoundEspSize");
		RV(SoundEspDistance, "SoundEspDistance");
		RV(WorldGrenade, "WorldGrenade");
		RV(WorldGrenadeStyle, "WorldGrenadeStyle");
		RV(WorldWeapons, "WorldWeapons");
		RV(WorldWeaponsStyle, "WorldWeaponsStyle");
		RV(WorldBomb, "WorldBomb");
		RV(WorldBombStyle, "WorldBombStyle");
		RV(WorldBombInfo, "WorldBombInfo");
		RV(GranadePrediction, "GranadePrediction");
		RV(Health, "Health");
		RV(HealthStyle, "HealthStyle");
		RV(Armor, "Armor");
		RV(ArmorStyle, "ArmorStyle");
		RV(Distance, "Distance");
		RV(Weapon, "Weapon");
		RV(WeaponStyle, "WeaponStyle");
		RV(Ammo, "Ammo");
		RV(AmmoStyle, "AmmoStyle");
		RV(Name, "Name");
		RV(NameBackground, "NameBackground");
		RV(Money, "Money");
		RV(Flashing, "Flashing");
		RV(Defusing, "Defusing");
		RV(Scope, "Scope");

		RV(TextNameSize, "TextNameSize");
		RV(TextWeaponSize, "TextWeaponSize");
		RV(TextAmmoSize, "TextAmmoSize");
		RV(TextDistanceSize, "TextDistanceSize");
		RV(TextMoneySize, "TextMoneySize");
		RV(TextScopedSize, "TextScopedSize");
		RV(TextFlashedSize, "TextFlashedSize");
		RV(TextDefusingSize, "TextDefusingSize");
		RV(TextHealthSize, "TextHealthSize");
		RV(TextArmorSize, "TextArmorSize");
		RV(TextSoundSize, "TextSoundSize");
		RV(TextGrenadeSize, "TextGrenadeSize");
		RV(TextBombSize, "TextBombSize");
		RV(TextWorldWeaponSize, "TextWorldWeaponSize");
		RV(BindEnable, "BindEnable");

		debug_log("Setup: CEsp sucessful\n");
	}
};