// GameHelper.h: interface for the CGameHelper class.
//
//////////////////////////////////////////////////////////////////////

#ifndef __GAME_HELPER_H__
#define __GAME_HELPER_H__

#include <list>
#include <map>
#include "Object.h"
class CGame;
class CUnit;
class CWeapon;
class CSolidObject;
class CFeature;

struct UnitDef;
#include <vector>
#include "Sim/Misc/DamageArray.h"
#include <list>
#include "MemPool.h"

using namespace std;

class CExplosionGraphics;

class CGameHelper  
{
public:
	CGameHelper(CGame* game);
	virtual ~CGameHelper();
	bool TestCone(const float3& from,const float3& dir,float length,float spread,int allyteam,CUnit* owner);
	bool TestTrajectoryCone(const float3 &from, const float3 &flatdir,float length, float linear, float quadratic, float spread, float baseSize, int allyteam,CUnit* owner);
	void GetEnemyUnits(float3& pos,float radius,int searchAllyteam,vector<int>& found);
	CUnit* GetClosestUnit(const float3& pos,float radius);
	CUnit* GetClosestEnemyUnit(const float3& pos,float radius,int searchAllyteam);
	CUnit* GetClosestEnemyUnitNoLosTest(const float3& pos,float radius,int searchAllyteam);
	CUnit* GetClosestFriendlyUnit(const float3& pos,float radius,int searchAllyteam);
	CUnit* GetClosestEnemyAircraft(const float3& pos,float radius,int searchAllyteam);
	void GenerateTargets(CWeapon *attacker, CUnit* lastTarget,std::map<float,CUnit*> &targets);
	float TraceRay(const float3& start,const float3& dir,float length,float power,CUnit* owner, CUnit*& hit);
	float GuiTraceRay(const float3& start,const float3& dir,float length, CUnit*& hit,float sizeMod,bool useRadar,CUnit* exclude=0);
	float GuiTraceRayFeature(const float3& start, const float3& dir, float length,CFeature*& feature);
	void Explosion(float3 pos,const DamageArray& damages,float radius,CUnit* owner,bool damageGround=true,float gfxMod=1,bool ignoreOwner=false,int graphicType=0);
	float TraceRayTeam(const float3& start,const float3& dir,float length, CUnit*& hit,bool useRadar,CUnit* exclude,int allyteam);
	void BuggerOff(float3 pos, float radius,CUnit* exclude=0);
	float3 Pos2BuildPos(float3 pos, const UnitDef* ud);
	void Update(void);

	CGame* game;
	bool LineFeatureCol(const float3& start, const float3& dir,float length);
	float3 GetUnitErrorPos(CUnit* unit, int allyteam);	//get the position of a unit + eventuall error due to lack of los

	std::vector<CExplosionGraphics*> explosionGraphics;

	struct WaitingDamage{
#ifndef SYNCIFY
		inline void* operator new(size_t size){return mempool.Alloc(size);};
		inline void operator delete(void* p,size_t size){mempool.Free(p,size);};
#endif
		WaitingDamage(int attacker,int target,const DamageArray& damage,const float3& impulse)
			:	attacker(attacker),
				target(target),
				damage(damage),
				impulse(impulse)
		{}

		int target;
		int attacker;
		DamageArray damage;
		float3 impulse;
	};

	std::list<WaitingDamage*> waitingDamages[128];		//probably a symptom of some other problems but im getting paranoid about putting whole classes into high trafic stl containers instead of pointers to them
};

extern CGameHelper* helper;

#endif // __GAME_HELPER_H__
