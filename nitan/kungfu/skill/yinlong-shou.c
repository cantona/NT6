// This program is a part of NITAN MudLIB
// yinlong-shou.c 銀龍手

inherit SKILL;

mapping *action = ({
([      "action" : "$N的身行飄忽不定，如同幻影一般，閃到了$n的身後，一招「無影無蹤」拍向$n的$l",
        "force" : 130,
        "dodge" : -20,
        "parry" : -20,
        "damage" : 100,
        "lvl" : 0,
        "skill_name" : "無影無蹤",
        "damage_type" : "內傷"
]),
([      "action" : "$N雙掌如同龍神一般，綻放開來，正是一招「龍神探影」，擊向$n的$l",
        "force" : 150,
        "dodge" : -10,
        "parry" : -10,
        "damage" : 130,
        "lvl" : 20,
        "skill_name" : "龍神探影",
        "damage_type" : "內傷"
]),
([      "action" : "$N身行繞著$n急速轉動，忽然出掌，正是一招「飛天幻掌」打向$n的$l",
        "force" : 150,
        "dodge" : -30,
        "parry" : -30,
        "damage" : 135,
        "lvl" : 30,
        "skill_name" : "飛天幻掌",
        "damage_type" : "內傷"
]),
([      "action" : "$N雙掌上下番飛，如同化成了千萬個手掌，正是一招「九天千幻」拍向$n的$l處",
        "force" : 250,
        "dodge" : -20,
        "parry" : -20,
        "damage" : 110,
        "lvl" : 40,
        "skill_name" : "九天千幻",
        "damage_type" : "內傷"
]),
});

int valid_enable(string usage) { return usage=="strike" || usage=="parry"; }

int valid_learn(object me)
{
        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("練銀龍手必須空手。\n");
        if( query("max_neili", me)<50 )
                return notify_fail("你的內力太弱，無法練銀龍手。\n");
        return 1;
}

mapping query_action(object me, object weapon)
{
        int i, level;
        level = (int) me->query_skill("yinlong-shou",1);
        for(i = sizeof(action); i > 0; i--)
                if(level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
        if( query("qi", me)<30 )
                return notify_fail("你的體力太低了。\n");
        if( query("neili", me)<20 )
                return notify_fail("你的內力不夠練銀龍手。\n");
        me->receive_damage("qi", 25);
        addn("neili", -10, me);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"yinlong-shou/" + action;
}
