inherit ROOM;

void create()
{
        set("short", "禹王廟");
        set("long", @LONG
禹王廟為追念大禹治水功德，在吹台上建造，廟內的大禹神像端
身平坐，一手握著把鐵鍬，目注遠方，來人多是祈求莫發大水的，西
下過去就是片樹林。
LONG );
        set("objects", ([
                  __DIR__"npc/obj/dayu" : 1,
        ]));
        set("no_clean_up", 0);
        set("exits", ([
                  "westdown" : __DIR__"yuwang",
        ]));

	set("coor/x", -5010);
	set("coor/y", 2100);
	set("coor/z", 20);
	setup();
        replace_program(ROOM);
}