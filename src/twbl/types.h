#ifndef TWBL_SRC_SHARED_TYPES_H
#define TWBL_SRC_SHARED_TYPES_H

#include <cstdio>
#include <cstring>
#include <twbl/teeworlds/base/system.h>
#include <twbl/tracer.h>

#include <twbl/callback_ctx.h>
#include <twbl/teeworlds/character.h>
#include <twbl/teeworlds/collision.h>
#include <twbl/teeworlds/player.h>

#define TWBL_MAX_LOG_LEN 16

#ifndef MAX_CLIENTS
#define MAX_CLIENTS 64
#endif

typedef void (*FCallbackDie)(CCharacter *pChr);
typedef void (*FStrTraceCallback)(const char *pStr, int Offset, void *pContext);

class CServerBotStateIn
{
public:
	int m_ClientId;
	int m_GameTick = 0;
	const CCollision *m_pCollision = nullptr;
	CCharacter *m_pCharacter = nullptr;
	CPlayer **m_ppPlayers = nullptr;

	// deprecated die callback
	// replaced by callback context
	FCallbackDie m_pfnCallbackDie = nullptr;

	TWBL::CCallbackCtx *m_pCallbackCtx = nullptr;
};

class CServerBotStateOut
{
public:
	int m_Direction = 0;
	int m_TargetX = 0;
	int m_TargetY = -1;
	int m_Jump = 0;
	int m_Fire = 0;
	int m_Hook = 0;
	int m_PlayerFlags = 0;
	int m_Weapon = 0;

	// debug
	const char *m_pDieComment;

	const char *m_apAimComments[TWBL_MAX_LOG_LEN];
	const char *m_apAimFunctions[TWBL_MAX_LOG_LEN];
	const char *m_apAimFiles[TWBL_MAX_LOG_LEN];
	int m_aAimLines[TWBL_MAX_LOG_LEN];

	const char *m_apDirComments[TWBL_MAX_LOG_LEN];
	const char *m_apDirFunctions[TWBL_MAX_LOG_LEN];
	const char *m_apDirFiles[TWBL_MAX_LOG_LEN];
	int m_aDirLines[TWBL_MAX_LOG_LEN];

	const char *m_apHookComments[TWBL_MAX_LOG_LEN];
	const char *m_apHookFunctions[TWBL_MAX_LOG_LEN];
	const char *m_apHookFiles[TWBL_MAX_LOG_LEN];
	int m_aHookLines[TWBL_MAX_LOG_LEN];

	const char *m_apJumpComments[TWBL_MAX_LOG_LEN];
	const char *m_apJumpFunctions[TWBL_MAX_LOG_LEN];
	const char *m_apJumpFiles[TWBL_MAX_LOG_LEN];
	int m_aJumpLines[TWBL_MAX_LOG_LEN];

	const char *m_apFireComments[TWBL_MAX_LOG_LEN];
	const char *m_apFireFunctions[TWBL_MAX_LOG_LEN];
	const char *m_apFireFiles[TWBL_MAX_LOG_LEN];
	int m_aFireLines[TWBL_MAX_LOG_LEN];

	const char *m_apSetWeaponComments[TWBL_MAX_LOG_LEN];
	const char *m_apSetWeaponFunctions[TWBL_MAX_LOG_LEN];
	const char *m_apSetWeaponFiles[TWBL_MAX_LOG_LEN];
	int m_aSetWeaponLines[TWBL_MAX_LOG_LEN];

	const char *m_apEmoteComments[TWBL_MAX_LOG_LEN];
	const char *m_apEmoteFunctions[TWBL_MAX_LOG_LEN];
	const char *m_apEmoteFiles[TWBL_MAX_LOG_LEN];
	int m_aEmoteLines[TWBL_MAX_LOG_LEN];

