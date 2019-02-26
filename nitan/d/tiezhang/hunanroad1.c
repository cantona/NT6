inherit ROOM;

void create()
{
        set("short", "土路");
        set("long", @LONG
你走在湘鄂交界的土路上，偶爾會有人騎着馬匆匆而過。這裏已經是湖
南地界，往北進入湖北境內。
LONG
        );
        set("outdoors", "tiezhang");

        set("exits", ([
            "east" : "d/xiangyang/caodi6",
            "southwest" : __DIR__"hunanroad2",
        ]));

        setup();
        replace_program(ROOM);
}