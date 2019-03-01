//
inherit ITEM;
void init()
{
        add_action("do_eat", "eat");
}

void create()
{
        set_name("蛇膽膏", ({"shedan gao", "gao"}));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "塊");
                set("long", "這是珍貴補品『蛇膽膏』。\n");
                set("value", 1000);
        }
        setup();
}

int do_eat(string arg)
{
        object me = this_player();
        if (!id(arg))
                return notify_fail("你要吃什麼？\n");
        if( (query("max_jing", me) >= 200) || (query("max_qi", me) >= 200) )
                return notify_fail("你吃『蛇膽膏』已無效用！\n");
        if( query("max_jing", me)<180 )
           {
            addn("max_jing", 10, me);
            addn("jing", 10, me);
            addn("max_qi", 10, me);
            addn("qi", 10, me);
           }
        else
           {
            addn("max_jing", 2, me);
            addn("jing", 2, me);
            addn("max_qi", 2, me);
            addn("qi", 2, me);
            }
        message_vision( "$N吃下一塊蛇膽膏，頓覺一股浩盪真氣直湧上來，
精，氣大增...\n" , me);
        destruct(this_object());
        return 1;
}
