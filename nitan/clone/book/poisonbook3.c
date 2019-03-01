// poisonbook3.c

inherit ITEM;

void create()
{
        set_name("毒經下篇", ({ "jing", "book" }));
        set_weight(50);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "本");
                set("long", "這是一本薄薄的小冊，上面密密麻麻的記滿了各種用毒的法門，可以用(kan)看一看。\n");
                set("no_drop", "這樣東西不能離開你。\n");
                set("value", 0);
                set("material", "silk");
        }
}
void init()
{
        add_action("do_read", "kan");
        add_action("do_read", "see");
        add_action("do_read", "du");

//        this_object()->set("created", 1);
        remove_call_out ("destroy_book");
        call_out ("destroy_book", 28800); // 8 hours

}

void destroy_book()
{
        message_vision("一陣風吹來，"+query("name", this_object())+"片片碎落，隨風而去了。\n",environment(this_object()));
        destruct(this_object());
}

int do_read(string arg)
{
        object me;
        int jing_cost, gain;
        me=this_player();
        if( !arg||!( arg == "jing"||arg =="book"))
                return notify_fail("什麼？\n");
        if (!present(this_object(), this_player()))
                return 0;

        if( me->is_busy() )
                return notify_fail("你現在忙著呢，哪有可能靜心研讀...\n");
        if( me->is_fighting() )
                return notify_fail("現在才想到精研毒技，太晚了吧？\n");
        if( query("family/family_name", me) != "五毒教"){
                remove_call_out ("destroy_book");
                call_out ("destroy_book", 0);
        }
        if( (int)me->query_skill("five-poison",1)<150
         || query("combat_exp", me)<300000 )
                return notify_fail("你看來看去，就是沒明白這本書上寫的都是啥。\n");
        if( (int)me->query_skill("five-poison",1)>300 )
                return notify_fail("你的毒技已經很有造詣，這本書不會讓你長進多少。\n");

        jing_cost=35+(20-query("int", me));
        if( query("jing", me)<jing_cost )
                return notify_fail("你現在頭暈腦脹，該休息休息了。\n");
        me->receive_damage("jing", jing_cost);

        gain = (int)me->query_skill("five-poison", 1)/4+(int)me->query_skill("literate",1)/2;
        me->improve_skill("five-poison", gain);

        message_vision("$N拿著絹冊仔細閱讀,只覺上面所載的種種用毒害人的\n方法都是聞所未聞，看著看著禁不住出了一身冷汗！\n", me);

        return 1;
}