// item: redobj.c

inherit ITEM;
#include <ansi.h>;
void create()
{
        set_name(HIR"紅布小囊"NOR, ({"hongbu xiaonan", "xiaonan"}));
        set_weight(80);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", "這是一隻紅布小囊，不知道有什麼用處。\n");
                set("unit", "只");
                set("value", 1);
        }
}

void init()
{
        add_action("do_chaikai", "chaikai");
}
int do_chaikai(string arg)
{
        object bu, me = this_player();
        string message;
        int col;

        if(!id(arg)) return notify_fail("你要拆什麼？\n");
        if(!present(this_object(), me))
                return notify_fail("你要拆什麼？\n");
        message_vision("$N拆開紅布小囊，攤開發現是張紅布！\n", me);
        bu = new(__DIR__"redcloth");
        bu->move(me);
        destruct(this_object());
        return 1;
}
