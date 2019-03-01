#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "赤壁古戰場");
        set("long", @LONG
這裡就是有名的古赤壁戰場，對岸一面巨大的懸崖絕壁之上書有
「赤壁」兩個大字，想當年曹操百萬精兵在此被周癒殺的片甲不留，
含恨而歸。文學家蘇東坡遊臨此地，便感慨的留下了『遙想公謹當年，
小喬初嫁了，羽扇綸巾，雄姿英發，談笑間，強虜灰飛煙滅……』令
後人引為佳句。從這裡向江面看去，只見滾滾江水東流去，江面上若
隱若現一條條大鐵索，原來是當年吳國為了抵御曹操而修的鎖江鏈。
LONG );
        set("outdoors", "jingzhou");
        set("item_desc", ([
                "tiesuo" : WHT "只見一條條鐵鎖鏈橫在江中，多年江水沖"
                           "擊依然不朽。\n" NOR,
        ]));
        set("exits", ([
                "east" : __DIR__"chibi5",
                            
        ]));
        set("objects", ([
                "/d/beijing/npc/shiren" : 1,
        ]));
        set("coor/x", -370);
        set("coor/y", -230);
        set("coor/z", -20);
        setup();
        replace_program(ROOM);
} 