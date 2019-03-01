#include <ansi.h>
inherit ITEM;

#define ZHUJIAN    "/clone/lonely/book/zhujian3"

void create()
{
        set_name("枯乾的骸骨", ({ "Skeleton", "skeleton", "骸骨" }));
        set_weight(500);
        if (clonep())
                set_default_object(__FILE__);
            else {
                set("unit", "具");
                set("long", "這副骸骨已經躺在這裡很久了。\n");
                set("value", 1);
                set("no_get", "這東西一碰就散，還是別揀吧！\n");
            }
}

void init()
{
        add_action("do_move", "move");
}

int do_move(string arg)
{
        object me, ob;
        me = this_player();

        if (! arg || ! id(arg))
                return 0;

        ob = find_object(ZHUJIAN);
        if (! ob) ob = load_object(ZHUJIAN);

        if (! environment(ob))
        {
                ob->move(environment(me));
                message_vision(HIC "\n$N" HIC "小心翼翼地將骸骨移開，發現下"
                               "面豁然藏有一卷竹簡。\n" NOR, me);
                return 1;
        } else
                message_vision(HIY "$N" HIY "小心翼翼地將骸骨移開，可是什麼"
                               "也沒發現。\n" NOR, me);
        return 1;
}