// Room: /d/guiyun/shulin3.c
// Last Modified by winder on Jul. 9 2001

inherit ROOM;

void create()
{
        set("short", "樹林");
        set("long",@LONG
這是一片小樹林。地面上綠草如蔭，茂密地生長著。樹葉的縫隙間
偶爾會有一只小鳥被驚起，四周十分靜寂。
LONG
);
        set("objects",([
                __DIR__"obj/stick" : 1,
        ]));  
        set("exits",([
                "west"  : __DIR__"shulin1",
                "north" : __DIR__"shulin4",
                "south" : __DIR__"caodi3",
        ]) );
        set("outdoors", "guiyun");
        set("coor/x", 300);
        set("coor/y", -820);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}
