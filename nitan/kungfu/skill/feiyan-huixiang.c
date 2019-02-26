// feiyan-huixiang.c 飛燕迴翔

#include <ansi.h>;
inherit SKILL;
string type() { return "martial"; }
string martialtype() { return "dodge"; }

string *dodge_msg = ({
        "但是$n身形飄忽，輕輕一縱，一招"GRN"「乳燕投林」"NOR"，舉重若輕的避開這一擊。\n",
        "$n身隨意轉，一式"HIW"「雪花飛舞」"NOR"，倏地往一旁飄開數尺，避過了這一招。\n",
        "可是$n側身一讓，使出"HIG"「柳絮輕飄」"NOR"，$N這一招撲了個空。\n",
        "卻見$n足不點地，一招"WHT"「騰雲駕霧」"NOR"，身形滴溜溜一轉，往旁閃開數尺，躲了開去。\n",
        "$n左腳一點右腳背，身形往上一拔，一招"HIC"「一鶴沖天」"NOR"，輕輕巧巧地避開了這一招。\n",
});

int valid_enable(string usage) { return (usage=="dodge") || (usage=="move"); }
int valid_learn(object me)
{
        return 1;
}
int practice_skill(object me)
{
        if( query("qi", me)<20 || query("neili", me)<4 )
                return notify_fail("你的體力太差了，不能練飛燕迴翔。\n");
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
        write(HIC"\n飛燕迴翔："NOR"\n");
        write(@HELP

    飛燕迴翔為華山派本門輕功。

        學習要求：
         紫霞神功10級
HELP
        );
        return 1;
}
