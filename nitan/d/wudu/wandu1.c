#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "萬毒窟外");
        set("long", @LONG
這裏是五毒教飼養毒物的地方，山壁旁有一個天然的石洞，裏面
黑漆漆的看不清楚。一陣山風吹來，你聞到一股腥味。有一個衣衫襤
褸的枯瘦老婦正靠在洞邊打盹。 
LONG);
        set("outdoors", "wudujiao");

        set("exits", ([
                "south" : __DIR__"wandu2",
                "north" : __DIR__"wdsl3",
        ]));
        set("objects", ([
                CLASS_D("wudu") + "/hehongyao" : 1,
        ]));
        setup();
}
int valid_leave(object me, string dir)
{
        if (dir == "south")
        {
                if( query("family/master_name", me) != "何鐵手"
                & objectp(present("he hongyao", environment(me))))
                        return notify_fail(CYN "何紅藥身形一晃，擋住你喝道：沒有"
                                           "教主准許，誰也不得進入本教聖地。\n"
                                           NOR);
        }
        return ::valid_leave(me, dir);
}