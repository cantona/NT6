inherit ROOM;

void create()
{
        set("short", "山間平地");
        set("long", @LONG
山間平地，地上是嫩綠的小草，周圍布了幾棵樺樹，山邊有一眼
清泉。草地上樹着幾個星宿老怪當年從少林寺偷來的木人，用來供星
宿弟子練功所用。東西邊緊鄰着另一個練功場。
LONG );
        set("resource/water", 1);
        set("objects", ([
                __DIR__"obj/yangrou" : 3,
        ]));
        set("exits", ([
                "east" : __DIR__"xxroad6",
                "west" : __DIR__"wuchang3",
        ]));
        set("outdoors", "xingxiu");
        set("for_family", "星宿派");
        setup();
        replace_program(ROOM);
}