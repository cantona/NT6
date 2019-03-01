// xixing-dafa.c 吸星大法

#include <ansi.h>;
inherit FORCE;

string type() { return "martial"; }
string martialtype() { return "force"; }
int valid_force(string force)
{
        return 1;
}

int query_neili_improve(object me)
{
        int lvl;

        lvl = (int)me->query_skill("xixing-dafa", 1);
        return lvl * lvl * 15 * 20 / 100 / 200;
}

int learn_bonus() { return 0; }
int practice_bonus() { return 0; }
int success() { return 10; }
int power_point() { return 1; }

int valid_enable(string usage) { return usage == "force"; }

int valid_learn(object me)
{
        int lvl = (int)me->query_skill("xixing-dafa", 1);

        if( query("character", me) == "光明磊落" )
                return notify_fail("你心中暗道：這種害人的武功，我學它作甚？\n");

        if( !query("family/family_name", me) || query("family/family_name", me) != "日月神教" )
                return notify_fail("你不是日月神教的人，難以修煉吸星大法。\n");

        if( query("con", me)<20 )
                return notify_fail("你試著按照法門運轉了一下內息，忽然覺得心火如"
                                   "焚，丹田卻是一陣冰涼！\n");

        if ((int)me->query_skill("force", 1) < 100)
                return notify_fail("你的基本內功修為不足，難以修煉吸星大法。\n");

        if( !query("can_learn/xixing-dafa/ren", me )
            && query("max_neili", me )
           && lvl < 200
           && lvl >= 10)
                return notify_fail("你沒有按照吸星大法的訣竅將內力散去，現在還不"
                                   "敢妄自繼續修行大法。\n");

        return ::valid_learn(me);
}

int practice_skill(object me)
{
        return notify_fail("吸星大法只能用學(learn)的來增加熟練度。\n");
}

mixed valid_damage(object ob, object me, int damage, object weapon)
{
        mapping result;
        int ap, dp;
        int jiali;

        if ((int)me->query_skill("xixing-dafa", 1) < 80
           || ! living(me))
                return;

        if( (jiali=query("jiali", ob))<1
            || ob->query_skill_mapped("force") == "taixuan-gong")
                return;

        ap = ob->query_skill("force");
        dp = me->query_skill("force");
        if (ap / 2 + random(ap) < dp)
        {
                if( query("neili", me)<query("max_neili", me)*15/10 )
                        addn("neili", jiali, me);

                result = ([ "damage" : -damage ]);

                switch (random(4))
                {
                case 0:
                        result += ([ "msg" : HIM "$N" HIM "只覺得內力源源而瀉"
                                             "，不由得大吃一驚。\n" NOR ]);
                        break;
                case 1:
                        result += ([ "msg" : HIM "$N" HIM "只覺得發出的內力猶"
                                             "如石沉大海，不知所蹤。\n" NOR ]);
                        break;
                case 2:
                        result += ([ "msg" : HIM "$N" HIM "只覺得發出的內力猶"
                                             "無影無蹤，渾然不知著落。\n" NOR ]);
                        break;
                default:
                        result += ([ "msg" : HIM "$N" HIM "不住催動內力，但是"
                                             "只覺得$n竟似毫不費力。\n" NOR ]);
                        break;
                }
                return result;
        }
}
void check_count(object me)
{
        if( !query("can_learn/xixing-dafa/ren", me )
            && query("max_neili", me) >= 3000
            && query("exception/xixing-count", me)>1000 )
        {
                me->apply_condition("xixing-fanshi",
                        me->query_condition("xixing-fanshi") +
                        query("exception/xixing-count", me)/10);
                delete("exception/xixing-count", me);
        }
}

void skill_improved(object me)
{
        addn("exception/xixing-count", me->query_skill("xixing-dafa",1)+1, me);
        check_count(me);
}
string exert_function_file(string func)
{
        return __DIR__"xixing-dafa/" + func;
}

int help(object me)
{
        write(HIC"\n吸星大法："NOR"\n");
        write(@HELP

    日月神教黑木崖的一種內功。

    吸星大法創自北宋年間的逍遙派，分為北冥神功和化功大法兩
路，後來從大理段氏和星宿派分別傳落，合而為一，稱為吸星大法。
主要是繼承了化功大法一路，修習者當令丹田常如空箱，恆似深谷，
空箱可貯物，深谷可容水。若有內息，散之于任脈諸穴。
    吸星大法只能拜任我行為師學習，非有相當機緣不能學到。

        學習要求：
                葵花心法
                基本內功10級
                盡量少的正氣
                不能學習佛門心法
                散功
HELP
        );
        return 1;
}
