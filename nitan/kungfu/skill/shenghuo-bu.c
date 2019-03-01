inherit SKILL;

string *dodge_msg = ({
        "$n身形急轉，避過了$N的攻勢。\n",
        "可是$n拔地而起，躲過了$N這一招。\n",
        "$n作閃右避，總算躲過了$N這一招。\n",
});

int valid_enable(string usage) { return (usage == "dodge") || (usage == "move"); }

int valid_learn(object me) { return 1; }

string query_dodge_msg(string limb)
{
        return dodge_msg[random(sizeof(dodge_msg))];
}

int practice_skill(object me)
{
        if( (int)query("qi", me) < 50 )
                return notify_fail("你的體力太差了，無法練習聖火步法。\n");

        me->receive_damage("qi", 40);
        return 1;
}