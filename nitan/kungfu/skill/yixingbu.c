// yixingbu.c 意形步法

#include <ansi.h>;
inherit SKILL;
string type() { return "martial"; }
string martialtype() { return "dodge"; }

string *dodge_msg = ({
        BLU"$n漫不經心的向左邁出一步，剛好避過$N的凌厲攻勢。\n"NOR,
        MAG"可是$n不緊不慢往右走了一步，躲過了$N這一招。\n"NOR,
        MAG"但是$n身形飄忽，輕輕一縱，早已避開。\n"NOR,
        MAG"$n身隨意轉，倏地往一旁挪開了三尺，避過了這一招。\n"NOR,
        BLU"可是$n側身一讓，$N這一招撲了個空。\n"NOR,
        BLU"卻見$n足不點地，往旁竄開數尺，躲了開去。\n"NOR,
        BLU"$n身形微晃，有驚無險地避開了$N這一招。\n"NOR,
        MAG"$n看似無心地信手一拂，肩頭微側，堪堪避過了$N這一招。\n"NOR,
});

int valid_enable(string usage) { return (usage=="dodge") || (usage=="move"); }
int valid_learn(object me)
{
        return 1;
}
int practice_skill(object me)
{
        if( query("qi", me)<40 || query("neili", me)<8 )
                return notify_fail("你的體力太差了，不能練意形步法。\n");
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
        write(HIC"\n意形步法："NOR"\n");
        write(@HELP

    意形步法為神龍島獨門輕功身法。

        學習要求：
          毒龍大法10級
HELP
        );
        return 1;
}

