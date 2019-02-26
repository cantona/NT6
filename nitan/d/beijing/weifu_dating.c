inherit ROOM;

void create()
{
        set("short", "韋府大廳");
        set("long", @LONG
這裏就是鹿鼎公府的大廳，相當的寬敞明亮，四周的牆上懸掛滿
了各朝名人的真跡。正廳中央坐着兩個老者，較老的老者身旁邊還站
着一個老婦和一個四十多歲的中年男子，那男子骨瘦如柴，不住的咳
嗽。大廳北邊是韋公爺的書房，左右兩邊分別是兩個廂房。
LONG );
        set("exits", ([
                "north" : "/d/beijing/weifu_shufang",
                "south" : "/d/beijing/weifu_zoulang2",
                "west" : "/d/beijing/weifu_fangw",
                "east" : "/d/beijing/weifu_fange",
        ]));
        set("objects", ([
                "/d/beijing/npc/guixinshu" : 1,
                "/d/beijing/npc/guierniang" : 1,
                "/d/beijing/npc/guizhong" : 1,
                "/d/beijing/npc/liudahong" : 1,
        ]));
        set("outdoors", "beijing");
	set("coor/x", -2800);
	set("coor/y", 7710);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}