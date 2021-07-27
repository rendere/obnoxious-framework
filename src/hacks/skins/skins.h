#pragma once
#include "../../Main.h"
#include "../Settings.h"
#include "../../Render/DXOverlayManager.h"
#include <limits> 
#include <unordered_map> 
#include <string>
#include <cstdlib>

using namespace std;

class CSkinListener : public IGameEventListener2
{
public:
	void RegListener();
	void UnRegListener();

	void FireGameEvent(IGameEvent *pEvent) override;
};

class ISkins
{
public:

	struct paint_kit
	{
		int id;
		string name;
		string name_eng;
		string cdn_name;

		paint_kit() {}
		paint_kit(int _id, string _name, string _name_eng, string _cdn_name) : id(_id), name(_name), name_eng(_name_eng), cdn_name(_cdn_name) { }
	};

	virtual void Menu() = 0;
	//virtual void Preview() = 0;
	//auto initialize_kits() -> void;

	virtual void PostDataUpdate(ClientFrameStage_t Stage) = 0;
	virtual void RecvProxy_Viewmodel(CRecvProxyData *pData, void *pStruct, void *pOut) = 0;

	virtual void ApplyCustomSkin(CBaseAttributableItem* pWeapon, int nWeaponIndex, bool IsTT) = 0;
	virtual void ApplyCustomModel(CBaseEntity* pLocal, CBaseAttributableItem* pWeapon) = 0;
	virtual bool IsKnife(int idx) = 0;
	virtual bool GetWeaponByDefIdx(int Idx, int &ListIdx, bool IsKnife, bool IsTT) = 0;

	virtual void ApplyStickerHooks(CBaseAttributableItem* pItem) = 0;
	virtual int StickWeaponByDefIndex(int DefIdx) = 0;

	virtual void ParseSortedKits() = 0;
	virtual void PrepareSortedSkins() = 0;

	virtual void UpdateSkins(bool reset = true) = 0;

	virtual void SetKillIconCfg() = 0;

	struct StickerSettings
	{
		int kit = 0;
		int kit_menu_index = 0;
		float wear = 0.000000001f;
		float scale = 1.f;
		float rotation = 0.f;

#define CHECK_VAR(l, r) if(l != src.##r) return false;
		bool operator==(const StickerSettings& src) const
		{
			CHECK_VAR(kit, kit);
			CHECK_VAR(kit_menu_index, kit_menu_index);
			CHECK_VAR(wear, wear);
			CHECK_VAR(scale, scale);
			CHECK_VAR(rotation, rotation);
			return true;
		}
	};

	struct SkinSettings
	{
		StickerSettings Stickers[5];
		float wear = 0.000000001f;
		float seed = 0.000000001f;
		bool auto_stat_track = false;
		int stat_track = 0;
		int rarity = 0;
		int quality = 0;
		char custom_name[32] = "";
		int paint_kit_id = 0;
		int paint_kit_menu = 0;
		int skins_mode = 1;

#define CHECK_VAR(l, r) if(l != src.##r) return false;
		bool operator==(const SkinSettings& src) const
		{
			CHECK_VAR(wear, wear);
			CHECK_VAR(seed, seed);
			CHECK_VAR(auto_stat_track, auto_stat_track);
			CHECK_VAR(stat_track, stat_track);
			CHECK_VAR(rarity, rarity);
			CHECK_VAR(quality, quality);
			CHECK_VAR(custom_name, custom_name);
			CHECK_VAR(paint_kit_id, paint_kit_id);
			CHECK_VAR(paint_kit_menu, paint_kit_menu);
			CHECK_VAR(skins_mode, skins_mode);

			return true;
		}
	};

	struct ItemSettings
	{
		ItemSettings(WEAPON_ID _ID, string _Name, string _CdnName, SkinSettings _Skin) :
			ID(_ID), Name(_Name), CdnName(_CdnName), Skin(_Skin), SkinTT(_Skin), IsInventory(false){}
		WEAPON_ID ID;
		string Name = "";
		string CdnName = "";
		SkinSettings Skin;
		SkinSettings SkinTT;
		bool IsInventory;
	};

