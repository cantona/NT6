// Room: /d/huangshan/guanyin.c
// Last Modified by winder on Sep. 27 2001

inherit ROOM;
void create()
{
        set("short", "觀音石");
        set("long", @LONG
由半山寺上來，過雲門到天都峰下，看到一個亭亭玉立的石人，活
象一尊古裝仕女，人稱觀音石。正面一塊小石，恰如跪拜之童子，這“
小甚侏儒大娉婷”的兩塊巧石，正好構成“童子拜觀音”。從這裡便開
始了“盤空千萬仞，險若上丹梯。迥入天都裡，回看鳥道低”的登頂過
程。
LONG
        );
        set("exits", ([ 
                "southdown"  : __DIR__"banshan",
                "northup"    : __DIR__"yingke",
                "east"       : __DIR__"jiyu",
        ]));
        set("objects", ([
                __DIR__"obj/guanyin" : 1,
                __DIR__"obj/xiaotong" : 1,
        ]) );
        set("outdoors", "huangshan");
        set("coor/x", -595);
        set("coor/y", -1060);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}