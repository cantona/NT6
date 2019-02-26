// Room: /wuliang/jianhugong.c
// Date: Oct.18 1999 by Winder

inherit ROOM;

void create()
{
        set("short", "劍湖宮");
        set("long", @LONG
劍湖宮高居劍湖之側，隔着劍湖，遙遙對着無量玉壁。這裏是無
量劍掌門人日常起居之所。
LONG );
        set("exits", ([
                "southdown"  : __DIR__"road4",
        ]));
        set("objects", ([
                __DIR__"npc/tang" : 1,
        ]));
        set("coor/x", -71000);
        set("coor/y", -79870);
        set("coor/z", 110);
        setup();
        replace_program(ROOM);
}