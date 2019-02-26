// Room: /d/huanggong/qinandian.c
inherit ROOM;

void create()
{
        set("short", "欽安殿");
        set("long", @LONG
欽安殿位於御花園內, 殿頂為平頂四坡式, 周圍有漢白玉石欄板. 
殿內供奉玄武大帝, 殿旁有魚池假山, 奇花異樹. 北邊穿過御花園壘石
砌就的堆秀山, 就是皇宮的北門神武門了.
LONG
        );
        set("exits", ([
                "north"     : __DIR__"shenwumen",
                "south"     : __DIR__"yuhuayuan2",
        ]));
	set("coor/x", -2820);
	set("coor/y", 7741);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}