// zhutian-bu.c 諸天化身步

#include <ansi.h>;
inherit SKILL;
string type() { return "martial"; }
string martialtype() { return "dodge"; }

string *dodge_msg = ({
        "只見$n一招"MAG"「天地鉤」"NOR"，身體騰空，雙足向上，筆直地縱起丈余，躲過了$N這一招。\n",
        "$n身隨意轉，一式"HIM"「鳳點頭」"NOR"頭部前挺，側身收腹，倏地往一旁挪開了三尺，避過了這一招。\n",
        "$n雙足抓地，身形微晃，一招"BLU"「鷹爪鬆」"NOR"有驚無險地避開了$N這一招。\n",
        "但是$n身形飄忽，一式"GRN"「風擺柳」"NOR"，輕輕一縱，早已避開。\n",
        "$n一個"HIB"「陰陽箭」"NOR"，向後縱出數丈之遠，避開了$N的凌厲攻勢，立即又欺近$N身旁。\n",
        "$n使出"HIW"「日月扣」"NOR"，雙手如鉤向一旁飄然縱出，輕輕著地。\n",
});

int valid_enable(string usage) { return (usage=="dodge") || (usage=="move"); }
int valid_learn(object me)
{
        return 1;
}

int practice_skill(object me)
{
        if( query("qi", me)<20 || query("neili", me)<4 )
                return notify_fail("你的體力太差了，不能練諸天化身步。\n");
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
        write(HIC"\n諸天化身步："NOR"\n");
        write(@HELP

    諸天化身步是峨嵋派本門輕功身法。

        學習要求：
          臨濟十二莊10級
HELP
        );
        return 1;
}
