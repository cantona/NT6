inherit SKILL;

mapping *action = ({
([      "action": "在呼呼風聲中，$N飛身一躍，雙手如鉤如戢，插向$n的$l",
        "force" : 60,
        "dodge" : 17,
        "parry" : 1,
        "damage": 1,
        "damage_type" : "抓傷"
]),
([      "action": "$N身形一躍，飛身撲上，右手直直抓向$n的$l",
        "force" : 80,
        "dodge" : 20,
        "parry" : 5,
        "damage": 3,
        "damage_type" : "抓傷"
]),
([      "action": "$N雙手平伸，十指微微上下抖動，雙手齊抓向$n的$l",    
        "force" : 120,
        "dodge" : 32,
        "parry" : 10,
        "damage": 5,
        "damage_type" : "抓傷"
]),
([      "action": "$N悄無聲息的遊走至$n身前，猛的一爪奮力抓向$n的$l",
        "force" : 132,
        "dodge" : 38,
        "parry" : 19,
        "damage": 5,
        "damage_type" : "抓傷"
]),
});

string main_skill() { return "baihua-cuoquan"; }

int valid_learn(object me)
{
        if (me->query_skill("baihua-cuoquan", 1) > 0)
                return notify_fail("你已經練成了百花錯拳，不必再單獨學習了。\n");

        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("練小擒拿手必須空手。\n");

        if ((int)me->query_skill("claw", 1) < (int)me->query_skill("xiao-qinna", 1))
                return notify_fail("你的基本爪法火候不足，無法領會更高深的小擒拿手。\n");

        return 1;
}

int valid_enable(string usage)
{
        return usage == "claw" || usage=="parry";
}

string query_skill_name(int lvl)
{
        return action[random(sizeof(action))]["skill_name"];
}

mapping query_action(object me, object weapon)
{
        return action[random(sizeof(action))];
}

int practice_skill(object me)
{
        if( query("qi", me)<100 )
                return notify_fail("你現在手足酸軟，休息一下再練吧。\n");

        if( query("neili", me)<80 )
                return notify_fail("你的內力不夠了。\n");

        me->receive_damage("qi", 80);
        addn("neili", -50, me);

        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"xiao-qinna/" + action;
}