//Room: /d/dali/dahejieeast.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
        set("short","大和街");
        set("long", @LONG
大道旁店鋪林立，長街古樸，屋舍鱗次櫛比，道上人來車往，一
片太平熱鬧景象。路口種了倆顆大菩提樹，樹下有一個大洞(dong)。
一踏入巷中，陣陣茶花香氣撲鼻而來。
LONG );
        set("outdoors", "dali");
        set("exits",([ /* sizeof() == 1 */
            "north"  : "/d/dali/baiyiziguan",
            "south"  : "/d/dali/baiyiminju",
            "west"   : "/d/dali/shizilukou",
        ]));
        set("item_desc", ([
            "dong" : "黑呼呼的大洞，不知道有多深。\n",
        ]));
        set("no_clean_up", 0);
	set("coor/x", -19120);
	set("coor/y", -6900);
	set("coor/z", 0);
	setup();
}

void init()
{
        add_action("do_enter", "enter");
        add_action("do_enter", "zuan");
}

int do_enter(string arg)
{
        object me;
        mapping fam;

        me = this_player();
        if( !arg || arg=="" ) return 0;
        if( arg=="dong" )
        {
           if( (fam=query("family", me)) && fam["family_name"] == "丐幫" )
           {
               message("vision",
                        me->name() + "運起丐幫縮骨功，一彎腰往狗洞裏鑽了進去。",
                        environment(me), ({me}) );
               me->move("/d/gaibang/underdl");
               message("vision",
                        me->name() + "從洞裏走了進來。\n",
                        environment(me), ({me}) );
                        return 1;
           }
           return notify_fail("這麼小的洞，你鑽得進去嗎？\n");
       }
} 