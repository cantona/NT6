// ding-dodge.c 丁字步 

inherit SKILL;

string *dodge_msg = ({
        "$n漫不經心的向左邁出一步，剛好避過$N的凌厲攻勢。\n",
        "可是$n恰巧往右走了一步，躲過了$N這一招。\n",
});

int valid_enable(string usage) { return (usage == "dodge"); }

int valid_learn(object me) { return 1; }

string query_dodge_msg()
{
        return dodge_msg[random(sizeof(dodge_msg))];
}

int practice_skill(object me)
{
        if( query("qi", me)<50 )
                return notify_fail("你的體力太差了，邁不開丁字步。\n");
        if( query("neili", me)<40 )
                return notify_fail("你的內力不夠。\n");
        me->receive_damage("qi", 40);
        addn("neili", -30, me);
        return 1;
}

