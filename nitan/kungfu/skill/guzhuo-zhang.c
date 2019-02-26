inherit SKILL;

mapping *action = ({
([        "action" : "$N一聲大喝，左掌疊於右掌之上，劈向$n",
        "force" : 100,
        "attack": 2,
        "dodge" : 30,
        "parry" : 1,
        "damage": 15,
        "lvl"   : 0,
        "damage_type" : "內傷"
]),
([        "action" : "$N面色凝重，雙掌輕抖，飄忽不定地拍向$n",
        "force" : 130,
        "attack": 8,
        "dodge" : 25,
        "parry" : 3,
        "damage": 30,
        "lvl"   : 20,
        "damage_type" : "內傷"
]),
([        "action" : "$N氣沉丹田，雙掌幻化一片掌影，將$n籠罩於內。",
        "force" : 160,
        "attack": 12,
        "dodge" : 43,
        "parry" : 4,
        "damage": 35,
        "lvl"   : 40,
        "damage_type" : "內傷"
]),
([        "action" : "$N跨前一步，右掌中攻直進，向$n的$l連擊三掌",
        "force" : 210,
        "attack": 15,
        "dodge" : 55,
        "parry" : 8,
        "damage": 50,
        "lvl"   : 60,
        "damage_type" : "內傷"
]),
([        "action" : "$N沉身頓氣，貫出雙掌，頓時只見一片掌影攻向$n",
        "force" : 250,
        "attack": 22,
        "dodge" : 52,
        "parry" : 0,
        "damage": 30,
        "lvl"   : 80,
        "damage_type" : "內傷"
]),
([        "action" : "$N雙掌平揮，猛擊向$n的$l，毫無半點花巧可言",
        "force" : 300,
        "attack": 23,
        "dodge" : 65,
        "parry" : 11,
        "damage": 50,
        "lvl"   : 100,
        "damage_type" : "內傷"
]),
([        "action" : "$N體內真氣迸發，雙掌繽紛拍出，頓時一片掌影籠罩$n",
        "force" : 310,
        "attack": 28,
        "dodge" : 63,
        "parry" : 5,
        "damage": 80,
        "lvl"   : 120,
        "damage_type" : "內傷"
]),
([        "action" : "$N左掌虛晃，右掌攜着千鈞之力猛然向$n的頭部擊落",
        "force" : 330,
        "attack": 25,
        "dodge" : 77,
        "damage": 90,
        "parry" : 12,
        "lvl"   : 140,
        "damage_type" : "內傷"
]),
([        "action" : "$N身子驀的橫移，右手橫掃$n的$l，左手攻向$n的胸口",
        "force" : 360,
        "attack": 31,
        "dodge" : 80,
        "parry" : 15,
        "damage": 100,
        "lvl"   : 160,
        "damage_type" : "內傷"
]),
([        "action" : "$N陡然一聲暴喝，真氣迸發，雙掌同時擊向$n的$l",
        "force" : 400,
        "attack": 32,
        "dodge" : 81,
        "parry" : 10,
        "damage": 130,
        "lvl"   : 180,
        "damage_type" : "內傷"
])
});

int valid_enable(string usage)
{
        return usage == "parry" || usage == "strike";
}

int valid_learn(object me)
{
        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("練古拙掌法必須空手。\n");

        if( query("str", me)<26 )
                return notify_fail("你先天膂力不足，無法學習淳厚的古拙掌法。\n");

        if ((int)me->query_skill("force") < 150)
                return notify_fail("你的內功火候不夠，無法練古拙掌法。\n");

        if( query("max_neili", me)<1500 )
                return notify_fail("你的內力太弱，無法練古拙掌法。\n");

        if ((int)me->query_skill("strike", 1) < 100)
                return notify_fail("你的基本掌法火候不夠，無法練古拙掌法。\n");

        if ((int)me->query_skill("strike", 1) < (int)me->query_skill("guzhuo-zhang", 1))
                return notify_fail("你的基本掌法水平有限，無法領會更高深的古拙掌法。\n");

        return 1;
}

mapping query_action(object me, object weapon)
{
        int i, level;
        level = (int) me->query_skill("guzhuo-zhang",1);
        for(i = sizeof(action); i > 0; i--)
                if(level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
        if( query("qi", me)<90 )
                return notify_fail("你的體力太低了。\n");
        if( query("neili", me)<80 )
                return notify_fail("你的內力不夠練古拙掌法。\n");

        me->receive_damage("qi", 81);
        addn("neili", -73, me);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"guzhuo-zhang/" + action;
}