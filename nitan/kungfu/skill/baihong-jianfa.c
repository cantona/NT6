// baihong-jianfa 白虹劍法

#include <ansi.h>
#include <combat.h>

inherit SKILL;

string *action_msg = ({
        "$N左手握拳，右手劍走輕靈，一招巧「白虹一現」，$w化成一道光芒，射向$n的$l",
        "$N使出一招「鷹起雲揚」，身形向上飄起，手中$w猛的劈向$n的$l",
        "$N身形一晃，猛然一式「波濤洶湧」，將$w舞得有如波濤，挾着一陣勁風向$n掃去",
        "$N一身清嘯，身行一頓，隨即將手中$w舞成一道光環，一招「日月無光」捲起地上的灰塵掃$n的$l",
        "$N倒轉身子，似乎象要逃跑，猛然身行一轉，使出一招“回手劍”，劍尖化作幾點星光射向$n的$l",
        "$N向左跨出一步，左手捏着劍決，一招「百流匯海」右手$w化出好幾道光芒射向$n的$l",
        "$N運力縱起丈餘，一招「天鷹翱翔」，揮出手中$w，飄然刺向$n的$l",
        "$N右手舉$w過頂，身子一擺，一招「冰霜雪雨」，$w化做幾點寒星射向$n",
        "$N將左手握拳，虛擊一招，突然面如寒霜，揮出手中$w刺向$n的$l，好一招「風雪江山」",
        "$N手中$w一指，臉上露出微微的笑容，真氣飛速地流遍全身，一招「白虹萬道」，$w化成萬道光芒雷霆般射向$n的$l",
});


int valid_enable(string usage) { return usage == "sword" || usage == "parry";}

int valid_learn(object me)
{
        if( query("max_neili", me)<100 )
                return notify_fail("你的內力不夠。\n");

        return 1;
}

mapping query_action(object me, object weapon)
{
        return ([
                "action": action_msg[random(sizeof(action_msg))],
                "damage": 120 + random(21),
                "attack": 20 + random(11),
                "dodge" : -30 + random(11),
                "parry" : -30 + random(11),
                "damage_type" : random(2)?"刺傷":"割傷",
        ]);
}

int practice_skill(object me)
{
        object weapon;

        if( !objectp(weapon=query_temp("weapon", me) )
         || query("skill_type", weapon) != "sword" )
                return notify_fail("你使用的武器不對。\n");

        if( query("qi", me)<70 )
                return notify_fail("你的體力不夠練白虹劍法。\n");
        if( query("neili", me)<70 )
                return notify_fail("你的內力不夠練白虹劍法。\n");

        me->receive_damage("qi", 60);
        addn("neili", -60, me);

        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"baihong-jianfa/" + action;
}

