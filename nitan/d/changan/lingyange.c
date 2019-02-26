//Room: lingyange.c

inherit ROOM;

void create()
{
        set("short", "凌煙閣");
        set("long", @LONG
窄窄的門，窄窄的樓梯，佈置清雅的房間，窗户都很寬大從窗內
看出去，滿城秋色俱在眼前。
LONG );
        set("exits", ([ /* sizeof() == 1 */
                "west" : "/d/changan/fengxu4",
        ]));

        set("coor/x", -10690);
	set("coor/y", 1920);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}