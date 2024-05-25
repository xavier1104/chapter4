#pragma once

enum eState
{
	eS_None = 0,
	eS_Normal,
	eS_KnowledgeKing,
	eS_Record,
	eS_DefaultConversation,
	eS_Interacting,
	eS_Recording,
	eS_Waiting,
	eS_Questioning,
	eS_ThanksForJoining

};

enum eCommand
{
	eC_King = 0,
	eC_KingStop,
	eC_PlayAgain,
	eC_Record,
	eC_StopRecording
};