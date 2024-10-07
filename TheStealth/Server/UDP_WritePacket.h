#pragma once
#include "UDP_Structure.h"

inline DWORD WRITE_PU_TUNNELING(BYTE *buffer, S_PU_TUNNELING &parameter)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

	Stream->WriteWCHARs(parameter.USERID, 16);
	Stream->WriteWCHARs(parameter.VIRTUAL_ADDRESS, 32);
	Stream->WriteUSHORT(parameter.VIRTUAL_PORT);

	return Stream->GetLength();
}

inline DWORD WRITE_PU_TUNNELING_SUCC_U(BYTE *buffer, S_PU_TUNNELING_SUCC_U &parameter)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

	Stream->WriteWCHARs(parameter.VIRTUAL_ADDRESS, 32);
	Stream->WriteUSHORT(parameter.VIRTUAL_PORT);
	Stream->WriteWCHARs(parameter.REAL_ADDRESS, 32);
	Stream->WriteUSHORT(parameter.REAL_PORT);

	return Stream->GetLength();
}

inline DWORD WRITE_PU_TUNNELING_FAIL_U(BYTE *buffer, S_PU_TUNNELING_FAIL_U &parameter)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);


	return Stream->GetLength();
}

inline DWORD WRITE_PU_U2C_MOVE_TO(BYTE *buffer, S_PU_U2C_MOVE_TO &parameter)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

	Stream->WriteDWORD(parameter.ROOM_ID);
	Stream->WriteDWORD(parameter.OID);
	Stream->WriteFloat(parameter.X);
	Stream->WriteFloat(parameter.Y);
	Stream->WriteFloat(parameter.Z);
	Stream->WriteFloat(parameter.DW);
	Stream->WriteFloat(parameter.DX);
	Stream->WriteFloat(parameter.DY);
	Stream->WriteFloat(parameter.DZ);
	Stream->WriteFloat(parameter.SPEED);
	Stream->WriteFloat(parameter.BOOSTTIME);
	Stream->WriteBOOL(parameter.ISFIRED);

	return Stream->GetLength();
}

inline DWORD WRITE_PU_H2C_MOVE_TO(BYTE *buffer, S_PU_H2C_MOVE_TO &parameter)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

	Stream->WriteWCHARs(parameter.USERID, 32);
	Stream->WriteDWORD(parameter.ROOM_ID);

	return Stream->GetLength();
}

inline DWORD WRITE_PU_C2U_MOVE_TO(BYTE *buffer, S_PU_C2U_MOVE_TO &parameter)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

	Stream->WriteBytes((BYTE*) parameter.USER, sizeof(USER_MOVE_TO_DATA) * 8);

	return Stream->GetLength();
}

inline DWORD WRITE_PU_U2C_DAMAGE(BYTE *buffer, S_PU_U2C_DAMAGE &parameter)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

	Stream->WriteDWORD(parameter.USERID);
	Stream->WriteDWORD(parameter.TARGETID);
	Stream->WriteFloat(parameter.DAMAGE);

	return Stream->GetLength();
}

inline DWORD WRITE_PU_TUNNELING(BYTE *buffer, WCHAR *userid, WCHAR *virtual_address, USHORT virtual_port)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

	WCHAR _userid[16] = {0,};
	_tcsncpy(_userid, userid, 16);
	Stream->WriteWCHARs(_userid, 16);
	WCHAR _virtual_address[32] = {0,};
	_tcsncpy(_virtual_address, virtual_address, 32);
	Stream->WriteWCHARs(_virtual_address, 32);
	Stream->WriteUSHORT(virtual_port);

	return Stream->GetLength();
}

inline DWORD WRITE_PU_TUNNELING_SUCC_U(BYTE *buffer, WCHAR *virtual_address, USHORT virtual_port, WCHAR *real_address, USHORT real_port)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

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

inline DWORD WRITE_PU_TUNNELING_FAIL_U(BYTE *buffer)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);


	return Stream->GetLength();
}

inline DWORD WRITE_PU_U2C_MOVE_TO(BYTE *buffer, DWORD room_id, DWORD oid, FLOAT x, FLOAT y, FLOAT z, FLOAT dw, FLOAT dx, FLOAT dy, FLOAT dz, FLOAT speed, FLOAT boosttime, BOOL isfired)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

	Stream->WriteDWORD(room_id);
	Stream->WriteDWORD(oid);
	Stream->WriteFloat(x);
	Stream->WriteFloat(y);
	Stream->WriteFloat(z);
	Stream->WriteFloat(dw);
	Stream->WriteFloat(dx);
	Stream->WriteFloat(dy);
	Stream->WriteFloat(dz);
	Stream->WriteFloat(speed);
	Stream->WriteFloat(boosttime);
	Stream->WriteBOOL(isfired);

	return Stream->GetLength();
}

inline DWORD WRITE_PU_H2C_MOVE_TO(BYTE *buffer, WCHAR *userid, DWORD room_id)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

	WCHAR _userid[32] = {0,};
	_tcsncpy(_userid, userid, 32);
	Stream->WriteWCHARs(_userid, 32);
	Stream->WriteDWORD(room_id);

	return Stream->GetLength();
}

inline DWORD WRITE_PU_C2U_MOVE_TO(BYTE *buffer, USER_MOVE_TO_DATA *user)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

	Stream->WriteBytes((BYTE*) user, sizeof(USER_MOVE_TO_DATA) * 8);

	return Stream->GetLength();
}

inline DWORD WRITE_PU_U2C_DAMAGE(BYTE *buffer, DWORD userid, DWORD targetid, FLOAT damage)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

	Stream->WriteDWORD(userid);
	Stream->WriteDWORD(targetid);
	Stream->WriteFloat(damage);

	return Stream->GetLength();
}

