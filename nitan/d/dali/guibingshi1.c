//Room: /d/dali/guibingshi1.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
        set("short","貴賓室");
        set("long",@LONG
這是一間貴賓室，這裡窗明幾亮，用具考究。單是窗邊一架
紫竹軟榻已是價值不菲。憑窗眺望，隱隱于淡煙之中可見蒼山的
玉局峰，只見山勢清秀，翠碧欲滴，令人心曠神怡。
LONG);
        set("exits",([ /* sizeof() == 1 */
            "out"      : __DIR__"zoulang3",
        ]));
        set("no_clean_up", 0);
	set("coor/x", -19142);
	set("coor/y", -6912);
	set("coor/z", 8);
	setup();
        replace_program(ROOM);
}