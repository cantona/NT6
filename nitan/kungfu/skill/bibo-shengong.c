// bibo-shengong.c 碧波神功

#include <ansi.h>;

inherit FORCE;
string type() { return "martial"; }
string martialtype() { return "force"; }

int learn_bonus() { return 0; }
int practice_bonus() { return 0; }
int success() { return 10; }
int power_point(object me) { return 1; }

int valid_enable(string usage) { return usage=="force"; }

int query_neili_improve(object me)
{
        int lvl;

        lvl = (int)me->query_skill("bibo-shengong", 1);
        return lvl * lvl * 15 * 10 / 100 / 200;
}

int valid_force(string force)
{
        return 1;
}

int valid_learn(object me)
{
        int lvl = (int)me->query_skill("bibo-shengong", 1);

        if( query("gender", me) == "無性" && lvl>49 )
                return notify_fail("你無根無性，陰陽不調，難"
                                   "以領會高深的碧波神功。\n");

/*
        if (me->query_skill("chuixiao-jifa", 1) < 100)
                return notify_fail("你沒有精通吹簫技法，無法"
                                   "領會碧波神功的奧祕。\n");
*/

        return ::valid_learn(me);
}

int practice_skill(object me)
{
        return notify_fail("碧波神功只能用學的，或是從運用(exert)中增加熟練度。\n");
}

string exert_function_file(string func)
{
        return __DIR__"bibo-shengong/" + func;
}

mapping curing_msg(object me)
{
        return ([
"apply_short"        :me->name()+"正踏著八卦方位緩步行走療傷。",
"start_self"    :HIY"你運氣凝神，腳下緩緩踏起八卦方位，開始運用碧波神功調理傷勢。\n"NOR,
"on_self"   :HIG"你腳下緩緩踏著八卦方位，步法暗合五行九宮，一邊潛運碧波神功調理傷勢。\n"NOR,
"start_other"        :HIG""+me->name()+"緩步走動，呼吸由急促漸漸轉而悠長，面上青氣時隱時現。\n"NOR,
"finish_self"        :HIY"你緩步行走多時，自覺經脈順暢，內傷盡去，在東方乙木之位停下了步伐。\n"NOR,
"finish_other"        :me->name()+"療傷已畢，臉上青氣一閃而退，停下腳步，看上去氣色飽滿，精神抖擻。\n",
"unfinish_self"        :"你正以奇門步法調勻真氣，忽覺內息後繼乏力，祗得停下腳步，暫緩療傷。\n",
"unfinish_other":me->name()+"停下腳步，臉上青氣隱退，氣色看起來好多了。\n",
"halt_self"        :"你吐氣納息，硬生生地將內息壓了下去，停下了腳步。\n",
"halt_other"        :me->name() +"緩緩停下步伐，身子一震，吐出一口瘀血，臉上青氣隨之散逸。\n",
"dazuo"                :"你閉上眼睛，腳踏八卦，步合五宮，耳中潮起潮落，內息漸長。\n",
"tuna"                :"你緩緩地呼吸，胸中似有大海浪潮洶湧彭湃，腦中卻寧靜一片，精神振奮。\n",
        ]);
}

int help(object me)
{
        write(HIC"\n碧波神功："NOR"\n");
        write(@HELP

    這是東海桃花島黃藥師所創的一門內功心法。傳説當初黃藥師行
船海上，忽見碧海潮生，碧波洶湧，聲勢驚人，在與風浪搏鬥之餘，
豁然頓悟，創出一門陽剛陰柔相結合的內功，此謂碧波神功。

        學習要求：
                基本內功10級
                太監無法領悟50級以上的碧波神功
HELP
        );
        return 1;
}
