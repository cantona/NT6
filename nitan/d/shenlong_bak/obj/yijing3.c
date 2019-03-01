// yijing.c  『孫思邈千金方』
// Last Modified by winder on Jul. 12 2002

inherit ITEM;
void setup()
{}

void create()
{
        set_name("孫思邈千金方", ({ "yijing", "book" }));
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
        if (me->is_busy())
        {
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
        if( (int)me->query_skill("medicine", 1) < 60 )
        {
                write("你還是先去讀一讀『十四經發揮』吧。\n");
                return 1;
        }
        if( (int)me->query_skill("medicine", 1) > 89 )
        {
                write("閣下已熟知各類傷痛治療方法和藥物配制，不必再讀『孫思邈千金方』。\n");
                return 1;
        }
        if( query("jing", me)<150 )
        {
                write("你的精神欠佳，捧著醫經連打呵欠。\n");
                return 1;
        }
        cost=50+1000/query("int", me);
        if( query_temp("lu/yi3", me))cost/=2;
        cost += random(cost / 2);

        me->improve_skill("medicine", random(2 * me->query_int()));
        me->receive_damage("jing", cost, "心力絞瘁死了");
        message_vision("$N一會兒翻閱著『孫思邈千金方』，一會兒苦思冥想。\n",me);

        return 1;
}