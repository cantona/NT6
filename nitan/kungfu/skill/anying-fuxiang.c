// anying-fuxiang.c
// Last Modified by sir on 10.18.2001

#include <ansi.h>;
inherit SKILL;
string type() { return "martial"; }
string martialtype() { return "dodge"; }

string *dodge_msg = ({
"$n一個"HIC"「月上柳梢頭」"NOR"，出白虎門，入天地門，隨着$N的攻勢飄起，從容躲過此招。\n",
"$n使一招"HIM"「大漠孤煙直」"NOR"，出青龍門，入風雲門，猛然縱起丈餘，結果$N撲了個空。\n",
"$n身形一搖，幻出幾個人影，出天地門，入青龍門，一招"BLU"「碎影舞斜陽」"NOR"躲過$N的攻勢。\n",
"$n一招"HIM"「燕子三抄水」"NOR"縱身躍起，出風雲門，入玄武門，倏忽已落至$N身後。\n",
"$n左一搖，右一晃，出玄武門，入朱雀門，一招"HIW"「雲深不知處」"NOR"已輕鬆閃過。\n",
"$n雙足一點，斜斜飛起，出朱雀門，入白虎門，使出"HIM"「斜日杏花飛」"NOR"，已閃到$N身側。\n",
});

int valid_enable(string usage) { return (usage=="dodge") || (usage=="move"); }
int valid_learn(object me) { return 1; }

string query_dodge_msg(string limb)
{
        return dodge_msg[random(sizeof(dodge_msg))];
}

int practice_skill(object me)
{
        if( query("qi", me)<50 )
            return notify_fail("你的體力太差了，不能練暗影浮香。\n");

        if (me->query_skill("anying-fuxiang", 1) < 30)
                me->receive_damage("qi", 10);
        else
        if (me->query_skill("anying-fuxiang", 1) < 50)
                me->receive_damage("qi", 25);
        else
                me->receive_damage("qi", 40);

        return 1;
}

int learn_bonus() { return 15; }
int practice_bonus() { return 15; }
int success() { return 15; }
int power_point(object me) { return 1.3; }

int help(object me)
{
        write(HIC"\n暗影浮香："NOR"\n");
        write(@HELP

    桃花島的獨門輕功身法。

        學習要求：
           碧波神功 10 級
HELP
        );
        return 1;
}