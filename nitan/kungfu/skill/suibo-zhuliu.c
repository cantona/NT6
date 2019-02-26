// 隨波逐流身法

inherit SKILL;
string *dodge_msg = ({
        "$n一式「隨波逐流」，身體便如大海中的一葉孤舟一樣，隨着$N的招式遊走，渾不着力。\n",
        "$n一式「風起雲湧」，縱身高躍，半空中忽然倒退，輕飄飄地落在數丈之外。\n",
        "$n一式「驚濤拍岸」，反倒搶向$N，於間不容髮之際避開了$N這一招。\n",
        "$n一式「順水推舟」，身子便如游魚般，輕輕一卸，就將$N襲來的招式推到一旁。\n",
        "$n一式「大浪淘沙」，縱高伏低，趁$N眼花繚亂之時已避開了此招。\n",
        "$n一式「擊棹中流」，蹂身而上，竟是兩敗俱傷的打法，$N一楞之下，$n已安全脱身。\n",
        "$n一式「星河倒懸」，雙足微蹬，身體向後平平飛出，堪堪躲過了這招。\n",
        "$n一式「天際歸舟」，倏爾遠遊，只一霎間，身子竟已在十丈開外！\n",
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
        if( query("qi", me)<40 )
                return notify_fail("你的體力太差了，不能練隨波逐流身法。\n");
        me->receive_damage("qi", 30);
        return 1;
}
