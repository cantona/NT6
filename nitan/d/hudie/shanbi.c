// 山壁 shanbi.c
 
#include <ansi.h>
inherit ROOM;

void create() 
{ 
        set("short", "山壁");
        set("long", @LONG
這裏嫣紅奼紫，遍山遍野都是鮮花，春光浪漫已極，轉了幾個彎，
卻見迎面一塊山壁，路途已盡。旁邊是一排花叢(huacong)。
LONG );

        set("item_desc", ([
                "huacong" : "這是一排漂亮的花叢，幾隻蝴蝶從花從裏鑽了進去。\n",
        ]));

        set("outdoors", "蝴蝶谷");

        set("exits", ([ 
                "east" : "/d/wudang/wdroad2",
        ]));

        set("coor/x",80);
  set("coor/y",-170);
   set("coor/z",0);
   setup();
}

void init()
{
        add_action("do_bo", "bo");
}

int do_bo(string arg)
{
        object room, me;
        mapping fam;

        me = this_player();
        fam=query("family", me);

        if(!living(me) ) return 0;

        if ( me->is_busy() || me->is_fighting())
              return notify_fail("你正忙着哪！\n");

        if( !arg || arg != "huacong" ) return 0;

        if( arg == "huacong" ){
            if( (!fam || fam["family_name"] != "明教") && (!query_temp("hdq", me)) )
                return notify_fail("你撥了撥花叢，並沒有什麼發現，不禁有些悵然。\n");
            message_vision(HIC"$N撥了撥周圍的花叢，突然發現右邊"HIY"(Right)"HIC"好像有一條小路。\n"NOR, me);
            if(!(room = find_object(__DIR__"shanbi")))
              room = load_object(__DIR__"shanbi");
              set("exits/right", __DIR__"huacong1");
              call_out("delete_exit", 5, room);
              return 1; 
        }
}

void delete_exit(object room)
{       
        message("vision",HIW"一陣微風吹來，花叢動了起來，擋住了小路。\n"NOR, room);
        delete("exits/right");
}

int valid_leave(object me, string dir)
{
	return ::valid_leave(me, dir);
}