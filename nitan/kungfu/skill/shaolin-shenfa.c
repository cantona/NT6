// shaolin-shenfa.c 少林身法

#include <ansi.h>;
inherit SKILL;
string type() { return "martial"; }
string martialtype() { return "dodge"; }

string *dodge_msg = ({
        "$n一式"HIW"「一葦渡江」"NOR"，前後腳腳尖腳跟相靠，身體如行雲流水般滑出丈余。\n",
        "$n一式"BLU"「雨燕掠波」"NOR"，雙臂前伸，全身貼地平飛，頓時閃過了$N的凌厲攻勢。\n",
        "$n一式"HIC"「移步換形」"NOR"，足不動，手不抬，一轉眼間便繞到了$N的身後。\n",
        "$n一式"HIG"「分身化影」"NOR"，一轉身間，四面八方飄動著無數個$n的身影，令$N手無足措。\n",
        "$n一式"HIY"「孤騖落日」"NOR"，全身筆直，拔地而起，在半空中一轉，已落到幾丈遠的地方。\n",
        "$n一式"HIB"「鴻雁雙飛」"NOR"，兩臂鵬舉如翼，在剌剌風聲中，從$N頭頂橫躍而過。\n",
        "$n一式"HIY"「蒼龍出水」"NOR"，雙腳點地，全身化為一道白影，急速繞著$N打了幾轉。\n",
        "$n一式"GRN"「稚鳳歸巢」"NOR"，身體如陀螺般急轉，氣流形成一個個漩渦，令$N陷身其間，動彈不得。\n",
});

int valid_enable(string usage) { return (usage=="dodge") || (usage=="move"); }
int valid_learn(object me)
{
        return 1;
}
int practice_skill(object me)
{
        if( query("qi", me)<30 || query("neili", me)<6 )
                return notify_fail("你的體力太差了，無法能練習少林身法。\n");

        me->receive_damage("qi", 30);
        addn("neili", -6, me);
        return 1;
}

string query_dodge_msg(string limb)
{
        return dodge_msg[random(sizeof(dodge_msg))];
}

int learn_bonus() { return 15; }
int practice_bonus() { return 15; }
int success() { return 15; }
int power_point(object me) { return 1.3; }
int river_point() {return 2;} // 過河比普通容易 越高越好
string river_go_msg() {        return HIW"$N撿起一段蘆葦拋入水中，緊跟著飛身躍上蘆葦，長袖飄飄，渡過了水面。\n"NOR;}
string river_come_msg() {        return HIW"只見$N踩著一段蘆葦從對岸過來，姿態瀟洒地落在岸邊。\n"NOR;}
/*
mixed valid_damage(object ob, object me, int damage, object weapon)
{
        mixed result;
        int ap, dp, mp;

        if ((int)me->query_skill("shaolin-shenfa", 1) < 100 ||
            ! living(me))
                return;

        mp = ob->query_skill("martial-cognize", 1);
        ap = ob->query_skill("force") + mp;
        dp = me->query_skill("dodge", 1) / 2 +
             me->query_skill("shailin-shengfa", 1);

        // 一個經典的算法
        if (ap / 2 + random(ap) < dp)
        {
                result = ([ "damage": -damage ]);
                // 去掉所有的傷害寫法

                switch (random(3))
                {
                case 0:
                        result += (["msg" : HIC "$n" HIC "一式「稚鳳歸巢」，身體如陀螺般急轉，氣流形成一個個漩渦，令$N陷身其間，動彈不得。\n" NOR]);
                        if (! ob->is_busy())
                        ob->start_busy(random(3));
                        break;

                case 1:
                        result += (["msg" : HIC "$n" HIC "一式「一葦渡江」，前後腳腳尖腳跟相靠，身體如行雲流水般滑出丈余。\n" NOR]);
                        if (! ob->is_busy())
                        ob->start_busy(random(1));
                        break;

                default:
                        result += (["msg" : HIC "$n" HIC "一式「分身化影」，一轉身間，四面八方飄動著無數個$n的身影，令$N手無足措。\n" NOR]);
                        break;
                }
                return result;
        }
}
*/

string perform_action_file(string action)
{
        return __DIR__"shaolin-shenfa/" + action;
}

int help(object me)
{
        write(HIC"\n少林身法："NOR"\n");
        write(@HELP

    少林身法為少林本門輕功身法。少林輕功名冠天下。

        學習要求：
                混元一氣功10級
HELP
        );
        return 1;
}

