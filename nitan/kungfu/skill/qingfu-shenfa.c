// This program is a part of NT MudLIB
// qingfu-shenfa.c 青蝠身法

#include <ansi.h>;
inherit SKILL;
string type() { return "martial"; }
string martialtype() { return "dodge"; }

string *dodge_msg = ({
        "只見$n一招"HIC"「福滿乾坤」"NOR"，身形陡然縱起，躲過了$N這一招。\n",
        "$n一式"HIC"「五蝠獻壽」"NOR"，身形晃動，向一旁飄出，避開了$N這一招。。\n",
        "$n使出"HIC"「洞天福地」"NOR"，一個空心筋斗向後翻出，避開了$N的凌厲攻勢。\n",
        "$n一招"HIC"「雲龍百蝠」"NOR"，身隨意轉，$N只覺眼前一花，$n已繞至$N的身後。\n",
});

int valid_enable(string usage) { return usage == "dodge" || usage == "move"; }
int valid_learn(object me)
{
        /*
        if( query("dex", me)<26 )
                return notify_fail("你先天身法太差，無法學習青蝠身法。\n");
        */

        if (me->query_skill("dodge", 1) < 100)
                return notify_fail("你輕功根基不足，無法學習青蝠身法。\n");
        return 1;
}

int practice_skill(object me)
{
        if( (int)query("qi", me) < 60 )
                return notify_fail("你的體力太低了，不能練青蝠身法。\n");

        if( (int)query("neili", me) < 60 )
                return notify_fail("你的內力不夠練青蝠身法。\n");

        me->receive_damage("qi", 50);
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

        lvl = me->query_skill("qingfu-shenfa", 1);
        if (lvl < 50)  return 0;
        if (lvl < 100) return 10;
        if (lvl < 150) return 20;
        if (lvl < 200) return 30;
        if (lvl < 250) return 40;
        if (lvl < 300) return 50;
        if (lvl < 350) return 60;
        return 80;
}

mixed valid_damage(object ob, object me, int damage, object weapon)
{
        mixed result;
        int ap, dp, mp;

        if ((int)me->query_skill("qingfu-shenfa", 1) < 100 ||
            ! living(me) || random(3) != 1)
                return;

        mp = ob->query_skill("count", 1);
        ap = ob->query_skill("dodge") + mp;
        dp = me->query_skill("dodge", 1) / 2 +
             me->query_skill("qingfu-shenfa", 1);

        if (ap / 2 + random(ap) < dp)
        {
                result = ([ "damage": -damage ]);

                switch (random(2))
                {
                case 0:
                        result += (["msg" : HIG "只見$n" HIG "長嘯一聲猶如一隻蝙"
                                            "蝠一樣縱身而起，於半空倒立，$N" HIG
                                            "這招卻撲了個空。\n" NOR]);
                        break;

                default:
                        result += (["msg" : HIG "但見$n" HIG "身法輕盈無比，忽然躍"
                                    "高忽而落下，令$N" HIG "完全無從攻擊。\n" NOR]);
                        break;
                }
                return result;
        } else
        if (mp >= 100)
        {
                switch (random(2))
                {
                case 0:
                        result = HIY "只見$n" HIY "長嘯一聲猶如一隻蝙"
                                 "蝠一樣縱身而起，於半空倒立，可是$N"
                                 HIY "精通易理，將其中虛實辨得清清楚楚。\n" NOR;

                default:
                        result = HIY "但見$n" HIY "身法輕盈無比，忽然躍"
                                     "高忽而落下，$N" HIY "不假思索，飛"
                                     "身出招，更是巧妙無方。\n" NOR;
                        break;
                }
                COMBAT_D->set_bhinfo(result);
        }
}

int learn_bonus() { return 10; }
int practice_bonus() { return 10; }
int success() { return 10; }
int power_point(object me) { return 1.4; }

int help(object me)
{
        write(HIC"\n青蝠身法："NOR"\n");
        write(@HELP

    明教的本門輕功身法。主要是從韋一笑的輕功身法而來。

        學習要求：
                無
HELP
        );
        return 1;
}