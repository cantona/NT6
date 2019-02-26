// fu-cemen 富家側門
// Winder Oct.10 1998

inherit ROOM;

void create()
{
        set("short", "富家側門");
        set("long", @LONG
這裏是一道小門，可能是由於怕進出不方便而修建的。門雖
然小，但還修飾得人模人樣，門上嵌着兩個大銅環。幾條大狼狗
懶洋洋躺在門邊，一看見有人進來就‘汪汪’地亂吠。出了門就
是漢中鎮的南街了，進門後是富家的小院。
LONG
        );
        set("exits", ([
                "northwest" : __DIR__"nanjie",
                "east" : __DIR__"fu-xiaoyuan",
        ]));
        set("objects", ([
                __DIR__"npc/wolfdog" : 2,
        ]));
        set("coor/x", -12240);
	set("coor/y", 790);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}