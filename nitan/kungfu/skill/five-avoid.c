// five-avoid.c 五行遁
// Modified by Venus Oct.1997
// written by deaner
#include <ansi.h>
inherit SKILL;

mapping *action = ({
([  "action" : "可是$n微微一笑，$N眼前水霧彌漫，$n已使出"+HIC"『水遁』"NOR+"借水而逝。\n",
    "dodge"  : 60
]),
([  "action" : "卻見$n拋下手中兵刃，撲向路邊的一棵大樹，轉眼和枝葉混為一體，"
               "$N茫然四顧，不知$n已經靠"+HIG"『木遁』"NOR+"躲開攻擊。\n",
    "dodge"  : 70
]),
([  "action" : "$n原地一轉，立時鑽入土中。$N這一招落到了空處，驚道"+HIY"『土"
              "遁』"NOR+"！\n",
    "dodge"  : 80
]),
([  "action" : "$n隨手打出一團火球，喝道"+HIR"『火遁』"NOR+"！ 整個人消失在□火球中。\n",
    "dodge"  : 90
]),
([  "action" : "$n哈哈一笑，把手中的兵刃交錯一擊，喝道“看我"+HIY
               "『金遁』"NOR+"”，突然精光耀眼，$N眼前一花，這一招不知落到了何處。\n",
    "dodge"  : 100
]),
});

mapping query_action(object me, object weapon)
{
    int zhaoshu, level;

    zhaoshu = sizeof(action);
    level   = (int) me->query_skill("five-avoid",1);

    if (level < 200 )
       zhaoshu--;
    if (level < 150 )
       zhaoshu--;
    if (level < 100 )
       zhaoshu--;
    if (level < 70 )
       zhaoshu--;
    return action[random(zhaoshu)];
}
int valid_enable(string usage)
{
    return (usage=="dodge") || (usage=="move");
}

int valid_learn(object me)
{
    return 1;
}
string query_dodge_msg(string limb)
{
    object me, ob;
    mapping action;

    me = this_player();
    action = query_action(me, ob);

    return action["action"];
}

int practice_skill(object me)
{
    if( query("qi", me)<70 )
        return notify_fail("你的氣力不夠,不能修煉五行遁.\n");

    me->receive_damage("qi", 65);
    return 1;
}
string perform_action_file(string action)
{
    return __DIR__"five-avoid/" + action;
}
