// tyroad4.c 崎嶇山路
// by Marz 

inherit ROOM;

#include "feng.h"

string* npcs = ({
        "guest",
        "tufei2",
        "guest",
        "xiao_tufei",
        "guest",
        "xiao_louluo",
});

void create()
{
        int i = random(sizeof(npcs));

        set("short", "崎嶇山路");
        set("long", @LONG
你走在一條崎嶇狹隘的山路上，一邊是峭壁，一邊是懸崖。高高
的天柱峯(feng)籠罩在雲霧中，隱約可見。可是身旁的進香客和遊人
都仔細地町着自己的腳下，不敢抬頭望一眼，惟恐一不小心摔下去。
更有強人趁機打劫，行人無不噤聲閉氣，只求快點趕路。
LONG );
        set("outdoors", "wudang");
        set("exits", ([
                "westup" : "/d/wudang/tyroad3",
                "southdown" : "/d/wudang/tyroad5",
        ]));
        set("item_desc", ([
                "feng" : (:look_feng:),
        ]));
        set("objects", ([
                "/d/wudang/npc/"+npcs[i] : 1
        ]));
//        set("no_clean_up", 0);
        set("coor/x", -330);
        set("coor/y", -290);
        set("coor/z", 70);
        setup();
}

void init()
{
        add_action("look_feng", "look");
}