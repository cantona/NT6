//Room: /d/dali/road1.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
        set("short","");
        set("short", "宮門");
        set("long", @LONG
這裏是大理皇宮的宮門，門口放着兩個高大石獅，大理皇帝沒有
一點架子，從來不禁止人們進入皇宮，往南是御街，往北就進入皇宮
了。
LONG );
        set("outdoors", "daligong");
        set("exits",([ /* sizeof() == 1 */
            "north"  : "/d/dali/qiandian",
            "south"  : "/d/dali/yujie",
        ]));
	set("coor/x", -19140);
	set("coor/y", -6860);
	set("coor/z", 0);
	setup();
}