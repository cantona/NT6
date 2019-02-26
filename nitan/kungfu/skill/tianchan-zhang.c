inherit SKILL;

mapping *action = ({
([      "action": "$N雙手不住地忽伸忽縮，手臂關節喀喇聲響，右掌一立，左掌啪的一下朝$n$l擊去",
        "force" : 100,
        "attack": 18,
        "dodge" : 30,
        "parry" : 15,
        "damage": 40,
        "lvl"   : 0,
        "damage_type": "瘀傷"
]),
([      "action": "$N身形挫動，風聲虎虎，接着朝$n連發八掌，一掌快似一掌，一掌猛似一掌",
        "force" : 200,
        "attack": 25,
        "dodge" : 40,
        "parry" : 30,
        "damage": 45,
        "lvl"   : 30,
        "damage_type": "瘀傷"
]),
([      "action": "$N攸地變爪為掌，身子不動，右臂陡長，潛運內力，一掌朝$n$l劈去",
        "force" : 250,
        "attack": 35,
        "dodge" : 50,
        "parry" : 55,
        "damage": 45,
        "lvl"   : 60,
        "damage_type": "瘀傷"
]),
([      "action": "$N一聲怪嘯，形如飄風，左掌已如風行電摯般拍向$n，掌未到，風先至，迅猛已極",
        "force" : 290,
        "attack": 42,
        "dodge" : 70,
        "parry" : 75,
        "damage": 43,
        "lvl"   : 90,
        "damage_type": "瘀傷"
]),
});

int valid_enable(string usage)
{
        return usage == "strike" || usage == "parry";
}

int valid_combine(string combo)
{
        return combo == "wusheng-zhao";
}

mapping query_action(object me, object weapon)
{
        int i, level;
        level = (int)me->query_skill("tianchan-zhang", 1);
        for (i = sizeof(action); i > 0; i--)
                if (level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level / 5)];
}

int valid_learn(object me)
{
        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("練天蟾掌必須空手。\n");

        if ((int)me->query_skill("force") < 80)
                return notify_fail("你的內功火候不夠，無法練天蟾掌。\n");

        if( query("max_neili", me)<450 )
                return notify_fail("你的內力太弱，無法練天蟾掌。\n");

        if (me->query_skill("strike", 1) < me->query_skill("tianchan-zhang", 1))
                return notify_fail("你的基本掌法水平有限，無法領會更高深的天蟾掌。\n");

        return 1;
}


int practice_skill(object me)
{
        if( query("qi", me)<60 )
                return notify_fail("你的體力太低了，先休息一下吧。\n");

        if( query("neili", me)<60 )
                return notify_fail("你的內力不夠練天蟾掌。\n");

        if (me->query_skill("tianchan-zhang", 1) < 50)
                me->receive_damage("qi", 30);
        else
                me->receive_damage("qi", 35);

        addn("neili", -54, me);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"tianchan-zhang/" + action;
}
