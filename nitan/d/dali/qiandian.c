//Room: /d/dali/qiandian.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
        set("short","前殿");
        set("long", @LONG
這裡是大理國皇宮的前殿，紅磚綠瓦建得十分精巧，大理歷代國
主勤政愛民，萬幾宸函，都在此殿。因此大理雖偏處西南的小國，百
姓對當朝君臣的愛戴均出自肺腑，十分真誠。往北就到了御花園， 往
南是皇宮大門。
LONG );
        set("objects",([
           "/d/dali/npc/taijian": 1,
        ]));
        set("objects", ([
            CLASS_D("duan")+"/duanzm": 1,
        ]));
        set("exits",([ /* sizeof() == 1 */
            "north"  : "/d/dali/yuhuayuan",
            "south"  : "/d/dali/gongmen",
        ]));
	set("coor/x", -19140);
	set("coor/y", -6850);
	set("coor/z", 0);
	setup();
}