// /yubifeng/westroom1.c
// Last modified by winder 2003.9.2

inherit ROOM;

void create()
{
        set("short", "書房");
        set("long", @long
這裏是莊主的書房推開房門，見裏面四壁圖書，陳設得甚是精雅。
long );
        set("exits", ([
                "east" : __DIR__"zoulang3",
        ]));
        set("no_clean_up", 0);
        set("coor/x", 6100);
        set("coor/y", 5190);
        set("coor/z", 100);
        setup();
        replace_program(ROOM);
}