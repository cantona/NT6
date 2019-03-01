// kunlun-shenfa.c (kunlun) 昆侖身法

#include <ansi.h>;
inherit SKILL;
string type() { return "martial"; }
string martialtype() { return "dodge"; }

string *dodge_msg = ({
"$n一式"HIC"「雁落平沙」"NOR"，變招奇速，右足向前踢出，身子已然騰起，輕輕巧巧地落在一旁。\n",
"$n一式"HIY"「玉龍飛起」"NOR"，縱身高躍，半空中一折一轉，已飄身在數丈之外。\n",
"$n一式"HIY"「夏日消融」"NOR"，兩足足跟不動，足尖左磨，身子隨之右轉，卸開了$N這一招。\n",
"$n一式"YEL"「枯鬆倒掛」"NOR"，只見$n身子後仰，雙掌往地下一撐，身子借勢倒射而出，$N便已打$n不著。\n",
"$n一式"HIW"「晴雪飛灘」"NOR"，縱高伏低，東奔西閃，身形飄忽不定，$N手無足措，只得回招自守。\n",
"$n一式"HIW"「冰絲帶雨」"NOR"，突然反手一招，竟然是兩敗俱傷的打法，趁$N手忙腳亂安全脫身。\n",
"$n一式"HIW"「寒江釣雪」"NOR"，不招不架，只微微一側身，$N猶如暴風驟雨般的進攻便即落空。\n",
"$n一式"HIY"「魚龍潛躍」"NOR"，陡然間身形拔起，直沖雲霄，直如鷹隼，幾個盤旋，飄飄盪盪落在數丈之外。\n",
});

int valid_enable(string usage) { return usage=="dodge" || usage=="move"; }
int valid_learn(object me)
{
        int ng, nl, nk;
        ng = (int)me->query_skill("goplaying", 1);
        nl = (int)me->query_skill("luteplaying", 1);
        nk = (int)me->query_skill("kunlun-shenfa", 1);

        if( query("family/master_name", me) != "何足道" )
        {
                if ( nl < nk || ng < nk  )
                return notify_fail("琴棋技藝當與武功並重，不然你無法領會更高深的昆侖身法。\n");
        }

        if( (int)me->query_skill("xuantian-wuji", 1) < 10 )
        return notify_fail("你的玄天無極功不夠精熟，無法領會昆侖身法。\n");
        return 1;
}
int practice_skill(object me)
{
        if( query("qi", me)<40 || query("neili", me)<6 )
                return notify_fail("你的體力太差了，不能練昆侖身法。\n");
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
int power_point(object me) { return 1.4; }

int help(object me)
{
        write(HIC"\n昆侖身法："NOR"\n");
        write(@HELP

    昆侖身法為昆侖高級輕功。

        學習要求：
                相當的琴棋技藝的造詣
                何足道的嫡傳弟子
HELP
        );
        return 1;
}
