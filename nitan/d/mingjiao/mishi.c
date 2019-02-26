// Room: /d/mingjiao/mishi.c
// Date: Java 97/04/9

inherit ROOM;

#include <room.h>

void create()
{
        set("short", "石室");
        set("long", @LONG
這間石室極大，頂上垂下鍾乳，顯是天然的石洞。走了幾步，突
見地下倒着兩具骷髏。骷髏身上衣服尚未爛盡，着得出是一男一女。
走近兩具骷髏，只見那女子右手抓着一柄晶光閃亮的匕首，插在她自
己胸口。
LONG );
        set("exits", ([
                "south" : __DIR__"midao0",
                "up"    : __DIR__"neishi",
        ]));
        set("objects", ([
                __DIR__"obj/yangdt" : 1,
                __DIR__"obj/yangfr" : 1,
        ]));
        set("no_clean_up", 0);
        set("xin_count", 1);
        setup();
        create_door("south", "石門", "north", !DOOR_CLOSED);
}

void init()
{
        add_action("do_ketou", "ketou");
}

int do_ketou()
{
        object me;

        me = this_player();
        message_vision("$N虔誠地跪下來，在陽教主遺骨前恭恭敬敬地磕了個頭。\n", me);
        if (query("xin_count") > 0 )
        {
                addn("xin_count", -1);
                new(__DIR__"obj/yixin")->move(this_object());
                new("/clone/book/qiankun_book")->move(this_object());
                tell_object(me, "突然你抬眼看到遺骨下面，有一些東西，你"
                            "看了看，原來是一封信和一張羊皮。\n");
        }
        return 1;
}
void reset()
{
        ::reset();
        set("xin_count",1);
}