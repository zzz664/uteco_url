#pragma once
#include "TCP_Structure.h"

inline DWORD WRITE_PT_CHANNEL_NICKNAME(BYTE *buffer, S_PT_CHANNEL_NICKNAME &parameter)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

	Stream->WriteWCHARs(parameter.USER_ID, 32);

	return Stream->GetLength();
}

inline DWORD WRITE_PT_CHANNEL_NICKNAME_SUCC_U(BYTE *buffer, S_PT_CHANNEL_NICKNAME_SUCC_U &parameter)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

	Stream->WriteWCHARs(parameter.USER_ID, 32);
	Stream->WriteWCHARs(parameter.NICK_NAME, 32);

	return Stream->GetLength();
}

inline DWORD WRITE_PT_CHANNEL_NICKNAME_FAIL_U(BYTE *buffer, S_PT_CHANNEL_NICKNAME_FAIL_U &parameter)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

	Stream->WriteDWORD(parameter.ERROR_CODE);

	return Stream->GetLength();
}

inline DWORD WRITE_PT_QUERY_NICKNAME(BYTE *buffer, S_PT_QUERY_NICKNAME &parameter)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

	Stream->WriteWCHARs(parameter.NICK_NAME, 32);

	return Stream->GetLength();
}

inline DWORD WRITE_PT_QUERY_NICKNAME_SUCC_U(BYTE *buffer, S_PT_QUERY_NICKNAME_SUCC_U &parameter)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);


	return Stream->GetLength();
}

inline DWORD WRITE_PT_QUERY_NICKNAME_FAIL_U(BYTE *buffer, S_PT_QUERY_NICKNAME_FAIL_U &parameter)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);


	return Stream->GetLength();
}

inline DWORD WRITE_PT_INSERT_NICKNAME(BYTE *buffer, S_PT_INSERT_NICKNAME &parameter)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

	Stream->WriteWCHARs(parameter.USER_ID, 32);
	Stream->WriteWCHARs(parameter.NICKNAME, 32);

	return Stream->GetLength();
}

inline DWORD WRITE_PT_INSERT_NICKNAME_SUCC_U(BYTE *buffer, S_PT_INSERT_NICKNAME_SUCC_U &parameter)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);


	return Stream->GetLength();
}

inline DWORD WRITE_PT_INSERT_NICKNAME_FAIL_U(BYTE *buffer, S_PT_INSERT_NICKNAME_FAIL_U &parameter)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);


	return Stream->GetLength();
}

inline DWORD WRITE_PT_CHANNEL_CHATTING(BYTE *buffer, S_PT_CHANNEL_CHATTING &parameter)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

	Stream->WriteWCHARs(parameter.CHAT, 256);

	return Stream->GetLength();
}

inline DWORD WRITE_PT_CHANNEL_SUCC_U(BYTE *buffer, S_PT_CHANNEL_SUCC_U &parameter)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);


	return Stream->GetLength();
}

inline DWORD WRITE_PT_CHANNEL_FAIL_U(BYTE *buffer, S_PT_CHANNEL_FAIL_U &parameter)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

	Stream->WriteDWORD(parameter.ERROR_CODE);

	return Stream->GetLength();
}

inline DWORD WRITE_PT_CHANNEL_CHATTING_M(BYTE *buffer, S_PT_CHANNEL_CHATTING_M &parameter)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

	Stream->WriteDWORD_PTR(parameter.SESSION_ID);
	Stream->WriteWCHARs(parameter.NICKNAME, 32);
	Stream->WriteWCHARs(parameter.CHAT, 256);

	return Stream->GetLength();
}

inline DWORD WRITE_PT_ROOM_CHATTING(BYTE *buffer, S_PT_ROOM_CHATTING &parameter)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

	Stream->WriteWCHARs(parameter.CHAT, 256);

	return Stream->GetLength();
}

inline DWORD WRITE_PT_ROOM_CHATTING_SUCC_U(BYTE *buffer, S_PT_ROOM_CHATTING_SUCC_U &parameter)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);


	return Stream->GetLength();
}

inline DWORD WRITE_PT_ROOM_CHATTING_FAIL_U(BYTE *buffer, S_PT_ROOM_CHATTING_FAIL_U &parameter)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

	Stream->WriteDWORD(parameter.ERROR_CODE);

	return Stream->GetLength();
}

inline DWORD WRITE_PT_ROOM_CHATTING_M(BYTE *buffer, S_PT_ROOM_CHATTING_M &parameter)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

	Stream->WriteWCHARs(parameter.NICKNAME, 16);
	Stream->WriteWCHARs(parameter.CHAT, 256);

	return Stream->GetLength();
}

inline DWORD WRITE_PT_LOGIN_USER(BYTE *buffer, S_PT_LOGIN_USER &parameter)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

	Stream->WriteWCHARs(parameter.USER_ID, 32);
	Stream->WriteWCHARs(parameter.USER_PWD, 32);

	return Stream->GetLength();
}

inline DWORD WRITE_PT_LOGIN_USER_SUCC_U(BYTE *buffer, S_PT_LOGIN_USER_SUCC_U &parameter)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

	Stream->WriteDWORD(parameter.OID);

	return Stream->GetLength();
}

inline DWORD WRITE_PT_LOGIN_USER_FAIL_U(BYTE *buffer, S_PT_LOGIN_USER_FAIL_U &parameter)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

	Stream->WriteDWORD(parameter.ERROR_CODE);

	return Stream->GetLength();
}

inline DWORD WRITE_PT_LOBBY_ENTER(BYTE *buffer, S_PT_LOBBY_ENTER &parameter)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);


	return Stream->GetLength();
}

