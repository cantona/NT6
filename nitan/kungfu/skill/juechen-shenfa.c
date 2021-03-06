inherit SKILL;

string *dodge_msg = ({
        "$n一個「銀鷺渡海」，躍起數尺，躲過了$N這一招。\n",
        "$n身形向後一縱，使出一招「玉兔落塵」，避過了$N的攻擊。\n",
        "$n使出「錦鯉穿沙」，恰好躲過了$N的攻勢。\n",
        "$n一招「靈狐幻遁」，姿態美妙地躲了開去。\n"
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
        if( query("qi", me)<50 )
                return notify_fail("你的體力太差了，不能練絕塵身法。\n");

        me->receive_damage("qi", 40);
        return 1;
}