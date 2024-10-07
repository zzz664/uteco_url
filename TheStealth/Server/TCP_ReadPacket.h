#pragma once
#include "TCP_Structure.h"

inline VOID READ_PT_CHANNEL_NICKNAME(BYTE *buffer, S_PT_CHANNEL_NICKNAME &parameter)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

	Stream->ReadWCHARs(parameter.USER_ID, 32);
}

inline VOID READ_PT_CHANNEL_NICKNAME_SUCC_U(BYTE *buffer, S_PT_CHANNEL_NICKNAME_SUCC_U &parameter)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

	Stream->ReadWCHARs(parameter.USER_ID, 32);
	Stream->ReadWCHARs(parameter.NICK_NAME, 32);
}

inline VOID READ_PT_CHANNEL_NICKNAME_FAIL_U(BYTE *buffer, S_PT_CHANNEL_NICKNAME_FAIL_U &parameter)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

	Stream->ReadDWORD(&parameter.ERROR_CODE);
}

inline VOID READ_PT_QUERY_NICKNAME(BYTE *buffer, S_PT_QUERY_NICKNAME &parameter)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

	Stream->ReadWCHARs(parameter.NICK_NAME, 32);
}

inline VOID READ_PT_QUERY_NICKNAME_SUCC_U(BYTE *buffer, S_PT_QUERY_NICKNAME_SUCC_U &parameter)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

}

inline VOID READ_PT_QUERY_NICKNAME_FAIL_U(BYTE *buffer, S_PT_QUERY_NICKNAME_FAIL_U &parameter)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

}

inline VOID READ_PT_INSERT_NICKNAME(BYTE *buffer, S_PT_INSERT_NICKNAME &parameter)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

	Stream->ReadWCHARs(parameter.USER_ID, 32);
	Stream->ReadWCHARs(parameter.NICKNAME, 32);
}

inline VOID READ_PT_INSERT_NICKNAME_SUCC_U(BYTE *buffer, S_PT_INSERT_NICKNAME_SUCC_U &parameter)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

}

inline VOID READ_PT_INSERT_NICKNAME_FAIL_U(BYTE *buffer, S_PT_INSERT_NICKNAME_FAIL_U &parameter)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

}

inline VOID READ_PT_CHANNEL_CHATTING(BYTE *buffer, S_PT_CHANNEL_CHATTING &parameter)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

	Stream->ReadWCHARs(parameter.CHAT, 256);
}

inline VOID READ_PT_CHANNEL_SUCC_U(BYTE *buffer, S_PT_CHANNEL_SUCC_U &parameter)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

}

inline VOID READ_PT_CHANNEL_FAIL_U(BYTE *buffer, S_PT_CHANNEL_FAIL_U &parameter)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

	Stream->ReadDWORD(&parameter.ERROR_CODE);
}

inline VOID READ_PT_CHANNEL_CHATTING_M(BYTE *buffer, S_PT_CHANNEL_CHATTING_M &parameter)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

	Stream->ReadDWORD_PTR(&parameter.SESSION_ID);
	Stream->ReadWCHARs(parameter.NICKNAME, 32);
	Stream->ReadWCHARs(parameter.CHAT, 256);
}

inline VOID READ_PT_ROOM_CHATTING(BYTE *buffer, S_PT_ROOM_CHATTING &parameter)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

	Stream->ReadWCHARs(parameter.CHAT, 256);
}

inline VOID READ_PT_ROOM_CHATTING_SUCC_U(BYTE *buffer, S_PT_ROOM_CHATTING_SUCC_U &parameter)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

}

inline VOID READ_PT_ROOM_CHATTING_FAIL_U(BYTE *buffer, S_PT_ROOM_CHATTING_FAIL_U &parameter)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

	Stream->ReadDWORD(&parameter.ERROR_CODE);
}

inline VOID READ_PT_ROOM_CHATTING_M(BYTE *buffer, S_PT_ROOM_CHATTING_M &parameter)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

	Stream->ReadWCHARs(parameter.NICKNAME, 16);
	Stream->ReadWCHARs(parameter.CHAT, 256);
}

