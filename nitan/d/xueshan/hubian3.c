inherit ROOM;

void create()
{
        set("short", "湖邊小路");
        set("long", @LONG
這是聖湖邊的小路。天蘭蘭的，白白雲朵在湖裡漂移，波光瀲灩。
湖邊生長著一些綠綠青青的不知名的矮樹。
LONG );
        set("outdoors", "xuedao");
        set("exits", ([
                "north" : __DIR__"hubian4",
                "west"  : __DIR__"hubian2",
        ]));
        setup();
        replace_program(ROOM);
}