// begging.c 叫化絕活
// Last Modified by winder on Mar. 10 2000

#include <ansi.h>;
inherit SKILL;

string type() { return "knowledge"; }
int learn_bonus() { return 30; }
int practice_bonus() { return 30; }
int success() { return 30; }
int power_point(object me) { return 1; }

int help(object me)
{
        write(HIC"\n叫化絕活："NOR"\n");
        write(@HELP

    丐幫乞討技能。丐幫弟子不能購買物品，乞討是獲得物品的一
種手段。乞討(beg) 不成功不會帶來對方的攻擊。

        學習要求：
                無
HELP
        );
        return 1;
}
