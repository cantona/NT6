//Room: /d/dali/xiaodao2.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
        set("short","林間小道");
        set("long", @LONG
這是一條卵石舖成的小道，曲曲折折地通向前方。兩邊是密密的
樹林這裡人跡罕至，惟聞足底叩擊路面，微風吹拂樹葉，沙沙作響。
LONG );
        set("outdoors", "dalic");
        set("exits",([ /* sizeof() == 1 */
            "northeast" : "/d/dali/heilongling",
            "west"      : "/d/dali/southgate",
        ]));
        set("no_clean_up", 0);
	set("coor/x", -19120);
	set("coor/y", -6910);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}