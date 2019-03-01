//Room: guozijian.c

inherit ROOM;

void create ()
{
        set ("short", "國子監");
        set("long", @LONG
國子監是朝廷培養人才的地方。高高低低的桌子排了兩排。在這
裡不時可以看到三三兩兩的學生模樣的人大聲爭辯著什麼問題，還有
一些老先生們蹙著眉頭匆匆的走過，象是在思考著什麼問題。
LONG );
        //set("item_desc", ([" *** " : " *** ", ]));

        set("exits", 
        ([ //sizeof() == 1
                "south" : "/d/changan/baihu3",
        ]));
        set("objects", 
        ([ //sizeof() == 1
                "/d/changan/npc/xueshi" : 1,
        ]));
              
        set("coor/x", -10710);
	set("coor/y", 1960);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}