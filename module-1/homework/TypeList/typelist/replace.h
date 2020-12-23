#pragma once

#include "typelist.h"

template<typename TList, typename OldType, typename NewType> 
struct Replace;

template<typename Head, typename Tail, typename OldType, typename NewType>
struct Replace<TypeList<Head,Tail>,OldType,NewType>{
    using NewTypeList = TypeList<Head,typename Replace<Tail,OldType,NewType>::NewTypeList>;
};

template<typename OldType, typename Tail, typename NewType>
struct Replace<TypeList<OldType,Tail>,OldType,NewType>{
    using NewTypeList = TypeList<NewType,typename Replace<Tail,OldType,NewType>::NewTypeList>;

};

template<typename OldType, typename NewType>
struct Replace<NullType,OldType,NewType>{
    using NewTypeList = NullType;
};