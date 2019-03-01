// 草徑 caojing.c
 
#include <ansi.h>

inherit ROOM;
void create() 
{ 
        set("short", "草徑");
        set("long", @LONG
這是一片草地，過了這片草地有七八間茅屋，茅屋的前後左右都
是花圃，看來已經到了蝶谷醫仙胡青牛的住處了。
LONG );

        set("outdoors", "蝴蝶谷");

        set("exits", ([ 
            "north" : __DIR__"maowu",
            "west" : __DIR__"maopeng",
            "south" : __DIR__"niupeng",
            "east" : __DIR__"xfang1",
]));

        setup();
}

int get_object(object ob)
{
        return (userp(ob));
}

int valid_leave(object me, string dir)
{
        object *ob, *inv;
        mapping myfam;
        myfam =( mapping)query("family", me);

        inv = deep_inventory(me);
        if (dir == "south"){
          write("南面是一片花圃，裡面種滿了諸般花草。\n");
          ob = filter_array(inv,(:get_object:));        
          if (myfam && myfam["family_name"] =="明教" && myfam["generation"] == 35 && ! sizeof(ob))
          write("由于你已聽聞張教主的教誨，走慣了這片花圃，所以信步走了出去。\n");
          else {
             tell_room(environment(me), me->name()+"往南面的牛棚快步離開。\n"NOR, ({ me }));
             me->move(__DIR__"huapu1");
             tell_room(environment(me), me->name()+"從草徑快步走了過來。\n"NOR, ({ me }));
             me->look();
             return notify_fail("");
          }
        }
        return ::valid_leave(me, dir);
}
