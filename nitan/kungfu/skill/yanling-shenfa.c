// yanling-shenfa.c 燕靈身法
// Last Modified by sir on 18.10.2001

#include <ansi.h>;
inherit SKILL;
string type() { return "martial"; }
string martialtype() { return "dodge"; }

string *dodge_msg = ({
        "$n輕輕巧巧地往後一躍，身輕如燕，一式"BLU"「單燕南飛」"NOR"，$N的招數頓時用盡。\n",
        "$n不退反進，身形颯然欺進，一式"BLU"「一葉障目」"NOR"，張開手掌往$N眼前一舞而過，$N視線被擋，手上招數頓時緩了一緩。\n",
        "$n雙袖輕拂，身形拔地而起，在空中一個空翻，"HIW"「雙燕分飛」"NOR"，躍到$N身後。\n",
        "$n左足上挑，右足力蹬，一式"HIC"「燕子出巢」"NOR"縱躍於幾丈開外。\n",
        "$n左一步，右一轉，斜刺裏一插，一式"GRN"「餘音繞樑」"NOR"，圍繞$N轉了半圈，避開了$N的出招。\n",
        "$n一聲輕嘯，一式"HIM"「走馬看花」"NOR"長身而起，側身讓過了$N這招。\n",
        "$n待$N攻近面門，後退幾步，突然身形後挫，回手一式"HIM"「燕子回頭」"NOR"，堪堪躲過$N這一招。\n",
        "$n一式"HIB"「燕南歸巢」"NOR"，一個側身飄然掠起，轉眼已在$N身後。\n",
});

int valid_enable(string usage) { return (usage=="dodge") || (usage=="move"); }
int valid_learn(object me)
{
        return 1;
}
int practice_skill(object me)
{
        if( query("qi", me)<30 || query("neili", me)<6 )
                return notify_fail("你的體力太差了，無法練習燕靈身法。\n");
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
int power_point(object me) { return 1.3; }

int help(object me)
{
        write(HIC"\n燕靈身法："NOR"\n");
        write(@HELP

    燕靈身法是慕容世家輕功身法，施展時有如飛燕掠空，輕靈迅
捷而得名。

        學習要求：
          神元功10級
HELP
        );
        return 1;
}
