// shedangao.c
inherit ITEM;
void init()
{
        add_action("do_eat", "eat");
        add_action("do_eat", "fu");
}

void create()
{
        set_name("蛇膽膏", ({"shedan gao", "gao"}));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "塊");
                set("long", "這是珍貴補品『蛇膽膏』。\n");
                set("value", 100);
        }
        set("pour_type", "1");
        setup();
}

int do_eat(string arg)
{
        object me = this_player();

        if(!id(arg)) return notify_fail("你要吃什麼？\n");
        if(!present(this_object(), me))
                return notify_fail("你要吃什麼？\n");
        if( me->is_busy() )
                return notify_fail("別急，慢慢吃，小心別噎著了。\n");

        if( (query("max_jing", me) >= 110) || (query("max_qi", me) >= 200) )
                return notify_fail("你吃『蛇膽膏』已無效用！\n");
        if( query("max_jing", me)<105 )
        {
                addn("max_jing", 2, me);
                addn("eff_jing", 2, me);
                addn("jing", 4, me);
                addn("max_qi", 5, me);
                addn("eff_qi", 5, me);
                addn("qi", 10, me);
        }
        else
        {
                addn("max_jing", 1, me);
                addn("eff_jing", 1, me);
                addn("jing", 2, me);
                addn("max_qi", 3, me);
                addn("eff_qi", 3, me);
                addn("qi", 5, me);
        }
        message_vision("$N吃下一塊蛇膽膏，頓覺一股浩盪真氣直湧上來，精，氣大增...\n" , me);
        destruct(this_object());
        return 1;
}