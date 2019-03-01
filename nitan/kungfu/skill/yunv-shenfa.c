// yunv-shenfa.c 玉女身法
// Last Modified by sir on 10.18.2001

#include <ansi.h>;
inherit SKILL;
string type() { return "martial"; }
string martialtype() { return "dodge"; }

string *dodge_msg = ({
        "但是$n身形一轉，使出"HIW"「麝熏微度」"NOR"，驀地不見，避開了這一招。\n",
        "$n一招"HIW"「西施浣紗」"NOR"，身隨意轉，倏地往一旁挪開了三尺。\n",
        "$n身形飄忽，瞻之在前，忽焉在後，卻是"HIW"「走馬蘭台」"NOR"的身法。\n",
        "$n使出"HIW"「洛河清波」"NOR"，猶如在水面滑行一般，身形晃了開去。\n",
        "可是$n的身影飄飄渺渺，竟絲毫不著力，是一式"HIW"「蓬山萬重」"NOR"的身法。\n",
});

int valid_enable(string usage) { return (usage=="dodge") || (usage=="move"); }
int valid_learn(object me)
{
        return 1;
}

int practice_skill(object me)
{
        if( query("qi", me)<40 || query("neili", me)<8 )
                return notify_fail("你的體力太差了，不能練玉女身法。\n");
        me->receive_damage("qi", 40);
        addn("neili", -8, me);
        return 1;
}

string query_dodge_msg(string limb)
{
        return dodge_msg[random(sizeof(dodge_msg))];
}

int learn_bonus() { return 10; }
int practice_bonus() { return 10; }
int success() { return 10; }
int power_point(object me) { return 1.4; }

int help(object me)
{
        write(HIC"\n玉女身法："NOR"\n");
        write(@HELP

    古墓派輕功妙絕天下，飄逸靈動、變化萬方，于丈許方圓之內
更是趨退若神，當世無比。

        學習要求：
          玉女心法10級
HELP
        );
        return 1;
}
