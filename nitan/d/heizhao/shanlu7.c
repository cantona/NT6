// Room: /heizhao/shanlu7.c
// Date: Dec. 8 1999 by Winder

inherit ROOM;

void create()
{
        set("short", "山路");
        set("long", @LONG
你邁開大步徑行入山。循著陡路上嶺，約莫走了一個時辰，道
路更窄，有些地方需側著身子方能過去。但見路旁山峰插天，想來
夏日裡定能將驕陽全然遮去，倒也顯見頗為清涼。
LONG );
        set("outdoors", "taoyuan");
        set("no_clean_up", 0);
        set("exits", ([
                "eastdown" : __DIR__"shanlu6",
                "northup"  : __DIR__"shanlu8",
        ]));
        set("coor/x", -5010);
        set("coor/y", -1300);
        set("coor/z", 10);
        setup();
        replace_program(ROOM);
}