inherit SKILL;

string *dodge_msg = ({
        "只見$n清嘯一聲，身體向上筆直地縱起丈余，躲過了$N這一招。\n",
        "$n身形飄忽，靈巧無比，輕輕向後一縱，早已避開。\n",
        "只見$n身行隨意轉，如同水蛇一般，倏地往一旁挪開了三尺，避過了這一招。\n",
        "可是$n著地一個猛翻，側身一讓，$N這一招撲了個空。\n",
        "卻見$n蠻腰擺動，足不點地，往旁竄開數尺，躲了開去。\n",
        "$n飛身躍起，在半空中一個翻滾，身形一晃，有驚無險地避開了$N這一招。\n"

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
        if( query("qi", me)<150 )
                return notify_fail("你的體力太差了，不能練習烏渡術。\n");

        if( query("neili", me)<300 )
                return notify_fail("你的內力太差了，不能練習烏渡術。\n");

        me->receive_damage("qi", 100);
        addn("neili", -250, me);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"wudu-shu/" + action;
}
