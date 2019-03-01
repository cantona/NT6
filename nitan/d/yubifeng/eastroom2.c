// /yubifeng/eastroom2.c
// Last modified by winder 2003.9.2

inherit ROOM;

void create()
{
        set("short", "東廂房");
        set("long", @long
東廂房原是杜莊主款待賓客的所在，床帳、屏風、幾桌、一應起居
之具齊備，陳設得甚是考究。        
long );
        set("exits", ([
                "west" : __DIR__"zoulang6",
        ]));
        set("objects", ([
                __DIR__"npc/miaoruolan" : 1,
                __DIR__"npc/qiner" : 1,
        ]));
        set("coor/x", 6140);
        set("coor/y", 5200);
        set("coor/z", 100);
        setup();
        replace_program(ROOM);
}