inherit ROOM;

void create()
{
        set("short", "獨尊廳");
        set("long", @LONG
這就是「靈鷲宮」獨尊廳。大廳全是以巨石砌成，石塊之間竟無
半點縫隙，令人稱奇。廳內矗立着四根石柱，皆為堅硬的花崗石所制。
LONG );
        set("exits", ([
                "north" : __DIR__"changl15",
                "south" : __DIR__"damen",
        ]));
        set("objects",([
                CLASS_D("lingjiu") + "/xuzhu" : 1,
        ]));
        set("valid_startroom", 1);
        setup();
        "/clone/board/lingjiu_b"->foo();
        replace_program(ROOM);
}