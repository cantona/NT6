// lbook6.c
#include <ansi.h>
inherit ITEM;
void create()
{
        set_name(YEL"「史記」"NOR, ({ "literateb6", "shu6", "book6" }));
        set_weight(200);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "卷");
                set("value", 1000);
                set("long", "一本很古舊的線裝書，蘭皮上寫著兩個篆字'史記'，裡面的內容很多都已經模糊不清。\n");
                set("material", "paper");
        }
}
void init()
{
        add_action("do_read","study");
        add_action("do_read","du");
}
int do_read(string arg)
{
        object me;
        me = this_player();
        if (!present(this_object(), this_player())) return 0;

        if( arg=="literateb6" || arg=="shu6" || arg=="book6")
        {
                write("這本書太破舊了，現在沒法讀。\n");
                return 1;
        }
}