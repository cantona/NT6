// Room: /d/huanggong/lou1.c

inherit ROOM;

void create()
{
        set("short", "角樓");
        set("long", @LONG
角樓中央是一個三開間的方亭樓, 四出抱廈. 最頂部十字脊鍍金寶
頂以下, 計有三層檐, 九樑, 十八柱, 七十二條脊, 上下重疊, 縱橫交
錯. 底座是白玉石台基周圍飾以白玉欄桿. 它緊扼內城一角, 能控制四
下, 內城四角各有一座這樣的角樓, 若有風吹草動, 都可一清二楚.
LONG
        );
        set("outdoors", "huanggong");
        set("exits", ([ /* sizeof() == 1 */
                "down" : __DIR__"jiao1",
        ]));
        set("no_clean_up", 0);

	set("coor/x", -2780);
	set("coor/y", 7701);
	set("coor/z", 10);
	setup();
        replace_program(ROOM);
}