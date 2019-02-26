//Room: /d/dali/heilongling.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
        set("short","黑龍嶺");
        set("long", @LONG
黑龍嶺上有紅梅二株，幹已剝蝕貽盡，僅存枯皮，古質斑斕，橫
卧於地，離奇喬異，如驕龍，如橫峯，而花朵攢躦，又如錦片，如火
球，清芳襲人，不知植自何代，相傳以為唐梅，疑或然也。南面就是
黑龍潭。
LONG );
        set("outdoors", "dalic");
        set("exits",([ /* sizeof() == 1 */
            "north"      : "/d/dali/xiaodao1",
            "south"      : "/d/dali/shulinwai",
            "southwest"  : "/d/dali/xiaodao2",
        ]));
        set("no_clean_up", 0);
	set("coor/x", -19110);
	set("coor/y", -6900);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}