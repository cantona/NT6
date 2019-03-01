// road4.c 小徑

inherit ROOM;

void create()
{
        object ob;

        set("short", "小徑");
        set("long", @LONG
這是一條蜿蜒的小徑，曲曲折折通往山裡。路面上光滑平實，看來是
經常有人來往。這裡已經是山腳了，山坡上有一些梯田，附近間或有一些
茅屋。只有東邊不遠的地方有一見小磚房，煙筒裡面時不時冒出一股股黑
煙，不象是炊火。
LONG );

        set("exits", ([
                "southwest" : __DIR__"road3",
                "east"      : __DIR__"road5",
        ]));
        set("outdoors", "suzhou");
        set("coor/x", 890);
        set("coor/y", -1060);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}
