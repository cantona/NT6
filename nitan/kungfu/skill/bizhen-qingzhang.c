#include <ansi.h>

inherit SKILL;

mapping *action = ({
([      "action" : "$N身形急晃，一躍而至$n跟前，右掌帶着切骨之勁砍向$n的$l",
        "force" : 180,
        "attack": 23,
        "dodge" : 25,
        "parry" : 17,
        "damage": 19,
        "lvl"   : 0,
        "damage_type" : "割傷"
]),
([      "action" : "$N飛身躍起，雙掌至上而下斜砍而出，頓時萬千道掌寒勁從四面八方席捲$n",
        "force" : 240,
        "attack": 41,
        "dodge" : 25,
        "parry" : 27,
        "damage": 25,
        "lvl"   : 30,
        "damage_type" : "割傷"
]),
([      "action" : "$N平掌為刀，斜斜砍出，幻出一道道剛猛的掌勁如颶風般裹向$n的全身",
        "force" : 330,
        "attack": 58,
        "dodge" : 36,
        "parry" : 35,
        "damage": 39,
        "lvl"   : 60,
        "damage_type" : "割傷"
]),
([      "action" : "$N反轉右掌護住全身，身形猛躍至$n面前，力注左掌，橫向$n攔腰砍去",
        "force" : 410,
        "attack": 96,
        "dodge" : 81,
        "parry" : 62,
        "damage": 53,
        "lvl"   : 90,
        "damage_type" : "割傷"
]),
([      "action" : "$N右掌後撤，手腕一翻，猛地揮掌砍出，幻出一道無比凌厲的掌勁直斬向$n的$l",
        "force" : 460,
        "attack": 125,
        "dodge" : 35,
        "parry" : 47,
        "damage": 78,
        "lvl"   : 120,
        "damage_type" : "割傷"
]),
([      "action" : "$N雙手揮舞出，形成一個大圈，一股勁氣澎湃洶湧而來，逼得$n踉踉後退",
        "force" : 520,
        "attack": 110,
        "dodge" : 45,
        "parry" : 40,
        "damage": 85,
        "lvl"   : 150,
        "damage_type" : "割傷"
]),
});

int valid_enable(string usage) { return usage=="strike" || usage=="parry"; }

int valid_learn(object me)
{
        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("練碧針清掌必須空手。\n");

        if ((int)me->query_skill("force") < 250)
                return notify_fail("你的內功火候不夠，無法練習碧針清掌。\n");

        if( query("max_neili", me)<2500 )
                return notify_fail("你的內力太弱，無法練習碧針清掌。\n");

        if ((int)me->query_skill("strike", 1) < 180)
                return notify_fail("你的基本掌法火候不夠，無法練習碧針清掌。\n");

        if ((int)me->query_skill("strike", 1) < (int)me->query_skill("bizhen-qingzhang", 1))
                return notify_fail("你的基本掌法水平有限，無法領會更高深的碧針清掌。\n");

        return 1;
}

string query_skill_name(int level)
{
        int i;
        for (i = sizeof(action) - 1; i >= 0; i--)
                if (level >= action[i]["lvl"])
                        return action[i]["skill_name"];
}

mapping query_action(object me, object weapon)
{
/* d_e=dodge_effect p_e=parry_effect f_e=force_effect m_e=damage_effect */
        int d_e1 = -20;
        int d_e2 = -40;
        int p_e1 = -35;
        int p_e2 = -15;
        int f_e1 = 200;
        int f_e2 = 300;
        int i, lvl, seq, ttl = sizeof(action);

        lvl = (int) me->query_skill("bizhen-qingzhang", 1);
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

int learn_bonus() { return 15; }
int practice_bonus() { return 15; }
int success() { return 15; }
int power_point(object me) { return 1.0; }

int practice_skill(object me)
{
        if( query("qi", me)<100 )
                return notify_fail("你的體力太低了。\n");

        if( query("neili", me)<100 )
                return notify_fail("你的內力不夠練碧針清掌。\n");

        me->receive_damage("qi", 80);
        addn("neili", -80, me);
        return 1;
}

mixed hit_ob(object me, object victim, int damage_bonus)
{
        if (damage_bonus < 100) return 0;

        if (random(me->query_skill("force")) > victim->query_skill("force") / 2)
        {
                victim->receive_wound("qi", (damage_bonus - 100) / 2);
                return HIR "只聽" + victim->name() +
                       HIR "前胸“喀嚓”一聲，竟像是肋骨碎斷的聲音！\n" NOR;
        }
}

string perform_action_file(string action)
{
        return __DIR__"bizhen-qingzhang/" + action;
}