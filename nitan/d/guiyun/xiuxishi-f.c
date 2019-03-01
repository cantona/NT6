// Room: /d/guiyun/xiuxishi-f.c
// Last Modified by winder on Jul. 9 2001

inherit ROOM;

void create()
{
        set("short", "女廂房");
        set("long", @LONG
這裡是歸雲莊女弟子的休息室，擺著幾張木床。床旁都有一支高腳
架子，用來掛衣物。屋角一張幾凳，放了一盆蘭花，散著淡淡幽香。
LONG );
        set("exits",([
                "west" : __DIR__"lianwuchang",
        ]) );
        set("no_clean_up",0);
        set("no_fight", 1);
        set("sleep_room", 1);
        set("coor/x", 260);
        set("coor/y", -860);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}