#pragma once
#include "UDP_Structure.h"

inline VOID READ_PU_TUNNELING(BYTE *buffer, S_PU_TUNNELING &parameter)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

	Stream->ReadWCHARs(parameter.USERID, 16);
	Stream->ReadWCHARs(parameter.VIRTUAL_ADDRESS, 32);
	Stream->ReadUSHORT(&parameter.VIRTUAL_PORT);
}

inline VOID READ_PU_TUNNELING_SUCC_U(BYTE *buffer, S_PU_TUNNELING_SUCC_U &parameter)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

	Stream->ReadWCHARs(parameter.VIRTUAL_ADDRESS, 32);
	Stream->ReadUSHORT(&parameter.VIRTUAL_PORT);
	Stream->ReadWCHARs(parameter.REAL_ADDRESS, 32);
	Stream->ReadUSHORT(&parameter.REAL_PORT);
}

inline VOID READ_PU_TUNNELING_FAIL_U(BYTE *buffer, S_PU_TUNNELING_FAIL_U &parameter)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

}

inline VOID READ_PU_U2C_MOVE_TO(BYTE *buffer, S_PU_U2C_MOVE_TO &parameter)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

	Stream->ReadDWORD(&parameter.ROOM_ID);
	Stream->ReadDWORD(&parameter.OID);
	Stream->ReadFloat(&parameter.X);
	Stream->ReadFloat(&parameter.Y);
	Stream->ReadFloat(&parameter.Z);
	Stream->ReadFloat(&parameter.DW);
	Stream->ReadFloat(&parameter.DX);
	Stream->ReadFloat(&parameter.DY);
	Stream->ReadFloat(&parameter.DZ);
	Stream->ReadFloat(&parameter.SPEED);
	Stream->ReadFloat(&parameter.BOOSTTIME);
	Stream->ReadBOOL(&parameter.ISFIRED);
}

inline VOID READ_PU_H2C_MOVE_TO(BYTE *buffer, S_PU_H2C_MOVE_TO &parameter)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

	Stream->ReadWCHARs(parameter.USERID, 32);
	Stream->ReadDWORD(&parameter.ROOM_ID);
}

inline VOID READ_PU_C2U_MOVE_TO(BYTE *buffer, S_PU_C2U_MOVE_TO &parameter)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

	Stream->ReadBytes((BYTE*) parameter.USER, sizeof(USER_MOVE_TO_DATA) * 8);
}

inline VOID READ_PU_U2C_DAMAGE(BYTE *buffer, S_PU_U2C_DAMAGE &parameter)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

	Stream->ReadDWORD(&parameter.USERID);
	Stream->ReadDWORD(&parameter.TARGETID);
	Stream->ReadFloat(&parameter.DAMAGE);
}

