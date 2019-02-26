inherit ROOM;

void create()
{
        set("short", "煉丹房");
        set("long", @LONG
這裏是藥王谷的煉丹房，周圍牆壁都是用石塊砌成的，青磚鋪地，
房間中央放着一尊青銅築成的大丹爐。
LONG );
        set("no_fight", 1);
        set("exits", ([
                "north" : __DIR__"yuemen",
        ]));
        set("objects", ([
                __DIR__"npc/obj/danlu2" : 1,
        ]));
        setup();
        replace_program(ROOM);
}
