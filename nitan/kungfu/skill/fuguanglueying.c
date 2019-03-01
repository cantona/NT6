// fuguanglueying.c  浮光掠影
// Last Modified by sir on 10.18.2001

#include <ansi.h>;
inherit SKILL;
string type() { return "martial"; }
string martialtype() { return "dodge"; }

string *dodge_msg = ({
        "只見$n一招"BLU"「似來還往」"NOR"，雙腳一前一後，似進又腿，在$n一愣間躲過了攻擊。\n",
        "但是$n使出"CYN"「蜻蜓點水」"NOR"，腳尖站地，身形東倒西歪間，破天沖起。\n",
        "$n一招"HIY"「飛黃騰達」"NOR"，身隨意轉，剎那間在原地轉了七八十圈，突然往地上一坐，\n原是轉暈了，卻使$N落了空。\n",
        "可是$n一個"HIW"「白駒過隙」"NOR"，身形微側，提氣直縱，躲過$N攻擊。\n",
        "卻見$n使出"HIW"「浮光掠影」"NOR"，在原地留下一個幻象，真身躲到了一邊。\n",
        "$n身形一頓，"HIB"「逝者如斯」"NOR"，身形平平掠出，在空中留下一道弧形。\n"
});

int valid_enable(string usage) { return (usage=="dodge") || (usage=="move"); }
int valid_learn(object me) 
{ 
        if( (int)me->query_skill("hanbing-zhenqi", 1) < 10 )
        return notify_fail("你的寒冰真氣不夠精熟，無法領會浮光掠影。\n");
        return 1;
}
int practice_skill(object me)
{
        if( query("qi", me)<30 || query("neili", me)<6 )
                return notify_fail("你的體力太差了，無法能練習浮光掠影。\n");
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
        write(HIC"\n浮光掠影："NOR"\n");
        write(@HELP

    嵩山派輕功身法。

        學習要求：
            寒冰真氣10級           
HELP
        );
        return 1;
}
