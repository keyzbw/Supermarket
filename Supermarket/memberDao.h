#pragma once
#include "member.h"
class memberDao
{
public:
	memberDao();
	~memberDao();
	member getMember(CString memberNo);
};