inline VOID READ_PT_LOGIN_USER(BYTE *buffer, S_PT_LOGIN_USER &parameter)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

	Stream->ReadWCHARs(parameter.USER_ID, 32);
	Stream->ReadWCHARs(parameter.USER_PWD, 32);
}

inline VOID READ_PT_LOGIN_USER_SUCC_U(BYTE *buffer, S_PT_LOGIN_USER_SUCC_U &parameter)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

	Stream->ReadDWORD(&parameter.OID);
}

inline VOID READ_PT_LOGIN_USER_FAIL_U(BYTE *buffer, S_PT_LOGIN_USER_FAIL_U &parameter)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

	Stream->ReadDWORD(&parameter.ERROR_CODE);
}

inline VOID READ_PT_LOBBY_ENTER(BYTE *buffer, S_PT_LOBBY_ENTER &parameter)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

}

inline VOID READ_PT_LOBBY_ENTER_SUCC_U(BYTE *buffer, S_PT_LOBBY_ENTER_SUCC_U &parameter)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

}

inline VOID READ_PT_LOBBY_ENTER_FAIL_U(BYTE *buffer, S_PT_LOBBY_ENTER_FAIL_U &parameter)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

}

inline VOID READ_PT_LOBBY_ENTER_M(BYTE *buffer, S_PT_LOBBY_ENTER_M &parameter)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

	Stream->ReadWCHARs(parameter.NICKNAME, 32);
}

inline VOID READ_PT_ROOM_INFO_REQ(BYTE *buffer, S_PT_ROOM_INFO_REQ &parameter)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

}

inline VOID READ_PT_ROOM_INFO_REQ_SUCC_U(BYTE *buffer, S_PT_ROOM_INFO_REQ_SUCC_U &parameter)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

	Stream->ReadBytes((BYTE*) parameter.ROOMS, sizeof(ROOM_INFO_DATA) * 10);
}

inline VOID READ_PT_ROOM_INFO_REQ_FAIL_U(BYTE *buffer, S_PT_ROOM_INFO_REQ_FAIL_U &parameter)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

}

inline VOID READ_PT_ROOM_INFO_REQ_M(BYTE *buffer, S_PT_ROOM_INFO_REQ_M &parameter)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

	Stream->ReadWCHARs(parameter.TITLE, 32);
	Stream->ReadDWORD(&parameter.CURRENTUSER);
	Stream->ReadBOOL(&parameter.STATE);
	Stream->ReadDWORD(&parameter.INDEX);
}

inline VOID READ_PT_USER_INFO_REQ(BYTE *buffer, S_PT_USER_INFO_REQ &parameter)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

}

inline VOID READ_PT_USER_INFO_REQ_SUCC_U(BYTE *buffer, S_PT_USER_INFO_REQ_SUCC_U &parameter)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

	Stream->ReadBytes((BYTE*) parameter.DATA, sizeof(USER_INFO_DATA) * 20);
}

inline VOID READ_PT_USER_INFO_REQ_FAIL_U(BYTE *buffer, S_PT_USER_INFO_REQ_FAIL_U &parameter)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

}

inline VOID READ_PT_CHANNEL_ENTER(BYTE *buffer, S_PT_CHANNEL_ENTER &parameter)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

	Stream->ReadDWORD(&parameter.OID);
	Stream->ReadWCHARs(parameter.VIRTUAL_ADDRESS, 32);
	Stream->ReadUSHORT(&parameter.VIRTUAL_PORT);
}

inline VOID READ_PT_CHANNEL_ENTER_SUCC_U(BYTE *buffer, S_PT_CHANNEL_ENTER_SUCC_U &parameter)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

	Stream->ReadDWORD_PTR(&parameter.SESSION_ID);
	Stream->ReadWCHARs(parameter.VIRTUAL_ADDRESS, 32);
	Stream->ReadUSHORT(&parameter.VIRTUAL_PORT);
	Stream->ReadWCHARs(parameter.REAL_ADDRESS, 32);
	Stream->ReadUSHORT(&parameter.REAL_PORT);
}

inline VOID READ_PT_CHANNEL_ENTER_FAIL_U(BYTE *buffer, S_PT_CHANNEL_ENTER_FAIL_U &parameter)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

	Stream->ReadDWORD(&parameter.ERROR_CODE);
}

