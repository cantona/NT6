inherit ROOM;

void create()
{
        set("short", "小吃店");
        set("long", @LONG
這裏是石樑邊的一間小吃店，賣些簡單的飲食，專門賺那些遊客
的錢。
LONG );
        set("exits", ([
                "west" : __DIR__"shiliang",
        ]));

        set("objects", ([
                __DIR__"npc/xiaoer" : 1,
        ]));
        set("coor/x", -360);
        set("coor/y", -250);
        set("coor/z", 50);
        setup();
        replace_program(ROOM);
}