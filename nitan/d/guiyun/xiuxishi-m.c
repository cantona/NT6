// Room: /d/guiyun/xiuxishi-m.c
// Last Modified by winder on Jul. 9 2001

inherit ROOM;

void create()
{
        set("short", "男廂房");
        set("long", @LONG
這裡是歸雲莊男弟子的休息室，擺著幾張木床。床旁都有一支高腳
架子，用來掛衣物。西首一扇小窗。外面是練武場。
LONG );
        set("exits",([
                "east" : __DIR__"lianwuchang",
        ]) );
        set("no_clean_up",0);
        set("no_fight", 1);
        set("sleep_room", 1);
        set("coor/x", 240);
        set("coor/y", -860);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}