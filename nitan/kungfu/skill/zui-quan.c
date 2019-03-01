inherit SKILL;

mapping *action = ({
([      "action": "$N連續上步，腳下蹣跚，雙拳緩緩劃向$n的$l",
        "force" : 80,
        "attack": 12,
        "parry" : 14,
        "dodge" : 5,
        "lvl"   : 0,
        "damage_type" : "瘀傷"
]),
([      "action": "$N左腳虛踏，全身右轉，擺姿扭腰，右臂順勢猛地掃向$n的$l",
        "force" : 100,
        "attack": 15,
        "parry" : 16,
        "dodge" : 10,
        "lvl"   : 8,
        "damage_type" : "瘀傷"
]),
([      "action": "$N身子往前一晃，伸出雙掌，指天打地，猛的向$n的$l劈去",
        "force" : 120,
        "attack": 18,
        "parry" : 19,
        "dodge" : 5,
        "lvl"   : 15,
        "damage_type" : "瘀傷"
]),
([      "action": "$N腳下一個不穩，身子頓時向前一傾，雙掌順勢拍出，如閃電一般切向$n",
        "force" : 170,
        "attack": 23,
        "parry" : 24,
        "dodge" : 10,
        "lvl"   : 42,
        "damage_type" : "瘀傷"
]),
([      "action": "$N搖搖晃晃，偏偏倒倒，可雙拳卻拳出如風，籠罩著$n頭，胸，腹三處要害",
        "force" : 200,
        "attack": 25,
        "parry" : 24,
        "dodge" : 5,
        "lvl"   : 50,
        "damage_type" : "瘀傷"
]),
([      "action": "$N醉眼朦朧，但卻舉重若輕，一聲大喝，噴出一口酒氣，單掌挾千鈞之力拍向$n",
        "force" : 210,
        "attack": 28,
        "parry" : 25,
        "dodge" : 10,
        "lvl"   : 58,
        "damage_type" : "瘀傷"
]),
});

int valid_enable(string usage)
{
        return usage == "cuff" || usage == "unarmed" || usage == "parry";
}

int valid_learn(object me)
{
        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("練醉拳三打必須空手。\n");

        if ((int)me->query_skill("force") < 20)
                return notify_fail("你的內功火候不夠，無法學醉拳三打。\n");

        if( query("max_neili", me)<50 )
                return notify_fail("你的內力太弱，無法練醉拳三打。\n");

        if (me->query_skill("unarmed", 1) < me->query_skill("zui-quan", 1)
           && me->query_skill("cuff", 1) < me->query_skill("zui-quan", 1))
                return notify_fail("你拳腳與拳法均火候不足，無法領會更高"
                                   "深的醉拳三打。\n");

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
        level = (int) me->query_skill("zui-quan", 1);
        for (i = sizeof(action); i > 0; i--)
                if (level > action[i - 1]["lvl"])
                        return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
        if( query_temp("weapon", me) || 
            query_temp("secondary_weapon", me) )
                return notify_fail("你必須空手練習！\n");

        if( query("qi", me)<35 )
                return notify_fail("你的體力太低了。\n");

        if( query("neili", me)<30 )
                return notify_fail("你的內力不夠了。\n");

        me->receive_damage("qi", 25);
        addn("neili", -20, me);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__ "zui-quan/" + action;
}
