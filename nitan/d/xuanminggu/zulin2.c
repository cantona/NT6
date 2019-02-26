inherit ROOM;

void create()
{
        set("short", "翠竹林");
        set("long", @LONG
這是玄冥峯山腰的一片翠竹林，四處青翠掩映，鳥語花香。
此處比之竹林入口處景色更佳，竹子的幽香氣息撲鼻而來。實在
是練武靜思之寶地。
LONG );
        set("exits", ([
                "eastdown"  : __DIR__"zulin1",
        ]));

        set("objects", ([
                 "/kungfu/class/xuanming/he" : 1,
        ]));

        set("outdoors", "xuanming");
        setup();
        replace_program(ROOM);
}
