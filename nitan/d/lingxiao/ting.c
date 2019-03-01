inherit ROOM; 

#include <ansi.h>;

void create()
{
    set("short", "戲梅亭");
    set("long", @LONG 
這裡是凌霄城的戲梅亭，是凌霄城主白自在平時最喜歡來的
地方。從這裡俯瞰群山，披襟當風，只覺萬裡江山，不如金樽一
醉。在廳柱上刻著一句詩(poem)，是白老爺子酒後性至，仗劍所
留。但有人卻說白老爺子生平最是好名，這樣說是自己打自己嘴
巴，可也沒人正直到敢在白老爺子面前譏諷半句。
LONG);
            set("exits", ([
                "west" : __DIR__"meiroad3",
            ])); 
        set("objects", ([ 
                __DIR__"obj/ban" : 3,
        ])); 
        set("item_desc", ([
                "poem" : HIR "\n\n          忍把浮名，換了淺酌低唱。\n\n" NOR,
        ]) );
        setup();
            set("outdoors", "lingxiao");
            set("no_clean_up", 0);
            setup();
        replace_program(ROOM);
}
