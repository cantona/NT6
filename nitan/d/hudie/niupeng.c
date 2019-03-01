// 牛棚 niupeng.c
 
#include <ansi.h>
inherit ROOM;

void create() 
{ 
        set("short", "牛棚");
        set("long", @LONG
這裡是蝴蝶谷的牛棚，據說因倒斃在這裡的人不計其數，使得『
見死不救』胡青牛的大名天下聞名。
LONG );

        set("outdoors", "蝴蝶谷");

        set("exits", ([ 
            "south" : __DIR__"kongdi",
            "northdown" : __DIR__"caojing",
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
        if (dir == "northdown"){
          write("北面是一片花圃，裡面種滿了諸般花草。\n");
          ob = filter_array(inv,(:get_object:));        
          if (myfam && myfam["family_name"] =="明教" && myfam["generation"] == 35 && ! sizeof(ob))
          write("由于你已聽聞張教主的教誨，走慣了這片花圃，所以信步走了進去。\n");
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
