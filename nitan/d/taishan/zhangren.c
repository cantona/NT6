// Room: /d/taishan/zhangren.c
// Last Modified by Winder on Aug. 25 2001

inherit ROOM;

void create()
{
        set("short", "丈人峰");
        set("long", @LONG
這裡位于玉皇頂以西裡許的地方，形狀有如一個傴僂的老人。附近
有數塊俊秀小石，故又有“老翁弄孫”之稱。峰上有“天下第一山”、
“凌霄峻極”、“中天獨立”、“東柱第一靈區”諸刻，並有乾隆詩刻
：“丈人五岳自青城，岱頂何來假借名。卻是世人知此慣，誰因杜老句
詳評。”
    靠西有黃華洞，因洞路極為危險，後人在進路處寫上「回車巖」。
從這裡往北走便是岱頂的北天門。
LONG );
        set("exits", ([
                "southeast" : __DIR__"yuhuang",
                "northup"   : __DIR__"beitian",
        ]));
        set("objects",([
                __DIR__"npc/wei-shi1" : 2,
        ]));
        set("outdoors", "taishan");
        set("coor/x", 20);
	set("coor/y", 320);
	set("coor/z", 210);
	setup();
        replace_program(ROOM);
}