#include <ansi.h>
inherit ROOM;

void create()
{
              set("short","小樹林");
        set("long", @LONG
這是峨嵋山金頂華藏庵外的一片小樹林。北邊是峨嵋派女弟子們
的寢宮的窗户，窗下好像蹲着一個人。
LONG );
              set("objects", ([
                   __DIR__"npc/songqingshu" : 1,
              ]));
              set("outdoors", "emei");
              set("exits",([
                  "northwest" : __DIR__"xiaoshulin3", 
                  "north"     : __DIR__"qinggong", 
              ]));
              setup();
}

int valid_leave(object me, string dir)
{
        int i;
        object ob;
        me = this_player();

        if (dir == "north")
        {
                if( query("family/family_name", me) != "峨嵋派"
                & objectp(present("song qingshu", environment(me))))
                        return notify_fail(CYN "宋青書一聲冷喝：閣下什麼"
                                           "人，在這裏鬼頭鬼腦的想幹什麼？\n" NOR);
        }
        return ::valid_leave(me, dir);
}