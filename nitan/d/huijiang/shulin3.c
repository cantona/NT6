// Room: /d/huijiang/shulin3.c
// Last Modified by winder on Sep. 12 2001

inherit ROOM;

void create()
{
        set("short", "樹林");
        set("long", @LONG
湖邊的這樹林並不茂密，只是稀疏的幾棵，遠處高山上覆蓋着白雪，
如同天上白色的雲彩。湖中碎冰相互撞擊的叮叮聲猶自傳來。林中野花
的香味從腳下升上來，在林中鋪了淺淺的一層。
LONG );
        set("outdoors", "huijiang");
        set("exits", ([ /* sizeof() == 2 */
                "north" : __DIR__"shulin",
                "west" : __DIR__"shulin2",
        ]));
        set("no_clean_up", 0);
        set("coor/x", -50040);
        set("coor/y", 9030);
        set("coor/z", 20);
        setup();
        replace_program(ROOM);
}