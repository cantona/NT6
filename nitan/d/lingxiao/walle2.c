// walle2.c

inherit ROOM;

void create()
{
        set("short", "城頭");
        set("long", @LONG 
雪花飄飄。站在這絕高之處，獨感天地之悠悠。回思歷代帝
皇，為成王圖霸業，每每出兵遠伐西域。山河遼闊，卻是無情戰
場，江山渺渺，偏是徵人墳地。此情此景，不由令人想起昔人所
言：“可憐無定河邊骨，猶是春閨夢裏人。”為一人之慾，苦天
下之人，古今同矣！
LONG );
        set("outdoors", "lingxiao");
        set("no_clean_up", 0);

        set("exits", ([
                "east"   : __DIR__"walle3",
                "west" : __DIR__"walle1",
        ]));
        set("objects", ([
                __DIR__"npc/dizi" : 1,
        ])); 
        setup();
        replace_program(ROOM);
}
