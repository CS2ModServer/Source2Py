// Include this _once_ in a source file to define Source2Py module

#pragma once

#include "PyAPI.h"
#include "PyInclude.h"

class CPlayerSlot;
#include <igameevents.h>

PYBIND11_EMBEDDED_MODULE(Source2Py, m) {
	using namespace Source2Py;

	m.def("ServerPrint", &PyAPI::ConPrint);
	m.def("ClientPrint", &PyAPI::ClientConPrint);

	m.def("ServerCommand", &PyAPI::ServerCommand);
	m.def("ClientCommand", &PyAPI::ClientCommand);

	m.def("SetTimescale", &PyAPI::SetTimescale);

	py::class_<GameEventKeySymbol_t>(m, "GameEventKeySymbol_t")
		.def(py::init<const char*>())
		;

	py::class_<CEntityInstance>(m, "CEntityInstance")
		//.def(py::init<>()) // Doesn't have a constructor?
		.def("GetRefEHandle",  &CEntityInstance::GetRefEHandle)
		.def("GetClassname",   &CEntityInstance::GetClassname)
		.def("GetEntityIndex", &CEntityInstance::GetEntityIndex)
		;

	py::class_<CEntityIndex>(m, "CEntityIndex")
		.def(py::init<int>()) 
		.def("Get",				&CEntityIndex::Get)
		.def(py::self == py::self)
		.def(py::self != py::self)
		;

	py::class_<CEntityHandle>(m, "CEntityHandle")
		.def(py::init<>())
		.def("Init",			&CEntityHandle::Init)
		.def("Term",			&CEntityHandle::Term)
		.def("IsValid",			&CEntityHandle::IsValid)
		.def("GetEntryIndex",	&CEntityHandle::GetEntryIndex)
		.def("GetSerialNumber", &CEntityHandle::GetSerialNumber)
		.def(py::self != py::self)
		.def(py::self == py::self)
		.def(py::self <  py::self)

		.def("Set", &CEntityHandle::Set)
		//.def("=", &CEntityHandle::operator=) //just use Set

		// Use this to dereference the handle.
		// Note: this is implemented in game code (ehandle.h)
		//.def("Get", &CEntityHandle::Get)
		;

	/*
	* Needed for IGameEvent if you want 
	* virtual CPlayerSlot GetPlayerSlot( const GameEventKeySymbol_t &keySymbol ) = 0;
	* virtual void SetPlayer( const GameEventKeySymbol_t &keySymbol, CPlayerSlot value ) = 0;
	*/ /*
	py::class_<CPlayerSlot>(m, "CPlayerSlot")
		.def(py::init<int>()) //constructor
		.def("Get", &CPlayerSlot::Get)        // int () const
		.def(py::self == py::self)
		.def(py::self != py::self)
		; 
	*/

	py::class_<IGameEvent>(m, "GameEvent")
		//*
		.def("GetName", &IGameEvent::GetName)
		.def("GetID", &IGameEvent::GetID)
		.def("GetBool", &IGameEvent::GetBool)
		.def("GetInt", &IGameEvent::GetInt)
		.def("GetFloat", &IGameEvent::GetFloat)
		.def("GetString", &IGameEvent::GetString)
		.def("GetDataKeys", &IGameEvent::GetDataKeys)
		
		//**
		.def("IsReliable", &IGameEvent::IsReliable)
		.def("IsLocal", &IGameEvent::IsLocal)
		.def("IsEmpty", &IGameEvent::IsEmpty)
		.def("GetUint64", &IGameEvent::GetUint64)
		.def("GetPtr", &IGameEvent::GetPtr)
		
		//***
		.def("GetEHandle", &IGameEvent::GetEHandle)
		.def("GetEntity", &IGameEvent::GetEntity)
		.def("GetEntityIndex", &IGameEvent::GetEntityIndex)
		//.def("GetPlayerSlot", &IGameEvent::GetPlayerSlot) //implement py::class_<CPlayerSlot> first
		.def("GetPlayerController", &IGameEvent::GetPlayerController)
		
		//****
		.def("GetPlayerPawn", &IGameEvent::GetPlayerPawn)
		.def("GetPawnEHandle", &IGameEvent::GetPawnEHandle)
		.def("GetPawnEntityIndex", &IGameEvent::GetPawnEntityIndex)
		.def("SetBool", &IGameEvent::SetBool)
		.def("SetInt", &IGameEvent::SetInt)
		
		//*****
		.def("SetUint64", &IGameEvent::SetUint64)
		.def("SetFloat", &IGameEvent::SetFloat)
		.def("SetString", &IGameEvent::SetString)
		.def("SetPtr", &IGameEvent::SetPtr)
		//.def("SetEntity", &IGameEvent::SetEntity) //figure out overloading
		
		//******
		//.def("SetPlayer", &IGameEvent::SetPlayer) //figure out overloading
		.def("SetPlayerRaw", &IGameEvent::SetPlayerRaw)
		.def("HasKey", &IGameEvent::HasKey)
		//.def("unk001", &IGameEvent::unk001) //virtual void* unk001() = 0; //Something script vm related
		;
}