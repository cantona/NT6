// This program is a part of NT MudLIB
// pili-shou.c 混元霹靂手

inherit SKILL;

mapping *action = ({
([        "action" : "$N一式「五指連心」，右掌直取$n的$l",
        "force" : 100,
        "dodge" : -15,
        "parry" : -20,
        "damage": 10,
        "lvl"   : 0,
        "skill_name" : "五指連心",
        "damage_type" : "瘀傷"
]),
([        "action" : "$N大喝一聲，一式「火上心頭」，雙掌掌力雄渾無比，連連拍向$n的$l",
        "force" : 130,
        "dodge" : -10,
        "parry" : -15,
        "damage": 20,
        "lvl"   : 30,
        "skill_name" : "火上心頭",
        "damage_type" : "瘀傷"
]),
([        "action" : "$N使一式「混元無際」，左掌虛出，右掌猛然跟進，直取$n的$l",
        "force" : 160,
        "dodge" : -20,
        "parry" : -20,
        "damage": 25,
        "lvl"   : 60,
        "skill_name" : "混元無際",
        "damage_type" : "瘀傷"
]),
([        "action" : "$N兩掌一分，一式「晴空霹靂」，隱隱帶有風雷之勢，向$n劈去",
        "force" : 180,
        "dodge" : -20,
        "parry" : -30,
        "damage": 30,
        "lvl"   : 80,
        "skill_name" : "晴空霹靂",
        "damage_type" : "瘀傷"
]),
([        "action" : "$N身形一轉，使出一式「混元刀」，但見$N右掌猶如一把利刀直下，劈向$n",
        "force" : 210,
        "dodge" : -25,
        "parry" : -20,
        "damage": 35,
        "lvl"   : 100,
        "skill_name" : "混元刀",
        "damage_type" : "瘀傷"
]),
([        "action" : "$N突然飛身而起，使出一式「霹靂雨」，雙掌連連而出，猶如暴雨般拍向$n全身",
        "force" : 250,
        "dodge" : -25,
        "parry" : -25,
        "damage": 40,
        "lvl"   : 120,
        "skill_name" : "霹靂雨",
        "damage_type" : "瘀傷"
]),
([        "action" : "$N使一式「晴空萬里」，雙掌一分，猛地劈向$n的$l",
        "force" : 290,
        "dodge" : -30,
        "parry" : -30,
        "damage": 55,
        "lvl"   : 140,
        "skill_name" : "晴空萬里",
        "damage_type" : "瘀傷"
]),
([        "action" : "$N一招「烈炎飛空」，雙掌帶着蕭瑟的烈炎之氣，拍向$n的$l",
        "force" : 330,
        "dodge" : -30,
        "parry" : -35,
        "damage": 70,
        "lvl"   : 150,
        "skill_name" : "烈炎飛空",
        "damage_type" : "瘀傷"
]),
([        "action" : "$N身法陡然一變，使出一式「混陽式」，掌影千變萬幻，令$n無法躲閃",
        "force" : 350,
        "dodge" : -40,
        "parry" : -45,
        "damage": 80,
        "lvl"   : 160,
        "skill_name" : "混陽式",
        "damage_type" : "瘀傷"
]),
([        "action" : "$N清嘯一聲，一式「雄心萬里」，雙掌揮舞，氣勢非凡，擊向$n的$l",
        "force" : 380,
        "dodge" : -45,
        "parry" : -50,
        "damage": 130,
        "lvl"   : 180,
        "skill_name" : "雄心萬里",
        "damage_type" : "瘀傷"
])
});

int valid_enable(string usage)
{
            return usage=="hand" || usage=="parry";
}

int valid_learn(object me)
{
        if (query_temp("weapon", me) || query_temp("secondary_weapon", me))
                return notify_fail("練混元霹靂手必須空手。\n");

        if ((int)me->query_skill("force") < 120)
                return notify_fail("你的內功火候不夠，無法練混元霹靂手。\n");

        if ((int)query("max_neili", me) < 900)
                return notify_fail("你的內力太弱，無法練混元霹靂手。\n");

        if ((int)me->query_skill("hand", 1) < 80)
                return notify_fail("你的基本手法火候不夠，無法練混元霹靂手。\n");

        if ((int)me->query_skill("hand", 1) < (int)me->query_skill("pili-shou", 1))
                return notify_fail("你的基本手法水平有限，無法領會更高深的混元霹靂手。\n");

        return 1;
}

string query_skill_name(int level)
{
        int i;
        for(i = sizeof(action)-1; i >= 0; i--)
                if(level >= action[i]["lvl"])
                        return action[i]["skill_name"];
}

mapping query_action(object me, object weapon)
{
        int i, level;
        level   = (int) me->query_skill("pili-shou",1);
        for(i = sizeof(action); i > 0; i--)
                if(level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
        if ((int)query("qi", me) < 80)
                return notify_fail("你的體力太低了。\n");

        if ((int)query("neili", me) < 80)
                return notify_fail("你的內力不夠練混元霹靂手。\n");

        me->receive_damage("qi", 6);
        addn("neili", -64, me);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"pili-shou/" + action;
}