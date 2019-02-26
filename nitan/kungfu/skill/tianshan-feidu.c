inherit SKILL;

string *dodge_msg = ({
        "$n一式「龍騰勢」，身行一轉，猛的跳向一旁,躲過了$N的功勢。\n",
        "$n一式「退馬勢」，雙臂置於身後，不急不緩，昂首從$N眼前跨過。\n",
        "$n一式「虎躍勢」，不退反進，一下子繞到了$N的身後。\n",
        "$n一式「擺荷勢」，緩緩的向後一退，輕鬆讓過了$N的凌厲攻勢。\n",
        "$n一式「插柳勢」，左手一揚，身行一晃，便向右飄出丈遠。\n",
        "$n一式「落瀑勢」，全身化為一道白影，忽的一個空翻，從左邊飄到右邊。\n",
        "$n一式「攬月勢」，宛若一條矯矢蒼龍，倏的拔地而起，令$N不敢仰視。\n",
});

int valid_enable(string usage)
{
        return usage == "dodge" || usage == "move";
}

int valid_learn(object me) { return 1; }

string query_dodge_msg(string limb)
{
        return dodge_msg[random(sizeof(dodge_msg))];
}

int practice_skill(object me)
{
        if( query("qi", me)<50 )
                return notify_fail("你的體力太差了，不能練天山飛渡。\n");

        me->receive_damage("qi", 40);
        return 1;
}