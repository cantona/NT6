// yijing.c  『十四經發揮』
// Last Modified by winder on Jul. 12 2002

inherit ITEM;
void setup()
{}

void create()
{
        set_name("十四經發揮", ({ "yijing", "book" }));
        set_weight(600);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "本");
                set("long", "這是一本線裝書，裡面有各式圖譜和詳細說明。\n");
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
        if( (int)me->query_skill("medicine", 1) < 30 )
        {
                write("你還是先去讀一讀『黃帝內經』吧。\n");
                return 1;
        }
        if( (int)me->query_skill("medicine", 1) > 59 )
        {
                write("閣下已熟知人體經脈和各處穴位，不必再讀『十四經發揮』。\n");
                return 1;
        }
        if( query("jing", me)<120 )
        {
                write("你的精神欠佳，捧著醫經連打呵欠。\n");
                return 1;
        }
        cost=40+800/query("int", me);
        if( query_temp("lu/yi2", me))cost/=2;
        cost += random(cost / 2);

        me->improve_skill("medicine", random(2 * me->query_int()));
        me->receive_damage("jing", cost, "心力絞瘁死了");
        message_vision("$N一會兒翻閱著『十四經發揮』，一會兒苦思冥想。\n", me);

        return 1;
}