	struct WeaponSkin
	{
		WEAPON_ID WeaponId;
		vector<paint_kit> skin_kits;
	};

#define lol(e) string(__xor(e))

	vector<ItemSettings> WeaponNames =
	{
	{ WEAPON_DEAGLE,	lol("Deagle"), lol("deagle"), SkinSettings() },
	{ WEAPON_ELITE,		lol("Elite"), lol("elite"), SkinSettings() },
	{ WEAPON_FIVESEVEN, lol("Five-Seven"), lol("fiveseven"), SkinSettings() },
	{ WEAPON_GLOCK,		lol("Glock-18"), lol("glock"), SkinSettings() },
	{ WEAPON_HKP2000,	lol("P2000"), lol("hkp2000"), SkinSettings() },
	{ WEAPON_P250,		lol("P250"), lol("p250"), SkinSettings() },
	{ WEAPON_USP_SILENCER, lol("USP-S"), lol("usp_silencer"), SkinSettings() },
	{ WEAPON_CZ75A,		lol("CZ-75"), lol("cz75a"), SkinSettings() },
	{ WEAPON_REVOLVER,	lol("R8 Revolver"), lol("revolver"), SkinSettings() },
	{ WEAPON_TEC9,		lol("Tec-9"), lol("tec9"), SkinSettings() },
	{ WEAPON_AK47,		lol("AK-47"), lol("ak47"), SkinSettings() },
	{ WEAPON_AUG,		lol("AUG"), lol("aug"), SkinSettings() },
	{ WEAPON_FAMAS,		lol("Famas"), lol("famas"), SkinSettings() },
	{ WEAPON_GALILAR,	lol("Galilar"), lol("galilar"), SkinSettings() },
	{ WEAPON_M249,		lol("M249"), lol("m249"), SkinSettings() },
	{ WEAPON_M4A4,		lol("M4A4"), lol("m4a4"), SkinSettings() },
	{ WEAPON_M4A1_SILENCER, lol("M4A1-S"), lol("m4a1_silencer"), SkinSettings() },
	{ WEAPON_MAC10, lol("MAC-10"), lol("mac10"), SkinSettings() },
	{ WEAPON_P90,		lol("P90"), lol("p90"), SkinSettings() },
	{ WEAPON_UMP45,		lol("UMP-45"), lol("ump45"), SkinSettings() },
	{ WEAPON_MP5,		lol("MP5-SD"), lol("mp5"), SkinSettings() },
	{ WEAPON_XM1014,	lol("XM1014"), lol("xm1014"), SkinSettings() },
	{ WEAPON_BIZON,	    lol("Bizon"), lol("bizon"), SkinSettings() },
	{ WEAPON_MAG7,	    lol("MAG-7"), lol("mag7"), SkinSettings() },
	{ WEAPON_NEGEV,	    lol("Negev"), lol("negev"), SkinSettings() },
	{ WEAPON_SAWEDOFF,  lol("Sawed-Off"), lol("sawedoff"), SkinSettings() },
	{ WEAPON_MP7,	lol("MP7"), lol("mp7"), SkinSettings() },
	{ WEAPON_MP9,	lol("MP9"), lol("mp9"), SkinSettings() },
	{ WEAPON_NOVA,	lol("Nova"), lol("nova"), SkinSettings() },
	{ WEAPON_SG553,lol("SG 553"), lol("sg556"), SkinSettings() },
	{ WEAPON_SCAR20,lol("SCAR-20"), lol("scar20"), SkinSettings() },
	{ WEAPON_G3SG1, lol("G3SG1"), lol("g3sg1"), SkinSettings() },
	{ WEAPON_AWP,	lol("AWP"), lol("awp"), SkinSettings() },
	{ WEAPON_SSG08, lol("SSG 08"), lol("ssg08"), SkinSettings() }
	};

