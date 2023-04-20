pushd %~dp0
protoc.exe -I=./ --csharp_out=./ --cpp_out=./ ./Enum.proto
protoc.exe -I=./ --csharp_out=./ --cpp_out=./ ./Struct.proto
protoc.exe -I=./ --csharp_out=./ --cpp_out=./ ./Protocol.proto

GenPackets.exe --path=./Protocol.proto --output=ClientPacketHandler --recv=C_ --send=S_
GenPackets.exe --path=./Protocol.proto --output=ServerPacketHandler --recv=S_ --send=C_

IF ERRORLEVEL 1 PAUSE

XCOPY /Y Enum.pb.h "../../../GameServer"
XCOPY /Y Enum.pb.cc "../../../GameServer"
XCOPY /Y Struct.pb.h "../../../GameServer"
XCOPY /Y Struct.pb.cc "../../../GameServer"
XCOPY /Y Protocol.pb.h "../../../GameServer"
XCOPY /Y Protocol.pb.cc "../../../GameServer"
XCOPY /Y ClientPacketHandler.h "../../../GameServer"

XCOPY /Y Enum.pb.h "../../../DummyClient"
XCOPY /Y Enum.pb.cc "../../../DummyClient"
XCOPY /Y Struct.pb.h "../../../DummyClient"
XCOPY /Y Struct.pb.cc "../../../DummyClient"
XCOPY /Y Protocol.pb.h "../../../DummyClient"
XCOPY /Y Protocol.pb.cc "../../../DummyClient"
XCOPY /Y ServerPacketHandler.h "../../../DummyClient"

XCOPY /Y Enum.cs "../../../../Client/Assets/Scripts/Packet"
XCOPY /Y Struct.cs "../../../../Client/Assets/Scripts/Packet"
XCOPY /Y Protocol.cs "../../../../Client/Assets/Scripts/Packet"
XCOPY /Y ClientPacketHandler.cs "../../../../Client/Assets/Scripts/Packet"
XCOPY /Y ClientPacketManager.cs "../../../../Client/Assets/Scripts/Packet"

DEL /Q /F *.pb.h
DEL /Q /F *.pb.cc
DEL /Q /F *.h
DEL /Q /F *.cs

PAUSE