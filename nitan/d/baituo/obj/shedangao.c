// shedangao.c

inherit ITEM;

void create()
{
        set_name("蛇膽膏", ({"shedan gao", "gao"}));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "塊");
                set("long", "這是珍貴補品『蛇膽膏』。\n");
                set("value", 100);
                set("only_do_effect", 1);
        }
        setup();
}

int do_effect(object me)
{
        if( query("eff_jing", me) >= query("max_jing", me) )
                return notify_fail("你現在吃『蛇膽膏』並無效用！\n");

        me->receive_curing("jing", 30);
        message_vision("$N吃下一塊蛇膽膏，頓覺一股浩蕩真氣直湧上來，"
                       "精神立刻好轉！\n", me);
        destruct(this_object());
        return 1;
}