inline DWORD WRITE_PT_LOBBY_ENTER_SUCC_U(BYTE *buffer, S_PT_LOBBY_ENTER_SUCC_U &parameter)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);


	return Stream->GetLength();
}

inline DWORD WRITE_PT_LOBBY_ENTER_FAIL_U(BYTE *buffer, S_PT_LOBBY_ENTER_FAIL_U &parameter)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);


	return Stream->GetLength();
}

inline DWORD WRITE_PT_LOBBY_ENTER_M(BYTE *buffer, S_PT_LOBBY_ENTER_M &parameter)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

	Stream->WriteWCHARs(parameter.NICKNAME, 32);

	return Stream->GetLength();
}

inline DWORD WRITE_PT_ROOM_INFO_REQ(BYTE *buffer, S_PT_ROOM_INFO_REQ &parameter)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);


	return Stream->GetLength();
}

inline DWORD WRITE_PT_ROOM_INFO_REQ_SUCC_U(BYTE *buffer, S_PT_ROOM_INFO_REQ_SUCC_U &parameter)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

	Stream->WriteBytes((BYTE*) parameter.ROOMS, sizeof(ROOM_INFO_DATA) * 10);

	return Stream->GetLength();
}

inline DWORD WRITE_PT_ROOM_INFO_REQ_FAIL_U(BYTE *buffer, S_PT_ROOM_INFO_REQ_FAIL_U &parameter)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);


	return Stream->GetLength();
}

inline DWORD WRITE_PT_ROOM_INFO_REQ_M(BYTE *buffer, S_PT_ROOM_INFO_REQ_M &parameter)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

	Stream->WriteWCHARs(parameter.TITLE, 32);
	Stream->WriteDWORD(parameter.CURRENTUSER);
	Stream->WriteBOOL(parameter.STATE);
	Stream->WriteDWORD(parameter.INDEX);

	return Stream->GetLength();
}

inline DWORD WRITE_PT_USER_INFO_REQ(BYTE *buffer, S_PT_USER_INFO_REQ &parameter)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);


	return Stream->GetLength();
}

inline DWORD WRITE_PT_USER_INFO_REQ_SUCC_U(BYTE *buffer, S_PT_USER_INFO_REQ_SUCC_U &parameter)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

	Stream->WriteBytes((BYTE*) parameter.DATA, sizeof(USER_INFO_DATA) * 20);

	return Stream->GetLength();
}

inline DWORD WRITE_PT_USER_INFO_REQ_FAIL_U(BYTE *buffer, S_PT_USER_INFO_REQ_FAIL_U &parameter)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);


	return Stream->GetLength();
}

inline DWORD WRITE_PT_CHANNEL_ENTER(BYTE *buffer, S_PT_CHANNEL_ENTER &parameter)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

	Stream->WriteDWORD(parameter.OID);
	Stream->WriteWCHARs(parameter.VIRTUAL_ADDRESS, 32);
	Stream->WriteUSHORT(parameter.VIRTUAL_PORT);

	return Stream->GetLength();
}

inline DWORD WRITE_PT_CHANNEL_ENTER_SUCC_U(BYTE *buffer, S_PT_CHANNEL_ENTER_SUCC_U &parameter)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

	Stream->WriteDWORD_PTR(parameter.SESSION_ID);
	Stream->WriteWCHARs(parameter.VIRTUAL_ADDRESS, 32);
	Stream->WriteUSHORT(parameter.VIRTUAL_PORT);
	Stream->WriteWCHARs(parameter.REAL_ADDRESS, 32);
	Stream->WriteUSHORT(parameter.REAL_PORT);

	return Stream->GetLength();
}

inline DWORD WRITE_PT_CHANNEL_ENTER_FAIL_U(BYTE *buffer, S_PT_CHANNEL_ENTER_FAIL_U &parameter)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

	Stream->WriteDWORD(parameter.ERROR_CODE);

	return Stream->GetLength();
}

inline DWORD WRITE_PT_CHANNEL_ENTER_M(BYTE *buffer, S_PT_CHANNEL_ENTER_M &parameter)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);


	return Stream->GetLength();
}

inline DWORD WRITE_PT_SIGN_UP_USER(BYTE *buffer, S_PT_SIGN_UP_USER &parameter)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

	Stream->WriteWCHARs(parameter.USER_ID, 32);
	Stream->WriteWCHARs(parameter.USER_PWD, 32);

	return Stream->GetLength();
}

inline DWORD WRITE_PT_SIGN_UP_USER_SUCC_U(BYTE *buffer, S_PT_SIGN_UP_USER_SUCC_U &parameter)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);


	return Stream->GetLength();
}

inline DWORD WRITE_PT_SIGN_UP_USER_FAIL_U(BYTE *buffer, S_PT_SIGN_UP_USER_FAIL_U &parameter)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

	Stream->WriteDWORD(parameter.ERROR_CODE);

	return Stream->GetLength();
}

inline DWORD WRITE_PT_QUERY_USER(BYTE *buffer, S_PT_QUERY_USER &parameter)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

	Stream->WriteWCHARs(parameter.USER_ID, 32);

	return Stream->GetLength();
}

inline DWORD WRITE_PT_QUERY_USER_SUCC_U(BYTE *buffer, S_PT_QUERY_USER_SUCC_U &parameter)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);


	return Stream->GetLength();
}

inline DWORD WRITE_PT_QUERY_USER_FAIL_U(BYTE *buffer, S_PT_QUERY_USER_FAIL_U &parameter)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

	Stream->WriteDWORD(parameter.ERROR_CODE);

	return Stream->GetLength();
}

inline DWORD WRITE_PT_ROOM_CREATE(BYTE *buffer, S_PT_ROOM_CREATE &parameter)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

	Stream->WriteWCHARs(parameter.TITLE, 20);

	return Stream->GetLength();
}

