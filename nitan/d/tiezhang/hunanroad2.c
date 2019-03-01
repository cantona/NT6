// /d/xiangyang/hunanroad2.c

inherit ROOM;

void create()
{
        set("short", "土路");
        set("long", @LONG
你走在湘鄂交界的土路上，偶爾會有人騎著馬匆匆而過。這裡已經是湖
南地界，往北進入湖北境內。
LONG
        );
        set("outdoors", "tiezhang");

        set("exits", ([
                "northeast" : __DIR__"hunanroad1",
                "south" : "/d/tiezhang/lx",
        ]));

        setup();
        replace_program(ROOM);
}