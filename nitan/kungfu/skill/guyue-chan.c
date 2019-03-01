inherit SKILL;

mapping *action = ({
([      "action":"$N縱步上前，手中$w自下而上，沉猛無比地向$n的小腹挑去",
        "force" : 35,
        "attack": 8,
        "dodge" : -10,
        "parry" : 5,
        "damage": 5,
        "lvl"   : 0,
        "damage_type":"挫傷"
]),
([      "action":"$N快步跨出，左手平托$w，右掌猛推杖端，頂向$n的胸口",
        "force" : 50,
        "attack": 10,
        "dodge" : -10,
        "parry" : 8,
        "damage": 8,
        "lvl"   : 30,
        "damage_type":"挫傷"
]),
([      "action":"$N高舉$w，全身躍起，手中$w朝著$n頭蓋天靈蓋猛然擊落下去",
        "force" : 65,
        "attack": 15,
        "dodge" : -5,
        "parry" : 10,
        "damage": 12,
        "lvl"   : 60,
        "damage_type":"挫傷"
]),
([      "action":"$N雙手持杖如櫓，對準$n猛地一攪，如同平地刮起一陣旋風",
        "force" : 80,
        "attack": 18,
        "dodge" : -5,
        "parry" : 12,
        "damage": 15,
        "lvl"   : 80,
        "damage_type":"挫傷"
]),
([      "action":"$N橫持$w，杖端化出無數個圓圈，凝滯沉重，把$n纏在其中",
        "force" : 100,
        "attack": 26,
        "dodge" : -15,
        "parry" : 18,
        "damage": 20,
        "lvl"   : 100,
        "damage_type":"挫傷"
]),
([      "action":"$N全身滾倒，$w盤地橫飛，化出漫天杖影，杖影把$n裹了起來",
        "force" : 130,
        "attack": 35,
        "dodge" : 5,
        "parry" : 22,
        "damage": 27,
        "lvl"   : 120,
        "damage_type":"挫傷"
]),
([      "action":"$N雙手和十，躬身一遞出$w，只見$w自肘彎飛出，攔腰向$n撞去",
        "force" : 160,
        "attack": 40,
        "dodge" : -5,
        "parry" : 28,
        "damage": 30,
        "lvl"   : 140,
        "damage_type":"挫傷"
]),
([      "action":"$N大喝一聲，手中$w如飛龍般自掌中躍出，直向$n的胸口穿入",
        "force" : 180,
        "attack": 52,
        "dodge" : -5,
        "parry" : 35,
        "damage": 35,
        "lvl"   : 160,
        "damage_type":"挫傷"
]),
});

int valid_enable(string usage)
{
        return usage == "staff" || usage == "parry";
}

int valid_learn(object me)
{
        object weapon;

        if( !objectp(weapon=query_temp("weapon", me) )
            || query("skill_type", weapon) != "staff" )
                return notify_fail("你使用的武器不對。\n");

        if( query("max_neili", me)<400 )
                return notify_fail("你的內力修為不足，無法學習孤月鏟法。\n");

        if ((int)me->query_skill("force") < 60)
                return notify_fail("你的內功火候太淺，無法學習孤月鏟法。\n");

        if ((int)me->query_skill("staff", 1) < 20)
                return notify_fail("你的基本杖法太淺，無法學習孤月鏟法。\n");

        if ((int)me->query_skill("staff", 1) < (int)me->query_skill("poshui-zhang", 1))
                return notify_fail("你的基本杖法水平有限，無法領會更高深的孤月鏟法。\n");

        return 1;
}

string query_skill_name(int level)
{
        int i;
        for (i = sizeof(action)-1; i >= 0; i--)
                if (level >= action[i]["lvl"])
                        return action[i]["skill_name"];
}

mapping query_action(object me, object weapon)
{
        int i, level;
        level = (int)me->query_skill("guyue-chan", 1);

        for(i = sizeof(action); i > 0; i--)
                if(level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level / 5)];
}

int practice_skill(object me)
{
        object weapon;

        if( !objectp(weapon=query_temp("weapon", me) )
            || query("skill_type", weapon) != "staff" )
                return notify_fail("你使用的武器不對。\n");

        if( query("qi", me)<70 )
                return notify_fail("你的體力不夠練孤月鏟法。\n");

        if( query("neili", me)<60 )
                return notify_fail("你的內力不夠練孤月鏟法。\n");

        me->receive_damage("qi", 65);
        addn("neili", -58, me);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"guyue-chan/" + action;
}