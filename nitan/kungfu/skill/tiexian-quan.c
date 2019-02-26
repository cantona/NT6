inherit SKILL;

mapping *action = ({
([      "action" : "只見$N身形一矮，施一招「赤膽忠心」對準$n的呼地砸了過去",
        "dodge"  : 15,
        "parry"  : 15,
        "attack" : 20,
        "force"  : 120,
        "damage_type":  "砸傷"
]),
([      "action" : "$N左拳拉開，右拳帶風，一招「忠心耿耿」勢不可擋地擊向$n",
        "dodge"  : 25,
        "parry"  : 25,
        "attack" : 30,
        "force"  : 140,
        "damage_type":  "瘀傷"
]),
([      "action" : "只見$N拉開架式，雙拳帶風，施一招「鐵門閘」驀地拍向$n而去",
        "dodge"  : 20,
        "parry"  : 20,
        "attack" : 25,
        "force"  : 160,
        "damage_type" : "瘀傷"
]),
([      "action" : "$N一個轉身，左掌護胸，右掌使出「直來直去」往$n當頭一拳",
        "dodge"  : 30,
        "parry"  : 30,
        "attack" : 40,
        "force"  : 270,
        "damage_type" : "砸傷"
]),
});

int valid_enable(string usage)
{
        return usage == "cuff" || usage == "parry";
}

int valid_combine(string combo)
{
        return combo == "chuanxin-zhang";
}

int valid_learn(object me)
{
        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("練鐵線拳法必須空手。\n");

        if ((int)me->query_skill("cuff", 1) < 20)
                return notify_fail("你的基本拳法火候不足，難以修煉鐵線拳法。\n");

        if ((int)me->query_skill("cuff", 1) < (int)me->query_skill("tiexian-quan", 1))
                return notify_fail("你的拳法根基火候不足，無法領會更高深的鐵線拳法。\n");

        return 1;
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
        if( query("qi", me)<40 )
                return notify_fail("你現在手足痠軟，休息一下再練吧。\n");

        if( query("neili", me)<25 )
                return notify_fail("你的內力不夠了。\n");

        me->receive_damage("qi", 35);
        addn("neili", -22, me);

        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"tiexian-quan/" + action;
}