// youshen-zhang.c 遊身八卦掌

inherit SKILL;

string *dodge_msg = ({
        "$n身形微微一晃，輕飄飄拍出一掌，借力一晃，身形已落至$N十步之外。\n",
        "$n遊身穿梭，單掌飄忽不定，繽紛拍出，將$N的攻勢全部擋回，只能自保。\n",
        "$n雙足輕輕點地，猛的拔地而起，躲開了$N的招式。\n",
});

mapping *action = ({
([      "action" : "$N身形遊走不定，在$n身旁圍繞數圈，陡然間“呼”的一掌向$n$l劈落",
        "force" : 260,
        "attack": 40,
        "dodge" : 90,
        "parry" : 90,
        "damage": 30,
        "lvl"   : 0,
        "damage_type" : "瘀傷",
]),
([      "action" : "$N身形一展，已然拔地而起，雙掌繽紛拍出數掌，盡數攻向$n的$l",
        "force" : 290,
        "attack": 40,
        "dodge" : 100,
        "parry" : 100,
        "damage": 30,
        "lvl"   : 60,
        "damage_type" : "瘀傷",
]),
([      "action" : "$N抽身躍起，退後數步，陡然間卻又疾身而上，朝著$n的$l處猛拍一掌",
        "force" : 320,
        "attack": 45,
        "dodge" : 115,
        "parry" : 115,
        "damage": 35,
        "lvl"   : 120,
        "damage_type" : "瘀傷",
]),
});

int valid_enable(string usage) { return usage == "unarmed" ||  usage == "parry" ||  usage == "dodge"; } 

int valid_learn(object me)
{
        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("學習遊身八卦掌必須空手。\n");

        if ((int)me->query_skill("force") < 100)
                return notify_fail("你的內功火候不夠，無法學遊身八卦掌。\n");

        if ((int)me->query_skill("dodge", 1) < 80)
                return notify_fail("你的基本輕功火候不夠，無法學遊身八卦掌。\n");

        if ((int)me->query_skill("unarmed", 1) < 80)
                return notify_fail("你的基本拳腳火候不夠，無法學遊身八卦掌。\n");

        if( query("max_neili", me)<800 )
                return notify_fail("你的內力太弱，無法練遊身八卦掌。\n");

        if ((int)me->query_skill("unarmed", 1) < (int)me->query_skill("youshen-zhang", 1))
                return notify_fail("你的基本拳腳水平有限，無法領會更高深的遊身八卦掌。\n");

        if ((int)me->query_skill("dodge", 1) < (int)me->query_skill("youshen-zhang", 1))
                return notify_fail("你的基本輕功水平有限，無法領會更高深的遊身八卦掌。\n");

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
        level = (int)me->query_skill("youshen-zhang", 1);
        for(i = sizeof(action); i > 0; i--)
            if(level > action[i-1]["lvl"])
                return action[NewRandom(i, 20, level/5)];
}

string query_dodge_msg(string limb)
{
        return dodge_msg[random(sizeof(dodge_msg))];
}

int practice_skill(object me)
{
        if( query("qi", me)<100 )
               return notify_fail("你的體力太低了。\n");

        if( query("neili", me)<80 )
               return notify_fail("你的內力不夠遊身八卦掌。\n");

        me->receive_damage("qi", 80);
        addn("neili", -60, me);

        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"youshen-zhang/" + action;
}