	vector<ItemSettings> KnifeNames =
	{
	{ WEAPON_KNIFE, lol("Default"), lol("Default"), SkinSettings() },
	{ WEAPON_KNIFE_BAYONET, lol("Bayonet"), lol("bayonet"), SkinSettings() },
	{ WEAPON_KNIFE_CSS,	lol("Classic"), lol("knife_css"), SkinSettings() },
	{ WEAPON_KNIFE_FLIP,	lol("Flip"), lol("knife_flip"), SkinSettings() },
	{ WEAPON_KNIFE_GUT,		lol("Gut Knife"), lol("knife_gut"), SkinSettings() },
	{ WEAPON_KNIFE_KARAMBIT,lol("Karambit"), lol("knife_karambit"), SkinSettings() },
	{ WEAPON_KNIFE_M9_BAYONET,	  lol("M9 Bayonet"), lol("knife_m9_bayonet"), SkinSettings() },
	{ WEAPON_KNIFE_TACTICAL,	   lol("Huntsman"), lol("knife_tactical"), SkinSettings() },
	{ WEAPON_KNIFE_FALCHION,	  lol("Falchion"), lol("knife_falchion"), SkinSettings() },
	{ WEAPON_KNIFE_SURVIVAL_BOWIE,lol("Bowie"), lol("knife_survival_bowie"), SkinSettings() },
	{ WEAPON_KNIFE_BUTTERFLY, lol("Butterfly"), lol("knife_butterfly"), SkinSettings() },
	{ WEAPON_KNIFE_PUSH,	  lol("Shadow"), lol("knife_push"), SkinSettings() },
	{ WEAPON_KNIFE_CORD,	  lol("Paracord"), lol("knife_cord"), SkinSettings() },
	{ WEAPON_KNIFE_CANIS,	  lol("Survivak"), lol("knife_canis"), SkinSettings() },
	{ WEAPON_KNIFE_URSUS, lol("Ursus"), lol("knife_ursus"), SkinSettings() },
	{ WEAPON_KNIFE_GYPSY_JACKKNIFE,	  lol("Navaja"), lol("knife_gypsy_jackknife"), SkinSettings() },
	{ WEAPON_KNIFE_OUTDOOR,	  lol("Nomad"), lol("knife_outdoor"), SkinSettings() },
	{ WEAPON_KNIFE_STILETTO, lol("Stiletto"),lol("knife_stiletto"), SkinSettings() },
	{ WEAPON_KNIFE_WIDOWMAKER,	  lol("Talon"), lol("knife_widowmaker"), SkinSettings() },
	{ WEAPON_KNIFE_SKELETON,	  lol("Skeleton"), lol("knife_skeleton"), SkinSettings() }
	};

