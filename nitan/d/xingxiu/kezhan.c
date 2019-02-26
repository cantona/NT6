// Room: /d/xingxiu/kezhan.c
// Last Modified by winder on Apr. 25 2001

inherit ROOM;

void create()
{
        set("short", "客棧");
        set("long", @LONG
這裏是伊犁城的客棧，門口放有一個大茶桶(tong)，有免費的茶水
供應，客站裏的小姑娘正在買烤熟的羊肉。你如果累了可以到樓上睡一
覺。
LONG);
        set("resource/water", 1);
        set("exits", ([ 
                "up"    : __DIR__"kezhan2",
                "south" : __DIR__"yili",
                "east"  : __DIR__"majiu",
        ]));
        set("item_desc", ([
              "tong" : "一隻裝滿茶水的大茶桶，你可以舀(drink)起來喝。\n"
        ]) );
        set("objects", ([
                __DIR__"npc/xiaoer" : 1    
        ]));
        set("coor/x", -39000);
        set("coor/y", 13100);
        set("coor/z", 0);
        setup();
        "/clone/board/kedian14_b"->foo();
//        replace_program(ROOM);
}

void init()
{
        add_action("do_drink", "drink");
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
                set("water", current_water+30, me);
                message("vision", me->name()+"用茶勺從茶桶中舀了一口茶水來喝。\n", environment(me), ({me}) );
                write("你舀了一口桶中的茶水來喝。\n");
        }
        else write("你再也喝不下了。\n");
        return 1;
}