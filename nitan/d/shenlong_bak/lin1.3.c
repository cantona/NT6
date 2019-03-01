inherit DEMONROOM;

void create()
{
        set("short", "東灌木林");
        set("long",@LONG
這是一片灌木林。你沒有想到這樣一個孤島上竟有這樣大一片灌
木林，不由感到非常吃驚。
LONG);

        set("exits", ([
                "east"  : __DIR__"lin1.4", 
                "west"  : __DIR__"lin1.2",

        ]));


                
                set("n_time", 60); 
                set("n_npc", 2); 
                set("n_max_npc", 20);
                set("s_npc", "/clone/dream_npc/shenlongdao/snake/fushe");

        set("outdoors", "shenlong");
        setup();
}
