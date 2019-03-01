// six-fingers.c 六脈神劍 - 中沖劍
#include <ansi.h>
inherit SKILL;

mapping *action = ({
        ([ "name":   "中沖劍",
           "action": "$N右手中指一豎，“中沖劍”向前刺出。真氣鼓盪，嗤然聲響，"
                     "無形劍氣直指$n的$l",
           "force":  490,
           "dodge":  -15,
           "damage": 110,
           "damage_type": "刺傷"
        ]),
});

string main_skill() { return "six-finger"; }

int valid_enable(string usage) { return usage == "finger" ||  usage == "parry"; }

int valid_learn(object me)
{
        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("練中沖劍必須空手。\n");

        if( query("max_neili", me)<2250 )
                return notify_fail("你的內力太弱，無法學中沖劍。\n");

        if ((int)me->query_skill("finger", 1) < (int)me->query_skill("zhongchong-sword", 1))
                return notify_fail("你的基本指法水平有限，無法無法領會更高深的中沖劍。\n");

        return 1;
}

string query_skill_name(int level)
{
        int i;
        for (i = sizeof(action); i > 0; i--)
                if (level >= action[i-1]["lvl"])
                        return action[i-1]["skill_name"];
}

int practice_skill(object me)
{
        object* ob, obj;
        int i, skill, damage;

        if ((int)me->query_skill("six-finger", 1))
                return notify_fail("你已經學齊六脈神劍了。\n");

        if( query("qi", me)<100 )
                return notify_fail("你的體力太低了。\n");

        if( query("neili", me)<200 )
                return notify_fail("你的內力不夠練中沖劍。\n");

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