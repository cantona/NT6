inherit SKILL;

string *dodge_msg = ({
        "$n足跟一支，全身後仰，一招「鯉魚倒穿波」，反竄出丈余，躲過了$N的攻擊。\n",
        "$n身體忽然柔若無骨，左右搖擺，使出一招「雨打漂萍」，避過了$N的攻擊。\n",
        "$n使出「物換星移」，滴溜溜一個轉身，從$N身旁擦身而過，反而到了$N身後。\n",
        "$n一招「落葉隨風」，身體如一片落葉一般飄了出去，身行之瀟洒，迅速到了極處。\n"
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
        return notify_fail("你的體力太差了，不能練登萍渡水。\n");

    me->receive_damage("qi", 40);
    return 1;
}
