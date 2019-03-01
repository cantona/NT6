inherit ROOM;

void create()
{
        set("short", "方丈室");
        set("long", @LONG
方丈室內的陳設相對來說比較簡單，正中的牆面上寫著個大大的
『佛』字。地上舖著一張大席子，一張矮幾就放在席子中間。兩邊是
兩個錦墊。在靠裡面的地方，有個蒲團，邊上是個小木魚，據說方丈
大師每天只需打坐片刻就精力充沛。
LONG );
        set("no_clean_up", 0);
        set("exits", ([
                  "south" : __DIR__"xiaoyuan",
        ]));
        set("objects", ([
                  __DIR__"npc/zhiqing" : 1,
        ]));

	set("coor/x", -5020);
	set("coor/y", 2230);
	set("coor/z", 10);
	setup();
        replace_program(ROOM);
}