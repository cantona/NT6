// Room: /d/guiyun/shulin2.c
// Last Modified by winder on Jul. 9 2001

inherit ROOM;

void create()
{
        set("short", "樹林");
        set("long",@LONG
這是一片小樹林。地面上綠草如蔭，茂密地生長着。樹葉的縫隙間
偶爾會有一隻小鳥被驚起，四周十分靜寂。
LONG
);
        set("objects",([
                __DIR__"npc/bee" : 1,
        ]));  
        set("exits",([
                "east"  : __DIR__"shulin1",
                "south" : __DIR__"caodi2",
        ]) );
        set("outdoors", "guiyun");
        set("coor/x", 280);
        set("coor/y", -820);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}
