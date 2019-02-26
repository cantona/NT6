// zhenyue.c

inherit ROOM;

void create()
{
        set("short", "鎮嶽宮");
        set("long", @LONG
鎮嶽宮倚壁而構，四邊松林蔽日，景色幽美。宮前有玉井(jing)，
相傳井中曾生千葉白蓮。這裏地勢略為平坦，上、下山的遊客多在此
稍作休息再繼續前行。附近有幾間簡陋的旅社，欲登東峯觀日出者，
大都於頭晚歇息於此。
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