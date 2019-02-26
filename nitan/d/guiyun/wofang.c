// Room: /d/guiyun/wofang.c
// Last Modified by winder on Jul. 9 2001

inherit ROOM;

void create()
{
        set("short","卧房");
        set("long",@LONG
這是莊主的卧房。房間不大，收拾得很乾淨。屋中的小八仙桌上放
着一把酒壺和一隻酒盅，看來主人常常以飲酒自繾。
LONG );
        set("exits",([
                "east" : __DIR__"houting",
        ]) );
        set("no_clean_up",0);
        set("coor/x", 230);
        set("coor/y", -830);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}