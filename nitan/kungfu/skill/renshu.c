// renshu 東洋忍術

inherit SKILL;

string *dodge_msg = ({
        "$n身子一扭，姿勢頗為怪異，躲過了$N這一招。\n",
        "可是$n突然抱頭滾地而走，躲過了$N這一招。\n",
        "$n突然身邊瀰漫起一團白霧，讓$N失去了方向。\n",
        "$n忽然身形加快，使$N失去了$n的蹤跡。\n",
        "$n突然匍匐於地，使$N招數全然落空。\n",
});

int valid_enable(string usage) { return (usage == "dodge") || (usage == "move"); }

int valid_learn(object me) { return 1; }

string query_dodge_msg(string limb)
{
        return dodge_msg[random(sizeof(dodge_msg))];
}

int practice_skill(object me)
{
        if( query("qi", me)<50 )
                return notify_fail("你的體力太差了，無法練習東洋忍術。\n");

        me->receive_damage("qi", 40);
        return 1;
}