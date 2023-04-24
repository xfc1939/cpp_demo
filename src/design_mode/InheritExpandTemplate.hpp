#ifndef __INHERIT_EXPAND_TEMPLATE_H__
#define __INHERIT_EXPAND_TEMPLATE_H__

#include "Log.h"

template<int...>
struct IndexSeq{};

template<int N, int... Indexes>
struct MakeIndexes : MakeIndexes<N - 1, N - 1, Indexes...>{};

template<int... Indexes>
struct MakeIndexes<0, Indexes...>
{
    typedef IndexSeq<Indexes...> type;
};

void InHeritExpandTemplate_Test()
{
    using T = MakeIndexes<3>::type;
    LOG_DEBUG() << typeid(T).name();

}
#endif