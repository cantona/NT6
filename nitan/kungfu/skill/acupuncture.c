// acupuncture.c 鍼灸之術
// Last modified by winder 2003.9.2

#include <ansi.h>;
inherit SKILL;

void create() { seteuid(getuid()); }

string type() { return "knowledge"; }
int learn_bonus() { return 30; }
int practice_bonus() { return 30; }
int success() { return 30; }
int power_point(object me) { return 1; }


int valid_learn(object me)
{
        if ((int)me->query_skill("medicine", 1) < 50)
                return notify_fail("你的濟世之術造詣太淺，無法領會鍼灸之術。\n");
        if ((int)me->query_skill("medicine", 1) <
                (int)me->query_skill("acupuncture", 1))
                return notify_fail("你的濟世之術有限，無法掌握更深奧的鍼灸之術。\n");
        return 1;
}
int practice_skill(object me)
{
        return notify_fail("鍼灸之術只能靠學習來提高。\n");
}
int help(object me)
{
        write(HIC"\n鍼灸之術："NOR"\n");
        write(@HELP

    精通鍼灸之術，可以悠遊天下，治病救人。

        學習要求：
                鍼灸之術限制了對更高深境界的努力
HELP
        );
        return 1;
}