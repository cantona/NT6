inherit SKILL;

string *dodge_msg = ({
        "$n隨風向上飄了一點，剛好避過$N的凌厲攻勢。\n",
        "可是$n在空中一個翻騰，躲過了$N這一招。\n"
});

int valid_enable(string usage) { return (usage == "dodge") || (usage == "move"); }

int valid_learn(object me) { return 1; }

string query_dodge_msg(string limb)
{
        return dodge_msg[random(sizeof(dodge_msg))];
}

int practice_skill(object me)
{
        if( query("qi", me)<40 )
                return notify_fail("你的體力太差了，怎麼能象精靈一樣在空中飛呢？\n");
        me->receive_damage("qi", 30);
        return 1;
}

