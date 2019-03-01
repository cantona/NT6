// Room: /d/yueyang/shijie1.c
// Last Modifyed by Winder on Dec. 4 2001

inherit ROOM;

void create()
{
        set("short", "石階");
        set("long", @LONG
這是龍口東側的青石階，連接龍口和山上的朗吟亭。石階兩邊茶樹
連綿，竹響隨人，真是個清幽所在。望山下，洞庭湖水簇擁君山，青碧
一片，十分怡人。
LONG );
        set("outdoors", "dongting");
        set("no_clean_up", 0);
        set("exits", ([
                "eastup"   : __DIR__"langyinting",
                "westdown" : __DIR__"longkou",
        ]));
        set("coor/x", -1710);
        set("coor/y", 2290);
        set("coor/z", -10);
        setup();
        replace_program(ROOM);
}