inherit ROOM;

void create()
{
        set("short", "青石大道");
        set("long", @LONG
這是條青石鋪成的寬敞大道，每塊青石都是長約八尺，寬約三尺，
甚是整齊。道旁是鬱鬱葱葱的松樹林，不時可以看到幾隻松鼠蹦蹦跳
跳地躍向樹林深處。往北望去，一座巨大的石堡巍然聳立。
LONG );
        set("outdoors", "lingjiu");

        set("exits", ([
                "north" : __DIR__"damen",
                "south" : __DIR__"dadao1",
        ]));
        set("objects", ([
                "/clone/quarry/song" : 2,
        ]));

        set("no_clean_up", 0);
        setup();
        replace_program(ROOM);
}