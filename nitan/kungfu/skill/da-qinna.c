inherit SKILL;

mapping *action = ({
([      "action": "在呼呼風聲中，$N飛身一躍，雙手如鉤如戢，插向$n的$l",
        "force" : 60,
        "dodge" : 17,
        "parry" : 1,
        "damage": 1,
        "damage_type" : "抓傷"
]),
([      "action": "$N雙手平提胸前，左手護住面門，右手猛然抓向$n的$l",
        "force" : 137,
        "dodge" : 41,
        "parry" : 21,
        "damage": 7,
        "damage_type" : "抓傷"
]),
([      "action": "$N低喝一聲，雙手化掌為爪，一前一後抓向$n的$l",
        "force" : 143,
        "dodge" : 49,
        "parry" : 22,
        "damage": 9,
        "damage_type" : "抓傷"
]),
([      "action": "$N跨前一步，雙爪如狂風驟雨般對準$n的$l連續抓出",
        "force" : 151,
        "dodge" : 58,
        "parry" : 38,
        "damage": 15,
        "damage_type" : "抓傷"
])
});

string main_skill() { return "baihua-cuoquan"; }

int valid_learn(object me)
{
        if (me->query_skill("baihua-cuoquan", 1) > 0)
                return notify_fail("你已經練成了百花錯拳，不必再單獨學習了。\n");

        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("練大擒拿手必須空手。\n");

        if ((int)me->query_skill("claw", 1) < (int)me->query_skill("da-qinna", 1))
                return notify_fail("你的基本爪法火候不足，無法領會更高深的大擒拿手。\n");

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
        return __DIR__"da-qinna/" + action;
}