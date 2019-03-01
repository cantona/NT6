inherit ROOM;

void create()
{
        set("short", "青石路");
        set("long", @LONG
由于離中州漸遠，路上見不到多少行人，你心裡不由也緊
張起來。北面可以通向中州府，西邊不遠便是軍事重地襄陽城。
LONG);
        set("exits", ([
                "southwest" : "/d/xiangyang/eastgate2",
                  "north" : __DIR__"nroad",
        ]));

        set("outdoors", "zhongzhou");
        set("no_clean_up", 0);
        set("coor/x", -150);
        set("coor/y", -130);
        set("coor/z", 10);
        setup();
        replace_program(ROOM);
}