// This program is a part of NITAN MudLIB
// Luan-blade.c 亂刀（田伯光）

inherit SKILL;

string *action_msg = ({
        "$N手中$w左一揮右一攔，對準$n的$l就是一戳",
        "$N手中$w上一挑下一撩，向$n的$l捅去",
        "$N手中$w東一劈西一插，刀鋒指向$n的$l",
        "$N手中$w前一指後一掃，刀尖挑向$n的$l",
});

int valid_enable(string usage) { return usage == "blade" || usage == "parry"; }

int valid_learn(object me)
{
        return 1;
}

mapping query_action(object me, object weapon)
{
        return ([
                "action": action_msg[random(sizeof(action_msg))],
                "damage": 120 + random(41),
                "attack": 60 + random(21),
                "dodge" : -60 + random(21),
                "parry" : -60 + random(21),
                "damage_type" : random(2) ? "挫傷" : "割傷",
        ]);
}

int practice_skill(object me)
{
        if( query("qi", me)<60 )
                return notify_fail("你的精力太低了。\n");
        if( query("neili", me)<60 )
                return notify_fail("你的內力不夠練亂刀。\n");
        me->receive_damage("qi", 50);
        addn("neili", -50, me);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"luan-blade/" + action;
}