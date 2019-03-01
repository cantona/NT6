// Room: eastroad1.c
// Date: Feb.14 1998 by Java

inherit ROOM;
void create()
{
        set("short", "東大街");
        set("long", @LONG
你走在東大街堅實的青石板地面上。南邊可以通向東城門，路邊
有一個簡陋的茶攤，一塊洗得發白了的舊帆布正頂著頭頂火辣辣的陽
光，一張長幾上放著幾只大號粗瓷碗 (Wan)。碗中盛滿著可口的茶水。
    往西北通往北大街，東北方一座大店面裡傳出陣陣劃拳的喧鬧。
LONG );
        set("outdoors", "chengdu");
        set("resource/water", 1);
        set("item_desc", ([
                "wan" : "香噴噴的大碗茶，來一碗吧！\n",
        ]));
        set("exits", ([
                    "northeast" : __DIR__"jiudian",
                    "northwest" : __DIR__"northroad3",
                    "south"     : __DIR__"eastroad2",
        ]));
        set("objects", ([
                    __DIR__"npc/xiaozei" : 1,
        ]));
        set("coor/x", -15200);
	set("coor/y", -1820);
	set("coor/z", 0);
	setup();
}

void init()
{
        add_action("do_drink","drink");
}

int do_drink(string arg)
{
        int current_water;
        int max_water;
        object me;

        me = this_player();
        current_water=query("water", me);
        max_water=query("str", me)*10+100;
        if (current_water<max_water)
        {
                set("water", current_water+60, me);
                message("vision", me->name() +
                        "端起一碗茶水來.... \n", environment(me), ({me}));
                write("你端起一碗茶水來.咕嚕.咕嚕..喝了個幹凈。真解渴呀！\n");
        }
        else write("你實在是喝不下了。\n");
        return 1;
}