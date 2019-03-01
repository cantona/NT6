// caodi.c 草地
// Java Oct.10 1998

inherit ROOM;

void create()
{
        set("short", "草地");
        set("long", @LONG
這裡是一片草地，草很深，幾乎淹沒了小腿。草間散布著一些奇花，
微風吹過，芬芳撲鼻。你聽到時而有“嗡嗡嗡”的聲音，看見有一些個
頭奇大的白色的蜜蜂在草地上飛舞盤旋。
LONG        );
        set("outdoors", "gumu");
        set("exits", ([
                "south" : __DIR__"mumen",
                "east"  : __DIR__"caodi2",
                "north" : __DIR__"shulin3",
        ]));
        set("objects", ([
                __DIR__"npc/yufeng" : random(5),
        ]));
        set("coor/x", -3220);
        set("coor/y", 40);
        set("coor/z", 90);
        setup();
        replace_program(ROOM);
}