// mishi2.c
inherit ROOM;
#include <ansi.h>
void create()
{
        set("short", "柳園");
        set("long", @LONG
這是一座小小的園子，裡面種滿了大大小小的柳樹，柳枝有的長
可及地，有的還是新枝嫩葉，但中間有一株灌木(guanmu)低低矮矮的，
長在那裡，非常惹人注目，你不禁朝那裡多看了兩眼。
LONG );
        set("exits", ([
            "west" : __DIR__"xiaoyuan",
        ]));
        set("objects", ([
            __DIR__"obj/guanmu" : 1,
        ]) );
        set("outdoors", "meizhuang");
        setup();
        replace_program(ROOM);
}
void reset()
{
        object *inv;
        object con, item, guanmu;
        ::reset();
        guanmu= present("guanmu", this_object());
        inv = all_inventory(guanmu);
        if( !sizeof(inv)) {
        con = new(__DIR__"obj/honghua");
        item = new(__DIR__"obj/zhuguo");
        item->move(con);
        con->move(guanmu);
        }
}
