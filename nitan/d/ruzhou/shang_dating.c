#include <ansi.h> 
inherit ROOM;

void create()
{
        set("short", "商家堡大廳");
        set("long", @LONG
這裡是商家堡的大廳，大廳內很是寬敞明亮，地上刻有一個
巨大的鐵八卦。正對廳門擺放著一張八仙桌，一人壓座中堂，身
材高大魁梧，留著短須，神情甚為嚴肅，正是「八卦刀」商劍鳴。
LONG);
        set("exits", ([
                "north"  : __DIR__"shang_houting",
                "south"  : __DIR__"shang_xiaojin2",
                "east"  : __DIR__"shang_tinge",
                "west"  : __DIR__"shang_tingw",
        ]));
        set("objects", ([
                CLASS_D("shang") + "/ming" : 1,
        ]));
        set("no_clean_up", 0);
        set("valid_startroom", 1);
	set("coor/x", -6750);
	set("coor/y", 1880);
	set("coor/z", 0);
	setup();
}


int valid_leave(object me, string dir)
{
        int i;
        object ob;
        me = this_player();

        if (dir == "north" || 
           dir == "east" || 
           dir == "west")
        {
                if( query("family/family_name", me) != "商家堡" && 
                   query("born_family", me) != "山東商家" && 
                   objectp(present("shang jianming", environment(me))))
                        return notify_fail(CYN "商劍鳴對你喝道：什麼東西，居然"
                                           "敢在我面前放肆！\n" NOR);
        }
        return ::valid_leave(me, dir);
}