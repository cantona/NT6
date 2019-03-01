// lingshe-quan 靈蛇拳

inherit SKILL;

mapping *action = ({
([        "action": "$N一式「靈蛇出洞」，右手虛晃，左手揚起，突然拍向$n的背後二穴",
        "force" : 60,
        "attack": 40,
        "dodge" : 30,
        "lvl"   : 0,
        "skill_name" : "靈蛇出洞",
        "damage_type" : "瘀傷"
]),
([        "action": "$N側身一晃，一式「虎頭蛇尾」，左手拿向$n的肩頭，右拳打向$n的胸口",
        "force" : 100,
        "attack": 45,
        "dodge" : 35,
        "lvl"   : 30,
        "skill_name" : "虎頭蛇尾",
        "damage_type" : "瘀傷"
]),
([        "action": "$N一式「畫蛇添足」，右手環攏成爪，一出手就向扣$n的嚥喉要害",
        "force" : 130,
        "attack": 50,
        "dodge" : 40,
        "damage": 5,
        "lvl"   : 50,
        "skill_name" : "畫蛇添足",
        "damage_type" : "瘀傷"
]),
([        "action": "$N左手虛招，右掌直立，一式「杯弓蛇影」，錯步飄出，疾拍$n的面門",
        "force" : 160,
        "attack": 55,
        "dodge" : 50,
        "damage": 10,
        "lvl"   : 70,
        "skill_name" : "杯弓蛇影",
        "damage_type" : "瘀傷"
]),
([        "action": "$N使一式「蛇行鼠竄」，左拳上格，右手探底突出，抓向$n的襠部",
        "force" : 210,
        "attack": 60,
        "dodge" : 65,
        "damage": 15,
        "lvl"   : 90,
        "skill_name" : "蛇行鼠竄",
        "damage_type" : "瘀傷"
]),
([        "action": "$N一式「蛇磐青竹」，十指伸縮，虛虛實實地襲向$n的全身要穴",
        "force" : 250,
        "attack": 70,
        "dodge" : 75,
        "damage": 25,
        "lvl"   : 120,
        "skill_name" : "蛇磐青竹",
        "damage_type" : "內傷"
]),
([        "action" : "$N雙手抱拳，一式「萬蛇洶湧」，掌影翻飛，同時向$n施出九九八十一招",
        "force" : 280,
        "attack": 80,
        "dodge" : 75,
        "damage": 30,
        "lvl"   : 140,
        "skill_name" : "萬蛇洶湧",
        "damage_type" : "內傷"
]),
([        "action" : "$N一式「白蛇吐信」，拳招若隱若現，若有若無，急急地拍向$n的丹田",
        "force" : 300,
        "attack": 90,
        "dodge" : 80,
        "damage": 40,
        "lvl"   : 160,
        "skill_name" : "白蛇吐信",
        "damage_type" : "內傷"
]),
});

int valid_enable(string usage) { return usage=="cuff" || usage=="strike" || usage=="parry"; }

int valid_combine(string combo) { return combo=="shedu-qiqiao"; }

int valid_learn(object me)
{
        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("練靈蛇拳必須空手。\n");

        if( query("max_neili", me)<500 )
                return notify_fail("你的內力太弱，無法練靈蛇拳。\n");

        if ((int)me->query_skill("cuff", 1) < (int)me->query_skill("lingshe-quan", 1))
                return notify_fail("你的基本拳法水平有限，無法領會更高深的靈蛇拳法。\n");

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
        level   = (int) me->query_skill("lingshe-quan", 1);
        for(i = sizeof(action); i > 0; i--)
                if(level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
        if( query("qi", me)<60 )
                return notify_fail("你的體力太低了。\n");

        if( query("neili", me)<60 )
                return notify_fail("你的內力不夠練靈蛇拳。\n");

        me->receive_damage("qi", 55);
        addn("neili", -55, me);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"lingshe-quan/" + action;
}