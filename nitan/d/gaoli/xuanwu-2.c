// /d/gaoli/xuanwudajie1.c
// Room in 高麗
// rich 99/03/28
inherit ROOM;
void create()        
{
        set("short", "玉龍大街");
        set("long", @LONG
你走在一條寬闊的石板大街上，北面是高麗的北城門玄武門，在向
南走就快到高麗皇宮了，大街的東面是一家私塾，傳來陣陣讀書聲，西
面是一家藥舖。
LONG
        );
set("outdoors", "gaoli");
set("exits", ([
                "north":__DIR__"xuanwumen", 
                "south":__DIR__"xuanwu-1", 
                "west":__DIR__"yaopu",
                 "east":__DIR__"sishu", 
        ]));
       setup();
        replace_program(ROOM);
}        
