// Room: /d/taishan/ertian.c
// Last Modified by winder on Aug. 25 2001

inherit ROOM;

void create()
{
        set("short", "二天門");
        set("long", @LONG
這裡又叫「中天門」。中天門峻嶺闊谷，樓閣簇擁。東有中溪山突
兀俏麗，可觀日出，望晚霞；西有鳳凰嶺蜿蜓伸展，可遠眺傲徠雄姿，
俯視山下城廓。佇立坊下，北瞻巍巍岱峰，眾山拱立，林茂泉飛，纜車
凌空，天然成畫。
    一般的登山者來到這裡都已累極，但是這裡才是泰山的一半啊！面
對前面險峻的十八盤，很多人都不禁猶豫起來。
LONG );
        set("exits", ([
                "north"     : __DIR__"kuaihuosan",
                "southdown" : __DIR__"huima",
        ]));
        set("objects",([
                __DIR__"npc/tiao-fu" : 1,
                CLASS_D("taishan")+"/tiansong" : 1,
        ]));
        set("outdoors", "taishan");
        set("coor/x", 60);
	set("coor/y", 190);
	set("coor/z", 100);
	setup();
        replace_program(ROOM);
}