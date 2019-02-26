// Room: /d/huanggong/jingshan.c

inherit ROOM;

void create()
{
        set("short", "景山");
        set("long", @LONG
此地又名煤山, 萬壽山, 是一片風景秀麗的皇家園林. 在幽靜的鬆
柏林中, 一片鬱鬱葱葱的喜人綠意, 顯得蒼老和雄勁, 也含藴着無限的
嫵媚風光. 在山的東麓有一株槐樹, 即為崇禎帝死難處.
LONG
        );
        set("outdoors", "huanggong");
        set("exits", ([ /* sizeof() == 1 */
                "south" : __DIR__"shenwumen",
                "north" : "/d/beijing/hgmen_n",
        ]));
        set("no_clean_up", 0);

	set("coor/x", -2820);
	set("coor/y", 7761);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}