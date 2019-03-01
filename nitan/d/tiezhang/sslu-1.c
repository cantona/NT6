inherit ROOM;

void create()
{
        set("short", "碎石路");
        set("long", @LONG
你走在一條用碎石鋪成的小路上。兩旁山勢低緩，長滿了翠綠的毛竹，
陣陣微風吹過，耳旁便響起一片沙沙聲。
LONG    );
        set("exits", ([
                "eastup" : __DIR__"sslu-2.c",
                "westdown" : __DIR__"pingtai",
        ]));
        set("no_clean_up", 0);
        set("outdoors", "tiezhang");

        setup();
        replace_program(ROOM);
}