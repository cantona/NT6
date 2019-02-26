// huhe-quan.c 虎鶴雙形拳
// Last Modified by Winder on Mar. 10 2000
// 主要用在沒門派的npc身上

#include <ansi.h>;
inherit SKILL;
string type() { return "martial"; }
string martialtype() { return "skill"; }

mapping *action = ({
([        "action" : "$N二手合十，一式「起首勢」，雙拳蓄勢而發，擊向$n的$l",
        "lvl" : 0,
        "skill_name" : "蓮花座"
]),
([        "action" : "$N一式「虎形」，雙掌輪流下擊，拳勢如焰，吡啪爆響",
        "lvl" : 10,
        "skill_name" : "虎形"
]),
([        "action" : "$N騰空飛起，一式「鶴形」，雙手雙腿齊出，令$n無可躲藏",
        "lvl" : 20,
        "skill_name" : "鶴形"
]),
([        "action" : "$N雙掌虛含，掌緣下沉，一式「黑虎掏心」，緩緩向$n推出",
        "lvl" : 30,
        "skill_name" : "黑虎掏心"
]),
([        "action" : "$N一臂前伸，一臂後指，一式「鶴度九天」，攻向$n的身前身後",
        "lvl" : 40,
        "skill_name" : "鶴度九天"
]),
([        "action" : "$N一式「白鶴點水」，兩手十指虛點$n的全身三十六道要穴",
        "lvl" : 48,
        "skill_name" : "白鶴點水"
]),
([        "action" : "$N兩目內視，雙手內籠，一式「虎嘯龍吟」，四面八方響起震人心魄的
龍吟",
        "lvl" : 54,
        "skill_name" : "虎嘯龍吟"
]),
([        "action" : "$N似笑非笑，雙拳無形無定，一式「猛虎下山」，驟然擊向$n的前胸",
        "lvl" : 60,
        "skill_name" : "猛虎下山"
])
});

int valid_enable(string usage) { return        usage=="cuff" || usage=="parry"; }
int valid_learn(object me)
{
        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("練虎鶴雙形拳必須空手。\n");
        if ((int)me->query_skill("haoran-zhengqi", 1) < 10)
                return notify_fail("你的浩然正氣火候不夠，無法學虎鶴雙形拳。\n");
        if( query("max_neili", me)<50 )
                return notify_fail("你的內力太弱，無法練虎鶴雙形拳。\n");
        return 1;
}

int practice_skill(object me)
{
        if( query("qi", me)<30 )
                return notify_fail("你的體力太低了。\n");
        if( query("neili", me)<20 )
                return notify_fail("你的內力不夠練虎鶴雙形拳。\n");
        me->receive_damage("qi", 30);
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
        int d_e1 = 40;
        int d_e2 = 60;
        int p_e1 = -20;
        int p_e2 = 0;
        int f_e1 = 60;
        int f_e2 = 210;
        int i, lvl, seq, ttl = sizeof(action);

        lvl = (int) me->query_skill("huhe-quan", 1);
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
                "damage_type" : "瘀傷",
        ]);
}
int learn_bonus() { return 30; }
int practice_bonus() { return 30; }
int success() { return 20; }
int power_point(object me) { return 1.0; }

int help(object me)
{
        write(HIC"\n虎鶴雙形拳："NOR"\n");
        write(@HELP

    虎鶴雙形拳是雲中鶴的成名絕技。

        學習要求：
                無
HELP
        );
        return 1;
}
