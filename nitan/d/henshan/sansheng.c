inherit ROOM;

void create()
{
        set("short", "三生塔");
        set("long", @LONG
三生塔是福嚴寺開山禪師慧思埋骨處，據說慧思禪師的三生均埋
骨這裡，故稱三生塔。不遠處有棵銀杏，據說曾受戒于慧思禪師，樹
齡千年，仍亭亭華蓋，歲歲青蒼。
LONG );
        set("exits", ([ 
               "southup"   : __DIR__"jigaoming",
               "northdown"     : __DIR__"shanlu8",
               "eastdown"  : __DIR__"fuyansi",
        ]));

        set("outdoors", "henshan");

        set("no_clean_up", 0);

	set("coor/x", -6950);
	set("coor/y", -5570);
	set("coor/z", 10);
	setup();
        replace_program(ROOM);
}