inline VOID READ_PT_CHANNEL_ENTER_M(BYTE *buffer, S_PT_CHANNEL_ENTER_M &parameter)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

}

inline VOID READ_PT_SIGN_UP_USER(BYTE *buffer, S_PT_SIGN_UP_USER &parameter)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

	Stream->ReadWCHARs(parameter.USER_ID, 32);
	Stream->ReadWCHARs(parameter.USER_PWD, 32);
}

inline VOID READ_PT_SIGN_UP_USER_SUCC_U(BYTE *buffer, S_PT_SIGN_UP_USER_SUCC_U &parameter)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

}

inline VOID READ_PT_SIGN_UP_USER_FAIL_U(BYTE *buffer, S_PT_SIGN_UP_USER_FAIL_U &parameter)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

	Stream->ReadDWORD(&parameter.ERROR_CODE);
}

inline VOID READ_PT_QUERY_USER(BYTE *buffer, S_PT_QUERY_USER &parameter)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

	Stream->ReadWCHARs(parameter.USER_ID, 32);
}

inline VOID READ_PT_QUERY_USER_SUCC_U(BYTE *buffer, S_PT_QUERY_USER_SUCC_U &parameter)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

}

inline VOID READ_PT_QUERY_USER_FAIL_U(BYTE *buffer, S_PT_QUERY_USER_FAIL_U &parameter)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

	Stream->ReadDWORD(&parameter.ERROR_CODE);
}

inline VOID READ_PT_ROOM_CREATE(BYTE *buffer, S_PT_ROOM_CREATE &parameter)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

	Stream->ReadWCHARs(parameter.TITLE, 20);
}

inline VOID READ_PT_ROOM_CREATE_SUCC_U(BYTE *buffer, S_PT_ROOM_CREATE_SUCC_U &parameter)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

	Stream->ReadDWORD(&parameter.INDEX);
}

inline VOID READ_PT_ROOM_CREATE_FAIL_U(BYTE *buffer, S_PT_ROOM_CREATE_FAIL_U &parameter)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

	Stream->ReadDWORD(&parameter.ERROR_CODE);
}

inline VOID READ_PT_ROOM_CREATE_M(BYTE *buffer, S_PT_ROOM_CREATE_M &parameter)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

	Stream->ReadWCHARs(parameter.TITLE, 20);
	Stream->ReadDWORD(&parameter.INDEX);
	Stream->ReadDWORD(&parameter.CURRENTNUM);
}

inline VOID READ_PT_ROOM_ENTER(BYTE *buffer, S_PT_ROOM_ENTER &parameter)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

	Stream->ReadDWORD(&parameter.ROOM_ID);
}

inline VOID READ_PT_ROOM_ENTER_SUCC_U(BYTE *buffer, S_PT_ROOM_ENTER_SUCC_U &parameter)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

	Stream->ReadUSHORT(&parameter.SLOT_INDEX);
}

inline VOID READ_PT_ROOM_ENTER_FAIL_U(BYTE *buffer, S_PT_ROOM_ENTER_FAIL_U &parameter)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

	Stream->ReadDWORD(&parameter.ERROR_CODE);
}

inline VOID READ_PT_ROOM_ENTER_M(BYTE *buffer, S_PT_ROOM_ENTER_M &parameter)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

	Stream->ReadDWORD(&parameter.OID);
	Stream->ReadDWORD_PTR(&parameter.SESSION_ID);
	Stream->ReadWCHARs(parameter.NICKNAME, 32);
	Stream->ReadUSHORT(&parameter.SLOT_INDEX);
}

inline VOID READ_PT_ROOM_REQ_INFO(BYTE *buffer, S_PT_ROOM_REQ_INFO &parameter)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

}

