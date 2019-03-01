// Room: /xiakedao/shidong5.c

inherit ROOM;

void create()
{
        set("short", "石洞");
        set("long", @LONG
這是一個石洞，四周點着八盞油燈，使得整個房間非常明亮。
山洞中支路甚多，你可要小心，別走錯了路。
LONG );
        set("exits", ([
                "east" : __FILE__,
                "west" : __FILE__,
                "south" : __DIR__"dating",
                "north" : __DIR__"yingbin",
        ]));
        set("no_clean_up", 0);
        set("coor/x", -3080);
        set("coor/y", -22100);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}