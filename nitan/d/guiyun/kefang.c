// Room: /d/guiyun/kefang.c
// Last Modified by winder on Jul. 9 2001

inherit ROOM;

void create()
{
        set("short","客房");
        set("long",@LONG
這是歸雲莊招待客人住宿的房間。室內陳設精雅，兩牀相對，枕衾
雅潔。北面窗外是一個大花園，江南景緻，盡在其中。
LONG
);
        set("exits",([
                "south" : __DIR__"zoulang2",
        ]) );
        set("no_clean_up", 0);
        set("sleep_room", 1);
        set("coor/x", 250);
        set("coor/y", -810);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}