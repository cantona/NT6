// Room: /d/yueyang/xiangchunting.c
// Last Modifyed by Winder on Dec. 4 2001

inherit ROOM;

void create()
{
        set("short", "香椿亭");
        set("long", @LONG
香爐山上，有雕龍石柱，六角鍔頂石亭。名曰香椿亭。前有青石大
香爐一個，亭爐相應，境與意會。山下是天然的避風港，宋代楊麼的英
雄豪傑在此結義，振虎帳之師，立鴉咀之戰船，建水軍之點將台，操練
戰船，風雪滾滾，輪櫓依依，萬古東南多壯觀，百年豪傑幾登臨。
LONG );
        set("outdoors", "dongting");
        set("no_clean_up", 0);
        set("exits", ([
                "north" : __DIR__"xianglushan",
        ]));
        set("objects", ([
                CLASS_D("gaibang")+"/fang" : 1,
        ]));
        set("coor/x", -1800);
        set("coor/y", 2250);
        set("coor/z", 10);
        setup();
        replace_program(ROOM);
}