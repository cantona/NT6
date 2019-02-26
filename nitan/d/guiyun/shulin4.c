// Room: /d/guiyun/shulin4.c
// Last Modified by winder on Jul. 9 2001

inherit ROOM;

void create()
{
        set("short", "樹林深處");
        set("long",@LONG
這是一片小樹林。地面上綠草如蔭，茂密地生長着。樹葉的縫隙間
偶爾會有一隻小鳥被驚起，四周十分靜寂。
LONG
);
        set("exits",([
                "northwest" : __DIR__"shulin5",
                "east"      : __DIR__"shulin6",
                "south"     : __DIR__"shulin3",
        ]) );
        set("no_clean_up",0);
        set("outdoors", "guiyun");
        set("coor/x", 300);
        set("coor/y", -810);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}
