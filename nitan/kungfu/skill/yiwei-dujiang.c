// yiwei-dujiang.c 南少林身法一葦渡江

#include <ansi.h>;
inherit SKILL;
string type() { return "martial"; }
string martialtype() { return "dodge"; }

string *dodge_msg = ({
"$n一式"HIW"「一葦渡江」"NOR"，前後腳腳尖腳跟相靠，身體如行雲流水般滑出丈余。\n",
"$n一式"BLU"「雨燕掠波」"NOR"，雙臂前伸，全身貼地平飛，頓時閃過了$N的凌厲攻勢。\n",
"$n一式"HIG"「移步換形」"NOR"，足不動，手不抬，一轉眼間便繞到了$N的身後。\n",
"$n一式"HIC"「分身化影」"NOR"，一轉身間，四面八方飄動著無數個$n的身影，令$N手無足措。\n",
"$n一式"HIY"「孤騖落日」"NOR"，全身筆直，拔地而起，在半空中一轉，已落到幾丈遠的地方。\n",
"$n一式"GRN"「鴻雁雙飛」"NOR"，兩臂鵬舉如翼，在剌剌風聲中，從$N頭頂橫躍而過。\n",
"$n一式"HIY"「蒼龍出水」"NOR"，雙腳點地，全身化為一道白影，急速繞著$N打了幾轉。\n",
"$n一式"HIG"「稚鳳歸巢」"NOR"，身體如陀螺般急轉，氣流形成一個個漩渦，令$N陷身其間，動彈不得。\n",
});


int valid_enable(string usage) { return (usage=="dodge") || (usage=="move"); }
int valid_learn(object me)
{
        if( query("dex", me)<25 || query("int", me)<25 )
               return notify_fail("就你這身法還練一葦渡江功？小心弄折了腿。\n");
        return 1;
}

int practice_skill(object me)
{
        if( query("qi", me)<30 || query("neili", me)<6 )
                return notify_fail("你的體力太差了，無法練習一葦渡江。\n");
        me->receive_damage("qi", 30);
        addn("neili", -6, me);
        return 1;
}

string query_dodge_msg(string limb)
{
        return dodge_msg[random(sizeof(dodge_msg))];
}
int query_effect_dodge(object victim, object me)
{
        int lvl;

        lvl = me->query_skill("yiwei-dujiang", 1);
        if (lvl < 80)  return 0;
        if (lvl < 200) return 100;
        if (lvl < 280) return 150;
        if (lvl < 350) return 200;
        return 250;
}

int difficult_level()
{
        return 300;
}

mixed valid_damage(object ob, object me, int damage, object weapon)
{
        mixed result;
        int ap, dp, mp;

        if ((int)me->query_skill("yiwei-dujiang", 1) < 100 ||
            ! living(me))
                return;

        mp = ob->query_skill("martial-cognize", 1);
        ap = ob->query_skill("force") + mp;
        dp = me->query_skill("dodge", 1) / 2 +
             me->query_skill("yiwei-dujiang", 1);

        if (ap / 2 + random(ap) < dp)
        {
                result = ([ "damage": -damage ]);
                switch (random(3))
                {
                case 0:
                        result += (["msg" : HIY "$n" HIY "一招「蜻蜓點水」，腳尖往地一點，身體沖天而起，"
                                            "頓時,$N一招失手！\n" NOR]);
                        break;
                case 1:
                        result += (["msg" : HIY "$n" HIY "一個「白駒過隙」，身行一側，提氣一縱，"
                                            "$N猛然一招過去，已經收不住去勢！\n" NOR]);
                        if (! ob->is_busy())
                                ob->start_busy(random(2));
                        break;
                default:
                        result += (["msg" : HIY "$n" HIY "使出「鷂子穿林」，向一旁平平掠出，"
                                            "一個轉身折身而下。\n" NOR]);
                        break;
                }
                return result;
        } else
        if (mp >= 100)
        {
                switch (random(3))
                {
                case 0:
                        result = HIY "$n" HIY "一招「蜻蜓點水」，腳尖往地一點，身體沖天而起,"
                                 "可是$N" HIY "早以洞察$n的企圖。搶佔了先機。\n" NOR;
                        break;
                case 1:
                        result = HIY "$n" HIY "一個「白駒過隙」，身行一側，提氣一縱，"
                                 "$N擰身而上，全力攻擊$n！\n" NOR;
                        break;
                default:
                        result = HIY "$n" HIY "使出「鷂子穿林」，向一旁平平掠出，"
                                 "$N冷笑幾聲，身行一拔往高處掠去，凌空搏擊$n！\n" NOR;
                        break;
                }
                COMBAT_D->set_bhinfo(result);
        }
}

string perform_action_file(string action)
{
        return __DIR__"yiwei-dujiang/" + action;
}

int learn_bonus() { return 15; }
int practice_bonus() { return 15; }
int success() { return 15; }
int power_point(object me) { return 1.3; }
int river_point() {return 2;} // 過河比普通容易 越高越好
string river_go_msg() {        return HIW"$N撿起一段蘆葦拋入水中，緊跟著飛身躍上蘆葦，長袖飄飄，渡過了水面。\n"NOR;}
string river_come_msg() {        return HIW"只見$N踩著一段蘆葦從對岸過來，姿態瀟洒地落在岸邊。\n"NOR;}

int help(object me)
{
        write(HIC"\n一葦渡江："NOR"\n");
        write(@HELP

    南少林身法一葦渡江

        學習要求：
           基本內功10級
HELP
        );
        return 1;
}


