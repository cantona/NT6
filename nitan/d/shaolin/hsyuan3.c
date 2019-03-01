// Room: /d/shaolin/hsyuan3.c
// Date: YZC 96/01/19

inherit ROOM;

void create()
{
        set("short", "和尚院三部");
        set("long", @LONG
這裡是僧眾們飲食起居的地方。靠牆一溜擺著幾張木床，床上舖
的是篾席。床頭疊著床薄換，冬天想必很冷，僧侶們全靠紮實的內功
根基御寒。地上整齊的放著幾個蒲團和木魚。
LONG );
        set("sleep_room",1);
        set("exits", ([
                "east" : __DIR__"zhulin3",
                "south" : __DIR__"hsyuan2",
        ]));
        set("objects",([
                CLASS_D("shaolin") + "/hui-se" : 1,
        ]));
//        set("no_clean_up", 0);
        setup();
        replace_program(ROOM);
}
