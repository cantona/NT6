// Room: /d/guiyun/shulin7.c
// Last Modified by winder on Jul. 9 2001

inherit ROOM;

void create()
{
        set("short", "樹林深處");
        set("long",@LONG
這是一片小樹林的深處。地面上綠草如蔭，茂密地生長着。樹葉的
縫隙間偶爾會有一隻小鳥被驚起，四周十分靜寂。這裏時常有毒蛇出沒，
最好不要在此久留。
LONG
);
        set("exits",([
                "south" : __DIR__"shulin5",
        ]) );
        set("objects",([
                __DIR__"npc/snake" : 2,
        ]));  
        set("outdoors", "guiyun");
        set("coor/x", 290);
        set("coor/y", -790);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}
