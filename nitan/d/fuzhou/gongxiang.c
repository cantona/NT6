// Room: /d/fuzhou/gongxiang.c
// Last Modifyed by Evil on Sep. 10 2002

inherit ROOM;

void create()
{
        set("short", "宮巷");
        set("long", @LONG
舊名仙居，以巷中有紫極宮得名，是當今福州保護得最完整的古巷
坊。巷內現存明代的建築六幢，清代的建築十三幢。其中面積在萬平方
尺以上的深宅大院有十幢之多。福州歷代尤以近代名人多居于巷內，如
清兩江總督、福建船政大臣沈葆楨，林則徐之子林聰彝，清海軍總長劉
冠雄等。宮巷裡的豪門住宅結構精巧，單是室內的木雕石刻構件就今人
嘆為觀止。如漏花窗戶採用縷空精雕，榫接而成，而且通過木格骨骼的
各種精心編排構成了豐富的圖案裝飾。在木穿鬥、插鬥、童柱、月樑等
部件上常飾以重點雕刻。各種精巧生動的石刻在柱礎、台階、門框、
花座、柱桿上隨處可見。真可算是福州古建築藝術集大成者。
LONG );
        set("exits", ([
                "west" : __DIR__"nanhoujie6",
        ]));
        set("outdoors", "fuzhou");
        set("no_clean_up", 0);
	set("coor/x", -80);
	set("coor/y", -6240);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}