//Room: /d/huashan/shop.c

inherit ROOM;

void create()
{
        set("short", "山頂小店");
        set("long", @LONG
這裡是華山山頂的一間小店，賣些簡單的飲食，專門賺那些遊客
的錢。
LONG );
        set("exits", ([
                "east" : __DIR__"square",
        ]));
//        set("no_clean_up", 0);
        set("objects", ([
                "/d/huashan/npc/xiaoer" : 1,
        ]));

        setup();
        replace_program(ROOM);
}
