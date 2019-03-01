// zhenyue.c

inherit ROOM;

void create()
{
        set("short", "鎮岳宮");
        set("long", @LONG
鎮岳宮倚壁而構，四邊鬆林蔽日，景色幽美。宮前有玉井(jing)，
相傳井中曾生千葉白蓮。這裡地勢略為平坦，上、下山的遊客多在此
稍作休息再繼續前行。附近有幾間簡陋的旅社，欲登東峰觀日出者，
大都于頭晚歇息于此。
LONG );
        set("exits", ([ /* sizeof() == 3 */
            "northdown"  : __DIR__"jinsuo",
            "eastup"     : __DIR__"yunu",
            "southwest"  : __DIR__"lianpath1",
        ]));

        set("item_desc", ([
            "jing" : "井中水色碧透，掬手可飲。\n",
        ]));

        set("outdoors", "huashan" );
        set("resource/water", 1);

        setup();
        replace_program(ROOM);
}