inherit SKILL;

mapping *action = ({
([      "action" : "$N斜裡沖前一步，身法詭異，手中$w急速橫掃$n的$l",
        "force"  : 220,
        "damage" : 40,
        "dodge"  : 50,
        "damage_type" : "挫傷"
]),
([      "action" : "$N忽然直身飛入半空，又忽的飛身撲下，$w攻向$n的$l",
        "force"  : 210,
        "damage" : 45,
        "dodge"  : 55,
        "damage_type" : "挫傷"
]),
([      "action" : "$N原地一個後滾翻，身體向$n平飛過去，手中$w指向$n的$l",
        "force"  : 210,
        "damage" : 35,
        "dodge"  : 60,
        "damage_type" : "挫傷"
]),
([      "action" : "$N突然一個急轉身，$w橫掃一圈後挾著猛烈的勁道打向$n而去",
        "force"  : 200,
        "damage" : 45,
        "dodge"  : 65,
        "damage_type" : "挫傷"
]),
([      "action" : "$N向前順勢一滾，接著翻身跳起，手裡$w斜向上擊向$n的$l",
        "force"  : 220,
        "damage" : 30,
        "dodge"  : 55,
        "damage_type" : "挫傷"
])
});

int valid_enable(string usage)
{
        return usage == "staff" || usage == "parry" ;
}

int valid_learn(object me)
{
        if( query("max_neili", me)<250 )
                return notify_fail("你的內力修為太弱，無法練叫花棒法。\n");

        if ((int)me->query_dex() < 24)
                return notify_fail("你的身法不夠靈活，無法練叫花棒法。\n");

        if ((int)me->query_skill("staff", 1) < (int)me->query_skill("jiaohua-bangfa", 1))
                return notify_fail("你的基本杖法水平有限，無法領會更高深的叫花棒法。\n");

        return 1;
}

mapping query_action(object me, object weapon)
{
        return action[random(sizeof(action))];
}

int practice_skill(object me)
{
        if( query("qi", me)<60 )
                return notify_fail("你的體力太低了。\n");

        if( query("neili", me)<50 )
                return notify_fail("你的內力不夠練叫花棒法。\n");

        me->receive_damage("qi", 45);
        addn("neili", -38, me);
        return 1;
}
