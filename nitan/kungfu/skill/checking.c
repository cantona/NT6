// checking.c 道聽途説
// Last Modified by winder on Mar. 10 2000

#include <ansi.h>;
inherit SKILL;

string type() { return "knowledge"; }
int learn_bonus() { return 30; }
int practice_bonus() { return 30; }
int success() { return 30; }
int power_point() { return 1; }

int help(object me)
{
        write(HIC"\n道聽途説："NOR"\n");
        write(@HELP

    丐幫幫眾遍及大江南北，消息靈通，凡江湖上發生什麼事，往
往他們最先得知。身具此藝的丐幫幫眾，可以在江湖上打探(check)
別人的消息。

        學習要求：
                無
HELP
        );
        return 1;
}
