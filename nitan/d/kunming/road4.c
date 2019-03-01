inherit ROOM;

void create()
{
        set("short", "亂石灘");
        set("long", @LONG
這裡怪石林立，路極不好走，不小心就要摔個跟鬥，過了
這片石灘，就是長江岸邊。
LONG);
        set("outdoors", "kunming");
        set("exits", ([
                "south" : __DIR__"road5", 
                "northeast" : __DIR__"road3",
        ]));

        set("objects", ([
                "/d/beijing/npc/old2" : 1,
        ]));
        setup();
        replace_program(ROOM);
}