inherit SKILL;

mapping *action = ({
([        "action" : "$N手掌交錯，身行前探，一招「虛式分金」，掌風直劈向$n的$l",
        "force" : 120,
        "attack": 10,
        "dodge" : 5,
        "parry" : 5,
        "damage": 35,
        "lvl"   : 0,
        "skill_name" : "虛式分金",
        "damage_type" : "瘀傷"
]),
([        "action" : "$N身行鬥轉，一招「月落西山」，左手護肘，右手直擊$n前胸",
        "force" : 140,
        "attack": 15,
        "dodge" : 7,
        "parry" : 7,
        "damage": 38,
        "lvl"   : 20,
        "skill_name" : "月落西山",
        "damage_type" : "抓傷"
]),
([        "action" : "$N輕喝一聲，一招「順水推舟」，身行不變，將右手迅間化掌，斜擊$n的後腰。",
        "force" : 170,
        "attack": 21,
        "dodge" : 11,
        "parry" : 11,
        "damage": 43,
        "lvl"   : 40,
        "skill_name" : "順水推舟",
        "damage_type" : "瘀傷",
]),
([        "action" : "$N雙手自外向內拗入，一招「鐵鎖橫江」，去勢奇快，向$n的$l劈去，",
        "force" : 190,
        "attack": 25,
        "dodge" : 13,
        "parry" : 13,
        "damage": 45,
        "lvl"   : 70,
        "skill_name" : "鐵鎖橫江",
        "damage_type" : "瘀傷"
]),
([        "action" : "$N衣袖輕擺,右手上封，左手下壓，連削帶打奔向$n的$l",
        "force" : 220,
        "attack": 35,
        "dodge" : 15,
        "parry" : 15,
        "damage": 51,
        "lvl"   : 100,
        "skill_name" : "輕羅小扇",
        "damage_type" : "內傷"
]),
([        "action" : "$N一招「黑沼靈狐」，左腳向前一個偷步，右手化掌向前劃出,左手順勢反拍$n的面門",
        "force" : 240,
        "attack": 55,
        "dodge" : 18,
        "parry" : 18,
        "damage": 55,
        "lvl"   : 130,
        "skill_name" : "黑沼靈狐",
        "damage_type" : "瘀傷"
]),
([        "action" : "$N腳踩奇門，猛然躍到$n的身旁,一招「生死茫茫」，揮手打向$n的$l",
        "force" : 270,
        "attack": 61,
        "dodge" : 25,
        "parry" : 25,
        "damage": 58,
        "lvl"   : 160,
        "skill_name" : "生死茫茫",
        "damage_type" : "瘀傷"
]),
([        "action" : "$N手指微微作響，一招「高山流水」，掌影猶如飛瀑般將$n籠罩了起來",
        "force" : 310,
        "attack": 75,
        "dodge" : 25,
        "parry" : 25,
        "damage": 65,
        "lvl"   : 200,
        "skill_name" : "高山流水",
        "damage_type" : "瘀傷"
]),
([        "action" : "$N突然愁眉緊縮，神態間散發萬種風情，$n猛一驚訝，忽然感到一股排山倒海的掌風襲來",
        "force" : 340,
        "attack": 85,
        "dodge" : 30,
        "parry" : 30,
        "damage": 71,
        "lvl"   : 250,
        "skill_name" : "伊人消魂",
        "damage_type" : "瘀傷"
]),
});

int valid_enable(string usage) { return usage=="hand" ||  usage=="parry"; }

int valid_combine(string combo) { return combo == "jinding-zhang" || combo == "tiangang-zhi"; }

int valid_learn(object me)
{
        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("練截手九式必須空手。\n");

        if ((int)me->query_skill("force") < 100)
                return notify_fail("你的內功火候不夠，無法學截手九式。\n");

        if( query("max_neili", me)<500 )
                return notify_fail("你的內力太弱，無法練截手九式。\n");

        if (me->query_skill("hand", 1) < me->query_skill("jieshou-jiushi", 1))
                return notify_fail("你的基本指法太差，無法領會更高深的截手九式。\n");

        return 1;
}

string query_skill_name(int level)
{
        int i;
        for(i = sizeof(action) - 1; i >= 0; i--)
                if (level >= action[i]["lvl"])
                        return action[i]["skill_name"];
}

mapping query_action(object me, object weapon)
{
        int i, level;
        level = (int)me->query_skill("jieshou-jiushi", 1);
        for (i = sizeof(action); i > 0; i--)
                if (level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
        if( query("qi", me)<70 )
                return notify_fail("你的體力太低了，無法練截手九式。\n");

        if( query("neili", me)<70 )
                return notify_fail("你的內力不夠，無法練截手九式。\n");

        me->receive_damage("qi", 55);
        addn("neili", -51, me);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"jieshou-jiushi/" + action;
}