inline DWORD WRITE_PT_ROOM_CREATE_SUCC_U(BYTE *buffer, S_PT_ROOM_CREATE_SUCC_U &parameter)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

	Stream->WriteDWORD(parameter.INDEX);

	return Stream->GetLength();
}

inline DWORD WRITE_PT_ROOM_CREATE_FAIL_U(BYTE *buffer, S_PT_ROOM_CREATE_FAIL_U &parameter)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

	Stream->WriteDWORD(parameter.ERROR_CODE);

	return Stream->GetLength();
}

inline DWORD WRITE_PT_ROOM_CREATE_M(BYTE *buffer, S_PT_ROOM_CREATE_M &parameter)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

	Stream->WriteWCHARs(parameter.TITLE, 20);
	Stream->WriteDWORD(parameter.INDEX);
	Stream->WriteDWORD(parameter.CURRENTNUM);

	return Stream->GetLength();
}

inline DWORD WRITE_PT_ROOM_ENTER(BYTE *buffer, S_PT_ROOM_ENTER &parameter)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

	Stream->WriteDWORD(parameter.ROOM_ID);

	return Stream->GetLength();
}

inline DWORD WRITE_PT_ROOM_ENTER_SUCC_U(BYTE *buffer, S_PT_ROOM_ENTER_SUCC_U &parameter)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

	Stream->WriteUSHORT(parameter.SLOT_INDEX);

	return Stream->GetLength();
}

inline DWORD WRITE_PT_ROOM_ENTER_FAIL_U(BYTE *buffer, S_PT_ROOM_ENTER_FAIL_U &parameter)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

	Stream->WriteDWORD(parameter.ERROR_CODE);

	return Stream->GetLength();
}

inline DWORD WRITE_PT_ROOM_ENTER_M(BYTE *buffer, S_PT_ROOM_ENTER_M &parameter)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

	Stream->WriteDWORD(parameter.OID);
	Stream->WriteDWORD_PTR(parameter.SESSION_ID);
	Stream->WriteWCHARs(parameter.NICKNAME, 32);
	Stream->WriteUSHORT(parameter.SLOT_INDEX);

	return Stream->GetLength();
}

inline DWORD WRITE_PT_ROOM_REQ_INFO(BYTE *buffer, S_PT_ROOM_REQ_INFO &parameter)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);


	return Stream->GetLength();
}

inline DWORD WRITE_PT_ROOM_REQ_INFO_SUCC_U(BYTE *buffer, S_PT_ROOM_REQ_INFO_SUCC_U &parameter)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

	Stream->WriteDWORD(parameter.ROOM_INDEX);
	Stream->WriteWCHARs(parameter.TITLE, 32);
	Stream->WriteUSHORT(parameter.CURRENT_USER_COUNT);
	Stream->WriteDWORD_PTR(parameter.ROOT_USER_SESSION_ID);
	Stream->WriteWCHARs(parameter.ROOT_REAL_ADDRESS, 32);
	Stream->WriteUSHORT(parameter.ROOT_REAL_PORT);
	Stream->WriteBytes((BYTE*) parameter.DATA, sizeof(SLOT_USER_DATA) * 8);

	return Stream->GetLength();
}

inline DWORD WRITE_PT_ROOM_REQ_INFO_FAIL_U(BYTE *buffer, S_PT_ROOM_REQ_INFO_FAIL_U &parameter)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

	Stream->WriteDWORD(parameter.ERROR_CODE);

	return Stream->GetLength();
}

inline DWORD WRITE_PT_ROOM_LEAVE(BYTE *buffer, S_PT_ROOM_LEAVE &parameter)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);


	return Stream->GetLength();
}

inline DWORD WRITE_PT_ROOM_LEAVE_SUCC_U(BYTE *buffer, S_PT_ROOM_LEAVE_SUCC_U &parameter)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);


	return Stream->GetLength();
}

inline DWORD WRITE_PT_ROOM_LEAVE_FAIL_U(BYTE *buffer, S_PT_ROOM_LEAVE_FAIL_U &parameter)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

	Stream->WriteDWORD(parameter.ERROR_CODE);

	return Stream->GetLength();
}

inline DWORD WRITE_PT_ROOM_LEAVE_M(BYTE *buffer, S_PT_ROOM_LEAVE_M &parameter)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

	Stream->WriteWCHARs(parameter.OUTUSER, 32);
	Stream->WriteWCHARs(parameter.ROOTUSER, 32);

	return Stream->GetLength();
}

inline DWORD WRITE_PT_ROOM_TEAM_CHANGE(BYTE *buffer, S_PT_ROOM_TEAM_CHANGE &parameter)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

	Stream->WriteBOOL(parameter.TEAM);

	return Stream->GetLength();
}

inline DWORD WRITE_PT_ROOM_TEAM_CHANGE_SUCC_U(BYTE *buffer, S_PT_ROOM_TEAM_CHANGE_SUCC_U &parameter)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

	Stream->WriteUSHORT(parameter.SLOT_INDEX);

	return Stream->GetLength();
}

inline DWORD WRITE_PT_ROOM_TEAM_CHANGE_FAIL_U(BYTE *buffer, S_PT_ROOM_TEAM_CHANGE_FAIL_U &parameter)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);


	return Stream->GetLength();
}

inline DWORD WRITE_PT_ROOM_TEAM_CHANGE_M(BYTE *buffer, S_PT_ROOM_TEAM_CHANGE_M &parameter)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

	Stream->WriteWCHARs(parameter.USER_ID, 32);
	Stream->WriteWCHARs(parameter.NICKNAME, 32);
	Stream->WriteUSHORT(parameter.SLOT_INDEX);

	return Stream->GetLength();
}

