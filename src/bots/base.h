#ifndef TWBL_SRC_BOTS_BASE_H
#define TWBL_SRC_BOTS_BASE_H

#include <cstddef>

#include <shared/character.h>
#include <shared/player.h>
#include <shared/types.h>
#include <shared/vmath.h>

#if defined(__GNUC__) && __GNUC__ >= 4
#define TWBL_HOT __attribute__((visibility("hidden")))
#elif defined(__SUNPRO_C) && (__SUNPRO_C >= 0x590)
#define TWBL_HOT __attribute__((visibility("hidden")))
#else
#define TWBL_HOT
#endif

namespace TWBL {

// 0 is newest
// MaxEntries-1 is oldest
void PushRingStr(const char **ppBuffer, const char *pNew, size_t MaxEntries);

// 0 is newest
// MaxEntries-1 is oldest
void PushRingInt(int *pBuffer, int New, size_t MaxEntries);

class CBaseBot
{
public:
	const CServerBotStateIn *m_pStateIn;
	CServerBotStateOut *m_pStateOut;

	CBaseBot(const CServerBotStateIn *pStateIn, CServerBotStateOut *pStateOut)
	{
		m_pStateIn = pStateIn;
		m_pStateOut = pStateOut;
	}

	const CCollision *Collision() const { return m_pStateIn->m_pCollision; }
	CCharacter *Character(int ClientId = -1);
	CPlayer *GetPlayer(int ClientId = -1);
	CCharacter *ClosestCharacter(vec2 Pos, const CCharacter *pNotThis);

	vec2 GetPos() { return Character()->GetPos(); }
	vec2 GetVel() { return Character()->Core()->m_Vel; }
	bool IsGrounded() { return Character()->IsGrounded(); }
	int FreezeTime() { return Character()->m_FreezeTime; }
	bool IsFrozen(CCharacter *pChr = nullptr);

	// it is recommended to use the macros instead

	void _DieRaw() const;
	void _Die(const char *pComment) const;

	void _AimRaw(int TargetX, int TargetY) const;
	void _Aim(int TargetX, int TargetY, const char *pComment, const char *pFunction, const char *pFile, int Line) const;

	void _SetDirectionRaw(int Dir) const;
	void _SetDirection(int Dir, const char *pComment, const char *pFunction, const char *pFile, int Line) const;

	void _HookRaw(int Value) const;
	void _Hook(int Value, const char *pComment, const char *pFunction, const char *pFile, int Line) const;

	void _JumpRaw(int Value) const;
	void _Jump(int Value, const char *pComment, const char *pFunction, const char *pFile, int Line) const;

	void _FireRaw(int Value) const;
	void _Fire(int Value, const char *pComment, const char *pFunction, const char *pFile, int Line) const;

	void _SetWeaponRaw(int Value) const;
	void _SetWeapon(int Value, const char *pComment, const char *pFunction, const char *pFile, int Line) const;

	void Tick(){};
};

} // namespace TWBL

extern "C" {

const char *TwblInfo();
const char *TwblTicks();
}

#endif
