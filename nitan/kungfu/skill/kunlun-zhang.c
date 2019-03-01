inherit SKILL;

mapping *action = ({
([      "action": "$N雙掌驟起，一招「天清雲淡」，一掌擊向$n面門，另一掌卻按向$n小腹",
        "force" : 73,
        "dodge" : 11,
        "parry" : 12,
        "attack": 9,
        "damage": 12,
        "lvl"   : 0,
        "skill_name" : "天清雲淡",
        "damage_type": "瘀傷"
]),
([      "action": "$N雙掌互錯，變幻莫測，一招「秋風不盡」，瞬息之間向$n攻出了四四一十六招",
        "force" : 95,
        "dodge" : 18,
        "parry" : 17,
        "attack": 13,
        "damage": 17,
        "lvl"   : 20,
        "skill_name" : "秋風不盡",
        "damage_type": "瘀傷"
]),
([      "action": "$N一聲清嘯，呼的一掌，一招「山回路轉」，去勢奇快，向$n的$l猛擊過去，",
        "force" : 127,
        "dodge" : 16,
        "parry" : 19,
        "attack": 17,
        "damage": 21,
        "lvl"   : 40,
        "skill_name" : "山回路轉",
        "damage_type": "瘀傷"
]),
([      "action": "$N雙掌交錯，若有若無，一招「天衣無縫」，自巧轉拙，拍向$n的$l",
        "force" : 145,
        "dodge" : 24,
        "parry" : 21,
        "attack": 22,
        "damage": 33,
        "lvl"   : 60,
        "skill_name" : "天衣無縫",
        "damage_type": "瘀傷"
]),
([      "action": "$N一招「青山斷河」，右手一拳擊出，左掌緊跟著在右拳上一搭，變成雙掌下劈，擊向$n的$l",
        "force" : 185,
        "dodge" : 24,
        "parry" : 28,
        "attack": 33,
        "damage": 41,
        "lvl"   : 80,
        "skill_name" : "青山斷河",
        "damage_type": "瘀傷"
]),
([      "action": "$N雙手齊劃，跟著雙掌齊推，一招「北風卷地」，一股排山倒海的掌力，直撲$n面門",
        "force" : 197,
        "dodge" : 28,
        "parry" : 30,
        "attack": 36,
        "damage": 49,
        "lvl"   : 100,
        "skill_name" : "北風卷地",
        "damage_type": "瘀傷"
]),
([      "action": "$N突然滴溜溜的轉身，一招「天山雪飄」，掌影飛舞，霎時之間將$n四面八方都裹住了",
        "force" : 210,
        "dodge" : 24,
        "parry" : 21,
        "attack": 37,
        "damage": 51,
        "lvl"   : 120,
        "skill_name" : "天山雪飄",
        "damage_type": "瘀傷"
]),
([      "action": "$N仰天大笑，勢若瘋狂，衣袍飛舞，一招「群山疊影」，掌風凌厲，如雨點般向$n打去",
        "force" : 220,
        "dodge" : 36,
        "parry" : 35,
        "attack": 41,
        "damage": 58,
        "lvl"   : 140,
        "skill_name" : "群山疊影",
        "damage_type": "瘀傷"
]),
});

int valid_enable(string usage) { return usage == "strike" || usage == "parry"; }

int valid_combine(string combo)
{
        return combo == "zhentian-quan" || combo == "sanyin-shou";
}

int valid_learn(object me)
{
        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("練昆侖掌法必須空手。\n");

        if ((int)me->query_skill("force") < 30)
                return notify_fail("你的內功火候不夠，無法學昆侖掌法。\n");

        if( query("max_neili", me)<100 )
                return notify_fail("你的內力太弱，無法練昆侖掌法。\n");

        if ((int)me->query_skill("strike", 1) < 80)
                return notify_fail("你的基本掌法火候太淺。\n");

        if ((int)me->query_skill("strike", 1) < (int)me->query_skill("kunlun-zhang", 1))
                return notify_fail("你的基本掌法水平有限，無法領會更高深的昆侖掌法。\n");

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
        level = (int) me->query_skill("kunlun-zhang", 1);
        for (i = sizeof(action); i > 0; i--)
            if (level > action[i-1]["lvl"])
                return action[NewRandom(i, 5, level / 5)];
}

int practice_skill(object me)
{
        if( query("qi", me)<80 )
                return notify_fail("你的體力太低了。\n");

        if( query("neili", me)<80 )
                return notify_fail("你的內力不夠練昆侖掌法。\n");

        me->receive_damage("qi", 55);
        addn("neili", -45, me);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"kunlun-zhang/" + action;
}