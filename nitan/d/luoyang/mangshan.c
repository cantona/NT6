// Room: /d/luoyang/mangshan.c
// Last modified by winder 2002.11.11

inherit ROOM;

void create()
{
        set("short", "邙山晚眺");
        set("long", @LONG
俗話説“生在蘇杭，葬在北邙”，古人把氣勢雄偉，土質深厚的北
邙當作死後長眠的好地方。孟津新莊村附近古冢林立，這就是東漢諸陵
和王公大臣們的墓葬區。
LONG);
        set("exits", ([  /*  sizeof()  ==  2  */
                "northwest" : __DIR__"shangqing",
                "northeast" : __DIR__"lvzuan",
                "southdown" : __DIR__"road6",
        ]));
        set("outdoors", "luoyang");
        set("no_clean_up", 0);
	set("coor/x", -6990);
	set("coor/y", 2270);
	set("coor/z", 10);
	setup();
        replace_program(ROOM);
}