inline DWORD WRITE_PT_ROOM_READY(BYTE *buffer, S_PT_ROOM_READY &parameter)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

	Stream->WriteBOOL(parameter.READY);

	return Stream->GetLength();
}

inline DWORD WRITE_PT_ROOM_READY_SUCC_U(BYTE *buffer, S_PT_ROOM_READY_SUCC_U &parameter)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);


	return Stream->GetLength();
}

inline DWORD WRITE_PT_ROOM_READY_FAIL_U(BYTE *buffer, S_PT_ROOM_READY_FAIL_U &parameter)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

	Stream->WriteDWORD(parameter.ERROR_CODE);

	return Stream->GetLength();
}

inline DWORD WRITE_PT_ROOM_READY_M(BYTE *buffer, S_PT_ROOM_READY_M &parameter)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

	Stream->WriteDWORD(parameter.OID);
	Stream->WriteWCHARs(parameter.NICKNAME, 32);
	Stream->WriteBOOL(parameter.READY);

	return Stream->GetLength();
}

inline DWORD WRITE_PT_ROOM_START(BYTE *buffer, S_PT_ROOM_START &parameter)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);


	return Stream->GetLength();
}

inline DWORD WRITE_PT_ROOM_START_SUCC_U(BYTE *buffer, S_PT_ROOM_START_SUCC_U &parameter)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);


	return Stream->GetLength();
}

inline DWORD WRITE_PT_ROOM_START_FAIL_U(BYTE *buffer, S_PT_ROOM_START_FAIL_U &parameter)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

	Stream->WriteDWORD(parameter.ERROR_CODE);

	return Stream->GetLength();
}

inline DWORD WRITE_PT_ROOM_START_M(BYTE *buffer, S_PT_ROOM_START_M &parameter)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

	Stream->WriteBytes((BYTE*) parameter.USERS, sizeof(USER_START_INFO) * 8);

	return Stream->GetLength();
}

inline DWORD WRITE_PT_GAME_LOAD_COMPLETE(BYTE *buffer, S_PT_GAME_LOAD_COMPLETE &parameter)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);


	return Stream->GetLength();
}

inline DWORD WRITE_PT_GAME_LOAD_COMPLETE_SUCC_U(BYTE *buffer, S_PT_GAME_LOAD_COMPLETE_SUCC_U &parameter)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);


	return Stream->GetLength();
}

inline DWORD WRITE_PT_GAME_LOAD_COMPLETE_FAIL_U(BYTE *buffer, S_PT_GAME_LOAD_COMPLETE_FAIL_U &parameter)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

	Stream->WriteDWORD(parameter.ERROR_CODE);

	return Stream->GetLength();
}

inline DWORD WRITE_PT_GAME_LOAD_COMPLETE_M(BYTE *buffer, S_PT_GAME_LOAD_COMPLETE_M &parameter)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

	Stream->WriteWCHARs(parameter.USER_ID, 32);

	return Stream->GetLength();
}

inline DWORD WRITE_PT_GAME_ALL_LOAD_COMPLETE_M(BYTE *buffer, S_PT_GAME_ALL_LOAD_COMPLETE_M &parameter)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);


	return Stream->GetLength();
}

inline DWORD WRITE_PT_GAME_INTRO_COMPLETE(BYTE *buffer, S_PT_GAME_INTRO_COMPLETE &parameter)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);


	return Stream->GetLength();
}

inline DWORD WRITE_PT_GAME_INTRO_COMPLETE_SUCC_U(BYTE *buffer, S_PT_GAME_INTRO_COMPLETE_SUCC_U &parameter)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);


	return Stream->GetLength();
}

inline DWORD WRITE_PT_GAME_INTRO_COMPLETE_FAIL_U(BYTE *buffer, S_PT_GAME_INTRO_COMPLETE_FAIL_U &parameter)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

	Stream->WriteDWORD(parameter.ERROR_CODE);

	return Stream->GetLength();
}

inline DWORD WRITE_PT_GAME_INTRO_COMPLETE_M(BYTE *buffer, S_PT_GAME_INTRO_COMPLETE_M &parameter)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

	Stream->WriteDWORD_PTR(parameter.SESSION_ID);

	return Stream->GetLength();
}

inline DWORD WRITE_PT_GAME_ALL_INTRO_COMPLETE_M(BYTE *buffer, S_PT_GAME_ALL_INTRO_COMPLETE_M &parameter)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);


	return Stream->GetLength();
}

inline DWORD WRITE_PT_GAME_START_M(BYTE *buffer, S_PT_GAME_START_M &parameter)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

	Stream->WriteDWORD(parameter.PORT);

	return Stream->GetLength();
}

inline DWORD WRITE_PT_ROOT_GAME_START(BYTE *buffer, S_PT_ROOT_GAME_START &parameter)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

	Stream->WriteUSHORT(parameter.CURRENT_USER_COUNT);
	Stream->WriteBytes((BYTE*) parameter.DATA, sizeof(SLOT_USER_DATA) * 8);
	Stream->WriteDWORD(parameter.PORT);

	return Stream->GetLength();
}

inline DWORD WRITE_PT_GAME_END_M(BYTE *buffer, S_PT_GAME_END_M &parameter)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);


	return Stream->GetLength();
}

inline DWORD WRITE_PT_C2U_KILL_USER_M(BYTE *buffer, S_PT_C2U_KILL_USER_M &parameter)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

	Stream->WriteDWORD(parameter.USEROID);
	Stream->WriteDWORD(parameter.TARGETID);

	return Stream->GetLength();
}

inline DWORD WRITE_PT_U2C_REGEN_USER(BYTE *buffer, S_PT_U2C_REGEN_USER &parameter)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);


	return Stream->GetLength();
}

