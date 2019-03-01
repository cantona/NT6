// xuefu-mizong.c 血蝠迷蹤
// Eeit By Vin On 26/2/2001

inherit SKILL;

string *dodge_msg = ({
        "只見$n一招「福滿乾坤」，身形陡然縱起，躲過了$N這一招。\n",
        "$n一式「五蝠獻壽」，身形晃動，向一旁飄出，避開了$N這一招。。\n"
        "$n使出「洞天福地」，一個空心筋鬥向後翻出，避開了$N的凌厲攻勢。\n",
        "$n一招「雲龍百蝠」，身隨意轉，$N只覺眼前一花，$n已繞至$N的身後。\n",
        "$n一式「血蝠迷蹤」，身子掣忽一轉，$N只覺的眼前一花，失去了目標。\n",
});

int valid_enable(string usage)
{
        return (usage == "dodge") || (usage == "move");
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
                return notify_fail("你的體力太低了，不能練血蝠迷蹤。\n");

        if( query("neili", me)<40 )
                return notify_fail("你的內力不夠練血蝠迷蹤。\n");

        me->receive_damage("qi", 40);
        addn("neili", -30, me);
        return 1;
}