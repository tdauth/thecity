//*******************************************************************
//Death Match
//Nicht dynamisch. Alle DeathMatches werden am Anfang definiert (Skins auch).
//*******************************************************************
#if defined DeathMatch_included
  	#endinput
#endif
#define DeathMatch_included
#pragma library DeathMatch

//-- Variables --
new DEATH_MATCHES = 0;

//-- Properties --
new DEATH_MATCH_NAME[MAX_DEATH_MATCHES][MAX_DEATH_MATCH_NAME];
new Float:DEATH_MATCH_CHECKPOINT[MAX_DEATH_MATCHES][4];
new Float:DEATH_MATCH_VIEW_POSITION[MAX_DEATH_MATCHES][3];
new Float:DEATH_MATCH_VIEW_TARGET[MAX_DEATH_MATCHES][4];
new DEATH_MATCH_INTERIOR[MAX_DEATH_MATCHES];
new DEATH_MATCH_SKINS[MAX_DEATH_MATCHES];
new DEATH_MATCH_SKIN[MAX_DEATH_MATCHES][MAX_DEATH_MATCH_SKINS];
new DEATH_MATCH_SKIN_NAME[MAX_DEATH_MATCHES][MAX_DEATH_MATCH_SKINS][MAX_DEATH_MATCH_SKIN_NAME];
new DEATH_MATCH_SKIN_COLOUR[MAX_DEATH_MATCHES][MAX_DEATH_MATCH_SKINS];
new DEATH_MATCH_SKIN_WEAPON[MAX_DEATH_MATCHES][MAX_DEATH_MATCH_SKINS][6];
new Float:DEATH_MATCH_SKIN_POSITION[MAX_DEATH_MATCHES][MAX_DEATH_MATCH_SKINS][4];
