#pragma once

#include "CompatVtable.h"

template <typename Intf>
class CompatWeakPtr
{
public:
	CompatWeakPtr(Intf* intf = nullptr) : m_intf(intf)
	{
	}

	Intf& operator*() const
	{
		return *m_intf;
	}

	const Vtable<Intf>* operator->() const
	{
		return &CompatVtableBase<Intf>::getOrigVtable(*m_intf);
	}

	operator Intf*() const
	{
		return m_intf;
	}

	Intf* get() const
	{
		return m_intf;
	}

	Intf* const& getRef() const
	{
		return m_intf;
	}

	Intf*& getRef()
	{
		return m_intf;
	}

	void release()
	{
		if (m_intf)
		{
			m_intf->lpVtbl->Release(m_intf);
			m_intf = nullptr;
		}
	}

protected:
	Intf* m_intf;
};