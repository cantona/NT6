// Yanwu.c 煙霧彈
#include <command.h>
#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(HIM"煙霧彈"NOR, ({ "yanwu"}) );
        set_weight(100);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("long", "一顆星宿派特製的煙霧彈。它可以用(apply)。\n");
                set("unit", "個");
                set("value", 10000);
                set("no_drop", RED"難道你想製造混亂嗎？\n"NOR);
        }
}

void init()
{
        add_action("do_apply","apply");
}
int do_apply(string arg)
{
        object me,ob;
        object *inv;
        int i;

        if (arg!="yanwu")
        {
                return 0;
        }

        me=this_player();
        if (me->is_busy())
        {
                notify_fail("你正在忙啊。\n");
                return 1;
        }

        inv = all_inventory(environment(me));
        for(i=0; i<sizeof(inv); i++)
        {
                ob=inv[i];
                if (ob==me)
                continue;
                if( (ob->is_character()) && (!ob->is_corpse()) )
                {
                        ob->start_busy(2);
                }
        }
        set_temp("no_follow", 1, me);
//      GO_CMD->do_flee(me);
        tell_room(environment(me),HIM"地面突然騰出一股桃紅色的煙霧，大傢什麼也看
不見，陷入混亂之中。\n"NOR);

        GO_CMD->do_flee(me);
        destruct(this_object());
        return 1;
}
void owner_is_killed()
{
        object me = this_player();
        write(HIM"只見一陣桃紅色的煙霧閃過...屍體上什麼東西消失了。\n"NOR);
        destruct(this_object());
}
int query_autoload()
{
        return 1;
}