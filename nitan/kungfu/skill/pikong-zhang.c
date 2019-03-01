inherit SKILL;

mapping *action = ({
([      "action": "$N雙掌一錯，一招「雨疾風狂」，狂風般掃向$n的$l",
        "force" : 100,
        "attack": 18,
        "dodge" : 30,
        "parry" : 15,
        "damage": 40,
        "lvl"   : 0,
        "damage_type": "瘀傷"
]),
([      "action": "$N一招「殘霞滿天」，身形突然旋轉起來撲向$n，雙掌拍向$n的$l",
        "force" : 200,
        "attack": 25,
        "dodge" : 40,
        "parry" : 30,
        "damage": 45,
        "lvl"   : 30,
        "damage_type": "瘀傷"
]),
([      "action": "$N將內力運至左手，一招「繽紛落影」，迅疾無比地抓向$n的$l",
        "force" : 250,
        "attack": 35,
        "dodge" : 50,
        "parry" : 55,
        "damage": 45,
        "lvl"   : 60,
        "damage_type": "瘀傷"
]),
([      "action": "$N後退一步，突然一招「掌打飛花」，掌力拍向$n的$l",
        "force" : 330,
        "attack": 42,
        "dodge" : 40,
        "parry" : 65,
        "damage": 50,
        "lvl"   : 120,
        "damage_type": "瘀傷"
]),
});

int valid_enable(string usage)
{
        return usage == "strike" || usage == "parry";
}

int valid_combine(string combo)
{
        return combo == "xuanfeng-tui";
}

mapping query_action(object me, object weapon)
{
        int i, level;
        level = (int)me->query_skill("pikong-zhang", 1);
        for (i = sizeof(action); i > 0; i--)
                if (level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level / 5)];
}

int valid_learn(object me)
{
        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("練劈空掌法必須空手。\n");

        if ((int)me->query_skill("force") < 100)
                return notify_fail("你的內功火候不夠，無法練劈空掌法。\n");

        if( query("max_neili", me)<450 )
                return notify_fail("你的內力太弱，無法練劈空掌法。\n");

        if (me->query_skill("strike", 1) < me->query_skill("pikong-zhang", 1))
                return notify_fail("你的基本掌法水平有限，無法領會更高深的劈空掌法。\n");

        return 1;
}


int practice_skill(object me)
{
        if( query("qi", me)<60 )
                return notify_fail("你的體力太低了，先休息一下吧。\n");

        if( query("neili", me)<60 )
                return notify_fail("你的內力不夠練劈空掌法。\n");

        if (me->query_skill("pikong-zhang", 1) < 50)
                me->receive_damage("qi", 30);
        else
                me->receive_damage("qi", 50);

        addn("neili", -54, me);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"pikong-zhang/" + action;
}