// pona-gong.c
inherit SHAOLIN_SKILL;

mapping *action = ({
([        "action" : "$N一式「起手式」，身體右甩，屈肘反切，雙拳蓄勢而發，擊向$n的$l",
        "force" : 180,
        "dodge" : -5,
        "parry" : -2,
        "lvl" : 0,
        "skill_name" : "起手式",
        "damage_type" : "瘀傷"
]),
([        "action" : "$N一式「石破天驚」，左掌向上，右掌向下，拳風□啪爆響，一股勁力直沖$n的$l",
        "force" : 200,
        "dodge" : 5,
        "parry" : 0,
        "damage": 10,
        "lvl" : 9,
        "skill_name" : "石破驚天",
        "damage_type" : "瘀傷"
]),
([        "action" : "$N全身提氣，騰空飛起，一式「鐵閂橫門」，雙拳雙腿齊出，來勢洶洶，令$n無可躲藏",
        "force" : 230,
        "dodge" : 15,
        "parry" : 10,
        "damage": 10,
        "lvl" : 29,
        "skill_name" : "鐵閂橫門",
        "damage_type" : "瘀傷"
]),
([        "action" : "$N神情凝重，雙掌虛含，掌緣下沉，大喝一聲，一式「千斤墜地」，緩緩向$n推出",
        "force" : 270,
        "dodge" : 5,
        "parry" : 15,
        "damage": 20,
        "lvl" : 39,
        "skill_name" : "千斤墜地",
        "damage_type" : "瘀傷"
]),
([        "action" : "$N一臂前伸，一臂後指，一式「傍花拂柳」，身行急閃直$n身前，攻向$n的$l",
        "force" : 320,
        "dodge" : 10,
        "parry" : 5,
        "damage": 15,
        "lvl" : 49,
        "skill_name" : "傍花拂柳",
        "damage_type" : "瘀傷"
]),
([        "action" : "$N一式「金剛摯尾」，右拳由下至上，左拳從左到右，迅雷不及掩耳之勢雙雙擊向$n的$l",
        "force" : 380,
        "dodge" : 25,
        "parry" : -5,
        "damage": 25,
        "lvl" : 59,
        "skill_name" : "金剛摯尾",
        "damage_type" : "瘀傷"
]),
([        "action" : "$N兩目內視，雙手內籠，一式「封閉手」，雙拳打向$n，只見$n躲閃過去，又擊向$n的$l",
        "force" : 420,
        "dodge" : 15,
        "parry" : 0,
        "damage": 35,
        "lvl" : 69,
        "skill_name" : "封閉手",
        "damage_type" : "瘀傷"
]),
([        "action" : "$N調整內息，緊握雙拳，一式「粉石碎玉」，全身發出暴豆般的響聲，用盡全身力量擊向$n的$l",
        "force" : 480,
        "dodge" : 20,
        "parry" : 10,
        "damage": 50,
        "lvl" : 80,
        "skill_name" : "粉石碎玉",
        "damage_type" : "瘀傷"
])
});

int valid_enable(string usage) { return  usage=="unarmed" || usage=="parry"; }
int valid_combine(string combo) { return combo=="hunyuan-zhang"; }
int valid_learn(object me)
{
        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
        return notify_fail("練破衲功須空手。\n");

        if ((int)me->query_skill("force") < 150) 
                return notify_fail("你的內功火候不夠，無法學破衲功。\n"); 

    if( query("max_neili", me)<1500 )
        return notify_fail("你的內力太弱，無法練破衲功。\n");
        return 1;
}


mapping query_action(object me, object weapon)
{
        int i, level;
        level   = (int)me->query_skill("pona-gong",1);
        for(i = sizeof(action); i > 0; i--)
                if(level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
        if( query("qi", me)<30 )
        return notify_fail("你的體力太低了。\n");

        if( query("neili", me)<20 )
        return notify_fail("你的內力不夠練破衲功。\n");
        me->receive_damage("qi", 30);
        addn("neili", -10, me);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"pona-gong/" + action;
}