inline VOID READ_PT_ROOM_REQ_INFO_SUCC_U(BYTE *buffer, S_PT_ROOM_REQ_INFO_SUCC_U &parameter)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

	Stream->ReadDWORD(&parameter.ROOM_INDEX);
	Stream->ReadWCHARs(parameter.TITLE, 32);
	Stream->ReadUSHORT(&parameter.CURRENT_USER_COUNT);
	Stream->ReadDWORD_PTR(&parameter.ROOT_USER_SESSION_ID);
	Stream->ReadWCHARs(parameter.ROOT_REAL_ADDRESS, 32);
	Stream->ReadUSHORT(&parameter.ROOT_REAL_PORT);
	Stream->ReadBytes((BYTE*) parameter.DATA, sizeof(SLOT_USER_DATA) * 8);
}

inline VOID READ_PT_ROOM_REQ_INFO_FAIL_U(BYTE *buffer, S_PT_ROOM_REQ_INFO_FAIL_U &parameter)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

	Stream->ReadDWORD(&parameter.ERROR_CODE);
}

inline VOID READ_PT_ROOM_LEAVE(BYTE *buffer, S_PT_ROOM_LEAVE &parameter)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

}

inline VOID READ_PT_ROOM_LEAVE_SUCC_U(BYTE *buffer, S_PT_ROOM_LEAVE_SUCC_U &parameter)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

}

inline VOID READ_PT_ROOM_LEAVE_FAIL_U(BYTE *buffer, S_PT_ROOM_LEAVE_FAIL_U &parameter)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

	Stream->ReadDWORD(&parameter.ERROR_CODE);
}

inline VOID READ_PT_ROOM_LEAVE_M(BYTE *buffer, S_PT_ROOM_LEAVE_M &parameter)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

	Stream->ReadWCHARs(parameter.OUTUSER, 32);
	Stream->ReadWCHARs(parameter.ROOTUSER, 32);
}

inline VOID READ_PT_ROOM_TEAM_CHANGE(BYTE *buffer, S_PT_ROOM_TEAM_CHANGE &parameter)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

	Stream->ReadBOOL(&parameter.TEAM);
}

inline VOID READ_PT_ROOM_TEAM_CHANGE_SUCC_U(BYTE *buffer, S_PT_ROOM_TEAM_CHANGE_SUCC_U &parameter)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

	Stream->ReadUSHORT(&parameter.SLOT_INDEX);
}

inline VOID READ_PT_ROOM_TEAM_CHANGE_FAIL_U(BYTE *buffer, S_PT_ROOM_TEAM_CHANGE_FAIL_U &parameter)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

}

inline VOID READ_PT_ROOM_TEAM_CHANGE_M(BYTE *buffer, S_PT_ROOM_TEAM_CHANGE_M &parameter)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

	Stream->ReadWCHARs(parameter.USER_ID, 32);
	Stream->ReadWCHARs(parameter.NICKNAME, 32);
	Stream->ReadUSHORT(&parameter.SLOT_INDEX);
}

inline VOID READ_PT_ROOM_READY(BYTE *buffer, S_PT_ROOM_READY &parameter)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

	Stream->ReadBOOL(&parameter.READY);
}

inline VOID READ_PT_ROOM_READY_SUCC_U(BYTE *buffer, S_PT_ROOM_READY_SUCC_U &parameter)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

}

inline VOID READ_PT_ROOM_READY_FAIL_U(BYTE *buffer, S_PT_ROOM_READY_FAIL_U &parameter)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

	Stream->ReadDWORD(&parameter.ERROR_CODE);
}

inline VOID READ_PT_ROOM_READY_M(BYTE *buffer, S_PT_ROOM_READY_M &parameter)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

	Stream->ReadDWORD(&parameter.OID);
	Stream->ReadWCHARs(parameter.NICKNAME, 32);
	Stream->ReadBOOL(&parameter.READY);
}

inline VOID READ_PT_ROOM_START(BYTE *buffer, S_PT_ROOM_START &parameter)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

}

inline VOID READ_PT_ROOM_START_SUCC_U(BYTE *buffer, S_PT_ROOM_START_SUCC_U &parameter)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

}

inline VOID READ_PT_ROOM_START_FAIL_U(BYTE *buffer, S_PT_ROOM_START_FAIL_U &parameter)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

	Stream->ReadDWORD(&parameter.ERROR_CODE);
}

