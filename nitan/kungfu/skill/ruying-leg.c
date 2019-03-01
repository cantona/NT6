// Last Modified by winder on May. 29 2001
// ruying-leg.c 如影隨形腿 不能互備 取自佛經中“六和敬”。

#include <ansi.h>;
inherit SKILL;
string type() { return "martial"; }
string martialtype() { return "skill"; }

mapping *action = ({
([        "action" : "$N縱身向前，忽然凌空伸出左腿，一式"HIC"「見和同解」"NOR"，卷起飛砂直踢$n的$l",
        "lvl"   : 0,
        "skill_name" : "見和同解"
]),
([        "action" : "$N身形一閃，雙足一點躍如空中，一式"HIM"「戒和同修」"NOR"，在半空連踢七腳，直奔$n$l",
        "lvl"   : 10,
        "skill_name" : "戒和同修"
]),
([        "action" : "$N身體前傾，左腳畫圓，凌空而起，右腿順勢使出一式"HIW"「身和同住」"NOR"，橫掃$n$l",
        "lvl"   : 30,
        "skill_name" : "身和同住"
]),
([        "action" : "$N一言不發，左足倏地彈出，連環三腿，分踢$n的頭，胸，腹，正是一式"HIB"「口和無凈」"NOR"",
        "lvl"   : 60,
        "skill_name" : "口和無凈"
]),
([        "action" : "$N左足獨立，身體旋轉，右腿隨身形反轉橫掃，一招"HIR"「意和同悅」"NOR"，拉起勁風掃向$n$l",
        "lvl"   : 100,
        "skill_name" : "意和同悅"
]),                                                                                                
([        "action" : "$N躍起在半空，雙足帶起無數勁風，一式"HIW"「利和同均」"NOR"，全身旋轉而下，迅捷無倫地轟向$n",
        "lvl"   : 150,
        "skill_name" : "利和同均"
]),
});

int valid_enable(string usage) { return usage=="leg" || usage=="parry"; }
int valid_learn(object me)
{
        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("學如影隨形腿時手裡不能拿武器。\n");
        if ((int)me->query_skill("zhanzhuang-gong", 1) < 120)
                return notify_fail("你的站樁功火候不夠，無法學如影隨形腿。\n");
        if( query("max_neili", me)<1500 )
                return notify_fail("你的內力太弱，無法練如影隨形腿。\n");
        if ((me->query_skill("shaolin-leg", 1) < 50) ||
                (me->query_skill("boruo-strike", 1) < 50))
                return notify_fail("你的少林彈腿和般若掌火候不夠，無法學如影隨形腿。\n");
        return 1;
}
int practice_skill(object me)
{
        if( query("qi", me)<30 )
                return notify_fail("你的精力太低了。\n");
        if( query("neili", me)<20 )
                return notify_fail("你的內力不夠練如影隨形腿。\n");
        me->receive_damage("qi", 50);
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
        int d_e1 = -50;
        int d_e2 = -20;
        int p_e1 = -10;
        int p_e2 = 20;
        int f_e1 = 300;
        int f_e2 = 400;
        int i, lvl, seq, ttl = sizeof(action);

        lvl = (int) me->query_skill("ruying-leg", 1);
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
                "damage_type" : random(2) ? "內傷" : "瘀傷",
        ]);
}
int learn_bonus() { return 10; }
int practice_bonus() { return 10; }
int success() { return 5; }
int power_point(object me) { return 1.0; }

string perform_action_file(string action)
{
         return __DIR__"ruying-leg/" + action;
}

int help(object me)
{
        write(HIC"\n如影隨形腿："NOR"\n");
        write(@HELP

   如影隨形腿是南少林高級腿法，不能互備，出自佛經中“六和敬”。

        學習要求：
                站樁功120級
                少林彈腿50級
                般若掌50級
                內力修為1500
HELP
        );
        return 1;
}
