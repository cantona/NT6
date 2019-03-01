// beimin-shengong.c 北冥神功
// Last Modified by winder on Mar. 10 2000

#include <ansi.h>;
inherit FORCE;
string type() { return "martial"; }
string martialtype() { return "force"; }

int valid_enable(string usage) { return usage=="force"; }
int learn_bonus() { return 0; }
int practice_bonus() { return 0; }
int success() { return 10; }
int power_point(object me) { return 1; }

int valid_force(string force) { return 1; }

// beiming 內力應該高10倍
int query_neili_improve(object me)
{
        int lvl;

        lvl = (int)me->query_skill("beiming-shengong", 1);
        return lvl /10 * lvl /10 * 28 * 15 / 10 / 10;
}

int valid_learn(object me)
{
        int lvl = (int)me->query_skill("beiming-shengong", 1);

        if( query("gender", me) == "無性" && lvl>49 )
                return notify_fail("你無根無性，陰陽不調，難以領會高深的北冥神功。\n");

        if( query("con", me)<24 )
                return notify_fail("算了吧，你先天根骨不好，別強學了。\n");

        if( query("int", me)<30 )
                return notify_fail("算了吧，你先天悟性不好，別強學了。\n");

        if (me->query_skill("force", 1) <= lvl)
                return notify_fail("你的基本內功基礎不夠，再學下去會走火入魔的。\n");

        return ::valid_learn(me);
}

int practice_skill(object me)
{
        return notify_fail("北冥神功只能用學的，或是從運用(exert)中增加熟練度。\n");
}

mixed valid_damage(object ob, object me, int damage, object weapon)
{
        mapping result;
        int ap, dp;
        int jiali;

        if ((int) me->query_skill("beiming-shengong", 1) < 80 ||
            ob->query_skill_mapped("force") == "taixuan-gong" ||
            ! living(me))
                return;

        if( (jiali=query("jiali", ob))<1 )
                return;

        ap = ob->query_skill("force") + ob->query_skill("dodge");
        dp = me->query_skill("force") + me->query_skill("dodge");
        if (ap / 2 + random(ap) < dp)
        {
                result = ([ "damage" : -damage ]);

                switch (random(3))
                {
                case 0:
                        result += ([ "msg" : HIM "$N" HIM "只覺得內力源源而瀉"
                                             "，不由得大吃一驚。\n" NOR ]);
                        break;
                case 1:
                        result += ([ "msg" : HIM "$N" HIM "只覺得發出的內力猶"
                                             "如石沉大海，不知所蹤。\n" NOR ]);
                        break;

                default:
                        result += ([ "msg" : HIM "$N" HIM "不住催動內力，但是"
                                             "只覺得$n竟似毫不費力。\n" NOR ]);
                        break;
                }
                return result;
        }
}

mixed hit_ob(object me, object victim, int damage_bonus, int factor)
{
        int percent,force1,force2,dodge1,dodge2,lv1,lv2;

        force1 = victim->query_skill("force");
        force2 = me->query_skill("force");
        dodge1 = victim->query_skill("dodge");
        dodge2 = me->query_skill("dodge");

        lv1= force1*dodge1;
        lv2= force2*dodge2;

        lv2 = lv2*3/2;
        if ((int)me->query_skill("beiming-shengong",1)>100
         && !query_temp("weapon", victim )
         && query("max_neili", victim)>500
        && lv1/2 + random(lv2) > lv1 )
        {
                addn("max_neili", -1*(5+(me->query_skill("beiming-shengong",1)/100)), victim);
                if( query("max_neili", me)<me->query_current_neili_limit() )
                addn("max_neili", 1*(5+(me->query_skill("beiming-shengong",1)/100)), me);
                return ([ "msg": HIR "$n只覺息關一開，一股內力被$N吸了過去！\n" NOR ]);
        }

        return damage_bonus;
}

int difficult_level()
{
        return 200;
}

string exert_function_file(string func)
{
        return __DIR__"beiming-shengong/" + func;
}
int help(object me)
{
        write(HIC"\n北冥神功："NOR"\n");
        write(@HELP

    北冥神功為逍遙派無上內功。
    莊子‘逍遙遊’有雲：‘窮發之北有冥海者，天池也。有魚焉，
其廣數千裡，未有知其修也。’又雲：‘且夫水之積也不厚，則其
負大舟也無力。覆杯水于坳堂之上，則芥為之舟；置杯焉則膠，水
淺而舟大也。’是故逍遙派武功，以積蓄內力為第一要義。內力既
厚，天下武功無不為我所用，猶之北冥，大舟小舟無不載，大魚小
魚無不容。是故內力為本，招數為末。北冥神功系引世人之內力而
為我有。北冥大水，非由自生。語雲：百川匯海，大海之水以容百
川而得。汪洋巨浸，端在積聚。
    世人練功，皆自雲門而至少商，我逍遙派則反其道而行之，自
少商而至雲門，拇指與人相接，彼之內力即入我身，貯于雲門等諸
穴。然敵之內力若勝于我，則海水倒灌而入江河，兇險莫甚。逍遙
派旁支，未窺要道，惟能消敵內力，不能引而為我用，猶日取千金
而復棄之于地，暴殄珍物，殊可哂也。

        學習要求：
                基本內功10級
                太監無法學到50級以上的北冥神功
HELP
        );
        return 1;
}
