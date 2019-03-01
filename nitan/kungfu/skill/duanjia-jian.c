#include <ansi.h>;
inherit SKILL;
string type() { return "martial"; }
string martialtype() { return "skill"; }

mapping *action = ({
([        "action" : "$N向前跨上一步，一招"HIB"「雲橫秦嶺」"NOR"，手中$w自左向右向$n的$l緩緩劃去",
        "lvl" : 0,
        "skill_name" : "雲橫秦嶺"
]),
([        "action" : "$N向上躍起，左手劍訣，右手一抖，$w劍光縵妙如瀑，一式" GRN"「飛流直下」"NOR"直刺$n的$l",
        "lvl" : 9,
        "skill_name" : "飛流直下"
]),
([        "action" : "$N一招"BLU"「雪擁藍關」"NOR"，$w閃起數道寒光，自下而上反挑$n的$l",
        "lvl" : 19,
        "skill_name" : "雪擁藍關"
]),
([        "action" : "$N一招"RED"「奇兵突起」"NOR"，手中$w看似橫掃實則斜劈，刺向$n的$l",
        "lvl" : 29,
        "skill_name" : "奇兵突起"
]),
([        "action" : "$N使出"HIB"「夜叉探海」"NOR"，$w挽出三個劍花，綿綿不斷劃向$n的$l",
        "lvl" : 39,
        "skill_name" : "夜叉探海"
]),
([        "action" : "$N一招"HIG"「泰山壓頂」"NOR"，左手一捏劍訣，右手$w自上而下雷霆萬鈞般直向$n的$l劈了下去",
        "lvl" : 49,
        "skill_name" : "泰山壓頂"
]),
([        "action" : "$N一招"MAG"「雨打梨花」"NOR"，身在半空，$w回抽，反手勾向$n的$l",
        "lvl" : 69,
        "skill_name" : "雨打梨花"
]),
([        "action" : "$N身影一晃, 繞到$n背後，一招"HIW"「逐鹿中原」"NOR"，劍尖向$n的$l疾挑",
        "lvl" : 89,
        "skill_name" : "逐鹿中原"
]),
});

int valid_enable(string usage)
{
        return (usage == "sword") || (usage == "staff") || (usage == "parry");
}

int valid_learn(object me)
{
        if( query("max_neili", me)<300 )
                return notify_fail("你的內力不夠。\n");

        if ((int)me->query_skill("sword", 1) < 30)
                return notify_fail("你的基本劍法火候太淺。\n");

        if ((int)me->query_skill("sword", 1) < (int)me->query_skill("duanjia-jian", 1)
               && (int)me->query_skill("staff", 1) < (int)me->query_skill("duanjia-jian", 1))
                return notify_fail("你的基本劍法或杖法火候不夠，無法領會更高深的段家劍法。\n");

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
        int d_e2 = -15;
        int p_e1 = 10;
        int p_e2 = 40;
        int f_e1 = 300;
        int f_e2 = 400;
        int m_e1 = 200;
        int m_e2 = 300;
        int i, lvl, seq, ttl = sizeof(action);

        lvl = (int) me->query_skill("duanjia-jian", 1);
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
                "damage_type" : random(2) ? "挫傷" : "刺傷",
        ]);
}

int practice_skill(object me)
{
        object weapon;

        if( !objectp(weapon=query_temp("weapon", me) )
        || (query("skill_type", weapon) != "staff"
        && query("skill_type", weapon) != "sword") )
                return notify_fail("你使用的武器不對。\n");

        if( query("qi", me)<50 )
                return notify_fail("你的體力不夠練段家劍。\n");

        if( query("neili", me)<40 )
                return notify_fail("你的內力不夠練段家劍。\n");

        me->receive_damage("qi", 45);
                addn("neili", -36, me);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"duanjia-jian/" + action;
}

int learn_bonus() { return 5; }
int practice_bonus() { return 5; }
int success() { return 10; }
int power_point(object me) { return 1.0; }

int help(object me)
{
        write(HIC"\n段家劍："NOR"\n");
        write(@HELP

    段家劍是天南大理段家劍法。

        學習要求：
                枯榮禪功20級
                內力100
HELP
        );
        return 1;
}
