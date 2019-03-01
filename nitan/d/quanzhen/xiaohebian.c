// /d/quanzhen/xiaohebian.c
// Java Oct.10 1998

inherit ROOM;

void create()
{
        set("short", "小河邊");
        set("long", @LONG
此處位於終南山角一偏僻處，只見濃蔭匝地，花光浮動，周圍盡
是叁天古木，頗具幽靜之美。不遠處的小河由山洞(dong)中湧出的泉
水所形成，淙淙的水聲更讓你覺得身心順暢。往北可通往山林深處。
往西可進入山洞中。
LONG
        );
        set("outdoors", "zhongnan");
        set("item_desc", ([
                "dong" : "一個深邃、幽暗、恐怖的小山洞。\n",
        ]));
        set("exits", ([
                "enter" : __DIR__"shandong1",
                "north" : __DIR__"shanlu7",
        ]));

        set("coor/x", -3160);
        set("coor/y", 0);
        set("coor/z", 20);
        setup();
        replace_program(ROOM);
}