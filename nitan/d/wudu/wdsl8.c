inherit ROOM;

void create()
{
        set("short", "五毒山路");
        set("long", @LONG
這裏是五毒山中的山間小路，蜿蜒曲折盤旋而上。山路上寂靜無
聲，看不到一絲鳥獸的痕跡。你順手撥開伸向路中的枝條，樹枝忽然
一動，縮了回去，竟然是一條形似枯枝的毒蛇。 
LONG);
        set("outdoors", "wudujiao");

        set("exits", ([
                "westdown" : __DIR__"wdsl5",
                "south" : __DIR__"sl1",
        ]));

        setup();
        replace_program(ROOM);
}