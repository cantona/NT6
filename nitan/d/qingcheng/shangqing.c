// Room: /qingcheng/shangqing.c
// Date: Frb.20 1998 by Java

inherit ROOM;
void create()
{
        set("short", "上清宮");
        set("long", @LONG
上清宮是老君道場。宮前山門，矮樹搭就，甚為靈動。宮內殿
堂古色清雅，正殿供奉太上老君、呂純陽和張三豐塑像。山前摩崖
石刻 "天下第五名山" 氣勢渾厚，很是壯觀。
LONG );
        set("outdoors","qingcheng");
        set("exits", ([
                "westdown" : __DIR__"sanwanjiudao",
                "westup"   : __DIR__"huyingting",
                "west"     : __DIR__"yuanyangjing",
                "east"     : __DIR__"maguchi",
                "northup"  : __DIR__"qiandian",
        ]));
        set("objects", ([
                __DIR__"npc/luo" : 1,
        ]));
        set("coor/x", -8080);
        set("coor/y", -880);
        set("coor/z", 80);
        setup();
        replace_program(ROOM);
}