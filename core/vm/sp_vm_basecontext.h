/**
 * vim: set ts=4 :
 * ================================================================
 * SourcePawn (C)2004-2007 AlliedModders LLC.  All rights reserved.
 * ================================================================
 *
 * This file is not open source and may not be copied without explicit
 * written permission of AlliedModders LLC.  This file may not be redistributed 
 * in whole or significant part.
 * For information, see LICENSE.txt or http://www.sourcemod.net/license.php
 *
 * Version: $Id$
 */

#ifndef _INCLUDE_SOURCEPAWN_BASECONTEXT_H_
#define _INCLUDE_SOURCEPAWN_BASECONTEXT_H_

#include "sp_vm_api.h"
#include "sp_vm_function.h"

/**
 * :TODO: Make functions allocate as a lump instead of individual allocations!
 */

namespace SourcePawn
{
	class BaseContext : 
		public IPluginContext,
		public IPluginDebugInfo
	{
	public:
		BaseContext(sp_context_t *ctx);
		~BaseContext();
	public: //IPluginContext
		IVirtualMachine *GetVirtualMachine();
		sp_context_t *GetContext();
		bool IsDebugging();
		int SetDebugBreak(SPVM_DEBUGBREAK newpfn, SPVM_DEBUGBREAK *oldpfn);
		IPluginDebugInfo *GetDebugInfo();
		int HeapAlloc(unsigned int cells, cell_t *local_addr, cell_t **phys_addr);
		int HeapPop(cell_t local_addr);
		int HeapRelease(cell_t local_addr);
		int FindNativeByName(const char *name, uint32_t *index);
		int GetNativeByIndex(uint32_t index, sp_native_t **native);
		uint32_t GetNativesNum();
		int FindPublicByName(const char *name, uint32_t *index);
		int GetPublicByIndex(uint32_t index, sp_public_t **publicptr);
		uint32_t GetPublicsNum();
		int GetPubvarByIndex(uint32_t index, sp_pubvar_t **pubvar);
		int FindPubvarByName(const char *name, uint32_t *index);
		int GetPubvarAddrs(uint32_t index, cell_t *local_addr, cell_t **phys_addr);
		uint32_t GetPubVarsNum();
		int LocalToPhysAddr(cell_t local_addr, cell_t **phys_addr);
		int LocalToString(cell_t local_addr, char **addr);
		int StringToLocal(cell_t local_addr, size_t chars, const char *source);
		int StringToLocalUTF8(cell_t local_addr, size_t maxbytes, const char *source, size_t *wrtnbytes);
		int PushCell(cell_t value);
		int PushCellArray(cell_t *local_addr, cell_t **phys_addr, cell_t array[], unsigned int numcells);
		int PushString(cell_t *local_addr, char **phys_addr, const char *string);
		int PushCellsFromArray(cell_t array[], unsigned int numcells);
		int BindNatives(const sp_nativeinfo_t *natives, unsigned int num, int overwrite);
		int BindNative(const sp_nativeinfo_t *native);
		int BindNativeToAny(SPVM_NATIVE_FUNC native);
		int Execute(uint32_t code_addr, cell_t *result);
		cell_t ThrowNativeErrorEx(int error, const char *msg, ...);
		cell_t ThrowNativeError(const char *msg, ...);
		IPluginFunction *GetFunctionByName(const char *public_name);
		IPluginFunction *GetFunctionById(funcid_t func_id);
#if defined SOURCEMOD_BUILD
		SourceMod::IdentityToken_t *GetIdentity();
		void SetIdentity(SourceMod::IdentityToken_t *token);
#endif
	public: //IPluginDebugInfo
		int LookupFile(ucell_t addr, const char **filename);
		int LookupFunction(ucell_t addr, const char **name);
		int LookupLine(ucell_t addr, uint32_t *line);
	public:
		void SetContext(sp_context_t *_ctx);
	private:
		void SetErrorMessage(const char *msg, va_list ap);
		void FlushFunctionCache(bool remove);
	private:
		sp_context_t *ctx;
#if defined SOURCEMOD_BUILD
		SourceMod::IdentityToken_t *m_pToken;
#endif
		char m_MsgCache[1024];
		bool m_CustomMsg;
		bool m_InExec;
		unsigned int m_funcsnum;
		CFunction **m_priv_funcs;
		CFunction **m_pub_funcs;
	};
};

#endif //_INCLUDE_SOURCEPAWN_BASECONTEXT_H_
