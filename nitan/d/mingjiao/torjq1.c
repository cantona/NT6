//TORJQ1.C

inherit ROOM;

void create()
{
        set("short", "青石大道");
        set("long", @LONG
這裏是通往鋭金旗的大道。道路開闊，大概可容十人並肩而行。
相傳鋭金旗是明教五旗中成立最早，規模最為宏偉的。百年來人才輩
出，除了守護明教外圍，還負責明教中所有兵器和護具的打造。
LONG );
        set("exits", ([
                "northeast" : __DIR__"torjq2",
                "southwest" : __DIR__"lhqpaifang",
        ]));
        set("no_clean_up", 0);
        set("outdoors", "mingjiao");
        setup();
        replace_program(ROOM);
}