	vector<ItemSettings> KnifeNamesTT =
	{
	{ WEAPON_KNIFE_T, lol("Default"), lol("Default"), SkinSettings() },
	{ WEAPON_KNIFE_BAYONET, lol("Bayonet"), lol("bayonet"), SkinSettings() },
	{ WEAPON_KNIFE_CSS,	lol("Classic"), lol("knife_css"), SkinSettings() },
	{ WEAPON_KNIFE_FLIP,	lol("Flip"), lol("knife_flip"), SkinSettings() },
	{ WEAPON_KNIFE_GUT,		lol("Gut Knife"), lol("knife_gut"), SkinSettings() },
	{ WEAPON_KNIFE_KARAMBIT,lol("Karambit"), lol("knife_karambit"), SkinSettings() },
	{ WEAPON_KNIFE_M9_BAYONET,	  lol("M9 Bayonet"), lol("knife_m9_bayonet"), SkinSettings() },
	{ WEAPON_KNIFE_TACTICAL,	   lol("Huntsman"), lol("knife_tactical"), SkinSettings() },
	{ WEAPON_KNIFE_FALCHION,	  lol("Falchion"), lol("knife_falchion"), SkinSettings() },
	{ WEAPON_KNIFE_SURVIVAL_BOWIE,lol("Bowie"), lol("knife_survival_bowie"), SkinSettings() },
	{ WEAPON_KNIFE_BUTTERFLY, lol("Butterfly"), lol("knife_butterfly"), SkinSettings() },
	{ WEAPON_KNIFE_PUSH,	  lol("Shadow"), lol("knife_push"), SkinSettings() },
	{ WEAPON_KNIFE_CORD,	  lol("Paracord"), lol("knife_cord"), SkinSettings() },
	{ WEAPON_KNIFE_CANIS,	  lol("Survivak"), lol("knife_canis"), SkinSettings() },
	{ WEAPON_KNIFE_URSUS, lol("Ursus"), lol("knife_ursus"), SkinSettings() },
	{ WEAPON_KNIFE_GYPSY_JACKKNIFE,	  lol("Navaja"), lol("knife_gypsy_jackknife"), SkinSettings() },
	{ WEAPON_KNIFE_OUTDOOR,	  lol("Nomad"), lol("knife_outdoor"), SkinSettings() },
	{ WEAPON_KNIFE_STILETTO, lol("Stiletto"),lol("knife_stiletto"), SkinSettings() },
	{ WEAPON_KNIFE_WIDOWMAKER,	  lol("Talon"), lol("knife_widowmaker"), SkinSettings() },
	{ WEAPON_KNIFE_SKELETON,	  lol("Skeleton"), lol("knife_skeleton"), SkinSettings() }
	};

	//vector<ItemSettings> GloveNames =
	//{
	//{ GLOVE_CT_SIDE, lol("Default"), lol("Default"), SkinSettings() },
	//{ GLOVE_SPORTY, lol("Sporty"), lol("glove_sporty"), SkinSettings() },
	//{ GLOVE_SLICK, lol("Slick"), lol("glove_slick"), SkinSettings() },
	//{ GLOVE_LEATHER_WRAP, lol("Handwrap"), lol("glove_handwrap_leathery"), SkinSettings() },
	//{ GLOVE_MOTORCYCLE, lol("Motorcycle"), lol("glove_motorcycle"), SkinSettings() },
	//{ GLOVE_SPECIALIST, lol("Specialist"), lol("glove_specialist"), SkinSettings() },
	//{ GLOVE_HYDRA, lol("Hydra"), lol("glove_bloodhound"), SkinSettings() },
	//};

	struct GlovesSkins_s
	{
		int ItemIndex;
		int PaintKit;
		const char* szModel;
		string Url;
	};

	struct SortedKits_s
	{
		int kit = 0;
		string name = "-";
		string name_rus = "-";
		string cdn_name = "--";
	};

	struct SortedWeapons_s
	{
		string name;
		int ID;
		vector<SortedKits_s> kits;
	};

	struct SortedStickers_s
	{
		vector<paint_kit> Stickers;
		string sub_name = "";
	};

	const char* bloodhound = lol("models/weapons/w_models/arms/w_glove_bloodhound.mdl").c_str();
	const char* handwrap = lol("models/weapons/w_models/arms/w_glove_sporty.mdl").c_str();
	const char* slick = lol("models/weapons/w_models/arms/w_glove_slick.mdl").c_str();
	const char* sporty = lol("models/weapons/w_models/arms/w_glove_handwrap_leathery.mdl").c_str();
	const char* motorcycle = lol("models/weapons/w_models/arms/w_glove_motorcycle.mdl").c_str();
	const char* specialist = lol("models/weapons/w_models/arms/w_glove_specialist.mdl").c_str();
	const char* hydra = lol("models/weapons/w_models/arms/w_glove_bloodhound_hydra.mdl").c_str();

