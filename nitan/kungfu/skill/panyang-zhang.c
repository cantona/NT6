inherit SKILL;

mapping *action = ({
([        "action" : "$N劃身錯步，一式「洪爐焚天」，雙掌內攏外託，攻向$n的左肩",
        "force" : 70,
        "attack": 5,
        "dodge" : 38,
        "parry" : 38,
        "damage": 1,
        "lvl"   : 0,
        "skill_name" : "洪爐焚天",
        "damage_type" : "瘀傷"
]),
([        "action" : "$N一式「舉火燒天」，雙掌以迅雷不及掩耳之勢，劈向$n的兩額太陽穴",
        "force" : 95,
        "attack": 8,
        "dodge" : 43,
        "parry" : 43,
        "damage": 4,
        "lvl"   : 20,
        "skill_name" : "舉火燒天",
        "damage_type" : "瘀傷"
]),
([        "action" : "$N使一式「偷星換日」，勁氣瀰漫，雙掌如輪，一環環向$n的後背斫去",
        "force" : 120,
        "attack": 13,
        "dodge" : 51,
        "parry" : 51,
        "damage": 8,
        "lvl"   : 40,
        "skill_name" : "偷星換日",
        "damage_type" : "瘀傷"
]),
([        "action" : "$N一式「烈陽繁生」，雙掌似讓非讓，似頂非頂，氣浪如急流般使$n陷身其中",
        "force" : 140,
        "attack": 15,
        "dodge" : 65,
        "parry" : 65,
        "damage": 12,
        "lvl"   : 60,
        "skill_name" : "烈陽繁生",
        "damage_type" : "瘀傷"
]),
});

int valid_enable(string usage) { return usage == "strike" ||  usage == "parry"; }

int valid_combine(string combo) { return combo=="qingyun-shou"; }

int valid_learn(object me)
{
        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("練攀陽掌必須空手。\n");

        if (me->query_skill("force") < 20)
                return notify_fail("你的內功火候不夠，不能練攀陽掌。\n");

        if( query("max_neili", me)<50 )
                return notify_fail("你的內力太弱，無法練攀陽掌。\n");

        if (me->query_skill("strike", 1) < me->query_skill("panyang-zhang", 1))
                return notify_fail("你的基本掌法太差，無法領會更高深的攀陽掌。\n");

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
        level   = (int)me->query_skill("panyang-zhang",1);
        for(i = sizeof(action); i > 0; i--)
                if(level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
        if( query("qi", me)<50 )
                return notify_fail("你的體力太低了。\n");

        if( query("neili", me)<60 )
                return notify_fail("你的內力不夠練習攀陽掌。\n");

        if (me->query_skill("panyang-zhang", 1) < 100)
                me->receive_damage("qi", 20);
        else
                me->receive_damage("qi", 30);

        addn("neili", -40, me);
        return 1;
}
string perform_action_file(string action)
{
        return __DIR__"panyang-zhang/"+ action;
}