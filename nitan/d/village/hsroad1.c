inherit ROOM;

void create()
{
        set("short", "青石大道");
        set("long", @LONG
你走在一條青石大道上，人來人往非常繁忙，不時地有人騎着馬
匆匆而過。大道兩旁有一些小貨攤，似乎是一處集市。南邊通向洛陽
古城。
LONG );
        set("outdoors", "village");
        set("exits", ([
                "north" : __DIR__"hsroad2",
                "south" : "/d/changan/road2",
        ]));
        set("objects", ([
                __DIR__"npc/girl" : 4,
        ]));

        setup();
        replace_program(ROOM);
}