#pragma once

#include "../../protobuf/base_gcmessages.pb.h"
#include "../../protobuf/cstrike15_gcmessages.pb.h"
#include "../../protobuf/econ_gcmessages.pb.h"
#include "../../protobuf/engine_gcmessages.pb.h"
#include "../../protobuf/gcsystemmsgs.pb.h"
#include "../../protobuf/gcsdk_gcmessages.pb.h"
#include "../../protobuf/netmessages.pb.h"
#include "../../protobuf/steammessages.pb.h"

#pragma comment(lib, "libprotoc.lib")

#include "../../Main.h"
#include"../Skins/Skins.h"

class IInventory : protected CSkins
{
protected:
	virtual void PostRetrieveMessage(uint32_t* punMsgType, void* pubDest, uint32_t cubDest, uint32_t* pcubMsgSize) = 0;
	virtual void PostRetrieveMessageProfile(uint32_t* punMsgType, void* pubDest, uint32_t cubDest, uint32_t* pcubMsgSize) = 0;

	virtual void Menu() = 0;
	virtual void InvListMenu() = 0;

	virtual int  GetInventoryByGame(int IndGame, int Eqp, TeamID Team) = 0;
	virtual void RetrieveMessage(void* ecx, void* edx, uint32_t* punMsgType, void* pubDest, uint32_t cubDest, uint32_t* pcubMsgSize) = 0;
	virtual void PreSendMessage(uint32_t& unMsgType, void* pubData, uint32_t& cubData) = 0;
	virtual void SSendMessage(void* ecx, void* edx, uint32_t unMsgType, const void* pubData, uint32_t cubData) = 0;

	virtual void AddMedals(CMsgSOCacheSubscribed::SubscribedType* pInventoryCacheObject, int Index, int MedalId) = 0;
	virtual void AddItem(CMsgSOCacheSubscribed::SubscribedType* Object, int index, int itemDefIndex, int rarity, int quality, int paintKit, int seed, float wear, const char* name, int InventoryLIdx) = 0;

	virtual void SendClientHello() = 0;
	virtual void SendMMHello() = 0;

	struct MedalsInfo
	{
		int Id;
		string Name;
	};

	virtual void InitalizeMedals() = 0;

	enum _ItemType
	{
		IT_NONE,
		IT_WEAPON,
		IT_KNIFE,
		IT_GLOVE,
		IT_MEDAL,
		IT_MUSIC,
		IT_CUSTOM
	};
public:
	struct Inventory
	{
		_ItemType ItemType = IT_NONE;

		int Index = 0;
		int Weapon = 0;
		int WeaponSkinId = 0;
		int Rarity = 0;
		int Quality = 0;
		int Style = 0;
		int iTeam = CYRT_AUTO;
		StickerSettings Stickers[5];
		int StickerId = 0;
		float StickerWear = 0;
		float StickerScale = 0;
		float StickerRotation = 0;

		TeamID Team = TEAM_UNASSIGNED;

		int GetEquippedState = 0;

		float Wear = 0.001f;
		float Seed = 0.001f;
		bool AutoStatTrack = false;
		int StatTrack = 0;
		char Name[32] = "";

		string WeaponName = "";
		string SkinName = "";

		static int LastIndex;
	};

	virtual void SaveInventory(nlohmann::json& j) = 0;
	virtual void LoadInventory(nlohmann::json& j) = 0;
	virtual void SetWeapon(Inventory* Inv, bool IsCT) = 0;
	virtual void SetKnife(Inventory* Inv, bool IsCT) = 0;
	virtual void SetGlove(Inventory* Inv, bool IsCT) = 0;
};

class CInventory : public IInventory
{
public:
	CConfig Config = CConfig(__xor("Inventory"));

	bool SkinsSyncEnable = true;
	void PostRetrieveMessage(uint32_t* punMsgType, void* pubDest, uint32_t cubDest, uint32_t* pcubMsgSize);
	void PostRetrieveMessageProfile(uint32_t* punMsgType, void* pubDest, uint32_t cubDest, uint32_t* pcubMsgSize);
	void RetrieveMessage(void* ecx, void* edx, uint32_t* punMsgType, void* pubDest, uint32_t cubDest, uint32_t* pcubMsgSize);
	void PreSendMessage(uint32_t& unMsgType, void* pubData, uint32_t& cubData);
	void SSendMessage(void* ecx, void* edx, uint32_t unMsgType, const void* pubData, uint32_t cubData);

	void Menu();
	void InvListMenu();

	int GetInventoryByGame(int IndGame, int Eqp, TeamID Team);

	void AddMedals(CMsgSOCacheSubscribed::SubscribedType* pInventoryCacheObject, int Index, int MedalId);
	void AddItem(CMsgSOCacheSubscribed::SubscribedType* Object, int index, int itemDefIndex, int rarity, int quality, int paintKit, int seed, float wear, const char* name, int InventoryLIdx);

	void SendClientHello();
	void SendMMHello();

	int InvSelectedWeapon = 0;
	int InvSelectedKnife = 0;
	int InvSelectedGlove = 0;
	float InvGloveWear = 0.001f;
	char InvGloveName[32] = "";

	bool ShowInventoryList = true;

	vector<ItemSettings> InvWeaponNames = WeaponNames;

	vector<MedalsInfo> Medals;
	void InitalizeMedals();

	void SaveInventory(nlohmann::json& j);
	void LoadInventory(nlohmann::json& j);
	void SetWeapon(Inventory* Inv, bool IsCT);
	void SetKnife(Inventory* Inv, bool IsCT);
	void SetGlove(Inventory* Inv, bool IsCT);

	int ProfileRank = 0;
	int ProfileLevel = 0;
	int ProfileXP = 0;
	int ProfileWins = 0;
	int ProfileFriendly = 0;
	int ProfileLeader = 0;
	int ProfileTeacher = 0;

	CInventory()
	{
		RV(ProfileRank, "ProfileRank");
		RV(ProfileLevel, "ProfileLevel");
		RV(ProfileXP, "ProfileXP");
		RV(ProfileWins, "ProfileWins");
		RV(ProfileFriendly, "ProfileFriendly");
		RV(ProfileLeader, "ProfileLeader");
		RV(ProfileTeacher, "ProfileTeacher");
		RV(SkinsSyncEnable, "SkinsSyncEnable");

		debug_log("Setup: CInventory sucessful\n");
	}
};

extern vector<IInventory::Inventory> InventoryList;