	const char* fbi_variantb = lol("models/player/custom_player/legacy/ctm_fbi_variantb.mdl").c_str(); //Agent Ava
	const char* fbi_variantf = lol("models/player/custom_player/legacy/ctm_fbi_variantf.mdl").c_str(); //Operator
	const char* fbi_variantg = lol("models/player/custom_player/legacy/ctm_fbi_variantg.mdl").c_str(); //Markus Delrow
	const char* fbi_varianth = lol("models/player/custom_player/legacy/ctm_fbi_varianth.mdl").c_str(); //Michael Syfers
	const char* sas_variantf = lol("models/player/custom_player/legacy/ctm_sas_variantf.mdl").c_str(); //Seal Team 6 Soldier
	const char* st6_variante = lol("models/player/custom_player/legacy/ctm_st6_variante.mdl").c_str(); //Buckshot
	const char* st6_variantg = lol("models/player/custom_player/legacy/ctm_st6_variantg.mdl").c_str(); //Ricksaw
	const char* st6_varianti = lol("models/player/custom_player/legacy/ctm_st6_varianti.mdl").c_str(); //3rd Commando Compan
	const char* st6_variantk = lol("models/player/custom_player/legacy/ctm_st6_variantk.mdl").c_str(); //McCoy
	const char* st6_variantm = lol("models/player/custom_player/legacy/ctm_st6_variantm.mdl").c_str(); //B Squadron Officer
	const char* balkan_variantf = lol("models/player/custom_player/legacy/tm_balkan_variantf.mdl").c_str(); //Mr Muhlik
	const char* balkan_variantg = lol("models/player/custom_player/legacy/tm_balkan_variantg.mdl").c_str(); //Prof. Shahmat
	const char* balkan_varianth = lol("models/player/custom_player/legacy/tm_balkan_varianth.mdl").c_str(); //Osiris
	const char* balkan_varianti = lol("models/player/custom_player/legacy/tm_balkan_varianti.mdl").c_str(); //Ground Rebel
	const char* balkan_variantj = lol("models/player/custom_player/legacy/tm_balkan_variantj.mdl").c_str(); //Dragomir
	const char* leet_variantf = lol("models/player/custom_player/legacy/tm_leet_variantf.mdl").c_str(); //Rezan The Ready
	const char* leet_variantg = lol("models/player/custom_player/legacy/tm_leet_variantg.mdl").c_str(); //Doctor Romanov
	const char* leet_varianth = lol("models/player/custom_player/legacy/tm_leet_varianth.mdl").c_str(); //Maximus
	const char* leet_varianti = lol("models/player/custom_player/legacy/tm_leet_varianti.mdl").c_str(); //Blackwolf
	const char* phoenix_variantf = lol("models/player/custom_player/legacy/tm_phoenix_variantf.mdl").c_str(); //Enforcer
	const char* phoenix_variantg = lol("models/player/custom_player/legacy/tm_phoenix_variantg.mdl").c_str(); //Slingshot
	const char* phoenix_varianth = lol("models/player/custom_player/legacy/tm_phoenix_varianth.mdl").c_str(); //Soldier Phoenix

