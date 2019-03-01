// /d/gaoli/maji
// Room in 高麗
// rich 99/03/28
inherit ROOM;
void create()        
{
        set("short", "馬房");
        set("long", @LONG
高麗馬雖然不如突厥馬那麼高大，但卻善走長途，這個馬房，各式
各樣的馬應有盡有，突厥馬，高麗馬，甚至連嶺南馬都有。
LONG
        );
set("outdoors", "gaoli");
set("exits", ([
               "south":__DIR__"qinglong-1", 
        ]));
set("objects", ([
                "/d/gaoli/npc/ma" : 1,
        ]));
       setup();
        replace_program(ROOM);
}        
