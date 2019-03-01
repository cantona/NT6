inherit ROOM;

void create()
{
        set("short", "小路");
        set("long", @LONG
這是一條小路向東南延伸，四周盡是花香鳥語，空氣頓時
清新了許多。前面有一座小小的山岡。
LONG);
        set("outdoors", "wudujiao");
        set("exits", ([
                "northwest" : __DIR__"road3",
                "southup" : __DIR__"shanlu2",
        ]));
        set("objects", ([
                "/clone/quarry/tu" : 3,
        ]));

        setup();
        replace_program(ROOM);
}