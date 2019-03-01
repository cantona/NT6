#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", WHT "第二指節" NOR );
        set("long", @LONG
這裡已到了中指峰的半山腰了，由于鐵掌山排列得象手指一樣，每座山
峰又再分為三截，就如手指的指節一般，因此這裡又正是位于第二指節的位
置。這裡離峰頂已近，透過淡淡的雲霧，似已可以看到山路的盡頭了。左前
方二十于丈處，黑黝黝的似有一個洞穴(dong)，洞口砌以玉石，修建得極是
齊整。
LONG    );
        set("exits", ([
                "south" : __DIR__"sslin-5",
                "northup" : __DIR__"shanlu-8",
                "enter" : __DIR__"dong1",
]));
        set("objects", ([
                __DIR__"npc/mayi" : 2,
]));

        set("item_desc", ([ 
                "dong" : WHT "一個黑黝黝的山洞。黑暗中偶爾有幾點磷光閃過。\n" NOR,
]));
        set("no_clean_up", 0);
        set("outdoors", "tiezhang");
        setup();
}

int valid_leave(object me, string dir)
{        
        if (dir == "enter" && objectp(present("mayi zhanglao", environment(me))))
           return notify_fail(CYN "麻衣長老喝道：此乃鐵掌幫禁地，任何人不得入內，否則有死無生！\n" NOR);
                
        return ::valid_leave(me, dir);
}