	GlovesSkins_s GlovesSkin_Array[49] =
	{
	{ GLOVE_SPORTY,10018,sporty,lol("sporty_gloves_sporty_light_blue") },
	{ GLOVE_SPORTY,10037,sporty,lol("sporty_gloves_sporty_purple") },
	{ GLOVE_SPORTY,10038,sporty,lol("sporty_gloves_sporty_green") },
	{ GLOVE_SPORTY,10019,sporty,lol("sporty_gloves_sporty_military") },
	{ GLOVE_SPORTY,10048,sporty,lol("sporty_gloves_sporty_blue_pink") },
	{ GLOVE_SPORTY,10047,sporty,lol("sporty_gloves_sporty_black_webbing_yellow") },
	{ GLOVE_SPORTY,10046,sporty,lol("sporty_gloves_sporty_poison_frog_red_green") },
	{ GLOVE_SPORTY,10045,sporty,lol("sporty_gloves_sporty_poison_frog_blue_white") },
	{ GLOVE_MOTORCYCLE,10024,motorcycle,lol("motorcycle_gloves_motorcycle_basic_black") },
	{ GLOVE_MOTORCYCLE,10026,motorcycle,lol("motorcycle_gloves_motorcycle_mint_triangle") },
	{ GLOVE_MOTORCYCLE,10027,motorcycle,lol("motorcycle_gloves_motorcycle_mono_boom") },
	{ GLOVE_MOTORCYCLE,10028,motorcycle,lol("motorcycle_gloves_motorcycle_triangle_blue") },
	{ GLOVE_MOTORCYCLE,10052,motorcycle,lol("motorcycle_gloves_motorcycle_trigrid_blue") },
	{ GLOVE_MOTORCYCLE,10051,motorcycle,lol("motorcycle_gloves_motorcycle_yellow_camo") },
	{ GLOVE_MOTORCYCLE,10050,motorcycle,lol("motorcycle_gloves_motorcycle_basic_green_orange") },
	{ GLOVE_MOTORCYCLE,10049,motorcycle,lol("motorcycle_gloves_motorcycle_choco_boom") },
	{ GLOVE_SPECIALIST,10033,specialist,lol("specialist_gloves_specialist_kimono_diamonds_red") },
	{ GLOVE_SPECIALIST,10034,specialist,lol("specialist_gloves_specialist_emerald_web") },
	{ GLOVE_SPECIALIST,10035,specialist,lol("specialist_gloves_specialist_orange_white") },
	{ GLOVE_SPECIALIST,10030,specialist,lol("specialist_gloves_specialist_ddpat_green_camo") },
	{ GLOVE_SPECIALIST,10064,specialist,lol("specialist_gloves_specialist_winterhex") },
	{ GLOVE_SPECIALIST,10063,specialist,lol("specialist_gloves_specialist_fade") },
	{ GLOVE_SPECIALIST,10062,specialist,lol("specialist_gloves_specialist_forest_brown") },
	{ GLOVE_SPECIALIST,10061,specialist,lol("specialist_gloves_specialist_webs_red") },
	{ GLOVE_SLICK,10013,slick,lol("slick_gloves_slick_black") },
	{ GLOVE_SLICK,10015,slick,lol("slick_gloves_slick_military") },
	{ GLOVE_SLICK,10016,slick,lol("slick_gloves_slick_red") },
	{ GLOVE_SLICK,10040,slick,lol("slick_gloves_slick_snakeskin_yellow") },
	{ GLOVE_SLICK,10044,slick,lol("slick_gloves_slick_stitched_green_grey") },
	{ GLOVE_SLICK,10043,slick,lol("slick_gloves_slick_stitched_black_orange") },
	{ GLOVE_SLICK,10042,slick,lol("slick_gloves_slick_plaid_purple") },
	{ GLOVE_SLICK,10041,slick,lol("slick_gloves_slick_snakeskin_white") },
	{ GLOVE_LEATHER_WRAP,10009,handwrap,lol("leather_handwraps_handwrap_leathery") },
	{ GLOVE_LEATHER_WRAP,10010,handwrap,lol("leather_handwraps_handwrap_camo_grey") },
	{ GLOVE_LEATHER_WRAP,10036,handwrap,lol("leather_handwraps_handwrap_fabric_orange_camo") },
	{ GLOVE_LEATHER_WRAP,10021,handwrap,lol("leather_handwraps_handwrap_red_slaughter") },
	{ GLOVE_LEATHER_WRAP,10056,handwrap,lol("leather_handwraps_handwrap_leathery_fabric_green_camo") },
	{ GLOVE_LEATHER_WRAP,10055,handwrap,lol("leather_handwraps_handwrap_leathery_ducttape") },
	{ GLOVE_LEATHER_WRAP,10054,handwrap,lol("leather_handwraps_handwrap_leathery_fabric_geometric_blue") },
	{ GLOVE_LEATHER_WRAP,10053,handwrap,lol("leather_handwraps_handwrap_leathery_fabric_blue_skulls") },
	{ GLOVE_STUDDED_BLOODHOUND,10006,bloodhound,lol("studded_bloodhound_gloves_bloodhound_black_silver") },
	{ GLOVE_STUDDED_BLOODHOUND,10007,bloodhound,lol("studded_bloodhound_gloves_bloodhound_snakeskin_brass") },
	{ GLOVE_STUDDED_BLOODHOUND,10008,bloodhound,lol("studded_bloodhound_gloves_bloodhound_metallic") },
	{ GLOVE_STUDDED_BLOODHOUND,10039,bloodhound,lol("studded_bloodhound_gloves_bloodhound_guerrilla") },
	{ GLOVE_HYDRA,10060,hydra,lol("studded_hydra_gloves_bloodhound_hydra_green_leather_mesh_brass") },
	{ GLOVE_HYDRA,10059,hydra,lol("studded_hydra_gloves_bloodhound_hydra_snakeskin_brass") },
	{ GLOVE_HYDRA,10058,hydra,lol("studded_hydra_gloves_bloodhound_hydra_green_leather_mesh_brass") },
	{ GLOVE_HYDRA,10057,hydra,lol("studded_hydra_gloves_bloodhound_hydra_black_green") },
	};


