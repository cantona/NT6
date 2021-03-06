inherit SKILL;

mapping *action = ({
([      "action" : "$N將手中$w一揚，一陣清風向$n的$l拂去",
        "damage" : 180,
        "dodge" : -50,
        "parry" : -30,
        "damage_type" : "割傷"
]),
([      "action" : "$N一揮$w，一片雲霞罩向$n的$l",
        "damage" : 220,
        "dodge" : -80,
        "parry" : -50,
        "damage_type" : "內傷"
])
});

int valid_enable(string usage) { return usage=="blade" || usage=="parry"; }

int valid_learn(object me)
{
        return 1;
}

mapping query_action(object me, object weapon)
{
        return action[random(sizeof(action))];
}

int practice_skill(object me)
{
        if ((int)me->query("qi") < 30)
                return notify_fail("你的體力太低了。\n");
        if ((int)me->query("neili") < 20)
                return notify_fail("你的內力不夠練精靈刀法。\n");
        me->receive_damage("qi", 30);
        me->add("neili", -10);
        return 1;
}

