// wudu-zhang.c 五毒掌
// Last Modified by sir 10.22.2001

#include <ansi.h>;
inherit SKILL;
string type() { return "martial"; }
string martialtype() { return "skill"; }

mapping *action = ({
([        "action" : "$N雙手一翻，兩掌帶著淡淡的藍光，直向$n拍去",
        "lvl" : 0,
        "skill_name" : "五毒掌"
]),
([        "action" : "$N左掌虛晃，右掌直出，猶如毒蛇一般直迫$n的胸前",
        "lvl" : 10,
        "skill_name" : "五毒掌"
]),
([        "action" : "$N雙掌翻飛，四周迷茫著一股暗淡的霧氣，排向$n的全身",
        "lvl" : 20,
        "skill_name" : "五毒掌"
]),
([        "action" : "$N兩掌一分，左掌如蠍，右掌似蛇，同時向$n擊過去",
        "lvl" : 30,
        "skill_name" : "五毒掌"
]),
([        "action" : "$N默運內力，雙掌忽然變黑，帶著一股陰風只撲$n的全身",
        "lvl" : 40,
        "skill_name" : "五毒掌"
])
});

int valid_enable(string usage) { return usage=="strike" || usage=="parry" ; }
int valid_combine(string combo) { return combo=="qianzhu-wandushou"; }

int valid_learn(object me)
{
        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("練五毒掌必須空手。\n");
        if ((int)me->query_skill("wudu-shengong", 1) < 20)
                return notify_fail("你的五毒神功火候不夠，無法學五毒掌。\n");
        if( query("max_neili", me)<100 )
                return notify_fail("你的內力太弱，無法練五毒掌。\n");
        return 1;
}
int practice_skill(object me)
{
        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("你的必須空手才能練習。\n");
        if( query("qi", me)<30 )
                return notify_fail("你的體力太低了。\n");
        if( query("neili", me)<20 )
                return notify_fail("你的內力不夠練五毒掌。\n");
        me->receive_damage("qi", 25);
        addn("neili", -10, me);
        return 1;
}
mixed hit_ob(object me, object victim, int damage_bonus, int factor)
{
        if( random(me->query_skill("qianzhu-wandushou",1)) > 30 )
                victim->receive_wound("qi", damage_bonus/3);
        if( query("family/family_name", victim) != "五毒教" && 
                me->query_skill("wudu-shengong",1)>40)
        {
                switch( random(5) )
                {
                        case 0:
                                victim->apply_condition("snake_poison", (me->query_skill("wudu-shengong"))/10 + victim->query_condition("snake_poison"));
                                break;
                        case 1:
                                victim->apply_condition("zhizhu_poison", (me->query_skill("wudu-shengong"))/10 + victim->query_condition("zhizhu_poison"));
                                break;
                        case 2:
                                victim->apply_condition("wugong_poison", (me->query_skill("wudu-shengong"))/10 + victim->query_condition("wugong_poison"));
                                break;
                        case 3:
                                victim->apply_condition("xiezi_poison", (me->query_skill("wudu-shengong"))/10 + victim->query_condition("xiezi_poison"));
                                break;
                        case 4:
                                victim->apply_condition("chanchu_poison", (me->query_skill("wudu-shengong"))/10 + victim->query_condition("chanchu_poison"));
                                break;
                }
                return HIR"$n只覺得傷處一陣發麻，似乎中毒了。\n" NOR;
        }
}
void skill_improved(object me)
{
        if( random(15)<1 && query("per", me)>5 )
        {
                tell_object(me, HIR"你忽然覺得體內毒氣狂竄，面上頓時罩著一層黑氣！\n" NOR );
                addn("per", -1, me);
        }
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
        int d_e1 = -20;
        int d_e2 = 5;
        int p_e1 = 25;
        int p_e2 = 50;
        int f_e1 = 120;
        int f_e2 = 230;
        int i, lvl, seq, ttl = sizeof(action);

        lvl = (int) me->query_skill("wudu-zhang", 1);
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
int learn_bonus() { return 30; }
int practice_bonus() { return 30; }
int success() { return 20; }
int power_point(object me) { return 1.0; }

int help(object me)
{
        write(HIC"\n五毒掌："NOR"\n");
        write(@HELP

    五毒掌是五毒教的獨門功夫，可與千蛛萬毒手互備。

        學習要求：
                五毒神功20級
                內力100
HELP
        );
        return 1;
}
