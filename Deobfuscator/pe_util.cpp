#include "stdafx.h"
#include "pe.h"

unsigned int PEUtil::getVirtAddrBeforeRelocate(const unsigned int vaddr,
	const unsigned int actual_oep, PEFormat pe_fmt)
{
	unsigned int actual_image_base
		= actual_oep - pe_fmt.nt_headers.OptionalHeader.AddressOfEntryPoint;

	return vaddr > actual_image_base ? vaddr - actual_image_base : vaddr;
}