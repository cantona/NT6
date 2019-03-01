// shulin1.c
// Modified by Winder June.25 2000

inherit ROOM;

void create()
{
        set("short", "樹林");
        set("long", @LONG
這是一片茂密的樹林。很多棵幾十丈高的大樹聚在一塊，象一把把
瓊天大傘，連日月都被遮蔽得暗然無光。樹林中還不時可以聽到大自然
發出的聲響。
LONG );
        set("exits", ([
                "north" : __DIR__"shulin1",
                "south" : __DIR__"shulin1",
                "east" : __DIR__"shulin2",
                "west" : __DIR__"xiaodao4",
        ]));
        set("outdoors", "xiaoyao");
        set("no_clean_up", 0);
        set("coor/x", 100);
        set("coor/y", -500);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}