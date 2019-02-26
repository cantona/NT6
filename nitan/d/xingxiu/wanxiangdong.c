// Room: /d/xingxiu/wanxiangdong.c
// Last Modified by winder on Apr. 25 2001
inherit ROOM;

void create()
{
        set("short", "萬象洞");
        set("long", @LONG
這是一個深邃的洞穴，洞內鐘乳石絢麗多姿，美妙神奇。有犀牛望
月、五嶽朝天、卧龍坪、煉丹井、仙人灶、上天梯、獨木橋等，景象萬
千，耐人尋味。
LONG);
        set("outdoors", "silu");
        set("exits", ([
                "east" : __DIR__"shashan",
        ]));
        set("no_clean_up", 0);
        set("coor/x", -20330);
        set("coor/y", 200);
        set("coor/z", 0);
        setup();
//        replace_program(ROOM);
}

#include "/d/xingxiu/job2.h";
