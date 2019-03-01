// road1.c 小徑

inherit ROOM;

void create()
{
        object ob;

        set("short", "小徑");
        set("long", @LONG
這是一條蜿蜒的小徑，曲曲折折通往山裡。路面上光滑平實，看來是
經常有人來往。東面隱隱約約可以看到青石舖就的官道。
LONG );

        set("exits", ([
                "west"   : "/d/suzhou/qsgdao1",
                "eastup" : __DIR__"road2",
        ]));

        set("objects", ([
                "/adm/npc/zhang" : 1,
        ]));

        set("outdoors", "suzhou");
        set("coor/x", 860);
        set("coor/y", -1070);
        set("coor/z", 0);
        set("coor/x", 860);
        set("coor/y", -1070);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}