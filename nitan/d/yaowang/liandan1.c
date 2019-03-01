inherit ROOM;

void create()
{
        set("short", "煉丹房");
        set("long", @LONG
這裡是藥王谷的煉丹房，周圍牆壁都是用石塊砌成的，青磚舖地，
房間中央放著一尊青銅築成的大丹爐。
LONG );
        set("no_fight", 1);
        set("exits", ([
                "south" : __DIR__"yuemen",
        ]));
        set("objects", ([
                __DIR__"npc/obj/danlu1" : 1,
        ]));
        setup();
        replace_program(ROOM);
}
