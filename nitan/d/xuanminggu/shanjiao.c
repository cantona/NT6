inherit ROOM;

void create()
{
        set("short", "玄冥峰山腳");
        set("long", @LONG
這是玄冥峰山腳，再往前走就是玄冥谷了。四周樹木蔥綠，綠草深
長。山雞野兔肆意奔跑。
LONG );
        set("exits", ([
                "eastdown"  : __DIR__"xiaolu1",
                "northwest" : __DIR__"shanlu1",
        ]));

        set("outdoors", "xuanming");
        setup();
        replace_program(ROOM);
}
