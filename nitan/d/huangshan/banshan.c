// Room: /d/huangshan/banshan.c
// Last Modified by winder on Sep. 27 2001

inherit ROOM;
void create()
{
        set("short", "半山寺");
        set("long", @LONG
黃山險峻，過去少有人煙，最早來此者多為出家苦修的僧人，所以
黃山之上寺廟甚多。半山寺就因為出了一位擅長山水的大畫家“雪莊和
尚”而名聲居眾寺之首。至今寺內尚有其真跡留傳。由半山寺西行下山
便是醉石，繼續攀爬可去天都峯。
LONG
        );
        set("exits", ([ 
                "northup"   : __DIR__"guanyin",
                "westdown"  : __DIR__"zuishi",
                "southdown" : __DIR__"qingluan",
        ]));
        set("outdoors", "huangshan");
        replace_program(ROOM);
        set("coor/x", -595);
        set("coor/y", -1070);
        set("coor/z", -10);
        setup();
        replace_program(ROOM);
}