inherit SKILL;

mapping *action = ({
([      "action": "只見$N飛身一縱，一招「燕子渡水」凌空一拳打向$n的$l",
        "dodge": 15,
        "parry": 15,
        "attack": 20,
        "force": 120,
        "damage_type":  "砸傷"
]),
([      "action": "$N步履一沉，左拳拉開，右拳帶風，一招「燕尾手」勢不可擋地擊向$n$l",
        "dodge": 25,
        "parry": 25,
        "attack": 30,
        "force": 140,
        "damage_type":  "瘀傷"
]),
([      "action": "只見$N拉開架式，一招「掠水掌」使得虎虎有風。底下卻飛起一腳踢向$n$l",
        "dodge": 20,
        "parry": 20,
        "attack": 25,
        "force": 160,
        "damage_type":  "瘀傷"
]),
([      "action": "$N一個轉身，左掌護胸，右掌使了個「百花齊放」往$n當頭一拳",
        "dodge": 30,
        "parry": 30,
        "attack": 40,
        "force": 270,
        "damage_type":  "砸傷"
]),
([      "action": "只見$N拉開架式，一招「平推掌」使得虎虎有風，數只手掌一齊擊向$n的$l",
        "dodge": 20,
        "parry": 20,
        "attack": 25,
        "force": 160,
        "damage_type":  "瘀傷"
]),
([      "action": "$N一個轉身，左掌護胸，右掌使了個「燕青逸翔」往$n當頭拂過",
        "dodge": 30,
        "parry": 30,
        "attack": 40,
        "force": 270,
        "damage_type":  "砸傷"
]),
});

string main_skill() { return "baihua-cuoquan"; }

int valid_learn(object me)
{
        if (me->query_skill("baihua-cuoquan", 1) > 0)
                return notify_fail("你已經練成了百花錯拳，不必再單獨學習了。\n");

        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("練燕青拳必須空手。\n");

        if ((int)me->query_skill("unarmed", 1) < (int)me->query_skill("yanqing-quan", 1))
                return notify_fail("你的基本拳腳火候不足，無法領會更高深的燕青拳。\n");

        if ((int)me->query_skill("cuff", 1) < (int)me->query_skill("yanqing-quan", 1))
                return notify_fail("你的拳法根基火候不足，無法領會更高深的燕青拳。\n");

        return 1;
}

int valid_enable(string usage)
{
        return usage == "cuff" || usage=="unarmed" || usage=="parry";
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
        return __DIR__"yanqing-quan/" + action;
}