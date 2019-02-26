//Room: tea-shop.c

inherit ROOM;

void create()
{
        set("short", "茶館");
        set("long", @LONG
這間茶房是長安的閒人雜聚的場所，裏面橫七豎八的擺放着一些
木製的桌椅。一個説書的老人正在滔滔不絕的講着什麼。一些茶客一
邊品茶，一邊聽書，一邊繪聲繪色交頭接耳，如果你要想打聽江湖掌
故和謠言，來這裏準沒錯。
LONG );
        set("exits", ([ /* sizeof() == 1 */
                "south" : "/d/changan/qixiang2",
        ]));
        set("objects", ([
                "/d/changan/npc/teawaiter" : 1,
                "/d/changan/npc/laoren" :1,
        ]) );

        set("coor/x", -10740);
	set("coor/y", 1970);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}