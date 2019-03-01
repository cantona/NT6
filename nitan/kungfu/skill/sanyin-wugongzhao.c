//sanyin-wugongzhao.c 三陰蜈蚣爪
// Last Modified by winder on Mar. 10 2000

#include <ansi.h>
inherit SKILL;
string type() { return "martial"; }
string martialtype() { return "skill"; }

mapping *action = ({
([        "action" : "$N爪現青白，骨結隆起，自上而下撕扯$n的$l",
        "lvl"    : 0,
        "skill_name" : "蜈蚣現爪" ,
]),
([        "action" : "$N雙手忽隱忽現，爪爪鬼魅般抓向$n的$l",
        "lvl"    : 10,
        "skill_name" : "鬼影連爪" ,
]),
([        "action" : "$N身形圍$n一轉，爪影縱橫毫不留情對著$n的$l抓下",
        "lvl"    : 20,
        "skill_name" : "旋風毒爪" ,
]),
([        "action" : "$N一聲怪叫，一爪橫出直擊$n的天靈蓋",
        "lvl"    : 40,
        "skill_name" : "唯我獨尊" ,
]),
});

int valid_enable(string usage) { return usage=="claw" || usage=="parry"; }
int valid_combine(string combo) { return combo=="chousui-duzhang"; }

int valid_learn(object me)
{
        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
            return notify_fail("練三陰蜈蚣爪必須空手。\n");

        if( query("max_neili", me)<200 )
            return notify_fail("你的內力太弱，無法練三陰蜈蚣爪。\n");

        if ((int)me->query_skill("claw", 1) < (int)me->query_skill("sanyin-wugongzhao", 1))
            return notify_fail("你的基本爪法水平有限，無法領會更高深的三陰蜈蚣爪法。\n");

        return 1;
}

int practice_skill(object me)
{
        object* ob;
        int i,damage;
        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("你的必須空手才能練習。\n");
        if( query("qi", me)<30 )
                return notify_fail("你的體力太低了。\n");
        if( query("neili", me)<20 )
                return notify_fail("你的內力不夠練三陰蜈蚣爪。\n");
        me->receive_damage("qi", 30);
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
        int d_e1 = 60;
        int d_e2 = 40;
        int p_e1 = 0;
        int p_e2 = -20;
        int f_e1 = 100;
        int f_e2 = 250;
        int i, lvl, seq, ttl = sizeof(action);

        lvl = (int)me->query_skill("sanyin-wugongzhao",1);
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
                "damage_type" : random(2) ? "抓傷" : "內傷",
        ]);
}
mixed hit_ob(object me, object victim, int damage_bonus, int factor)
{
        if( random(me->query_skill("huagong-dafa",1)) > 5)
        {
                victim->apply_condition("xx_poison", random(2) + 5);
        }
}
int learn_bonus() { return 30; }
int practice_bonus() { return 30; }
int success() { return 20; }
int power_point(object me) { return 1; }

string perform_action_file(string action)
{
        return __DIR__"sanyin-wugongzhao/" + action;
}

int help(object me)
{
        write(HIC"\n三陰蜈蚣爪："NOR"\n");
        write(@HELP

    三陰蜈蚣爪為星宿派歹毒武功。
    可與抽髓掌互備。

        學習要求：
                化功大法20級
                內力200
HELP
        );
        return 1;
}
