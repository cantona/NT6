inherit ROOM;

void create()
{
        set("short", "翠竹林");
        set("long", @LONG
這是玄冥峰山腰的一片翠竹林，四處青翠掩映，鳥語花香。
LONG );
        set("exits", ([
                "eastdown"  : __DIR__"xiaolu3",
                "westup"    : __DIR__"zulin2",
                "northwest" : __DIR__"shanlu2",
        ]));

        set("objects", ([
                 "/kungfu/class/xuanming/wuwang" : 1,
        ]));

        set("outdoors", "xuanming");
        setup();
        replace_program(ROOM);
}
