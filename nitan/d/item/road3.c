// road3.c 小徑

inherit ROOM;

void create()
{
        object ob;

        set("short", "小徑");
        set("long", @LONG
這是一條蜿蜒的小徑，曲曲折折通往山裡。路面上光滑平實，看來是
經常有人來往。四周非常安靜，道旁都是田園村戶。有時可以聽見幾聲清
脆動人的鳥叫。
LONG );

        set("exits", ([
                "westup"    : __DIR__"road2",
                "northeast" : __DIR__"road4",
        ]));
        set("outdoors", "suzhou");
        set("coor/x", 880);
        set("coor/y", -1070);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}