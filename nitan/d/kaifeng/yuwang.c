inherit ROOM;

void create()
{
        set("short", "禹王台");
        set("long", @LONG
禹王台建造于小山丘之上，這裡風景優美，環境幽雅，自古以來
就是人們遊春登高的勝地。相傳春秋時期，晉國盲人樂師曠常在此吹
奏古樂，故名『吹台』。
LONG );
        set("objects", ([
                  __DIR__"npc/woman" : 1,
        ]));
        set("no_clean_up", 0);
        set("exits", ([
                  "west" : __DIR__"shulin",
                  "eastup" : __DIR__"yuwangmiao",
        ]));
        set("outdoors", "kaifeng");

	set("coor/x", -5020);
	set("coor/y", 2100);
	set("coor/z", 10);
	setup();
        replace_program(ROOM);
}