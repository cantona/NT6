// shijie1.c

inherit ROOM;

void create()
{
        set("short", "石階");
        set("long", @LONG
山路突然陡峭，兩旁山峯筆立，中間留出一條窄窄的石階，僅能
兩人並肩而行。
LONG );
        set("outdoors", "heimuya");
        set("exits", ([
            "eastdown" : __DIR__"shandao2",
            "westup"   : __DIR__"shijie2",
        ]));
        set("objects", ([
            CLASS_D("riyue") + "/fansong": 1,
        ]));
//        set("no_clean_up", 0);
        setup();
        replace_program(ROOM);
}