// /yubifeng/westroom2.c
// Last modified by winder 2003.9.2

inherit ROOM;

void create()
{
        set("short", "西廂房");
        set("long", @long
西廂房原是杜莊主的臥室的所在，床帳幾桌、一應起居之具齊備，
陳設得甚是考究。        
long );
        set("exits", ([
                "east" : __DIR__"zoulang5",
        ]));
        set("no_clean_up", 0);
        set("coor/x", 6100);
        set("coor/y", 5200);
        set("coor/z", 100);
        setup();
        replace_program(ROOM);
}