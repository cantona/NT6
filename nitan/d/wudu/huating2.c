#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "棲鳳亭");
        set("long", @LONG
這裏是一個花園中的小亭子，雕樑畫棟，古色古香。亭子
當中立着座青銅香爐(lu)，爐中正冒着許許清煙，也不知是燃
着什麼東西，煙味頗為刺鼻。
LONG);
        set("exits", ([
                "west" : __DIR__"huayuan2",
                "north" : __DIR__"huating1",
        ]));

        set("item_desc", ([
                "lu" : YEL "\n這是一座青銅香爐，模樣頗為古舊，香爐周"
                       "圍似乎有移動過的痕跡。\n" NOR,
        ]));

        setup();
}

void init()
{
        add_action("do_move", "move");
}

int do_move(string arg)
{
        object me = this_player();

        if (! arg || arg != "lu")
                return notify_fail("你要移動什麼？\n");

        if (query("exits/down"))
                return notify_fail("香爐已經被移開了。\n");

        message_vision(HIY "\n$N" HIY "剛一推動香爐，香爐卻自己"
                       "向一方移開，地面豁然現出一個洞口。\n\n"
                       NOR, me);
        set("exits/down", __DIR__"midao");
        remove_call_out("close");
        call_out("close", 8, this_object());

        return 1;
}

void close(object room)
{
        message("vision", WHT "忽然只聽「喀喀喀」幾聲，香爐縮回"
                          "原地，把密道擋住了。\n" NOR, room);
        delete("exits/down", room);
}