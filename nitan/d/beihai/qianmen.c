// /d/beihai/qianmen.c
// Last Modified by winder on May. 22 2002

inherit ROOM;

void create()
{
        set("short", "前門");
        set("long", @LONG
這裏是北海的前門，由於北海是專門供皇宮貴族遊樂的地方，所以
一向是禁區，普通老百姓是不可以進去的。門是硃紅色的，門楣上掛這
一塊匾(bian)，門口站着兩個衞士。
LONG
        );
        set("cost", 2);
        set("item_desc", ([
                "bian" : "這是一塊黑色的匾，上面用金漆寫了四個大字:北海 禁苑\n",
        ]));
        set("exits", ([
                "east"      : __DIR__"shulin",
                "southwest" : __DIR__"zhaojing",
        ]));
        set("outdoors", "beihai");
        set("no_clean_up", 0);

        set("coor/x", -180);
        set("coor/y", 4070);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}