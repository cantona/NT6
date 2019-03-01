// yijing.c  『黃帝內經』
// Last Modified by winder on Jul. 12 2002

#include <ansi.h>

inherit ITEM;
void setup()
{}

void create()
{
        set_name("黃帝內經", ({ "yijing", "book" }));
        set_weight(600);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "本");
                set("long", "這是一本線裝書，裡面密密麻麻的寫滿了文字。\n");
                set("value", 300);
                set("material", "paper");
        }
}

void init()
{
        add_action("do_study","study");
        add_action("do_study", "du");
}

int do_study(string arg)
{
        object ob, me = this_player(), where = environment(me);
        int cost;

        if( query("pigging", where) )
        {
                write("你還是專心拱豬吧！\n");
                return 1;
        }
        if (me->is_busy()) {
                write("你現在正忙著呢。\n");
                return 1;
        }
        if( me->is_fighting() )
        {
                write("你無法在戰鬥中專心下來研讀新知！\n");
                return 1;
        }
        if (!id(arg))
        {
                write("你要讀什麼？\n");
                return 1;
        }
        if( (int)me->query_skill("literate", 1) < 20 )
        {
                write("你識的字不多，讀不懂書中的講解。\n");
                return 1;
        }
        if( (int)me->query_skill("medicine", 1) > 29 )
        {
                write("閣下對醫理略有見識，不必再讀『黃帝內經』了。\n");
                return 1;
        }
        if( query("jing", me)<80 )
        {
                write("你的精神欠佳，捧著醫經連打呵欠。\n");
                return 1;
        }
        if( query("sg/exp", me)<1000 && !query_temp("sgbook_poison", me) )
        {
                message_vision("$N伸食指在口中一舔，蘸了些唾液翻閱起書來。\n", me);
                set_temp("sgbook_poison", 1, me);
                call_out("poison", 5, me);
        }
        cost=30+600/query("int", me);
        if( query_temp("lu/yi1", me))cost/=2;
        cost += random(cost / 2);

        me->improve_skill("medicine", random(2 * me->query_int()));
        me->receive_damage("jing", cost, "心力絞瘁死了");
        message_vision("$N一會兒翻閱著『黃帝內經』，一會兒苦思冥想。\n", me);
        return 1;
}

void poison(object me)
{
        tell_object(me, HIR"你突然感到一陣暈旋，原來是書上劇毒發作了！\n"NOR);
        me->receive_wound("qi", 50, "劇毒發作死了");
        call_out("extra", 20, me);
}

void extra(object me)
{
        delete_temp("sgbook_poison", me);
        tell_object(me, HIR"你突然感到一陣暈旋，原來是書上劇毒發作了！\n"NOR);
        message("vision", me->name()+"腳下幾個踉蹌，雙腳一蹬便不動了，眼、耳、鼻、口中都流出黑血來！\n", environment(me), ({me}) );
        if( (int)me->query_skill("force") < 120 )
                me->receive_wound("qi",query("max_qi", me)+100,"劇毒發作死了");
        else me->unconcious();
}