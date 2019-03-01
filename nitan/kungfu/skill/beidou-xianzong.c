// beidou-xianzong.c

inherit SKILL;

string *dodge_msg = ({
        "只見$n一招「仙蹤緲去」，身體飄然後退，躲過了$N這一招。\n",
        "$n一個「星宿易位」，向後縱出數丈之遠，避開了$N的凌厲攻勢。\n",
        "$n使出「奇星而出」，向一旁飄然縱出，輕輕著地。\n",
        "但是$n一招「無中生有」，身形飄忽，早已避開。\n",
        "$n身隨意轉，一招「化身金虹」倏的不見蹤影。\n",
        "可是$n身形不斷閃動，一招「流星破空」$N這一招撲了個空。\n",
        "卻見$n足不點地，一招「群星送客」往旁竄開數尺，躲了開去。\n",
        "$n身形微晃，一招「仙過九天」有驚無險地避開了$N這一招。\n",
});

int valid_enable(string usage) { return (usage == "dodge") || (usage == "move");}

int valid_learn(object me) { return 1; }

string query_dodge_msg(string limb)
{
        return dodge_msg[random(sizeof(dodge_msg))];
}

int practice_skill(object me)
{
        if( query("qi", me)<50 )
                return notify_fail("你的體力太差了，不能練北鬥仙蹤步法。\n");

        me->receive_damage("qi", 40);
        return 1;
}