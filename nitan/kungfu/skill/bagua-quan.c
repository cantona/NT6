inherit SKILL;

mapping *action=({
([        "action" : "$N雙掌一錯，使出「乾字決」，雙拳一上一下對準$n的$l連拍三招",
        "force" : 60,
        "attack": 20,
        "dodge" : 40,
        "parry" : 5,
        "damage": 4,
        "lvl"   : 0,
        "skill_name" : "乾字決",
        "damage_type" : "瘀傷"
]),
([        "action" : "$N繞著$n一轉，滿場遊走，拳出如風，連綿不絕地擊向$n，正是八卦拳中的「坤字決」",
        "force" : 80,
        "attack": 25,
        "dodge" : 43,
        "parry" : 6,
        "damage": 7,
        "lvl"   : 20,
        "skill_name" : "坤字決",
        "damage_type" : "瘀傷"
]),
([        "action" : "$N使出一招「巽字決」，左拳虛擊$n的前胸，一錯身，右拳迅速橫掃$n的太陽穴",
        "force" : 100,
        "attack": 28,
        "dodge" : 45,
        "parry" : 8,
        "damage": 10,
        "lvl"   : 40,
        "skill_name" : "巽字決",
        "damage_type" : "瘀傷"
]),
([        "action" : "$N使一招「坎字決」左拳擊出，不等招式使老，右拳已從左拳之底穿出，對準$n的$l「呼」地一拳",
        "force" : 120,
        "attack": 35,
        "dodge" : 47,
        "parry" : 11,
        "damage": 17,
        "lvl"   : 60,
        "skill_name" : "坎字決",
        "damage_type" : "瘀傷"
]),
([        "action" : "$N使出一招「震字決」，身形一低，左手護頂，右手已迅雷不及掩耳的一拳擊向$n的襠部",
        "force" : 140,
        "attack": 40,
        "dodge" : 49,
        "parry" : 13,
        "damage": 20,
        "lvl"   : 90,
        "skill_name" : "震字決",
        "damage_type" : "瘀傷"
]),
([        "action" : "$N左拳突然張開，拳開變掌，直擊化為橫掃，一招「兌字決」便往$n的$l招呼過去",
        "force" : 200,
        "attack": 48,
        "dodge" : 54,
        "parry" : 18,
        "damage": 28,
        "lvl"   : 120,
        "skill_name" : "兌字決",
        "damage_type" : "瘀傷"
]),
([        "action" : "$N一招「離字決」，頓時幻出重重拳影，氣勢如虹，舖天蓋地襲向$n全身",
        "force" : 280,
        "attack": 60,
        "dodge" : 63,
        "parry" : 23,
        "damage": 37,
        "lvl"   : 150,
        "skill_name" : "離字決",
        "damage_type" : "內傷"
]),
([        "action" : "$N微微一笑，手捏「艮字決」，飛身躍起，半空中一腳踢向$n面門，卻是個虛招。\n"
                   "說時遲那時快，只見$N一個倒翻，雙拳已到了$n的$l",
        "force" : 290,
        "attack": 62,
        "dodge" : 65,
        "parry" : 25,
        "damage": 40,
        "lvl"   : 180,
        "skill_name" : "艮字決",
        "damage_type" : "內傷"
]),
});

int valid_enable(string usage)
{
        return usage == "cuff" || usage == "parry";
}

int valid_combine(string combo)
{
        return combo == "bagua-zhang";
}

int valid_learn(object me)
{
        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("練八卦拳必須空手。\n");

        if( query("max_neili", me)<150 )
                return notify_fail("你的內力不夠，無法練習八卦拳。\n");

        if ((int)me->query_skill("cuff", 1) < (int)me->query_skill("bagua-quan", 1))
                return notify_fail("你的基本拳法火候有限，無法領會更高深的八卦拳。\n");

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
        level = (int)me->query_skill("bagua-quan", 1);
        for (i = sizeof(action); i > 0; i--)
                if (level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
        if( query("qi", me)<70 )
                return notify_fail("你現在手足酸軟，休息一下再練吧。\n");

        if( query("neili", me)<60 )
                return notify_fail("你的內力不夠了。\n");

        me->receive_damage("qi", 65);
        addn("neili", -40, me);

        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"bagua-quan/" + action;
}