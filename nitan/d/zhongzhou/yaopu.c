inherit ROOM;

void create()
{
        set("short", "藥鋪");
        set("long", @LONG
這是中州城最大的藥鋪。從普通藥材到名貴的中草藥一應
俱全。濃濃的藥味讓你有點透不過氣來。店裏人來人往的，看
的出此處生意不錯。你如需要藥的話可以向小二買一點，如你
有藥方後院還可以讓你自己熬藥。
LONG);
        set("objects", ([
                  "/d/city/npc/huoji" : 1,
        ]));

        set("no_clean_up", 0);
        set("exits", ([
                  "north" : __DIR__"yaopuboss",
                  "west" : __DIR__"wendingbei2",
                  "south" : __DIR__"yaopu1",
        ]));

        set("coor/x", -9030);
	set("coor/y", -980);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}