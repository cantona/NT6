// /d/gaoli/zhuquedajie2
// Room in 高麗
// rich 99/03/28
inherit ROOM;
void create()        
{
        set("short", "飛鳳大街");
        set("long", @LONG
你走在一條寬闊的石板大街上，東面就快到高麗皇宮了。都可以看
見皇宮的圍牆，西面是高麗的西門飛鳳門，北面是高麗的驛站，南面是
高麗官方開的鹽局。
LONG
        );
set("outdoors", "gaoli");
set("exits", ([
                "west" : __DIR__"qinglongmen",
                "east" : __DIR__"qinglong-1",
                "north":__DIR__"yizhan",
                "south":__DIR__"yanju",    
        ]));
       setup();
        replace_program(ROOM);
}        
