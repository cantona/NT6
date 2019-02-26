inherit ROOM;

void create()
{
        set("short", "小路");
        set("long", @LONG
你走到這條小路上，前面已經可以隱隱約約看到一座小小的院落
的影子，你可以非常的肯定，琴聲就是從這個小院裏發出來的，想到
立刻就可以見到大莊主黃鐘公了，你不禁一陣緊張。 
LONG );
        set("exits", ([
            "north" : __DIR__"yuedong",
            "westdown" : __DIR__"qhpo",
        ]));

        set("outdoors", "meizhuang");
        set("no_clean_up", 0);

        setup();
        replace_program(ROOM);
}