// Room: /d/mingjiao/shanjiao.c
// Date: Java 97/05/11

#include <room.h>
inherit ROOM;

void create()
{
    set("short", "昆侖山下");
        set("long", @LONG
這裡是千裡昆侖的東麓，遠望蒼天浩浩，白雲悠悠。東方沃野千
裡，楚天遼闊；西面高山巍巍，迤邐萬裡。叱□武林八百年的明教就
座落在這群山之中。明教----是多少武林豪傑所向往的地方，在那裡，
有無數生死相許的好兄弟，無論是正是邪。就在這西方的群山之後，
等待著你去譜寫又一曲武林傳奇。
LONG );
    set("exits", ([
        "west" : __DIR__"tomen2",
        "east" : __DIR__"gebitan5",
                "northwest" : "/d/kunlun/zhenyuanqiao", 
    ]));
        set("objects", ([
                __DIR__"npc/monkey" : 2,
        ]));

    set("outdoors", "mingjiao");
    set("no_clean_up", 0);
    setup();
    replace_program(ROOM);
}
