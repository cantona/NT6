// dusha-zhang.c 毒砂掌 藥王谷
// Edit By Vin On 26/2/2001

#include <ansi.h>

inherit SKILL;

mapping *action = ({
([      "action": "$N雙手不住地忽伸忽縮，手臂關節喀喇聲響，右掌一立，左掌啪的一下朝$n$l擊去",
        "force" : 80,
        "attack": 28,
        "dodge" : 10,
        "parry" : 5,
        "damage": 60,
        "lvl"   : 0,
        "damage_type": "瘀傷"
]),
([      "action": "$N身形挫動，風聲虎虎，接著朝$n連發八掌，一掌快似一掌，一掌猛似一掌",
        "force" : 130,
        "attack": 35,
        "dodge" : 10,
        "parry" : 10,
        "damage": 67,
        "lvl"   : 30,
        "damage_type": "瘀傷"
]),
([      "action": "$N攸地變爪為掌，身子不動，右臂陡長，潛運內力，一掌朝$n$l劈去",
        "force" : 170,
        "attack": 37,
        "dodge" : 20,
        "parry" : 25,
        "damage": 65,
        "lvl"   : 60,
        "damage_type": "瘀傷"
]),
([      "action": "$N一聲怪嘯，形如飄風，左掌已如風行電摯般拍向$n，掌未到，風先至，迅猛已極",
        "force" : 220,
        "attack": 42,
        "dodge" : 30,
        "parry" : 35,
        "damage": 73,
        "lvl"   : 90,
        "damage_type": "瘀傷"
]),
});

int valid_enable(string usage) { return usage == "strike" || usage == "parry"; }

int valid_combine(string combo) { return combo=="lansha-shou"; }

mapping query_action(object me, object weapon)
{
        int i, level;
        level = (int)me->query_skill("dusha-zhang", 1);
        for (i = sizeof(action); i > 0; i--)
                if (level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level / 5)];
}

int valid_learn(object me)
{
        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("練毒砂掌必須空手。\n");

        if ((int)me->query_skill("force") < 100)
                return notify_fail("你的內功火候不夠，無法練毒砂掌。\n");

        if( query("max_neili", me)<450 )
                return notify_fail("你的內力太弱，無法練毒砂掌。\n");

        if (me->query_skill("strike", 1) < me->query_skill("dusha-zhang", 1))
                return notify_fail("你的基本掌法水平有限，無法領會更高深的毒砂掌。\n");

        return 1;
}

int practice_skill(object me)
{
        if( query("qi", me)<60 )
                return notify_fail("你的體力太低了，先休息一下吧。\n");

        if( query("neili", me)<70 )
                return notify_fail("你的內力不夠練毒砂掌。\n");

        if (me->query_skill("dusha-zhang", 1) < 50)
                me->receive_damage("qi", 30);
        else
                me->receive_damage("qi", 40);

        addn("neili", -60, me);
        return 1;
}

mixed hit_ob(object me, object victim, int damage_bonus, int factor)
{
        int lvl;
        int flvl;

        lvl  = me->query_skill("dusha-zhang", 1);
        flvl=query("jiali", me);
        if (lvl < 80 || flvl < 10 || ! damage_bonus)
                return;

        if (flvl * 2 + random(lvl) > victim->query_skill("force") &&
           victim->affect_by("sha_poison",
                ([ "level" : flvl + random(flvl),
                   "id":query("id", me),
                   "duration" : lvl / 50 + random(lvl / 20) ])))
        {
                return WHT "$n" WHT "忽然感到一股莫名的惡心，全身癱軟，嘴皮烏紫。\n" NOR;
        }
}

string perform_action_file(string action)
{
        return __DIR__"dusha-zhang/" + action;
}