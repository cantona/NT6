// room: /d/xingxiu/tianroad5.c
// Last Modified by winder on Feb. 28 2001

inherit ROOM;

void create()
{
        set("short", "天山山路");
        set("long", @LONG
這裏是天山東麓，山風從山上吹來，你冷得瑟瑟發抖。路邊是一片
針葉林。西邊望去，頂峯遙遙可見。
LONG );
        set("exits", ([
                "westup"   : __DIR__"tianroad6",
                "eastdown" : __DIR__"tianroad4",
                "north"    : "/d/npc/m_weapon/liandaoshi",
        ]));
        set("objects", ([
                __DIR__"npc/caiyaoren" : 1, 
        ]));
        set("item_desc", ([
                "cave" : "黑黢黢的山洞裏飄出一陣陰風，嚇得你直打哆嗦。\n"
        ]) );
//        set("no_clean_up", 0);
        set("outdoors", "xingxiu");
        set("coor/x", -52010);
        set("coor/y", 20100);
        set("coor/z", 40);
        setup();
        replace_program(ROOM);
}