// chuanhua.c 穿花繞樹
// Last Modified by sir on 10.18.2001

#include <ansi.h>;
inherit SKILL;
string type() { return "martial"; }
string martialtype() { return "dodge"; }

string *dodge_msg = ({
        "$n一式"GRN"「斜燕歸林去」"NOR"，身體如雨燕投林般直滑出丈余。\n",
        "$n一式"MAG"「花蝶戲蕊心」"NOR"，忽然一彎腰，全身凌空而行，頓時閃過了$N的凌厲攻勢。\n",
        "$n一式"HIY"「黃雀啄葉露」"NOR"，足不動，手不抬，一轉眼間便繞到了$N的身後。\n",
        "$n一式"GRN"「青蜂弄花粉」"NOR"，一轉身間，四面八方飄動著無數個$n的身影，令$N手足無措。\n",
        "$n一式"HIW"「蜓尾點水舞」"NOR"，長袖一拂，全身化為一道白影，幽幽地從$N頭頂飄落。\n",
        "$n一式"MAG"「知了藏影蹤」"NOR"，身行倏的從$N的眼前飄過，長發一甩，瀟洒之極。\n",
});

int valid_enable(string usage) { return (usage=="dodge") || (usage=="move"); }
int valid_learn(object me) 
{              
       if( (int)me->query_skill("qingming-xuangong", 1) < 10 )
       return notify_fail("你的青冥玄功不夠精熟，無法領會穿花繞樹。\n");
       return 1;
}
int practice_skill(object me)
{
        if( query("qi", me)<30 || query("neili", me)<6 )
                return notify_fail("你的體力太差了，不能練穿花繞樹。\n");
        me->receive_damage("qi", 30);
        addn("neili", -6, me);
        return 1;
}
string query_dodge_msg(string limb)
{
        return dodge_msg[random(sizeof(dodge_msg))];
}
int learn_bonus() { return 15; }
int practice_bonus() { return 15; }
int success() { return 15; }
int power_point() { return 1.3; }

int help(object me)
{
        write(HIC"\n穿花繞樹："NOR"\n");
        write(@HELP

    青城派本門輕功。

        學習要求：
            青冥玄功 10 級                
HELP
        );
        return 1;
}
