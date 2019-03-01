// /d/beihai/jiulongbi.c
// Last Modified by winder on May. 22 2002

inherit ROOM;

void create()
{
        set("short", "九龍壁");
        set("long", @LONG
這裡是小西天西之九龍壁，青白玉基台，上有綠琉璃須彌座，壁面
前後各有九條形態各異，奔騰在雲霧波濤中的蛟龍浮雕。壁東面為江崖
海水，旭日東升流雲紋飾，西面為江崖海水，明月當空流雲紋飾。影壁
用四百二十四塊七色琉璃磚砌築而成。色彩絢麗，古樸大方。
LONG
        );
        set("exits", ([
                "east"  : __DIR__"xitian",
                "south" : __DIR__"dukou1",
        ]));
        set("outdoors", "beihai");
        set("no_clean_up", 0);

        set("coor/x", -190);
        set("coor/y", 4090);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}