// tyroad5.c 崎嶇山路
// by Marz 

inherit ROOM;

#include "feng.h"

void create()
{
        set("short", "崎嶇山路");
        set("long", @LONG
你走在一條崎嶇狹窄的山路上，一邊是峭壁，一邊是懸崖，高高
的天柱峰(feng)在雲霧中隱約可見。身旁的進香客和遊人都仔細地盯
著自己的腳下，不敢抬頭望一眼，惟恐一不小心摔下去。更有強人趁
機打劫，行人無不噤聲閉氣，只求快點趕路。
LONG );
        set("outdoors", "wudang");
        set("exits", ([
                "northup" : "/d/wudang/tyroad4",
                "eastdown" : "/d/wudang/tyroad6",
        ]));
        set("item_desc", ([
                "feng" : (:look_feng:),
        ]));
        set("no_clean_up", 0);
        set("coor/x", -330);
        set("coor/y", -300);
        set("coor/z", 60);
        setup();
}

void init()
{
        add_action("look_feng", "look");
}