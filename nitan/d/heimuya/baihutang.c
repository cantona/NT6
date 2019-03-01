inherit ROOM;
 
void create()
{
        set("short", "白虎堂");
        set("long", @LONG
這裡是黑木崖的第二大堂『白虎堂』。堂內青磚舖地，堂內橫屍
滿地。
LONG );
        set("exits", ([
            "north"   : __DIR__"baistep2",
            "south"      : __DIR__"chitang", 
        ]));
        set("objects", ([
            CLASS_D("riyue") + "/shanggy": 1,
        ]));       
//        set("no_clean_up", 0);
        setup();
        replace_program(ROOM);
}