	CServerBotStateOut()
	{
#ifdef TWBL_DEBUG
		m_pDieComment = "";
		for(int i = 0; i < TWBL_MAX_LOG_LEN; i++)
		{
			m_apAimComments[i] = "";
			m_apAimFunctions[i] = "";
			m_apAimFiles[i] = "";
			m_aAimLines[i] = 0;

			m_apDirComments[i] = "";
			m_apDirFunctions[i] = "";
			m_apDirFiles[i] = "";
			m_aDirLines[i] = 0;

			m_apHookComments[i] = "";
			m_apHookFunctions[i] = "";
			m_apHookFiles[i] = "";
			m_aHookLines[i] = 0;

			m_apJumpComments[i] = "";
			m_apJumpFunctions[i] = "";
			m_apJumpFiles[i] = "";
			m_aJumpLines[i] = 0;

			m_apFireComments[i] = "";
			m_apFireFunctions[i] = "";
			m_apFireFiles[i] = "";
			m_aFireLines[i] = 0;

			m_apSetWeaponComments[i] = "";
			m_apSetWeaponFunctions[i] = "";
			m_apSetWeaponFiles[i] = "";
			m_aSetWeaponLines[i] = 0;

			m_apEmoteComments[i] = "";
			m_apEmoteFunctions[i] = "";
			m_apEmoteFiles[i] = "";
			m_aEmoteLines[i] = 0;
		}
#endif
	}

	bool TraceDirStrOffset(char *pBuf, int BufSize, int Offset) const
	{
		pBuf[0] = '\0';
#ifdef TWBL_DEBUG
		char aLine[512];
		if(m_apDirFiles[Offset][0] == '\0')
			return false;

		str_format(
			aLine,
			sizeof(aLine),
			"%s:%d %s() '%s'",
			m_apDirFiles[Offset],
			m_aDirLines[Offset],
			m_apDirFunctions[Offset],
			m_apDirComments[Offset]);
		str_append(pBuf, aLine, BufSize);
		return true;
#else
		str_copy(pBuf, "to use tracing compile with -DTWBL_DEBUG=ON", BufSize);
		return false;
#endif
	}

	void TraceDirStrFull(char *pBuf, int BufSize, int MaxHist = TWBL_MAX_LOG_LEN) const
	{
		pBuf[0] = '\0';
#ifdef TWBL_DEBUG
		char aLine[512];
		str_format(aLine, sizeof(aLine), "Dir=%d", m_Direction);
		str_append(pBuf, aLine, BufSize);

		for(int i = 0; i < TWBL_MAX_LOG_LEN; i++)
		{
			if(i > MaxHist)
				break;
			if(!TraceDirStrOffset(aLine, sizeof(aLine), i))
				break;

			str_append(pBuf, ", ", BufSize);
			str_append(pBuf, aLine, BufSize);
		}
#else
		str_copy(pBuf, "to use tracing compile with -DTWBL_DEBUG=ON", BufSize);
#endif
	}

	void TraceDir(FStrTraceCallback pCallback = twbl_default_log_tracer, void *pContext = nullptr, int MaxHist = TWBL_MAX_LOG_LEN) const
	{
#ifdef TWBL_DEBUG
		char aLine[512];
		char aBuf[512];
		str_format(aLine, sizeof(aLine), "Dir=%d", m_Direction);
		pCallback(aLine, 0, pContext);

		for(int i = 0; i < TWBL_MAX_LOG_LEN; i++)
		{
			if(i > MaxHist)
				break;
			if(!TraceDirStrOffset(aLine, sizeof(aLine), i))
				break;

			str_format(aBuf, sizeof(aBuf), "  %s", aLine);
			pCallback(aBuf, i + 1, pContext);
		}
#else
		pCallback("to use tracing compile with -DTWBL_DEBUG=ON", 0, pContext);
#endif
	}

	void DumpStr(char *pBuf, int BufSize) const
	{
		pBuf[0] = '\0';
		char aLine[512];

		snprintf(aLine, sizeof(aLine), "m_Direction=%d\n", m_Direction);
		strncat(pBuf, aLine, BufSize - 1);

		snprintf(aLine, sizeof(aLine), "m_TargetX=%d\n", m_TargetX);
		strncat(pBuf, aLine, BufSize - 1);
	}

	void DumpStdout() const
	{
		char aBuf[1024];
		DumpStr(aBuf, sizeof(aBuf));
		printf("%s\n", aBuf);
	}
};

#endif
