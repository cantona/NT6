// Room: /d/huanggong/taiji.c

inherit ROOM;

void create()
{
        set("short", "台基");
        set("long", @LONG
這個巨大的台基建在皇城的中軸線上, 有三層台階, 中間是鋪了地
毯的御道. 東西兩側各是一個日晷(gui)和一個嘉量(liang). 四周圍都
是漢白玉雕刻欄板, 景象無比壯觀. 三層台基每層都呈須彌座形, 四周
漢白玉欄杆環繞, 欄杆上共有一千四百五十八根望柱.
LONG
        );
        set("outdoors", "huanggong");
        set("exits", ([
                "south" : __DIR__"guangchang",
                "north" : __DIR__"taihedian",
        ]));
        set("objects", ([
                __DIR__"npc/suke" :1,
        ]));
        set("no_clean_up", 0);
        set("item_desc", ([
                "gui"   : "這原是時間的標準量器, 是皇帝受命于天的象徵.\n",
                "liang" : "這原是容積的標準量器, 是皇帝公正無私和至高無上的象徵.\n",
        ]));
	set("coor/x", -2800);
	set("coor/y", 7731);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}