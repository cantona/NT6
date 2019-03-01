// yunv-xinfa.c 玉女心法
// Last Modified by winder on Mar. 10 2000

#include <ansi.h>;

inherit FORCE;
string type() { return "martial"; }
string martialtype() { return "force"; }
int query_neili_improve(object me)
{
        int lvl;

        lvl = (int)me->query_skill("yunv-xinfa", 1);
        return lvl * lvl * 15 * 12 / 100 / 200;
}

int valid_force(string force)
{
        // return (force == "minggu-xinfa");
        return 1;
}

int learn_bonus() { return 0; }
int practice_bonus() { return 0; }
int success() { return 10; }
int power_point() { return 1; }

int valid_enable(string usage) { return usage == "force"; }

int valid_learn(object me)
{
        if( (!me->query_family() ||
            me->query_family() != "古墓派") && (!query("reborn/times", me) || member_array("古墓派", query("reborn/fams", me)) == -1) )
                return notify_fail("你不是古墓派中人，無法修習！\n");

        if( query("gender", me) == "無性" )
                return notify_fail("你無根無性，陰陽難調，不能修習玉女心法。\n");

        if ((int)me->query_skill("force", 1) < 150)
                return notify_fail("你的基本內功火候還不夠，不能修習玉女心法。\n");

        if ((int)me->query_int() < 42)
                return notify_fail("你的後天悟性不足，無法領悟玉女心法。\n");

        if( query("max_neili", me)<1000 )
                return notify_fail("你的內力修為不足，難以領會玉女心法。\n");

        return ::valid_learn(me);
}

int practice_skill(object me)
{
        return notify_fail("玉女心法只能用學(learn)來增加熟練度。\n");
}
mixed hit_ob(object me, object victim)
{
        int lvl;
        int damage_bonus;
        string wn;
        object weapon;

        lvl = me->query_skill("yunv-xinfa", 1);

        if (lvl < 150
             || query("neili", me)<300
             || !objectp(weapon=query_temp("weapon", me) )
            || random(me->query_skill("force") / 6) < victim->query_con()
            || random(3) > 1
             || !query("can_learn/yunv-xinfa/wall", me) )
                return 0;

        wn = weapon->name();

        if( query("skill_type", weapon) == "sword"
            && me->query_skill_mapped("sword") == "suxin-jian")
        {
                addn("neili", -50, me);
                damage_bonus = lvl / 5 + random(lvl / 5);

                victim->receive_damage("qi", damage_bonus, me);
                victim->receive_wound("qi", damage_bonus * 2 / 3, me);

                return HIW "$N" HIW "手中" + wn + HIW "忽的一振，將玉"
                       "女心經功力運于劍端，漫出無邊寒意。\n" NOR;
        } else
        if( query("skill_type", weapon) == "whip"
            && me->query_skill_mapped("whip") == "yinsuo-jinling")
        {
                addn("neili", -50, me);
                damage_bonus = lvl / 4 + random(lvl / 4);

                victim->receive_damage("qi", damage_bonus, me);
                victim->receive_wound("qi", damage_bonus * 2 / 3, me);

                return HIW "$N" HIW "一聲嬌喝，將玉女心法功力運至" + wn +
                       HIW "之上，姿勢妙曼，令人肅然起敬。\n" NOR;
        }
}
int difficult_level()
{
        return 400;
}

string exert_function_file(string func)
{
        return __DIR__"yunv-xinfa/" + func;
}

int help(object me)
{
        write(HIC"\n玉女心法："NOR"\n");
        write(@HELP

    古墓內功講究一個“靜”字，唯有平心靜氣、擺脫世俗之擾才
能修習上乘武功。玉女心經修煉難度很大，學習者要不急不躁，循
序漸進方有成功之望。可以尋覓本門秘籍《玉女心經》上下冊研讀。

        學習要求：
                基本內功10級
                不能做太監
HELP
        );
        return 1;
}
