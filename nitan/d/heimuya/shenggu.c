inherit ROOM;
 
void create()
{
        set("short", "聖姑堂");
        set("long", @LONG
這裡是黑木崖的聖姑所在地『聖姑堂』。堂上五彩雲羅，煞是漂
亮。堂中一位妙齡女子，青衫小袖，明艷不可方物。
LONG );
        set("exits", ([
            "west"   : __DIR__"chlang3",
        ]));
        set("objects", ([
            CLASS_D("riyue") + "/ren" : 1,
            __DIR__"npc/shinu":2,
        ]));       
//        set("no_clean_up", 0);
        setup();
        replace_program(ROOM);
}