#include <ansi.h> 

inherit ROOM;

void create()
{
        set("short", "苗家後廳");
        set("long", @LONG
這裏是苗家的後廳，廳內非常的寬敞明亮。正中擺放着張
八仙桌，四周牆壁上掛着一些字畫。只見一個臉色透黃，神情
嚴肅的瘦高個子正座中堂，正是「金面佛」苗人鳳。
LONG);
        set("exits", ([
                  "west"  : __DIR__"miaojia_zoulang1",
                  "north" : __DIR__"miaojia_zoulang2",
                  "south" : __DIR__"miaojia_shufang",
        ]));
        set("objects", ([
                CLASS_D("miao") + "/miao" : 1,
        ]));

        set("no_clean_up", 0);
        set("valid_startroom", 1);
        set("coor/x", -8990);
	set("coor/y", -960);
	set("coor/z", 0);
	setup();
        "/clone/board/miao_b"->foo();
}

int valid_leave(object me, string dir)
{
        int i;
        object ob;
        me = this_player();

        if (dir == "north" || dir == "south")
        {
                if( query("family/family_name", me) != "中原苗家"
                & objectp(present("miao renfeng", environment(me))))
                        return notify_fail(CYN "苗人鳳眉頭微微一皺，喝道：閣下未"
                                           "免太過放肆，是瞧不起苗某人嗎？\n" NOR);
        }
        return ::valid_leave(me, dir);
}