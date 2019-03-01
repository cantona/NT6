//Room: /d/dali/shulinwai.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
        set("short","樹林外");
        set("long", @LONG
你來到了一片黑森森的樹林面前，放眼望去，密密麻麻的都是樹
木，而且荊棘叢生，隱約可見有些小路東盤西曲。你仔細觀察，發現
這顯然是個人造的迷宮。其中暗合五行八卦，奇門遁甲，端的非同小
可，千萬不要冒然進去。
LONG );
        set("outdoors", "dalic");
        set("exits",([ /* sizeof() == 1 */
            "north"      : "/d/dali/heilongling",
            //"south"      : __DIR__"maze1",
        ]));
        set("no_clean_up", 0);
	set("coor/x", -19110);
	set("coor/y", -6910);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}