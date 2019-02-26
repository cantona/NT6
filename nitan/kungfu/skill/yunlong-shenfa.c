// yunlong-shenfa 雲龍身法
// Last Modified by sir on 10.18.2001

#include <ansi.h>;
inherit SKILL;
string type() { return "martial"; }
string martialtype() { return "dodge"; }

string *dodge_msg = ({
        "$n一式"HIY"「龍騰虎躍」"NOR"，身行一轉，猛的跳向一旁,躲過了$N的功勢。\n",
        "$n一式"HIY"「沙場點兵」"NOR"，雙臂置於身後，不急不緩，昂首從$N眼前跨過。\n",
        "$n一式"HIG"「風雨同舟」"NOR"，不退反進，一下子繞到了$N的身後。\n",
        "$n一式"HIG"「養精蓄鋭」"NOR"，緩緩的向後一退，輕鬆讓過了$N的凌厲攻勢。\n",
        "$n一式"GRN"「無心插柳」"NOR"，左手一揚，身行一晃，便向右飄出丈遠。\n",
        "$n一式"MAG"「蒼鷹搏兔」"NOR"，身體如一隻蒼鷹，呼的一聲從$N的眼前飛過。\n",
        "$n一式"HIY"「九龍在天」"NOR"，忽的拔地而起，在半空中一轉，已落到幾丈遠的地方。\n",
        "$n一式"HIC"「瀑落九天」"NOR"，全身化為一道白影，忽的一個空翻，從左邊飄到右邊。\n",
        "$n一式"HIC"「幻眼雲煙」"NOR"，身形陡地變得飄忽不定，令$N無法看清。\n",
        "$n一式"HIW"「九天攬月」"NOR"，宛若一條矯矢蒼龍，倏的拔地而起，令$N不敢仰視。\n",
});

int valid_enable(string usage) { return (usage=="dodge") || (usage=="move"); }
int valid_learn(object me)
{
        return 1;
}
int practice_skill(object me)
{
        if( query("qi", me)<40 || query("neili", me)<8 )
                return notify_fail("你的體力太差了，不能練雲龍身法。\n");
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
int power_point() { return 1.4; }

int help(object me)
{
        write(HIC"\n雲龍身法："NOR"\n");
        write(@HELP

    雲龍身法為天地會雲龍門本門輕功身法。

        學習要求：
           雲龍神功10級
HELP
        );
        return 1;
}
