inherit ROOM;

void create()
{
        set("short", "試劍亭");
        set("long", @LONG
這裏是一個用白玉石砌成的亭子，亭子砌得小巧玲瓏，十
分精巧。亭子的北面是一片桃花林，南面則是桃花山莊的正門。
LONG);
        set("exits", ([
                "south" : __DIR__"damen",
                "north" : __DIR__"tao_out",
        ]));
        set("outdoors", "taohua");
        setup();
        replace_program(ROOM);
}