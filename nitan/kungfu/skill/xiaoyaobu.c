inherit SKILL;

int is_ultimate_skill() { return 1; }

string *dodge_msg = ({
        "$n亂跳一通，避過了$N的攻勢。\n",
});

int valid_enable(string usage) { return (usage == "dodge");}

int valid_learn(object me) { return 1; }

string query_dodge_msg(string limb)
{
        return dodge_msg[random(sizeof(dodge_msg))];
}

int practice_skill(object me)
{
        if( query("qi", me)<50 )
                return notify_fail("你的體力太差了，無法繼續練習。\n");

        me->receive_damage("qi", 40);
        return 1;
}
