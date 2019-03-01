// Room: /city/duchang.c
// YZC 1995/12/04 

inherit ROOM;

void create()
{
	set("short", "賭場");
        set("long", @LONG
這裡是揚州賭坊的大堂，四周的房間裡傳出來吆五喝六的賭博聲。
賭坊布置豪華，充滿了溫暖和歡樂，酒香中混合著上等脂粉的香氣，
銀錢敲擊，發出一陣陣清脆悅耳的聲音。世間幾乎沒有任何一種音樂
能比得上。這賭坊實在是個很奢侈的地方，隨時都在為各式各樣奢侈
的人，準備著各式各樣奢侈的享受。
LONG );
	set("item_desc", ([
		"paizi" : "二樓的拱豬房正處于測試階段。\n",
	]));
	set("objects", ([
		CLASS_D("shenlong")+"/pang" : 1,
                CLASS_D("shenlong")+"/shou" : 1,
	]));
        set("no_fight",0);
	set("exits", ([
		"west" : "/d/city/daxiao",
		"up"   : "/d/city/duchang2",
		"east" : "/d/city/nandajie1",
	]));
	set("coor/x", -10);
	set("coor/y", -10);
	set("coor/z", 0);
	setup();
}
