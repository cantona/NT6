inherit ROOM;

void create()
{
        set("short", "大廳");
        set("long", @LONG
這裏是寺內的大廳，幾位有道的高僧在高聲辯論。看來正在引經
據典，爭鬥機鋒。
LONG );
        set("exits", ([
                "east"  : __DIR__"zoulang1",
                "west"  : __DIR__"zoulang2",
                "north" : __DIR__"cangjing",
                "south" : __DIR__"cangjingge",
                "southwest" : "/d/xueshan/hongdian",
        ]));
        set("objects", ([
                CLASS_D("xueshan")+"/jiumozhi" :1,
        ]));
        setup();
        replace_program(ROOM);
}