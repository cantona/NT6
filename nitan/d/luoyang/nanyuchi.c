inherit ROOM;

void create()
{
        set("short", "男浴池");
        set("long", @LONG
這裡熱氣騰騰，煙霧裊繞，一切都在朦朧之中，當中好象有個很大的
浴池，一些人正在裡面盡情的享受著，微波粼粼，肉光閃動，你睜大眼睛
仔細一看，原來都是些大老爺們，沒勁沒勁。
LONG);
        set("no_clean_up", 0);
        set("exits", ([
                "west" : __DIR__"rest1",
        ]));
        set("objects", ([
                "/d/kaifeng/npc/obj/zaopeng" : 2,
        ]));
	set("coor/x", -6960);
	set("coor/y", 2150);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}