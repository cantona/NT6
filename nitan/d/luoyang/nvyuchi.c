inherit ROOM;

void create()
{
        set("short", "女浴池");
        set("long", @LONG
這裡熱氣騰騰，煙霧裊繞，一切都在朦朧之中，無法看個真切，微波
粼粼，肉光閃動，你睜大眼睛仔細一看，發覺這個世界上身材苗條的女子
真是多耶！再看看自己，不禁相形見絀。慚愧慚愧，還是趕快找個地方洗
澡吧！
LONG);
        set("no_clean_up", 0);
        set("exits", ([
                  "west" : __DIR__"rest2",
        ]));
        set("objects", ([
                "/d/kaifeng/npc/obj/zaopeng" : 2,
        ]));
	set("coor/x", -6970);
	set("coor/y", 2150);
	set("coor/z", 10);
	setup();
        replace_program(ROOM);
}