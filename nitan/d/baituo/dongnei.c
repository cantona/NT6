inherit ROOM;

void create()
{
        set("short", "洞內");
        set("long", @LONG
這裡是山賊的老窩的所在。旁邊有一側洞，裡面隱隱傳來女子的
哭聲。一個粗壯的山賊守衛在這裡。
LONG );
        set("exits", ([
                "west"  : __DIR__"cedong",
                "south" : __DIR__"dongkou",
        ]));

        set("objects", ([
                __DIR__"npc/shanzei3" : 1,
        ]));

        set("coor/x", -49950);
        set("coor/y", 20050);
        set("coor/z", 20);
        setup();
        // replace_program(ROOM);
}
int valid_leave(object me, string dir)
{
        object npc;
        
        if ( (dir == "west")
             && objectp(npc = present("shanzei tou", environment(me)))
             && living(npc) )
                return notify_fail("山賊頭操起拳頭：你想佔我老婆的便宜？快滾！\n");
        return ::valid_leave(me, dir);
}