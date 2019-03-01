inherit ROOM;

void create()
{
        set("short", "九老洞");
        set("long", @LONG
這就是峨嵋第一大洞，洞內深窈無比，神秘難測。你一走進來，
便發覺洞中叉洞多如迷宮，怪異莫測似乎黝黑無底。還是快快離開吧。
LONG );
        set("objects", ([
                "/clone/quarry/fu" : 4,
        ]));
        set("exits", ([
                "out"   : __DIR__"jldongkou",
                "north" : __DIR__"jldongnei",
        ]));
        set("coor/x", -520);
        set("coor/y", -250);
        set("coor/z", 130);
        set("coor/x", -520);
        set("coor/y", -250);
        set("coor/z", 130);
        setup();
        replace_program(ROOM);
}