inline DWORD WRITE_PT_C2U_REGEN_USER_SUCC_U(BYTE *buffer, S_PT_C2U_REGEN_USER_SUCC_U &parameter)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);


	return Stream->GetLength();
}

inline DWORD WRITE_PT_C2U_REGEN_USER_FAIL_U(BYTE *buffer, S_PT_C2U_REGEN_USER_FAIL_U &parameter)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);


	return Stream->GetLength();
}

inline DWORD WRITE_PT_C2U_RESULT_M(BYTE *buffer, S_PT_C2U_RESULT_M &parameter)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

	Stream->WriteUSHORT(parameter.WINTEAM);
	Stream->WriteBytes((BYTE*) parameter.DATA, sizeof(RESULT_USER_DATA) * 8);

	return Stream->GetLength();
}

inline DWORD WRITE_PT_CHANNEL_NICKNAME(BYTE *buffer, WCHAR *user_id)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

	WCHAR _user_id[32] = {0,};
	_tcsncpy(_user_id, user_id, 32);
	Stream->WriteWCHARs(_user_id, 32);

	return Stream->GetLength();
}

inline DWORD WRITE_PT_CHANNEL_NICKNAME_SUCC_U(BYTE *buffer, WCHAR *user_id, WCHAR *nick_name)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

	WCHAR _user_id[32] = {0,};
	_tcsncpy(_user_id, user_id, 32);
	Stream->WriteWCHARs(_user_id, 32);
	WCHAR _nick_name[32] = {0,};
	_tcsncpy(_nick_name, nick_name, 32);
	Stream->WriteWCHARs(_nick_name, 32);

	return Stream->GetLength();
}

inline DWORD WRITE_PT_CHANNEL_NICKNAME_FAIL_U(BYTE *buffer, DWORD error_code)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

	Stream->WriteDWORD(error_code);

	return Stream->GetLength();
}

inline DWORD WRITE_PT_QUERY_NICKNAME(BYTE *buffer, WCHAR *nick_name)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

	WCHAR _nick_name[32] = {0,};
	_tcsncpy(_nick_name, nick_name, 32);
	Stream->WriteWCHARs(_nick_name, 32);

	return Stream->GetLength();
}

inline DWORD WRITE_PT_QUERY_NICKNAME_SUCC_U(BYTE *buffer)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);


	return Stream->GetLength();
}

inline DWORD WRITE_PT_QUERY_NICKNAME_FAIL_U(BYTE *buffer)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);


	return Stream->GetLength();
}

inline DWORD WRITE_PT_INSERT_NICKNAME(BYTE *buffer, WCHAR *user_id, WCHAR *nickname)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

	WCHAR _user_id[32] = {0,};
	_tcsncpy(_user_id, user_id, 32);
	Stream->WriteWCHARs(_user_id, 32);
	WCHAR _nickname[32] = {0,};
	_tcsncpy(_nickname, nickname, 32);
	Stream->WriteWCHARs(_nickname, 32);

	return Stream->GetLength();
}

inline DWORD WRITE_PT_INSERT_NICKNAME_SUCC_U(BYTE *buffer)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);


	return Stream->GetLength();
}

inline DWORD WRITE_PT_INSERT_NICKNAME_FAIL_U(BYTE *buffer)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);


	return Stream->GetLength();
}

inline DWORD WRITE_PT_CHANNEL_CHATTING(BYTE *buffer, WCHAR *chat)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

	WCHAR _chat[256] = {0,};
	_tcsncpy(_chat, chat, 256);
	Stream->WriteWCHARs(_chat, 256);

	return Stream->GetLength();
}

inline DWORD WRITE_PT_CHANNEL_SUCC_U(BYTE *buffer)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);


	return Stream->GetLength();
}

inline DWORD WRITE_PT_CHANNEL_FAIL_U(BYTE *buffer, DWORD error_code)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

	Stream->WriteDWORD(error_code);

	return Stream->GetLength();
}

inline DWORD WRITE_PT_CHANNEL_CHATTING_M(BYTE *buffer, DWORD_PTR session_id, WCHAR *nickname, WCHAR *chat)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

	Stream->WriteDWORD_PTR(session_id);
	WCHAR _nickname[32] = {0,};
	_tcsncpy(_nickname, nickname, 32);
	Stream->WriteWCHARs(_nickname, 32);
	WCHAR _chat[256] = {0,};
	_tcsncpy(_chat, chat, 256);
	Stream->WriteWCHARs(_chat, 256);

	return Stream->GetLength();
}

inline DWORD WRITE_PT_ROOM_CHATTING(BYTE *buffer, WCHAR *chat)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

	WCHAR _chat[256] = {0,};
	_tcsncpy(_chat, chat, 256);
	Stream->WriteWCHARs(_chat, 256);

	return Stream->GetLength();
}

inline DWORD WRITE_PT_ROOM_CHATTING_SUCC_U(BYTE *buffer)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);


	return Stream->GetLength();
}

inline DWORD WRITE_PT_ROOM_CHATTING_FAIL_U(BYTE *buffer, DWORD error_code)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

	Stream->WriteDWORD(error_code);

	return Stream->GetLength();
}

inline DWORD WRITE_PT_ROOM_CHATTING_M(BYTE *buffer, WCHAR *nickname, WCHAR *chat)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

	WCHAR _nickname[16] = {0,};
	_tcsncpy(_nickname, nickname, 16);
	Stream->WriteWCHARs(_nickname, 16);
	WCHAR _chat[256] = {0,};
	_tcsncpy(_chat, chat, 256);
	Stream->WriteWCHARs(_chat, 256);

	return Stream->GetLength();
}

