// Room: /d/taishan/yitian.c
// Last Modified by winder on Aug. 25 2001

inherit ROOM;

void create()
{
        set("short", "一天門");
        set("long", @LONG
從岱宗坊上山大約走四里，便來到一天門。北面有一座天階坊，過
了此坊便進入了登泰山的盤道。南面有一座更衣亭，士大夫們及其隨從，
都會在這裏換上輕便的服裝，才繼續登山。從一天門向北眺望，南天門
與十八盤在雲霧明滅間或隱或現，登泰山的人到此已有觀止之歎。附近
有一牌坊，嘉靖狀元羅洪先題額(e) 並聯(lian)，相傳為「孔子過泰山
側」的故事發生的地方。
LONG );
        set("exits", ([
                "southwest" : __DIR__"guandi",
                "northup"   : __DIR__"sanyibai",
                "southdown" : __DIR__"hongmen",
        ]));
        set("item_desc", ([
                "e"    : "孔子登臨處\n",
                "lian" : "秦王獨步傳千古  聖主遙臨慶萬年\n",
        ]));

        set("objects",([
                __DIR__"npc/dao-ke" : 1,
        ]));
        set("outdoors", "taishan");
        set("coor/x", 70);
	set("coor/y", 90);
	set("coor/z", 30);
	setup();
        replace_program(ROOM);
}