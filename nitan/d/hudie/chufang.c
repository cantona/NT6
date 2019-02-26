// 廚房 chufang.c
 
#include <ansi.h>
inherit ROOM;

void create() 
{ 
        set("short", "廚房");
        set("long", @LONG
這是一間寬敞的廚房，一個小童正在忙碌着作飯，整個房間瀰漫
着令人垂涎欲滴的菜香，看來這個小童的手藝還不錯。你走了半天本
來就餓的肚子不由地咕咕交了起來。
LONG );

        set("no_fight", 1);

        set("exits", ([ 
            "north" : __DIR__"huapu4",
            "south" : __DIR__"xfang2",
            "east" : __DIR__"caotang",
        ]));

        set("objects",([
            __DIR__"npc/xtong3" : 1,
        ]));

        setup();
}

int valid_leave(object me, string dir)
{
        object *ob = deep_inventory(me);
        int i = sizeof(ob);
        if((dir != "west")){
          while (i--)
          if(ob[i]->id("rice") || ob[i]->id("miantang") || ob[i]->id("qingcai"))
             return notify_fail(CYN"小僮哼了一聲：吃飽喝足了還要帶走呀！\n"NOR);                
        }
        return ::valid_leave(me, dir);
}