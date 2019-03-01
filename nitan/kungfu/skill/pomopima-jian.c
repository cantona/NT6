// pomopima-jian.c 潑墨披麻劍法
// Last Modified by sir 11.1.2001

#include <ansi.h>;
inherit SKILL;
string type() { return "martial"; }
string martialtype() { return "skill"; }

mapping *action = ({
([        "action":       "$N使一招"HIW"「白虹貫日」"NOR"，手中$w輕飄飄地向$n的$l斬去！",
        "lvl" : 0,
        "skill_name" : "白虹貫日"
]),
([        "action":       "$N金刃劈風，$w隨著一招"HIY"「騰蛟起風」"NOR"由下而上撩往$n的$l",
        "lvl" : 10,
        "skill_name" : "騰蛟起風"
]),
([        "action":       "$N身形一轉，一招"GRN"「春風楊柳」"NOR"$w劍光不定，斬向$n的$l",
        "lvl" : 20,
        "skill_name" : "春風楊柳"
]),
([        "action":       "$N舞動$w，一招"CYN"「心馳神遙」"NOR"迅捷無倫地劈向$n的$l",
        "lvl" : 30,
        "skill_name" : "心馳神遙"
]),
([        "action":       "$N手中$w一晃，一招"HIG"「青山依舊」"NOR"往$n的$l斜斜砍出一劍",
        "lvl" : 40,
        "skill_name" : "青山依舊"
]),
([        "action":       "$N提劍過肩，蓄勁發力，一招"HIC"「玉龍倒懸」"NOR"直劈$n$l",
        "lvl" : 50,
        "skill_name" : "玉龍倒懸"
]),
([        "action":       "$N移步側身，使一招"HIM"「漫山遍野」"NOR"劍光霍霍斬向$n的$l",
        "lvl" : 60,
        "skill_name" : "漫山遍野"
]),
});
int valid_enable(string usage) { return usage == "sword" || usage == "parry";}
int valid_learn(object me)
{
        if( query("max_neili", me)<100 )
                return notify_fail("你的內力不夠。\n");

        if ((int)me->query_skill("force") < 20)
                return notify_fail("你的內功火候太淺。\n");

        if ((int)me->query_skill("sword", 1) < (int)me->query_skill("pomopima-jian", 1))
                return notify_fail("你的基本劍法水平有限，無法領會更高深的潑墨披麻劍。\n");

        return 1;
}

int practice_skill(object me)
{
        object weapon;

        if( !objectp(weapon=query_temp("weapon", me)) || 
                query("skill_type", weapon) != "sword" )
                return notify_fail("你必須先找一把劍，才能練劍法。\n");

        if( query("qi", me)<30 || query("neili", me)<30 )
                return notify_fail("你的內力或氣不夠練這門劍法，還是先休息休息吧。\n");
        me->receive_damage("qi", 20);
        addn("neili", -10, me);
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
        int d_e1 = 30;
        int d_e2 = 55;
        int p_e1 = 5;
        int p_e2 = 25;
        int f_e1 = 50;
        int f_e2 = 100;
        int m_e1 = 30;
        int m_e2 = 125;
        int i, lvl, seq, ttl = sizeof(action);

        lvl = (int) me->query_skill("pomopima-jian", 1);
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
int learn_bonus() { return 30; }
int practice_bonus() { return 30; }
int success() { return 20; }
int power_point(object me) { return 1.0; }

string perform_action_file(string action)
{
        return __DIR__"pomopima-jian/" + action;
}

int help(object me)
{
        write(HIC"\n潑墨披麻劍法："NOR"\n");
        write(@HELP

    日月神教黑木崖武功，梅莊四莊主丹青生看家本領。

        學習要求：
                葵花心法10級
                內力100
HELP
        );
        return 1;
}