inherit ROOM;

void create()
{
        set("short", "石階");
        set("long", @LONG
這裡是嵩山南麓的少室山山腳。一條長長的石階如同巨龍般蜿蜒
而上，直沒雲端。嵩山群峰壁立，翠色滿山，令人俯仰間頓生渺小之
意。邊上有幾個叫賣的小販和挑夫，似乎在嚷嚷著爭吵些什麼。
LONG );
        set("exits", ([
                "east"    : "/d/songshan/taishique",
                "west"    : __DIR__"xiaojing1",
                "northup" : __DIR__"shijie2",
        ]));
        set("objects",([
                __DIR__"npc/xiao-fan" : 1,
                __DIR__"npc/tiao-fu" : 2,
                "/clone/npc/walker" : 1,
        ]));
        set("outdoors", "shaolin");
        setup();
        replace_program(ROOM);
}