inline DWORD WRITE_PT_LOGIN_USER(BYTE *buffer, WCHAR *user_id, WCHAR *user_pwd)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

	WCHAR _user_id[32] = {0,};
	_tcsncpy(_user_id, user_id, 32);
	Stream->WriteWCHARs(_user_id, 32);
	WCHAR _user_pwd[32] = {0,};
	_tcsncpy(_user_pwd, user_pwd, 32);
	Stream->WriteWCHARs(_user_pwd, 32);

	return Stream->GetLength();
}

inline DWORD WRITE_PT_LOGIN_USER_SUCC_U(BYTE *buffer, DWORD oid)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

	Stream->WriteDWORD(oid);

	return Stream->GetLength();
}

inline DWORD WRITE_PT_LOGIN_USER_FAIL_U(BYTE *buffer, DWORD error_code)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

	Stream->WriteDWORD(error_code);

	return Stream->GetLength();
}

inline DWORD WRITE_PT_LOBBY_ENTER(BYTE *buffer)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);


	return Stream->GetLength();
}

inline DWORD WRITE_PT_LOBBY_ENTER_SUCC_U(BYTE *buffer)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);


	return Stream->GetLength();
}

inline DWORD WRITE_PT_LOBBY_ENTER_FAIL_U(BYTE *buffer)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);


	return Stream->GetLength();
}

inline DWORD WRITE_PT_LOBBY_ENTER_M(BYTE *buffer, WCHAR *nickname)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

	WCHAR _nickname[32] = {0,};
	_tcsncpy(_nickname, nickname, 32);
	Stream->WriteWCHARs(_nickname, 32);

	return Stream->GetLength();
}

inline DWORD WRITE_PT_ROOM_INFO_REQ(BYTE *buffer)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);


	return Stream->GetLength();
}

inline DWORD WRITE_PT_ROOM_INFO_REQ_SUCC_U(BYTE *buffer, ROOM_INFO_DATA *rooms)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

	Stream->WriteBytes((BYTE*) rooms, sizeof(ROOM_INFO_DATA) * 10);

	return Stream->GetLength();
}

inline DWORD WRITE_PT_ROOM_INFO_REQ_FAIL_U(BYTE *buffer)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);


	return Stream->GetLength();
}

inline DWORD WRITE_PT_ROOM_INFO_REQ_M(BYTE *buffer, WCHAR *title, DWORD currentuser, BOOL state, DWORD index)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

	WCHAR _title[32] = {0,};
	_tcsncpy(_title, title, 32);
	Stream->WriteWCHARs(_title, 32);
	Stream->WriteDWORD(currentuser);
	Stream->WriteBOOL(state);
	Stream->WriteDWORD(index);

	return Stream->GetLength();
}

inline DWORD WRITE_PT_USER_INFO_REQ(BYTE *buffer)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);


	return Stream->GetLength();
}

inline DWORD WRITE_PT_USER_INFO_REQ_SUCC_U(BYTE *buffer, USER_INFO_DATA *data)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

	Stream->WriteBytes((BYTE*) data, sizeof(USER_INFO_DATA) * 20);

	return Stream->GetLength();
}

inline DWORD WRITE_PT_USER_INFO_REQ_FAIL_U(BYTE *buffer)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);


	return Stream->GetLength();
}

inline DWORD WRITE_PT_CHANNEL_ENTER(BYTE *buffer, DWORD oid, WCHAR *virtual_address, USHORT virtual_port)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

	Stream->WriteDWORD(oid);
	WCHAR _virtual_address[32] = {0,};
	_tcsncpy(_virtual_address, virtual_address, 32);
	Stream->WriteWCHARs(_virtual_address, 32);
	Stream->WriteUSHORT(virtual_port);

	return Stream->GetLength();
}

inline DWORD WRITE_PT_CHANNEL_ENTER_SUCC_U(BYTE *buffer, DWORD_PTR session_id, WCHAR *virtual_address, USHORT virtual_port, WCHAR *real_address, USHORT real_port)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

	Stream->WriteDWORD_PTR(session_id);
	WCHAR _virtual_address[32] = {0,};
	_tcsncpy(_virtual_address, virtual_address, 32);
	Stream->WriteWCHARs(_virtual_address, 32);
	Stream->WriteUSHORT(virtual_port);
	WCHAR _real_address[32] = {0,};
	_tcsncpy(_real_address, real_address, 32);
	Stream->WriteWCHARs(_real_address, 32);
	Stream->WriteUSHORT(real_port);

	return Stream->GetLength();
}

inline DWORD WRITE_PT_CHANNEL_ENTER_FAIL_U(BYTE *buffer, DWORD error_code)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

	Stream->WriteDWORD(error_code);

	return Stream->GetLength();
}

inline DWORD WRITE_PT_CHANNEL_ENTER_M(BYTE *buffer)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);


	return Stream->GetLength();
}

inline DWORD WRITE_PT_SIGN_UP_USER(BYTE *buffer, WCHAR *user_id, WCHAR *user_pwd)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

	WCHAR _user_id[32] = {0,};
	_tcsncpy(_user_id, user_id, 32);
	Stream->WriteWCHARs(_user_id, 32);
	WCHAR _user_pwd[32] = {0,};
	_tcsncpy(_user_pwd, user_pwd, 32);
	Stream->WriteWCHARs(_user_pwd, 32);

	return Stream->GetLength();
}

inline DWORD WRITE_PT_SIGN_UP_USER_SUCC_U(BYTE *buffer)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);


	return Stream->GetLength();
}

inline DWORD WRITE_PT_SIGN_UP_USER_FAIL_U(BYTE *buffer, DWORD error_code)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

	Stream->WriteDWORD(error_code);

	return Stream->GetLength();
}

