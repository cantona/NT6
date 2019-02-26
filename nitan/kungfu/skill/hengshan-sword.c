// hengshan-sword.c 衡山劍法
// Last Modified by sir 10.22.2001
// Modified by Java Sep.1998
//重進攻輕防守

#include <ansi.h>
inherit SKILL;
string type() { return "martial"; }
string martialtype() { return "skill"; }

mapping *action = ({
([      "skill_name" :"衡山雲霧",
        "action":  "$N右手$w慢慢指出，突然間在空中一顫，發出嗡嗡之聲，跟着便是嗡嗡兩劍，一招"HIW"「衡山雲霧」"NOR"手中$w劍光暴長，向$n的$l刺去",
        "lvl" : 0
]),
([      "skill_name" :"百變千幻",
        "action":  "$N一招"HIC"「百變千幻」"NOR"手中$w如鬼如魅，竟然已繞到了$n背後，$n急忙轉身，耳邊只聽得嗡嗡兩聲",
        "lvl" : 10
]),
([      "skill_name":    "泉鳴芙蓉",
        "action":  "$N不理會對方攻勢來路，手中$w刷的一劍"MAG"「泉鳴芙蓉」"NOR"，向$n小腹刺去",
        "lvl" : 20
]),
([      "skill_name":    "鶴翔紫蓋",
        "action":  "$N不理會對方攻勢來路，手中$w刷的一劍"HIM"「鶴翔紫蓋」"NOR"，向$n額頭刺去",
        "lvl" : 30
]),
([      "skill_name":    "石廩書聲",
        "action":  "$N手中$w倏地刺出，劍勢穿插迂迴，如夢如幻，正是一招" HIG"「石廩書聲」"NOR"，向$n$l刺去",
        "lvl" : 40
]),
([      "skill_name":    "天柱雲氣",
        "action":  "$N手中$w倏地刺出，極盡詭奇之能事，動向無定，不可捉摸。正是一招"RED"「天柱雲氣」"NOR"，指向$n$l",
        "lvl" : 50
]),
([      "skill_name":    "雁回祝融",
        "action" : "$N飛身躍起，"HIR"『雁回祝融』"NOR"！，$w發出一聲龍吟從半空中灑向$n的$l",
        "lvl" : 60
]),
});

int valid_enable(string usage) { return usage=="sword" || usage=="parry"; }
int valid_learn(object me)
{
        object ob;

        if( query("max_neili", me)<200 )
                return notify_fail("你的內力不夠，沒有辦法練衡山劍法。\n");

        if ((int)me->query_skill("force") < 40)
                return notify_fail("你的內功火候不夠，沒有辦法練衡山劍法。\n");

        if( !(ob=query_temp("weapon", me) )
         || query("skill_type", ob) != "sword" )
                return notify_fail("你必須先找一把劍才能練劍法。\n");

        return 1;
}
int practice_skill(object me)
{
        object weapon;

        if( !objectp(weapon=query_temp("weapon", me) )
         || query("skill_type", weapon) != "sword" )
                return notify_fail("你使用的武器不對。\n");
        if( query("qi", me)<40 || query("neili", me)<30 )
                return notify_fail("你的內力或氣不夠，沒有辦法練習衡山劍法。\n");
        me->receive_damage("qi", 35);
        addn("neili", -20, me);
        return 1;
}

string query_skill_name(int level)
{
        int i;
        for(i = sizeof(action); i > 0; i--)
                if(level >= action[i-1]["lvl"])
                        return action[i-1]["skill_name"];
}
mapping query_action(object me, object weapon)
{
/* d_e=dodge_effect p_e=parry_effect f_e=force_effect m_e=damage_effect */
        int d_e1 = 5;
        int d_e2 = 30;
        int p_e1 = -20;
        int p_e2 = -5;
        int f_e1 = 100;
        int f_e2 = 150;
        int m_e1 = 110;
        int m_e2 = 200;
        int i, lvl, seq, ttl = sizeof(action);

        lvl = (int) me->query_skill("hengshan-sword", 1);
        for(i = ttl; i > 0; i--)
                if(lvl > action[i-1]["lvl"])
                {
                        seq = i; /* 獲得招數序號上限 */
                        break;
                }
        seq = random(seq);       /* 選擇出手招數序號 */
        return ([
                "action"      : action[seq]["action"],
                "dodge"       : d_e1 + (d_e2 - d_e1) * seq / ttl,
                "parry"       : p_e1 + (p_e2 - p_e1) * seq / ttl,
                "force"       : f_e1 + (f_e2 - f_e1) * seq / ttl,
                "damage"      : m_e1 + (m_e2 - m_e1) * seq / ttl,
                "damage_type" : random(2) ? "割傷" : "刺傷",
        ]);
}
int learn_bonus() { return 20; }
int practice_bonus() { return 20; }
int success() { return 10; }
int power_point(object me) { return 1.0; }

int valid_effect(object me, object weapon, string name, int skill)
{
}

string perform_action_file(string action)
{
        return __DIR__"hengshan-sword/" + action;
}
int help(object me)
{
        write(HIC"\n衡山劍法："NOR"\n");
        write(@HELP

    衡山劍法為衡山武功。

        學習要求：
                回雁心法
                內力50
HELP
        );
        return 1;
}
