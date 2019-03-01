// Room: /d/taishan/weiping.c
// Last Modified by Winder on Aug. 25 2001

inherit ROOM;

void create()
{
        set("short", "圍屏山");
        set("long", @LONG
這是泰山的其中一座山峰，又名懸石峰。山的東面有一個虎頭崖，
其形狀有如一頭伏虎。南面有避風崖，崖上大大地刻著「振衣岡」三字
于上面。崖南隔澗為蓮花峰，上題“海日石蓮”。峰東為五花崖，俗呼
望人峰。舊時谷中有盤路，登峰視道中往來行人如蟻。峰頂二石鉤連于
上，名試心石。舊傳朝山者登之，心誠則不動，不誠則搖跌入崖底。北
邊則有北鬥壇。從這裡往東走，便可到達伺奉泰山之神碧霞元君的碧霞
祠。
LONG );
        set("exits", ([
                "westdown" : __DIR__"tianjie",
                "eastdown" : __DIR__"bixia",
        ]));
        set("no_clean_up", 0);
        set("outdoors", "taishan");
        set("coor/x", 50);
	set("coor/y", 300);
	set("coor/z", 220);
	setup();
        replace_program(ROOM);
}