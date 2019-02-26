inherit ROOM;

void create()
{
        set("short", "後堂");
        set("long", @LONG
絕情谷後堂擺放着各種珍奇的古董和陶瓷，正中靠牆處的
櫃子上供着一尊泥像，泥像下輕煙繚繞，想必是絕情谷開山祖
師的靈位。
LONG);
        set("exits", ([
               "west"   : __DIR__"zhifang",
               "north"   : __DIR__"jianshi",
               "east"   : __DIR__"chucangshi",
               "south"   : __DIR__"changlang4",
        ]));

        set("no_clean_up", 0);

        setup();
        replace_program(ROOM);
}
