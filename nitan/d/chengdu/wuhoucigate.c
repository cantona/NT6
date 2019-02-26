// Room: wuhoucigate.c
// Date: Feb.14 1998 by Java

inherit ROOM;
void create()
{
        set("short", "武侯祠大門");
        set("long", @LONG
這裏原來是武侯祠。大門人進人出，大多纏着武侯巾。原來武侯
生前治蜀，造福兩川，這武侯巾乃是他去世川人為其帶孝之俗。由於
武侯遺愛甚深，雖千載以下，川人頭巾仍不去首。
LONG );
        set("outdoors", "chengdu");
        set("exits", ([
                "northeast" : __DIR__"southroad3",
                "north"     : __DIR__"liubeidian",
        ]));
        set("no_clean_up", 0);
        set("coor/x", -15240);
	set("coor/y", -1860);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}