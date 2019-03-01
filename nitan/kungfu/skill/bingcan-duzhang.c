// bingcan-duzhang.c  冰蠶毒掌

#include <ansi.h>

inherit SKILL;

mapping *action = ({
([      "action": "$N臉上露出詭異的笑容，雙掌攜滿寒霜，橫掃$n",
        "dodge" : -30,
        "attack": 79,
        "parry" : -37,
        "dmage" : 52,
        "force" : 430,
        "damage_type": "瘀傷"
]),
([      "action": "$N突然身形旋轉起來撲向$n，雙掌飛舞著拍向$n的$l",
        "dodge" : -22,
        "attack": 96,
        "parry" : -34,
        "dmage" : 67,
        "force" : 490,
        "damage_type": "瘀傷"
]),
([      "action": "$N將冰蠶寒毒運至右手，陰毒無比地拍向$n的$l",
        "dodge" : -20,
        "attack": 113,
        "parry" : 10,
        "dmage" : 82,
        "force" : 530,
        "damage_type": "瘀傷"
]),
([      "action": "$N詭異的一笑，雙掌帶著凌厲的寒氣拍向$n的$l",
        "dodge" : 28,
        "attack": 139,
        "parry" : 36,
        "dmage" : 95,
        "force" : 580,
        "damage_type": "瘀傷"
]),
([      "action": "$N仰天一聲長嘯，聚集全身的力量擊向$n",
        "dodge" : 27,
        "attack": 161,
        "parry" : 21,
        "dmage" : 105,
        "force" : 640,
        "damage_type": "瘀傷"
]),
});

int valid_enable(string usage) { return usage=="strike" || usage=="parry"; }

int valid_learn(object me)
{
        if( !query("family", me) || 
            query("family/family_name", me) != "星宿派" )
                return notify_fail("你不是星宿派門人，無法學習此神功。\n");

        if ((int)me->query_skill("freezing-force", 1) < 0)
                return notify_fail("你所修的內功無法練冰蠶毒掌。\n");

        if ((int)me->query_skill("force") < 200)
                return notify_fail("你的內功火候不夠，無法練冰蠶毒掌。\n");

        if( query("max_neili", me)<3000 )
                return notify_fail("你的內力太弱，無法練冰蠶毒掌。");

        if ((int)me->query_skill("strike", 1) < (int)me->query_skill("bingcan-duzhang", 1))
                return notify_fail("你的基本掌法水平有限，無法領會更高深的冰蠶毒掌。\n");

        if ((int)me->query_skill("freezing-force", 1) < (int)me->query_skill("bingcan-duzhang", 1))
                return notify_fail("你的冰蠶寒功水平有限，無法領會更高深的冰蠶毒掌。\n");

        return 1;
}

/*
string query_skill_name(int level)
{
        int i;
        for(i = sizeof(action)-1; i >= 0; i--)
                if(level >= action[i]["lvl"])
                        return action[i]["skill_name"];
}
*/
mapping query_action(object me, object weapon)
{
/* d_e=dodge_effect p_e=parry_effect f_e=force_effect m_e=damage_effect */
        int d_e1 = -20;
        int d_e2 = -40;
        int p_e1 = -35;
        int p_e2 = -55;
        int f_e1 = 200;
        int f_e2 = 300;
        int i, lvl, seq, ttl = sizeof(action);

        lvl = (int) me->query_skill("bingcan-duzhang", 1);
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
        if( query("qi", me)<40 )
                return notify_fail("你的體力太低了。\n");

        if( query("neili", me)<30 )
                return notify_fail("你的內力不夠練冰蠶毒掌。\n");

        if (me->query_skill("bingcan-duzhang", 1) < 50)
                me->receive_damage("qi", 100);
        else
                me->receive_damage("qi", 150);

        addn("neili", -180, me);
        return 1;
}

mixed hit_ob(object me, object victim, int damage_bonus, int factor)
{
        int lvl;
        int flvl;

        lvl  = me->query_skill("bingcan-duzhang", 1);
        flvl=query("jiali", me);
        if (lvl < 80 || flvl < 10 || ! damage_bonus)
                return;

        if (flvl * 2 + random(lvl) > victim->query_skill("force") &&
            victim->affect_by("bingcan_duzhang",
                              ([ "level" : flvl + random(flvl),
                                 "id":query("id", me),
                                 "duration" : lvl / 100 + random(lvl / 10) ])))
        {
                return HIW "$n" HIW "只感一陣極寒從心底升起，看來是中了$N" HIW "掌上的冰蠶寒毒。\n" NOR;
        }
}

string perform_action_file(string action)
{
        return __DIR__"bingcan-duzhang/" + action;
}
