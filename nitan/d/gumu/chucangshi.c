// Room: /d/gumu/chucangshi.c
// Last Modifyed by Winder on Jan. 14 2002

#include <room.h>
inherit ROOM;
#include <ansi.h>

void create()
{
        set("short", HIC"儲藏室"NOR);
        set("long", @LONG
古墓生活甚是清苦，儲藏室堆著些日常用品，都整整齊齊堆放在牆
角，看來經常有古墓弟子前來打掃，其余別無他物。
LONG        );

        set("exits", ([
                "east" : __DIR__"mudao22",
        ]));
        set("fire_count", 2);
        set("no_clean_up", 0);
        set("coor/x", -3240);
        set("coor/y", -20);
        set("coor/z", 90);
        setup();
}

void init()
{
        add_action("do_search", ({"search", "zhao"}));
}

int do_search(string arg)
{
        object ob, me = this_player();

        if ( arg == "qiangjiao" || arg == "牆角")
        {
                if( query_temp("fire", me)<3 )
                {
                        if(objectp(ob = present("fire", me)))
                                return notify_fail("你已經拿了火折了，怎麼這麼貪心？\n");
                        addn_temp("fire", 1, me);
                        message_vision(YEL "$N在牆腳的物品堆裡翻來翻去什麼也沒找著。\n"NOR, me);
                        return 1;
                }
                message_vision("$N在牆腳的物品堆裡翻來翻去找出一把火折。\n",me);
                delete_temp("fire", me);
                new("/clone/misc/fire")->move(me);
                return 1;
        }
        return notify_fail("你要找什麼？\n");         
}