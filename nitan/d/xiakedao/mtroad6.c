// mtroad6.c  山間平地

inherit ROOM;

void create()
{
        set("short", "山間平地");
        set("long", @LONG
這裡是森林中的一塊小平地。長草沒脛，野花浪漫，四周都是
密密的森林。時不時傳來陣陣野獸嘶叫，飛鳥啼鳴。西南有一高崖
突兀而起，極是險峻。
LONG );
        set("outdoors", "motianya");
        set("exits", ([
                "east"  : __DIR__"mtroad4",
                "west"  : __DIR__"mtroad4",
                "north" : __DIR__"mtroad4",
                "south" : __DIR__"mtroad4",
        ]));
        set("objects", ([
//                __DIR__"npc/shipopo" : 1,
                CLASS_D("lingxiao")+"/shipopo" : 1,
        ]));
        set("coor/x", -1900);
        set("coor/y", -1700);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}