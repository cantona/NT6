// zhuifeng-steps.c  追風步
// modified by Venus Oct.1997
// by jacki

inherit SKILL;

string *dodge_msg = ({
    "$n一個「隨風而舞」，身形飄忽不定，躲過了$N這一招。\n",
    "$n身形飄飄，使出一招「身隨意轉」，避過了$N的攻擊。\n",
    "$n使出「移步換形」，在千鈞一發間躲過了$N的攻勢。\n",
    "$n衣袂飄飄，一招「事了拂衣去」，瀟洒地避了開去。\n"
});

int valid_enable(string usage)
{
    return (usage == "dodge") || (usage == "move");
}

int valid_learn(object me) { return 1; }

string query_dodge_msg(string limb)
{
    return dodge_msg[random(sizeof(dodge_msg))];
}

int practice_skill(object me)
{
    if( query("qi", me)<50 )
        return notify_fail("你的體力太差了，不能練追風步。\n");

    me->receive_damage("qi", 40);
    return 1;
}