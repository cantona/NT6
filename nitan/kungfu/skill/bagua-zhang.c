inherit SKILL;

mapping *action=({
([        "action" : "$N左肩低，右肩高，左手斜，右手正，一式「懷中抱月」，雙掌疾推向$n的肩頭",
        "force" : 60,
        "attack": 5,
        "dodge" : 40,
        "parry" : 5,
        "damage": 2,
        "lvl"   : 0,
        "skill_name" : "懷中抱月",
        "damage_type" : "瘀傷"
]),
([        "action" : "$N先退又進，使招「猛虎伏樁」，左掌切向$n的$l，跟著右掌變拳，直擊他前胸",
        "force" : 80,
        "attack": 11,
        "dodge" : 43,
        "parry" : 6,
        "damage": 7,
        "lvl"   : 20,
        "skill_name" : "猛虎伏樁",
        "damage_type" : "瘀傷"
]),
([        "action" : "$N身法陡然一變，使出一式「沉肘擒拿」，掌影千變萬幻，令$n無法躲閃",
        "force" : 100,
        "attack": 8,
        "dodge" : 45,
        "parry" : 8,
        "damage": 6,
        "lvl"   : 40,
        "skill_name" : "沉肘擒拿",
        "damage_type" : "瘀傷"
]),
([        "action" : "$N左掌向外一穿，右掌「遊空探爪」斜劈，對準$n的$l拍出一排掌影，隱隱帶著風聲",
        "force" : 120,
        "attack": 15,
        "dodge" : 47,
        "parry" : 11,
        "damage": 11,
        "lvl"   : 60,
        "skill_name" : "遊空探爪",
        "damage_type" : "瘀傷"
]),
([        "action" : "$N左掌畫了個圈圈，暗藏諸多變化，右掌推出，一招「金龍抓爪」直取$n的$l",
        "force" : 140,
        "attack": 24,
        "dodge" : 49,
        "parry" : 13,
        "damage": 15,
        "lvl"   : 90,
        "skill_name" : "金龍抓爪",
        "damage_type" : "瘀傷"
]),
([        "action" : "$N左掌突然張開，變掌為爪，直擊化為橫掃，一招「遁甲擒蹤」便往$n的$l招呼過去",
        "force" : 160,
        "attack": 28,
        "dodge" : 54,
        "parry" : 18,
        "damage": 18,
        "lvl"   : 120,
        "skill_name" : "遁甲擒蹤",
        "damage_type" : "瘀傷"
]),
([        "action" : "$N使出「劈雷墜地」，身形凌空飛起，從空中當頭向$n的$l出掌攻擊",
        "force" : 190,
        "attack": 31,
        "dodge" : 53,
        "parry" : 23,
        "damage": 15,
        "lvl"   : 150,
        "skill_name" : "劈雷墜地",
        "damage_type" : "內傷"
]),
([        "action" : "$N前腿踢出，後腿腳尖點地，一式「雙打奇門」，二掌直出，雙雙攻向$n的上中下三路",
        "force" : 210,
        "attack": 33,
        "dodge" : 55,
        "parry" : 25,
        "damage": 13,
        "lvl"   : 180,
        "skill_name" : "雙打奇門",
        "damage_type" : "內傷"
]),
});

int valid_enable(string usage)
{
        return usage == "strike" || usage == "parry";
}

int valid_combine(string combo)
{
        return combo == "bagua-quan";
}

string main_skill() { return "baihua-cuoquan"; }

int valid_learn(object me)
{
        if (me->query_skill("baihua-cuoquan", 1) > 0)
                return notify_fail("你已經練成了百花錯拳，不必再單獨學習了。\n");

        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("練八卦掌必須空手。\n");

        if( query("max_neili", me)<150 )
                return notify_fail("你的內力不夠，無法練習八卦掌。\n");

        if ((int)me->query_skill("strike", 1) < (int)me->query_skill("bagua-zhang", 1))
                return notify_fail("你的基本掌法火候有限，無法領會更高深的八卦掌。\n");

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
        level = (int)me->query_skill("bagua-zhang", 1);
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
        return __DIR__"bagua-zhang/" + action;
}