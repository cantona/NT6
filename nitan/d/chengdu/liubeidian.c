// Room: liubeidian.c
// Date: Feb.14 1998 by Java

inherit ROOM;
void create()
{
        set("short", "劉備殿");
        set("long", @LONG
這裡是武侯祠的劉備殿。正中供著漢昭烈帝，高可丈許。後主卻
沒得供奉，所謂 "扶不起來" 的阿鬥吧。而哭廟玉碎的北地王劉諶得
能和英父同祀，令人不勝唏噓。    殿下左右是趙雲等的武將廊和蔣
琬為首的文臣廊。
LONG );
        set("exits", ([
                "south"   : __DIR__"wuhoucigate",
                "northup" : __DIR__"wuhouci",
        ]));
        set("no_clean_up", 0);
        set("coor/x", -15240);
	set("coor/y", -1850);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}