inherit ROOM;

void create()
{
        set("short", "南樹林");
        set("long", @LONG
這裡長滿了高大的樹木，盡是碗口般粗大的樹木，
在樹木的掩映下，光線也昏暗下來。各種小動物在林
間跳來跳去，使這裡充滿了勃勃生機。
LONG);
        set("exits", ([
                "west" : __DIR__"zhulin",
                "north" : __DIR__"beishulin",
        ]));

        set("xinshoucun", 1);
            set("outdoors", "newbie");

           set("objects", ([
                "/clone/quarry/tu" : 40 + random(30),
           ]));
        setup();

        replace_program(ROOM);
}