inherit ROOM;

void create()
{
        set("short", "草棚");
        set("long", @LONG
這是峨嵋山腳下一個簡單的草棚，地上堆著些上貨。很多上山的
遊客都在這裡買些上山用品。草棚後有個口井，西面是間簡陋的馬廄。
LONG );
        set("outdoors", "emei");
        set("objects", ([
                __DIR__"npc/xiao-fan": 1,
        ]));
        set("exits", ([
                "west" : __DIR__"majiu1",
                "east" : __DIR__"qsjie2",
        ]));
        set("coor/x", -380);
        set("coor/y", -200);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}