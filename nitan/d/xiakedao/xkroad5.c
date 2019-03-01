inherit ROOM;

void create()
{
        set("short", "漁村曬網場");
        set("long", @LONG
小村不大，卻有個好大的曬網場。幾個小孩在場中無憂地玩耍，
聲音喧鬧。靠南海邊上，有個漁夫面向大海，悠然垂釣。
LONG );
        set("outdoors", "nanhai");
        set("exits", ([
                "north"   : __DIR__"xkroad6",
                "west"    : __DIR__"xkroad4",
        ]));
        set("objects", ([
                __DIR__"npc/boy": 1,
                __DIR__"npc/girl": 1,
                __DIR__"npc/yufu": 1,
                CLASS_D("misc/haigui") : 1,
        ]));
        set("coor/x", -1390);
        set("coor/y", -9000);
        set("coor/z", 0);
        setup();
}

void init()
{
        MYGIFT_D->check_mygift(this_player(), "newbie_mygift/haigui");
}

