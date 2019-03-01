// six-fingers.c 六脈神劍 - 少商劍
#include <ansi.h>
inherit SKILL;

mapping *action = ({
        ([ "name":   "少商劍",
           "action": "$N反過手來，雙手拇指同時捺出，嗤嗤兩聲急響，“少商劍”"
                     "有如石破天驚、風雨大至之勢，指向$n的$l",
           "force":  370,
           "dodge":  10,
           "damage": 100,
           "damage_type":  "刺傷"
        ]),
});

string main_skill() { return "six-finger"; }

int valid_enable(string usage) { return usage=="finger" ||  usage=="parry"; }

int valid_learn(object me)
{
        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("練少商劍必須空手。\n");

        if( query("max_neili", me)<2250 )
                return notify_fail("你的內力太弱，無法學少商劍。\n");

        if ((int)me->query_skill("finger", 1) < (int)me->query_skill("shaoshang-sword", 1))
                return notify_fail("你的基本指法水平有限，無法無法領會更高深的少商劍。\n");

        return 1;
}

string query_skill_name(int level)
{
        int i;
        for(i = sizeof(action); i > 0; i--)
                if(level >= action[i-1]["lvl"])
                        return action[i-1]["skill_name"];
}

int practice_skill(object me)
{
        object* ob, obj;
        int i,skill,damage;

        if ((int)me->query_skill("six-finger", 1))
                return notify_fail("你已經學齊六脈神劍了。\n");

        if( query("qi", me)<100 )
                return notify_fail("你的體力太低了。\n");

        if( query("neili", me)<200 )
                return notify_fail("你的內力不夠練少商劍。\n");

        me->receive_damage("qi", 40);
        addn("neili", -80, me);
        return 1;
}
                                          
mixed hit_ob(object me, object victim, int damage_bonus)
{
        if( damage_bonus < 100 ) return 0;

        if( random(damage_bonus/4) > victim->query_str() )
        {
                victim->receive_wound("qi", (damage_bonus - 100) / 2 );
                return HIR "你聽到「嗤啦」一聲輕響，臉上竟濺到一些血滴！\n" NOR;
        }
}

mapping query_action(object me, object weapon)
{
        return action[random(sizeof(action))];
}