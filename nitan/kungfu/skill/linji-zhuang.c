// linji-zhuang.c 臨濟十二莊

#include <ansi.h>
inherit FORCE;
string type() { return "martial"; }
string martialtype() { return "force"; }

int learn_bonus() { return 0; }
int practice_bonus() { return 0; }
int success() { return 10; }
int power_point(object me) { return 1; }
int valid_force(string force) { return 1; }

int query_neili_improve(object me)
{
        int lvl;

        if( query("sex", me) )
                return 0;

        lvl = (int)me->query_skill("linji-zhuang", 1);
        return lvl / 100 * lvl * 24 * 15 / 200;
}

string *skill_name = ({
        "天字莊",
        "地字莊",
        "之字莊",
        "心字莊",
        "遊龍莊",
        "鶴翔莊",
        "旋風莊",
        "飄雲莊",
        "大字莊",
        "小字莊",
        "幽字莊",
        "冥字莊",
        "臨濟十二莊",
});

string *combo_name = ({
        "天地",
        "之心",
        "龍鶴",
        "風雲",
        "大小",
        "幽冥",
});
int valid_enable(string usage) { return usage == "force"; }

int valid_learn(object me)
{
        int i, np, nf, nh, ns, ts;
        nf = (int)me->query_skill("force", 1);
        nh = (int)me->query_skill("linji-zhuang", 1);
        np = (int)me->query_skill("mahayana", 1);

        if( query("gender", me) != "女性" )
                return notify_fail("你非女子，不能練習臨濟十二莊。\n");

        if (np <= nh && np < 200)
                return notify_fail("你的大乘涅磐功修為不夠，無法領會更高深的臨濟十二莊。\n");

        if (nf < 40)
                return notify_fail("你的基本內功火候還不夠，無法領會臨濟十二莊。\n");

        return 1;
}

int practice_skill(object me)
{
        return notify_fail("臨濟十二莊只能用學(learn)的來增加熟練度。\n");
}

void skill_improved(object me)
{
        int level = me->query_skill("linji-zhuang",1);
        int o_lvl=query("linji_lvl", me);
        int i;

        if ( level > 180 ) return;

        if ( level/15*15 == level ) {
                tell_object(me, HIG "你對「" + skill_name[level/15-1] + "」已豁然貫通。\n"NOR);
                if (o_lvl < level) {
                        tell_object(me, HIG"頓時你對基本內功的領悟也大大提高。\n"NOR);
                        for (i=0; i< level; i++)
                        me->improve_skill("force", level);
                }
        }

        if ( level/30*30 == level )
        if (o_lvl < level) {
                tell_object(me, HIY"此時你" + combo_name[level/30-1] +
                        "二莊融會貫通，一股柔和的真氣周遊全身，內力修為更精深了一層。\n"NOR);
                addn("max_neili", level, me);
        }


        if( o_lvl<level)set("linji_lvl", level, me);

}
/*
void skill_improved(object me)
{
        switch (me->query_skill("linji-zhuang",1))
        {
                case 30:
                        tell_object(me, HIG "你天地莊練成了! \n" NOR );
                        break;
                case 60:
                        tell_object(me, HIG "你之心莊練成了! \n" NOR );
                        break;
                case 90:
                        tell_object(me, HIG "你龍鶴莊練成了! \n" NOR );
                        break;
                case 120:
                        tell_object(me, HIG "你風雲莊練成了! \n" NOR );
                        break;
                case 150:
                        tell_object(me, HIG "你大小莊練成了! \n" NOR );
                        break;
                case 180:
                        tell_object(me, HIG "你幽冥莊練成了! \n" NOR );
                        break;
        }
        return;
}
*/
string exert_function_file(string func)
{
        return __DIR__"linji-zhuang/" + func;
}

int help(object me)
{
        write(HIC"\n臨濟十二莊："NOR"\n");
        write(@HELP

    臨濟十二莊，講動靜功修練，其排列順序是：天地之心、龍鶴
風雲、大小幽冥。練功的入手途徑，始于道家而歸于佛家的四智如
來境界。十二莊分別以十二個字標名，又可分別稱為天字莊、地字
莊、之字莊、心字莊、遊龍莊、鶴翔莊、旋風莊、飄雲莊、大字莊、
小字莊、幽字莊、冥字莊。每練成一莊都有對自身有莫大好處，特
別是當將十二莊互為反正融會貫通時，（指天地、之心、大小、龍
鶴、風雲、幽冥），對內力修為會有助益，並可增加可以使用的內
功特異功能。若能貫通幽冥二莊（１８０級）更可到達武林人士夢
寐以求的龍虎交會、水火既濟的境界、並熟通採制靈丹之妙法。
    臨濟十二莊可用于為他人療傷，有效程度比其他內功高，但不
可用于自療。

        學習要求：
                處女純陰之體
                出家人才能修習30級以上的臨濟十二莊
                相應級別的大乘涅磐功
                基本內功10級
                不犯戒
HELP
        );
        return 1;
}
