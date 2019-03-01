// This program is a part of NITAN MudLIB
// shentuo-zhang 神駝雪山掌

#include <ansi.h>
inherit SKILL;

string *action_msg = ({
        "$N雙臂一舒，使出一招「明駝西來」，身形旋轉，掌勢飄忽，擊向$n的$l",
        "$N身形向後一錯，左掌陰勢，右掌陽型，使出一式「大漠冰揚」，拍向$n的$l",
        "$N彈腿飛身，步法陰陽互易，若有若無的踢向$n的$l，正是一招「靈駝駿足」",
        "$N身形飛旋，一式「萬裡飛霜」，掌影紛飛，掌上內勁已把$n的上盤統統罩住",
        "$N身形急轉，半空中一招「神駝沖霄」，頭下腳上，剎那間手腳齊攻，擊向$n的$l",
        "$N掌勢一緩，使出一式「雪鎖千山」，掌上陰勁如怒濤洶湧，緩緩推向$n的$l",
});


int valid_enable(string usage) { return usage == "strike" ||  usage == "parry"; }

// int valid_combine(string combo) { return combo == "lingshe-quan"; }

int valid_learn(object me)
{
        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("練神駝雪山掌必須空手。\n");

        if( query("max_neili", me)<50 )
                return notify_fail("你的內力太弱，無法練神駝雪山掌。\n");
        return 1;
}

mapping query_action(object me, object weapon)
{
        return ([
                "action": action_msg[random(sizeof(action_msg))],
                "force": 320 + random(60),
                "attack": 50 + random(10),
                "dodge" : 20 + random(10),
                "parry" : 20 + random(10),
                "damage_type" : random(2)?"瘀傷":"內傷",
        ]);
}

int practice_skill(object me)
{
        if( query("qi", me)<60 )
                return notify_fail("你的體力太低了。\n");
        if( query("neili", me)<60 )
                return notify_fail("你的內力不夠練神駝雪山掌。\n");
        me->receive_damage("qi", 50);
        addn("neili", -50, me);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"shentuo-zhang/" + action;
}