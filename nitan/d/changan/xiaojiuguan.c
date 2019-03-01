//Room: xiaojiuguan.c

inherit ROOM;

void create ()
{
        set ("short", "小酒館");
        set("long", @LONG
這是一家小酒館，屋子並不是很寬敞，酒水也是長安城裡最最廉
價的，可是卻仍然有許多人來光顧，也不知道他們是來喝酒的，還是
來欣賞那位坐在櫃台後面的老板娘。
LONG );
        set("exits", 
        ([ //sizeof() == 1
                "north" : "/d/changan/liande-nankou",
        ]));
        set("objects", 
        ([ //sizeof() == 1
                "/d/changan/npc/ruhua" : 1,
        ]));

        set("no_clean_up", 0);
        set("coor/x", -10680);
	set("coor/y", 1890);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}