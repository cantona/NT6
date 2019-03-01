// xiyang-boji.c 西洋搏擊術

inherit SKILL;

string *dodge_msg = ({
        "$n身子一扭，恰好躲過了$N這一招。\n",
        "可是$n突然飛身後退，敏捷的躲過了$N這一招。\n",
        "$n奮力橫移，閃開了$N的追擊。\n",
        "$n身隨$N轉動，忽快忽慢，讓$N無法捕捉到$n的蹤影。\n",
        "$n嗔目大喝，氣勢異樣恢弘，$N手一軟，招數全然落空。\n",
});

int valid_enable(string usage) { return usage == "dodge"; }

int valid_learn(object me) { return 1; }

string query_dodge_msg(string limb)
{
        return dodge_msg[random(sizeof(dodge_msg))];
}

int practice_skill(object me)
{
        if( query("qi", me)<50 )
                return notify_fail("你的體力太差了，無法練習西洋搏擊術。\n");

        me->receive_damage("qi", 40);
        return 1;
}