inline VOID READ_PT_ROOM_START_M(BYTE *buffer, S_PT_ROOM_START_M &parameter)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

	Stream->ReadBytes((BYTE*) parameter.USERS, sizeof(USER_START_INFO) * 8);
}

inline VOID READ_PT_GAME_LOAD_COMPLETE(BYTE *buffer, S_PT_GAME_LOAD_COMPLETE &parameter)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

}

inline VOID READ_PT_GAME_LOAD_COMPLETE_SUCC_U(BYTE *buffer, S_PT_GAME_LOAD_COMPLETE_SUCC_U &parameter)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

}

inline VOID READ_PT_GAME_LOAD_COMPLETE_FAIL_U(BYTE *buffer, S_PT_GAME_LOAD_COMPLETE_FAIL_U &parameter)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

	Stream->ReadDWORD(&parameter.ERROR_CODE);
}

inline VOID READ_PT_GAME_LOAD_COMPLETE_M(BYTE *buffer, S_PT_GAME_LOAD_COMPLETE_M &parameter)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

	Stream->ReadWCHARs(parameter.USER_ID, 32);
}

inline VOID READ_PT_GAME_ALL_LOAD_COMPLETE_M(BYTE *buffer, S_PT_GAME_ALL_LOAD_COMPLETE_M &parameter)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

}

inline VOID READ_PT_GAME_INTRO_COMPLETE(BYTE *buffer, S_PT_GAME_INTRO_COMPLETE &parameter)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

}

inline VOID READ_PT_GAME_INTRO_COMPLETE_SUCC_U(BYTE *buffer, S_PT_GAME_INTRO_COMPLETE_SUCC_U &parameter)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

}

inline VOID READ_PT_GAME_INTRO_COMPLETE_FAIL_U(BYTE *buffer, S_PT_GAME_INTRO_COMPLETE_FAIL_U &parameter)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

	Stream->ReadDWORD(&parameter.ERROR_CODE);
}

inline VOID READ_PT_GAME_INTRO_COMPLETE_M(BYTE *buffer, S_PT_GAME_INTRO_COMPLETE_M &parameter)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

	Stream->ReadDWORD_PTR(&parameter.SESSION_ID);
}

inline VOID READ_PT_GAME_ALL_INTRO_COMPLETE_M(BYTE *buffer, S_PT_GAME_ALL_INTRO_COMPLETE_M &parameter)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

}

inline VOID READ_PT_GAME_START_M(BYTE *buffer, S_PT_GAME_START_M &parameter)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

	Stream->ReadDWORD(&parameter.PORT);
}

inline VOID READ_PT_ROOT_GAME_START(BYTE *buffer, S_PT_ROOT_GAME_START &parameter)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

	Stream->ReadUSHORT(&parameter.CURRENT_USER_COUNT);
	Stream->ReadBytes((BYTE*) parameter.DATA, sizeof(SLOT_USER_DATA) * 8);
	Stream->ReadDWORD(&parameter.PORT);
}

inline VOID READ_PT_GAME_END_M(BYTE *buffer, S_PT_GAME_END_M &parameter)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

}

inline VOID READ_PT_C2U_KILL_USER_M(BYTE *buffer, S_PT_C2U_KILL_USER_M &parameter)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

	Stream->ReadDWORD(&parameter.USEROID);
	Stream->ReadDWORD(&parameter.TARGETID);
}

inline VOID READ_PT_U2C_REGEN_USER(BYTE *buffer, S_PT_U2C_REGEN_USER &parameter)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

}

inline VOID READ_PT_C2U_REGEN_USER_SUCC_U(BYTE *buffer, S_PT_C2U_REGEN_USER_SUCC_U &parameter)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

}

inline VOID READ_PT_C2U_REGEN_USER_FAIL_U(BYTE *buffer, S_PT_C2U_REGEN_USER_FAIL_U &parameter)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

}

inline VOID READ_PT_C2U_RESULT_M(BYTE *buffer, S_PT_C2U_RESULT_M &parameter)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

	Stream->ReadUSHORT(&parameter.WINTEAM);
	Stream->ReadBytes((BYTE*) parameter.DATA, sizeof(RESULT_USER_DATA) * 8);
}

