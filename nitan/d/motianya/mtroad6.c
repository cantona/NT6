// mtroad6.c  山間平地

inherit ROOM;

void create()
{
        set("short", "樹林");
        set("long", @LONG
這裏是森林中的一塊小平地。長草沒脛，野花浪漫，四周都是密
密的森林。時不時傳來陣陣野獸嘶叫，飛鳥啼鳴。西南有一高崖突兀
而起，極是險峻。
LONG );
        set("outdoors", "motianya");
        set("exits", ([
            "east"  : __DIR__"mtroad4",
            "west"  : __DIR__"mtroad4",
            "north" : __DIR__"mtroad4",
            "south" : __DIR__"mtroad4",
        ]));
        set("objects", ([
                CLASS_D("lingxiao")+"/shipopo" : 1,
        ]));

        setup();
        replace_program(ROOM);
}
