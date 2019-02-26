inherit ROOM;

void create()
{
        set("short", "黃土大道");
        set("long", @LONG
這是一條向南的黃土大道，兩旁是一片片綠油油的水田和悠閒的
牧童。大道上人流熙熙攘攘，過往的行人頂着炎炎烈日滿頭大汗的匆
匆趕路，似乎並無心欣賞這優美的田園風光。
LONG);
        set("outdoors", "wudujiao");

        set("exits", ([
                "south" : __DIR__"road2",
                "north" : "/d/dali/luyuxi",
        ]));

        setup();
        replace_program(ROOM);
}