// This program is a part of NITAN MudLIB
// biye-wu.c 碧葉隨風舞

inherit SKILL;

string *action_msg = ({
        "$N雙手揚起，輕飄飄一式「葉落」，掌若落葉，向$n的$l拍去",
        "$N左腳為軸心，右腳一旋，雙手交替揮舞，如竹葉翻飛，正是「葉舞」，向$n的$l拍下",
        "$N身體高高躍起，左手立在胸前，右臂微曲，使一招「葉飄零」，向$n的$l和麪門打去",
        "$N微一運勁，雙掌青筋爆露，一式「枯葉」，將$n渾身上下都籠罩在重重掌影之中",
        "$N雙掌平攤，左掌緩緩收至肩，右掌猛向前推出，\n掌風帶着破空聲，一招「彈枝」，如竹枝反彈，直奔$n心窩而去",
        "$N突然收掌，由腹部向前向上推出，掌風如濤，一式「葉如潮」，一片勁風直逼$n",
});

int valid_enable(string usage) { return usage == "strike" || usage == "parry"; }

int valid_learn(object me)
{
        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("練碧葉隨風舞必須空手。\n");
        if ((int)me->query_skill("biyun-xinfa", 1) < 30)
                return notify_fail("你的碧雲心法火候不夠，無法學碧葉隨風舞。\n");
        if( query("max_neili", me)<100 )
                return notify_fail("你的內力太弱，無法練碧葉隨風舞。\n");
        return 1;
}

mapping query_action(object me, object weapon)
{
        return ([
                "action": action_msg[random(sizeof(action_msg))],
                "force" : 320 + random(100),
                "dodge" : -40 + random(10),
                "parry" : -50 + random(10),
                "attack": 10 + random(20),
                "damage_type":random(2)?"搓傷":"淤傷",
        ]);
}

int practice_skill(object me)
{
        if( query("qi", me)<70 )
                return notify_fail("你的體力太低了。\n");
        if( query("neili", me)<70 )
                return notify_fail("你的內力不夠練碧葉隨風舞。\n");
        me->receive_damage("qi", 60);
        addn("neili", -60, me);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"biye-wu/" + action;
}
