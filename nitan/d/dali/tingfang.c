//Room: /d/dali/tingfang.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
        set("short","花廳");
        set("long", @LONG
這裡是鎮南王府的內廳。整個大廳十分寬闊。雖說是王府，但擺
設很簡單，正中間有兩張太師椅，邊上擺滿了各種各樣的山茶花。
LONG );
        set("objects",([
            CLASS_D("dali")+"/guducheng": 1,
        ]));
        set("exits",([ /* sizeof() == 1 */
            "north"  : "/d/dali/yongdao1",
            "west"   : "/d/dali/chufang",
            "east"   : "/d/dali/shufang",
            "south"  : "/d/dali/changlang",
        ]));
        set("no_clean_up", 0);
	set("coor/x", -19101);
	set("coor/y", -6841);
	set("coor/z", -1);
	setup();
        replace_program(ROOM);
}