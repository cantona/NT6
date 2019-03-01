inherit ROOM;

void create()
{
        set("short", "刑場");
        set("long", @LONG
這裡是京城的刑場，是朝廷處決欽犯的場所。你走到了這裡，發
現整個刑場很是空曠，刑場正中有一個高高的石台，石台上由幾根圓
木柱搭建成了一個框架，上面垂著一根很粗的麻繩。框架下面是一個
正方形的大木樁，上面還能夠看見隱隱血跡。
LONG );
       set("exits", ([
                "west" : "/d/beijing/wang_2",
        ]));
        set("objects", ([
                "/d/beijing/npc/guizishou" : 1,
               "/clone/npc/walker"  : 1, 
        ]));

	set("coor/x", -2760);
	set("coor/y", 7680);
	set("coor/z", 0);
	setup();
       set("outdoors", "beijing");
        replace_program(ROOM);
}