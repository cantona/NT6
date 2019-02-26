inherit ROOM;

void create()
{
        set("short", "側洞");
        set("long", @LONG
這裏是一個小小的側洞，裏面有張梳粧枱，上邊凌亂的擺放着些
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