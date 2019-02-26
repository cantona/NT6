// /d/gaoli/xuanwudajie3.c
// Room in 高麗
// rich 99/03/28
inherit ROOM;
void create()        
{
        set("short", "玉龍大街");
        set("long", @LONG
你走在一條寬闊的石板大街上，南面就快到高麗皇宮了，北面通向
玄武門，大街的東面傳來叮叮噹噹的打鐵聲，原來是一家鐵匠鋪，西面
是一家錢莊，在大街上就能聽見，數錢的聲音。
LONG
        );
set("outdoors", "gaoli");
set("exits", ([
                "north":__DIR__"xuanwu-2", 
                "south":__DIR__"yudao8", 
                "west":__DIR__"qianzhuang",
                 "east":__DIR__"tiejiangpu", 
        ]));
set("objects",([
 __DIR__"npc/gaoli-yongshi":1,
 ]));
       setup();
        replace_program(ROOM);
}        
