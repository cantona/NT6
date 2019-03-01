// Room: /d/changcheng/badaling.c
// Last Modified by Winder on Aug. 25 2000

#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "八達嶺");
        set("long", WHT@LONG
八達嶺為居庸關外口，關城建于兩山之間。關城有二門，東門額題
“居庸外鎮”，西門額題“北門鎖鑰”。登上關樓，向西眺望，只見崇
山峻嶺，層巒疊嶂，群山之中只有八達嶺城關這個缺口，大有“一夫當
關，萬夫莫開”的氣勢。
LONG
NOR  );
        set("outdoors", "changcheng");
        set("exits", ([
                "west"      :__DIR__"juyongguan",
                "northeast" :__DIR__"beisilou",
        ]));
        set("objects", ([
                "/d/city/npc/wujiang" : 1,
        ]));
        set("coor/x", 1000);
        set("coor/y", 5000);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}