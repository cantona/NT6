// Room:  /d/luoyang/pingquan.c
// Last modified by winder 2002.11.11

inherit  ROOM;

void  create  ()
{
        set("short",  "平泉朝遊");
        set("long",  @LONG
在洛陽城南三十里，龍門西邊的山腳下，有個樑家屯村。這裏山巒
環抱，林木掩映，泉水源口，清溪縈迴，這就是唐武帝時宰相李德裕的
別墅。“平泉朝遊”是洛陽大八景之一。
LONG);
        set("exits",  ([  /*  sizeof()  ==  2  */
                "east" :  __DIR__"guandaos4",
        ]));
        set("outdoors", "luoyang");
        set("no_clean_up", 0);
	set("coor/x", -7000);
	set("coor/y", 2060);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}