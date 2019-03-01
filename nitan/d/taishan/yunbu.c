// Room: /d/taishan/yunbu.c
// Last Modified by winder on Aug. 25 2001

inherit ROOM;

void create()
{
        set("short", "雲步橋");
        set("long", @LONG
在快活三裡北首就是雲步橋。因谷深林茂，常有雲霧縈繞，楊承訓
題“雲步橋”。橋北大壑忽臨斷崖，壁立如削。崖上石坪坦豁，傳宋真
宗曾在此駐蹕，故名御帳坪，今柱窩尚存。岱頂下諸水奔流而來，飛瀑
下瀉，濺沫迸珠，生雲化霧，蔚為壯觀，故又名飛瀑巖、天河、護駕泉。
崖上有“紅橋飛瀑”、“霖雨蒼生”、“河山元脈”、“太古清音”等
題刻。明代陳鳳梧有詩：“百丈崖高鎖雲煙，半空垂下玉龍涎。天晴六
月常飛雨，風靜三更自奏弦。蒼水佩懸雲片片，珠簾洞織月娟娟。晚山
倒著肩輿下，回看斜陽景更艷。”
    此處東有酌泉亭，由此西上，就是三蹬崖。
LONG );
        set("exits", ([
                "east"   : __DIR__"zhuoquan",
                "south"  : __DIR__"kuaihuosan",
                "westup" : __DIR__"sandengya",
        ]));
        set("outdoors", "taishan");
        set("no_clean_up", 0);
        set("coor/x", 60);
	set("coor/y", 210);
	set("coor/z", 100);
	setup();
        replace_program(ROOM);
}