inline DWORD WRITE_PT_QUERY_USER(BYTE *buffer, WCHAR *user_id)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

	WCHAR _user_id[32] = {0,};
	_tcsncpy(_user_id, user_id, 32);
	Stream->WriteWCHARs(_user_id, 32);

	return Stream->GetLength();
}

inline DWORD WRITE_PT_QUERY_USER_SUCC_U(BYTE *buffer)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);


	return Stream->GetLength();
}

inline DWORD WRITE_PT_QUERY_USER_FAIL_U(BYTE *buffer, DWORD error_code)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

	Stream->WriteDWORD(error_code);

	return Stream->GetLength();
}

inline DWORD WRITE_PT_ROOM_CREATE(BYTE *buffer, WCHAR *title)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

	WCHAR _title[20] = {0,};
	_tcsncpy(_title, title, 20);
	Stream->WriteWCHARs(_title, 20);

	return Stream->GetLength();
}

inline DWORD WRITE_PT_ROOM_CREATE_SUCC_U(BYTE *buffer, DWORD index)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

	Stream->WriteDWORD(index);

	return Stream->GetLength();
}

inline DWORD WRITE_PT_ROOM_CREATE_FAIL_U(BYTE *buffer, DWORD error_code)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

	Stream->WriteDWORD(error_code);

	return Stream->GetLength();
}

inline DWORD WRITE_PT_ROOM_CREATE_M(BYTE *buffer, WCHAR *title, DWORD index, DWORD currentnum)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

	WCHAR _title[20] = {0,};
	_tcsncpy(_title, title, 20);
	Stream->WriteWCHARs(_title, 20);
	Stream->WriteDWORD(index);
	Stream->WriteDWORD(currentnum);

	return Stream->GetLength();
}

inline DWORD WRITE_PT_ROOM_ENTER(BYTE *buffer, DWORD room_id)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

	Stream->WriteDWORD(room_id);

	return Stream->GetLength();
}

inline DWORD WRITE_PT_ROOM_ENTER_SUCC_U(BYTE *buffer, USHORT slot_index)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

	Stream->WriteUSHORT(slot_index);

	return Stream->GetLength();
}

inline DWORD WRITE_PT_ROOM_ENTER_FAIL_U(BYTE *buffer, DWORD error_code)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

	Stream->WriteDWORD(error_code);

	return Stream->GetLength();
}

inline DWORD WRITE_PT_ROOM_ENTER_M(BYTE *buffer, DWORD oid, DWORD_PTR session_id, WCHAR *nickname, USHORT slot_index)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

	Stream->WriteDWORD(oid);
	Stream->WriteDWORD_PTR(session_id);
	WCHAR _nickname[32] = {0,};
	_tcsncpy(_nickname, nickname, 32);
	Stream->WriteWCHARs(_nickname, 32);
	Stream->WriteUSHORT(slot_index);

	return Stream->GetLength();
}

inline DWORD WRITE_PT_ROOM_REQ_INFO(BYTE *buffer)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);


	return Stream->GetLength();
}

inline DWORD WRITE_PT_ROOM_REQ_INFO_SUCC_U(BYTE *buffer, DWORD room_index, WCHAR *title, USHORT current_user_count, DWORD_PTR root_user_session_id, WCHAR *root_real_address, USHORT root_real_port, SLOT_USER_DATA *data)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

	Stream->WriteDWORD(room_index);
	WCHAR _title[32] = {0,};
	_tcsncpy(_title, title, 32);
	Stream->WriteWCHARs(_title, 32);
	Stream->WriteUSHORT(current_user_count);
	Stream->WriteDWORD_PTR(root_user_session_id);
	WCHAR _root_real_address[32] = {0,};
	_tcsncpy(_root_real_address, root_real_address, 32);
	Stream->WriteWCHARs(_root_real_address, 32);
	Stream->WriteUSHORT(root_real_port);
	Stream->WriteBytes((BYTE*) data, sizeof(SLOT_USER_DATA) * 8);

	return Stream->GetLength();
}

inline DWORD WRITE_PT_ROOM_REQ_INFO_FAIL_U(BYTE *buffer, DWORD error_code)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

	Stream->WriteDWORD(error_code);

	return Stream->GetLength();
}

inline DWORD WRITE_PT_ROOM_LEAVE(BYTE *buffer)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);


	return Stream->GetLength();
}

inline DWORD WRITE_PT_ROOM_LEAVE_SUCC_U(BYTE *buffer)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);


	return Stream->GetLength();
}

inline DWORD WRITE_PT_ROOM_LEAVE_FAIL_U(BYTE *buffer, DWORD error_code)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

	Stream->WriteDWORD(error_code);

	return Stream->GetLength();
}

inline DWORD WRITE_PT_ROOM_LEAVE_M(BYTE *buffer, WCHAR *outuser, WCHAR *rootuser)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

	WCHAR _outuser[32] = {0,};
	_tcsncpy(_outuser, outuser, 32);
	Stream->WriteWCHARs(_outuser, 32);
	WCHAR _rootuser[32] = {0,};
	_tcsncpy(_rootuser, rootuser, 32);
	Stream->WriteWCHARs(_rootuser, 32);

	return Stream->GetLength();
}

inline DWORD WRITE_PT_ROOM_TEAM_CHANGE(BYTE *buffer, BOOL team)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

	Stream->WriteBOOL(team);

	return Stream->GetLength();
}

inline DWORD WRITE_PT_ROOM_TEAM_CHANGE_SUCC_U(BYTE *buffer, USHORT slot_index)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

	Stream->WriteUSHORT(slot_index);

	return Stream->GetLength();
}

inline DWORD WRITE_PT_ROOM_TEAM_CHANGE_FAIL_U(BYTE *buffer)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);


	return Stream->GetLength();
}

