inherit ROOM;

void create()
{
        set("short", "北樹林");
        set("long", @LONG
這裏生長的盡是幾人合抱的大樹，幾乎都看不倒路了，光線更加
昏暗。各種動物在林間跳來跳去，使這裏充滿了勃勃生機。
LONG);
        set("exits", ([
                "south" : __DIR__"shulin",
        ]));

        set("xinshoucun", 1);
        set("outdoors", "newbie");

        set("objects", ([
                "/clone/quarry/tu" : 40 + random(20),
        ]));
        setup();

        replace_program(ROOM);
}