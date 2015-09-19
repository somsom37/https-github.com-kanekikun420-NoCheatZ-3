#include <stdio.h>
#include "engine/iserverplugin.h"
#include "tier1/tier1.h"
#include "Misc/temp_Singleton.h"

#ifndef CNOCHEATZ_PLUGIN
#define CNOCHEATZ_PLUGIN

class CNoCheatZPlugin: public IServerPluginCallbacks, public Singleton<CNoCheatZPlugin>
{
public:
	// IServerPluginCallbacks methods
	virtual bool			Load(CreateInterfaceFn interfaceFactory, CreateInterfaceFn gameServerFactory );
	virtual void			Unload( void );
	virtual void			Pause( void );
	virtual void			UnPause( void );
	virtual const char     *GetPluginDescription( void );      
	virtual void			LevelInit( char const *pMapName );
	virtual void			ServerActivate( edict_t *pEdictList, int edictCount, int clientMax );
	virtual void			GameFrame( bool simulating );
	virtual void			LevelShutdown( void );
	virtual void			ClientActive( edict_t *pEntity );
#ifdef NCZ_CSGO
	virtual void            ClientFullyConnect(edict_t *) {};
#endif
	virtual void			ClientDisconnect( edict_t *pEntity );
	virtual void			ClientPutInServer( edict_t *pEntity, char const *playername );
	virtual void			SetCommandClient( int index );
	virtual void			ClientSettingsChanged( edict_t *pEdict );
	virtual PLUGIN_RESULT	ClientConnect( bool *bAllowConnect, edict_t *pEntity, const char *pszName, const char *pszAddress, char *reject, int maxrejectlen );
#ifndef NCZ_EP1
	virtual PLUGIN_RESULT	ClientCommand( edict_t *pEntity, const CCommand &args );
#else
	virtual PLUGIN_RESULT	ClientCommand( edict_t *pEntity );
#endif
	virtual PLUGIN_RESULT	NetworkIDValidated( const char *pszUserName, const char *pszNetworkID );
	virtual void			OnQueryCvarValueFinished( QueryCvarCookie_t iCookie, edict_t *pPlayerEntity, EQueryCvarValueStatus eStatus, const char *pCvarName, const char *pCvarValue );

	// added with version 3 of the interface.
	virtual void			OnEdictAllocated( edict_t *edict );
	virtual void			OnEdictFreed( const edict_t *edict  );

	virtual int GetCommandIndex() { return m_iClientCommandIndex; }

	CNoCheatZPlugin();
	~CNoCheatZPlugin();

private:
	CNoCheatZPlugin(const CNoCheatZPlugin & toCopy);
	CNoCheatZPlugin & operator =(const CNoCheatZPlugin & toCopy);
	int m_iClientCommandIndex;
	bool m_bAlreadyLoaded;
};

#endif
