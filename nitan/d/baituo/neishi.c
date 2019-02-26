#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "內室");
        set("long", @LONG
這是歐陽克的內室，內部擺設很有情趣。屋角擺着一盆名貴蘭花，
正驕傲地吐露芳蕊。花盆(pen)下撒落一些浮土，可能是被人搬出去曬
太陽時撒下的。
LONG );
        set("exits", ([
                "east" : __DIR__"huayuan",
        ]));
 
        set("item_desc", ([
                "pen" : WHT "\n這是一個大花盆，看上去非常堅固結"
                        "實，作工也很考究，仔細\n觀察下，不難發"
                        "現地上有些浮土，似乎有人移動(move)過花"
                        "盆。\n" NOR,
        ]));
        set("coor/x", -49990);
        set("coor/y", 20050);
        set("coor/z", 30);
        setup();
}

void init()
{
        add_action("do_move", "move");
}

int do_move(string arg)
{
        object me = this_player();

        if (arg != "pen")
                return notify_fail("你要搬什麼？\n");

        if( query("born_family", me) != "歐陽世家" )
                return notify_fail("你移動了一下花盆，卻沒發現什麼特別的東西。\n");

        if (! query("exits/down"))
        {
                set("exits/down", __DIR__"midao");
                message_vision(HIY "\n$N" HIY "移動花盆，只見花盆下面"
                               "露出一個黑幽幽的洞口。\n\n" NOR, me);
        } else
        {
                delete("exits/down");
                message_vision(HIY "\n$N" HIY "把花盆搬回原位，洞口頓"
                               "時被封住了。\n\n" NOR, me);
        }
        return 1;
}