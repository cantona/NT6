// /d/xingxiu/silk3.c
// Last Modified by winder on Feb. 28 2001

inherit ROOM;
int do_climb(string arg);

void create()
{
        set("short", "絲綢之路");
        set("long", @LONG
這是一條中原和西域之間的商道。南面連綿的祁連山脈在陽光的照
射下好像是一條玉帶。東邊是中原，西面則通往西域。西南有一座黃沙
堆積形成的山(mount)。
LONG );
        set("outdoors", "silu");
        set("exits", ([
                "eastup"    : __DIR__"songmoya",
                "west"      : __DIR__"shimen",
                "northwest" : __DIR__"yanzhishan",
        ]));
        set("objects", ([
                "/d/hangzhou/honghua/huo" :1,
                __DIR__"npc/trader" : 1,
        ]));
        set("item_desc", ([
                "mount" : 
                "這是一座黃沙堆積形成的山。微風吹動，沙山發出嗡嗡的響聲。你\n" 
                "不禁對自然的造物發出由衷的讚歎。\n"
        ]) );
        set("no_clean_up", 0);
        set("coor/x", -21500);
        set("coor/y", 600);
        set("coor/z", 0);
        setup();
}

void init()
{
        add_action("do_climb", "climb");
}
int do_climb(string arg)
{
        object me;
        me = this_player();

        if( !arg || arg=="" ) return 0;
        if( arg=="mount")
        {
                message("vision", me->name() + "吭吃吭吃向沙山上爬去。\n", environment(me), ({me}) );
                me->move("/d/xingxiu/shashan");
                message("vision", me->name() + "從沙山下爬了上來，粘了一身沙子。\n", environment(me), me );
                return 1;
        }
}

#include "/d/xingxiu/job2.h";
