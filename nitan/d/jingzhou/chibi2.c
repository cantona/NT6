inherit ROOM;

void create()
{
        set("short",  "小路" );
        set("long", @LONG
這是一條通向江邊的小路，路十分的陡，走起來得小心一點，四
周靜悄悄的，只聞的鳥兒歌唱的聲音。
LONG );
        set("outdoors", "jingzhou");

        set("exits", ([
                "northup" : __DIR__"chibi1",
                "southdown" : __DIR__"chibi3",
        ]));

        set("coor/x", -350);
        set("coor/y", -210);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
} 