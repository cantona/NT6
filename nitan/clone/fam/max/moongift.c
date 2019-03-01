
#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(HIY "中秋月餅四盒裝" NOR, ({ "moongift" }) );
        set_weight(1);

        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIY "二零零五年炎黃中秋特別禮品，請使用open moongift指令打開。\n"
                                                "同時，深切悼念在9.18事變中犧牲的烈士，勿忘國恥！\n"NOR);
                set("value", 1);
                set("no_sell", 1);
                        set("unit", "盒");
        }

        setup();
}

void init()
{
        if (this_player() == environment())
        {
                add_action("do_open", "open");
        }
}


int do_open(string arg)
{
                object me;
                object ob;

                me = this_player();


                if (! arg)return notify_fail("指令格式: open moongift\n");

                ob = new("/clone/fam/max/yuebinggift");
                ob->move(me, 1);
                ob = new("/clone/fam/max/yuebinggift");
                ob->move(me, 1);
                ob = new("/clone/fam/max/yuebinggift");
                ob->move(me, 1);
                ob = new("/clone/fam/max/yuebinggift");
                ob->move(me, 1);

                tell_object(me, HIG "你打開中秋月餅四盒裝。\n" NOR);
                
                destruct(this_object());
                
                return 1;
}

int query_autoload()
{
         return 1;
}
