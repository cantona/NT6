// Room: /d/xingxiu/xxhb4.c
// Last Modified by Winder on Apr. 25 2001

inherit ROOM;
void create()
{
        set("short", "海邊荒路");
        set("long", @LONG
一條崎嶇的小路，東面是方圓幾百裡，一望無際的星宿海，靠西是
一片山石。這裡荒無人煙，寒風凜冽。枯樹敗草間，不時有毒蟲出沒。
你感到有點乏力，歇了一口氣再往前走。
LONG);
        set("exits", ([
                "east"   : __DIR__"xxhb2",
                "westup" : __DIR__"shanshi",
        ]));
        set("objects", ([
                __DIR__"npc/boshou"  : 1,
                __DIR__"npc/xxdizi" : 1,
        ]));
        set("outdoors", "xingxiu");
        set("coor/x", -50200);
        set("coor/y", 20400);
        set("coor/z", 100);
        setup();
        replace_program(ROOM);
}
