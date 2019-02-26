// chanchu_bufa.c 蟾蜍步法
// Last Modified by sir on 10.18.2001

#include <ansi.h>;
inherit SKILL;
string type() { return "martial"; }
string martialtype() { return "dodge"; }

string *dodge_msg = ({
        "只見$n一招"HIY"「蟾飛九天」"NOR"，身體向上筆直地縱起丈餘，躲過了$N這一招。\n",
        "但是$n一個使出"HIY"「蛙鳴震天」"NOR"，身形飄忽，輕輕一縱，早已避開。\n",
         "$n一招"HIY"「蛙入稻田」"NOR"，身行隨意轉，倏地往一旁挪開了三尺，避過了這一招。\n",
        "可是$n一個"HIY"「蟾蜍撲蟲」"NOR"，側身一讓，$N這一招撲了個空。\n",
        "卻見$n"HIY"「蟾翻白肚」"NOR"，足不點地，往旁竄開數尺，躲了開去。\n",
        "$n身形一招"HIY"「金蟾歸月」"NOR"，身形微晃，有驚無險地避開了$N這一招。\n"
});

int valid_enable(string usage) { return (usage=="dodge") || (usage=="move"); }
int valid_learn(object me)
{
        return 1;
}

int practice_skill(object me)
{
        if( query("qi", me)<80 )
                return notify_fail("你的體力太差了，不能練蟾蜍步法。\n");

        if( query("neili", me)<80 )
                return notify_fail("你的內力不夠。\n");

        me->receive_damage("qi", 70);
        addn("neili", -70, me);

        return 1;
}

string query_dodge_msg(string limb)
{
        return dodge_msg[random(sizeof(dodge_msg))];
}

mixed valid_damage(object ob, object me, int damage, object weapon)
{
        mixed result;
        int ap, dp, mp;

        if ((int)me->query_skill("chanchu-bufa", 1) < 100 ||
            ! living(me))
                return;

        mp = ob->query_skill("count", 1);
        ap = ob->query_skill("force") + mp;
        dp = me->query_skill("dodge", 1) / 2 +
             me->query_skill("chanchu-bufa", 1) / 2;

        if (ap / 2 + random(ap) < dp)
        {
                result = ([ "damage" : -damage ]);
                switch (random(3))
                {
                case 0:
                        result += (["msg" : WHT "$n" WHT "身體向下一伏，手腳飛快地攪動起地上的塵土，匪所思疑地往後一縱，\n"
                                            "$N只見眼前瀰漫着一陣嗆人塵煙，視線一片模糊！\n" NOR]);
                        break;
                case 1:
                        result += (["msg" : WHT "$n" WHT "身體向後一翻，向後縱出數丈之遠，"
                                            "$N情急之下，額頭的汗都出來了！\n" NOR]); ;

                        break;
                default:
                        result += (["msg" : WHT "$n" WHT "一個側身閃過，"
                                            "竟然不留一絲痕跡。\n" NOR]);
                        break;
                }
                return result;
        } else
        if (mp >= 100)
        {
                switch (random(3))
                {
                case 0:
                        result = WHT "$n" WHT "身體向下一伏，手腳飛快地攪動起地上的塵土，匪所思疑地往後一縱，\n"
                                 "$N" WHT "猛地向前一衝，早突過塵煙，來到$n的身後。\n" NOR;
                        break;
                case 1:
                        result = WHT "$n" WHT "身體向後一翻，向後縱出數丈之遠，\n"
                                 "$N一個箭步就衝到了$n面前！\n" NOR;
                        break;
                default:
                        result = WHT "$n" WHT "一個側身閃過，"
                                 "$N就象影子一樣緊緊地咬住！\n" NOR;
                        break;
                }
                COMBAT_D->set_bhinfo(result);
        }
}

int query_effect_dodge(object attacker, object me)
{
        int lvl;
        lvl = me->query_skill("chanchu-bufa", 1);
        if (lvl < 80)  return 0;
        if (lvl < 200) return 40;
        if (lvl < 280) return 70;
        if (lvl < 350) return 90;
        return 110;
}


int learn_bonus() { return 25; }
int practice_bonus() { return 25; }
int success() { return 20; }
int power_point() { return 1.1; }

int help(object me)
{
        write(HIC"\n蟾蜍步法："NOR"\n");
        write(@HELP

    白駝山本門輕功。

        學習要求：
           蛤蟆功10級
HELP
        );
        return 1;
}
