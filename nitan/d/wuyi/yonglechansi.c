// Room: /d/wuyi/yonglechansi.c
// Last modified by Winder on Mar.20.2002

inherit ROOM;

void create()
{
        set("short", "永樂禪寺");
        set("long", @LONG
“自古田園風光好，天下名山僧佔多”。位於天心巖腹地的天心永
樂禪寺，從創建的那天起，就把禪心裹進武夷的山水中去了。周圍羣峯
料峭，古木參天。數百年過去了，每天的晨鐘暮鼓，敲打着同樣的聲調：
“天心原佛國碧水丹山開法界，永樂本禪居清風明月皈真如。”
LONG );
        set("outdoors", "wuyi");
        set("no_clean_up", 0);
        set("exits", ([
                "east"      : __DIR__"tianxinyan",
                "south"     : __DIR__"path5",
                "southwest" : __DIR__"path11",
                "northwest" : __DIR__"path14",
        ]));
        set("objects", ([
                "/d/hangzhou/npc/seng": random(2),
                "/d/hangzhou/npc/shami": random(3),
        ]));
        set("coor/x", 1400);
        set("coor/y", -4930);
        set("coor/z", 10);
        setup();
        replace_program(ROOM);
}
