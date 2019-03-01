#include <ansi.h> 
inherit ROOM;

void create()
{
        set("short", "百毒窟外");
        set("long", @LONG
這裡是五毒教飼養毒物的地方，山壁旁有一個天然的石洞，裡面
黑漆漆的看不清楚。一陣山風吹來，你聞到一股腥味。洞口有幾個五
毒教弟子正在閒聊。 
LONG
        );
        set("outdoors", "wudujiao");

        set("exits", ([
                "south" : __DIR__"baidu2",
                "north" : __DIR__"wdsl4",
        ]));
        set("objects", ([
                 __DIR__"npc/jiaotu": 4,
        ]));
    

        setup();
}

int valid_leave(object me, string dir)
{
        int i;
        object ob;
        me = this_player();

        if(dir == "south")
        {
                if( query("family/family_name", me) != "五毒教"
                & objectp(present("jiao tu", environment(me))))
                        return notify_fail(CYN "五毒教徒忽然擋住你，厲聲喝道：這位" +
                        RANK_D->query_respect(me) + "鬼頭鬼腦的想幹什麼？\n" NOR);
        }
        return ::valid_leave(me, dir);
}