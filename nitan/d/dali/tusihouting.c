//Room: /d/dali/tusihouting.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
        set("short","後廳");
        set("long", @LONG
議事廳後是後廳，是一樓一底的中式建築。屋角雕刻細密，紋飾
精美，各種圖案和禽獸花木的雕刻，栩栩如生，紋路新穎。這是雲南
十八座土司府中保留最好的一座。
LONG );
        set("exits",([ /* sizeof() == 2 */
            "south"  : "/d/dali/tusimentang",
         "down" : "/d/xueshan/mishi" , 
        ]));
        set("no_clean_up", 0);
	set("coor/x", -19141);
	set("coor/y", -6881);
	set("coor/z", -1);
	setup();
        replace_program(ROOM);
}