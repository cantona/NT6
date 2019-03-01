// 杜撰的苗家掌法，招數名稱與其劍法相近

inherit SKILL;

mapping *action = ({
([      "action": "$N雙掌驟起，一招「下步摘星勢」，一掌擊向$n面門，另一掌卻按向$n小腹",
        "force" : 185,
        "dodge" : 11,
        "parry" : 12,
        "attack": 9,
        "damage": 12,
        "lvl"   : 0,
        "skill_name" : "下步摘星勢",
        "damage_type": "瘀傷"
]),
([      "action": "$N雙掌互錯，變幻莫測，一招「洗劍懷中抱月」，瞬息之間已向$n攻出數掌",
        "force" : 205,
        "dodge" : 18,
        "parry" : 17,
        "attack": 13,
        "damage": 17,
        "lvl"   : 30,
        "skill_name" : "洗劍懷中抱月",
        "damage_type": "瘀傷"
]),
([      "action": "$N一聲清嘯，呼的一掌，一招「黃龍轉身吐須」，去勢奇快，向$n猛擊過去",
        "force" : 217,
        "dodge" : 16,
        "parry" : 19,
        "attack": 17,
        "damage": 21,
        "lvl"   : 60,
        "skill_name" : "黃龍轉身吐須",
        "damage_type": "瘀傷"
]),
([      "action": "$N雙掌交錯，若有若無，一招「上步雲邊摘月」，自巧轉拙，拍向$n的$l",
        "force" : 225,
        "dodge" : 24,
        "parry" : 21,
        "attack": 22,
        "damage": 33,
        "lvl"   : 90,
        "skill_name" : "上步雲邊摘月",
        "damage_type": "瘀傷"
]),
([      "action": "$N一招「提撩劍白鶴舒翅」，右手一拳擊出，左掌緊跟著在右拳順勢擊向$n的$l",
        "force" : 255,
        "dodge" : 24,
        "parry" : 28,
        "attack": 33,
        "damage": 41,
        "lvl"   : 120,
        "skill_name" : "提撩劍白鶴舒翅",
        "damage_type": "瘀傷"
]),
([      "action": "$N雙手齊劃，跟著雙掌齊推，一招「沖天掌蘇秦背劍」，一股排山般掌力直撲$n",
        "force" : 267,
        "dodge" : 28,
        "parry" : 30,
        "attack": 36,
        "damage": 49,
        "lvl"   : 150,
        "skill_name" : "沖天掌蘇秦背劍",
        "damage_type": "瘀傷"
]),
});

int valid_enable(string usage) { return usage == "strike" || usage == "parry"; }

int valid_combine(string combo) { return combo == "panlong-zhao"; }

int valid_learn(object me)
{
        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("練白鶴沖天掌必須空手。\n");

        if ((int)me->query_skill("force") < 100)
                return notify_fail("你的內功火候不夠，無法學白鶴沖天掌。\n");

        if( query("max_neili", me)<800 )
                return notify_fail("你的內力太弱，無法練白鶴沖天掌。\n");

        if ((int)me->query_skill("strike", 1) < 60)
                return notify_fail("你的基本掌法火候太淺。\n");

        if ((int)me->query_skill("strike", 1) < (int)me->query_skill("chongtian-zhang", 1))
                return notify_fail("你的基本掌法水平有限，無法領會更高深的白鶴沖天掌。\n");

        return 1;
}

string query_skill_name(int level)
{
        int i;
        for (i = sizeof(action) - 1; i >= 0; i--)
            if (level >= action[i]["lvl"])
                return action[i]["skill_name"];
}

mapping query_action(object me, object weapon)
{
        int i, level;
        level = (int) me->query_skill("chongtian-zhang", 1);
        for (i = sizeof(action); i > 0; i--)
            if (level > action[i-1]["lvl"])
                return action[NewRandom(i, 5, level / 5)];
}

int practice_skill(object me)
{
        if( query("qi", me)<80 )
                return notify_fail("你的體力太低了。\n");

        if( query("neili", me)<100 )
                return notify_fail("你的內力不夠練白鶴沖天掌。\n");

        me->receive_damage("qi", 55);
        addn("neili", -90, me);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"chongtian-zhang/" + action;
}