	virtual void SetSkin(CBaseAttributableItem* pWeapon, SkinSettings *SkinParam, int id, bool IsCT, bool IsKnife) = 0;

	virtual void ItemsList(const vector<ItemSettings> &Items, int &var, const Vec2 Size, const string Name) = 0;
	virtual void SkinsList(const vector<paint_kit> &Skins, int &var, const Vec2 Size, const string Name, const string Find = "") = 0;
	virtual void SortSkinsList(const vector<SortedKits_s> &Skins, int &var, const Vec2 Size, const string Name, const string Find = "") = 0;

	virtual void SaveSkins(nlohmann::json &j) = 0;
	virtual void LoadSkins(nlohmann::json &j) = 0;
	virtual int GetKnifeModelIdx(int ci, bool IsTT) = 0;
};

class CSkins : public ISkins
{
private:
	bool IsNameChange = false;
public:
	CConfig Config = CConfig(__xor("Skins"));

	vector<paint_kit> skin_kits;
	vector<paint_kit> glove_kits;
	vector<paint_kit> sticker_kits;

	unordered_map<int, const char*> g_ViewModelCfg;
	unordered_map<const char*, const char*> g_KillIconCfg;

	virtual void Menu();
	//virtual void Preview();
	auto initialize_kits() -> void;

	virtual void PostDataUpdate(ClientFrameStage_t Stage);
	virtual void RecvProxy_Viewmodel(CRecvProxyData *pData, void *pStruct, void *pOut);

	virtual void ApplyCustomSkin(CBaseAttributableItem* pWeapon, int nWeaponIndex, bool IsTT);
	virtual void ApplyCustomModel(CBaseEntity* pLocal, CBaseAttributableItem* pWeapon);
	virtual bool IsKnife(int idx);
	virtual bool GetWeaponByDefIdx(int Idx, int& ListIdx, bool IsKnife, bool IsTT);

	virtual void ApplyStickerHooks(CBaseAttributableItem* pItem);
	virtual int  StickWeaponByDefIndex(int DefIdx);

	CSkinListener FireEvent;

	virtual void ParseSortedKits();
	virtual void PrepareSortedSkins();

	virtual void UpdateSkins(bool reset = true);

	virtual void SetKillIconCfg();

	int SelectedWeapon = 0;

	int SelectedKnifeModelCT = 0;
	int SelectedKnifeModelTT = 0;

