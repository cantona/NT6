//ROOM: fen0.c
inherit ROOM;

void create()
{
        set("short", "風雷堂");
        set("long", @LONG
這裡是日月神教教下第一大堂。這裡距黑木崖不遠，教下第一大
堂堂主童百熊掌管此堂。
LONG );
        set("exits", ([
            "north" :  __DIR__"grass1",
        ]));
        set("objects",([
            CLASS_D("riyue") + "/tongbw": 1,
        ]));
//        set("no_clean_up", 0);
        setup();
        replace_program(ROOM);
}
