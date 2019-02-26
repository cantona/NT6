// jinyan-gong.c 金雁功

#include <ansi.h>;
inherit SKILL;
string type() { return "martial"; }
string martialtype() { return "dodge"; }

string *dodge_msg = ({
        "卻不料$n身形一轉，一個"HIY"「藏形匿跡」"NOR"突然轉到了$N的身後。\n",
        "$n足尖在地面一點，身形拔地而起，"HIC"「飛靈八方」"NOR"躲開了這一招。\n",
        "$n隨着$N攻來的招式一個"HIW"「乘虛御空」"NOR"飄了起來，就如一片微風中的柳絮一般。\n",
        "$n使出"HIY"「解行遁變」"NOR"，身形左一晃、右一閃，不知怎麼的，從攻擊的間隙中鑽了出來。\n",
        "$n使出"HIM"「回神轉玄」"NOR"，足不點地地圍繞$N連繞三個大圈，把$N這一招避了開去。\n",
        "$n連旋數個大圈，跟着又是一個大圈，運起金雁功的"HIC"「棄厄飛霄」"NOR"，身形高高地拔了起來。\n",
        "$n身形流轉，衣袖飄拂，繞場團走，正是金雁功的"HIB"「隱景舞天」"NOR"，形態縵妙已極。\n",
        "$n身形飄浮，長袖翻卷，一勢"HIW"「出有入無」"NOR"，輕鬆自如地避開了$N的攻勢。\n",
});

int valid_enable(string usage) { return usage=="dodge" || usage=="move"; }
int valid_learn(object me)
{
        if ((int)me->query_skill("dodge", 1) < 50)
                return notify_fail("你基本輕功修為有限，難以修煉金雁功。\n");

        if( query("max_neili", me)<500 )
                return notify_fail("你內力修為太淺，難以修煉金雁功。\n");
        return 1;
}
int practice_skill(object me)
{
        if( query("qi", me)<70 )
                return notify_fail("你的體力太差了，不能練金雁功。\n");

        if( query("neili", me)<60 )
                return notify_fail("你的內力太差了，不能練金雁功。\n");

        me->receive_damage("qi", 58);
        addn("neili", -55, me);
        return 1;
}
string query_dodge_msg(string limb)
{
        return dodge_msg[random(sizeof(dodge_msg))];
}
int query_effect_dodge(object attacker, object me)
{
        int lvl;

        lvl = me->query_skill("jinyan-gong", 1);
        if (lvl < 30)  return 0;
        if (lvl < 50)  return 10;
        if (lvl < 100) return 20;
        if (lvl < 150) return 30;
        if (lvl < 200) return 40;
        return 50;
}

string perform_action_file(string action)
{
        return __DIR__"jinyan-gong/" + action;
}

int learn_bonus() { return 20; }
int practice_bonus() { return 20; }
int success() { return 20; }
int power_point(object me) { return 1.2; }

int help(object me)
{
        write(HIC"\n金雁功："NOR"\n");
        write(@HELP

    金雁功為全真派本門輕功。

        學習要求：
          先天功10級
HELP
        );
        return 1;
}
