inherit SKILL;

mapping *action = ({
([      "action": "在呼呼風聲中，$N使一招「虎口奪食」，雙手如鉤如戢，插向$n的$l",
        "force" : 60,
        "dodge" : 17,
        "parry" : 1,
        "damage": 1,
        "damage_type" : "抓傷",
        "skill_name" : "虎口奪食",
]),
([      "action": "$N身形一躍，費神撲上，使出一招「餓虎撲食」，右手直直抓向$n的$l",
        "force" : 80,
        "dodge" : 20,
        "parry" : 5,
        "damage": 3,
        "damage_type" : "抓傷",
        "skill_name" : "餓虎撲食",
]),
([      "action": "$N雙手平伸，十指微微上下抖動，一招「山崩地裂」打向$n的$l",
        "force" : 120,
        "dodge" : 32,
        "parry" : 10,
        "damage": 5,
        "damage_type" : "抓傷",
        "skill_name" : "山崩地裂",
]),
([      "action": "$N使出一招「夜黑風高」，悄無聲息的遊走至$n身前，猛的一爪奮力抓向$n的$l",
        "force" : 132,
        "dodge" : 38,
        "parry" : 19,
        "damage": 5,
        "damage_type" : "抓傷",
        "skill_name" : "夜黑風高",
]),
([      "action": "$N雙手平提胸前，左手護住面門，一招「損筋斷骨」右手推向$n的$l",
        "force" : 137,
        "dodge" : 41,
        "parry" : 21,
        "damage": 7,
        "damage_type" : "抓傷",
        "skill_name" : "損筋斷骨",
]),
([      "action": "$N使出「惡林虎嘯」，低喝一聲，雙手化掌為爪，一前一後抓向$n的$l",
        "force" : 143,
        "dodge" : 49,
        "parry" : 22,
        "damage": 9,
        "damage_type" : "抓傷",
        "skill_name" : "惡林虎嘯",
]),
([      "action": "$N使出「困獸猶鬥」，雙爪如狂風驟雨般對準$n的$l連續抓出",
        "force" : 151,
        "dodge" : 58,
        "parry" : 38,
        "damage": 15,
        "damage_type" : "抓傷",
        "skill_name" : "困獸猶鬥",
])
});

string main_skill() { return "baihua-cuoquan"; }

int valid_learn(object me)
{
        if (me->query_skill("baihua-cuoquan", 1) > 0)
                return notify_fail("你已經練成了百花錯拳，不必再單獨學習了。\n");

        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("練虎爪手必須空手。\n");

        if ((int)me->query_skill("claw", 1) < (int)me->query_skill("huzhao-shou", 1))
                return notify_fail("你的基本爪法火候不足，無法領會更高深的虎爪手。\n");

        return 1;
}

int valid_enable(string usage)
{
        return usage == "claw" || usage=="parry";
}

string query_skill_name(int level)
{
        int i;
        for (i = sizeof(action); i > 0; i--)
                if (level >= action[i-1]["lvl"])
                        return action[i-1]["skill_name"];
}

mapping query_action(object me, object weapon)
{
        int i, level;
        level = (int) me->query_skill("huzhao-shou",1);
        for (i = sizeof(action); i > 0; i--)
                if (level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level/5)];

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
        return __DIR__"huzhao-shou/" + action;
}
