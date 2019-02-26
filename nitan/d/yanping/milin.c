// Room: /d/yanping/milin.c
// Date: Sep 28, 2002  Winder

inherit ROOM;

void create()
{
        set("short", "密林");
        set("long", @LONG
你走在一條僻靜的林中官道上，兩旁是陰森森的馬尾松林。只見左
右前後，到處都是鋪天蓋地的松樹，幾十丈高的大松樹簇在一塊，密實
的鬆蓬象一柄柄巨帚般伸向天空，把陽光遮得絲毫也無。
LONG );
        set("exits", ([
                "northwest" : __DIR__"guandao3",
                "southeast" : __DIR__"guandao2",
        ]));
        set("objects", ([
                __DIR__"npc/jianjingzei" : random(2)+1,
        ]));
        set("outdoors", "yanping");
        set("coor/x", 1600);
        set("coor/y", -6200);
        set("coor/z", 10);
        setup();
}

void init()
{
        if (userp(this_player()))
        switch (random(3))
        {
                case 1:
                        set("exits", ([
                                "northwest" : __DIR__"guandao3",
                                "southeast" : __FILE__,
                        ]));
                        break;
                case 2:
                        set("exits", ([
                                "northwest" : __FILE__,
                                "southeast" : __DIR__"guandao2",
                        ]));
                        break;
                default:
                        set("exits", ([
                                "northwest" : __FILE__,
                                "southeast" : __FILE__,
                        ]));
                        break;
        }
        return;
}