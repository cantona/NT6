inherit SKILL;

mapping *action = ({
([        "action" : "$N跨前一步，一式「寒月初升」，單手一拂而過，拍向$n的$l",
        "force" : 70,
        "attack": 5,
        "dodge" : 38,
        "parry" : 38,
        "damage": 1,
        "lvl"   : 0,
        "skill_name" : "寒月初升",
        "damage_type" : "瘀傷"
]),
([        "action" : "$N一式「雲霧茫茫」，雙手繽紛拍出，同時擊向$n的胸前幾大要穴",
        "force" : 95,
        "attack": 8,
        "dodge" : 43,
        "parry" : 43,
        "damage": 4,
        "lvl"   : 20,
        "skill_name" : "雲霧茫茫",
        "damage_type" : "瘀傷"
]),
([        "action" : "$N使一式「天際排雲」，雙掌紛飛，連續拍出，掌影向$n層層推進",
        "force" : 120,
        "attack": 13,
        "dodge" : 51,
        "parry" : 51,
        "damage": 8,
        "lvl"   : 40,
        "skill_name" : "天際排雲",
        "damage_type" : "瘀傷"
]),
([        "action" : "$N一式「平步青雲」，單手一揮，手影虛虛實實，難辨真偽，完全籠罩$n",
        "force" : 140,
        "attack": 15,
        "dodge" : 65,
        "parry" : 65,
        "damage": 12,
        "lvl"   : 60,
        "skill_name" : "平步青雲",
        "damage_type" : "瘀傷"
]),
});

int valid_enable(string usage) { return usage == "hand" ||  usage == "parry"; }

int valid_combine(string combo) { return combo=="panyang-zhang"; }

int valid_learn(object me)
{
        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("練青雲手必須空手。\n");

        if (me->query_skill("force") < 20)
                return notify_fail("你的內功火候不夠，不能練青雲手。\n");

        if( query("max_neili", me)<50 )
                return notify_fail("你的內力太弱，無法練青雲手。\n");

        if (me->query_skill("hand", 1) < me->query_skill("qingyun-shou", 1))
                return notify_fail("你的基本手法太差，無法領會更高深的青雲手。\n");

        return 1;
}

string query_skill_name(int level)
{
        int i;
        for(i = sizeof(action)-1; i >= 0; i--)
                if(level >= action[i-1]["lvl"])
                        return action[i-1]["skill_name"];
}

mapping query_action(object me, object weapon)
{
        int i, level;
        level   = (int)me->query_skill("qingyun-shou", 1);
        for(i = sizeof(action); i > 0; i--)
                if(level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
        if( query("qi", me)<50 )
                return notify_fail("你的體力太低了。\n");

        if( query("neili", me)<60 )
                return notify_fail("你的內力不夠練習青雲手。\n");

        if (me->query_skill("qingyun-shou", 1) < 100)
                me->receive_damage("qi", 20);
        else
                me->receive_damage("qi", 30);

        addn("neili", -40, me);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"qingyun-shou/"+ action;
}