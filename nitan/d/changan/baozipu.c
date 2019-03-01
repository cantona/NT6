//Room: baozipu.c

inherit ROOM;

void create ()
{
        set ("short", "包子舖");
        set("long", @LONG
舖子裡的擺設並不是很講究，橫豎擺了幾排圓木方桌，桌子四周
零亂的放了幾把長條椅子。一個小伙計沒精打採的靠在櫃台邊，看見
你進來，只是懶洋洋的向你打了個招呼。看起來這裡的生意並不怎麼
好。
LONG );
        //set("item_desc", ([" *** " : " *** ", ]));
        set("exits", 
        ([ //sizeof() == 1
                "north" : "/d/changan/yongtai-nankou",
        ]));
        set("objects", 
        ([ //sizeof() == 1
                "/d/changan/npc/huoji" : 1,
        ]));

        set("no_clean_up", 0);
        set("coor/x", -10760);
	set("coor/y", 1880);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}