	bool UpdateGlove = false;

	int SelectedGloveCT = 0;
	int SelectedGloveTT = 0;

	char GloveCTName[32] = "";
	char GloveTTName[32] = "";

	float GloveCTWear = 0.001f;
	float GloveTTWear = 0.001f;

	int SelectedAgentCT = 0;
	int SelectedAgentTT = 0;

	bool ShowSkinPreview = false;

	string WeaponPreview = __xor("<default>");
	string SkinPreview = __xor("<default>");

	bool SkinsEnable = false;

	vector<SortedWeapons_s> SortedWeapons;
	vector<SortedWeapons_s> SortedKnives;
	vector<SortedStickers_s> SortedStickers;

	virtual void SetSkin(CBaseAttributableItem* pWeapon, SkinSettings *SkinParam, int id, bool IsCT, bool IsKnife);

	virtual void SaveSkins(nlohmann::json &j);
	virtual void LoadSkins(nlohmann::json &j);
	virtual int  GetKnifeModelIdx(int ci, bool IsTT);
	virtual void ItemsList(const vector<ItemSettings> &Items, int &var, const Vec2 Size, const string Name);
	virtual void SkinsList(const vector<paint_kit> &Skins, int &var, const Vec2 Size, const string Name, const string Find = "");
	virtual void SortSkinsList(const vector<SortedKits_s> &Skins, int &var, const Vec2 Size, const string Name, const string Find = "");

	bool AllSkinsLoaded = false;

	CSkins()
	{
		RV(SelectedWeapon, "SelectedWeapon");
		RV(SelectedKnifeModelCT, "SelectedKnifeModelCT");
		RV(SelectedKnifeModelTT, "SelectedKnifeModelTT");
		RV(SelectedGloveCT, "SelectedGloveCT");
		RV(SelectedGloveTT, "SelectedGloveTT");
		RV(GloveCTWear, "GloveCTWear");
		RV(GloveTTWear, "GloveTTWear");
		RV(SkinsEnable, "SkinsEnable");
		debug_log("Setup: CSkins sucessful\n");
	}
};

namespace detail
{
	template <typename Type, Type OffsetBasis, Type Prime>
	struct size_dependant_data
	{
		using type = Type;
		constexpr static auto k_offset_basis = OffsetBasis;
		constexpr static auto k_prime = Prime;
	};

	template <size_t Bits>
	struct size_selector;

	template <>
	struct size_selector<32>
	{
		using type = size_dependant_data<std::uint32_t, 0x811c9dc5ul, 16777619ul>;
	};

	template <>
	struct size_selector<64>
	{
		using type = size_dependant_data<std::uint64_t, 0xcbf29ce484222325ull, 1099511628211ull>;
	};

	// Implements FNV-1a hash algorithm
	template <std::size_t Size>
	class fnv_hash
	{
	private:
		using data_t = typename size_selector<Size>::type;

	public:
		using hash = typename data_t::type;

	private:
		constexpr static auto k_offset_basis = data_t::k_offset_basis;
		constexpr static auto k_prime = data_t::k_prime;

	public:
		template <std::size_t N>
		static __forceinline constexpr auto hash_constexpr(const char(&str)[N], const std::size_t size = N) -> hash
		{
			return static_cast<hash>(1ull * (size == 1
				? (k_offset_basis ^ str[0])
				: (hash_constexpr(str, size - 1) ^ str[size - 1])) * k_prime);
		}

		static auto __forceinline hash_runtime(const char* str) -> hash
		{
			auto result = k_offset_basis;
			do
			{
				result ^= *str++;
				result *= k_prime;
			} while (*(str - 1) != '\0');

			return result;
		}
	};
}

using fnv = ::detail::fnv_hash<sizeof(void*) * 8>;

#define FNV(str) (std::integral_constant<fnv::hash, fnv::hash_constexpr(str)>::value)
