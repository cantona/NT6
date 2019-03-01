// Last Modified by sir on 10.18.2001
// snowstep.c 梅雪飄香步

#include <ansi.h>
inherit SKILL;
string type() { return "martial"; }
string martialtype() { return "dodge"; }

string *order = ({""HIY"", ""HIG"", ""RED"", ""MAG"", ""YEL"", ""HIC"", ""HIW"", ""HIR"",""HIB"", ""CYN"",""WHT"",""HIM"",""BLU""});

string *dodge_msg = ({
        "但是$n輕笑一聲，回身高撥而起，一式"+(order[random(13)])+"「紅梅飄雪」"NOR"，輕輕閃過了這招。\n",
        "$n隨意轉身，一招"+(order[random(13)]) +"「檀板金樽」"NOR"，如舞樂般飄身而上，避過了這招。\n",
        "只見$n身形一旋，撥身而起，使出"+(order[random(13)]) +"「梅月黃昏」"NOR"，整個人都失去了蹤影，令$N撲了個空。\n",
        "卻見$n伸手往地上遙遙一拍，一式"+(order[random(13)]) +"「梅飄九宵」"NOR"，如柳絮般輕輕飄起，躲過了這招。\n",
        "$n長笑一聲，一式"+(order[random(13)]) +"「寒梅傲雪」"NOR"，長身而起，一時四面八方都是$n的影子，虛虛實實，不知哪個才是真的。\n",
});

int valid_enable(string usage) { return (usage=="dodge") || (usage=="move"); }
int valid_learn(object me)
{              
        if( (int)me->query_skill("bingxue-xinfa", 1) < 10 )
                return notify_fail("你的冰雪心法不夠精熟，無法領會梅雪飄香步。\n");
        return 1;
}
int practice_skill(object me)
{
        if( query("qi", me)<20 || query("neili", me)<4 )
                return notify_fail("你的體力太差了，不能練梅雪飄香步。\n");
        me->receive_damage("qi", 20);
        addn("neili", -4, me);
        return 1;
}
string query_dodge_msg(string limb)
{
        return dodge_msg[random(sizeof(dodge_msg))];
}

int learn_bonus() { return 20; }
int practice_bonus() { return 20; }
int success() { return 20; }
int power_point(object me) { return 1.2; }

int help(object me)
{
        write(HIC"\n梅雪飄香步："NOR"\n");
        write(@HELP

    梅雪飄香步是凌霄派本門輕功身法。

        學習要求：
          冰雪心法10級
HELP
        );
        return 1;
}