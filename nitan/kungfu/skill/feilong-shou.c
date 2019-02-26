inherit SKILL;

mapping *action = ({
([      "action": "在呼呼風聲中，$N使一招「捕風捉影」，雙手如鈎如戢，插向$n的$l",
        "force" : 80,
        "attack": 25,
        "dodge" : 20,
        "parry" : 25,
        "damage": 10,
        "lvl"   : 0,
        "damage_type" : "瘀傷"
]),
([      "action": "$N雙拳揮舞，一式「浮雲去來」，兩手環扣，攏成圈狀，猛擊$n的下頜",
        "force" : 100,
        "attack": 28,
        "dodge" : 20,
        "parry" : 27,
        "damage": 20,
        "lvl"   : 30,
        "damage_type" : "瘀傷"
]),
([      "action": "$N一招「飛龍獻爪」，雙手紛飛，$n只覺眼花繚亂",
        "force" : 120,
        "attack": 32,
        "dodge" : 30,
        "parry" : 28,
        "damage": 30,
        "lvl"   : 60,
        "damage_type" : "瘀傷"
]),
([      "action": "$N左手護胸，腋下含空，右手五指如鈎，一招「抱殘守缺」插向$n的頂門",
        "force" : 150,
        "attack": 33,
        "dodge" : 30,
        "parry" : 33,
        "damage": 35,
        "lvl"   : 80,
        "damage_type" : "瘀傷"
]),
([      "action": "$N一手頂天成爪，一手指地，一招「撥雲見日」，勁氣籠罩$n的全身",
        "force" : 180,
        "attack": 36,
        "dodge" : 30,
        "parry" : 37,
        "damage": 45,
        "lvl"   : 100,
        "damage_type" : "瘀傷"
]),

([      "action": "$N雙手平舉，一招「蒼龍出水」，身形化作一道閃電射向$n",
        "force" : 210,
        "attack": 42,
        "dodge" : 35,
        "parry" : 45,
        "damage": 40,
        "lvl"   : 120,
        "damage_type" : "瘀傷"
]),
([      "action": "$N一招「雲中現爪」，拿向$n，似乎$n的全身都被籠罩",
        "force" : 240,
        "attack": 47,
        "dodge" : 30,
        "parry" : 41,
        "damage": 45,
        "lvl"   : 140,
        "damage_type" : "內傷"
]),

([      "action": "$N左手虛晃，右手一記「龍飛在天」擊向$n的頭部",
        "force" : 260,
        "attack": 46,
        "dodge" : 30,
        "parry" : 47,
        "damage": 50,
        "lvl"   : 160,
        "damage_type" : "瘀傷"
]),
});

int valid_enable(string usage) { return usage=="parry"|| usage=="hand"; }

int valid_learn(object me)
{
        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("練飛龍探雲手必須空手。\n");

        if( query("max_neili", me)<2500 )
                return notify_fail("你的內力太弱，無法練飛龍探雲手。\n");

        if ((int)me->query_skill("force") < 200)
                return notify_fail("你的內功火候不夠，無法練飛龍探雲手。\n");

        if ((int)me->query_skill("hand", 1) < 150)
                return notify_fail("你的基本手法火候不夠，無法練飛龍探雲手。\n");

        if ((int)me->query_skill("hand", 1) < (int)me->query_skill("feilong-shou", 1))
                return notify_fail("你的基本手法水平有限，無法領會更高深的飛龍探雲手。\n");

        return 1;
}

mapping query_action(object me, object weapon)
{
        int i, level;
        level = (int) me->query_skill("feilong-shou",1);
        for(i = sizeof(action); i > 0; i--)
                if(level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
        if( query("qi", me)<70 )
                return notify_fail("你的體力太低了。\n");

        if( query("neili", me)<70 )
                return notify_fail("你的內力不夠練飛龍探雲手。\n");

        me->receive_damage("qi", 65);
        addn("neili", -62, me);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"feilong-shou/" + action;
}
