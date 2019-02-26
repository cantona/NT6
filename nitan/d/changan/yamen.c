//Room: yamen.c

inherit ROOM;

void create ()
{
        set ("short", "衙門大門");
        set("long", @LONG
這是長安城的衙門大門，也是長安城最高的行政機構，這裏負責
管理城裏的大事小情。無論是偷雞摸狗的小賊，還是放火殺人的強盜，
都會在這裏受到應有的處罰。牆上貼着一張告示(gaoshi)
LONG );
        set("item_desc", ([
                "gaoshi": ""
        ]) );
        set("exits", 
        ([ //sizeof() == 2
                "south" : "/d/changan/yamen-datang",
                "north" : "/d/changan/qinglong3",
        ]));
        set("objects", 
        ([ //sizeof() == 1
                "/d/changan/npc/yayi" : 4,
        ]));

        set("coor/x", -10710);
	set("coor/y", 1900);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}