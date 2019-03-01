// huashan-sword.c
// 氣宗,重force

#include <ansi.h>
inherit SKILL;
string type() { return "martial"; }
string martialtype() { return "skill"; }

mapping *action = ({
([        "skill_name" : "有鳳來儀",
        "action": "$N使一招"HIM"「有鳳來儀」"NOR"，手中$w劍光暴長，向$n的$l刺去",
        "lvl" : 0
]),
([        "skill_name" :"無邊落木",
        "action": "$N劍隨身轉，一招"GRN"「無邊落木」"NOR"罩向$n的$l",
        "lvl" : 10
]),
([        "skill_name" :"鴻飛冥冥",
        "action": "$N舞動$w，一招"BLU"「鴻飛冥冥」"NOR"挾著無數劍光刺向$n的$l",
        "lvl" : 20
]),
([        "skill_name" :"平沙落雁",
        "action": "$N手中$w龍吟一聲，祭出"HIY"「平沙落雁」"NOR"往$n的$l刺出數劍",
        "lvl" : 30
]),
([        "skill_name" :"金玉滿堂",
        "action": "$N手中$w劍光暴長，一招"RED"「金玉滿堂」"NOR"往$n$l刺去",
        "lvl" : 40
]),
([        "skill_name" :"白虹貫日",
        "action": "$N手中$w化成一道光弧，直指$n$l，一招"HIW"「白虹貫日」"NOR"發出虎哮龍吟刺去",
        "lvl" : 50
]),
});

int valid_enable(string usage) { return usage=="sword" || usage=="parry"; }
int valid_learn(object me)
{
        object ob;
        if( query("max_neili", me)<50 )
                return notify_fail("你的內力不夠，沒有辦法練華山劍法。\n");
        if( !(ob=query_temp("weapon", me)) || query("skill_type", ob) != "sword" )
                return notify_fail("你必須先找一把劍才能練劍法。\n");
        if (me->query_skill("sword", 1) < me->query_skill("huashan-sword", 1))
                return notify_fail("你的基本劍法火候有限，無法領會更高深的華山劍法。\n");

        return 1;
}
int practice_skill(object me)
{
        if( query("qi", me)<40 || query("neili", me)<30 )
                return notify_fail("你內力或氣不夠，沒有辦法練習華山劍法。\n");
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
        int d_e1 = 0;
        int d_e2 = 25;
        int p_e1 = -25;
        int p_e2 = -10;
        int f_e1 = 100;
        int f_e2 = 150;
        int m_e1 = 120;
        int m_e2 = 220;
        int i, lvl, seq, ttl = sizeof(action);

        lvl = (int) me->query_skill("huashan-sword", 1);
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

mixed hit_ob(object me, object victim, int damage)
{
        mixed result;

        if (me->query_skill("zixia-shengong", 1) < 100
        ||  me->query_skill_mapped("force") != "huashan-sword"
         || !query_temp("powerup", me )
        ||  damage < 100) return 0;

        if (random(damage / 2) > 50)
        {
                result = ([ "damage": damage ]);
                result += (["msg" : HIR "只見紫光閃過，$n□血四□，被$N" HIR "劍上的紫霞神功所傷！\n" NOR]);
                return result;
        }
}

string perform_action_file(string action)
{
        return __DIR__"huashan-sword/" + action;
}
int help(object me)
{
        write(HIC"\n華山劍法："NOR"\n");
        write(@HELP

    華山劍法為華山氣宗劍法。

        學習要求：
                紫霞神功
                內力50
HELP
        );
        return 1;
}