inline DWORD WRITE_PT_ROOM_TEAM_CHANGE_M(BYTE *buffer, WCHAR *user_id, WCHAR *nickname, USHORT slot_index)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

	WCHAR _user_id[32] = {0,};
	_tcsncpy(_user_id, user_id, 32);
	Stream->WriteWCHARs(_user_id, 32);
	WCHAR _nickname[32] = {0,};
	_tcsncpy(_nickname, nickname, 32);
	Stream->WriteWCHARs(_nickname, 32);
	Stream->WriteUSHORT(slot_index);

	return Stream->GetLength();
}

inline DWORD WRITE_PT_ROOM_READY(BYTE *buffer, BOOL ready)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

	Stream->WriteBOOL(ready);

	return Stream->GetLength();
}

inline DWORD WRITE_PT_ROOM_READY_SUCC_U(BYTE *buffer)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);


	return Stream->GetLength();
}

inline DWORD WRITE_PT_ROOM_READY_FAIL_U(BYTE *buffer, DWORD error_code)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

	Stream->WriteDWORD(error_code);

	return Stream->GetLength();
}

inline DWORD WRITE_PT_ROOM_READY_M(BYTE *buffer, DWORD oid, WCHAR *nickname, BOOL ready)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

	Stream->WriteDWORD(oid);
	WCHAR _nickname[32] = {0,};
	_tcsncpy(_nickname, nickname, 32);
	Stream->WriteWCHARs(_nickname, 32);
	Stream->WriteBOOL(ready);

	return Stream->GetLength();
}

inline DWORD WRITE_PT_ROOM_START(BYTE *buffer)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);


	return Stream->GetLength();
}

inline DWORD WRITE_PT_ROOM_START_SUCC_U(BYTE *buffer)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);


	return Stream->GetLength();
}

inline DWORD WRITE_PT_ROOM_START_FAIL_U(BYTE *buffer, DWORD error_code)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

	Stream->WriteDWORD(error_code);

	return Stream->GetLength();
}

inline DWORD WRITE_PT_ROOM_START_M(BYTE *buffer, USER_START_INFO *users)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

	Stream->WriteBytes((BYTE*) users, sizeof(USER_START_INFO) * 8);

	return Stream->GetLength();
}

inline DWORD WRITE_PT_GAME_LOAD_COMPLETE(BYTE *buffer)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);


	return Stream->GetLength();
}

inline DWORD WRITE_PT_GAME_LOAD_COMPLETE_SUCC_U(BYTE *buffer)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);


	return Stream->GetLength();
}

inline DWORD WRITE_PT_GAME_LOAD_COMPLETE_FAIL_U(BYTE *buffer, DWORD error_code)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

	Stream->WriteDWORD(error_code);

	return Stream->GetLength();
}

inline DWORD WRITE_PT_GAME_LOAD_COMPLETE_M(BYTE *buffer, WCHAR *user_id)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

	WCHAR _user_id[32] = {0,};
	_tcsncpy(_user_id, user_id, 32);
	Stream->WriteWCHARs(_user_id, 32);

	return Stream->GetLength();
}

inline DWORD WRITE_PT_GAME_ALL_LOAD_COMPLETE_M(BYTE *buffer)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);


	return Stream->GetLength();
}

inline DWORD WRITE_PT_GAME_INTRO_COMPLETE(BYTE *buffer)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);


	return Stream->GetLength();
}

inline DWORD WRITE_PT_GAME_INTRO_COMPLETE_SUCC_U(BYTE *buffer)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);


	return Stream->GetLength();
}

inline DWORD WRITE_PT_GAME_INTRO_COMPLETE_FAIL_U(BYTE *buffer, DWORD error_code)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

	Stream->WriteDWORD(error_code);

	return Stream->GetLength();
}

inline DWORD WRITE_PT_GAME_INTRO_COMPLETE_M(BYTE *buffer, DWORD_PTR session_id)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

	Stream->WriteDWORD_PTR(session_id);

	return Stream->GetLength();
}

inline DWORD WRITE_PT_GAME_ALL_INTRO_COMPLETE_M(BYTE *buffer)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);


	return Stream->GetLength();
}

inline DWORD WRITE_PT_GAME_START_M(BYTE *buffer, DWORD port)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

	Stream->WriteDWORD(port);

	return Stream->GetLength();
}

inline DWORD WRITE_PT_ROOT_GAME_START(BYTE *buffer, USHORT current_user_count, SLOT_USER_DATA *data, DWORD port)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

	Stream->WriteUSHORT(current_user_count);
	Stream->WriteBytes((BYTE*) data, sizeof(SLOT_USER_DATA) * 8);
	Stream->WriteDWORD(port);

	return Stream->GetLength();
}

inline DWORD WRITE_PT_GAME_END_M(BYTE *buffer)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);


	return Stream->GetLength();
}

inline DWORD WRITE_PT_C2U_KILL_USER_M(BYTE *buffer, DWORD useroid, DWORD targetid)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

	Stream->WriteDWORD(useroid);
	Stream->WriteDWORD(targetid);

	return Stream->GetLength();
}

inline DWORD WRITE_PT_U2C_REGEN_USER(BYTE *buffer)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);


	return Stream->GetLength();
}

inline DWORD WRITE_PT_C2U_REGEN_USER_SUCC_U(BYTE *buffer)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);


	return Stream->GetLength();
}

inline DWORD WRITE_PT_C2U_REGEN_USER_FAIL_U(BYTE *buffer)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);


	return Stream->GetLength();
}

inline DWORD WRITE_PT_C2U_RESULT_M(BYTE *buffer, USHORT winteam, RESULT_USER_DATA *data)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

	Stream->WriteUSHORT(winteam);
	Stream->WriteBytes((BYTE*) data, sizeof(RESULT_USER_DATA) * 8);

	return Stream->GetLength();
}

