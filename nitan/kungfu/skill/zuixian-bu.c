inherit SKILL;

string *dodge_msg = ({
    "$n一式「醉裡乾坤」，身子掣忽一轉，$N只覺的眼前一花，失去了目標。\n",
    "$n一式「太白醉酒」，雙腳點地，身子突然拔高了丈許，緩緩飄落在$N身後。\n",
    "$n一式「移行幻影」，身行一晃，頓時無數條身影一下子出現在$N的面前。\n",
    "$n一式「醉仙望月」，飄然向後一退，躲開$N的凌厲攻勢。\n",
    "$n一式「如夢似幻」，身體急轉，化為一道白光，虛幻不定的出現在$N的周圍。\n",
});

int valid_enable(string usage)
{
        return usage == "dodge" || usage == "move";
}

int valid_learn(object me)
{
        return 1;
}

string query_dodge_msg(string limb)
{
    return dodge_msg[random(sizeof(dodge_msg))];
}

int practice_skill(object me)
{
    if( query("qi", me)<100 )
        return notify_fail("你的體力太差了，不能練醉仙望月步。\n");

    me->receive_damage("qi", 80);
    return 1;
}
