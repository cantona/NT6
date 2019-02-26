// gebi5.c
#include <room.h>
inherit ROOM;
void create()
{
       set("short","西域大戈壁");
       set("long", @LONG
這是西域的大戈壁，要走出這裏並非易事。不遠處塵土沙粒鋪天蓋
地般吹來，看來要起風暴了。
LONG);
        set("exits", ([
                "north" : __DIR__"gebi2",
                "south" : __DIR__"gebi3",
                "east" : __DIR__"gebi4",
                "west" : __DIR__"gebi1",
        ]));
        set("outdoors", "hasake");
        set("no_quest",1);
        setup();
}

void init()
{
       object me = this_player();
       switch(random(4)) {
       case 0 : set_temp("gc_n",1, me); 
       tell_object(me,"直覺告訴你：往北走有一片綠洲。\n");break;
       case 1 : set_temp("gc_s",1, me); 
       tell_object(me,"直覺告訴你：往南走有一片綠洲。\n");break;
       case 2 : set_temp("gc_e",1, me); 
       tell_object(me,"直覺告訴你：往東走有一片綠洲。\n");break;
       case 3 : set_temp("gc_w",1, me); 
       tell_object(me,"直覺告訴你：往西走有一片綠洲。\n");break;
       }       
       if(me->query_skill("dodge", 1) <= 150) 
            addn("jing", -15, me);
       else addn("jing", -5, me);
}
