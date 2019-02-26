inherit ROOM;

void create()
{
        set("short", "土路");
        set("long", @LONG
你走在湘鄂交界的土路上，偶爾會有人騎着馬匆匆而過。這裏已
經是湖南地界，往北進入湖北境內。
LONG );
        set("outdoors", "tiezhang");

        set("exits", ([
            "east" : "d/xiangyang/caodi6",
            "southwest" : __DIR__"hunanroad2",
        ]));

        set("coor/x", -3590);
        set("coor/y", -160);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}