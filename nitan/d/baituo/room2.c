//room2.c

inherit ROOM;
void create()
{
        set("short","練功室");
        set("long", @LONG
這裡是白駝山弟子的練功室。有幾個制作精致的木人陪你練功。
LONG );
        set("exits",([
                "out" : __DIR__"fang",
        ]));

        set("objects",([
                "/clone/npc/mu-ren" : 4,
        ]));

        set("coor/x", -49970);
        set("coor/y", 20040);
        set("coor/z", 30);
        setup();
}