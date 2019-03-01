// sword.c 基本劍法
// Last Modified by winder on Mar. 10 2000

#include <ansi.h>;
inherit SKILL;

string type() { return "martial"; }
string martialtype() { return "skill"; }
int learn_bonus() { return 30; }
int practice_bonus() { return 30; }
int success() { return 30; }
int power_point(object me) { return 1; }

int help(object me)
{
        write(HIC"\n基本劍法："NOR"\n");
        write(@HELP

    劍類武技的基本功。
    劍，號稱「百兵之君」。劍訣雲：「劍是青龍劍走劍要平善，
氣要隨劍行，兩眼顧劍尖，氣沉兩足穩，身法需自然，劍行如飛燕，
劍落如停風，劍收如花絮，劍刺如鋼釘。」

        學習要求：
                無
HELP
        );
        return 1;
}
