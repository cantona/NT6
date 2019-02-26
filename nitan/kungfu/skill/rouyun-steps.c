// rouyun-steps.c  柔雲步法
// modified by Venus Oct.1997
// Made by deaner
#include <ansi.h>
inherit SKILL;

string *dodge_msg = ({
      "$n使一式"+HIW"『雲中鶴影』"NOR+"，身形縱離地面數尺，躲過了$N這一招。\n",
      "$n身形飄飄，使出一式"+MAG"『雲彩飄忽』"NOR+"，避過了$N的攻擊。\n",
      "$n使出一式"+HIB"『雲霧繚繞』"NOR+"，$N眼前已沒了$n的蹤影。\n",
      "$n施展出一式"+HIG"『雲雨不定』"NOR+"，身影急幌，在千鈞一髮間躲過了$N的攻勢。\n",
      "$n衣袂飄飄，一式"+HIY"『雲蒸霞蔚』"NOR+"，輕靈地避了開去。\n",
      "$n立即使出一式"+YEL"『雲海浮沉』"NOR+"，沉肩滑步，微晃身影，避開了$N的攻擊。\n",
      "$n立刻使一式"+BLU"『雲影萬千』"NOR+"，身形忽進忽退，忽左忽右，$N的攻擊已然無效。\n",
});

int valid_enable(string usage)
{
    return (usage == "dodge") || (usage == "move");
}

int valid_learn(object me)
{
    if ((int)me->query_dex() <= 30)
        return notify_fail("你的身法不夠，難以領會柔雲步法。");

    return 1;
}

string query_dodge_msg()
{
    return dodge_msg[random(sizeof(dodge_msg))];
}

int practice_skill(object me)
{
    if( query("qi", me)<50 )
        return notify_fail(HIC"你的體力太差了，不能練柔雲步法。\n"NOR);

    if( query("neili", me)<50 )
        return notify_fail(HIC"你的內力太差了，不能練柔雲步法。\n"NOR);

    me->receive_damage("qi", 45);
    addn("neili", -20, me);
    return 1;
}

string perform_action_file(string action)
{
    return __DIR__"rouyun-steps/" + action;
}