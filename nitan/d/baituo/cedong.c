inherit ROOM;

void create()
{
        set("short", "側洞");
        set("long", @LONG
這裡是一個小小的側洞，裡面有張梳妝台，上邊凌亂的擺放著些
女人的用品。
LONG );
        set("exits", ([
                "east" : __DIR__"dongnei",
        ]));
        set("objects", ([
                __DIR__"npc/jinhua" : 1,
        ]));
        set("coor/x", -49960);
        set("coor/y", 20050);
        set("coor/z", 20);
        setup();
        replace_program(ROOM);
}