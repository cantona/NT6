inherit ROOM;

void create()
{
        set("short", "黃土大道");
        set("long", @LONG
這是一條向南的黃土大道，遠處隱約看見一片翠綠的山巒。路上
行人逐漸稀少起來，大路越走越窄，有些地方竟長出了一片片的雜草。
東邊似乎有一條岔路。
LONG);
        set("outdoors", "wudujiao");

        set("exits", ([
                "southeast" : __DIR__"xiaolu",
                "south" : __DIR__"shanlu1",
                "north" : __DIR__"road2",
        ]));

        setup();
        replace_program(ROOM);
}