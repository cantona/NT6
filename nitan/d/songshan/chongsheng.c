// Room: /d/songshan/chongsheng.c
// Last Modified by Winder on Jul. 15 2001

inherit ROOM;

void create()
{
        set("short", "崇聖門");
        set("long", @LONG
崇聖門前古神庫有四座鎮庫鐵人，高達丈許，振臂握拳，怒目挺胸，
身姿雄健。向北就是中嶽廟最大的殿宇中嶽大殿了。
LONG );
        set("exits", ([
                "north" : __DIR__"dadian",
                "south" : __DIR__"tianzhongge",
        ]));
        set("no_clean_up", 0);
        set("coor/x", 0);
        set("coor/y", 720);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}