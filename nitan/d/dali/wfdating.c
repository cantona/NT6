//Room: /d/dali/wfdating.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
        set("short","鎮南王府大廳");
        set("long", @LONG
進了大廳，放眼看那大廳，只見正中一塊，橫匾，寫着‘邦國柱
石’四個大字，下首署着‘丁卯御筆’四個小字，楹柱中堂懸滿了字
畫，一時也看不了這許多。向北是鎮南王總理國務見人辦公之處，西
邊是帳房，往東是一條石徑通往內宅。
LONG );
        set("objects",([
            "/d/dali/npc/jiading": 1,
        ]));
        set("exits",([ /* sizeof() == 1 */
            "west"   : "/d/dali/zhangfang",
            "east"   : "/d/dali/shijing",
            "north"  : "/d/dali/zonglichu",
            "out"    : "/d/dali/wangfugate",
        ]));
	set("coor/x", -19121);
	set("coor/y", -6861);
	set("coor/z", -1);
	setup();
        replace_program(ROOM);
}